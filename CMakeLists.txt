cmake_minimum_required(VERSION 3.5)

project(asiotest LANGUAGES CXX)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#add_definitions(-DBOOST_LOG_DYN_LINK)

add_definitions(-DBOOST_COROUTINES_NO_DEPRECATION_WARNING)

find_package(OpenSSL 1.1 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.67 REQUIRED COMPONENTS
        system
        program_options
        coroutine
        log
        )

include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    PUBLIC ${Boost_LIBRARIES}
    )
target_compile_definitions(${PROJECT_NAME} PUBLIC -DBOOST_COROUTINES_NO_DEPRECATION_WARNING=1)
