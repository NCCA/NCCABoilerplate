#include <iostream>
#include <cstdlib>
#include <cxxopts.hpp>
int main(int argc, char **argv)
{
  cxxopts::Options options("Demo", "Demo of cxxopts");
  options.allow_unrecognised_options();

  options.add_options()
  ("w,width", "Int example", cxxopts::value<int>()->default_value("50"))
  ("r,radius", "float example", cxxopts::value<float>()->default_value("1.0"))
  ("f,file", "string example", cxxopts::value<std::string>()->default_value("Filename"))
  ("filenames", "The filename(s) to process", cxxopts::value<std::vector<std::string>>())
  ("h,help", "Print usage");
  options.parse_positional({"filenames"});

  auto result = options.parse(argc, argv);
  auto width = result["width"].as<int>();
  auto r = result["radius"].as<float>();
  auto f = result["file"].as<std::string>();
  for(auto& filename : result["filenames"].as<std::vector<std::string>>())
  {
    std::cout << filename << '\n';
  }
  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout<<width<<' '<<r<<' '<<f<<'\n';
  for (auto unmached : result.unmatched()
  )
  {
    std::cout << "Unmatched argument: " << unmached << '\n';
  }
}