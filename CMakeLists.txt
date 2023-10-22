cmake_minimum_required(VERSION 3.0.0)
project(practice VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include(CTest)
enable_testing()

add_executable(test_pn_diode test_pn_diode.cpp pn_diode.cpp function.h)
add_executable(test_message test_message.cpp message.cpp message.h)

add_executable(pn_diode example.cpp pn_diode.cpp function.h)
add_executable(pn_diode_message example.cpp pn_diode.cpp function.h message.cpp message.h)

target_compile_definitions(pn_diode_message PRIVATE MESSAGE VERBOSITY=DEBUG)


add_test(NAME TestPNDiode COMMAND test_pn_diode)
add_test(NAME TestMessage COMMAND test_message)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
