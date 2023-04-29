mkdir build
cmake -S . -B build -A x64 -D CMAKE_BUILD_TYPE=Debug ^
    -D CMAKE_INSTALL_PREFIX:PATH="D:/Program Files/OCCT" ^
    -D 3RDPARTY_DIR:PATH="%~dp0../../../3rd_party_libraries" ^
    -D BUILD_SAMPLES_QT:BOOL="1" ^
    -D 3RDPARTY_QT_DIR:PATH="%~dp0../../../../Qt\Qt5.12.11\5.12.11\msvc2017_64"
pause
