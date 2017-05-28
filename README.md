# smart-rockets
Simple genetic algorithm example using SDL for 2D graphics.

Set Up:
1. Download and install Microsoft Visual Studio 2017 Community with C/C++ packages.
  https://www.visualstudio.com/downloads/
2. Download SDL Development Library SDL2-devel-2.0.5-VC.zip (Visual C++ 32/64-bit) and move to C:\dev_libs should look like C:\dev_libs\SDL2-2.0.5 (if elsewhere will need to update project properties)
  https://www.libsdl.org/download-2.0.php
3. Download SDL Image and STL TTF Development Libraries
  https://www.libsdl.org/projects/SDL_image/ SDL2_image-devel-2.0.1-VC.zip (Visual C++ 32/64-bit)
  https://www.libsdl.org/projects/SDL_ttf/ SDL2_ttf-devel-2.0.14-VC.zip (Visual C++ 32/64-bit)

  Open and copy the lib files (SDL2_image-2.0.1\lib\x86\SDL2_image.lib and SDL2_ttf-2.0.14\lib\x86\SDL2_ttf.lib) into C:\dev_libs\SDL2-   2.0.5\lib\x86
  Open and copy the .h files (SDL2_image-2.0.1\include\SDL_image.h and SDL2_ttf-2.0.14\include\SDL_ttf.h) into C:\dev_libs\SDL2-2.0.5\include
  
4. Make sure in project properties it is set to build 32bit version
