


cmake_minimum_required(VERSION 4.0.0)

project("Requests" VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(source_extensions ".c++" ".C++" ".cpp" ".cxx" ".cc" ".CC")
set(header_extensions ".h++" ".H++" ".hpp" ".hxx" ".hh" ".H" ".h" "")


include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries)

FetchContent_Declare(
    networking
    GIT_REPOSITORY git@gitlab.com:fastest-ho-group/Networking-library.git
    GIT_TAG version1.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(networking)


set(hosts "${CMAKE_CURRENT_SOURCE_DIR}/Hosts")
set(urls "${CMAKE_CURRENT_SOURCE_DIR}/Url")

add_library(
    Requests STATIC 
    "${urls}/url.c++"
    "${hosts}/host.c++"
)

target_include_directories(Requests PUBLIC
    "${urls}"
    "${hosts}"
)

target_link_libraries(Requests PUBLIC networking)


if(PROJECT_IS_TOP_LEVEL)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/objects")
    file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})


    set(test_directory "${CMAKE_CURRENT_SOURCE_DIR}/Tests")
    set(web_content_dir "${test_directory}/web content")
    set(test_cert "${web_content_dir}/cert.pem")
    set(test_key "${web_content_dir}/key.pem")

    file(MAKE_DIRECTORY "${web_content_dir}")

    if(NOT EXISTS "${test_cert}" AND NOT EXISTS "${test_key}")
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



    include(FetchContent)
    set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries)

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

    add_executable(
        host_tests
        "${test_directory}/Host Tests.c++"
        "${urls}"
    )

    target_include_directories(host_tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Url")
    target_link_libraries(host_tests PRIVATE networking gtest_main)
    set_target_properties(host_tests PROPERTIES OUTPUt_NAME "Host Tests")
    gtest_discover_tests(host_tests WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DISCOVERY_MODE PRE_TEST)


endif(PROJECT_IS_TOP_LEVEL)
