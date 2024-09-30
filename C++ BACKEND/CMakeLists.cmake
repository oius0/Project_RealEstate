cmake_minimum_required(VERSION 3.10)
project(RealEstatePlatform)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)
include_directories(third_party/sqlite3)
include_directories(third_party/cpprestsdk/Release/include)

# Link directories
link_directories(third_party/sqlite3)
link_directories(third_party/cpprestsdk/Release/Binaries)

# Add executable
add_executable(RealEstatePlatform src/main.cpp src/Database.cpp src/PropertyController.cpp)

# Link libraries
target_link_libraries(RealEstatePlatform sqlite3 cpprest)
