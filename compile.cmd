@echo off
g++ -std=c++11 src/lolgame.cpp src/Scene.cpp src/GameObject.cpp src/BitmapManager.cpp -lole32 -luser32 -lgdi32 -lkernel32 -lshlwapi -lwindowscodecs -lmsvcrt -lmsimg32 -o bin/lolgame.exe
@
pause