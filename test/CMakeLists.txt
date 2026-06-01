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

cmake_minimum_required(VERSION 3.15)
project(utf8)

include(CTest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

# Base warning flags and whether -std= flags are supported.
# MSVC and clang-cl use /std: and don't accept -std=, so we skip
# the standard flag for those compilers.
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set(UTF8_C_WARNINGS "-Wall -Wextra -Werror")
  set(UTF8_C_USE_STD_FLAG TRUE)
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
  if(CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    set(UTF8_C_WARNINGS "/Wall /WX /wd4514 /wd5045")
    set(UTF8_C_USE_STD_FLAG FALSE)
  else()
    set(UTF8_C_WARNINGS "-Wall -Wextra -Weverything -Werror -Wno-poison-system-directories")
    set(UTF8_C_USE_STD_FLAG TRUE)
  endif()
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  set(UTF8_C_WARNINGS "/Wall /WX /wd4514 /wd5045")
  set(UTF8_C_USE_STD_FLAG FALSE)
else()
  message(WARNING "Unknown C compiler '${CMAKE_C_COMPILER_ID}'!")
  set(UTF8_C_WARNINGS "")
  set(UTF8_C_USE_STD_FLAG FALSE)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(UTF8_CXX_WARNINGS "-Wall -Wextra -Werror")
  set(UTF8_CXX_USE_STD_FLAG TRUE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    set(UTF8_CXX_WARNINGS "/Wall /WX /wd4514 /wd5045")
    set(UTF8_CXX_USE_STD_FLAG FALSE)
  else()
    set(UTF8_CXX_WARNINGS "-Wall -Wextra -Weverything -Werror -Wno-poison-system-directories")
    set(UTF8_CXX_USE_STD_FLAG TRUE)
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(UTF8_CXX_WARNINGS "/Wall /WX /wd4514 /wd5045")
  set(UTF8_CXX_USE_STD_FLAG FALSE)
else()
  message(WARNING "Unknown C++ compiler '${CMAKE_CXX_COMPILER_ID}'!")
  set(UTF8_CXX_WARNINGS "")
  set(UTF8_CXX_USE_STD_FLAG FALSE)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  set(UTF8_CXX98_COMPAT_FLAG "-Wno-c++98-compat")
else()
  set(UTF8_CXX98_COMPAT_FLAG "")
endif()

# Helper: set compile flags for a C source file (warnings + standard + extras).
function(utf8_set_c_flags FILE STANDARD)
  set(EXTRA_FLAGS ${ARGN})
  if(UTF8_C_USE_STD_FLAG)
    set_source_files_properties(${FILE} PROPERTIES
      COMPILE_FLAGS "${UTF8_C_WARNINGS} ${STANDARD} ${EXTRA_FLAGS}")
  else()
    set_source_files_properties(${FILE} PROPERTIES
      COMPILE_FLAGS "${UTF8_C_WARNINGS} ${EXTRA_FLAGS}")
  endif()
endfunction()

# Helper: set compile flags for a C++ source file (warnings + standard + extras).
function(utf8_set_cxx_flags FILE STANDARD)
  set(EXTRA_FLAGS ${ARGN})
  if(UTF8_CXX_USE_STD_FLAG)
    set_source_files_properties(${FILE} PROPERTIES
      COMPILE_FLAGS "${UTF8_CXX_WARNINGS} ${STANDARD} ${EXTRA_FLAGS}")
  else()
    set_source_files_properties(${FILE} PROPERTIES
      COMPILE_FLAGS "${UTF8_CXX_WARNINGS} ${EXTRA_FLAGS}")
  endif()
endfunction()

# C files — each compiled under a specific C standard.
utf8_set_c_flags(main.c  "-std=gnu89")
utf8_set_c_flags(test.c  "-std=gnu89")
utf8_set_c_flags(test99.c "-std=c99")

list(FIND CMAKE_C_COMPILE_FEATURES c_std_11 IDX)
if(${IDX} GREATER -1)
  utf8_set_c_flags(test11.c "-std=c11")
endif()

# C++ files — each compiled under a specific C++ standard.
utf8_set_cxx_flags(test.cpp   "" "${UTF8_CXX98_COMPAT_FLAG}")
utf8_set_cxx_flags(test98.cpp "-std=gnu++98" "${UTF8_CXX98_COMPAT_FLAG}")
utf8_set_cxx_flags(test11.cpp "-std=c++11" "${UTF8_CXX98_COMPAT_FLAG}")
utf8_set_cxx_flags(test14.cpp "-std=c++14" "${UTF8_CXX98_COMPAT_FLAG}")
utf8_set_cxx_flags(test17.cpp "-std=c++17" "${UTF8_CXX98_COMPAT_FLAG}")
utf8_set_cxx_flags(test20.cpp "-std=c++20" "${UTF8_CXX98_COMPAT_FLAG}")
if(MSVC OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
  utf8_set_cxx_flags(test20_no_char_t.cpp "" "${UTF8_CXX98_COMPAT_FLAG} /Zc:char8_t-")
else()
  utf8_set_cxx_flags(test20_no_char_t.cpp "-std=c++20" "${UTF8_CXX98_COMPAT_FLAG} -fno-char8_t")
endif()

set(UTF8_TEST_SOURCES
  ../utf8.h
  utest.h
  test_shared.h
  main.c
  test.c
  test99.c
  test11.c
  test.cpp
  test98.cpp
  test11.cpp
  test14.cpp
  test17.cpp
  test20.cpp
  test20_no_char_t.cpp
)

# Helper: add a test executable and register it with CTest.
function(utf8_add_test NAME)
  add_executable(${NAME} ${UTF8_TEST_SOURCES})
  add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}>)
endfunction()

function(utf8_add_no_malloc_test NAME)
  add_executable(${NAME} no_malloc.c)
  add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}>)
endfunction()

utf8_add_test(utf8_test)
utf8_add_no_malloc_test(utf8_no_malloc_test)

# Some sanitizer runtimes can't initialise on every host even when
# the toolchain links them fine — e.g. clang's TSan and MSan on
# aarch64 only ship shadow-memory layouts for 39-, 42- and 48-bit
# user VMAs, but Raspberry Pi OS' kernel is configured with
# CONFIG_ARM64_VA_BITS=47. The binary builds, but aborts before
# main with "FATAL: ThreadSanitizer: unsupported VMA range". Probe
# each candidate sanitizer with try_run and skip the ones whose
# runtime can't start. Result is cached so reconfigure is cheap;
# delete CMakeCache.txt to re-probe (e.g. after changing kernels).
function(utf8_check_sanitizer_runs SAN OUT_VAR)
  set(CACHE_VAR "UTF8_SAN_${SAN}_RUNS")
  if(DEFINED ${CACHE_VAR})
    set(${OUT_VAR} ${${CACHE_VAR}} PARENT_SCOPE)
    return()
  endif()

  set(PROBE_SRC "${CMAKE_BINARY_DIR}/utf8_san_probe_${SAN}.c")
  file(WRITE "${PROBE_SRC}" "int main(void) { return 0; }\n")

  try_run(RUN_RESULT COMPILE_RESULT
    "${CMAKE_BINARY_DIR}/utf8_san_probe_${SAN}"
    "${PROBE_SRC}"
    COMPILE_DEFINITIONS "-fsanitize=${SAN}" "-fno-omit-frame-pointer"
    LINK_OPTIONS "-fsanitize=${SAN}"
  )

  if(COMPILE_RESULT AND "${RUN_RESULT}" STREQUAL "0")
    set(RESULT TRUE)
    message(STATUS "Sanitizer ${SAN}: usable")
  else()
    set(RESULT FALSE)
    message(STATUS "Sanitizer ${SAN}: skipping "
                   "(compile=${COMPILE_RESULT}, run=${RUN_RESULT})")
  endif()

  set(${CACHE_VAR} ${RESULT} CACHE INTERNAL
      "Whether the ${SAN} sanitizer runtime starts on this host")
  set(${OUT_VAR} ${RESULT} PARENT_SCOPE)
endfunction()

if(("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang") AND NOT "${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
  set(UTF8_SANITIZER_CANDIDATES
    address
    undefined
    thread
  )

  if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
    set(UTF8_SANITIZER_CANDIDATES ${UTF8_SANITIZER_CANDIDATES} memory)
  endif()

  set(UTF8_SANITIZERS)
  foreach(UTF8_SANITIZER ${UTF8_SANITIZER_CANDIDATES})
    if(CMAKE_CROSSCOMPILING)
      list(APPEND UTF8_SANITIZERS ${UTF8_SANITIZER})
    else()
      utf8_check_sanitizer_runs(${UTF8_SANITIZER} UTF8_SAN_RUNS)
      if(UTF8_SAN_RUNS)
        list(APPEND UTF8_SANITIZERS ${UTF8_SANITIZER})
      endif()
    endif()
  endforeach()

  foreach(UTF8_SANITIZER ${UTF8_SANITIZERS})
    utf8_add_test(utf8_${UTF8_SANITIZER}_test)
    target_compile_options(utf8_${UTF8_SANITIZER}_test PRIVATE -fsanitize=${UTF8_SANITIZER} -fno-omit-frame-pointer)
    target_link_options(utf8_${UTF8_SANITIZER}_test PRIVATE -fsanitize=${UTF8_SANITIZER})

    utf8_add_no_malloc_test(utf8_no_malloc_${UTF8_SANITIZER}_test)
    target_compile_options(utf8_no_malloc_${UTF8_SANITIZER}_test PRIVATE -fsanitize=${UTF8_SANITIZER} -fno-omit-frame-pointer)
    target_link_options(utf8_no_malloc_${UTF8_SANITIZER}_test PRIVATE -fsanitize=${UTF8_SANITIZER})
  endforeach()
endif()
