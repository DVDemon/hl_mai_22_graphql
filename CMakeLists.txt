cmake_minimum_required(VERSION 3.2)

project(hl_graphql C CXX)

SET (EXAMPLE_BINARY "hl_graphql")
SET (GRAPHQL_LIBS "libgraphqlclient.so")
LIST(APPEND GRAPHQL_LIBS "libgraphqlintrospection.so")
LIST(APPEND GRAPHQL_LIBS "libgraphqlpeg.so")
LIST(APPEND GRAPHQL_LIBS "libgraphqljson.so")
LIST(APPEND GRAPHQL_LIBS "libgraphqlresponse.so")
LIST(APPEND GRAPHQL_LIBS "libgraphqlservice.so")

SET (POCO_DATA_LIBS "libPocoData.so")
LIST(APPEND POCO_DATA_LIBS "libPocoDataMySQL.so")
LIST(APPEND POCO_DATA_LIBS "libmysqlclient.so")  

find_package(OpenSSL)
find_package(GTest REQUIRED)
find_package(Threads)
find_package(ZLIB)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL)
find_package(Boost COMPONENTS filesystem system program_options regex REQUIRED)

if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

include_directories(${Poco_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})
include_directories("/usr/include/mysql")
include_directories("/usr/local/include/mysql")
link_directories("/usr/local/lib")


add_executable(${EXAMPLE_BINARY} main.cpp 
                                 config/config.cpp 
                                 database/database.cpp
                                 database/AuthorObject.cpp
                                 database/GQLSchema.cpp
                                 database/QueryObject.cpp)

target_include_directories(${EXAMPLE_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${EXAMPLE_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror )

target_link_libraries(${EXAMPLE_BINARY} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES}
                             ${POCO_DATA_LIBS}
                             ${GRAPHQL_LIBS}
                             ${Boost_LIBRARIES}
                             stdc++fs
                             ZLIB::ZLIB)

set_target_properties(${EXAMPLE_BINARY} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${EXAMPLE_BINARY} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)