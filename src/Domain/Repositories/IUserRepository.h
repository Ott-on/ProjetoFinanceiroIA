#pragma once

#include "../Entities/User.h"

#include <cstdint>
#include <optional>

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual User create(const User& user) = 0;

    virtual std::optional<User> findByTelegramId(
        std::int64_t telegramId
    ) = 0;

    virtual void update(const User& user) = 0;
};