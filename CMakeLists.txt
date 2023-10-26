cmake_minimum_required(VERSION 3.0.0)
project(practice VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include(CTest)
enable_testing()

add_executable(test_pn_diode test_pn_diode.cpp pn_diode.cpp pn_diode.h)
add_executable(test_message test_message.cpp message.cpp message.h)
add_executable(test_configure test_configure.cpp configure.cpp configure.h)

add_executable(pn_diode example.cpp pn_diode.cpp pn_diode.h configure.cpp configure.h)
add_executable(pn_diode_message example.cpp pn_diode.cpp pn_diode.h message.cpp message.h configure.cpp configure.h)

target_compile_definitions(test_message PRIVATE MESSAGE VERBOSITY=DEBUG)
target_compile_definitions(pn_diode_message PRIVATE MESSAGE VERBOSITY=DEBUG)


add_test(NAME TestPNDiode COMMAND test_pn_diode)
add_test(NAME TestMessage COMMAND test_message)
add_test(NAME TestConfigure COMMAND test_configure)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
