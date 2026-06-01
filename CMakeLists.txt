
cmake_minimum_required(VERSION 4.0.0)

project("Requests" VERSION 0.4.0 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(source_extensions ".c++" ".C++" ".cpp" ".cxx" ".cc" ".CC")
set(header_extensions ".h++" ".H++" ".hpp" ".hxx" ".hh" ".H" ".h" "")

include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries)

FetchContent_Declare(
    networking
    GIT_REPOSITORY git@gitlab.com:fastest-ho-group/Networking-library.git
    GIT_TAG version1.1
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(networking)
# get_target_property(networking_INCLUDE_DIRS networking INCLUDE_DIRECTORIES)
get_target_property(networking_INCLUDE_DIRS networking INTERFACE_INCLUDE_DIRECTORIES)




FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nlohmann_json)



FetchContent_Declare(
    string_functions
    GIT_REPOSITORY "git@gitlab.com:fastest-ho-group/string-functions.git"
    GIT_TAG version0.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(string_functions)


FetchContent_Declare(
    publicsuffix
    GIT_REPOSITORY https://github.com/publicsuffix/list.git
    GIT_TAG main            # or pin a commit hash for reproducible builds
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(publicsuffix)


# --- Library ---

set(model_directory "${CMAKE_CURRENT_SOURCE_DIR}/Model")
set(source_files "")
list(APPEND source_files 
    "${model_directory}/Impl/Url.c++"
    "${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/Impl/Request Exceptions.c++"
)

add_library(requests STATIC "${source_files}")

# target_compile_definitions(requests PRIVATE PSL_PATH="${publicsuffix_SOURCE_DIR}/public_suffix_list.dat")
target_include_directories(requests PRIVATE ${publicsuffix_SOURCE_DIR})

target_include_directories(requests PUBLIC "${model_directory}" "${networking_INCLUDE_DIRS}" "${CMAKE_CURRENT_SOURCE_DIR}/Exceptions")

target_link_libraries(requests PUBLIC networking nlohmann_json::nlohmann_json string_functions )

target_compile_features(requests PUBLIC cxx_std_23)



# --- Tests (only when this is top-level project) ---

if(PROJECT_IS_TOP_LEVEL)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Objects")
    file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    set(test_directory "${CMAKE_CURRENT_SOURCE_DIR}/Tests")
    set(web_content_directory "${test_directory}/web content")

    set(test_certification "${web_content_directory}/cert.pem")
    set(test_key "${web_content_directory}/key.pem")

    file(MAKE_DIRECTORY "${web_content_directory}")


    if(NOT EXISTS "${test_certification}" AND NOT EXISTS "${test_key}")
        find_program(OPENSSL_EXECUTABLE openssl)
        if(OPENSSL_EXECUTABLE)
            execute_process(
                COMMAND ${OPENSSL_EXECUTABLE} req
                    -x509
                    -newkey rsa:2048
                    -keyout "${test_key}"
                    -out "${test_cert}"
                    -days 365
                    -nodes
                    -subj "/CN=localhost"
                RESULT_VARIABLE openssl_result
                ERROR_VARIABLE openssl_error
            )
            if(NOT openssl_result EQUAL 0)
                message(WARNING "Failed to generate test certificates: ${openssl_error}")
            else()
                message(STATUS "Generated test certificates in ${web_content_dir}")
            endif()
        else()
            message(WARNING "OpenSSL executable not found — cannot generate test certificates")
        endif()
    endif()


    set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Libraries")

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    include(GoogleTest)

    # url tests
    add_executable(
        url_tests
        "${test_directory}/Url Tests.c++"
    )

    target_link_libraries(url_tests PRIVATE requests gtest_main)
    set_target_properties(url_tests PROPERTIES OUTPUT_NAME "Url Tests")
    gtest_discover_tests(url_tests WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DISCOVERY_MODE PRE_TEST)
    

endif(PROJECT_IS_TOP_LEVEL)