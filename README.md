# DDoS Simulation Tool 
 
## Overview 
This project is a simple Distributed Denial of Service (DDoS) simulation tool designed to send multiple HTTP requests to a specified URL or IP address. It uses multithreading to simulate a large number of simultaneous connections to overwhelm the target server. This tool is intended for educational purposes and should not be used for malicious activities. 
 
## Features 
- Supports both HTTP and HTTPS connections. 
- Configurable user-agent strings loaded from an external file. 
- Multithreading to simulate multiple concurrent requests. 
- Ability to set connection and receive timeouts. 
 
## Prerequisites 
- Windows operating system. 
- GCC compiler (for compiling the code). 
 
## Compilation 
To compile the source code, use the following command: 
 
```bash 
gcc ddos.c -o ddos -lwininet 
``` 
 
## Usage 
1. **Prepare the User-Agent File:** 
- Create a file named `qa.txt` in the `bin` directory of your project. 
- Add user-agent strings, one per line, in this file. 
2. **Run the Tool:** 
- Open a command prompt and navigate to the directory containing the `ddos` executable. 
- Execute the program by running `ddos.exe`. 
3. **Input Parameters:** 
- The program will prompt you for the target URL or IP address and port number. 
- If the port number is 443, the program will use HTTPS. 
4. **Behavior:** 
- The tool will continuously send requests to the specified URL or IP address using multiple threads. 
- It will use random user-agent strings from the `qa.txt` file for each request. 
 
## Example 
```bash 
Enter the URL or IP address: example.com 
Enter the port number (e.g., 80): 80 
``` 
This will start sending HTTP requests to example.com on port 80. 
 
## Notes 
- **Ethical Considerations:** This tool should only be used on servers that you own or have explicit permission to test. Unauthorized use against other servers may be illegal and unethical.

- **Performance:** The number of threads (`num_threads`) is set to 100000 by default, which may be excessive. Adjust this number based on your testing needs and system capabilities. 
 
## License 
This project is licensed under the MIT License.
