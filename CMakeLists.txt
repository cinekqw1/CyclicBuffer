cmake_minimum_required(VERSION 3.10)
project(CyclicBuffer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER g++)

include_directories(include)
set(SRC
    src/main.cpp
)
add_executable(${PROJECT_NAME} ${SRC})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -lpthread)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

set(Boost_NO_SYSTEM_PATHS ON)
set(BOOST_INCLUDEDIR "${LIBS_DIR}/boost")
set(BOOST_LIBRARYDIR "${LIBS_DIR}boost/libs")
find_package(Boost 1.56.0)
include_directories("${Boost_INCLUDE_DIRS}")