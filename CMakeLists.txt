# Запрашиваем минимальную версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

# Мета-информация о проекте
set(META_PROJECT_NAME module_webui)
set(META_LIB_NAME lib${META_PROJECT_NAME})
set(META_VERSION_MAJOR 0)
set(META_VERSION_MINOR 1)
set(META_VERSION_PATCH 0)
set(META_VERSION ${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH})
set(META_LANGUAGES C CXX)

project(${META_PROJECT_NAME} VERSION ${META_VERSION} LANGUAGES ${META_LANGUAGES})

if (NOT TARGET libmodule_core)
	add_subdirectory(modules/sway.module_core)
endif()

if (NOT TARGET libmodule_webcore)
	add_subdirectory(modules/sway.module_webcore)
endif()

if (NOT TARGET libmodule_webcore.mvc)
	add_subdirectory(modules/sway.module_webcore.mvc)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "emcc")

# Определяем каталог вывода по умолчанию
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else()
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif()

set(MODULE_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories("/home/bonus85/emsdk/emscripten/incoming/system/include")
include_directories(${MODULE_DIR}/include)
include_directories(${MODULE_DIR}/modules/sway.module_core/include)
include_directories(${MODULE_DIR}/modules/sway.module_webcore/include)
include_directories(${MODULE_DIR}/modules/sway.module_webcore.mvc/include)

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_HEADERS ${MODULE_DIR}/include/*.*)
file(GLOB_RECURSE MODULE_SOURCES ${MODULE_DIR}/src/*.*)

# Добавляем в проект цель для сборки статической библиотеки
add_library(${META_LIB_NAME} STATIC ${MODULE_SOURCES})
set_target_properties(${META_LIB_NAME} PROPERTIES OUTPUT_NAME ${META_PROJECT_NAME})
set_target_properties(${META_LIB_NAME} PROPERTIES PREFIX "")
set_target_properties(${META_LIB_NAME} PROPERTIES SUFFIX ".a.${META_VERSION}")

target_link_libraries(${META_LIB_NAME} libmodule_webcore libmodule_webcore.mvc)
