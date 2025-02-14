# Offline Flashcards by Kali Forces

**Offline Flash Cards System Created by Kali Forces**

## Flashcards

This repository contains the executable file for the Flashcards program.

### How to Download and Run

#### Installing Prerequisites

To compile the code, you need to have both `g++` and Git Bash installed on your system. Follow these steps:

#### Installing g++

1. Download MinGW from [MinGW website](http://www.mingw.org/).
2. Run the installer and select the `g++` component during installation.
3. Add the MinGW `bin` directory to your system PATH. This allows you to run `g++` from the command line.

#### Installing Git Bash

1. Download Git Bash from [Git for Windows](https://gitforwindows.org/).
2. Run the installer and follow the on-screen instructions to install Git Bash.
3. During installation, you can choose the default options or customize them based on your preferences.

Once both `g++` and Git Bash are installed, you can proceed with the compilation and execution of the program.

### Download and Installation

#### Method 1: Clone the Repository using Git

1. Click on **Code**, then with the HTTPS option selected below **Clone**, copy the URL to clipboard.
2. Create a folder where you want to import/clone the repository.
3. Go inside the folder, right-click, and select `Open Git Bash here`.
4. Inside the Bash console, paste the URL you copied before like this and run the command:
   ```bash
   git clone https://github.com/xsupremeyx/offline-flashcards-kali-forces.git
5. This should clone the repository.

6. Now run the `install.bat` file inside the `hack_the_hills` folder.

7. This should successfully create the `program.exe` file inside the `hack_the_hills` folder. Run this executable file to use our program.

### Method 2: Download the ZIP File

1. Download the ZIP directly.

2. Inside the `hack_the_hills` folder, run the batch file `install.bat`. This should install the executable file properly.

3. Use the `program.exe` inside the `hack_the_hills` folder on your Windows machine to use the program.

### Compiling the Source Code

If you prefer to compile the source code yourself, use the following command:
```bash
g++ FlashCards.cpp -o program.exe
