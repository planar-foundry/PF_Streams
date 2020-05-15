add_library(PF_Streams PF_Streams/ByteStream.cpp PF_Streams/ByteStream.hpp)

if (${PFSTREAMS_BIG_ENDIAN})
    target_compile_definitions(PF_Streams PRIVATE "PFENDIAN_BYTE_ORDER_BIG_ENDIAN")
endif()

target_include_directories(PF_Streams PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(PF_Streams PRIVATE PF_Debug PF_Endian)

target_compile_options(PF_Streams PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>)
