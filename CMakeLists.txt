




# Use 

#   cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# in the build directory





# cmake_minimum_required(VERSION 3.10)

# project(requests)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # find the libraries
# find_package(OpenSSL REQUIRED)

# # Include directories
# include_directories(${PROJECT_SOURCE_DIR}/headers)
# include_directories(${PROJECT_SOURCE_DIR}/prototypes)
# include_directories(${OPENSSL_INCLUDE_DIR})  # Add OpenSSL include directory


# # Create output directories
# file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)


# # Add source files
# set(SOURCES
#     ${PROJECT_SOURCE_DIR}/libs/networking_functions.c++
#     ${PROJECT_SOURCE_DIR}/libs/string_functions.c++
#     ${PROJECT_SOURCE_DIR}/tests/requests_tests.c++
# )


# # Create static libraries from source files
# add_library(networking_functions STATIC ${PROJECT_SOURCE_DIR}/libs/networking_functions.c++)
# add_library(string_functions STATIC ${PROJECT_SOURCE_DIR}/libs/string_functions.c++)
# add_library(requests_ STATIC ${PROJECT_SOURCE_DIR}/libs/requests.c++)


# # Create executables
# add_executable(requests_tests ${PROJECT_SOURCE_DIR}/tests/requests_tests.c++)


# # Link libraries to executables
# target_link_libraries(requests_tests PRIVATE networking_functions string_functions requests_)

# # Set output directory for the executables
# set_target_properties(requests_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)


# # Add compiler warning flags
# if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
#     target_compile_options(networking_functions PRIVATE -Wall -Wextra)
#     target_compile_options(string_functions PRIVATE -Wall -Wextra)
#     target_compile_options(requests_ PRIVATE -Wall -Wextra)
#     target_compile_options(requests_tests PRIVATE -Wall -Wextra)
# elseif(MSVC)
#     target_compile_options(requests_tests PRIVATE /W4)  # Use level 4 warnings for MSVC
# endif()














cmake_minimum_required(VERSION 3.10)

project(requests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the OpenSSL libraries
find_package(OpenSSL REQUIRED)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/headers)
include_directories(${PROJECT_SOURCE_DIR}/prototypes)
include_directories(${OPENSSL_INCLUDE_DIR})  # Add OpenSSL include directory

# Create output directories
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)

# Add source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/libs/networking_functions.c++
    ${PROJECT_SOURCE_DIR}/libs/string_functions.c++
    ${PROJECT_SOURCE_DIR}/tests/requests_tests.c++
)

# Create static libraries from source files
add_library(networking_functions STATIC ${SOURCES})
add_library(string_functions STATIC ${SOURCES})
add_library(requests_ STATIC ${SOURCES})

# Create executables
add_executable(requests_tests ${PROJECT_SOURCE_DIR}/tests/requests_tests.c++)

# Link libraries to executables
target_link_libraries(requests_tests PRIVATE networking_functions string_functions requests_ OpenSSL::SSL OpenSSL::Crypto)

# Set output directory for the executables
set_target_properties(requests_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)

# Add compiler warning flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(networking_functions PRIVATE -Wall -Wextra)
    target_compile_options(string_functions PRIVATE -Wall -Wextra)
    target_compile_options(requests_ PRIVATE -Wall -Wextra)
    target_compile_options(requests_tests PRIVATE -Wall -Wextra)
elseif(MSVC)
    target_compile_options(requests_tests PRIVATE /W4)  # Use level 4 warnings for MSVC
endif()
