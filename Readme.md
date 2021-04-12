# Project gemini

![CLI use of gemini](Picture.png)

A simple CLI client for [Gemini protocol](https://gemini.circumlunar.space/), a minimal internet protocol.

## How to use 

### Compile 

``` bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```


### Run

``` bash
./build/code/bin/CliClient url port
```

Standard protocol port is 1965.

Some [urls](https://gemini.circumlunar.space/servers/) to try.


### Test

Test must be activated at compilation time using flag ```-DENABLE_TESTING```.

``` bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING=ON
cmake --build build 
cmake --build build --target test
```


## Bug and todos

* comment code;
* review socket behaviour in multiple usage.


## Acknowledgments 

Socket is based on: https://gist.github.com/vedantroy/d2b99d774484cf4ea5165b200888e414