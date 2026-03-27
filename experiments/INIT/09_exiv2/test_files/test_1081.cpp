// File: test_image_writeXmpFromPacket_1081.cpp
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

namespace {

// Fixture for TEST_ID 1081
class ImageWriteXmpFromPacketTest_1081 : public ::testing::Test {
 protected:
  static Exiv2::Image makeImage() {
    // Avoid relying on specific enum constants; treat as black-box construction inputs.
    const auto type = static_cast<Exiv2::ImageType>(0);
    const uint16_t supportedMetadata = 0;

    // Use a real BasicIo implementation from Exiv2.
    Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);

    return Exiv2::Image(type, supportedMetadata, std::move(io));
  }
};

}  // namespace

TEST_F(ImageWriteXmpFromPacketTest_1081, DefaultIsFalse_1081) {
  auto img = makeImage();

  // Observable behavior via public getter
  EXPECT_FALSE(img.writeXmpFromPacket());
}

TEST_F(ImageWriteXmpFromPacketTest_1081, SetTrueThenGetterReturnsTrue_1081) {
  auto img = makeImage();

  img.writeXmpFromPacket(true);

  EXPECT_TRUE(img.writeXmpFromPacket());
}

TEST_F(ImageWriteXmpFromPacketTest_1081, SetFalseThenGetterReturnsFalse_1081) {
  auto img = makeImage();

  img.writeXmpFromPacket(true);
  ASSERT_TRUE(img.writeXmpFromPacket());

  img.writeXmpFromPacket(false);

  EXPECT_FALSE(img.writeXmpFromPacket());
}

TEST_F(ImageWriteXmpFromPacketTest_1081, ToggleMultipleTimesTracksLastValue_1081) {
  auto img = makeImage();

  img.writeXmpFromPacket(true);
  EXPECT_TRUE(img.writeXmpFromPacket());

  img.writeXmpFromPacket(false);
  EXPECT_FALSE(img.writeXmpFromPacket());

  img.writeXmpFromPacket(true);
  EXPECT_TRUE(img.writeXmpFromPacket());
}

TEST_F(ImageWriteXmpFromPacketTest_1081, IdempotentWhenSettingSameValue_1081) {
  auto img = makeImage();

  img.writeXmpFromPacket(false);
  EXPECT_FALSE(img.writeXmpFromPacket());

  img.writeXmpFromPacket(false);
  EXPECT_FALSE(img.writeXmpFromPacket());

  img.writeXmpFromPacket(true);
  EXPECT_TRUE(img.writeXmpFromPacket());

  img.writeXmpFromPacket(true);
  EXPECT_TRUE(img.writeXmpFromPacket());
}