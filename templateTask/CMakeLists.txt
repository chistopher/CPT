
#get current foldername as executable name
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${ProjectId} main.cpp)