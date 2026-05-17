#include "component.cpp"

struct button : public component
{
    button() : component{"button"}
    {
    }

    virtual std::string toJson() const override
    {
        std::string result{};
        result += "{\"id\":\"";
        result += id;
        result += "\",\"tag\":\"";
        result += tag;
        result += "\",\"event\":\"click\"}";

        return result;
    }

};