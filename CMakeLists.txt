cmake_minimum_required(VERSION 3.8)

project(MovieRecommendatoinSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

# Find and include CURL
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Qt5 COMPONENTS Core Quick QuickControls2 REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

include_directories(/usr/include/cppconn)
link_directories(/usr/lib)

# Include directories for headers
include_directories(~/Projects/cpp_projects/cmake_practice/include/controllers)
include_directories(~/Projects/cpp_projects/cmake_practice/include/models)
include_directories(~/Projects/cpp_projects/cmake_practice/include/views)
include_directories(~/Projects/cpp_projects/cmake_practice/include/)

set(SOURCES src/main.cpp src/db.cpp src/RecommendationEngines/UserBasedCollaborativeFiltering.cpp src/RecommendationEngines/PopularityBasedFiltering.cpp src/RecommendationEngines/ContentBasedFiltering.cpp src/controllers/authenticationController.cpp src/controllers/movieController.cpp src/controllers/ratingController.cpp src/controllers/userController.cpp src/models/movie.cpp src/models/user.cpp src/views/movieView.cpp )

qt5_add_resources(QT_RESOURCES qml.qrc)


add_executable(MovieRecommendatoinSystem ${SOURCES} ${QT_RESOURCES})


# Link the required libraries
target_link_libraries(MovieRecommendatoinSystem Qt5::Core Qt5::Quick Qt5::QuickControls2 mysqlcppconn ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)
