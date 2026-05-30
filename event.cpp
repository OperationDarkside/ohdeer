#ifndef OHDEER_EVENT
#define OHDEER_EVENT

#include <string>

struct event_request {
    std::string event;
    std::string target;
    std::string payload;
};

#endif