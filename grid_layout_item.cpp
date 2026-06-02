#ifndef OHDEER_GRID_LAYOUT_ITEM
#define OHDEER_GRID_LAYOUT_ITEM

#include "component.cpp"

struct grid_layout_item : public component
{
    int m_column{};
    int m_row{};

    grid_layout_item(int column, int row) : component{"div"}, m_column(column), m_row(row)
    {
        std::string style{"grid-column: "};
        style += std::to_string(m_column);
        style += "; grid-row: ";
        style += std::to_string(m_row);
        style += ";";
        this->attributes["style"] = style;
    }

    void add_component(const std::shared_ptr<component> &child)
    {
        this->children.push_back(child);
    }
};

#endif