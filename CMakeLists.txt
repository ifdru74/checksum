cmake_minimum_required(VERSION 3.16)
project(checksum VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    add_compile_definitions(VALIDATIONSUM_EXPORTS)
    add_library(crypto_checksum SHARED dll_export.h CheckSum.cpp CheckSum.h Crc32Sum.cpp Crc32Sum.h
            MD5Sum.cpp MD5Sum.h fileSum.h fileSum.cpp CryptoProvider.cpp CryptoProvider.h)
    set(SOURCE_FILES dll_export.h CheckSum.cpp CheckSum.h Crc32Sum.cpp Crc32Sum.h
            MD5Sum.cpp MD5Sum.h fileSum.h fileSum.cpp)
else(WIN32)
    find_package (OpenSSL REQUIRED)
    add_library(crypto_checksum SHARED tchar_port.h dll_export.h CheckSum.cpp CheckSum.h Crc32Sum.cpp Crc32Sum.h
            MD5Sum.cpp MD5Sum.h fileSum.h fileSum.cpp CryptoProvider.cpp CryptoProvider.h)
    set(SOURCE_FILES tchar_port.h dll_export.h CheckSum.cpp CheckSum.h Crc32Sum.cpp Crc32Sum.h
            MD5Sum.cpp MD5Sum.h fileSum.h fileSum.cpp)
    if (OPENSSL_FOUND)
        message(STATUS "use OpenSSL library for crypto_checksum")
        target_link_libraries (crypto_checksum LINK_PUBLIC ${OPENSSL_CRYPTO_LIBRARY})
    endif (OPENSSL_FOUND)
endif (WIN32)
add_executable(testCheckSum testCheckSum.cpp CheckSum.h fileSum.h MD5Sum.h Crc32Sum.h)
target_link_libraries(testCheckSum crypto_checksum)
add_test(checkSumTest testCheckSum )
enable_testing()


