#ifndef OHDEER_APP_LAYOUT
#define OHDEER_APP_LAYOUT

#include "tab_layout.cpp"
// #include "grid_layout_item.cpp"

struct app_layout : public component
{
protected:
    std::shared_ptr<component> burger = std::make_shared<component>("div");
    std::shared_ptr<component> headline = std::make_shared<component>("div");
    std::shared_ptr<component> settings = std::make_shared<component>("div");
    std::shared_ptr<component> menu = std::make_shared<component>("div");
    std::shared_ptr<tab_layout> m_tab_layout = std::make_shared<tab_layout>();

public:
    app_layout() : component{"div"}
    {
        this->attributes["class"] = "app-layout";

        burger->attributes["class"] = "burger";
        headline->attributes["class"] = "headline";
        settings->attributes["class"] = "settings";
        menu->attributes["class"] = "menu";

        burger->properties["textContent"] = "≡";
        settings->properties["textContent"] = "⚙";

        this->children.push_back(burger);
        this->children.push_back(headline);
        this->children.push_back(settings);
        this->children.push_back(menu);
        this->children.push_back(m_tab_layout);
    }

    /*
    void add_component(int column, int row, const std::shared_ptr<component> &child)
    {
        auto item_wrapper = std::make_shared<grid_layout_item>(column, row);
        item_wrapper->add_component(child);
        this->children.push_back(item_wrapper);
    }
    */

    void add_menu_item(const std::string &title, const std::string &type, std::function<std::shared_ptr<component>()> factory)
    {
        // add item to menu
        std::shared_ptr<component> menu_item = std::make_shared<component>("div");
        menu_item->attributes["class"] = "menu_item";
        menu_item->addListener("click", [this, type, title](const std::string &)
                               { this->m_tab_layout->open_new_tab(type, title); });
        menu_item->properties["textContent"] = title;
        menu->children.push_back(menu_item);

        m_tab_layout->register_factory(type, factory);
    }

    void set_headline(const std::string_view hl)
    {
        headline->properties["textContent"] = hl;
    }
};

#endif