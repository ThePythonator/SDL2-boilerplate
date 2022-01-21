include(FetchContent)

FetchContent_Declare(json
	GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
	GIT_TAG v3.10.4
)

FetchContent_GetProperties(json)

if(NOT json_POPULATED)
	FetchContent_Populate(json)
	add_subdirectory(${json_SOURCE_DIR} JSON EXCLUDE_FROM_ALL)
endif()