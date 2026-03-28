#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcDataTest_698 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that a newly created IptcData is empty
TEST_F(IptcDataTest_698, DefaultConstructedIsEmpty_698) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(IptcDataTest_698, BeginEqualsEndWhenEmpty_698) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding an Iptcdatum and verifying size increases
TEST_F(IptcDataTest_698, AddIptcdatumIncreasesSize_698) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    EXPECT_EQ(iptcData_.add(key, &value), 0);
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test adding multiple entries
TEST_F(IptcDataTest_698, AddMultipleEntries_698) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("Caption 1");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword1");
    iptcData_.add(key2, &value2);

    EXPECT_EQ(iptcData_.size(), 2u);
    EXPECT_EQ(iptcData_.count(), 2u);
}

// Test operator[] creates entry if not found
TEST_F(IptcDataTest_698, OperatorBracketCreatesEntry_698) {
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    // After accessing via operator[], the entry should exist
    EXPECT_GE(iptcData_.size(), 1u);
}

// Test operator[] returns existing entry
TEST_F(IptcDataTest_698, OperatorBracketReturnsExistingEntry_698) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    iptcData_.add(key, &value);

    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.toString(), "Test caption");
}

// Test findKey on existing key
TEST_F(IptcDataTest_698, FindKeyExistingEntry_698) {
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
TEST_F(IptcDataTest_698, FindKeyNonExistingEntry_698) {
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId on existing entry
TEST_F(IptcDataTest_698, FindIdExistingEntry_698) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Caption by ID");
    iptcData_.add(key, &value);

    // Caption is dataset 120, record 2
    auto it = iptcData_.findId(120, 2);
    EXPECT_NE(it, iptcData_.end());
}

// Test findId on non-existing entry
TEST_F(IptcDataTest_698, FindIdNonExistingEntry_698) {
    auto it = iptcData_.findId(9999, 9999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes an entry
TEST_F(IptcDataTest_698, EraseRemovesEntry_698) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("To be erased");
    iptcData_.add(key, &value);
    EXPECT_EQ(iptcData_.size(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test clear removes all entries
TEST_F(IptcDataTest_698, ClearRemovesAllEntries_698) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("Caption");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword");
    iptcData_.add(key2, &value2);

    EXPECT_EQ(iptcData_.size(), 2u);
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test sortByKey does not change size
TEST_F(IptcDataTest_698, SortByKeyPreservesSize_698) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("caption");
    iptcData_.add(key2, &value2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByKey actually sorts entries by key
TEST_F(IptcDataTest_698, SortByKeyOrdersCorrectly_698) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("caption");
    iptcData_.add(key2, &value2);

    iptcData_.sortByKey();

    // After sorting by key, entries should be in key order
    auto it = iptcData_.begin();
    std::string prevKey = it->key();
    ++it;
    while (it != iptcData_.end()) {
        EXPECT_LE(prevKey, it->key());
        prevKey = it->key();
        ++it;
    }
}

// Test sortByTag does not change size
TEST_F(IptcDataTest_698, SortByTagPreservesSize_698) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("caption");
    iptcData_.add(key2, &value2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag orders by tag
TEST_F(IptcDataTest_698, SortByTagOrdersCorrectly_698) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("caption");
    iptcData_.add(key2, &value2);

    iptcData_.sortByTag();

    auto it = iptcData_.begin();
    uint16_t prevTag = it->tag();
    ++it;
    while (it != iptcData_.end()) {
        EXPECT_LE(prevTag, it->tag());
        prevTag = it->tag();
        ++it;
    }
}

// Test sortByKey on empty data does not crash
TEST_F(IptcDataTest_698, SortByKeyEmptyNoCrash_698) {
    EXPECT_NO_THROW(iptcData_.sortByKey());
}

// Test sortByTag on empty data does not crash
TEST_F(IptcDataTest_698, SortByTagEmptyNoCrash_698) {
    EXPECT_NO_THROW(iptcData_.sortByTag());
}

// Test sortByKey on single element
TEST_F(IptcDataTest_698, SortByKeySingleElement_698) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Only one");
    iptcData_.add(key, &value);

    EXPECT_NO_THROW(iptcData_.sortByKey());
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test adding duplicate keys (IPTC allows repeatable datasets like Keywords)
TEST_F(IptcDataTest_698, AddDuplicateRepeatableKeys_698) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword1");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword2");
    iptcData_.add(key2, &value2);

    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test detectCharset on empty data
TEST_F(IptcDataTest_698, DetectCharsetOnEmptyData_698) {
    const char* charset = iptcData_.detectCharset();
    // Could be nullptr or some default; just don't crash
    // Not asserting specific value since implementation is a black box
    (void)charset;
}

// Test that erase returns a valid iterator
TEST_F(IptcDataTest_698, EraseReturnsValidIterator_698) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("caption");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword");
    iptcData_.add(key2, &value2);

    auto it = iptcData_.begin();
    auto next = iptcData_.erase(it);
    // next should be a valid iterator
    EXPECT_EQ(iptcData_.size(), 1u);
    if (next != iptcData_.end()) {
        // Should be able to access the remaining element
        EXPECT_FALSE(next->key().empty());
    }
}

// Test count matches size
TEST_F(IptcDataTest_698, CountMatchesSize_698) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    iptcData_.add(key, &value);

    EXPECT_EQ(iptcData_.count(), iptcData_.size());
}

// Test adding via Iptcdatum object
TEST_F(IptcDataTest_698, AddViaIptcdatum_698) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    StringValue value;
    value.read("Via datum");
    datum.setValue(&value);

    EXPECT_EQ(iptcData_.add(datum), 0);
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test clear on already empty data
TEST_F(IptcDataTest_698, ClearOnEmptyData_698) {
    EXPECT_NO_THROW(iptcData_.clear());
    EXPECT_TRUE(iptcData_.empty());
}

// Test iterator traversal
TEST_F(IptcDataTest_698, IteratorTraversal_698) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("caption");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword");
    iptcData_.add(key2, &value2);

    size_t count = 0;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// Test const findKey
TEST_F(IptcDataTest_698, ConstFindKey_698) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Const find");
    iptcData_.add(key, &value);

    const IptcData& constData = iptcData_;
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = constData.findKey(searchKey);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "Const find");
}

// Test const findId
TEST_F(IptcDataTest_698, ConstFindId_698) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Const find by ID");
    iptcData_.add(key, &value);

    const IptcData& constData = iptcData_;
    auto it = constData.findId(120, 2);
    EXPECT_NE(it, constData.end());
}

// Test multiple sorts preserve all data
TEST_F(IptcDataTest_698, MultipleSortsPreserveData_698) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue v1;
    v1.read("zeta");
    iptcData_.add(key1, &v1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue v2;
    v2.read("alpha");
    iptcData_.add(key2, &v2);

    IptcKey key3("Iptc.Application2.Headline");
    StringValue v3;
    v3.read("beta");
    iptcData_.add(key3, &v3);

    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), 3u);

    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), 3u);

    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), 3u);
}
