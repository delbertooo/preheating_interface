idf_component_register(SRCS "preheating_interface_main.cpp"
                    INCLUDE_DIRS "")

set(LIB_SCHEDULNG_PATH ${preheating_interface_SOURCE_DIR}/main/lib/libscheduling)

add_subdirectory(lib/libpreheatinginterface)
add_subdirectory(lib/libscheduling)


include_directories(lib/libscheduling/src)
include_directories(lib/libpreheatinginterface/src)
link_directories(lib/libscheduling/src)
link_directories(lib/libpreheatinginterface/src)
target_link_libraries(${COMPONENT_LIB} PUBLIC LibScheduling LibPreheatingInterface)

