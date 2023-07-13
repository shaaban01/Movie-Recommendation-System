cmake_minimum_required(VERSION 3.8)
project(MovieRecommendatoinSystem)
set(CMAKE_CXX_STANDARD 14)

# Find and include CURL
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Qt5 COMPONENTS Core Quick QuickControls2 REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(/usr/include/cppconn)
link_directories(/usr/lib)

# Include directories for headers
include_directories(include/controllers)
include_directories(include/models)
include_directories(include/views)
include_directories(include)

set(SOURCES 
    src/main.cpp 
    src/db.cpp 
    src/RecommendationEngines/UserBasedCollaborativeFiltering.cpp 
    src/RecommendationEngines/PopularityBasedFiltering.cpp 
    src/RecommendationEngines/ContentBasedFiltering.cpp 
    src/controllers/authenticationController.cpp 
    src/controllers/movieController.cpp 
    src/controllers/ratingController.cpp 
    src/controllers/userController.cpp 
    src/models/movie.cpp 
    src/models/user.cpp 
    src/views/movieView.cpp
)

qt5_add_resources(QT_RESOURCES qml.qrc)

# Run MOC on UserController class
qt5_wrap_cpp(MOC_SOURCES
    include/controllers/userController.h include/engine.h include/models/user.h include/models/movie.h src/models/movie.cpp include/controllers/ratingController.h src/controllers/ratingController.cpp include/controllers/movieController.h src/controllers/movieController.cpp
    )

add_executable(MovieRecommendatoinSystem ${SOURCES} ${QT_RESOURCES} ${MOC_SOURCES})

# Link the required libraries
target_link_libraries(MovieRecommendatoinSystem 
    Qt5::Core 
    Qt5::Quick 
    Qt5::QuickControls2 
    mysqlcppconn 
    ${CURL_LIBRARIES} 
    nlohmann_json::nlohmann_json
)