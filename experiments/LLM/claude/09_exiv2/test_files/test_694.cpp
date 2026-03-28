#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <string>
#include <memory>

using namespace Exiv2;

class IptcDataTest_694 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that a newly created IptcData is empty
TEST_F(IptcDataTest_694, DefaultConstructedIsEmpty_694) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test adding an entry via key and value increases size
TEST_F(IptcDataTest_694, AddWithKeyAndValueIncreasesSize_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test caption");
    int result = iptcData_.add(key, value.get());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test adding an Iptcdatum directly
TEST_F(IptcDataTest_694, AddIptcdatumIncreasesSize_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test caption");
    Iptcdatum datum(key, value.get());
    int result = iptcData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test adding multiple entries
TEST_F(IptcDataTest_694, AddMultipleEntries_694) {
    IptcKey key1("Iptc.Application2.Caption");
    Value::UniquePtr value1 = Value::create(string);
    value1->read("Caption 1");
    iptcData_.add(key1, value1.get());

    IptcKey key2("Iptc.Application2.Keywords");
    Value::UniquePtr value2 = Value::create(string);
    value2->read("keyword1");
    iptcData_.add(key2, value2.get());

    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test findKey returns valid iterator for existing key
TEST_F(IptcDataTest_694, FindKeyExistingEntry_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test caption");
    iptcData_.add(key, value.get());

    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_NE(it, iptcData_.end());
}

// Test findKey returns end iterator for non-existing key
TEST_F(IptcDataTest_694, FindKeyNonExistingEntry_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test caption");
    iptcData_.add(key, value.get());

    IptcKey searchKey("Iptc.Application2.Keywords");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findKey on empty IptcData
TEST_F(IptcDataTest_694, FindKeyOnEmptyData_694) {
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes an entry
TEST_F(IptcDataTest_694, EraseRemovesEntry_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test caption");
    iptcData_.add(key, value.get());
    EXPECT_EQ(iptcData_.size(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test clear removes all entries
TEST_F(IptcDataTest_694, ClearRemovesAllEntries_694) {
    IptcKey key1("Iptc.Application2.Caption");
    Value::UniquePtr value1 = Value::create(string);
    value1->read("Caption");
    iptcData_.add(key1, value1.get());

    IptcKey key2("Iptc.Application2.Keywords");
    Value::UniquePtr value2 = Value::create(string);
    value2->read("keyword");
    iptcData_.add(key2, value2.get());

    EXPECT_EQ(iptcData_.size(), 2u);
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test operator[] creates entry if it doesn't exist
TEST_F(IptcDataTest_694, OperatorBracketCreatesEntry_694) {
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    // After accessing with operator[], the entry should exist
    // The size should be at least 1
    EXPECT_GE(iptcData_.size(), 1u);
}

// Test operator[] returns existing entry
TEST_F(IptcDataTest_694, OperatorBracketReturnsExisting_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test caption");
    iptcData_.add(key, value.get());

    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test begin and end iterators on empty data
TEST_F(IptcDataTest_694, BeginEqualsEndWhenEmpty_694) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test begin and end iterators on non-empty data
TEST_F(IptcDataTest_694, BeginNotEqualsEndWhenNonEmpty_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test");
    iptcData_.add(key, value.get());
    EXPECT_NE(iptcData_.begin(), iptcData_.end());
}

// Test sortByKey does not change size
TEST_F(IptcDataTest_694, SortByKeyPreservesSize_694) {
    IptcKey key1("Iptc.Application2.Keywords");
    Value::UniquePtr value1 = Value::create(string);
    value1->read("keyword");
    iptcData_.add(key1, value1.get());

    IptcKey key2("Iptc.Application2.Caption");
    Value::UniquePtr value2 = Value::create(string);
    value2->read("caption");
    iptcData_.add(key2, value2.get());

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag does not change size
TEST_F(IptcDataTest_694, SortByTagPreservesSize_694) {
    IptcKey key1("Iptc.Application2.Keywords");
    Value::UniquePtr value1 = Value::create(string);
    value1->read("keyword");
    iptcData_.add(key1, value1.get());

    IptcKey key2("Iptc.Application2.Caption");
    Value::UniquePtr value2 = Value::create(string);
    value2->read("caption");
    iptcData_.add(key2, value2.get());

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test findId for existing dataset and record
TEST_F(IptcDataTest_694, FindIdExistingEntry_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test");
    iptcData_.add(key, value.get());

    uint16_t dataset = key.tag();
    uint16_t record = key.record();
    auto it = iptcData_.findId(dataset, record);
    EXPECT_NE(it, iptcData_.end());
}

// Test findId for non-existing dataset and record
TEST_F(IptcDataTest_694, FindIdNonExistingEntry_694) {
    auto it = iptcData_.findId(9999, 9999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test adding with null value pointer
TEST_F(IptcDataTest_694, AddWithNullValue_694) {
    IptcKey key("Iptc.Application2.Caption");
    int result = iptcData_.add(key, nullptr);
    // Should still succeed or handle gracefully
    // We just check it doesn't crash and returns something
    EXPECT_GE(iptcData_.size(), 0u);
}

// Test count method
TEST_F(IptcDataTest_694, CountMatchesSize_694) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr value = Value::create(string);
    value->read("Test");
    iptcData_.add(key, value.get());

    EXPECT_EQ(iptcData_.count(), iptcData_.size());
}

// Test detectCharset on empty data
TEST_F(IptcDataTest_694, DetectCharsetOnEmptyData_694) {
    const char* charset = iptcData_.detectCharset();
    // May return nullptr or some default value
    // Just ensure it doesn't crash
    (void)charset;
}

// Test adding duplicate keys (Keywords is repeatable)
TEST_F(IptcDataTest_694, AddDuplicateRepeatableKeys_694) {
    IptcKey key1("Iptc.Application2.Keywords");
    Value::UniquePtr value1 = Value::create(string);
    value1->read("keyword1");
    iptcData_.add(key1, value1.get());

    IptcKey key2("Iptc.Application2.Keywords");
    Value::UniquePtr value2 = Value::create(string);
    value2->read("keyword2");
    iptcData_.add(key2, value2.get());

    // Both entries should exist for repeatable datasets
    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test iterator traversal
TEST_F(IptcDataTest_694, IteratorTraversal_694) {
    IptcKey key1("Iptc.Application2.Caption");
    Value::UniquePtr value1 = Value::create(string);
    value1->read("Caption");
    iptcData_.add(key1, value1.get());

    IptcKey key2("Iptc.Application2.Keywords");
    Value::UniquePtr value2 = Value::create(string);
    value2->read("Keyword");
    iptcData_.add(key2, value2.get());

    size_t count = 0;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// Test erase from middle
TEST_F(IptcDataTest_694, EraseFromMiddle_694) {
    IptcKey key1("Iptc.Application2.Caption");
    Value::UniquePtr value1 = Value::create(string);
    value1->read("Caption");
    iptcData_.add(key1, value1.get());

    IptcKey key2("Iptc.Application2.Keywords");
    Value::UniquePtr value2 = Value::create(string);
    value2->read("Keyword");
    iptcData_.add(key2, value2.get());

    IptcKey key3("Iptc.Application2.Byline");
    Value::UniquePtr value3 = Value::create(string);
    value3->read("Author");
    iptcData_.add(key3, value3.get());

    EXPECT_EQ(iptcData_.size(), 3u);

    // Erase second element
    auto it = iptcData_.begin();
    ++it;
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test sortByKey actually sorts
TEST_F(IptcDataTest_694, SortByKeyOrders_694) {
    IptcKey key1("Iptc.Application2.Keywords");
    Value::UniquePtr value1 = Value::create(string);
    value1->read("keyword");
    iptcData_.add(key1, value1.get());

    IptcKey key2("Iptc.Application2.Caption");
    Value::UniquePtr value2 = Value::create(string);
    value2->read("caption");
    iptcData_.add(key2, value2.get());

    iptcData_.sortByKey();

    // After sorting by key, verify ordering
    auto it = iptcData_.begin();
    std::string prevKey = it->key();
    ++it;
    while (it != iptcData_.end()) {
        EXPECT_LE(prevKey, it->key());
        prevKey = it->key();
        ++it;
    }
}

// Test clear on already empty data
TEST_F(IptcDataTest_694, ClearOnEmptyData_694) {
    EXPECT_TRUE(iptcData_.empty());
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}
