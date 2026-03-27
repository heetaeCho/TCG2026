// =================================================================================================
// TEST_ID: 1079
// File: test_image_clearxmpdata_1079.cpp
// Unit tests for Exiv2::Image::clearXmpData()
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Exiv2
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

namespace {

// Helper: create a minimal Image instance backed by MemIo.
// We treat Image as a black box and only use its public interface.
std::unique_ptr<Exiv2::Image> makeImage()
{
  auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo);
  // Use a broadly-supported metadata mask; the exact value is not important for this test.
  constexpr uint16_t kSupportedMetadata = 0xFFFF;
  return std::make_unique<Exiv2::Image>(Exiv2::ImageType::none, kSupportedMetadata, std::move(io));
}

} // namespace

class ImageClearXmpDataTest_1079 : public ::testing::Test {
protected:
  void SetUp() override { image_ = makeImage(); }

  std::unique_ptr<Exiv2::Image> image_;
};

TEST_F(ImageClearXmpDataTest_1079, ClearsNonEmptyXmpData_1079)
{
  ASSERT_NE(image_, nullptr);

  // Make XMP data observably non-empty via public API.
  (*image_).xmpData()["Xmp.dc.title"] = "hello";
  EXPECT_FALSE(image_->xmpData().empty());
  EXPECT_GT(image_->xmpData().count(), 0);

  // Flip the writeXmpFromPacket flag to true, then clearXmpData should force it to false
  // (observable via the public getter).
  image_->writeXmpFromPacket(true);
  EXPECT_TRUE(image_->writeXmpFromPacket());

  image_->clearXmpData();

  EXPECT_TRUE(image_->xmpData().empty());
  EXPECT_EQ(image_->xmpData().count(), 0);
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageClearXmpDataTest_1079, NoOpOnAlreadyEmptyXmpData_1079)
{
  ASSERT_NE(image_, nullptr);

  // Preconditions: ensure empty
  image_->xmpData().clear();
  EXPECT_TRUE(image_->xmpData().empty());
  EXPECT_EQ(image_->xmpData().count(), 0);

  // Set flag true and verify clearXmpData still forces it to false even when data is empty.
  image_->writeXmpFromPacket(true);
  EXPECT_TRUE(image_->writeXmpFromPacket());

  EXPECT_NO_THROW(image_->clearXmpData());

  EXPECT_TRUE(image_->xmpData().empty());
  EXPECT_EQ(image_->xmpData().count(), 0);
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageClearXmpDataTest_1079, IdempotentWhenCalledMultipleTimes_1079)
{
  ASSERT_NE(image_, nullptr);

  (*image_).xmpData()["Xmp.dc.subject"] = "test";
  image_->writeXmpFromPacket(true);

  ASSERT_FALSE(image_->xmpData().empty());
  ASSERT_TRUE(image_->writeXmpFromPacket());

  image_->clearXmpData();
  EXPECT_TRUE(image_->xmpData().empty());
  EXPECT_FALSE(image_->writeXmpFromPacket());

  // Call again: should remain empty and keep the flag false.
  EXPECT_NO_THROW(image_->clearXmpData());
  EXPECT_TRUE(image_->xmpData().empty());
  EXPECT_EQ(image_->xmpData().count(), 0);
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageClearXmpDataTest_1079, ClearsMultipleEntries_1079)
{
  ASSERT_NE(image_, nullptr);

  (*image_).xmpData()["Xmp.dc.creator"] = "alice";
  (*image_).xmpData()["Xmp.dc.description"] = "desc";
  (*image_).xmpData()["Xmp.dc.rights"] = "rights";

  EXPECT_FALSE(image_->xmpData().empty());
  EXPECT_GE(image_->xmpData().count(), 3);

  image_->writeXmpFromPacket(true);
  image_->clearXmpData();

  EXPECT_TRUE(image_->xmpData().empty());
  EXPECT_EQ(image_->xmpData().count(), 0);
  EXPECT_FALSE(image_->writeXmpFromPacket());
}