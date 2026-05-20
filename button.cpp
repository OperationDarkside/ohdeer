#include "component.cpp"

struct button : public component {
    button() : component{"button"} {
        // The click event is automatically detected by the base class 
        // if you use addListener() on it!
    }
};