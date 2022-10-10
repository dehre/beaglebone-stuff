cmake_minimum_required(VERSION 3.21)
project(beaglebone-stuff VERSION 1.0)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_C_STANDARD 17)

set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# See: https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
add_compile_options(
    -g3
    -O0
    $<$<CONFIG:RELEASE>:-g0> # overwrites -g3
    $<$<CONFIG:RELEASE>:-O3> # overwrites -O0

    -Wall -Wextra             # reasonable and standard
    -Wshadow                  # warn the user if a variable declaration shadows one from a parent context
    -Wnon-virtual-dtor        # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
    -Wold-style-cast          # warn for c-style casts
    -Wcast-align              # warn for potential performance problem casts
    -Wunused                  # warn on anything being unused
    -Woverloaded-virtual      # warn if you overload (not override) a virtual function
    -Wconversion              # warn on type conversions that may lose data
    -Wsign-conversion         # (Clang all versions, GCC >= 4.3) warn on sign conversions
    -Wmisleading-indentation  # (only in GCC >= 6.0) warn if indentation implies blocks where blocks do not exist
    -Wnull-dereference        # (only in GCC >= 6.0) warn if a null dereference is detected
    -Wdouble-promotion        # (GCC >= 4.6, Clang >= 3.8) warn if float is implicit promoted to double
    -Wformat=2                # warn on security issues around functions that format output (ie printf)
    -Weffc++                  # warning mode can be too noisy, but if it works for your project, use it also
    -Wduplicated-cond         # (only in GCC >= 6.0) warn if if / else chain has duplicated conditions
    -Wduplicated-branches     # (only in GCC >= 7.0) warn if if / else branches have duplicated code
    -Wlogical-op              # (only in GCC) warn about logical operations being used where bitwise were probably wanted
    -Wuseless-cast            # (only in GCC >= 4.8) warn if you perform a cast to the same type
#   -pedantic                 # warn on language extensions
#   -Werror                   # treat warnings as errors
  )

# add_link_options(-pthread)
add_compile_definitions($<$<NOT:$<CONFIG:RELEASE>>:DEBUG>)

############################################################
## TARGET: GPIO
############################################################

add_executable(gpio gpio/main.cpp gpio/GPIO.cpp)
# target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)
# target_link_libraries(main PRIVATE somelib)

############################################################
## TARGET: I2C
############################################################

add_executable(i2c i2c/main.cpp)
# target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)
# target_link_libraries(main PRIVATE somelib)
