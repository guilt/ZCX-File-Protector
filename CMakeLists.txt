CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

project(ZCX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib")

if(WIN32)
  # See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  # Static Link MSVC
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else(WIN32)
  # Static Link GCC
  add_definitions(-DILIN)
  set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
endif(WIN32)

# Include Directories
include_directories(
  ${PROJECT_SOURCE_DIR}/Include/
)

# Sources
set(APP_ENCOM ${PROJECT_NAME}-Encom)
set(APP_ENCOM_SOURCES Src/encom.cpp)

set(APP_DECOM ${PROJECT_NAME}-Decom)
set(APP_DECOM_SOURCES Src/decom.cpp)

set(LIB_NAME ${PROJECT_NAME}-Common)
set(LIB_SOURCES Src/common.cpp)

# Creates ./Build/Bin/APP_*
add_executable(${APP_ENCOM} ${APP_ENCOM_SOURCES})
add_executable(${APP_DECOM} ${APP_DECOM_SOURCES})


# shared library
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${APP_ENCOM} ${LIBRARY_NAME})
target_link_libraries(${APP_DECOM} ${LIBRARY_NAME})
