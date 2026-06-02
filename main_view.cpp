#include <iostream>

#include "button.cpp"
#include "label.cpp"
#include "vertical_layout.cpp"
#include "grid_layout.cpp"

struct main_view : public component {
    int counter{};
    std::shared_ptr<button> btn = std::make_shared<button>();
    std::shared_ptr<label> lbl = std::make_shared<label>();
    std::shared_ptr<label> lbl1 = std::make_shared<label>();
    std::shared_ptr<label> lbl2 = std::make_shared<label>();
    std::shared_ptr<vertical_layout> vl = std::make_shared<vertical_layout>();

    std::shared_ptr<grid_layout> gl = std::make_shared<grid_layout>();
    std::shared_ptr<label> lbl3 = std::make_shared<label>();
    std::shared_ptr<label> lbl4 = std::make_shared<label>();
    std::shared_ptr<label> lbl5 = std::make_shared<label>();
    std::shared_ptr<label> lbl6 = std::make_shared<label>();


    main_view() : component{"div"} {
        children.push_back(btn);
        children.push_back(lbl);

        btn->set_text("Click me");
        btn->addListener("click", [&](const std::string& input){
            lbl->setText(std::to_string(counter++));
        });

        // VERTICAL LAYOUT
        lbl1->setText("Text1");
        lbl2->setText("Text2");
        vl->add_component(lbl1);
        vl->add_component(lbl2);
        children.push_back(vl);

        // GRID LAYOUT
        lbl3->setText("Text3");
        lbl4->setText("Text4");
        lbl5->setText("Text5");
        lbl6->setText("Text6");
        gl->add_component(1, 1, lbl3);
        gl->add_component(2, 1, lbl4);
        gl->add_component(1, 2, lbl5);
        gl->add_component(2, 3, lbl6);
        children.push_back(gl);
    }
};