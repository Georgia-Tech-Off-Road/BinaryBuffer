#Disclaimer: Much of this code was taken from: https://github.com/google/googletest/tree/main/googletest

add_library(BinaryBuffer INTERFACE)
target_include_directories(BinaryBuffer INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../")

include(CTest)

# To use Boost/endian
# Implementation taken from: https://www.boost.org/doc/user-guide/building-with-cmake.html
find_package(Boost REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(BinaryBufferTest BinaryBuffer_unittest.cpp)
target_link_libraries(BinaryBufferTest PUBLIC gtest_main)

# Include Boost header files
target_include_directories(BinaryBufferTest PRIVATE ${Boost_INCLUDE_DIRS})

add_test(NAME BinaryBufferTest COMMAND BinaryBufferTest)