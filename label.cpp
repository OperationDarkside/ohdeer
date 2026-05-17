#include "component.cpp"

struct label : public component
{
    std::string text{};

    label() : component{"label"}
    {
        
    }

    virtual std::string toJson() const override
    {
        std::string result{};
        result += "{\"id\":\"";
        result += id;
        result += "\",\"tag\":\"";
        result += tag;
        result += "\",\"text\":\"";
        result += text;
        result += "\"}";

        return result;
    }

};