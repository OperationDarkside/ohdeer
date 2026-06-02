#ifndef OHDEER_GRID_LAYOUT
#define OHDEER_GRID_LAYOUT

#include "grid_layout_item.cpp"

struct grid_layout : public component
{
    grid_layout() : component{"div"}
    {
        this->attributes["class"] = "grid_layout";
    }

    void add_component(int column, int row, const std::shared_ptr<component> &child)
    {
        auto item_wrapper = std::make_shared<grid_layout_item>(column, row);
        item_wrapper->add_component(child);
        this->children.push_back(item_wrapper);
    }
};

#endif