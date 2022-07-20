cmake_minimum_required(VERSION 3.19)

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
    set(GLEW_BINDIR "build/packages/Glew_dynamic.2.0.0.0/build/native/bin/v140/$(Platform)")

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
    add_compile_options(-Wno-write-strings)
    add_compile_options(-pedantic)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -ggdb")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb")
elseif(WIN32)
    #add_compile_options(-W3)
    add_compile_definitions(_UNICODE UNICODE _CRT_SECURE_NO_WARNINGS)
    remove_definitions(MBCS)
endif()

###############################################################################

set(GRAPHENE_SOURCES
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
    Graphene/texture.h
    Graphene/texture.cpp
    Graphene/material.h
    Graphene/material.cpp
    Graphene/blinn.h
    Graphene/blinn.cpp
)
add_library(Graphene STATIC ${GRAPHENE_SOURCES})
target_include_directories(Graphene PUBLIC ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_directories(Graphene PUBLIC ${SDL2_LIBDIR} ${GLEW_LIBDIR} ${SDL2_BINDIR} ${GLEW_BINDIR})
target_link_libraries(Graphene PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
target_compile_features(Graphene PUBLIC cxx_std_17)
if (WIN32)
    set_property(TARGET Graphene PROPERTY VS_PACKAGE_REFERENCES "sdl2_2.0.5;GLEW_dynamic_2.0.0.0;glm_0.9.9.800")
endif()

###############################################################################

set(SOURCES
    main.cpp
)
if (WIN32)
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCES})
else()
    add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
endif()
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC Graphene)
set_property(GLOBAL
    PROPERTY
    VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME}
)

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Graphene/")

set_source_files_properties(fragment.glsl vertex.glsl
    PROPERTIES
    LANGUAGE glsl
    VS_COPY_TO_OUT_DIR Always
)
source_group("Source Files" REGULAR_EXPRESSION Graphene/.+\.c\(pp|c\)?$)
source_group("Header Files" REGULAR_EXPRESSION Graphene/.+\.h\(pp|h\)?$)
source_group(Shaders REGULAR_EXPRESSION \.glsl$)

###############################################################################

set(SHADERS
    Shaders/default.vertex.glsl
    Shaders/default.fragment.glsl
    Shaders/blinn.vertex.glsl
    Shaders/blinn.fragment.glsl
)
add_custom_target(Shaders SOURCES ${SHADERS})

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)
