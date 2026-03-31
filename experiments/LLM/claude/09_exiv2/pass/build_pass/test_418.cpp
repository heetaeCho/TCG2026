#include <gtest/gtest.h>
#include <sstream>
#include "nikonmn_int.hpp"
#include "exiv2/exiv2.hpp"

namespace {

// Test fixture for Nikon2MakerNote tests
class Nikon2MakerNoteTest_418 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that tagList() returns a non-null pointer
TEST_F(Nikon2MakerNoteTest_418, TagListReturnsNonNull_418) {
  auto tagList = Exiv2::Internal::Nikon2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

// Test that tagList() is callable multiple times and returns the same result (constexpr/static)
TEST_F(Nikon2MakerNoteTest_418, TagListIsConsistent_418) {
  auto tagList1 = Exiv2::Internal::Nikon2MakerNote::tagList();
  auto tagList2 = Exiv2::Internal::Nikon2MakerNote::tagList();
  EXPECT_EQ(tagList1, tagList2);
}

// Test that the first entry in tagList has a valid tag (tag 0 or some known starting tag)
TEST_F(Nikon2MakerNoteTest_418, TagListFirstEntryHasValidTag_418) {
  auto tagList = Exiv2::Internal::Nikon2MakerNote::tagList();
  // The first entry should have a non-empty title or valid tag number
  // At minimum, the tag info array should have entries before the sentinel
  EXPECT_NE(tagList[0].tag_, 0xffff);  // Not immediately a sentinel
}

// Test that tagList contains a sentinel entry (last entry marker)
TEST_F(Nikon2MakerNoteTest_418, TagListContainsSentinel_418) {
  auto tagList = Exiv2::Internal::Nikon2MakerNote::tagList();
  // Walk through the tag list to find the sentinel (tag_ == 0xffff typically)
  bool foundSentinel = false;
  for (int i = 0; i < 1000; ++i) {  // Upper bound to avoid infinite loop
    if (tagList[i].tag_ == 0xffff) {
      foundSentinel = true;
      break;
    }
  }
  EXPECT_TRUE(foundSentinel);
}

// Test print0x000a with a valid value
TEST_F(Nikon2MakerNoteTest_418, Print0x000aWithValidValue_418) {
  std::ostringstream os;
  Exiv2::ULongValue value;
  value.read("72");  // Example zoom value
  
  Exiv2::Internal::Nikon2MakerNote::print0x000a(os, value, nullptr);
  
  std::string result = os.str();
  // The function should produce some output
  EXPECT_FALSE(result.empty());
}

// Test print0x000a with zero value
TEST_F(Nikon2MakerNoteTest_418, Print0x000aWithZeroValue_418) {
  std::ostringstream os;
  Exiv2::ULongValue value;
  value.read("0");
  
  Exiv2::Internal::Nikon2MakerNote::print0x000a(os, value, nullptr);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x000a with nullptr ExifData
TEST_F(Nikon2MakerNoteTest_418, Print0x000aWithNullExifData_418) {
  std::ostringstream os;
  Exiv2::ULongValue value;
  value.read("100");
  
  // Should not crash with nullptr ExifData
  Exiv2::Internal::Nikon2MakerNote::print0x000a(os, value, nullptr);
  
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test print0x000a returns the same ostream reference
TEST_F(Nikon2MakerNoteTest_418, Print0x000aReturnsOstream_418) {
  std::ostringstream os;
  Exiv2::ULongValue value;
  value.read("50");
  
  std::ostream& returnedOs = Exiv2::Internal::Nikon2MakerNote::print0x000a(os, value, nullptr);
  
  EXPECT_EQ(&returnedOs, &os);
}

// Test that tagList entries have reasonable properties
TEST_F(Nikon2MakerNoteTest_418, TagListEntriesHaveNames_418) {
  auto tagList = Exiv2::Internal::Nikon2MakerNote::tagList();
  // Check that the first few entries (before sentinel) have non-null names
  if (tagList[0].tag_ != 0xffff) {
    EXPECT_NE(tagList[0].name_, nullptr);
    if (tagList[0].name_ != nullptr) {
      EXPECT_GT(strlen(tagList[0].name_), 0u);
    }
  }
}

}  // namespace
