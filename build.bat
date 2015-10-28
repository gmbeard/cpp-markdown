@ECHO OFF

CLS
RMDIR /S /Q lib
MKDIR lib
PUSHD lib
REM Create 3rd party library/include dirs...
MKDIR variant_operation
XCOPY /S "%CODELIB%\variant_operation\include\*.*" variant_operation\
POPD

RMDIR /S /Q build
MKDIR build
PUSHD build

cl.exe /Zi /EHs ^
        /D _DEBUG ^
        /MDd ^
        /I ..\include ^
        /I ..\lib ^
       ..\src\main.cpp ^
       ..\src\parsing.cpp ^
       ..\src\states.cpp ^
       /link /out:markdown.exe
POPD

