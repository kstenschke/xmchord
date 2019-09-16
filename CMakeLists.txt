# Copyright (c) 2019, Kay Stenschke
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
# * Neither the name of  nor the names of its contributors may be used to
# endorse or promote products derived from this software without specific
# prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.9.6)

project(xmchord C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

set (XMCHORD_EXECUTABLE_NAME "xmchord")
set (XMCHORD_VERSION_MAJOR 0)
set (XMCHORD_VERSION_MINOR 1)
set (XMCHORD_VERSION_PATCH 1)

# configure config.h to be generated from config.h.in, with injected version number
configure_file (
        "src/xmchord/config.h.in"
        "src/xmchord/config.h"
)

find_package(Threads)

include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(xmchord
        src/xmchord/helper/textual.cc
        src/xmchord/helper/file.cc
        src/xmchord/helper/system.cc
        src/xmchord/helper/mouse.cc
        src/xmchord/helper/keyboard.cc
        src/xmchord/models/action_runner.cc
        src/xmchord/models/action_runner.h
        src/xmchord/xmchord.cc)

target_link_libraries(xmchord ${CMAKE_THREAD_LIBS_INIT})
