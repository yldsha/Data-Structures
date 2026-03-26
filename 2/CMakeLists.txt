cmake_minimum_required(VERSION 3.10)
project(BaseFile)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

add_executable(BaseFile
    src/lab2.cpp
    src/BaseFile.cpp
    src/myString.cpp
)

enable_testing()

add_executable(test_basefile 
    src/test_basefile.cpp
    src/BaseFile.cpp
    src/myString.cpp
)
add_test(NAME test_basefile COMMAND test_basefile)

add_executable(test_rlefile 
    src/test_rlefile.cpp
    src/BaseFile.cpp
    src/myString.cpp
)
add_test(NAME test_rlefile COMMAND test_rlefile)

add_executable(test_rlefile2 
    src/test_rlefile2.cpp
    src/BaseFile.cpp
    src/myString.cpp
)
add_test(NAME test_rlefile2 COMMAND test_rlefile2)