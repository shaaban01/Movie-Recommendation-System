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
include_directories(~/Projects/cpp_projects/cmake_practice/include/)


set(SOURCES src/main.cpp src/db.cpp src/RecommendationEngines/UserBasedCollaborativeFiltering.cpp src/RecommendationEngines/PopularityBasedFiltering.cpp src/RecommendationEngines/ContentBasedFiltering.cpp src/controllers/authenticationController.cpp src/controllers/movieController.cpp src/controllers/ratingController.cpp src/controllers/userController.cpp src/models/movie.cpp src/models/user.cpp src/views/movieView.cpp )


add_executable(MovieRecommendatoinSystem ${SOURCES})

# Link the required libraries
target_link_libraries(MovieRecommendatoinSystem mysqlcppconn ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)