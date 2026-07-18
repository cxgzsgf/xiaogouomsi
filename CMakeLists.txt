# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.16)
project(xiaogou_remote_open_sdk_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vehicle_adapter_example OBJECT examples/cpp/vehicle_adapter_example.cpp)
target_include_directories(vehicle_adapter_example PRIVATE include)

add_library(auto_headlights_example OBJECT examples/cpp/auto_headlights_example.cpp)
