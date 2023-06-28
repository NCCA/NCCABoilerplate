#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <cstdlib>

auto main() -> int
{
    std::cout << "This demo shows how to use fmt library\n";
    std::cout << fmt::format("Hello, {}! \n", "world");
    int a = 1;
    float b = 2.0f;
    double c = 4.2324324324;
    std::cout << fmt::format("a = {}, b = {}, c = {}\n", a, b, c);

    for (int i = 0; i < 10; ++i)
    {
        auto filename = fmt::format("beauty.{:04}.exr", i);
        std::cout << filename << '\n';
    }

    using namespace std::literals::chrono_literals;
    fmt::print("Default format: {} {}\n", 42s, 100ms);
    fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);

    // containers work too
    std::vector<int> v = {1, 2, 99, 22, 34};
    fmt::print("{}\n", v);
    // colour and unicode
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
               "Hello, {}!\n", "world");
    fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
                   fmt::emphasis::underline,
               "Hello, {}!\n", "мир");
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
               "Hello, {}!\n", "世界");
    return EXIT_SUCCESS;
}
