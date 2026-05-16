#include <iostream>

#include "boing/webserver.cpp"
#include "boing/annotations.cpp"
#include "boing/simple_session.cpp"

namespace endpoints
{
    using namespace boing;

    struct[[= controller("/")]] root
    {
        [[= GET("")]] static void greeting(context<simple_session> &ctx)
        {
            ctx.html("<h2>Welcome to Boing</h2><p>Try our <a href=\"/stats\">/stats</a> page</p>");
        }

        int visit_count = 0;

        [[= GET("stats")]] void stats(context<simple_session> &ctx)
        {
            std::string msg = "<p>You have visited this site " +
                              std::to_string(visit_count++) + " times!</p>";
            ctx.html(msg);
        }
    };

}

int main(int, char**){
    std::cout << "Hello, from ohdeer!\n";

    boing::webserver<^^endpoints, simple_session> server{};
    server.start();
}
