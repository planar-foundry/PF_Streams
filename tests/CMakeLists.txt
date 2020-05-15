add_executable(PF_Streams_UnitTests main.cpp Test_ByteStream.cpp)
target_link_libraries(PF_Streams_UnitTests PF_Debug PF_Streams PF_Test)

target_compile_options(PF_Streams_UnitTests PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>)

add_custom_command(TARGET PF_Streams_UnitTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:PF_Debug>
    $<TARGET_FILE:PF_Streams>
    $<TARGET_FILE_DIR:PF_Streams_UnitTests>)
