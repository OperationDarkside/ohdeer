#ifndef OHDEER_COMPONENT
#define OHDEER_COMPONENT

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>
#include <sstream>

#include "boing/extern/CppJsonMagic/json_magic.cpp"
#include "event.cpp"

struct kv
{
    std::string key{};
    std::string value{};
};

struct component_dto
{
    std::string id{};
    std::string tag{};
    std::vector<kv> attributes{};
    std::vector<kv> properties{};
    std::vector<component_dto> children{};
    std::vector<std::string> events{};
};

class component
{
protected:
    std::map<std::string, std::string> properties{};
    std::map<std::string, std::string> attributes{};
    std::vector<std::shared_ptr<component>> children{};
    std::map<std::string, std::function<void(const std::string &)>> listeners{};

public:
    std::string id{};
    std::string tag{};

    explicit component(std::string tg, std::string _id = std::to_string(rand()))
        : id{std::move(_id)}, tag{std::move(tg)} {}

    virtual ~component() = default;

    component_dto to_dto () const
    {
        // HTML attributes
        std::vector<kv> attributes_dto{};
        for (const auto &[key, value] : attributes)
        {
            attributes_dto.emplace_back(key, value);
        }

        // ohdeer properties
        std::vector<kv> properties_dto{};
        for (const auto &[key, value] : properties)
        {
            properties_dto.emplace_back(key, value);
        }

        std::vector<std::string> events{};
        if (!listeners.empty())
        {
            for (const auto &[event_name, _] : listeners)
            {
                events.emplace_back(event_name);
            }
        }

        std::vector<component_dto> children_dto{};
        if (!children.empty())
        {
            for (auto &child : children)
            {
                children_dto.emplace_back(child->to_dto());
            }
        }

        return component_dto{.id = id, .tag = tag, .attributes = attributes_dto, .properties = properties_dto, .children = children_dto, .events = events};
    }

    std::string toJson() const
    {
        return json_magic::to_string(to_dto());
    }

    void addListener(const std::string &eventType, std::function<void(const std::string &)> callback)
    {
        listeners[eventType] = callback;
    }

    void dispatch_event(const event_request &req)
    {
        if (this->id == req.target)
        {
            triggerEvent(req);
        }
        else if (!this->children.empty())
        {
            for (auto &&child : this->children)
            {
                child->dispatch_event(req);
            }
        }
    }

    void triggerEvent(const event_request &req)
    {
        if (listeners.count(req.event))
        {
            listeners[req.event](req.payload);
        }
    }
};

#endif