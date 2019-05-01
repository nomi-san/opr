@echo off

gcc -w -O2 -o test.exe test.c -lpsapi
g++ -w -O2 -o test_cpp.exe test.cpp -lpsapi