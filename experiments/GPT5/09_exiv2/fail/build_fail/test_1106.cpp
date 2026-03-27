// TEST_ID 1106
// File: test_imagefactory_open_path_1106.cpp

#include <gtest/gtest.h>

#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <random>
#include <string>
#include <vector>

namespace {

class ImageFactoryOpenPathTest_1106 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (const auto& p : created_files_) {
      std::error_code ec;
      std::filesystem::remove(p, ec);
    }
    created_files_.clear();
  }

  std::filesystem::path MakeTempPath(const std::string& suffix) {
    const auto base = std::filesystem::temp_directory_path();

    // Create a reasonably-unique filename without relying on platform-specific APIs.
    std::random_device rd;
    std::mt19937_64 gen(rd());
    const auto r = static_cast<unsigned long long>(gen());

    std::filesystem::path p = base / ("exiv2_imagefactory_open_1106_" + std::to_string(r) + suffix);
    created_files_.push_back(p);
    return p;
  }

  std::filesystem::path WriteBinaryFile(const std::string& suffix, const std::vector<unsigned char>& bytes) {
    auto p = MakeTempPath(suffix);
    std::ofstream ofs(p, std::ios::binary);
    EXPECT_TRUE(ofs.good());
    ofs.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    ofs.close();
    EXPECT_TRUE(std::filesystem::exists(p));
    return p;
  }

  std::filesystem::path WriteEmptyFile(const std::string& suffix) {
    auto p = MakeTempPath(suffix);
    std::ofstream ofs(p, std::ios::binary);
    EXPECT_TRUE(ofs.good());
    ofs.close();
    EXPECT_TRUE(std::filesystem::exists(p));
    return p;
  }

 private:
  std::vector<std::filesystem::path> created_files_;
};

// A tiny valid 1x1 RGBA PNG (commonly used minimal PNG test fixture).
static const std::vector<unsigned char> kPng1x1_1106 = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
    0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0x15, 0xC4, 0x89,
    0x00, 0x00, 0x00, 0x0A, 0x49, 0x44, 0x41, 0x54,
    0x78, 0x9C, 0x63, 0x00, 0x01, 0x00, 0x00, 0x05,
    0x00, 0x01, 0x0D, 0x0A, 0x2D, 0xB4,
    0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44,
    0xAE, 0x42, 0x60, 0x82,
};

TEST_F(ImageFactoryOpenPathTest_1106, OpenValidPngPathReturnsNonNullImage_1106) {
  const auto path = WriteBinaryFile(".png", kPng1x1_1106).string();

  Exiv2::ImageFactory factory;
  EXPECT_NO_THROW({
    auto img = factory.open(path, /*useCurl=*/false);
    ASSERT_NE(img.get(), nullptr);
  });
}

TEST_F(ImageFactoryOpenPathTest_1106, OpenUnknownFileTypeThrowsFileContainsUnknownImageType_1106) {
  // Random bytes that should not be recognized as a supported image format.
  const std::vector<unsigned char> bytes = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0xAA, 0xBB, 0xCC, 0xDD};
  const auto path = WriteBinaryFile(".bin", bytes).string();

  Exiv2::ImageFactory factory;
  try {
    (void)factory.open(path, /*useCurl=*/false);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Observable behavior from the provided implementation: throws this code when open(io) returns null.
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFileContainsUnknownImageType);
    // The constructor is passed `path`; error text should typically include it (if exposed by Exiv2).
    const std::string what = e.what() ? std::string(e.what()) : std::string();
    EXPECT_NE(what.find(path), std::string::npos);
  }
}

TEST_F(ImageFactoryOpenPathTest_1106, OpenNonExistentPathPropagatesError_1106) {
  const auto path = (MakeTempPath(".does_not_exist").string());
  // Ensure it really doesn't exist (TearDown will attempt removal anyway).
  std::error_code ec;
  std::filesystem::remove(path, ec);

  Exiv2::ImageFactory factory;
  EXPECT_THROW((void)factory.open(path, /*useCurl=*/false), Exiv2::Error);
}

TEST_F(ImageFactoryOpenPathTest_1106, OpenEmptyFileThrowsError_1106) {
  const auto path = WriteEmptyFile(".empty").string();

  Exiv2::ImageFactory factory;
  EXPECT_THROW((void)factory.open(path, /*useCurl=*/false), Exiv2::Error);
}

}  // namespace