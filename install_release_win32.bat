mkdir build
cmake -S . -B build -A Win32 -D CMAKE_BUILD_TYPE=Release -D BUILD_LIBRARY_TYPE:STRING="Static" ^
    -D CMAKE_INSTALL_PREFIX:PATH="%~dp0../../../3rd_party_libraries/OCCT" ^
    -D 3RDPARTY_DIR:PATH="%~dp0../../../3rd_party_libraries" ^
    -D BUILD_SAMPLES_MFC:BOOL="0" -D BUILD_SAMPLES_QT:BOOL="0" ^
    -D 3RDPARTY_QT_DIR:PATH="%~dp0../../../../Qt/Qt5.12.11/5.12.11/msvc2017_64" ^
    -D USE_OPENGL:BOOL="1" -D USE_TK:BOOL="0" -D USE_FREETYPE:BOOL="1" -D BUILD_MODULE_Draw:BOOL="0"
cmake --build build --config Release
cmake --install build --config Release
pause
