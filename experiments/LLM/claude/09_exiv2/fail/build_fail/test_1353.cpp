#include <gtest/gtest.h>
#include <sstream>

// Include necessary Exiv2 headers
#include "casiomn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test that tagList() returns a non-null pointer
TEST(Casio2MakerNoteTest_1353, TagListReturnsNonNull_1353) {
  auto tagList = Casio2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

// Test that the first entry in the tag list has a valid tag ID (tag 0 or similar)
TEST(Casio2MakerNoteTest_1353, TagListFirstEntryValid_1353) {
  auto tagList = Casio2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // The first entry should have a non-empty title or a valid tag
  // TagInfo arrays are terminated by a sentinel with tag == 0xffff or similar
  // At minimum, the first tag's name should not be null
  EXPECT_NE(tagList[0].name_, nullptr);
}

// Test that tagList has a proper sentinel/terminator entry
TEST(Casio2MakerNoteTest_1353, TagListHasSentinel_1353) {
  auto tagList = Casio2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  // Iterate through the tag list until we find the sentinel
  int count = 0;
  const int maxTags = 1000; // safety limit
  while (count < maxTags && tagList[count].tag_ != 0xffff) {
    count++;
  }
  // We should find a sentinel before hitting the safety limit
  EXPECT_LT(count, maxTags);
}

// Test that tagList contains multiple entries
TEST(Casio2MakerNoteTest_1353, TagListContainsMultipleEntries_1353) {
  auto tagList = Casio2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  int count = 0;
  const int maxTags = 1000;
  while (count < maxTags && tagList[count].tag_ != 0xffff) {
    count++;
  }
  // Casio2 maker note should have at least a few tags
  EXPECT_GT(count, 0);
}

// Test print0x2001 with a valid value
TEST(Casio2MakerNoteTest_1353, Print0x2001WithValidValue_1353) {
  std::ostringstream os;
  UShortValue value;
  value.read("1");
  
  auto& result = Casio2MakerNote::print0x2001(os, value, nullptr);
  
  // Verify it returns the same stream
  EXPECT_EQ(&result, &os);
  // The output should not be empty
  EXPECT_FALSE(os.str().empty());
}

// Test print0x2001 with value 0
TEST(Casio2MakerNoteTest_1353, Print0x2001WithZeroValue_1353) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  
  auto& result = Casio2MakerNote::print0x2001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test print0x2022 with a valid value
TEST(Casio2MakerNoteTest_1353, Print0x2022WithValidValue_1353) {
  std::ostringstream os;
  UShortValue value;
  value.read("1");
  
  auto& result = Casio2MakerNote::print0x2022(os, value, nullptr);
  
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test print0x2022 with value 0
TEST(Casio2MakerNoteTest_1353, Print0x2022WithZeroValue_1353) {
  std::ostringstream os;
  UShortValue value;
  value.read("0");
  
  auto& result = Casio2MakerNote::print0x2022(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test print0x2001 with an out-of-range value
TEST(Casio2MakerNoteTest_1353, Print0x2001WithOutOfRangeValue_1353) {
  std::ostringstream os;
  UShortValue value;
  value.read("9999");
  
  auto& result = Casio2MakerNote::print0x2001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Should still produce some output (even if it's the numeric value)
  EXPECT_FALSE(os.str().empty());
}

// Test print0x2022 with an out-of-range value
TEST(Casio2MakerNoteTest_1353, Print0x2022WithOutOfRangeValue_1353) {
  std::ostringstream os;
  UShortValue value;
  value.read("9999");
  
  auto& result = Casio2MakerNote::print0x2022(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

// Test that calling tagList() multiple times returns the same pointer (constexpr/static data)
TEST(Casio2MakerNoteTest_1353, TagListIsConsistentAcrossCalls_1353) {
  auto tagList1 = Casio2MakerNote::tagList();
  auto tagList2 = Casio2MakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

// Test print0x2001 with nullptr ExifData (should not crash)
TEST(Casio2MakerNoteTest_1353, Print0x2001WithNullExifData_1353) {
  std::ostringstream os;
  UShortValue value;
  value.read("2");
  
  // Should not crash with nullptr ExifData
  EXPECT_NO_THROW(Casio2MakerNote::print0x2001(os, value, nullptr));
}

// Test print0x2022 with nullptr ExifData (should not crash)
TEST(Casio2MakerNoteTest_1353, Print0x2022WithNullExifData_1353) {
  std::ostringstream os;
  UShortValue value;
  value.read("2");
  
  EXPECT_NO_THROW(Casio2MakerNote::print0x2022(os, value, nullptr));
}

// Test that each tag in the list has a non-null name
TEST(Casio2MakerNoteTest_1353, AllTagsHaveNonNullNames_1353) {
  auto tagList = Casio2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  int i = 0;
  const int maxTags = 1000;
  while (i < maxTags && tagList[i].tag_ != 0xffff) {
    EXPECT_NE(tagList[i].name_, nullptr) << "Tag at index " << i << " has null name";
    i++;
  }
}
