cmake_minimum_required(VERSION 3.8)

project(MovieRecommendatoinSystem)

set(CMAKE_CXX_STANDARD 14)

# Find and include CURL
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

include_directories(/usr/include/cppconn)
link_directories(/usr/lib)

# Include directories for headers
include_directories(~/Projects/cpp_projects/cmake_practice/include/controllers)
include_directories(~/Projects/cpp_projects/cmake_practice/include/models)
include_directories(~/Projects/cpp_projects/cmake_practice/include/views)

# Add executable
add_executable(
    MovieRecommendatoinSystem 
    src/main.cpp 
    src/controllers/movieApiController.cpp
    src/controllers/userController.cpp
    src/controllers/authentication.cpp
    src/models/movie.cpp
    src/models/user.cpp
    src/models/db.cpp
    src/views/viewMovies.cpp
)

# Link the required libraries
target_link_libraries(MovieRecommendatoinSystem mysqlcppconn ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)
