#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcDataTest_45 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that a newly created IptcData is empty
TEST_F(IptcDataTest_45, DefaultConstructorCreatesEmptyContainer_45) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(IptcDataTest_45, BeginEqualsEndWhenEmpty_45) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding an Iptcdatum and verifying size increases
TEST_F(IptcDataTest_45, AddIptcdatumIncreasesSize_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    EXPECT_EQ(iptcData_.add(key, &value), 0);
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test adding multiple entries
TEST_F(IptcDataTest_45, AddMultipleEntries_45) {
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

// Test operator[] creates entry if it doesn't exist
TEST_F(IptcDataTest_45, OperatorBracketCreatesEntry_45) {
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    // The operator[] should have added an entry
    EXPECT_GE(iptcData_.size(), 1u);
}

// Test operator[] returns existing entry
TEST_F(IptcDataTest_45, OperatorBracketReturnsExistingEntry_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    iptcData_.add(key, &value);

    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.toString(), "Test caption");
}

// Test findKey on existing key
TEST_F(IptcDataTest_45, FindKeyExistingReturnsIterator_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Found me");
    iptcData_.add(key, &value);

    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Found me");
}

// Test findKey on non-existing key returns end
TEST_F(IptcDataTest_45, FindKeyNonExistingReturnsEnd_45) {
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId on existing dataset/record
TEST_F(IptcDataTest_45, FindIdExistingReturnsIterator_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("ID search test");
    iptcData_.add(key, &value);

    // Caption is dataset 120, record 2
    auto it = iptcData_.findId(IptcDataSets::Caption, IptcDataSets::application2);
    EXPECT_NE(it, iptcData_.end());
}

// Test findId on non-existing dataset/record returns end
TEST_F(IptcDataTest_45, FindIdNonExistingReturnsEnd_45) {
    auto it = iptcData_.findId(9999, 9999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes element
TEST_F(IptcDataTest_45, EraseRemovesElement_45) {
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

// Test clear removes all elements
TEST_F(IptcDataTest_45, ClearRemovesAllElements_45) {
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
TEST_F(IptcDataTest_45, SortByKeyDoesNotChangeSize_45) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword1");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("caption1");
    iptcData_.add(key2, &value2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag does not change size
TEST_F(IptcDataTest_45, SortByTagDoesNotChangeSize_45) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword1");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("caption1");
    iptcData_.add(key2, &value2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test adding duplicate keys (IPTC allows repeatable datasets like Keywords)
TEST_F(IptcDataTest_45, AddDuplicateRepeatableKey_45) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword1");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword2");
    iptcData_.add(key2, &value2);

    // Keywords is repeatable, so both should be present
    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test iteration over elements
TEST_F(IptcDataTest_45, IterationOverElements_45) {
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

// Test detectCharset on empty data
TEST_F(IptcDataTest_45, DetectCharsetOnEmptyData_45) {
    const char* charset = iptcData_.detectCharset();
    // On empty data, detectCharset may return nullptr or some default
    // We just verify it doesn't crash and returns something
    // (charset can be nullptr)
    (void)charset;  // no crash is the test
}

// Test add with Iptcdatum overload
TEST_F(IptcDataTest_45, AddIptcdatumOverload_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("test value");

    Iptcdatum datum(key, &value);
    int result = iptcData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test erase returns valid iterator
TEST_F(IptcDataTest_45, EraseReturnsValidIterator_45) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("caption");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword");
    iptcData_.add(key2, &value2);

    auto it = iptcData_.begin();
    auto nextIt = iptcData_.erase(it);
    // After erasing first element, the returned iterator should be valid
    EXPECT_EQ(iptcData_.size(), 1u);
    if (nextIt != iptcData_.end()) {
        // Should be able to access the remaining element
        EXPECT_FALSE(nextIt->key().empty());
    }
}

// Test sortByKey actually sorts
TEST_F(IptcDataTest_45, SortByKeyActuallySorts_45) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2;
    value2.read("caption");
    iptcData_.add(key2, &value2);

    iptcData_.sortByKey();

    // After sorting by key, entries should be in alphabetical order of key
    auto it = iptcData_.begin();
    std::string firstKey = it->key();
    ++it;
    std::string secondKey = it->key();
    EXPECT_LE(firstKey, secondKey);
}

// Test const findKey
TEST_F(IptcDataTest_45, ConstFindKey_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("const test");
    iptcData_.add(key, &value);

    const IptcData& constData = iptcData_;
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = constData.findKey(searchKey);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "const test");
}

// Test const findId
TEST_F(IptcDataTest_45, ConstFindId_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("const id test");
    iptcData_.add(key, &value);

    const IptcData& constData = iptcData_;
    auto it = constData.findId(IptcDataSets::Caption, IptcDataSets::application2);
    EXPECT_NE(it, constData.end());
}

// Test adding with null value pointer
TEST_F(IptcDataTest_45, AddWithNullValue_45) {
    IptcKey key("Iptc.Application2.Caption");
    int result = iptcData_.add(key, nullptr);
    // Should handle gracefully - either succeed with empty value or return error
    // We just check it doesn't crash
    (void)result;
}

// Test count matches size for standard usage
TEST_F(IptcDataTest_45, CountMatchesSize_45) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("caption");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("keyword");
    iptcData_.add(key2, &value2);

    EXPECT_EQ(iptcData_.size(), iptcData_.count());
}

// Test empty after clear
TEST_F(IptcDataTest_45, EmptyAfterClear_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("to clear");
    iptcData_.add(key, &value);

    EXPECT_FALSE(iptcData_.empty());
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test that findKey returns end after clearing
TEST_F(IptcDataTest_45, FindKeyAfterClearReturnsEnd_45) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("before clear");
    iptcData_.add(key, &value);

    iptcData_.clear();

    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test sortByTag with multiple entries
TEST_F(IptcDataTest_45, SortByTagOrdersByTag_45) {
    // Keywords (tag 25) and Caption (tag 120) in Application2
    IptcKey key1("Iptc.Application2.Caption");  // tag 120
    StringValue value1;
    value1.read("caption");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");  // tag 25
    StringValue value2;
    value2.read("keyword");
    iptcData_.add(key2, &value2);

    iptcData_.sortByTag();

    auto it = iptcData_.begin();
    uint16_t firstTag = it->tag();
    ++it;
    uint16_t secondTag = it->tag();
    EXPECT_LE(firstTag, secondTag);
}
