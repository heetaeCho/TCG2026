// File: test_exifdatum_tag_748.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>

namespace {

// A small fixture to keep naming consistent.
class ExifdatumTest_748 : public ::testing::Test {};

TEST_F(ExifdatumTest_748, TagReturnsKeyTag_Basic_748) {
  const uint16_t kTag = 0x1234;
  Exiv2::ExifKey key(kTag, "Exif.Image");

  // pValue is an external dependency; we do not assume anything about Value types here.
  Exiv2::Exifdatum datum(key, /*pValue=*/nullptr);

  EXPECT_EQ(datum.tag(), kTag);
}

TEST_F(ExifdatumTest_748, TagSupportsBoundaryValues_748) {
  {
    const uint16_t kTag = 0x0000;
    Exiv2::ExifKey key(kTag, "Exif.Image");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), kTag);
  }
  {
    const uint16_t kTag = 0xFFFF;
    Exiv2::ExifKey key(kTag, "Exif.Photo");
    Exiv2::Exifdatum datum(key, nullptr);
    EXPECT_EQ(datum.tag(), kTag);
  }
}

TEST_F(ExifdatumTest_748, TagPreservedByCopyConstruction_748) {
  const uint16_t kTag = 0x00A1;
  Exiv2::ExifKey key(kTag, "Exif.Photo");
  Exiv2::Exifdatum original(key, nullptr);

  Exiv2::Exifdatum copied(original);

  EXPECT_EQ(copied.tag(), kTag);
  EXPECT_EQ(original.tag(), kTag);
}

TEST_F(ExifdatumTest_748, TagPreservedByCopyAssignment_748) {
  Exiv2::ExifKey keyA(static_cast<uint16_t>(0x0102), "Exif.Image");
  Exiv2::ExifKey keyB(static_cast<uint16_t>(0x0F0E), "Exif.Photo");

  Exiv2::Exifdatum a(keyA, nullptr);
  Exiv2::Exifdatum b(keyB, nullptr);

  ASSERT_EQ(a.tag(), 0x0102);
  ASSERT_EQ(b.tag(), 0x0F0E);

  a = b;

  EXPECT_EQ(a.tag(), b.tag());
  EXPECT_EQ(a.tag(), 0x0F0E);
}

TEST_F(ExifdatumTest_748, TagUnaffectedByValueAssignmentOperators_748) {
  const uint16_t kTag = 0x2222;
  Exiv2::ExifKey key(kTag, "Exif.Image");
  Exiv2::Exifdatum datum(key, nullptr);

  ASSERT_EQ(datum.tag(), kTag);

  // These operators are part of the public interface; regardless of what they do to the value,
  // the tag should remain the key tag (observable via tag()).
  datum = static_cast<uint16_t>(7);
  EXPECT_EQ(datum.tag(), kTag);

  datum = static_cast<uint32_t>(123456u);
  EXPECT_EQ(datum.tag(), kTag);

  datum = std::string("hello");
  EXPECT_EQ(datum.tag(), kTag);
}

}  // namespace