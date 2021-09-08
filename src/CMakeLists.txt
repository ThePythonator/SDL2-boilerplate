include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(YourGame ${PROJECT_SOURCE})

target_link_libraries(YourGame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})