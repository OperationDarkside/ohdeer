#include <iostream>

#include "button.cpp"
#include "label.cpp"

struct main_view : public component {
    int counter{};
    std::shared_ptr<button> btn = std::make_shared<button>();
    std::shared_ptr<label> lbl = std::make_shared<label>();

    main_view() : component{"div"} {
        children.push_back(btn);
        children.push_back(lbl);

        btn->set_text("Click me");
        btn->addListener("click", [&](const std::string& input){
            lbl->setText(std::to_string(counter++));
        });
    }
};