
#pragma once

#include <chrono>
#include <string>

enum class MessageRole {
    User,
    Assistant
};

class ConversationMessage {
public:
    using Timestamp = std::chrono::system_clock::time_point;

    ConversationMessage(
        std::string id,
        std::string userId,
        MessageRole role,
        std::string content
    );

    const std::string& getId() const;
    const std::string& getUserId() const;

    MessageRole getRole() const;
    const std::string& getContent() const;

    Timestamp getCreatedAt() const;

private:
    std::string id_;
    std::string userId_;

    MessageRole role_;
    std::string content_;

    Timestamp createdAt_;
};
