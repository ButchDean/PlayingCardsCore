cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(playing_cards_core)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(includes)

# Using GTest for unit testing
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

enable_testing()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_library(ProgBarLibTest STATIC src/aux/progbar.cc)
    add_library(FunctionalLibTest STATIC src/functional.cc)
    add_library(CardsLibTest STATIC src/cards.cc)

    add_executable(
        cardstest
        unittest/cardstest.cc
    )

    target_link_libraries(
        cardstest
        ProgBarLibTest
        FunctionalLibTest
        CardsLibTest
        gtest_main
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_executable(
        cardstest
        unittest/cardstest.cc
        src/aux/progbar.cc
        src/functional.cc
        src/cards.cc
        )

        target_link_libraries(
        cardstest
        gtest_main
        )
else()
    message(FATAL_ERROR "Only Mac and Linux officially supported.")
endif()

include(GoogleTest)
gtest_discover_tests(cardstest)
