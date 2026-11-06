
cmake_minimum_required(VERSION 3.21)

project(FinanceAssistant
    VERSION 1.0.0
    LANGUAGES CXX
)

# Configuração do C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Executável principal
add_executable(FinanceAssistant
    src/FinanceAssistant.cpp
    src/FinanceAssistant.h
)

# Configurações específicas do compilador MSVC
if(MSVC)
    target_compile_options(FinanceAssistant PRIVATE
        /W4
        /permissive-
    )
endif()