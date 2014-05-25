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

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "1")
set (CPACK_PACKAGE_VERSION_MINOR "0")
include (CPack)
