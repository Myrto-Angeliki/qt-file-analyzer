﻿# qt-file-analyzer

---


## Development Environment
- Qt Creator 19.0.1
- Qt version 6.11.0


## Project description

Developed a multithreaded desktop file analyzer in C++ and Qt with asynchronous file analysis to keep the UI responsive during processing.

## Features
- Open text/log files
- Display file contents
- Count lines/words
- Find the three most common words in the file
- Search and highlight keywords
- Asynchronous file analysis to keep the UI responsive

## Technologies
- Qt Widgets
- QFile
- QTextStream
- QtConcurrent
- signals & slots

## Architecture
- GUI implemented with Qt Widgets
- File handling using QFile and QTextStream
- Background processing implemented with QtConcurrent
- Communication handled with Qt signals and slots

## Screenshots

### Main Window
![Main Window](screenshots/1_main_window.png)

### Attempt at analysis or search without opening a file
![File not Selected](screenshots/2_file_not_selected.png)

### File Opened
![File Selected](screenshots/3_file_selected.png)

### File analysis
![File analysis](screenshots/4_after_analysis.png)

### Search Functionality
![Search Functionality](screenshots/5_string_highlighted.png)


## Build Instructions

```bash
git clone https://github.com/yourusername/qt-file-analyzer.git
cd qt-file-analyzer

mkdir build
cd build

cmake ..
cmake --build .











