project(morr_text_dll)			# Название проекта									
cmake_minimum_required(VERSION 2.8) # Проверка версии CMake.
                                    # Если версия установленой программы
                                    # старее указаной, произайдёт аварийный выход.
include_directories(include)
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release ReleaseProtect)
   set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
     "Reset the configurations to what we need"
     FORCE)
 endif()
set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /D NDEBUG ")
 
set(CMAKE_CXX_FLAGS_RELEASEPROTECT ${CMAKE_CXX_FLAGS_RELEASE} " /D AngelPROTECT ")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASEPROTECT ${CMAKE_SHARED_LINKER_FLAGS_RELEASE})
set(SOURCE_DLL 
src/armor_fix.cpp
src/cdcheck.cpp
src/Console.cpp
src/crc32.cpp
src/DialogEngine.cpp
src/DictStr.cpp
src/HelperFunctions.cpp
src/items_info.cpp
src/morr_text_dll.cpp
src/mw_exepatches.cpp
src/mw_input.cpp
src/mw_layout.cpp
src/stdafx.cpp
src/Topic.cpp

)
list(APPEND RCFILE  morr_text_dll.rc)
add_library(text SHARED ${SOURCE_DLL})
									
