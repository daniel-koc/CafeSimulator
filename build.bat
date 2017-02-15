@set BARISTA_FILES=barista_file_getter.cpp barista_generic_getter.cpp barista_numbered_getter.cpp
@set PARAM_FILES=cafe_params.cpp
@i686-w64-mingw32-g++.exe -std=c++11 -o bin\barista_getter_test.exe %BARISTA_FILES% %PARAM_FILES% barista_getter_test.cpp

