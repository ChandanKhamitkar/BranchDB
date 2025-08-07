# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define your project name
project(BranchDB CXX)

set(CMAKE_CXX_STANDARD 17) # Use C++17 for std::optional
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Define source files for Executables
set(SRC_CORE_FILES
    src/main.cpp
    src/database.cpp
)
set(SRC_CLI_FILES

    # CLI Entry point
    src/cli/start_cli.cpp

    # CLI Commands
    src/cli/commands/set_command.cpp
    src/cli/commands/get_command.cpp
    src/cli/commands/del_command.cpp
    src/cli/commands/ttl_command.cpp
    src/cli/commands/expire_command.cpp
    src/cli/commands/exists_command.cpp
    src/cli/commands/persist_command.cpp
    src/cli/commands/getall_command.cpp
    src/cli/commands/flush_command.cpp
    src/cli/commands/info_command.cpp
    src/cli/commands/help_command.cpp

    # Commands helper
    src/cli/commands/helper/is_valid_seconds.cpp
    src/cli/commands/helper/enum_parse.cpp
    src/cli/commands/helper/trim_whitespaces.cpp
    src/cli/commands/helper/command_parser.cpp

    # Persistent Connect
    src/persistent_connect/handle_client.cpp
)
    
set(SRC_TEST_FILES
    # Test
    src/test/main_test.cpp
)
    
set(SRC_DB_FILES
    # DB
    src/db/value_metadata.cpp
    src/db/response_metadata.cpp
)
    
set(SRC_HELPER_FILES
    # HELPER
    src/helper/build_serialized_response.cpp
)

# ALL SRC FILES
set(ALL_SRC_FILES
    ${SRC_CORE_FILES}
    ${SRC_CLI_FILES}
    ${SRC_TEST_FILES}
    ${SRC_DB_FILES}
    ${SRC_HELPER_FILES}
)

# Add an Executabale target
add_executable(BranchDB ${ALL_SRC_FILES})

target_include_directories(BranchDB PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)