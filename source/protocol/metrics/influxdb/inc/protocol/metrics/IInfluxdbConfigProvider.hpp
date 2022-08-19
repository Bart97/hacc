#pragma once
#include <string>

namespace protocol::metrics
{
class IInfluxdbConfigProvider
{
public:
    virtual ~IInfluxdbConfigProvider() = default;
    virtual std::string getHostname() const = 0;
    virtual std::uint16_t getPort() const = 0;
    virtual std::string getDatabase() const = 0;
    virtual std::string getBucket() const = 0;
    virtual std::string getOrganization() const = 0;
    virtual std::string getApiKey() const = 0;
};
} // namespace protocol::metrics
