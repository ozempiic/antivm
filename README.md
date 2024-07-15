# Anti Virtual-Machine

## Overview

This program detects virtual machine environments by checking for specific files and file patterns commonly associated with virtualization technologies. If any of these files or patterns are found, the program terminates with an error message indicating that it cannot run in a virtual machine environment.

## How It Works

- **File Checking**: The program checks for the existence of certain files in critical system directories.
- **Pattern Matching**: It also searches for files matching specific patterns that are characteristic of virtual machine configurations.
- **Detection Logic**: If any of the monitored files or patterns are found, the program displays an error message stating "This program can't run in a virtual machine." and exits.
- **Inspiration**: This program is inspired by techniques outlined at [Unprotect.it, Detecting Virtual Environment Files](https://unprotect.it/technique/detecting-virtual-environment-files/) and has been extended to include additional file patterns.

## Additional Notes

This program utilizes Windows API functions for file system operations and pattern matching. It temporarily disables file system redirection on 64-bit systems to ensure accurate file checks.

## Usage

Compile the program using a C++ compiler that supports Windows API, such as Visual Studio or MinGW. Run the executable on a Windows system to detect virtual machine environments.

## Disclaimer

This program is for educational purposes and is not intended for malicious use. Use responsibly and respect local laws and regulations regarding software usage.

