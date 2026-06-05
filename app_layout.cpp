#ifndef OHDEER_APP_LAYOUT
#define OHDEER_APP_LAYOUT

#include "component.cpp"
// #include "grid_layout_item.cpp"

struct app_layout : public component
{
    protected:
        std::shared_ptr<component> burger = std::make_shared<component>("div");
        std::shared_ptr<component> headline = std::make_shared<component>("div");
        std::shared_ptr<component> settings = std::make_shared<component>("div");
        std::shared_ptr<component> menu = std::make_shared<component>("div");
        std::shared_ptr<component> content = std::make_shared<component>("div");

    public:

    app_layout() : component{"div"}
    {
        this->attributes["class"] = "app-layout";

        burger->attributes["class"] = "burger";
        headline->attributes["class"] = "headline";
        settings->attributes["class"] = "settings";
        menu->attributes["class"] = "menu";
        content->attributes["class"] = "app-content";

        burger->properties["textContent"] = "≡";
        headline->properties["textContent"] = "My First App";
        settings->properties["textContent"] = "⚙";

        this->children.push_back(burger);
        this->children.push_back(headline);
        this->children.push_back(settings);
        this->children.push_back(menu);
        this->children.push_back(content);
    }

    /*
    void add_component(int column, int row, const std::shared_ptr<component> &child)
    {
        auto item_wrapper = std::make_shared<grid_layout_item>(column, row);
        item_wrapper->add_component(child);
        this->children.push_back(item_wrapper);
    }
    */
    void set_content(const std::shared_ptr<component> &child)
    {
        content->children.clear();
        content->children.push_back(child);
    }
};

#endif