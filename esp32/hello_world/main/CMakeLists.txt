idf_component_register(SRCS "hello_world_main.cpp"
                    INCLUDE_DIRS "")

set(LIB_SCHEDULNG_PATH ${hello_world_SOURCE_DIR}/main/lib/libscheduling)

add_subdirectory(lib/libpreheatinginterface)
add_subdirectory(lib/libscheduling)


include_directories(lib/libscheduling/src)
include_directories(lib/libpreheatinginterface/src)
link_directories(lib/libscheduling/src)
link_directories(lib/libpreheatinginterface/src)
target_link_libraries(${COMPONENT_LIB} PUBLIC LibScheduling LibPreheatingInterface)

