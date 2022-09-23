include_directories(includes)

add_library(ProgBarLibTest STATIC src/aux/progbar.cc)
add_library(FunctionalLibTest STATIC src/functional.cc)
add_library(CardsLibTest STATIC src/cards.cc)

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

include(GoogleTest)
gtest_discover_tests(cardstest)