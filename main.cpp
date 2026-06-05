#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include "boing/webserver.cpp"
#include "boing/annotations.cpp"

//#include "boing/extern/CppJsonMagic/json_magic.cpp"

#include "ohdeer_session.cpp"

namespace endpoints
{
    using namespace boing;

    struct[[= controller("/")]] root
    {
        [[= GET("")]] static void start(context<ohdeer_session> &ctx)
        {
            std::cout << std::filesystem::current_path() << std::endl;
            std::filesystem::path index_path = std::filesystem::current_path() / "main/index.html";
            
            if (std::filesystem::exists(index_path))
            {
                std::ifstream input_file{index_path};
                if (input_file.is_open())
                {
                    std::string file_contents{std::istreambuf_iterator<char>{input_file}, std::istreambuf_iterator<char>{}};
                    //input_file >> file_contents;
                    ctx.html(file_contents);
                }
                else
                {
                    ctx.html("index.html exists, but could not be opened");
                }
            }
            else
            {
                ctx.html("index.html doesn't exist");
            }
        }

        [[= GET("ui/init")]] static void ui_init(context<ohdeer_session> &ctx)
        {
            ctx.json(ctx.session_->view->get_app()->toJson());
        }

        [[= POST("ui/event")]] static void ui_event(context<ohdeer_session> &ctx)
        {
            //std::cout << ctx.req << std::endl;
            event_request e = json_magic::from_string<event_request>(ctx.req.body());
            std::cout << "event: " << e.event << std::endl;
            std::cout << "target: " << e.target << std::endl;
            std::cout << "payload: " << e.payload << std::endl;

            ctx.session_->view->get_app()->dispatch_event(e);

            ctx.json(ctx.session_->view->get_app()->toJson());
        }

        int visit_count = 0;

        [[= GET("stats")]] void stats(context<ohdeer_session> &ctx)
        {
            std::string msg = "<p>You have visited this site " +
                              std::to_string(visit_count++) + " times!</p>";
            ctx.html(msg);
        }
    };

}

int main(int, char **)
{
    std::cout << "Hello, from ohdeer!\n" << std::endl;

    boing::webserver<^^endpoints, ohdeer_session> server{};
    server.start();
}
