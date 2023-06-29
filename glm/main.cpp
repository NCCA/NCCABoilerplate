#include <fmt/format.h>
#include <fmt/color.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string_view>
#include <cstdlib>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>
auto main() -> int
{
    // a couple of lambdas to make printing easier
    auto print_blue = [](const std::string_view _text)
    {
        fmt::print(fg(fmt::color::blue) | fmt::emphasis::bold, "{}", _text);
    };
    auto print_yellow = [](const std::string_view _text)
    {
        fmt::print(fg(fmt::color::yellow), "{}", _text);
    };

    print_blue("This demo shows how to use glm library");
    print_blue("Some matrix maths \n");

    print_blue("translation matrix \n");
    auto point = glm::vec4(1.0f, 2.0f, 3.0f, 1.0f);
    auto matrix = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              2.0f, 3.0f, 4.0f, 1.0f);
    auto result = matrix * point;
    fmt::print(fg(fmt::color::yellow) | fmt::emphasis::bold, fmt::format("{} * {} = {}\n\n", glm::to_string(point), glm::to_string(matrix), glm::to_string(result)));
    result = point * matrix;
    print_blue("Note the non commutative nature of matrix multiplication\n");
    print_yellow(fmt::format("Point {} * Matrix {} = {}\n\n", glm::to_string(point), glm::to_string(matrix), glm::to_string(result)));

    print_blue("Now lets use the glm::translate function\n");
    matrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 3.0f, 4.0f));
    result = matrix * point;
    print_yellow(fmt::format("Point {} * Matrix {} = {}\n\n", glm::to_string(point), glm::to_string(matrix), glm::to_string(result)));

    print_blue("Now lets use the glm::rotate function\n");
    matrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
    result = matrix * point;
    print_yellow(fmt::format("Point {} * Matrix {} = {}\n\n", glm::to_string(point), glm::to_string(matrix), glm::to_string(result)));

    print_blue("The glm::lookAt function\n");
    auto eye = glm::vec3(2.0f, 2.0f, 2.0f);
    auto center = glm::vec3(0.0f, 0.0f, 0.0f);
    auto up = glm::vec3(0.0f, 1.0f, 0.0f);
    auto look = glm::lookAt(eye, center, up);
    print_yellow(fmt::format("Matrix {} \n\n", glm::to_string(matrix)));

    print_blue("The glm::perspective function\n");
    auto fov = glm::radians(45.0f);
    auto aspect = 4.0f / 3.0f;
    auto near = 0.1f;
    auto far = 100.0f;
    auto perspective = glm::perspective(fov, aspect, near, far);
    print_yellow(fmt::format("Matrix {} \n\n", glm::to_string(perspective)));

    print_blue("Typically we construct an Model, View , Project matrix\n");
    print_blue("To transform all the vertices \n");
    auto mvp = perspective * look * matrix;
    print_yellow(fmt::format("Matrix {} \n\n", glm::to_string(mvp)));

    std::array<glm::vec4, 4> vertices = {
        glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, -1.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f)};
    print_blue("Vertices \n");
    for (auto &vertex : vertices)
    {
        print_yellow(fmt::format("{}\n", glm::to_string(vertex)));
    }
    print_blue("Transformed Vertices \n");
    for (auto &vertex : vertices)
    {
        auto transformed = mvp * vertex;
        print_yellow(fmt::format("{}\n", glm::to_string(transformed)));
    }
    return EXIT_SUCCESS;
}
