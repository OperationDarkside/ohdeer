#ifndef OHDEER_COMPONENT
#define OHDEER_COMPONENT

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>

class component
{
protected:
    std::map<std::string, std::string> properties{};
    std::vector<std::shared_ptr<component>> children{};

    // Event listeners mapped by event name (e.g., "click" -> handler)
    std::map<std::string, std::function<void(const std::string &)>> listeners{};

public:
    std::string id{};  // Unique identifier for DOM matching
    std::string tag{}; // e.g., "div", "button", "input"

    explicit component(std::string tg, std::string _id = std::to_string(rand()))
        : id{std::move(_id)}, tag{std::move(tg)}
    {
    }

    virtual ~component() = default;

    // Serializes the component and its children to send to the JS client
    virtual std::string toJson() const = 0;

    void addListener(const std::string &eventType, std::function<void(const std::string &)> callback)
    {
        listeners[eventType] = callback;
    }

    void triggerEvent(const std::string &eventType, const std::string &payload)
    {
        if (listeners.count(eventType))
        {
            listeners[eventType](payload);
        }
    }
};

#endif