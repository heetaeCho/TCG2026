#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <sstream>

namespace {

class IptcDataTest_46 : public ::testing::Test {
 protected:
  Exiv2::IptcData iptcData_;
};

// Test that a newly constructed IptcData is empty
TEST_F(IptcDataTest_46, DefaultConstructedIsEmpty_46) {
  EXPECT_TRUE(iptcData_.empty());
  EXPECT_EQ(iptcData_.size(), 0u);
  EXPECT_EQ(iptcData_.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(IptcDataTest_46, BeginEqualsEndWhenEmpty_46) {
  EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding an Iptcdatum and checking size
TEST_F(IptcDataTest_46, AddIptcdatumIncreasesSize_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
  value->read("Test Caption");
  EXPECT_EQ(iptcData_.add(key, value.get()), 0);
  EXPECT_EQ(iptcData_.size(), 1u);
  EXPECT_FALSE(iptcData_.empty());
}

// Test adding multiple entries
TEST_F(IptcDataTest_46, AddMultipleEntries_46) {
  Exiv2::IptcKey key1("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
  val1->read("Caption 1");
  iptcData_.add(key1, val1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
  val2->read("Keyword 1");
  iptcData_.add(key2, val2.get());

  EXPECT_EQ(iptcData_.size(), 2u);
  EXPECT_EQ(iptcData_.count(), 2u);
}

// Test operator[] creates entry if not found
TEST_F(IptcDataTest_46, OperatorBracketCreatesEntry_46) {
  Exiv2::Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
  // After operator[], the entry should exist
  EXPECT_GE(iptcData_.size(), 1u);
  (void)datum;  // suppress unused warning
}

// Test operator[] returns existing entry
TEST_F(IptcDataTest_46, OperatorBracketReturnsExisting_46) {
  iptcData_["Iptc.Application2.Caption"] = "Hello World";
  Exiv2::Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
  EXPECT_EQ(datum.toString(), "Hello World");
}

// Test findKey for existing key
TEST_F(IptcDataTest_46, FindKeyExisting_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
  val->read("Find me");
  iptcData_.add(key, val.get());

  Exiv2::IptcKey searchKey("Iptc.Application2.Caption");
  auto it = iptcData_.findKey(searchKey);
  EXPECT_NE(it, iptcData_.end());
  EXPECT_EQ(it->toString(), "Find me");
}

// Test findKey for non-existing key
TEST_F(IptcDataTest_46, FindKeyNonExisting_46) {
  Exiv2::IptcKey searchKey("Iptc.Application2.Caption");
  auto it = iptcData_.findKey(searchKey);
  EXPECT_EQ(it, iptcData_.end());
}

// Test findId for existing dataset/record
TEST_F(IptcDataTest_46, FindIdExisting_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
  val->read("Caption text");
  iptcData_.add(key, val.get());

  // Caption is dataset 120, record 2
  auto it = iptcData_.findId(120, 2);
  EXPECT_NE(it, iptcData_.end());
}

// Test findId for non-existing dataset/record
TEST_F(IptcDataTest_46, FindIdNonExisting_46) {
  auto it = iptcData_.findId(9999, 9999);
  EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes an entry
TEST_F(IptcDataTest_46, EraseRemovesEntry_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
  val->read("To be erased");
  iptcData_.add(key, val.get());
  EXPECT_EQ(iptcData_.size(), 1u);

  auto it = iptcData_.begin();
  iptcData_.erase(it);
  EXPECT_EQ(iptcData_.size(), 0u);
  EXPECT_TRUE(iptcData_.empty());
}

// Test clear empties the container
TEST_F(IptcDataTest_46, ClearEmptiesContainer_46) {
  Exiv2::IptcKey key1("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
  val1->read("Caption");
  iptcData_.add(key1, val1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
  val2->read("Keyword");
  iptcData_.add(key2, val2.get());

  EXPECT_EQ(iptcData_.size(), 2u);
  iptcData_.clear();
  EXPECT_TRUE(iptcData_.empty());
  EXPECT_EQ(iptcData_.size(), 0u);
}

// Test sortByKey does not crash and maintains entries
TEST_F(IptcDataTest_46, SortByKeyMaintainsEntries_46) {
  Exiv2::IptcKey key1("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
  val1->read("Keyword");
  iptcData_.add(key1, val1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
  val2->read("Caption");
  iptcData_.add(key2, val2.get());

  iptcData_.sortByKey();
  EXPECT_EQ(iptcData_.size(), 2u);
}

// Test sortByTag does not crash and maintains entries
TEST_F(IptcDataTest_46, SortByTagMaintainsEntries_46) {
  Exiv2::IptcKey key1("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
  val1->read("Keyword");
  iptcData_.add(key1, val1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
  val2->read("Caption");
  iptcData_.add(key2, val2.get());

  iptcData_.sortByTag();
  EXPECT_EQ(iptcData_.size(), 2u);
}

// Test sortByKey produces sorted order
TEST_F(IptcDataTest_46, SortByKeyProducesSortedOrder_46) {
  Exiv2::IptcKey key1("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
  val1->read("Keyword");
  iptcData_.add(key1, val1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
  val2->read("Caption");
  iptcData_.add(key2, val2.get());

  iptcData_.sortByKey();

  // After sorting by key, entries should be in alphabetical key order
  auto it = iptcData_.begin();
  std::string prevKey = it->key();
  ++it;
  while (it != iptcData_.end()) {
    EXPECT_LE(prevKey, it->key());
    prevKey = it->key();
    ++it;
  }
}

// Test adding duplicate keywords (IPTC allows repeatable fields)
TEST_F(IptcDataTest_46, AddDuplicateRepeatableField_46) {
  Exiv2::IptcKey key1("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
  val1->read("Keyword1");
  iptcData_.add(key1, val1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
  val2->read("Keyword2");
  iptcData_.add(key2, val2.get());

  EXPECT_EQ(iptcData_.size(), 2u);
}

// Test detectCharset on empty data
TEST_F(IptcDataTest_46, DetectCharsetOnEmptyData_46) {
  const char* charset = iptcData_.detectCharset();
  // Empty IPTC data - charset detection returns null or some default
  // We just verify it doesn't crash
  (void)charset;
}

// Test detectCharset with data present
TEST_F(IptcDataTest_46, DetectCharsetWithData_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
  val->read("Simple ASCII text");
  iptcData_.add(key, val.get());

  const char* charset = iptcData_.detectCharset();
  // Just verify it doesn't crash; charset could be nullptr or a valid string
  (void)charset;
}

// Test iteration over entries
TEST_F(IptcDataTest_46, IterationOverEntries_46) {
  Exiv2::IptcKey key1("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
  val1->read("Caption");
  iptcData_.add(key1, val1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
  val2->read("Keyword");
  iptcData_.add(key2, val2.get());

  size_t count = 0;
  for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 2u);
}

// Test erase returns valid iterator
TEST_F(IptcDataTest_46, EraseReturnsValidIterator_46) {
  Exiv2::IptcKey key1("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
  val1->read("Caption");
  iptcData_.add(key1, val1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
  val2->read("Keyword");
  iptcData_.add(key2, val2.get());

  auto it = iptcData_.begin();
  auto nextIt = iptcData_.erase(it);
  // After erasing first element, nextIt should be valid
  EXPECT_EQ(iptcData_.size(), 1u);
  if (nextIt != iptcData_.end()) {
    // The remaining element should be accessible
    EXPECT_FALSE(nextIt->key().empty());
  }
}

// Test adding via Iptcdatum object
TEST_F(IptcDataTest_46, AddViaIptcdatum_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Iptcdatum datum(key);
  datum.setValue("Test value");
  int result = iptcData_.add(datum);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(iptcData_.size(), 1u);
}

// Test clear on already empty container
TEST_F(IptcDataTest_46, ClearOnEmptyContainer_46) {
  EXPECT_TRUE(iptcData_.empty());
  iptcData_.clear();
  EXPECT_TRUE(iptcData_.empty());
  EXPECT_EQ(iptcData_.size(), 0u);
}

// Test const findKey
TEST_F(IptcDataTest_46, ConstFindKey_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
  val->read("Test");
  iptcData_.add(key, val.get());

  const Exiv2::IptcData& constData = iptcData_;
  Exiv2::IptcKey searchKey("Iptc.Application2.Caption");
  auto it = constData.findKey(searchKey);
  EXPECT_NE(it, constData.end());
  EXPECT_EQ(it->toString(), "Test");
}

// Test const findId
TEST_F(IptcDataTest_46, ConstFindId_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
  val->read("Test");
  iptcData_.add(key, val.get());

  const Exiv2::IptcData& constData = iptcData_;
  // Caption is dataset 120, record 2
  auto it = constData.findId(120, 2);
  EXPECT_NE(it, constData.end());
}

// Test empty() const qualifier
TEST_F(IptcDataTest_46, EmptyIsConst_46) {
  const Exiv2::IptcData& constData = iptcData_;
  EXPECT_TRUE(constData.empty());
}

// Test count() const qualifier
TEST_F(IptcDataTest_46, CountIsConst_46) {
  const Exiv2::IptcData& constData = iptcData_;
  EXPECT_EQ(constData.count(), 0u);
}

// Test size() const qualifier
TEST_F(IptcDataTest_46, SizeIsConst_46) {
  const Exiv2::IptcData& constData = iptcData_;
  EXPECT_EQ(constData.size(), 0u);
}

// Test that findKey after erase returns end()
TEST_F(IptcDataTest_46, FindKeyAfterEraseReturnsEnd_46) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
  val->read("To erase");
  iptcData_.add(key, val.get());

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  EXPECT_NE(it, iptcData_.end());

  iptcData_.erase(it);

  auto it2 = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  EXPECT_EQ(it2, iptcData_.end());
}

}  // namespace
