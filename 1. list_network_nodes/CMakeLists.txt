cmake_minimum_required(VERSION 3.28)
project(list_network_nodes)

set(MAIN_EXE main.c)
set(NETWORK_LIB network.c)
set(IPV4_CONVERT_LIB ipv4_convert.c)

add_library(GCS.1LNN.Network STATIC ${NETWORK_LIB})
add_executable(list_network_nodes ${MAIN_EXE})

target_link_libraries(list_network_nodes GCS.1LNN.Network GCS.C_ToBits.Bits m)
