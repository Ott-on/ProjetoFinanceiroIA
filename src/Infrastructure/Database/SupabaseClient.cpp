#include "SupabaseClient.h"

#include <curl/curl.h>

#include <stdexcept>
#include <utility>

// Recebe os dados enviados pelo servidor.
static size_t writeCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    void* userData
) {
    size_t totalSize = size * nmemb;

    std::string* response =
        static_cast<std::string*>(userData);

    response->append(
        static_cast<char*>(contents),
        totalSize
    );

    return totalSize;
}

SupabaseClient::SupabaseClient(
    std::string supabaseUrl,
    std::string apiKey
)
    : supabaseUrl_(std::move(supabaseUrl)),
    apiKey_(std::move(apiKey))
{
    if (supabaseUrl_.empty() || apiKey_.empty()) {
        throw std::invalid_argument(
            "Supabase URL e API Key sao obrigatorios."
        );
    }
}

std::string SupabaseClient::get(
    const std::string& endpoint
) {
    return request("GET", endpoint);
}

std::string SupabaseClient::post(
    const std::string& endpoint,
    const std::string& body
) {
    return request("POST", endpoint, body);
}

std::string SupabaseClient::patch(
    const std::string& endpoint,
    const std::string& body
) {
    return request("PATCH", endpoint, body);
}

std::string SupabaseClient::request(
    const std::string& method,
    const std::string& endpoint,
    const std::string& body
) {
    CURL* curl = curl_easy_init();

    if (!curl) {
        throw std::runtime_error(
            "Falha ao inicializar o libcurl."
        );
    }

    std::string response;

    std::string url = supabaseUrl_ + endpoint;

    struct curl_slist* headers = nullptr;

    headers = curl_slist_append(
        headers,
        ("apikey: " + apiKey_).c_str()
    );

    headers = curl_slist_append(
        headers,
        "Content-Type: application/json"
    );

    headers = curl_slist_append(
        headers,
        "Accept: application/json"
    );

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(
        curl,
        CURLOPT_HTTPHEADER,
        headers
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        writeCallback
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEDATA,
        &response
    );

    curl_easy_setopt(
        curl,
        CURLOPT_TIMEOUT,
        30L
    );

    if (method == "POST") {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(
            curl,
            CURLOPT_POSTFIELDS,
            body.c_str()
        );
    }
    else if (method == "PATCH") {
        curl_easy_setopt(
            curl,
            CURLOPT_CUSTOMREQUEST,
            "PATCH"
        );

        curl_easy_setopt(
            curl,
            CURLOPT_POSTFIELDS,
            body.c_str()
        );
    }

    CURLcode result = curl_easy_perform(curl);

    long statusCode = 0;

    curl_easy_getinfo(
        curl,
        CURLINFO_RESPONSE_CODE,
        &statusCode
    );

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (result != CURLE_OK) {
        throw std::runtime_error(
            std::string("Erro na requisicao: ") +
            curl_easy_strerror(result)
        );
    }

    if (statusCode < 200 || statusCode >= 300) {
        throw std::runtime_error(
            "Erro HTTP " + std::to_string(statusCode) +
            ": " + response
        );
    }

    return response;
}