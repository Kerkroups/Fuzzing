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

## EXE FUNCTIONS, EXTERNAL / EXPORTED FUNCTIONS  
**Tools**:  
- Dependency walker - показывает список динамически скомпилированных функций.
- PEView (https://github.com/lyshark/PeView)
- Resource Hacker

DLL- и EXE-файлы могут экспортировать свои функции, чтобы взаимодействовать  с другими программами и кодом. Обычно в DLL реализована одна или несколько  функций, экспортирующихся для использования в любом исполняемом файле, который пожелает их импортировать. 
PE-файл содержит информацию о том, какие функции экспортируются программой. Поскольку библиотеки DLL специально созданы для предоставления своей функциональности исполняемым файлам, экспортируемые функции обычно встречаются именно в них. 
EXE-файлы не предназначены для того, чтобы делиться своими возможностями с другими программами, поэтому экспортируемые функции в них являются редкостью и обычно несут в себе полезную информацию.  

## Звголовки и разделы PE файла  
- .text
- .rdata
- .data
- .rsrc
- .idata
- .edata
- .pdata
- .reloc

## DISABLE ASLR:  
1. Set-ProcessMitigation -Name "yourfilename.exe" -Disable ForceRelocateImages
2. CFF Explorer -> DLLCharacteristics -> Uncheck "DLL Can Move" -> Save and overwrite executable.
3. setdllcharacteristics -d yourfile.exe (https://blog.didierstevens.com/2010/10/17/setdllcharacteristics/)
4. Windows Security -> App & Browser Control -> Exploit protection section -> Add program to customize -> Force randomization for image -> Overwrite system settings -> Apply.

