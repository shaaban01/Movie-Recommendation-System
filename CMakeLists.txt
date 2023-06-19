cmake_minimum_required(VERSION 3.8)

project(MovieRecommendatoinSystem)

set(CMAKE_CXX_STANDARD 14)

# Find and include CURL
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

include_directories(/usr/include/cppconn)
link_directories(/usr/lib)

add_executable(MovieRecommendatoinSystem main.cpp movieApiController.cpp movie.cpp viewMovies.cpp db.cpp authentication.cpp user.cpp userController.cpp)

# Link the required libraries
target_link_libraries(MovieRecommendatoinSystem mysqlcppconn ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)