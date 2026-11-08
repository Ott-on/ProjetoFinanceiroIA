#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <filesystem>

#include "Infrastructure/Database/SupabaseClient.h"
#include "Infrastructure/Database/UserRepository.h"

std::string trim(const std::string& value) {
    const auto first = value.find_first_not_of(" \t\r\n");

    if (first == std::string::npos) {
        return "";
    }

    const auto last = value.find_last_not_of(" \t\r\n");

    return value.substr(first, last - first + 1);
}

void loadEnv(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo .env");
    }

    std::string line;

    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        const auto separator = line.find('=');

        if (separator == std::string::npos) {
            continue;
        }

        std::string key = trim(line.substr(0, separator));
        std::string value = trim(line.substr(separator + 1));

        if (key.empty()) {
            continue;
        }

        if (_putenv_s(key.c_str(), value.c_str()) != 0) {
            throw std::runtime_error("Falha ao configurar variavel: " + key);
        }
    }
}

int main() {
    try {
        std::filesystem::path envPath =
            std::filesystem::path(PROJECT_ROOT) / ".env";

        loadEnv(envPath.string());

        const char* url = std::getenv("SUPABASE_URL");
        const char* key = std::getenv("SUPABASE_SECRET_KEY");

        if (url == nullptr || key == nullptr ||
            url[0] == '\0' || key[0] == '\0') {
            throw std::runtime_error("Credenciais nao configuradas.");
        }

        SupabaseClient client(url, key);
        UserRepository repository(client);

        User user("", 987654321, "Usuario Teste");

        User createdUser = repository.create(user);

        std::cout << "Usuario cadastrado!\n";
        std::cout << "ID: " << createdUser.getId() << '\n';
        std::cout << "Nome: " << createdUser.getName() << '\n';

        auto foundUser = repository.findByTelegramId(987654321);

        if (foundUser.has_value()) {
            std::cout << "\nUsuario encontrado!\n";
            std::cout << foundUser->getName() << '\n';
        }
    }
    catch (const std::exception& error) {
        std::cerr << "Erro: " << error.what() << '\n';
        return 1;
    }

    return 0;
}