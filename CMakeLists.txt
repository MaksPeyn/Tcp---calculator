cmake_minimum_required(VERSION 3.4)

project(boost-example
	VERSION 0.0.0
	LANGUAGES
		CXX
)

find_package(Boost 1.60 REQUIRED
	COMPONENTS
		filesystem
		system
)
add_executable(example
	"src/main.cpp"
)
target_link_libraries(example
	Boost::filesystem
	Boost::system
)