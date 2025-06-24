cmake_minimum_required(VERSION 3.10)
project(cpp_crow_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg toolchain 파일 지정
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# 필요한 패키지 찾기 (예: Boost, asio 등)
find_package(Boost REQUIRED)
# 만약 crow가 asio 등 다른 라이브러리를 요구하면 추가로 find_package 필요

# include 경로 설정
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

# 실행 파일 지정
add_executable(cpp_crow_server main.cpp)

# 링크할 라이브러리 지정 (필요하면)
target_link_libraries(cpp_crow_server PRIVATE ${Boost_LIBRARIES})
