# Thread Pool

## Environment

* C++11
* g++ 12.2.0 (MSYS2)
* PATH=...;C:\msys64\usr\bin;C:\msys64\mingw64\bin;

## Usage

```shell script
# build
~/thread-lib-cpp $ make
mkdir -p obj
g++ -o obj/thread.o src/thread.cpp -c -g -Wall -std=c++11 -Iinc   -MD
mkdir -p obj
g++ -o obj/main.o src/main.cpp -c -g -Wall -std=c++11 -Iinc   -MD
g++ -o test.out obj/thread.o obj/main.o -g -Wall -std=c++11 -Iinc

# run test.out
~/thread-lib-cpp $ ./test.out

...

999

# clean
~/thread-lib-cpp $ make clean
```

## Reference

1. [Thread Pool 사용 이유 및 C++ 구현](https://devbin.kr/posts/thread-pool-%EC%82%AC%EC%9A%A9-%EC%9D%B4%EC%9C%A0-%EB%B0%8F-c++-%EA%B5%AC%ED%98%84/)

2. [씹어먹는 C++ - <15 - 5. C++ 쓰레드풀(ThreadPool) 만들기>](https://modoocode.com/285)
