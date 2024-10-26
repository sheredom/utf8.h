# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>

cmake_minimum_required(VERSION 2.8.12)
project(utf8)

set(UTF8_USE_SANITIZER "" CACHE STRING "Set which Clang Sanitizer to use")

macro(add_sanitizer target)
  if(NOT "${UTF8_USE_SANITIZER}" STREQUAL "")
    target_compile_options(${target} PUBLIC -fno-omit-frame-pointer -fsanitize=${UTF8_USE_SANITIZER})
    target_link_options(${target} PUBLIC -fno-omit-frame-pointer -fsanitize=${UTF8_USE_SANITIZER})
  endif()
endmacro()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(utf8_test main.c)
add_sanitizer(utf8_test)

add_executable(utf8_no_malloc_test no_malloc.c)
add_sanitizer(utf8_no_malloc_test)

add_executable(utf8_test_c90 test.c)
add_sanitizer(utf8_test_c90)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(utf8_test_c90 PUBLIC "-std=c90")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  if("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
  else()
    target_compile_options(utf8_test_c90 PUBLIC "-std=c90")
  endif()
endif()

add_executable(utf8_test_c99 test.c)
add_sanitizer(utf8_test_c99)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(utf8_test_c99 PUBLIC "-std=c99")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  if("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
  else()
    target_compile_options(utf8_test_c99 PUBLIC "-std=c99")
  endif()
endif()

add_executable(utf8_test_c11 test.c)
add_sanitizer(utf8_test_c11)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(utf8_test_c11 PUBLIC "-std=c11")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  if("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
  else()
    target_compile_options(utf8_test_c11 PUBLIC "-std=c11")
  endif()
endif()

add_executable(utf8_test_cpp11 test.cpp)
add_sanitizer(utf8_test_cpp11)
set_target_properties(utf8_test_cpp11 PROPERTIES CXX_STANDARD 11)

add_executable(utf8_test_cpp14 test.cpp)
add_sanitizer(utf8_test_cpp14)
set_target_properties(utf8_test_cpp14 PROPERTIES CXX_STANDARD 14)

add_executable(utf8_test_cpp17 test.cpp)
add_sanitizer(utf8_test_cpp17)
set_target_properties(utf8_test_cpp17 PROPERTIES CXX_STANDARD 17)

add_executable(utf8_test_cpp20 test.cpp)
add_sanitizer(utf8_test_cpp20)
set_target_properties(utf8_test_cpp20 PROPERTIES CXX_STANDARD 20)

add_executable(utf8_test_cpp20_no_char_t test.cpp)
add_sanitizer(utf8_test_cpp20_no_char_t)
set_target_properties(utf8_test_cpp20_no_char_t PROPERTIES CXX_STANDARD 20)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(utf8_test_cpp20_no_char_t PUBLIC "-fno-char8_t")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  if("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
    target_compile_options(utf8_test_cpp20_no_char_t PUBLIC "/Zc:char8_t-")
  else()
    target_compile_options(utf8_test_cpp20_no_char_t PUBLIC "-fno-char8_t")
  endif()
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  target_compile_options(utf8_test_cpp20_no_char_t PUBLIC "/Zc:char8_t-")
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(test.c test.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Werror"
  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set_source_files_properties(test.c test.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -Wno-c++98-compat"
  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  set_source_files_properties(test.c test.cpp PROPERTIES
    COMPILE_FLAGS "/Wall /WX /wd4514"
  )
  if(${MSVC_VERSION} VERSION_GREATER "15.7")
    set_source_files_properties(test.c test.cpp PROPERTIES
        COMPILE_FLAGS "/Zc:__cplusplus"
        )
  endif()
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()
