#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

namespace {

class IptcDataTest_47 : public ::testing::Test {
 protected:
  Exiv2::IptcData iptcData_;
};

// Test that a newly constructed IptcData is empty
TEST_F(IptcDataTest_47, DefaultConstructedIsEmpty_47) {
  EXPECT_TRUE(iptcData_.empty());
  EXPECT_EQ(iptcData_.size(), 0u);
  EXPECT_EQ(iptcData_.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(IptcDataTest_47, BeginEqualsEndWhenEmpty_47) {
  EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding an Iptcdatum via add(IptcKey, Value*)
TEST_F(IptcDataTest_47, AddWithKeyAndValue_47) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
  value->read("Test caption");
  int result = iptcData_.add(key, value.get());
  EXPECT_EQ(result, 0);
  EXPECT_FALSE(iptcData_.empty());
  EXPECT_EQ(iptcData_.size(), 1u);
}

// Test adding an Iptcdatum via add(Iptcdatum)
TEST_F(IptcDataTest_47, AddWithIptcdatum_47) {
  Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
  datum.setValue("Hello World");
  int result = iptcData_.add(datum);
  EXPECT_EQ(result, 0);
  EXPECT_FALSE(iptcData_.empty());
  EXPECT_EQ(iptcData_.size(), 1u);
}

// Test operator[] creates entry if it doesn't exist
TEST_F(IptcDataTest_47, OperatorBracketCreatesEntry_47) {
  iptcData_["Iptc.Application2.Caption"] = "Some value";
  EXPECT_FALSE(iptcData_.empty());
  EXPECT_GE(iptcData_.size(), 1u);
}

// Test operator[] retrieves existing entry
TEST_F(IptcDataTest_47, OperatorBracketRetrievesExisting_47) {
  iptcData_["Iptc.Application2.Caption"] = "Value1";
  std::string val = iptcData_["Iptc.Application2.Caption"].toString();
  EXPECT_EQ(val, "Value1");
}

// Test findKey on existing key
TEST_F(IptcDataTest_47, FindKeyExisting_47) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
  value->read("FindMe");
  iptcData_.add(key, value.get());

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  ASSERT_NE(it, iptcData_.end());
  EXPECT_EQ(it->toString(), "FindMe");
}

// Test findKey on non-existing key returns end
TEST_F(IptcDataTest_47, FindKeyNonExisting_47) {
  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  EXPECT_EQ(it, iptcData_.end());
}

// Test findId on existing dataset/record
TEST_F(IptcDataTest_47, FindIdExisting_47) {
  // Iptc.Application2.Caption is dataset 120, record 2
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
  value->read("FindById");
  iptcData_.add(key, value.get());

  auto it = iptcData_.findId(120, 2);
  ASSERT_NE(it, iptcData_.end());
  EXPECT_EQ(it->toString(), "FindById");
}

// Test findId on non-existing returns end
TEST_F(IptcDataTest_47, FindIdNonExisting_47) {
  auto it = iptcData_.findId(9999, 9999);
  EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes an element
TEST_F(IptcDataTest_47, EraseRemovesElement_47) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
  value->read("ToBeErased");
  iptcData_.add(key, value.get());
  ASSERT_EQ(iptcData_.size(), 1u);

  auto it = iptcData_.begin();
  iptcData_.erase(it);
  EXPECT_TRUE(iptcData_.empty());
  EXPECT_EQ(iptcData_.size(), 0u);
}

// Test clear empties the container
TEST_F(IptcDataTest_47, ClearEmptiesContainer_47) {
  Exiv2::IptcKey key1("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value1 = Exiv2::Value::create(Exiv2::string);
  value1->read("Val1");
  iptcData_.add(key1, value1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr value2 = Exiv2::Value::create(Exiv2::string);
  value2->read("Val2");
  iptcData_.add(key2, value2.get());

  ASSERT_EQ(iptcData_.size(), 2u);
  iptcData_.clear();
  EXPECT_TRUE(iptcData_.empty());
  EXPECT_EQ(iptcData_.size(), 0u);
}

// Test adding multiple entries with the same key (IPTC allows repeatable fields)
TEST_F(IptcDataTest_47, AddMultipleSameKey_47) {
  Exiv2::IptcKey key("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr value1 = Exiv2::Value::create(Exiv2::string);
  value1->read("Keyword1");
  iptcData_.add(key, value1.get());

  Exiv2::Value::UniquePtr value2 = Exiv2::Value::create(Exiv2::string);
  value2->read("Keyword2");
  iptcData_.add(key, value2.get());

  EXPECT_EQ(iptcData_.size(), 2u);
}

// Test count returns the number of elements
TEST_F(IptcDataTest_47, CountReturnsCorrectNumber_47) {
  EXPECT_EQ(iptcData_.count(), 0u);

  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
  value->read("CountTest");
  iptcData_.add(key, value.get());

  EXPECT_EQ(iptcData_.count(), 1u);
}

// Test sortByKey does not crash and preserves size
TEST_F(IptcDataTest_47, SortByKeyPreservesSize_47) {
  Exiv2::IptcKey key1("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr v1 = Exiv2::Value::create(Exiv2::string);
  v1->read("B");
  iptcData_.add(key1, v1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr v2 = Exiv2::Value::create(Exiv2::string);
  v2->read("A");
  iptcData_.add(key2, v2.get());

  size_t sizeBefore = iptcData_.size();
  iptcData_.sortByKey();
  EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag does not crash and preserves size
TEST_F(IptcDataTest_47, SortByTagPreservesSize_47) {
  Exiv2::IptcKey key1("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr v1 = Exiv2::Value::create(Exiv2::string);
  v1->read("B");
  iptcData_.add(key1, v1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr v2 = Exiv2::Value::create(Exiv2::string);
  v2->read("A");
  iptcData_.add(key2, v2.get());

  size_t sizeBefore = iptcData_.size();
  iptcData_.sortByTag();
  EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByKey on empty container doesn't crash
TEST_F(IptcDataTest_47, SortByKeyOnEmpty_47) {
  EXPECT_NO_THROW(iptcData_.sortByKey());
}

// Test sortByTag on empty container doesn't crash
TEST_F(IptcDataTest_47, SortByTagOnEmpty_47) {
  EXPECT_NO_THROW(iptcData_.sortByTag());
}

// Test detectCharset on empty returns something or null
TEST_F(IptcDataTest_47, DetectCharsetOnEmpty_47) {
  const char* charset = iptcData_.detectCharset();
  // On empty data, detectCharset may return nullptr
  // We just ensure it doesn't crash
  (void)charset;
}

// Test iteration over multiple entries
TEST_F(IptcDataTest_47, IterateOverEntries_47) {
  Exiv2::IptcKey key1("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr v1 = Exiv2::Value::create(Exiv2::string);
  v1->read("Caption");
  iptcData_.add(key1, v1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr v2 = Exiv2::Value::create(Exiv2::string);
  v2->read("Keyword");
  iptcData_.add(key2, v2.get());

  size_t count = 0;
  for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 2u);
}

// Test erase returns valid iterator
TEST_F(IptcDataTest_47, EraseReturnsValidIterator_47) {
  Exiv2::IptcKey key1("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr v1 = Exiv2::Value::create(Exiv2::string);
  v1->read("First");
  iptcData_.add(key1, v1.get());

  Exiv2::IptcKey key2("Iptc.Application2.Keywords");
  Exiv2::Value::UniquePtr v2 = Exiv2::Value::create(Exiv2::string);
  v2->read("Second");
  iptcData_.add(key2, v2.get());

  auto it = iptcData_.erase(iptcData_.begin());
  EXPECT_EQ(iptcData_.size(), 1u);
  // The returned iterator should be valid (either points to next element or end)
  if (it != iptcData_.end()) {
    EXPECT_FALSE(it->toString().empty());
  }
}

// Test const findKey
TEST_F(IptcDataTest_47, ConstFindKey_47) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
  value->read("ConstFind");
  iptcData_.add(key, value.get());

  const Exiv2::IptcData& constData = iptcData_;
  auto it = constData.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  ASSERT_NE(it, constData.end());
  EXPECT_EQ(it->toString(), "ConstFind");
}

// Test const findId
TEST_F(IptcDataTest_47, ConstFindId_47) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
  value->read("ConstFindId");
  iptcData_.add(key, value.get());

  const Exiv2::IptcData& constData = iptcData_;
  // Caption is dataset 120, record 2
  auto it = constData.findId(120, 2);
  ASSERT_NE(it, constData.end());
  EXPECT_EQ(it->toString(), "ConstFindId");
}

// Test clear on already empty container
TEST_F(IptcDataTest_47, ClearOnEmptyContainer_47) {
  EXPECT_NO_THROW(iptcData_.clear());
  EXPECT_TRUE(iptcData_.empty());
}

// Test adding and then clearing and adding again
TEST_F(IptcDataTest_47, AddClearAddAgain_47) {
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr v1 = Exiv2::Value::create(Exiv2::string);
  v1->read("First");
  iptcData_.add(key, v1.get());
  EXPECT_EQ(iptcData_.size(), 1u);

  iptcData_.clear();
  EXPECT_TRUE(iptcData_.empty());

  Exiv2::Value::UniquePtr v2 = Exiv2::Value::create(Exiv2::string);
  v2->read("Second");
  iptcData_.add(key, v2.get());
  EXPECT_EQ(iptcData_.size(), 1u);
  EXPECT_FALSE(iptcData_.empty());
}

}  // namespace
