#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include "protocol/mqtt/IMqttClient.hpp"
#include "protocol/mqtt/IMqttWrapper.hpp"

namespace protocol::mqtt
{
class MqttClient : public IMqttClient
{
public:
    explicit MqttClient(std::shared_ptr<IMqttWrapper>);

    void processMessages() override;

    void publish(const std::string& string, const std::string& string1) override;
    void subscribe(const std::string& string, PublishCallback callback) override;

private:
    void queuePublishedMessage(const PublishedMessage&);
    PublishedMessage popMessage();

    std::multimap<std::string, PublishCallback> callbackMap;
    std::shared_ptr<IMqttWrapper> wrapper;
    std::mutex queueMutex;
    std::queue<PublishedMessage> messageQueue;
};
} // namespace protocol::mqtt
