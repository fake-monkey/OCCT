mkdir build
cmake -S . -B build -A x64 -D CMAKE_BUILD_TYPE=Debug ^
    -D CMAKE_INSTALL_PREFIX:PATH="D:/Program Files/OCCT" ^
    -D 3RDPARTY_DIR:PATH="D:/fake_monkey_files/3rd_party_libraries" ^
    -D BUILD_SAMPLES_QT:BOOL="1" ^
    -D 3RDPARTY_QT_DIR:PATH="D:\Qt\Qt5.12.11\5.12.11\msvc2017_64"
pause
