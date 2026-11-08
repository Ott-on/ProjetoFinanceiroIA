#pragma once

#include "../../Domain/Repositories/IUserRepository.h"
#include "SupabaseClient.h"

class UserRepository : public IUserRepository {
public:
    explicit UserRepository(SupabaseClient& client);

    User create(const User& user) override;

    std::optional<User> findByTelegramId(
        std::int64_t telegramId
    ) override;

    void update(const User& user) override;

private:
    SupabaseClient& client_;
};