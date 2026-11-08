
#include "User.h"

#include <utility>

User::User(
    std::string id,
    std::int64_t telegramId,
    std::string name,
    std::optional<InvestmentHorizon> investmentHorizon,
    std::optional<InvestmentExperience> investmentExperience,
    std::optional<RiskTolerance> riskTolerance
)
    : id_(std::move(id)),
    telegramId_(telegramId),
    name_(std::move(name)),
    investmentHorizon_(investmentHorizon),
    investmentExperience_(investmentExperience),
    riskTolerance_(riskTolerance),
    createdAt_(std::chrono::system_clock::now()),
    updatedAt_(createdAt_)
{
}

const std::string& User::getId() const {
    return id_;
}

std::int64_t User::getTelegramId() const {
    return telegramId_;
}

const std::string& User::getName() const {
    return name_;
}

const std::optional<InvestmentHorizon>&
User::getInvestmentHorizon() const {
    return investmentHorizon_;
}

const std::optional<InvestmentExperience>&
User::getInvestmentExperience() const {
    return investmentExperience_;
}

const std::optional<RiskTolerance>&
User::getRiskTolerance() const {
    return riskTolerance_;
}

User::Timestamp User::getCreatedAt() const {
    return createdAt_;
}

User::Timestamp User::getUpdatedAt() const {
    return updatedAt_;
}
