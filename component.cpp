#ifndef OHDEER_COMPONENT
#define OHDEER_COMPONENT

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>
#include <sstream>

#include "event.cpp"

class component
{
protected:
    std::map<std::string, std::string> properties{};
    std::vector<std::shared_ptr<component>> children{};
    std::map<std::string, std::function<void(const std::string &)>> listeners{};

public:
    std::string id{};
    std::string tag{};

    explicit component(std::string tg, std::string _id = std::to_string(rand()))
        : id{std::move(_id)}, tag{std::move(tg)} {}

    virtual ~component() = default;

    // Base implementation handles EVERYTHING automatically
    std::string toJson() const
    {
        std::ostringstream ss;
        ss << "{";
        ss << "\"id\":\"" << id << "\",";
        ss << "\"tag\":\"" << tag << "\"";

        // 1. Serialize all generic properties
        for (const auto &[key, value] : properties)
        {
            ss << ",\"" << key << "\":\"" << value << "\"";
        }

        // 2. Serialize events if listeners exist
        if (!listeners.empty())
        {
            ss << ",\"events\":[";
            bool first_event = true;
            for (const auto &[event_name, _] : listeners)
            {
                if (!first_event)
                    ss << ",";
                ss << "\"" << event_name << "\"";
                first_event = false;
            }
            ss << "]";
        }

        // 3. Serialize children recursively
        if (!children.empty())
        {
            ss << ",\"children\":[";
            for (size_t i = 0; i < children.size(); ++i)
            {
                if (i > 0)
                    ss << ",";
                ss << children[i]->toJson();
            }
            ss << "]";
        }

        ss << "}";
        return ss.str();
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