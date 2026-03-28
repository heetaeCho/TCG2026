// File: test_image_clearIptcData_1075.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

class ImageClearIptcDataTest_1075 : public ::testing::Test {
 protected:
  static Exiv2::Image makeImage() {
    // Use an in-memory IO implementation (MemIo) so we don't touch the filesystem.
    auto io = std::make_unique<Exiv2::MemIo>();

    // We only need a valid-looking Image instance for exercising clearIptcData().
    // Avoid relying on specific ImageType values: use a casted value.
    return Exiv2::Image(static_cast<Exiv2::ImageType>(0), /*supportedMetadata=*/0, std::move(io));
  }

  static void addOneIptcDatum(Exiv2::IptcData& iptc, const std::string& key, const std::string& valueText) {
    // Add a simple string IPTC value using public API.
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::string);
    ASSERT_TRUE(v.get() != nullptr);
    ASSERT_NO_THROW(v->read(valueText));

    Exiv2::IptcKey k(key);
    EXPECT_NO_THROW((void)iptc.add(k, v.get()));
  }
};

TEST_F(ImageClearIptcDataTest_1075, ClearsPreviouslyAddedIptcData_1075) {
  Exiv2::Image image = makeImage();
  Exiv2::IptcData& iptc = image.iptcData();

  EXPECT_TRUE(iptc.empty());
  EXPECT_EQ(iptc.count(), 0u);

  addOneIptcDatum(iptc, "Iptc.Application2.ObjectName", "hello");
  EXPECT_FALSE(iptc.empty());
  EXPECT_GE(iptc.count(), 1u);

  EXPECT_NO_THROW(image.clearIptcData());

  EXPECT_TRUE(iptc.empty());
  EXPECT_EQ(iptc.count(), 0u);
}

TEST_F(ImageClearIptcDataTest_1075, ClearOnAlreadyEmptyIsSafeAndIdempotent_1075) {
  Exiv2::Image image = makeImage();
  Exiv2::IptcData& iptc = image.iptcData();

  EXPECT_TRUE(iptc.empty());
  EXPECT_EQ(iptc.count(), 0u);

  EXPECT_NO_THROW(image.clearIptcData());
  EXPECT_TRUE(iptc.empty());
  EXPECT_EQ(iptc.count(), 0u);

  // Call again to verify idempotency via observable state.
  EXPECT_NO_THROW(image.clearIptcData());
  EXPECT_TRUE(iptc.empty());
  EXPECT_EQ(iptc.count(), 0u);
}

TEST_F(ImageClearIptcDataTest_1075, ClearsMultipleEntries_1075) {
  Exiv2::Image image = makeImage();
  Exiv2::IptcData& iptc = image.iptcData();

  addOneIptcDatum(iptc, "Iptc.Application2.ObjectName", "one");
  addOneIptcDatum(iptc, "Iptc.Application2.Caption", "two");
  addOneIptcDatum(iptc, "Iptc.Application2.Byline", "three");

  EXPECT_FALSE(iptc.empty());
  EXPECT_GE(iptc.count(), 1u);

  EXPECT_NO_THROW(image.clearIptcData());

  EXPECT_TRUE(iptc.empty());
  EXPECT_EQ(iptc.count(), 0u);
}

TEST_F(ImageClearIptcDataTest_1075, ReferenceFromIptcDataReflectsClear_1075) {
  Exiv2::Image image = makeImage();

  Exiv2::IptcData& iptcRef1 = image.iptcData();
  addOneIptcDatum(iptcRef1, "Iptc.Application2.ObjectName", "persist?");

  EXPECT_FALSE(iptcRef1.empty());
  EXPECT_GE(iptcRef1.count(), 1u);

  // Obtain another reference through the public accessor to verify the same observable state.
  Exiv2::IptcData& iptcRef2 = image.iptcData();
  EXPECT_FALSE(iptcRef2.empty());
  EXPECT_EQ(iptcRef2.count(), iptcRef1.count());

  EXPECT_NO_THROW(image.clearIptcData());

  EXPECT_TRUE(iptcRef1.empty());
  EXPECT_TRUE(iptcRef2.empty());
  EXPECT_EQ(iptcRef1.count(), 0u);
  EXPECT_EQ(iptcRef2.count(), 0u);
}

}  // namespace