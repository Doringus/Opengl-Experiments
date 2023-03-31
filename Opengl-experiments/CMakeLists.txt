cmake_minimum_required (VERSION 3.8)

project ("Opengl-experiments")


find_package(GLEW)
find_package(glfw3)
find_package(spdlog)
find_package(glm)
find_package(stb)

#CXX
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Sources
file(GLOB_RECURSE HEADERS  "src/*.hpp")
file(GLOB_RECURSE SRC "src/*.cpp")


add_executable (Opengl-experiments ${HEADERS} ${SRC})

#Link conan libs
target_link_libraries(Opengl-experiments PRIVATE
                      GLEW::GLEW glfw spdlog::spdlog spdlog::spdlog_header_only glm::glm)
target_include_directories(Opengl-experiments PRIVATE ${Stb_INCLUDE_DIR})

#Copy resources
add_custom_command(TARGET Opengl-experiments PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BUILD_DIRECTORY}/res)

add_custom_command(TARGET Opengl-experiments PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:Opengl-experiments>/res)