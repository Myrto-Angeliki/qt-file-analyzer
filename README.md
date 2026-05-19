﻿
# qt-file-analyzer

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
<img src="/screenshots/1_main_window.PNG" alt="Main Window" width="550" height="650">

### Attempt at analysis or search without opening a file
<img src="/screenshots/2_file_not_selected.PNG" alt="File not Selected" width="550" height="650">

### File Opened
<img src="/screenshots/3_file_selected.PNG" alt="File Selected" width="550" height="650">

### File analysis
<img src="/screenshots/4_after_analysis.PNG" alt="File analysis" width="550" height="650">

### Search Functionality

<img src="/screenshots/5_string_highlighted.PNG" alt="Search Functionality" width="550" height="650">


## Build Instructions

```bash
git clone https://github.com/yourusername/qt-file-analyzer.git
cd qt-file-analyzer

mkdir build
cd build

cmake ..
cmake --build .
```











