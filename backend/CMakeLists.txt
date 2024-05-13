cmake_minimum_required(VERSION 3.23)
project(backend)

set(CMAKE_CXX_STANDARD 14)

# Include directories for custom headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# Include OpenSSL headers
include_directories(${OPENSSL_INCLUDE_DIR})

# Include Asio headers
include_directories(/usr/local/Cellar/asio/1.28.1/include)

# Find SQLite3 package
find_package(SQLite3 REQUIRED)

# Define the backend target
add_executable(backend main.cpp)

# Define the api target
add_executable(api api.cpp)


# Link against OpenSSL
target_link_libraries(backend OpenSSL::Crypto)
# Link against OpenSSL
target_link_libraries(api OpenSSL::Crypto)


# Link against SQLite3
target_link_libraries(backend SQLite::SQLite3)
# Link against SQLite3
target_link_libraries(api SQLite::SQLite3)
