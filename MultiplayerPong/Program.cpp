#include "Program.h"

using namespace RGL;

int Program::Main(const std::vector<std::string> &args)
{
    std::shared_ptr<WindowManager> _window(new WindowManager());

    _window->Initialize(GAME_NAME, SCREEN_WIDTH, SCREEN_WIDTH);

    _window->Finish();

    return 0;
}

int main(int argc, char** argv)
{
    std::vector<std::string> args(argv, argv + argc);

    Program prog;
    return prog.Main(args);
}
