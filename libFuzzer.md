## COMPILING THE TARGET:  

**C++**: ```clang++ -std=c++14 -O2 -g -fsanitize=fuzzer,fuzzer-no-link fuzzer.cpp -o fuzzer -lpthread```   
**C**: ``` clang -g -O1 -fsanitize=fuzzer,address -Wall -Werror -DLIBDEFLATE_ENABLE_ASSERTIONS=1 -I <path_to_libraries> test.c -o test```  

## RUN FUZZER:  
```./test -max_len=8192 -artifact_prefix=corpus/```  

## COMPILE SOURCES:  
```
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
cmake --build .
```

## ДОПОЛНИТЕЛЬНЫЕ ИСТОЧНИКИ ИНФОРМАЦИИ:  
[https://appsec.guide/docs/fuzzing/c-cpp/libfuzzer/](https://appsec.guide/docs/fuzzing/c-cpp/libfuzzer/)  
