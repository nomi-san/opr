@echo off

set luasrc=lua51\src
set lualib=lua51\lib
set cc=gcc

%cc% -w -shared -o opr.dll -I%luasrc% lopr.c -lpsapi -L%lualib% -llua