cmake_minimum_required (VERSION 2.8)
project (stikkit)
file(GLOB src 
    "*.hpp"
    "*.cpp"
)
add_executable(stikkit ${src})
find_package(CURL)
target_link_libraries(stikkit ${CURL_LIBRARIES})
install (TARGETS stikkit DESTINATION bin)


