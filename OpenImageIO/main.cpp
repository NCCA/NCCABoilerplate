#include <iostream>
// #include <gtest/gtest.h>
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <algorithm>
#include <memory>
#include <string>
#include <array>
#include <OpenImageIO/imageio.h>

void generateImages();
void removeFiles();
constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;

int main(int argc, char *argv[])
{
  // global setup...
  generateImages();

  int result = Catch::Session().run(argc, argv);

  // global clean-up...
  if (argc <= 1)
    removeFiles();

  return (result < 0xff ? result : 0xff);
}

void loadImage(const std::string &_fname)
{
  using namespace OIIO;
  std::unique_ptr<ImageInput> in(ImageInput::create(_fname));
  ImageSpec spec;
  in->open(_fname, spec);
  std::unique_ptr<unsigned char[]> pixels = std::make_unique<unsigned char[]>(spec.width * spec.height * spec.nchannels);
  REQUIRE(spec.width == WIDTH);
  REQUIRE(spec.height == HEIGHT);
  REQUIRE(spec.nchannels == 3);

  in->read_image(0,0,0,-1,TypeDesc::UINT8, pixels.get());
  if (_fname != "test.jpg")
  {
    // test pixels to be honest this is a bit crap but hey
    // use 25 for jpg compression
    REQUIRE(pixels[0] == Catch::Approx(255).margin(25));
    REQUIRE(pixels[1] == Catch::Approx(255).margin(25));
    REQUIRE(pixels[2] == Catch::Approx(255).margin(25));

    size_t index = (2 * WIDTH * 3) + 2 * 3;
    // red
    REQUIRE(pixels[index] == Catch::Approx(255).margin(25));
    REQUIRE(pixels[index + 1] == Catch::Approx(0).margin(25));
    REQUIRE(pixels[index + 2] == Catch::Approx(0).margin(25));
  }

  in->close();
}

TEST_CASE("OIIO Test tga", "[tga]")
{
  loadImage("test.tga");
}

TEST_CASE("OIIO Test bmp", "bmp")
{
  loadImage("test.bmp");
}

TEST_CASE("OIIO Test pbm", "pbm")
{
  loadImage("test.pbm");
}

TEST_CASE("OIIO Test pgm", "pgm")
{
  loadImage("test.pgm");
}

TEST_CASE("OIIO Test ppm", "ppm")
{
  loadImage("test.ppm");
}

TEST_CASE("OIIO Test jpg", "jpg")
{
  loadImage("test.jpg");
}

TEST_CASE("OIIO Test tiff", "tiff")
{
  loadImage("test.tiff");
}

TEST_CASE("OIIO Test png", "png")
{
  loadImage("test.png");
}

TEST_CASE("OIIO Test exr", "exr")
{
  loadImage("test.exr");
}

TEST_CASE("OIIO Test z", "z")
{
  loadImage("test.z");
}
constexpr std::array<const char *, 10> gExtensions = {
    {"tga", "bmp", "pbm", "pgm", "ppm", "jpg", "tiff", "png", "exr", "z"}};

void generateImages()
{
  constexpr auto imageSize = WIDTH * HEIGHT * 3 * sizeof(unsigned char);
  std::unique_ptr<unsigned char[]> image = std::make_unique<unsigned char[]>(imageSize);
  // set background colour
  std::fill(image.get(), image.get() + imageSize, 255);

  // set pixel as lambda
  auto setPixel = [&image](size_t _x, size_t _y, unsigned char _r, unsigned char _g, unsigned char _b)
  {
    size_t index = (_y * WIDTH * 3) + _x * 3;
    image.get()[index] = _r;
    image.get()[index + 1] = _g;
    image.get()[index + 2] = _b;
  };

  for (size_t y = 0; y < HEIGHT; ++y)
  {
    for (size_t x = 0; x < WIDTH; ++x)
    {
      if ((y % 20) && (x % 20))
      {
        setPixel(x, y, 255, 0, 0);
      }
      else
      {
        setPixel(x, y, 255, 255, 255);
      }
    }
  }

  using namespace OIIO;

  for (auto ext : gExtensions)
  {
    std::string fname("test.");
    fname += ext;
    const int channels = 3; // RGB
    std::unique_ptr<ImageOutput> out = ImageOutput::create(fname);
    ImageSpec spec(WIDTH, HEIGHT, channels, TypeDesc::UINT8);
    // std::cout<<fname<<'\n';
    out->open(fname, spec);
    out->write_image(TypeDesc::UINT8, &image[0]);
    out->close();
    // delete out;
  }
}

void removeFiles()
{
  for (auto ext : gExtensions)
  {
    std::string fname("test.");
    fname += ext;
    //    std::remove(fname.c_str());
  }
}
