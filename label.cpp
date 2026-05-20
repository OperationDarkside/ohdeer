#include "component.cpp"

struct label : public component {
    label() : component{"label"} {}

    // Use a setter to keep the internal properties map synchronized
    void setText(const std::string& new_text) {
        properties["text"] = new_text;
    }
    
    std::string getText() const {
        auto it = properties.find("text");
        return (it != properties.end()) ? it->second : "";
    }
};