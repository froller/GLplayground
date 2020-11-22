cmake_minimum_required(VERSION 3.17)

project(GLplayground)

set(OpenGL_GL_PREFERENCE "GLVND")

set(CMAKE_glsl_COMPILE_OBJECT )

if(WIN32)
    # Copy NuGet packages config
    set(PACKAGES_CONFIG "packages.config")
    message(STATUS "Copying ${PROJECT_SOURCE_DIR}/${PACKAGES_CONFIG} to ${PROJECT_BINARY_DIR}")
    file(READ "${PROJECT_SOURCE_DIR}/${PACKAGES_CONFIG}" TMP)
    file(WRITE "${PROJECT_BINARY_DIR}/${PACKAGES_CONFIG}" "${TMP}")

    # Package settings for NuGet
    set(SDL2_LIBRARIES "SDL2.lib")
    set(GLEW_LIBRARIES "glew32.lib")
    set(OPENGL_LIBRARIES "OpenGL32.lib")
    set(PNG_LIBRARIES "libpng16.lib")

    set(SDL2_LIBDIR "build/packages/sdl2.2.0.5/build/native/lib/$(Platform)/dynamic")
    set(SDL2_BINDIR "build/packages/sdl2.redist.2.0.5/build/native/bin/$(Platform)/dynamic")
    set(GLEW_LIBDIR "build/packages/Glew_dynamic.2.0.0.0/build/native/lib/v140/$(Platform)")

    set(SDL2_INCLUDE_DIRS "build/packages/sdl2.2.0.5/build/native/include")
    set(GLEW_INCLUDE_DIRS "build/packages/Glew_dynamic.2.0.0.0/build/native/include")
    set(GLM_INCLUDE_DIRS "build/packages/glm.0.9.9.800/build/native/include")

    set(glm_FOUND TRUE)
else()
    # Finding dependencies
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glm REQUIRED)

endif()

if(${glm_FOUND})
    add_compile_definitions("WITH_GLM")
endif()

# Add global definitions
#add_compile_options("-Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Add compiler flags
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    add_compile_options(-Wno-write-strings -pedantic)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -ggdb")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb")
elseif(WIN32)
    add_compile_definitions(_UNICODE UNICODE)
    remove_definitions(MBCS)
endif()

set(SOURCES
    main.cpp
    Graphene/graphene.h
    Graphene/graphene_types.h
    Graphene/graphene.cpp
    Graphene/shader.h
    Graphene/shader.cpp
    Graphene/program.h
    Graphene/program.cpp
    Graphene/object.h
    Graphene/object.cpp
    Graphene/model.h
    Graphene/model.cpp
    Graphene/simpleobjects.h
    Graphene/simpleobjects.cpp
    Graphene/camera.h
    Graphene/camera.cpp
    Graphene/light.h
    Graphene/light.cpp
    Graphene/scene.h
    Graphene/scene.cpp
)
set(SHADERS
    fragment.glsl
    vertex.glsl
)

if (WIN32)
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCES})
    set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY VS_PACKAGE_REFERENCES "sdl2_2.0.5;GLEW_dynamic_2.0.0.0;glm_0.9.9.800")
else()
    add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
endif()

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Graphene/" ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC ${SDL2_LIBDIR} ${GLEW_LIBDIR})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

set_source_files_properties(fragment.glsl vertex.glsl
    PROPERTIES
    LANGUAGE glsl
    VS_COPY_TO_OUT_DIR Always
)
source_group(Shaders REGULAR_EXPRESSION glsl$)
add_custom_target(Shaders SOURCES ${SHADERS})

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)
