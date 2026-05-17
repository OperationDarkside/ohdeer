#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include "boing/webserver.cpp"
#include "boing/annotations.cpp"

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
            ctx.json(ctx.session_->view.toJson());
        }

        [[= POST("ui/event")]] static void ui_event(context<ohdeer_session> &ctx)
        {
            
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
