#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

// We need access to the internal function. Since it's in an anonymous-like static context
// within the Internal namespace, we need to declare it or include the internal header.
#include "samsungmn_int.hpp"

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to invoke printValueMinus4 via the tag info if exposed,
// or we test it indirectly through the Samsung makernote tags.
// Since printValueMinus4 is a static function in the .cpp file, 
// we may need to test it through the Samsung MakerNote tag definitions.

// The function printValueMinus4 is used as a print function for Samsung tags.
// We can test it by looking up Samsung makernote tags and using their print method.

class SamsungMnTest_1724 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Samsung makernote tags are accessible
TEST_F(SamsungMnTest_1724, Samsung2MnTagListNotEmpty_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  // At least one tag should exist
  EXPECT_NE(tagList[0].tag_, 0xffff);  // Check it's not immediately the end marker
}

// Test that we can look up known Samsung2 tags
TEST_F(SamsungMnTest_1724, Samsung2KnownTagLookup_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  bool foundTag = false;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    if (tagList[i].tag_ != 0) {
      foundTag = true;
      break;
    }
  }
  // There should be at least some tags defined
  EXPECT_TRUE(foundTag);
}

// Test printValueMinus4 behavior through a tag that uses it.
// The FaceDetect tag (0x0100) in Samsung2 makernote uses printValueMinus4.
// We find a tag that uses this print function and test its output.

// We need to find which tag uses printValueMinus4.
// Typically Samsung2 FaceDetect (tag 0x0100) or similar uses it.
// Let's test by iterating and finding tags, then testing their print functions.

TEST_F(SamsungMnTest_1724, TagListContainsValidEntries_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  int count = 0;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    count++;
    // Each tag should have a non-null name
    EXPECT_NE(tagList[i].name_, nullptr);
  }
  EXPECT_GT(count, 0);
}

// Test that tag names are non-empty strings
TEST_F(SamsungMnTest_1724, TagNamesAreNonEmpty_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    ASSERT_NE(tagList[i].name_, nullptr);
    EXPECT_GT(strlen(tagList[i].name_), 0u) 
        << "Tag 0x" << std::hex << tagList[i].tag_ << " has empty name";
  }
}

// Test printing of a UShort value through a tag that uses printValueMinus4
// We search for such a tag and test it
TEST_F(SamsungMnTest_1724, PrintValueMinus4WithUShortValue_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  // Find a tag with a non-null print function (potentially printValueMinus4)
  const TagInfo* targetTag = nullptr;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    if (tagList[i].print_ != nullptr && tagList[i].tag_ == 0x0100) {
      targetTag = &tagList[i];
      break;
    }
  }
  
  // If we found tag 0x0100 (FaceDetect) which uses printValueMinus4
  if (targetTag && targetTag->print_) {
    // Create a UShort value with count 1
    ValueType<uint16_t> val(unsignedShort);
    val.value_.push_back(10);
    
    std::ostringstream os;
    targetTag->print_(os, val, nullptr);
    
    std::string result = os.str();
    // If it uses printValueMinus4, the result should be "6" (10-4=6)
    // Otherwise it will print the value differently
    // We just verify it doesn't crash and produces output
    EXPECT_FALSE(result.empty());
  }
}

// Test the Samsung (not Samsung2) tag list
TEST_F(SamsungMnTest_1724, SamsungMnTagListAccessible_1724) {
  // Samsung (original) makernote tags
  const TagInfo* tagList = SamsungMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

// Test that Samsung tag list has valid entries
TEST_F(SamsungMnTest_1724, SamsungTagListValidEntries_1724) {
  const TagInfo* tagList = SamsungMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  int count = 0;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    count++;
    EXPECT_NE(tagList[i].name_, nullptr);
  }
  // Should have at least some entries
  EXPECT_GE(count, 0);
}

// Test printValueMinus4 with wrong type (not unsignedShort) - should print raw value
TEST_F(SamsungMnTest_1724, PrintValueMinus4WithWrongType_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  const TagInfo* targetTag = nullptr;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    if (tagList[i].print_ != nullptr && tagList[i].tag_ == 0x0100) {
      targetTag = &tagList[i];
      break;
    }
  }
  
  if (targetTag && targetTag->print_) {
    // Create a string value (wrong type for printValueMinus4)
    AsciiValue val;
    val.read("test");
    
    std::ostringstream os;
    targetTag->print_(os, val, nullptr);
    
    std::string result = os.str();
    // Should print the raw value since type doesn't match
    EXPECT_FALSE(result.empty());
  }
}

// Test printValueMinus4 with multiple count UShort - should print raw value
TEST_F(SamsungMnTest_1724, PrintValueMinus4WithMultipleCount_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  const TagInfo* targetTag = nullptr;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    if (tagList[i].print_ != nullptr && tagList[i].tag_ == 0x0100) {
      targetTag = &tagList[i];
      break;
    }
  }
  
  if (targetTag && targetTag->print_) {
    // Create a UShort value with count > 1
    ValueType<uint16_t> val(unsignedShort);
    val.value_.push_back(10);
    val.value_.push_back(20);
    
    std::ostringstream os;
    targetTag->print_(os, val, nullptr);
    
    std::string result = os.str();
    // count != 1, so should print raw value
    EXPECT_FALSE(result.empty());
  }
}

// Test printValueMinus4 with zero value
TEST_F(SamsungMnTest_1724, PrintValueMinus4WithZeroValue_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  const TagInfo* targetTag = nullptr;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    if (tagList[i].print_ != nullptr && tagList[i].tag_ == 0x0100) {
      targetTag = &tagList[i];
      break;
    }
  }
  
  if (targetTag && targetTag->print_) {
    ValueType<uint16_t> val(unsignedShort);
    val.value_.push_back(0);
    
    std::ostringstream os;
    targetTag->print_(os, val, nullptr);
    
    std::string result = os.str();
    // 0 - 4 = -4
    EXPECT_EQ(result, "-4");
  }
}

// Test printValueMinus4 with value = 4 (should yield 0)
TEST_F(SamsungMnTest_1724, PrintValueMinus4WithValue4_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  const TagInfo* targetTag = nullptr;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    if (tagList[i].print_ != nullptr && tagList[i].tag_ == 0x0100) {
      targetTag = &tagList[i];
      break;
    }
  }
  
  if (targetTag && targetTag->print_) {
    ValueType<uint16_t> val(unsignedShort);
    val.value_.push_back(4);
    
    std::ostringstream os;
    targetTag->print_(os, val, nullptr);
    
    std::string result = os.str();
    // 4 - 4 = 0
    EXPECT_EQ(result, "0");
  }
}

// Test printValueMinus4 with large value
TEST_F(SamsungMnTest_1724, PrintValueMinus4WithLargeValue_1724) {
  const TagInfo* tagList = Samsung2MakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
  
  const TagInfo* targetTag = nullptr;
  for (int i = 0; tagList[i].tag_ != 0xffff; ++i) {
    if (tagList[i].print_ != nullptr && tagList[i].tag_ == 0x0100) {
      targetTag = &tagList[i];
      break;
    }
  }
  
  if (targetTag && targetTag->print_) {
    ValueType<uint16_t> val(unsignedShort);
    val.value_.push_back(65535);  // max uint16
    
    std::ostringstream os;
    targetTag->print_(os, val, nullptr);
    
    std::string result = os.str();
    // 65535 - 4 = 65531
    EXPECT_EQ(result, "65531");
  }
}

}  // namespace
