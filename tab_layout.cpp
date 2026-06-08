#ifndef OHDEER_TAB_LAYOUT
#define OHDEER_TAB_LAYOUT

#include "component.cpp"
// 1. Plain Data Structure for State Keeping
struct tab_instance
{
    std::string id{};
    std::string title{};
    std::string type{};
    std::shared_ptr<component> root_node{};
};

// 2. Pure Visual Viewport Container
class tab_container : public component
{
public:
    tab_container() : component("div")
    {
        this->attributes["class"] = "tab-container";
    }

    void mount_view(std::shared_ptr<component> view)
    {
        this->children.clear();
        if (view)
        {
            this->children.push_back(view);
        }
    }
};

// 3. Pure Visual Tab Bar
class tab_bar : public component
{
public:
    tab_bar() : component("div")
    {
        this->attributes["class"] = "tab-bar";
    }
};

// 4. The Hierarchical Orchestrator
class tab_layout : public component
{
private:
    std::shared_ptr<tab_bar> bar = std::make_shared<tab_bar>();
    std::shared_ptr<tab_container> container = std::make_shared<tab_container>();

    std::vector<tab_instance> open_tabs{};
    std::string active_tab_id{};
    std::map<std::string, std::function<std::shared_ptr<component>()>> factories{};

    void sync_ui()
    {
        // Clear old headers out of the tab bar
        bar->children.clear();

        std::shared_ptr<component> active_view = nullptr;

        for (const auto &tab : open_tabs)
        {
            // Build the tab bar item component dynamically
            auto item = std::make_shared<component>("div");
            //item->id = "btn_" + tab.id;
            item->properties["textContent"] = tab.title;
            item->attributes["class"] = (tab.id == active_tab_id) ? "tab-bar-item active" : "tab-bar-item";

            // Bind click event to trigger activation via this layout manager
            std::string tid = tab.id;
            item->addListener("click", [this, tid](const std::string &) {
                this->switch_to_tab(tid);
            });

            bar->children.push_back(item);

            // Locate active child instance to mount
            if (tab.id == active_tab_id)
            {
                active_view = tab.root_node;
            }
        }

        // Send the correct active view down to the content viewport container
        container->mount_view(active_view);
    }

public:
    tab_layout() : component("div")
    {
        this->attributes["class"] = "tab-layout";
        
        // Assemble sub-components into the rendering hierarchy
        this->children.push_back(bar);
        this->children.push_back(container);
    }

    void register_factory(const std::string &type, std::function<std::shared_ptr<component>()> factory)
    {
        factories[type] = factory;
    }

    void open_new_tab(const std::string &type, const std::string &title)
    {
        if (!factories.count(type)) return;

        std::string new_id = type + "_" + std::to_string(rand());

        tab_instance new_tab{
            .id = new_id,
            .title = title,
            .type = type,
            .root_node = factories[type]() 
        };

        open_tabs.push_back(new_tab);
        active_tab_id = new_id;
        sync_ui();
    }

    void switch_to_tab(const std::string &tab_id)
    {
        active_tab_id = tab_id;
        sync_ui();
    }

    void close_tab(const std::string &tab_id)
    {
        open_tabs.erase(
            std::remove_if(open_tabs.begin(), open_tabs.end(),
                           [&](const tab_instance &t) { return t.id == tab_id; }),
            open_tabs.end()
        );

        if (active_tab_id == tab_id && !open_tabs.empty())
        {
            active_tab_id = open_tabs.back().id;
        }
        else if (open_tabs.empty())
        {
            active_tab_id = "";
        }
        sync_ui();
    }
};

#endif