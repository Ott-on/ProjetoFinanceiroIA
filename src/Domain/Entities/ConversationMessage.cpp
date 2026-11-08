
#include "ConversationMessage.h"

#include <utility>

ConversationMessage::ConversationMessage(
    std::string id,
    std::string userId,
    MessageRole role,
    std::string content
)
    : id_(std::move(id)),
    userId_(std::move(userId)),
    role_(role),
    content_(std::move(content)),
    createdAt_(std::chrono::system_clock::now())
{
}

const std::string& ConversationMessage::getId() const {
    return id_;
}

const std::string& ConversationMessage::getUserId() const {
    return userId_;
}

MessageRole ConversationMessage::getRole() const {
    return role_;
}

const std::string& ConversationMessage::getContent() const {
    return content_;
}

ConversationMessage::Timestamp ConversationMessage::getCreatedAt() const {
    return createdAt_;
}
