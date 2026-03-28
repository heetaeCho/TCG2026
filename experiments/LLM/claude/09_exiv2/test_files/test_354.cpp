#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exif.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffMnEntry tests
class TiffMnEntryTest_354 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that TiffMnEntry can be constructed with valid parameters
TEST_F(TiffMnEntryTest_354, ConstructWithValidParams_354) {
  ASSERT_NO_THROW({
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
  });
}

// Test that TiffMnEntry can be constructed with different tag values
TEST_F(TiffMnEntryTest_354, ConstructWithDifferentTag_354) {
  ASSERT_NO_THROW({
    TiffMnEntry entry(0x0001, IfdId::exifId, IfdId::canonId);
  });
}

// Test that TiffMnEntry can be constructed with tag value 0 (boundary)
TEST_F(TiffMnEntryTest_354, ConstructWithZeroTag_354) {
  ASSERT_NO_THROW({
    TiffMnEntry entry(0x0000, IfdId::exifId, IfdId::canonId);
  });
}

// Test that TiffMnEntry can be constructed with max tag value (boundary)
TEST_F(TiffMnEntryTest_354, ConstructWithMaxTag_354) {
  ASSERT_NO_THROW({
    TiffMnEntry entry(0xFFFF, IfdId::exifId, IfdId::canonId);
  });
}

// Test that TiffMnEntry destructor works correctly
TEST_F(TiffMnEntryTest_354, DestructorDoesNotThrow_354) {
  ASSERT_NO_THROW({
    auto* entry = new TiffMnEntry(0x927c, IfdId::exifId, IfdId::canonId);
    delete entry;
  });
}

// Test that TiffMnEntry stores the correct tag
TEST_F(TiffMnEntryTest_354, StoresCorrectTag_354) {
  TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
  EXPECT_EQ(entry.tag(), 0x927c);
}

// Test that TiffMnEntry stores the correct group
TEST_F(TiffMnEntryTest_354, StoresCorrectGroup_354) {
  TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
  EXPECT_EQ(entry.group(), IfdId::exifId);
}

// Test doCount returns expected value for empty entry
TEST_F(TiffMnEntryTest_354, DoCountForEmptyEntry_354) {
  TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
  // An empty MnEntry should report 0 count
  EXPECT_EQ(entry.count(), 0u);
}

// Test doSize returns expected value for empty entry
TEST_F(TiffMnEntryTest_354, DoSizeForEmptyEntry_354) {
  TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
  // An empty MnEntry should report 0 size
  EXPECT_EQ(entry.size(), 0u);
}

// Test that multiple TiffMnEntry objects can coexist
TEST_F(TiffMnEntryTest_354, MultipleEntriesCoexist_354) {
  TiffMnEntry entry1(0x927c, IfdId::exifId, IfdId::canonId);
  TiffMnEntry entry2(0x927c, IfdId::exifId, IfdId::nikonId);
  EXPECT_EQ(entry1.tag(), entry2.tag());
  EXPECT_EQ(entry1.group(), entry2.group());
}

// Test clone functionality
TEST_F(TiffMnEntryTest_354, ClonePreservesTag_354) {
  TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
  auto cloned = entry.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->tag(), 0x927c);
  EXPECT_EQ(cloned->group(), IfdId::exifId);
}
