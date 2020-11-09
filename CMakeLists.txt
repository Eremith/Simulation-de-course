cmake_minimum_required (VERSION 3.9)
project(SFML_Test2)
set(CompilerFlags
	CMAKE_CXX_FLAGS
	CMAKE_CXX_FLAGS_DEBUG
	CMAKE_CXX_FLAGS_RELEASE
	CMAKE_C_FLAGS      
	CMAKE_C_FLAGS_DEBUG    
	CMAKE_C_FLAGS_RELEASE        
	)
if(MSVC) 
	foreach(CompilerFlag ${CompilerFlags})   
		string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")  
		string(REPLACE "/W3" "/W4" ${CompilerFlag} "${${CompilerFlag}}")        
		set(CompilerFlag "${CompilerFlag} /std:c++17")    
	endforeach()    
	set(SFML_STATIC_LIBRARIES TRUE)    
	set(SFML_DIR "C:/SFML-2.5.1_windows_VS15.6_static/lib/cmake/SFML")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL"GNU")   
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")
endif()
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
set(SRCS "main.cpp" "Point3D.cpp" "Runner.cpp")
set(HEADERS "Point3D.h" "Runner.h")
add_executable (Simulation-course ${SRCS} ${HEADERS})
target_link_libraries(Simulation-course sfml-graphics sfml-window)