# CMakeList.txt : CMake project for PytorchCpp, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project ("PytorchCpp")

set(CMAKE_PREFIX_PATH "C:/Users/Alstra/Documents/Libtorch")
find_package(Torch REQUIRED)

# Add source to this project's executable.
add_executable (PytorchCpp "PytorchCpp.cpp" "PytorchCpp.h")
target_link_libraries(PytorchCpp "${TORCH_LIBRARIES}")
set_property(TARGET PytorchCpp PROPERTY CXX_STANDARD 17)

if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET PytorchCpp
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:PytorchCpp>)
endif (MSVC)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PytorchCpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
