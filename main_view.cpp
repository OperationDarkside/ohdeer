#include <iostream>

#include "button.cpp"
#include "label.cpp"

struct main_view : public component
{
    int counter{};
    std::shared_ptr<button> btn = std::make_shared<button>();
    std::shared_ptr<label> lbl = std::make_shared<label>();

    main_view() : component{"div"}
    {
        children.push_back(btn);
        children.push_back(lbl);

        btn->addListener("click", [this](const std::string& input){
            lbl->text = std::to_string(counter++);
        });
    }

    virtual std::string toJson() const override
    {
        bool is_first = true;
        std::string result{};
        result += "{\"id\":\"";
        result += id;
        result += "\",\"tag\":\"";
        result += tag;
        result += "\",\"children\":[";
        for(const auto& sub_c : children) {
            if(is_first) {
                is_first = false;
            } else {
                result += ",";
            }
            result += sub_c->toJson();
        }
        result += "]}";

        return result;
    }
};