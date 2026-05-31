#include "component.cpp"

struct label : public component {
    label() : component{"label"} {}

    // Use a setter to keep the internal properties map synchronized
    void setText(const std::string& new_text) {
        properties["textContent"] = new_text;
    }
    
    std::string getText() const {
        auto it = properties.find("textContent");
        return (it != properties.end()) ? it->second : "";
    }
};