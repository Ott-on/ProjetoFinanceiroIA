#pragma once

#include "../Entities/ConversationMessage.h"

#include <string>
#include <vector>
#include <cstddef>

class IConversationMessageRepository {
public:
    virtual ~IConversationMessageRepository() = default;

    virtual ConversationMessage create(
        const ConversationMessage& message
    ) = 0;

    virtual std::vector<ConversationMessage> findByUserId(
        const std::string& userId,
        std::size_t limit
    ) = 0;
};