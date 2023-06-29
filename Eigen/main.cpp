#include <fmt/format.h>
#include <fmt/color.h>
#include <string_view>
#include <cstdlib>
#include <array>
#include <Eigen/Dense>
#include <strstream>
auto main() -> int
{
    // a couple of lambdas to make printing easier
    auto to_string = [](const auto &_text)
    {
        std::strstream ss;
        ss << _text;
        return std::string_view{ss.str()};
    };
    auto print_blue = [](const std::string_view _text)
    {
        fmt::print(fg(fmt::color::blue) | fmt::emphasis::bold, "{}", _text);
    };
    auto print_yellow = [](const std::string_view _text)
    {
        fmt::print(fg(fmt::color::yellow), "{}", _text);
    };

    print_blue("This demo shows how to use Eigen library");
    print_blue("Some vector maths \n");
    Eigen::Vector4f a(1, 2, 3, 4);
    Eigen::Vector4f b(5, 6, 7, 8);
    auto c = a + b;
    // Note that we need to convert to string before printing as
    print_yellow(fmt::format("Eigen::Vector4f c=a+b: \n{}\n", to_string(c)));
    print_blue("Some matrix maths \n");
    Eigen::Matrix4f m;
    m << 1.0f, 2.9f, 3.5f, 4.0f,
        5.0f, 6.0f, 7.2f, 8.0f,
        9.0f, 10.0f, 11.1f, 12.3f,
        13.0f, 14.0f, 15.0f, 16.2f;
    print_yellow(fmt::format("Eigen::Matrix4f m: \n{}\n", to_string(m)));
    print_yellow(fmt::format("Eigen::Matrix4f m.transpose(): \n{}\n", to_string(m.transpose())));
    print_yellow(fmt::format("Eigen::Matrix4f m.sum(): \n{}\n", to_string(m.sum())));
    print_yellow(fmt::format("Eigen::Matrix4f m.trace(): \n{}\n", to_string(m.trace())));
    print_yellow(fmt::format("Eigen::Matrix4f m.row(1): \n{}\n", to_string(m.row(1))));
    print_yellow(fmt::format("Eigen::Matrix4f m.col(1): \n{}\n", to_string(m.col(1))));
    print_yellow(fmt::format("Eigen::Matrix4f m.diagonal(): \n{}\n", to_string(m.diagonal())));
    print_yellow(fmt::format("Eigen::Matrix4f m.inverse(): \n{}\n", to_string(m.inverse())));

    print_blue("Some matrix multiplication \n");
    Eigen::Matrix4f m1;
    m1 << 1.0f, 2.9f, 3.5f, 4.0f,
        5.0f, 6.0f, 7.2f, 8.0f,
        9.0f, 10.0f, 11.1f, 12.3f,
        13.0f, 14.0f, 15.0f, 16.2f;
    Eigen::Matrix4f m2;
    m2 << 1.0f, 2.9f, 3.5f, 4.0f,
        5.0f, 6.0f, 7.2f, 8.0f,
        9.0f, 10.0f, 11.1f, 12.3f,
        13.0f, 14.0f, 15.0f, 16.2f;
    print_yellow(fmt::format("Eigen::Matrix4f m1*m2: \n{}\n", to_string(m1 * m2)));
    return EXIT_SUCCESS;
}
