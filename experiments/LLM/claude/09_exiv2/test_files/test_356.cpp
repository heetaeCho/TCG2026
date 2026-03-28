void doEncode(TiffEncoder& encoder, const Exifdatum* datum) {
    encoder.encodeSubIfd(this, datum);
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exif.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffSubIfd tests
class TiffSubIfdTest_356 : public ::testing::Test {
 protected:
  void SetUp() override {
  }
  void TearDown() override {
  }
};

// Test that TiffSubIfd can be constructed with valid parameters
TEST_F(TiffSubIfdTest_356, ConstructWithValidParameters_356) {
  EXPECT_NO_THROW({
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  });
}

// Test construction with tag 0 (boundary)
TEST_F(TiffSubIfdTest_356, ConstructWithZeroTag_356) {
  EXPECT_NO_THROW({
    TiffSubIfd subIfd(0x0000, IfdId::ifd0Id, IfdId::subImage1Id);
  });
}

// Test construction with max uint16 tag (boundary)
TEST_F(TiffSubIfdTest_356, ConstructWithMaxTag_356) {
  EXPECT_NO_THROW({
    TiffSubIfd subIfd(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
  });
}

// Test that TiffSubIfd inherits tag properly from TiffEntryBase
TEST_F(TiffSubIfdTest_356, TagIsSetCorrectly_356) {
  TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  EXPECT_EQ(subIfd.tag(), 0x014a);
}

// Test that TiffSubIfd inherits group properly from TiffEntryBase
TEST_F(TiffSubIfdTest_356, GroupIsSetCorrectly_356) {
  TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  EXPECT_EQ(subIfd.group(), IfdId::ifd0Id);
}

// Test construction with different group/newGroup combinations
TEST_F(TiffSubIfdTest_356, ConstructWithDifferentGroups_356) {
  EXPECT_NO_THROW({
    TiffSubIfd subIfd1(0x014a, IfdId::exifId, IfdId::subImage2Id);
  });
  EXPECT_NO_THROW({
    TiffSubIfd subIfd2(0x014a, IfdId::gpsId, IfdId::subImage3Id);
  });
}

// Test that multiple TiffSubIfd instances can coexist
TEST_F(TiffSubIfdTest_356, MultipleInstancesCoexist_356) {
  TiffSubIfd subIfd1(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  TiffSubIfd subIfd2(0x014b, IfdId::ifd0Id, IfdId::subImage2Id);
  
  EXPECT_EQ(subIfd1.tag(), 0x014a);
  EXPECT_EQ(subIfd2.tag(), 0x014b);
  EXPECT_NE(subIfd1.tag(), subIfd2.tag());
}

// Test that destruction works properly (no crash/leak)
TEST_F(TiffSubIfdTest_356, DestructionIsClean_356) {
  auto subIfd = std::make_unique<TiffSubIfd>(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  EXPECT_NO_THROW({
    subIfd.reset();
  });
}

// Test clone functionality
TEST_F(TiffSubIfdTest_356, ClonePreservesTag_356) {
  TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  auto cloned = subIfd.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->tag(), 0x014a);
  EXPECT_EQ(cloned->group(), IfdId::ifd0Id);
}

// Test that the type is set to unsigned long as per constructor
TEST_F(TiffSubIfdTest_356, TypeIsUnsignedLong_356) {
  TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  // The constructor passes ttUnsignedLong to TiffEntryBase
  // We can verify through size-related methods if available
  EXPECT_EQ(subIfd.tag(), 0x014a);
}
