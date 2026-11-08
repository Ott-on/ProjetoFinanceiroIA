#include "UserRepository.h"

#include <nlohmann/json.hpp>

#include <stdexcept>
#include <string>

using json = nlohmann::json;

static std::string toString(InvestmentHorizon value) {
    switch (value) {
    case InvestmentHorizon::ShortTerm:
        return "ShortTerm";

    case InvestmentHorizon::MediumTerm:
        return "MediumTerm";

    case InvestmentHorizon::LongTerm:
        return "LongTerm";
    }

    throw std::invalid_argument("Horizonte de investimento invalido.");
}

static std::string toString(InvestmentExperience value) {
    switch (value) {
    case InvestmentExperience::Beginner:
        return "Beginner";

    case InvestmentExperience::Intermediate:
        return "Intermediate";

    case InvestmentExperience::Advanced:
        return "Advanced";
    }

    throw std::invalid_argument("Experiencia de investimento invalida.");
}

static std::string toString(RiskTolerance value) {
    switch (value) {
    case RiskTolerance::Conservative:
        return "Conservative";

    case RiskTolerance::Moderate:
        return "Moderate";

    case RiskTolerance::Aggressive:
        return "Aggressive";
    }

    throw std::invalid_argument("Tolerancia ao risco invalida.");
}

static InvestmentHorizon parseHorizon(const std::string& value) {
    if (value == "ShortTerm")
        return InvestmentHorizon::ShortTerm;

    if (value == "MediumTerm")
        return InvestmentHorizon::MediumTerm;

    if (value == "LongTerm")
        return InvestmentHorizon::LongTerm;

    throw std::runtime_error("Horizonte desconhecido: " + value);
}

static InvestmentExperience parseExperience(const std::string& value) {
    if (value == "Beginner")
        return InvestmentExperience::Beginner;

    if (value == "Intermediate")
        return InvestmentExperience::Intermediate;

    if (value == "Advanced")
        return InvestmentExperience::Advanced;

    throw std::runtime_error("Experiencia desconhecida: " + value);
}

static RiskTolerance parseRisk(const std::string& value) {
    if (value == "Conservative")
        return RiskTolerance::Conservative;

    if (value == "Moderate")
        return RiskTolerance::Moderate;

    if (value == "Aggressive")
        return RiskTolerance::Aggressive;

    throw std::runtime_error("Tolerancia desconhecida: " + value);
}

UserRepository::UserRepository(SupabaseClient& client)
    : client_(client)
{
}

User UserRepository::create(const User & user) {

        json data;

        data["telegram_id"] = user.getTelegramId();
        data["name"] = user.getName();

        data["investment_horizon"] =
            user.getInvestmentHorizon().has_value()
            ? json(toString(*user.getInvestmentHorizon()))
            : json(nullptr);

        data["investment_experience"] =
            user.getInvestmentExperience().has_value()
            ? json(toString(*user.getInvestmentExperience()))
            : json(nullptr);

        data["risk_tolerance"] =
            user.getRiskTolerance().has_value()
            ? json(toString(*user.getRiskTolerance()))
            : json(nullptr);

        client_.post("/rest/v1/users", data.dump());

        auto createdUser = findByTelegramId(user.getTelegramId());

        if (!createdUser.has_value()) {
            throw std::runtime_error(
                "Usuario cadastrado, mas nao foi possivel recupera-lo."
            );
        }

        return *createdUser;
}

std::optional<User> UserRepository::findByTelegramId(
    std::int64_t telegramId
) {

    std::string endpoint =
        "/rest/v1/users?telegram_id=eq." +
        std::to_string(telegramId) +
        "&select=*";

    std::string response = client_.get(endpoint);

    json data = json::parse(response);

    if (data.empty()) {
        return std::nullopt;
    }

    const auto& record = data.at(0);

    std::optional<InvestmentHorizon> horizon;
    std::optional<InvestmentExperience> experience;
    std::optional<RiskTolerance> risk;

    if (!record.at("investment_horizon").is_null()) {
        horizon = parseHorizon(
            record.at("investment_horizon").get<std::string>()
        );
    }

    if (!record.at("investment_experience").is_null()) {
        experience = parseExperience(
            record.at("investment_experience").get<std::string>()
        );
    }

    if (!record.at("risk_tolerance").is_null()) {
        risk = parseRisk(
            record.at("risk_tolerance").get<std::string>()
        );
    }

    return User(
        record.at("id").get<std::string>(),
        record.at("telegram_id").get<std::int64_t>(),
        record.at("name").get<std::string>(),
        horizon,
        experience,
        risk
    );
}

void UserRepository::update(const User& user) {

    json data;

    data["name"] = user.getName();

    data["investment_horizon"] =
        user.getInvestmentHorizon().has_value()
        ? json(toString(*user.getInvestmentHorizon()))
        : json(nullptr);

    data["investment_experience"] =
        user.getInvestmentExperience().has_value()
        ? json(toString(*user.getInvestmentExperience()))
        : json(nullptr);

    data["risk_tolerance"] =
        user.getRiskTolerance().has_value()
        ? json(toString(*user.getRiskTolerance()))
        : json(nullptr);

    std::string endpoint =
        "/rest/v1/users?id=eq." + user.getId();

    client_.patch(endpoint, data.dump());
}