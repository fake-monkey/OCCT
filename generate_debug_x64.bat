mkdir build
cmake -S . -B build -A x64 -D CMAKE_BUILD_TYPE=Debug -D BUILD_LIBRARY_TYPE:STRING="Static" ^
    -D CMAKE_INSTALL_PREFIX:PATH="%~dp0../../../3rd_party_libraries/OCCT" ^
    -D 3RDPARTY_DIR:PATH="%~dp0../../../3rd_party_libraries" ^
    -D BUILD_SAMPLES_QT:BOOL="0" ^
    -D 3RDPARTY_QT_DIR:PATH="%~dp0../../../../Qt/Qt5.12.11/5.12.11/msvc2017_64"
cmake --build build --config Debug
cmake --install build --config Debug
pause
