// =================================================================================================
// TEST_ID: 656
// File: test_quicktimevideo_mimetype_656.cpp
// Unit tests for Exiv2::QuickTimeVideo::mimeType()
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/quicktimevideo.hpp>

#include <memory>
#include <string>

namespace {

class QuickTimeVideoTest_656 : public ::testing::Test {
 protected:
  static constexpr size_t kMaxRecursionDepth = 1;
};

TEST_F(QuickTimeVideoTest_656, MimeTypeReturnsVideoQuickTime_656) {
  // Arrange: construct with an in-memory IO object (no filesystem dependency).
  Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
  Exiv2::QuickTimeVideo video(std::move(io), kMaxRecursionDepth);

  // Act
  const std::string mime = video.mimeType();

  // Assert
  EXPECT_EQ("video/quicktime", mime);
}

TEST_F(QuickTimeVideoTest_656, MimeTypeIsStableAcrossMultipleCalls_656) {
  Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
  Exiv2::QuickTimeVideo video(std::move(io), kMaxRecursionDepth);

  const std::string first = video.mimeType();
  const std::string second = video.mimeType();
  const std::string third = video.mimeType();

  EXPECT_EQ("video/quicktime", first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(QuickTimeVideoTest_656, MimeTypeCallableViaConstReference_656) {
  Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
  Exiv2::QuickTimeVideo video(std::move(io), kMaxRecursionDepth);
  const Exiv2::QuickTimeVideo& const_ref = video;

  const std::string mime = const_ref.mimeType();

  EXPECT_EQ("video/quicktime", mime);
}

}  // namespace