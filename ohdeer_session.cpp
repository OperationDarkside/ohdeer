#include <string>
#include <chrono>

#include "main_view.cpp"

struct ohdeer_session {
    // Identity
    std::string session_id{};
    int user_id{};

    // State
    bool is_authenticated{};

    // Lifecycle
    std::chrono::steady_clock::time_point last_active{};

    main_view view{};
};