#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class IptcDataTest_693 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that an empty IptcData has size 0
TEST_F(IptcDataTest_693, EmptyDataHasSizeZero_693) {
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test that an empty IptcData reports empty
TEST_F(IptcDataTest_693, EmptyDataIsEmpty_693) {
    EXPECT_TRUE(iptcData_.empty());
}

// Test that an empty IptcData has count 0
TEST_F(IptcDataTest_693, EmptyDataHasCountZero_693) {
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test adding a single entry increases count
TEST_F(IptcDataTest_693, AddSingleEntryIncreasesCount_693) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Hello");
    iptcData_.add(key, &value);
    EXPECT_EQ(iptcData_.count(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test size() for a single small entry: 5 bytes header + data size
TEST_F(IptcDataTest_693, SizeForSingleSmallEntry_693) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Hello");
    iptcData_.add(key, &value);
    // size = 5 + strlen("Hello") = 5 + 5 = 10
    // (StringValue::size() for "Hello" should be 5)
    size_t expectedSize = 5 + value.size();
    EXPECT_EQ(iptcData_.size(), expectedSize);
}

// Test adding multiple entries accumulates size correctly
TEST_F(IptcDataTest_693, SizeForMultipleEntries_693) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1;
    value1.read("Hello");
    iptcData_.add(key1, &value1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2;
    value2.read("World");
    iptcData_.add(key2, &value2);

    size_t expectedSize = (5 + value1.size()) + (5 + value2.size());
    EXPECT_EQ(iptcData_.size(), expectedSize);
}

// Test adding an entry via Iptcdatum
TEST_F(IptcDataTest_693, AddIptcdatumIncreasesCount_693) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    iptcData_.add(datum);
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test clear empties the data
TEST_F(IptcDataTest_693, ClearEmptiesData_693) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Hello");
    iptcData_.add(key, &value);
    EXPECT_FALSE(iptcData_.empty());

    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.count(), 0u);
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test erase removes an entry
TEST_F(IptcDataTest_693, EraseRemovesEntry_693) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Hello");
    iptcData_.add(key, &value);
    EXPECT_EQ(iptcData_.count(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.count(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test findKey returns end for non-existing key
TEST_F(IptcDataTest_693, FindKeyReturnsEndForMissing_693) {
    IptcKey key("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(key);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findKey finds an existing key
TEST_F(IptcDataTest_693, FindKeyFindsExistingEntry_693) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Hello");
    iptcData_.add(key, &value);

    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->key(), "Iptc.Application2.Caption");
}

// Test findId returns end for non-existing dataset/record
TEST_F(IptcDataTest_693, FindIdReturnsEndForMissing_693) {
    auto it = iptcData_.findId(999, 999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test operator[] creates entry if not found
TEST_F(IptcDataTest_693, SubscriptOperatorCreatesEntry_693) {
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test operator[] finds existing entry
TEST_F(IptcDataTest_693, SubscriptOperatorFindsExisting_693) {
    iptcData_["Iptc.Application2.Caption"] = std::string("Test");
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.toString(), "Test");
    // Should not add a second entry
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test sortByKey doesn't crash on empty data
TEST_F(IptcDataTest_693, SortByKeyOnEmptyDoesNotCrash_693) {
    EXPECT_NO_THROW(iptcData_.sortByKey());
}

// Test sortByTag doesn't crash on empty data
TEST_F(IptcDataTest_693, SortByTagOnEmptyDoesNotCrash_693) {
    EXPECT_NO_THROW(iptcData_.sortByTag());
}

// Test sortByKey with multiple entries
TEST_F(IptcDataTest_693, SortByKeyMultipleEntries_693) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue val1;
    val1.read("Keyword1");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue val2;
    val2.read("Caption1");
    iptcData_.add(key2, &val2);

    iptcData_.sortByKey();

    // After sorting by key, Caption should come before Keywords alphabetically
    auto it = iptcData_.begin();
    EXPECT_EQ(it->key(), "Iptc.Application2.Caption");
    ++it;
    EXPECT_EQ(it->key(), "Iptc.Application2.Keywords");
}

// Test size with large data value (> 32767 bytes triggers extra 4 bytes)
TEST_F(IptcDataTest_693, SizeForLargeDataEntry_693) {
    IptcKey key("Iptc.Application2.Caption");
    // Create a string value larger than 32767 bytes
    std::string largeStr(32768, 'A');
    StringValue value;
    value.read(largeStr);
    iptcData_.add(key, &value);

    size_t dataSize = value.size();
    ASSERT_GT(dataSize, 32767u);
    // size = 5 + dataSize + 4 (because dataSize > 32767)
    size_t expectedSize = 5 + dataSize + 4;
    EXPECT_EQ(iptcData_.size(), expectedSize);
}

// Test size with data exactly at boundary (32767 bytes)
TEST_F(IptcDataTest_693, SizeForBoundaryDataEntry_693) {
    IptcKey key("Iptc.Application2.Caption");
    std::string boundaryStr(32767, 'B');
    StringValue value;
    value.read(boundaryStr);
    iptcData_.add(key, &value);

    size_t dataSize = value.size();
    // If dataSize == 32767, it is NOT > 32767, so no extra 4 bytes
    size_t expectedSize = 5 + dataSize;
    if (dataSize > 32767) {
        expectedSize += 4;
    }
    EXPECT_EQ(iptcData_.size(), expectedSize);
}

// Test size with data just above boundary (32768 bytes)
TEST_F(IptcDataTest_693, SizeForJustAboveBoundaryDataEntry_693) {
    IptcKey key("Iptc.Application2.Caption");
    std::string aboveBoundaryStr(32768, 'C');
    StringValue value;
    value.read(aboveBoundaryStr);
    iptcData_.add(key, &value);

    size_t dataSize = value.size();
    ASSERT_GT(dataSize, 32767u);
    size_t expectedSize = 5 + dataSize + 4;
    EXPECT_EQ(iptcData_.size(), expectedSize);
}

// Test begin and end iterators on empty data
TEST_F(IptcDataTest_693, BeginEqualsEndOnEmpty_693) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test begin and end iterators on non-empty data
TEST_F(IptcDataTest_693, BeginNotEqualsEndOnNonEmpty_693) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    iptcData_.add(key, &value);
    EXPECT_NE(iptcData_.begin(), iptcData_.end());
}

// Test detectCharset on empty data
TEST_F(IptcDataTest_693, DetectCharsetOnEmptyData_693) {
    const char* charset = iptcData_.detectCharset();
    // On empty data, detectCharset may return nullptr or some default
    // We just ensure it doesn't crash
    (void)charset;
}

// Test Iptcdatum key, familyName, groupName, tagName
TEST_F(IptcDataTest_693, IptcdatumKeyProperties_693) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_STREQ(datum.familyName(), "Iptc");
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test Iptcdatum assignment from string
TEST_F(IptcDataTest_693, IptcdatumAssignFromString_693) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("TestValue");
    EXPECT_EQ(datum.toString(), "TestValue");
}

// Test Iptcdatum copy constructor
TEST_F(IptcDataTest_693, IptcdatumCopyConstructor_693) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("CopyTest");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "CopyTest");
}

// Test Iptcdatum assignment operator
TEST_F(IptcDataTest_693, IptcdatumAssignmentOperator_693) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1 = std::string("Original");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), "Original");
}

// Test add returns 0 on success
TEST_F(IptcDataTest_693, AddReturnsZeroOnSuccess_693) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    int result = iptcData_.add(key, &value);
    EXPECT_EQ(result, 0);
}

// Test adding multiple entries with same key
TEST_F(IptcDataTest_693, AddMultipleEntriesSameKey_693) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("Keyword1");
    iptcData_.add(key, &value1);

    StringValue value2;
    value2.read("Keyword2");
    iptcData_.add(key, &value2);

    EXPECT_EQ(iptcData_.count(), 2u);
}

// Test size accumulates correctly with mixed small entries
TEST_F(IptcDataTest_693, SizeAccumulatesForMixedEntries_693) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1;
    val1.read("Short");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2;
    val2.read("A");
    iptcData_.add(key2, &val2);

    size_t expectedSize = (5 + val1.size()) + (5 + val2.size());
    EXPECT_EQ(iptcData_.size(), expectedSize);
}

// Test empty string value
TEST_F(IptcDataTest_693, EmptyStringValue_693) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("");
    iptcData_.add(key, &value);

    // size should be 5 + 0 = 5 (empty data, no extra bytes)
    size_t expectedSize = 5 + value.size();
    EXPECT_EQ(iptcData_.size(), expectedSize);
    EXPECT_EQ(iptcData_.count(), 1u);
}
