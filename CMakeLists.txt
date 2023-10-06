cmake_minimum_required(VERSION 3.0.0)
project(practice VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(test_pn_diode test.cpp pn_diode.cpp function.h)
add_executable(pn_diode main.cpp pn_diode.cpp function.h)


add_test(NAME TestPNDiode COMMAND test_pn_diode)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
