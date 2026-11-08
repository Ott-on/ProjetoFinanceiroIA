
cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE
    "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING ""
)

project(FinanceAssistant
    VERSION 1.0.0
    LANGUAGES CXX
)

# Configuração do C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Executável principal
add_executable(FinanceAssistant
    src/FinanceAssistant.cpp
    src/FinanceAssistant.h
    src/Domain/Entities/User.cpp
    src/Domain/Entities/User.h
    src/Domain/Entities/ConversationMessage.cpp
    src/Domain/Entities/ConversationMessage.h
    src/Infrastructure/Database/SupabaseClient.cpp
    src/Infrastructure/Database/SupabaseClient.h
    src/Infrastructure/Database/UserRepository.cpp
    src/Infrastructure/Database/UserRepository.h
    src/Infrastructure/Database/ConversationMessageRepository.cpp
    src/Infrastructure/Database/ConversationMessageRepository.h
)

target_compile_definitions(FinanceAssistant PRIVATE
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)

target_link_libraries(FinanceAssistant PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)

# Configurações específicas do compilador MSVC
if(MSVC)
    target_compile_options(FinanceAssistant PRIVATE
        /W4
        /permissive-
    )
endif()