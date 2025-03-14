## INSTALLATION:
1. Download DynamoRIO (https://github.com/DynamoRIO/dynamorio/releases)
2. Download WinAFL sources (https://github.com/googleprojectzero/winafl.git)
3. Install Visual Studio with C++ Development tools  
4. Open WinAFL folder in Visual Studio
5. In Visual Studio open Terminal
6. 
```
mkdir build64
cd build64
cmake -A x64 .. -DDynamoRIO_DIR=C:\path\to\DynamoRIO\cmake -DINTELPT=1
cmake --build . --config Release
```

