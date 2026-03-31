#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

namespace {

using namespace Exiv2;

class IptcDataTest_699 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that a newly created IptcData is empty
TEST_F(IptcDataTest_699, DefaultConstructorCreatesEmptyContainer_699) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test begin() == end() for empty container
TEST_F(IptcDataTest_699, BeginEqualsEndWhenEmpty_699) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding a datum via add(IptcKey, Value*)
TEST_F(IptcDataTest_699, AddWithKeyAndValueIncreasesSize_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test caption");
    int result = iptcData_.add(key, &value);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test adding an Iptcdatum
TEST_F(IptcDataTest_699, AddIptcdatumIncreasesSize_699) {
    Iptcdatum datum(IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Hello World");
    int result = iptcData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test adding multiple entries
TEST_F(IptcDataTest_699, AddMultipleEntries_699) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("Caption 1");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("keyword1");
    iptcData_.add(key2, &val2);

    IptcKey key3("Iptc.Application2.Keywords");
    StringValue val3("keyword2");
    iptcData_.add(key3, &val3);

    EXPECT_EQ(iptcData_.size(), 3u);
}

// Test operator[] creates entry if not present
TEST_F(IptcDataTest_699, OperatorBracketCreatesEntry_699) {
    EXPECT_TRUE(iptcData_.empty());
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    // After accessing with operator[], the entry should exist
    EXPECT_GE(iptcData_.size(), 1u);
    (void)datum;
}

// Test operator[] returns existing entry
TEST_F(IptcDataTest_699, OperatorBracketReturnsExistingEntry_699) {
    iptcData_["Iptc.Application2.Caption"].setValue("Test");
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.toString(), "Test");
}

// Test findKey on existing key
TEST_F(IptcDataTest_699, FindKeyReturnsIteratorToExistingEntry_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Find me");
    iptcData_.add(key, &val);

    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Find me");
}

// Test findKey on non-existing key returns end()
TEST_F(IptcDataTest_699, FindKeyReturnsEndForNonExistingKey_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Something");
    iptcData_.add(key, &val);

    IptcKey searchKey("Iptc.Application2.Keywords");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId on existing dataset/record
TEST_F(IptcDataTest_699, FindIdReturnsIteratorToExistingEntry_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("By ID");
    iptcData_.add(key, &val);

    // Caption is dataset 120, record 2
    auto it = iptcData_.findId(120, 2);
    EXPECT_NE(it, iptcData_.end());
}

// Test findId on non-existing dataset/record returns end()
TEST_F(IptcDataTest_699, FindIdReturnsEndForNonExistingId_699) {
    auto it = iptcData_.findId(9999, 9999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase reduces size
TEST_F(IptcDataTest_699, EraseReducesSize_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("To erase");
    iptcData_.add(key, &val);
    EXPECT_EQ(iptcData_.size(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test erase returns valid iterator
TEST_F(IptcDataTest_699, EraseReturnsValidIterator_699) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("First");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("Second");
    iptcData_.add(key2, &val2);

    auto it = iptcData_.erase(iptcData_.begin());
    EXPECT_EQ(iptcData_.size(), 1u);
    // The returned iterator should be valid (either pointing to next element or end)
    if (it != iptcData_.end()) {
        EXPECT_FALSE(it->key().empty());
    }
}

// Test clear empties the container
TEST_F(IptcDataTest_699, ClearEmptiesContainer_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Clear me");
    iptcData_.add(key, &val);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("Also clear");
    iptcData_.add(key2, &val2);

    EXPECT_EQ(iptcData_.size(), 2u);
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test sortByTag does not change the size
TEST_F(IptcDataTest_699, SortByTagPreservesSize_699) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue val1("keyword");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue val2("caption");
    iptcData_.add(key2, &val2);

    IptcKey key3("Iptc.Application2.City");
    StringValue val3("city");
    iptcData_.add(key3, &val3);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag actually sorts (tag numbers should be non-decreasing)
TEST_F(IptcDataTest_699, SortByTagOrdersByTag_699) {
    // Add entries in various orders
    IptcKey key1("Iptc.Application2.Keywords");  // dataset 25
    StringValue val1("keyword");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Caption");   // dataset 120
    StringValue val2("caption");
    iptcData_.add(key2, &val2);

    IptcKey key3("Iptc.Application2.City");      // dataset 90
    StringValue val3("city");
    iptcData_.add(key3, &val3);

    iptcData_.sortByTag();

    // After sorting by tag, tags should be non-decreasing
    uint16_t prevTag = 0;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        EXPECT_GE(it->tag(), prevTag);
        prevTag = it->tag();
    }
}

// Test sortByKey does not change the size
TEST_F(IptcDataTest_699, SortByKeyPreservesSize_699) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue val1("keyword");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue val2("caption");
    iptcData_.add(key2, &val2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByKey orders by key string
TEST_F(IptcDataTest_699, SortByKeyOrdersByKey_699) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue val1("keyword");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue val2("caption");
    iptcData_.add(key2, &val2);

    IptcKey key3("Iptc.Application2.City");
    StringValue val3("city");
    iptcData_.add(key3, &val3);

    iptcData_.sortByKey();

    std::string prevKey;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        EXPECT_GE(it->key(), prevKey);
        prevKey = it->key();
    }
}

// Test count matches size
TEST_F(IptcDataTest_699, CountMatchesSize_699) {
    EXPECT_EQ(iptcData_.count(), iptcData_.size());

    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    iptcData_.add(key, &val);

    EXPECT_EQ(iptcData_.count(), iptcData_.size());
}

// Test detectCharset on empty data
TEST_F(IptcDataTest_699, DetectCharsetOnEmptyData_699) {
    const char* charset = iptcData_.detectCharset();
    // charset can be nullptr or a valid string for empty data
    // We just ensure it doesn't crash
    (void)charset;
}

// Test sorting empty container does not crash
TEST_F(IptcDataTest_699, SortByTagOnEmptyDoesNotCrash_699) {
    EXPECT_NO_THROW(iptcData_.sortByTag());
    EXPECT_TRUE(iptcData_.empty());
}

// Test sorting empty container by key does not crash
TEST_F(IptcDataTest_699, SortByKeyOnEmptyDoesNotCrash_699) {
    EXPECT_NO_THROW(iptcData_.sortByKey());
    EXPECT_TRUE(iptcData_.empty());
}

// Test clear on empty container
TEST_F(IptcDataTest_699, ClearOnEmptyDoesNotCrash_699) {
    EXPECT_NO_THROW(iptcData_.clear());
    EXPECT_TRUE(iptcData_.empty());
}

// Test adding duplicate repeatable entries
TEST_F(IptcDataTest_699, AddDuplicateRepeatableKeywords_699) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue val1("keyword1");
    int r1 = iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("keyword2");
    int r2 = iptcData_.add(key2, &val2);

    EXPECT_EQ(r1, 0);
    EXPECT_EQ(r2, 0);
    // Keywords is repeatable, so both should be present
    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test findKey with const version
TEST_F(IptcDataTest_699, ConstFindKeyWorks_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("const test");
    iptcData_.add(key, &val);

    const IptcData& constData = iptcData_;
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = constData.findKey(searchKey);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "const test");
}

// Test const findId
TEST_F(IptcDataTest_699, ConstFindIdWorks_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("const id test");
    iptcData_.add(key, &val);

    const IptcData& constData = iptcData_;
    auto it = constData.findId(120, 2);
    EXPECT_NE(it, constData.end());
}

// Test iteration over entries
TEST_F(IptcDataTest_699, IterationVisitsAllEntries_699) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("cap");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("kw");
    iptcData_.add(key2, &val2);

    size_t count = 0;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// Test sort stability - sorting single element
TEST_F(IptcDataTest_699, SortByTagSingleElement_699) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("solo");
    iptcData_.add(key, &val);

    EXPECT_NO_THROW(iptcData_.sortByTag());
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_EQ(iptcData_.begin()->toString(), "solo");
}

// Test erase in the middle
TEST_F(IptcDataTest_699, EraseMiddleElement_699) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("first");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("second");
    iptcData_.add(key2, &val2);

    IptcKey key3("Iptc.Application2.City");
    StringValue val3("third");
    iptcData_.add(key3, &val3);

    EXPECT_EQ(iptcData_.size(), 3u);

    auto it = iptcData_.begin();
    ++it; // point to second element
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test that findKey on empty container returns end
TEST_F(IptcDataTest_699, FindKeyOnEmptyReturnsEnd_699) {
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test that findId on empty container returns end
TEST_F(IptcDataTest_699, FindIdOnEmptyReturnsEnd_699) {
    auto it = iptcData_.findId(120, 2);
    EXPECT_EQ(it, iptcData_.end());
}

}  // namespace
