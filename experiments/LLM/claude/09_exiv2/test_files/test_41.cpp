#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

class ExifDataTest_41 : public ::testing::Test {
 protected:
  Exiv2::ExifData exifData_;
};

TEST_F(ExifDataTest_41, DefaultConstructedIsEmpty_41) {
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
}

TEST_F(ExifDataTest_41, BeginEqualsEndWhenEmpty_41) {
  EXPECT_EQ(exifData_.begin(), exifData_.end());
}

TEST_F(ExifDataTest_41, AddWithKeyAndValueIncreasesCount_41) {
  Exiv2::ExifKey key("Exif.Image.Make");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
  value->read("Canon");
  exifData_.add(key, value.get());

  EXPECT_FALSE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 1u);
}

TEST_F(ExifDataTest_41, AddExifdatumIncreasesCount_41) {
  exifData_["Exif.Image.Make"] = "Nikon";

  EXPECT_FALSE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 1u);
}

TEST_F(ExifDataTest_41, OperatorBracketCreatesEntry_41) {
  exifData_["Exif.Image.Model"] = "D850";

  EXPECT_EQ(exifData_.count(), 1u);
  auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));
  ASSERT_NE(it, exifData_.end());
  EXPECT_EQ(it->toString(), "D850");
}

TEST_F(ExifDataTest_41, OperatorBracketUpdatesExistingEntry_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Image.Make"] = "Nikon";

  EXPECT_EQ(exifData_.count(), 1u);
  auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData_.end());
  EXPECT_EQ(it->toString(), "Nikon");
}

TEST_F(ExifDataTest_41, FindKeyReturnsEndForNonExistentKey_41) {
  auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  EXPECT_EQ(it, exifData_.end());
}

TEST_F(ExifDataTest_41, FindKeyReturnsValidIteratorForExistingKey_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData_.end());
  EXPECT_EQ(it->key(), "Exif.Image.Make");
}

TEST_F(ExifDataTest_41, ClearRemovesAllEntries_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Image.Model"] = "EOS R5";
  EXPECT_EQ(exifData_.count(), 2u);

  exifData_.clear();
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
  EXPECT_EQ(exifData_.begin(), exifData_.end());
}

TEST_F(ExifDataTest_41, EraseSingleElement_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Image.Model"] = "EOS R5";
  EXPECT_EQ(exifData_.count(), 2u);

  auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, exifData_.end());
  exifData_.erase(it);

  EXPECT_EQ(exifData_.count(), 1u);
  EXPECT_EQ(exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make")), exifData_.end());
}

TEST_F(ExifDataTest_41, EraseRange_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Image.Model"] = "EOS R5";
  exifData_["Exif.Image.Software"] = "Exiv2";
  EXPECT_EQ(exifData_.count(), 3u);

  exifData_.erase(exifData_.begin(), exifData_.end());
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
}

TEST_F(ExifDataTest_41, EraseEmptyRange_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  auto it = exifData_.begin();
  exifData_.erase(it, it);
  EXPECT_EQ(exifData_.count(), 1u);
}

TEST_F(ExifDataTest_41, SortByKeyDoesNotChangeCount_41) {
  exifData_["Exif.Image.Model"] = "EOS R5";
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";

  size_t countBefore = exifData_.count();
  exifData_.sortByKey();
  EXPECT_EQ(exifData_.count(), countBefore);
}

TEST_F(ExifDataTest_41, SortByKeyOrdersCorrectly_41) {
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Image.Model"] = "EOS R5";

  exifData_.sortByKey();

  std::string prevKey;
  for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
    if (!prevKey.empty()) {
      EXPECT_LE(prevKey, it->key());
    }
    prevKey = it->key();
  }
}

TEST_F(ExifDataTest_41, SortByTagDoesNotChangeCount_41) {
  exifData_["Exif.Image.Model"] = "EOS R5";
  exifData_["Exif.Image.Make"] = "Canon";

  size_t countBefore = exifData_.count();
  exifData_.sortByTag();
  EXPECT_EQ(exifData_.count(), countBefore);
}

TEST_F(ExifDataTest_41, AddMultipleEntriesAndIterate_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Image.Model"] = "EOS R5";
  exifData_["Exif.Image.Software"] = "Exiv2";

  EXPECT_EQ(exifData_.count(), 3u);

  size_t iterCount = 0;
  for (auto it = exifData_.begin(); it != exifData_.end(); ++it) {
    ++iterCount;
  }
  EXPECT_EQ(iterCount, 3u);
}

TEST_F(ExifDataTest_41, AddWithExifdatum_41) {
  Exiv2::ExifData other;
  other["Exif.Image.Make"] = "Sony";

  auto it = other.begin();
  ASSERT_NE(it, other.end());

  exifData_.add(*it);
  EXPECT_EQ(exifData_.count(), 1u);

  auto found = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(found, exifData_.end());
  EXPECT_EQ(found->toString(), "Sony");
}

TEST_F(ExifDataTest_41, ConstFindKeyOnConstObject_41) {
  exifData_["Exif.Image.Make"] = "Canon";

  const Exiv2::ExifData& constRef = exifData_;
  auto it = constRef.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, constRef.end());
  EXPECT_EQ(it->toString(), "Canon");
}

TEST_F(ExifDataTest_41, ConstFindKeyReturnsEndForMissing_41) {
  const Exiv2::ExifData& constRef = exifData_;
  auto it = constRef.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  EXPECT_EQ(it, constRef.end());
}

TEST_F(ExifDataTest_41, EmptyAfterClearOnNonEmpty_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  EXPECT_FALSE(exifData_.empty());
  exifData_.clear();
  EXPECT_TRUE(exifData_.empty());
}

TEST_F(ExifDataTest_41, ClearOnAlreadyEmptyIsNoOp_41) {
  EXPECT_TRUE(exifData_.empty());
  exifData_.clear();
  EXPECT_TRUE(exifData_.empty());
  EXPECT_EQ(exifData_.count(), 0u);
}

TEST_F(ExifDataTest_41, SortByKeyOnEmptyDataIsNoOp_41) {
  EXPECT_NO_THROW(exifData_.sortByKey());
  EXPECT_TRUE(exifData_.empty());
}

TEST_F(ExifDataTest_41, SortByTagOnEmptyDataIsNoOp_41) {
  EXPECT_NO_THROW(exifData_.sortByTag());
  EXPECT_TRUE(exifData_.empty());
}

TEST_F(ExifDataTest_41, SortByKeyOnSingleElement_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  EXPECT_NO_THROW(exifData_.sortByKey());
  EXPECT_EQ(exifData_.count(), 1u);
}

TEST_F(ExifDataTest_41, EraseReturnsValidIterator_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Image.Model"] = "EOS R5";

  auto it = exifData_.erase(exifData_.begin());
  EXPECT_EQ(exifData_.count(), 1u);
  // The returned iterator should be valid (either pointing to next element or end)
  if (exifData_.count() > 0) {
    EXPECT_EQ(it, exifData_.begin());
  }
}

TEST_F(ExifDataTest_41, AddWithKeyAndNullptrValue_41) {
  Exiv2::ExifKey key("Exif.Image.Make");
  // Adding with nullptr value - testing boundary behavior
  // This may throw or handle gracefully depending on implementation
  try {
    exifData_.add(key, nullptr);
  } catch (...) {
    // If it throws, that's acceptable boundary behavior
  }
}

TEST_F(ExifDataTest_41, MultipleAddAndEraseCycles_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  EXPECT_EQ(exifData_.count(), 1u);

  exifData_.erase(exifData_.begin());
  EXPECT_EQ(exifData_.count(), 0u);
  EXPECT_TRUE(exifData_.empty());

  exifData_["Exif.Image.Model"] = "EOS R5";
  EXPECT_EQ(exifData_.count(), 1u);
  EXPECT_FALSE(exifData_.empty());
}

TEST_F(ExifDataTest_41, CopyConstructor_41) {
  exifData_["Exif.Image.Make"] = "Canon";
  exifData_["Exif.Image.Model"] = "EOS R5";

  Exiv2::ExifData copy(exifData_);
  EXPECT_EQ(copy.count(), 2u);
  EXPECT_FALSE(copy.empty());

  auto it = copy.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, copy.end());
  EXPECT_EQ(it->toString(), "Canon");
}

TEST_F(ExifDataTest_41, AssignmentOperator_41) {
  exifData_["Exif.Image.Make"] = "Canon";

  Exiv2::ExifData other;
  other = exifData_;
  EXPECT_EQ(other.count(), 1u);

  auto it = other.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(it, other.end());
  EXPECT_EQ(it->toString(), "Canon");
}
