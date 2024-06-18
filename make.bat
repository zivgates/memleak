@echo off



cl src/*.c /Fe:memleak.exe
del *.obj