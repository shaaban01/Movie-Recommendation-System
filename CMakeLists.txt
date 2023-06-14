cmake_minimum_required(VERSION 3.8)

project(MovieRecommendatoinSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/cppconn)
link_directories(/usr/lib)

add_executable(MovieRecommendatoinSystem main.cpp db.cpp authentication.cpp)
target_link_libraries(MovieRecommendatoinSystem mysqlcppconn)
