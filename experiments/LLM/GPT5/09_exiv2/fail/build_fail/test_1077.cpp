// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::Image::clearXmpPacket (TEST_ID = 1077)

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

class ImageClearXmpPacketTest_1077 : public ::testing::Test {
protected:
  static std::unique_ptr<Exiv2::Image> makeImage() {
    // Use an in-memory IO implementation (external dependency).
    auto io = std::make_unique<Exiv2::MemIo>();

    // Minimal constructor args: image type + supported metadata flags + IO.
    // "none" is commonly available; if your tree uses a different sentinel,
    // adjust to an existing ImageType enumerator.
    return std::make_unique<Exiv2::Image>(Exiv2::ImageType::none, /*supportedMetadata=*/0, std::move(io));
  }
};

TEST_F(ImageClearXmpPacketTest_1077, ClearXmpPacket_EmptiesPacketAndSetsWriteFlagTrue_1077) {
  auto img = makeImage();

  img->setXmpPacket("dummy-xmp");
  img->writeXmpFromPacket(false);

  ASSERT_FALSE(img->xmpPacket().empty());
  ASSERT_FALSE(img->writeXmpFromPacket());

  img->clearXmpPacket();

  EXPECT_TRUE(img->xmpPacket().empty());
  EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageClearXmpPacketTest_1077, ClearXmpPacket_WhenAlreadyEmpty_StillSetsWriteFlagTrue_1077) {
  auto img = makeImage();

  img->setXmpPacket(std::string{});
  img->writeXmpFromPacket(false);

  ASSERT_TRUE(img->xmpPacket().empty());
  ASSERT_FALSE(img->writeXmpFromPacket());

  img->clearXmpPacket();

  EXPECT_TRUE(img->xmpPacket().empty());
  EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageClearXmpPacketTest_1077, ClearXmpPacket_IsIdempotent_MultipleCallsKeepEmptyAndFlagTrue_1077) {
  auto img = makeImage();

  img->setXmpPacket("x");
  img->writeXmpFromPacket(false);

  img->clearXmpPacket();
  ASSERT_TRUE(img->xmpPacket().empty());
  ASSERT_TRUE(img->writeXmpFromPacket());

  // Call again (boundary/idempotence behavior)
  img->clearXmpPacket();

  EXPECT_TRUE(img->xmpPacket().empty());
  EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageClearXmpPacketTest_1077, ClearXmpPacket_ClearsLargePacket_1077) {
  auto img = makeImage();

  std::string large(256 * 1024, 'A');  // boundary-ish: large packet
  img->setXmpPacket(large);
  img->writeXmpFromPacket(false);

  ASSERT_EQ(img->xmpPacket().size(), large.size());
  ASSERT_FALSE(img->writeXmpFromPacket());

  img->clearXmpPacket();

  EXPECT_TRUE(img->xmpPacket().empty());
  EXPECT_TRUE(img->writeXmpFromPacket());
}

}  // namespace