cmake_minimum_required(VERSION 3.11)
execute_process(COMMAND cargo build --release
                WORKING_DIRECTORY ffi-examples)

link_directories("ffi-examples/target/release/")
add_executable(reverse
    main.c
    ffi-examples.h)

target_link_libraries(reverse rusty)