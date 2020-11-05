cmake_minimum_required(VERSION 3.17)

project(GLplayground)

set(OpenGL_GL_PREFERENCE "GLVND")

if(WIN32)
    # Package settings for NuGet
    set(SDL2_LIBRARIES "SDL2.lib")
    set(GLEW_LIBRARIES "glew.lib")
    set(OPENGL_LIBRARIES "OpenGL32.lib")
    set(PNG_LIBRARIES "libpng16.lib")

    set(SDL2_LIBDIR "build/packages/sdl2.2.0.5/build/native/lib/$(Platform)/dynamic")
    set(GLEW_LIBDIR "build/packages/glew.1.9.0.1/build/native/lib/v110/$(Platform)/$(Configuration)/dynamic")
    set(PNG_LIBDIR  "build/packages/libpng.1.6.28.1/build/native/lib/$(Platform)/v140/dynamic/$(Configuration)")
    set(ZLIB_LIBDIR "build/packages/zlib.v140.windesktop.msvcstl.dyn.rt-dyn.1.2.8.8/lib/native/v140/windesktop/msvcstl/dyn/rt-dyn/$(Platform)/$(Configuration)")

    set(SDL2_INCLUDE_DIRS "build/packages/sdl2.2.0.5/build/native/include")
    set(GLEW_INCLUDE_DIRS "build/packages/glew.1.9.0.1/build/native/include")
    set(GLM_INCLUDE_DIRS "build/packages/glm.0.9.9.800/build/native/include")
    set(PNG_INCLUDE_DIRS "build/packages/libpng.1.6.28.1/build/native/include")
    set(ZLIB_INCLUDE_DIRS "build/packages/zlib.v140.windesktop.msvcstl.dyn.rt-dyn.1.2.8.8/build/native/include")

    set(PNG_FOUND TRUE)
    set(ZLIB_FOUND TRUE)

    add_compile_definitions("USE_GLM")
else()
    # Finding dependencies
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glm REQUIRED)
    find_package(PNG)

    if(${glm_FOUND})
        add_compile_definitions("USE_GLM")
    endif()
endif()

if(${PNG_FOUND})
    add_definitions(${PNG_DEFINITIONS})
    add_compile_definitions("WITH_PNG")
    if(${ZLIB_FOUND})
        add_compile_definitions("WITH_ZLIB")
    endif()
endif()

# Add global definitions
add_definitions("-Wall")

# Add compiler flags
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    add_compile_options(-Wno-write-strings)
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
    Graphene/simpleobjects.h
    Graphene/camera.h
    Graphene/graphene.cpp
    Graphene/shader.cpp
    Graphene/program.cpp
    Graphene/model.cpp
    Graphene/simpleobjects.cpp
    Graphene/camera.cpp
    Graphene/scene.cpp
)

if (WIN32)
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCES})
    set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY VS_PACKAGE_REFERENCES "sdl2_2.0.5;glew_1.9.0.1;glm_0.9.9.800;libpng_1.6.28.1;zlib_v140.windesktop.msvcstl.dyn.rt-dyn.1.2.8.8")
else()
    add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
endif()

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Graphene/" ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC ${SDL2_LIBDIR} ${GLEW_LIBDIR})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)
