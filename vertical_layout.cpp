#ifndef OHDEER_VERTICAL_LAYOUT
#define OHDEER_VERTICAL_LAYOUT

#include "component.cpp"

struct vertical_layout : public component
{
    vertical_layout() : component{"div"}
    {
        this->attributes["class"] = "vertical_layout";
    }

    void add_component(const std::shared_ptr<component>& child) {
        this->children.push_back(child);
    }
};

#endif