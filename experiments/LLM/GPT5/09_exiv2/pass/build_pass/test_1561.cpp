// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_asfvideo_mimetype_1561.cpp

#include <gtest/gtest.h>

#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>

namespace {

class AsfVideoTest_1561 : public ::testing::Test {
 protected:
  static std::string makeTempFilePath_() {
    // Simple, portable-enough temp file strategy for unit tests.
    // (We intentionally avoid relying on internal Exiv2 helpers.)
    const std::string base = "asfvideo_mimetype_1561_tmp.asf";
    // Ensure old file doesn't interfere.
    std::remove(base.c_str());
    // Create an empty file.
    std::ofstream ofs(base, std::ios::binary);
    ofs.close();
    return base;
  }

  static Exiv2::BasicIo::UniquePtr makeFileIo_() {
    const std::string path = makeTempFilePath_();
    return Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(path));
  }
};

TEST_F(AsfVideoTest_1561, MimeTypeReturnsExpectedValue_1561) {
  Exiv2::AsfVideo video(makeFileIo_());
  EXPECT_EQ("video/asf", video.mimeType());
}

TEST_F(AsfVideoTest_1561, MimeTypeIsStableAcrossMultipleCalls_1561) {
  Exiv2::AsfVideo video(makeFileIo_());
  const std::string first = video.mimeType();
  const std::string second = video.mimeType();
  const std::string third = video.mimeType();

  EXPECT_EQ("video/asf", first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(AsfVideoTest_1561, MimeTypeCallableOnConstObject_1561) {
  Exiv2::AsfVideo video(makeFileIo_());
  const Exiv2::AsfVideo& cref = video;

  const std::string mt = cref.mimeType();
  EXPECT_EQ("video/asf", mt);
  EXPECT_FALSE(mt.empty());
}

}  // namespace