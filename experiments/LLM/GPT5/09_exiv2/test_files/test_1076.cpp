// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_image_setIptcData_1076.cpp
//
// Unit tests for Exiv2::Image::setIptcData
// TEST_ID: 1076

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/iptc.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

// Helper: create an Image with an in-memory IO backend.
static Exiv2::BasicIo::UniquePtr makeMemIo()
{
  // Prefer an explicit empty buffer ctor to avoid depending on a default ctor.
  return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(nullptr, 0));
}

static std::unique_ptr<Exiv2::Image> makeImage()
{
  // The specific ImageType/supportedMetadata values are not relevant for setIptcData;
  // we only need a valid instance.
  return std::unique_ptr<Exiv2::Image>(
      new Exiv2::Image(Exiv2::ImageType::none, /*supportedMetadata=*/0, makeMemIo()));
}

// Best-effort helper to populate IPTC with a single entry using only the public interface.
// If the key/value assignment semantics change in Exiv2, these tests will reveal it.
static void addOneIptcEntry(Exiv2::IptcData& iptc, const std::string& key, const std::string& value)
{
  // Exiv2 datum types commonly support assignment from std::string via operator=.
  iptc[key] = value;
}

} // namespace

class ImageSetIptcDataTest_1076 : public ::testing::Test {
protected:
  void SetUp() override { image_ = makeImage(); }
  std::unique_ptr<Exiv2::Image> image_;
};

TEST_F(ImageSetIptcDataTest_1076, SetEmptyIptcDataResultsInEmpty_1076)
{
  Exiv2::IptcData empty;
  ASSERT_TRUE(empty.empty());
  ASSERT_EQ(empty.size(), 0u);

  image_->setIptcData(empty);

  EXPECT_TRUE(image_->iptcData().empty());
  EXPECT_EQ(image_->iptcData().size(), 0u);
  EXPECT_EQ(image_->iptcData().count(), 0u);
}

TEST_F(ImageSetIptcDataTest_1076, SetNonEmptyIptcDataCopiesContent_1076)
{
  Exiv2::IptcData src;
  addOneIptcEntry(src, "Iptc.Application2.ObjectName", "UnitTest");

  ASSERT_FALSE(src.empty());
  ASSERT_EQ(src.size(), 1u);

  image_->setIptcData(src);

  EXPECT_FALSE(image_->iptcData().empty());
  EXPECT_EQ(image_->iptcData().size(), 1u);

  // Verify the key is observable via operator[] / count behavior.
  // (count() is total count, not per-key; so we just check retrieval doesn’t reduce size.)
  const auto beforeSize = image_->iptcData().size();
  (void)image_->iptcData()["Iptc.Application2.ObjectName"];
  EXPECT_EQ(image_->iptcData().size(), beforeSize);
}

TEST_F(ImageSetIptcDataTest_1076, ModifyingSourceAfterSetDoesNotAffectImage_1076)
{
  Exiv2::IptcData src;
  addOneIptcEntry(src, "Iptc.Application2.ObjectName", "Original");
  ASSERT_EQ(src.size(), 1u);

  image_->setIptcData(src);
  ASSERT_EQ(image_->iptcData().size(), 1u);

  // Mutate the source after setting.
  src.clear();
  ASSERT_TRUE(src.empty());
  ASSERT_EQ(src.size(), 0u);

  // Image should retain its own copy.
  EXPECT_FALSE(image_->iptcData().empty());
  EXPECT_EQ(image_->iptcData().size(), 1u);
  EXPECT_EQ(image_->iptcData().count(), 1u);
}

TEST_F(ImageSetIptcDataTest_1076, RepeatedSetOverwritesPreviousIptcData_1076)
{
  Exiv2::IptcData first;
  addOneIptcEntry(first, "Iptc.Application2.ObjectName", "First");
  ASSERT_EQ(first.size(), 1u);

  image_->setIptcData(first);
  ASSERT_EQ(image_->iptcData().size(), 1u);

  Exiv2::IptcData second; // empty
  image_->setIptcData(second);

  EXPECT_TRUE(image_->iptcData().empty());
  EXPECT_EQ(image_->iptcData().size(), 0u);
  EXPECT_EQ(image_->iptcData().count(), 0u);
}

TEST_F(ImageSetIptcDataTest_1076, SelfAssignmentDoesNotCrashAndPreservesData_1076)
{
  Exiv2::IptcData src;
  addOneIptcEntry(src, "Iptc.Application2.ObjectName", "SelfAssign");
  image_->setIptcData(src);
  ASSERT_EQ(image_->iptcData().size(), 1u);

  // Observable behavior: calling setIptcData with the same object returned by iptcData()
  // should not crash and should keep content consistent.
  image_->setIptcData(image_->iptcData());

  EXPECT_FALSE(image_->iptcData().empty());
  EXPECT_EQ(image_->iptcData().size(), 1u);
  EXPECT_EQ(image_->iptcData().count(), 1u);
}