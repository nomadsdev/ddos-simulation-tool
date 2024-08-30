
# DDoS Simulation Tool

## Overview
This project is a simple Distributed Denial of Service (DDoS) simulation tool designed to send multiple HTTP/HTTPS requests to a specified URL or IP address. It utilizes multithreading to simulate a large number of simultaneous connections, which can overwhelm the target server. This tool is intended strictly for educational purposes and should **not** be used for any malicious activities.

## Features
- **Supports HTTP and HTTPS:** Automatically switches between HTTP and HTTPS based on the port (80 for HTTP, 443 for HTTPS).
- **Custom User-Agent Strings:** Load configurable user-agent strings from an external file to simulate requests from various clients.
- **Multithreading:** Simulates multiple concurrent requests using threads.
- **Timeout Settings:** Customize connection and receive timeouts for each request.

## Prerequisites
- **Operating System:** Windows
- **Compiler:** GCC (for compiling the code)

## Compilation
To compile the source code, run the following command in your terminal:

```bash
gcc ddos.c -o ddos -lwininet
```

## Usage
### 1. Prepare the User-Agent File
- Create a file named `qa.txt` inside the `bin` directory of your project.
- Add one user-agent string per line in this file.

### 2. Run the Tool
- Open a command prompt and navigate to the directory containing the `ddos` executable.
- Run the program by executing `ddos.exe`.

### 3. Input Parameters
- When prompted, enter the target URL or IP address and the port number.
- If you enter port `443`, the program will use HTTPS; otherwise, it will default to HTTP.

### 4. Behavior
- The tool continuously sends requests to the specified URL or IP address using multiple threads.
- Each request uses a randomly selected user-agent string from the `qa.txt` file.

## Example
```bash
Enter the URL or IP address: example.com
Enter the port number (e.g., 80): 80
```
This will start sending HTTP requests to `example.com` on port `80`.

## Ethical Considerations
This tool should **only** be used on servers that you own or have explicit permission to test. Unauthorized use against other servers is illegal and unethical.

## Performance
The number of threads (`num_threads`) is set to `100000` by default. Depending on your system's capabilities and the target server, you may need to adjust this number. Running too many threads may overwhelm your own system before impacting the target.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
