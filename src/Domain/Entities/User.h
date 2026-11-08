
#pragma once

#include <optional>
#include <cstdint>
#include <chrono>
#include <string>

enum class InvestmentHorizon {
    ShortTerm,
    MediumTerm,
    LongTerm
};

enum class InvestmentExperience {
    Beginner,
    Intermediate,
    Advanced
};

enum class RiskTolerance {
    Conservative,
    Moderate,
    Aggressive
};

class User {
public:
    using Timestamp = std::chrono::system_clock::time_point;

    User(
        std::string id,
        std::int64_t telegramId,
        std::string name,
        std::optional<InvestmentHorizon> investmentHorizon = std::nullopt,
        std::optional<InvestmentExperience> investmentExperience = std::nullopt,
        std::optional<RiskTolerance> riskTolerance = std::nullopt
    );

    const std::string& getId() const;
    std::int64_t getTelegramId() const;
    const std::string& getName() const;

    const std::optional<InvestmentHorizon>& getInvestmentHorizon() const;
    const std::optional<InvestmentExperience>& getInvestmentExperience() const;
    const std::optional<RiskTolerance>& getRiskTolerance() const;

    Timestamp getCreatedAt() const;
    Timestamp getUpdatedAt() const;

private:
    std::string id_;
    std::int64_t telegramId_;
    std::string name_;

    std::optional<InvestmentHorizon> investmentHorizon_;
    std::optional<InvestmentExperience> investmentExperience_;
    std::optional<RiskTolerance> riskTolerance_;

    Timestamp createdAt_;
    Timestamp updatedAt_;
};
