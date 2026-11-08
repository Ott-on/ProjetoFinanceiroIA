#pragma once

#include <string>

class SupabaseClient {
public:
    SupabaseClient(
        std::string supabaseUrl,
        std::string apiKey
    );

    std::string get(const std::string& endpoint);

    std::string post(
        const std::string& endpoint,
        const std::string& body
    );

    std::string patch(
        const std::string& endpoint,
        const std::string& body
    );

private:
    std::string supabaseUrl_;
    std::string apiKey_;

    std::string request(
        const std::string& method,
        const std::string& endpoint,
        const std::string& body = ""
    );
};