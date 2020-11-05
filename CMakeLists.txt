project(GLplayground)
cmake_minimum_required(VERSION 3.17)

# Finding dependencies
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# Add global definitions
add_definitions("-Wall")

# Add compiler flags
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    add_compile_options(-Wno-write-strings)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -ggdb")
endif()

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    Graphene/graphene.h
    Graphene/graphene_types.h
    Graphene/graphene.cpp
    Graphene/shader.cpp
    Graphene/program.cpp
    Graphene/model.cpp
    Graphene/simpleobjects.h
    Graphene/simpleobjects.cpp
    Graphene/camera.h
    Graphene/camera.cpp
    Graphene/light.h
    Graphene/light.cpp
    Graphene/scene.cpp
)

#target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -frepo)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USE_GLM)
target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Graphene/" ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC ${SDL2_LIBDIR} ${GLEW_LIBDIR})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)
