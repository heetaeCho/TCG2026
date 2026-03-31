#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcDataTest_48 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that a newly constructed IptcData is empty
TEST_F(IptcDataTest_48, DefaultConstructorCreatesEmptyContainer_48) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.count(), 0u);
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(IptcDataTest_48, BeginEqualsEndWhenEmpty_48) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding an Iptcdatum increases count
TEST_F(IptcDataTest_48, AddIptcdatumIncreasesCount_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    EXPECT_EQ(iptcData_.add(key, &value), 0);
    EXPECT_EQ(iptcData_.count(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test adding multiple entries
TEST_F(IptcDataTest_48, AddMultipleEntries_48) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("Caption 1");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword1");
    iptcData_.add(key2, &value2);

    EXPECT_EQ(iptcData_.count(), 2u);
    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test operator[] creates entry if not present
TEST_F(IptcDataTest_48, OperatorBracketCreatesEntry_48) {
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    // After using operator[], the entry should exist
    EXPECT_GE(iptcData_.count(), 1u);
}

// Test operator[] returns existing entry
TEST_F(IptcDataTest_48, OperatorBracketReturnsExistingEntry_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Hello");
    iptcData_.add(key, &value);

    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.toString(), "Hello");
}

// Test findKey on existing key
TEST_F(IptcDataTest_48, FindKeyExistingKey_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Found me");
    iptcData_.add(key, &value);

    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Found me");
}

// Test findKey on non-existing key
TEST_F(IptcDataTest_48, FindKeyNonExistingKey_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Something");
    iptcData_.add(key, &value);

    IptcKey searchKey("Iptc.Application2.Keywords");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findKey on empty container
TEST_F(IptcDataTest_48, FindKeyOnEmptyContainer_48) {
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId with existing dataset and record
TEST_F(IptcDataTest_48, FindIdExisting_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    iptcData_.add(key, &value);

    // Caption is dataset 120, record 2
    auto it = iptcData_.findId(IptcDataSets::Caption, IptcDataSets::application2);
    EXPECT_NE(it, iptcData_.end());
}

// Test findId with non-existing dataset
TEST_F(IptcDataTest_48, FindIdNonExisting_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    iptcData_.add(key, &value);

    // Keywords is dataset 25
    auto it = iptcData_.findId(IptcDataSets::Keywords, IptcDataSets::application2);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes an entry
TEST_F(IptcDataTest_48, EraseRemovesEntry_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("To be erased");
    iptcData_.add(key, &value);

    EXPECT_EQ(iptcData_.count(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);

    EXPECT_EQ(iptcData_.count(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test erase from middle of multiple entries
TEST_F(IptcDataTest_48, EraseFromMiddle_48) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("First");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("Second");
    iptcData_.add(key2, &value2);

    IptcKey key3("Iptc.Application2.City");
    StringValue value3;
    value3.read("Third");
    iptcData_.add(key3, &value3);

    EXPECT_EQ(iptcData_.count(), 3u);

    auto it = iptcData_.begin();
    ++it; // point to second element
    iptcData_.erase(it);

    EXPECT_EQ(iptcData_.count(), 2u);
}

// Test clear removes all entries
TEST_F(IptcDataTest_48, ClearRemovesAllEntries_48) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("Entry 1");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("Entry 2");
    iptcData_.add(key2, &value2);

    EXPECT_EQ(iptcData_.count(), 2u);

    iptcData_.clear();

    EXPECT_EQ(iptcData_.count(), 0u);
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test clear on already empty container
TEST_F(IptcDataTest_48, ClearOnEmptyContainer_48) {
    EXPECT_TRUE(iptcData_.empty());
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test sortByKey does not change count
TEST_F(IptcDataTest_48, SortByKeyDoesNotChangeCount_48) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("Keyword");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("Caption");
    iptcData_.add(key2, &value2);

    size_t countBefore = iptcData_.count();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.count(), countBefore);
}

// Test sortByTag does not change count
TEST_F(IptcDataTest_48, SortByTagDoesNotChangeCount_48) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("Keyword");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("Caption");
    iptcData_.add(key2, &value2);

    size_t countBefore = iptcData_.count();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.count(), countBefore);
}

// Test sortByKey actually sorts
TEST_F(IptcDataTest_48, SortByKeyOrdersCorrectly_48) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("Keyword");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("Caption");
    iptcData_.add(key2, &value2);

    iptcData_.sortByKey();

    auto it = iptcData_.begin();
    std::string firstKey = it->key();
    ++it;
    std::string secondKey = it->key();
    EXPECT_LE(firstKey, secondKey);
}

// Test adding duplicate keys (IPTC allows repeatable datasets like Keywords)
TEST_F(IptcDataTest_48, AddDuplicateKeywords_48) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword1");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword2");
    iptcData_.add(key2, &value2);

    EXPECT_EQ(iptcData_.count(), 2u);
}

// Test detectCharset on empty container
TEST_F(IptcDataTest_48, DetectCharsetOnEmpty_48) {
    const char* charset = iptcData_.detectCharset();
    // On empty data, detectCharset may return nullptr or some default
    // We just ensure it doesn't crash
    (void)charset;
}

// Test detectCharset with data
TEST_F(IptcDataTest_48, DetectCharsetWithData_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("ASCII text");
    iptcData_.add(key, &value);

    const char* charset = iptcData_.detectCharset();
    // We can't assume a specific return value, but it should not crash
    (void)charset;
}

// Test size equals count
TEST_F(IptcDataTest_48, SizeEqualsCount_48) {
    EXPECT_EQ(iptcData_.size(), iptcData_.count());

    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    iptcData_.add(key, &value);

    EXPECT_EQ(iptcData_.size(), iptcData_.count());
}

// Test iteration over entries
TEST_F(IptcDataTest_48, IterationOverEntries_48) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("Caption");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("Keyword");
    iptcData_.add(key2, &value2);

    size_t iterCount = 0;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        ++iterCount;
    }
    EXPECT_EQ(iterCount, 2u);
}

// Test const findKey on const object
TEST_F(IptcDataTest_48, ConstFindKey_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Const test");
    iptcData_.add(key, &value);

    const IptcData& constRef = iptcData_;
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = constRef.findKey(searchKey);
    EXPECT_NE(it, constRef.end());
    EXPECT_EQ(it->toString(), "Const test");
}

// Test const findId on const object
TEST_F(IptcDataTest_48, ConstFindId_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Const ID test");
    iptcData_.add(key, &value);

    const IptcData& constRef = iptcData_;
    auto it = constRef.findId(IptcDataSets::Caption, IptcDataSets::application2);
    EXPECT_NE(it, constRef.end());
}

// Test add returns 0 on success
TEST_F(IptcDataTest_48, AddReturnsZeroOnSuccess_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Success");
    int result = iptcData_.add(key, &value);
    EXPECT_EQ(result, 0);
}

// Test adding with Iptcdatum overload
TEST_F(IptcDataTest_48, AddWithIptcdatum_48) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Datum value");
    int result = iptcData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test erase returns valid iterator
TEST_F(IptcDataTest_48, EraseReturnsValidIterator_48) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("First");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("Second");
    iptcData_.add(key2, &value2);

    auto it = iptcData_.erase(iptcData_.begin());
    EXPECT_EQ(iptcData_.count(), 1u);
    // The returned iterator should be valid
    if (it != iptcData_.end()) {
        EXPECT_FALSE(it->key().empty());
    }
}

// Test sortByKey on empty container does not crash
TEST_F(IptcDataTest_48, SortByKeyOnEmpty_48) {
    EXPECT_NO_THROW(iptcData_.sortByKey());
    EXPECT_TRUE(iptcData_.empty());
}

// Test sortByTag on empty container does not crash
TEST_F(IptcDataTest_48, SortByTagOnEmpty_48) {
    EXPECT_NO_THROW(iptcData_.sortByTag());
    EXPECT_TRUE(iptcData_.empty());
}

// Test single element sort
TEST_F(IptcDataTest_48, SortByKeySingleElement_48) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Only one");
    iptcData_.add(key, &value);

    EXPECT_NO_THROW(iptcData_.sortByKey());
    EXPECT_EQ(iptcData_.count(), 1u);
    EXPECT_EQ(iptcData_.begin()->toString(), "Only one");
}
