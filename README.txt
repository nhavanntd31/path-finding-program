To run and compile this project, you need to add graphics.h library to compiler.

Our recommended compiling environment is MingW or TDM-GCC-32, the download link for MingW is https://sourceforge.net/projects/mingw/files/latest/download, for TDM-GCC-32 : https://jmeubank.github.io/tdm-gcc/

For example, we will use MingW and Visual Studio Code edior. Now open minGW’s downloaded setup then click on Install and choose your directory where the software should be installed and click on continue.

After installing, you will see an image like below now you have to right click on highlighted (“mingw-32-base”, “mingw32-gcc-g++” and “mysys-base”) box and choose mark for installation.

After checking the checkboxes you should see something like the image, now click on Installation on the top left corner and then click on apply changes.

After installation is complete, click close to close the installer.

Search for "Edit the system enviroment variables", click its. Now you have to right click on Advanced System Settings, you should see System Properties then you have click on Environment Variables.

In "System variables", doublue click on "Path". Then click on "New" and paste "C:\MinGW\bin" ( or other path if you changes compiler address when installation)  and click "Ok".

To setup "graphics.h" in Visual Studio Code, download the zip file linked above to get all the required files.

extract the downloaded file, there will be three important files:

graphics.h
winbgim.h
libbgi.a

Download link : https://drive.google.com/drive/folders/1AEUDI_4yBJo3-fQ2M7y5eB7Emw9B99aU

Then, copy graphics.h and winbgim.h files then paste into MinGW/include folder, as shown in the image below.

path might be ("C:\MinGW\include")

copy libbgi.a file then paste into MinGW/lib folder, as shown in the image below.

path might be ("C:\MinGW\lib")

Next step open project folder again, choose "Open with Code"

Check if ".vscode" already exist, you need else create one.

It must be include three file : 
"c_cpp_properties.json" : 
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/MinGW/include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "C:\\MinGW\\bin\\g++"
        }
    ],
    "version": 4
}
Note : You should check value of these key : "includePath", "compilerPath" with your correct path of your compiler 

And "tasks.json" :
{
    "version": "2.0.0",
    "tasks": [
      {
        "type": "process",
        "label": "C/C++: Build .exe",
        "command": "C:\\MinGW\\bin\\g++.exe",
        "args": ["-g",
                 "${workspaceFolder}\\Home\\src\\main.cpp",
                 "-o", 
                 "${workspaceFolder}\\Home\\build\\mappingprogram.exe",
                 "-lbgi",
                 "-lgdi32",
                 "-lcomdlg32",
                 "-luuid",
                 "-loleaut32",
                 "-lole32"
                ],
        "options": {
          "cwd": "${workspaceFolder}"
        },
        "problemMatcher": [],
        "group": {
          "kind": "build",
          "isDefault": true
        },
        "detail": "compiler: C:\\MinGW\\bin\\g++.exe"
      }
    ]
  }
Note : You should check value of these key : "command", "detail" with your correct path of your compiler 

And "launch.json" :
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C/C++: Build .exe",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${workspaceFolder}\\Home\\build\\mappingprogram.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "console": "externalTerminal"
        }
    ]
}

The final step, install "Code Runner" extension (if you haven't installed)
Now, everything is completely done. On the 'File explorer' side, select 'Home' -> 'src' -> 'main.cpp' and press F5

To use our sample map. Copy from "test.txt" and paste into console menu.



