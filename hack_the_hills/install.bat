@echo off
echo Compiling FlashCard.cpp...
g++ FlashCard.cpp -o program.exe
if %errorlevel% neq 0 (
    echo Compilation failed. Please ensure g++ is installed and in your PATH.
    pause
    exit /b 1
)
echo Compilation successful. program.exe created.
pause
