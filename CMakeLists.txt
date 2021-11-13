cmake_minimum_required(VERSION 3.4)

project(tcp-calculator
	VERSION 0.0.0
	LANGUAGES
		CXX
)

find_package(Threads REQUIRED)
find_package(Boost 1.60 REQUIRED
	COMPONENTS
		system
)
add_executable(calculator
	"src/main.cpp"
)
include_directories(include)
target_link_libraries(calculator ${Boost_LIBRARIES})

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(calculator PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(calculator "${CMAKE_THREAD_LIBS_INIT}")
endif()

