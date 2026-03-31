#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

class ExifDataTest_39 : public ::testing::Test {
 protected:
  Exiv2::ExifData exifData_;
};

// Test that a newly created ExifData is empty
TEST_F(ExifDataTest_39, DefaultConstructedIsEmpty_39) {
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
}

// Test that begin() == end() for empty ExifData
TEST_F(ExifDataTest_39, BeginEqualsEndWhenEmpty_39) {
  EXPECT_EQ(exifData_.begin(), exifData_.end());
}

// Test adding an element via operator[] increases count
TEST_F(ExifDataTest_39, OperatorBracketAddsElement_39) {
  exifData_["Exif.Image.Make"] = "TestCamera";
  EXPECT_FALSE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 1u);
}

// Test operator[] returns the same datum for the same key
TEST_F(ExifDataTest_39, OperatorBracketReturnsSameDatum_39) {
  exifData_["Exif.Image.Make"] = "TestCamera";
  std::string val = exifData_["Exif.Image.Make"].toString();
  EXPECT_EQ(val, "TestCamera");
}

// Test adding multiple elements via operator[]
TEST_F(ExifDataTest_39, OperatorBracketMultipleElements_39) {
  exifData_["Exif.Image.Make"] = "CameraA";
  exifData_["Exif.Image.Model"] = "ModelB";
  EXPECT_EQ(exifData_.count(), 2u);
}

// Test add with ExifKey and Value
TEST_F(ExifDataTest_39, AddWithKeyAndValue_39) {
  Exiv2::ExifKey key("Exif.Image.Make");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
  value->read("TestValue");
  exifData_.add(key, value.get());
  EXPECT_EQ(exifData_.count(), 1u);
  auto it = exifData_.findKey(key);
  ASSERT_NE(it, exifData_.end());
  EXPECT_EQ(it->toString(), "TestValue");
}

// Test add with Exifdatum
TEST_F(ExifDataTest_39, AddWithExifdatum_39) {
  exifData_["Exif.Image.Make"] = "Original";
  Exiv2::Exifdatum datum = *exifData_.begin();
  Exiv2::ExifData other;
  other.add(datum);
  EXPECT_EQ(other.count(), 1u);
  EXPECT_EQ(other.begin()->toString(), "Original");
}

// Test findKey returns end() when key not found
TEST_F(ExifDataTest_39, FindKeyNotFound_39) {
  Exiv2::ExifKey key("Exif.Image.Make");
  auto it = exifData_.findKey(key);
  EXPECT_EQ(it, exifData_.end());
}

// Test findKey returns valid iterator when key is found
TEST_F(ExifDataTest_39, FindKeyFound_39) {
  exifData_["Exif.Image.Make"] = "Found";
  Exiv2::ExifKey key("Exif.Image.Make");
  auto it = exifData_.findKey(key);
  ASSERT_NE(it, exifData_.end());
  EXPECT_EQ(it->toString(), "Found");
}

// Test const findKey
TEST_F(ExifDataTest_39, FindKeyConst_39) {
  exifData_["Exif.Image.Model"] = "ConstTest";
  const Exiv2::ExifData& constRef = exifData_;
  Exiv2::ExifKey key("Exif.Image.Model");
  auto it = constRef.findKey(key);
  ASSERT_NE(it, constRef.end());
  EXPECT_EQ(it->toString(), "ConstTest");
}

// Test clear empties the data
TEST_F(ExifDataTest_39, ClearRemovesAll_39) {
  exifData_["Exif.Image.Make"] = "A";
  exifData_["Exif.Image.Model"] = "B";
  EXPECT_EQ(exifData_.count(), 2u);
  exifData_.clear();
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase single element
TEST_F(ExifDataTest_39, EraseSingleElement_39) {
  exifData_["Exif.Image.Make"] = "ToErase";
  exifData_["Exif.Image.Model"] = "ToKeep";
  EXPECT_EQ(exifData_.count(), 2u);
  
  Exiv2::ExifKey key("Exif.Image.Make");
  auto it = exifData_.findKey(key);
  ASSERT_NE(it, exifData_.end());
  exifData_.erase(it);
  EXPECT_EQ(exifData_.count(), 1u);
  
  it = exifData_.findKey(key);
  EXPECT_EQ(it, exifData_.end());
}

// Test erase range
TEST_F(ExifDataTest_39, EraseRange_39) {
  exifData_["Exif.Image.Make"] = "A";
  exifData_["Exif.Image.Model"] = "B";
  exifData_["Exif.Image.Software"] = "C";
  EXPECT_EQ(exifData_.count(), 3u);
  
  exifData_.erase(exifData_.begin(), exifData_.end());
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase range with partial range
TEST_F(ExifDataTest_39, ErasePartialRange_39) {
  exifData_["Exif.Image.Make"] = "A";
  exifData_["Exif.Image.Model"] = "B";
  exifData_["Exif.Image.Software"] = "C";
  EXPECT_EQ(exifData_.count(), 3u);
  
  auto beg = exifData_.begin();
  auto end = beg;
  ++end;
  exifData_.erase(beg, end);
  EXPECT_EQ(exifData_.count(), 2u);
}

// Test sortByKey doesn't lose elements
TEST_F(ExifDataTest_39, SortByKeyPreservesCount_39) {
  exifData_["Exif.Image.Software"] = "Soft";
  exifData_["Exif.Image.Make"] = "Make";
  exifData_["Exif.Image.Model"] = "Model";
  size_t countBefore = exifData_.count();
  exifData_.sortByKey();
  EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByTag doesn't lose elements
TEST_F(ExifDataTest_39, SortByTagPreservesCount_39) {
  exifData_["Exif.Image.Software"] = "Soft";
  exifData_["Exif.Image.Make"] = "Make";
  exifData_["Exif.Image.Model"] = "Model";
  size_t countBefore = exifData_.count();
  exifData_.sortByTag();
  EXPECT_EQ(exifData_.count(), countBefore);
}

// Test sortByKey actually sorts
TEST_F(ExifDataTest_39, SortByKeyOrder_39) {
  exifData_["Exif.Image.Software"] = "Soft";
  exifData_["Exif.Image.Make"] = "Make";
  exifData_["Exif.Image.Model"] = "Model";
  exifData_.sortByKey();
  
  std::string prevKey;
  for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
    std::string currentKey = it->key();
    if (!prevKey.empty()) {
      EXPECT_LE(prevKey, currentKey);
    }
    prevKey = currentKey;
  }
}

// Test iterating over elements
TEST_F(ExifDataTest_39, IterateOverElements_39) {
  exifData_["Exif.Image.Make"] = "CamMake";
  exifData_["Exif.Image.Model"] = "CamModel";
  
  size_t count = 0;
  for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 2u);
}

// Test operator[] overwrites existing value
TEST_F(ExifDataTest_39, OperatorBracketOverwrites_39) {
  exifData_["Exif.Image.Make"] = "First";
  EXPECT_EQ(exifData_["Exif.Image.Make"].toString(), "First");
  exifData_["Exif.Image.Make"] = "Second";
  EXPECT_EQ(exifData_["Exif.Image.Make"].toString(), "Second");
  // Count should still be 1 since we're overwriting the same key
  EXPECT_EQ(exifData_.count(), 1u);
}

// Test clear on already empty data
TEST_F(ExifDataTest_39, ClearOnEmpty_39) {
  EXPECT_TRUE(exifData_.empty());
  exifData_.clear();
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
}

// Test erase range with begin == end (no-op)
TEST_F(ExifDataTest_39, EraseEmptyRange_39) {
  exifData_["Exif.Image.Make"] = "Keep";
  auto it = exifData_.begin();
  exifData_.erase(it, it);
  EXPECT_EQ(exifData_.count(), 1u);
}

// Test empty() returns false after adding
TEST_F(ExifDataTest_39, EmptyReturnsFalseAfterAdd_39) {
  Exiv2::ExifKey key("Exif.Image.Make");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
  value->read("Val");
  exifData_.add(key, value.get());
  EXPECT_FALSE(exifData_.empty());
}

// Test that erase returns a valid iterator
TEST_F(ExifDataTest_39, EraseReturnsIterator_39) {
  exifData_["Exif.Image.Make"] = "A";
  exifData_["Exif.Image.Model"] = "B";
  auto it = exifData_.erase(exifData_.begin());
  // The returned iterator should be valid
  EXPECT_EQ(exifData_.count(), 1u);
  if (it != exifData_.end()) {
    EXPECT_FALSE(it->key().empty());
  }
}

// Test adding duplicate keys via add method
TEST_F(ExifDataTest_39, AddDuplicateKeys_39) {
  Exiv2::ExifKey key("Exif.Image.Make");
  Exiv2::Value::UniquePtr value1 = Exiv2::Value::create(Exiv2::asciiString);
  value1->read("First");
  exifData_.add(key, value1.get());
  
  Exiv2::Value::UniquePtr value2 = Exiv2::Value::create(Exiv2::asciiString);
  value2->read("Second");
  exifData_.add(key, value2.get());
  
  // add() may allow duplicates unlike operator[]
  EXPECT_GE(exifData_.count(), 1u);
}

// Test const begin/end
TEST_F(ExifDataTest_39, ConstBeginEnd_39) {
  exifData_["Exif.Image.Make"] = "ConstTest";
  const Exiv2::ExifData& constRef = exifData_;
  size_t count = 0;
  for (auto it = constRef.begin(); it != constRef.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 1u);
}
