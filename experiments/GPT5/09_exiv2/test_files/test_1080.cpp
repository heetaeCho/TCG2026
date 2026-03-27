// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_image_setxmpdata_1080.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <memory>
#include <string>

namespace {

class ImageSetXmpDataTest_1080 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr makeIo() {
    // Prefer an in-memory IO object to avoid filesystem dependencies.
    // MemIo is part of Exiv2 public API (basicio.hpp) in typical builds.
    return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo());
  }

  static Exiv2::Image makeImage() {
    // supportedMetadata is not relevant for setXmpData behavior being tested.
    // Use a default/placeholder ImageType; behavior under test is independent of type.
    return Exiv2::Image(Exiv2::ImageType::none, /*supportedMetadata=*/0, makeIo());
  }
};

TEST_F(ImageSetXmpDataTest_1080, StoresProvidedXmpPacketInXmpData_1080) {
  auto image = makeImage();

  Exiv2::XmpData xmp;
  xmp.setPacket("packet-1080");

  image.setXmpData(xmp);

  EXPECT_EQ(image.xmpData().xmpPacket(), std::string("packet-1080"));
}

TEST_F(ImageSetXmpDataTest_1080, OverwritesPreviouslySetXmpData_1080) {
  auto image = makeImage();

  Exiv2::XmpData first;
  first.setPacket("first");
  image.setXmpData(first);
  ASSERT_EQ(image.xmpData().xmpPacket(), std::string("first"));

  Exiv2::XmpData second;
  second.setPacket("second");
  image.setXmpData(second);

  EXPECT_EQ(image.xmpData().xmpPacket(), std::string("second"));
}

TEST_F(ImageSetXmpDataTest_1080, ResetsWriteXmpFromPacketFlagToFalse_1080) {
  auto image = makeImage();

  // Put the image into a known non-default state.
  image.writeXmpFromPacket(true);
  ASSERT_TRUE(image.writeXmpFromPacket());

  Exiv2::XmpData xmp;
  xmp.setPacket("any");
  image.setXmpData(xmp);

  // Observable effect of internal writeXmpFromPacket(false) call.
  EXPECT_FALSE(image.writeXmpFromPacket());
}

TEST_F(ImageSetXmpDataTest_1080, SettingEmptyXmpDataClearsPacket_1080) {
  auto image = makeImage();

  Exiv2::XmpData nonEmpty;
  nonEmpty.setPacket("will-be-cleared");
  image.setXmpData(nonEmpty);
  ASSERT_EQ(image.xmpData().xmpPacket(), std::string("will-be-cleared"));

  Exiv2::XmpData empty;
  image.setXmpData(empty);

  EXPECT_TRUE(image.xmpData().xmpPacket().empty());
}

TEST_F(ImageSetXmpDataTest_1080, AcceptsLargePacketBoundary_1080) {
  auto image = makeImage();

  std::string largePacket(1 << 20, 'x');  // 1 MiB
  Exiv2::XmpData xmp;
  xmp.setPacket(largePacket);

  image.setXmpData(xmp);

  EXPECT_EQ(image.xmpData().xmpPacket().size(), largePacket.size());
  EXPECT_EQ(image.xmpData().xmpPacket(), largePacket);
}

}  // namespace