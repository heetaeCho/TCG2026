#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>

using namespace Exiv2;

// Test fixture for IptcData tests
class IptcDataTest_692 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that a newly created IptcData is empty
TEST_F(IptcDataTest_692, DefaultConstructedIsEmpty_692) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(IptcDataTest_692, EmptyBeginEqualsEnd_692) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test operator[] creates a new entry when key doesn't exist
TEST_F(IptcDataTest_692, OperatorBracketCreatesNewEntry_692) {
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_FALSE(iptcData_.empty());
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test operator[] returns existing entry when key exists
TEST_F(IptcDataTest_692, OperatorBracketReturnsExistingEntry_692) {
    iptcData_["Iptc.Application2.Caption"].setValue("Test Caption");
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_EQ(datum.toString(), "Test Caption");
}

// Test operator[] with multiple different keys
TEST_F(IptcDataTest_692, OperatorBracketMultipleKeys_692) {
    iptcData_["Iptc.Application2.Caption"];
    iptcData_["Iptc.Application2.Keywords"];
    iptcData_["Iptc.Application2.Byline"];
    EXPECT_EQ(iptcData_.size(), 3u);
}

// Test add with IptcKey and Value
TEST_F(IptcDataTest_692, AddWithKeyAndValue_692) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Hello World");
    int result = iptcData_.add(key, &value);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test add with Iptcdatum
TEST_F(IptcDataTest_692, AddWithIptcdatum_692) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Test");
    int result = iptcData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test findKey returns end() when key not found
TEST_F(IptcDataTest_692, FindKeyNotFound_692) {
    IptcKey key("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(key);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findKey returns correct iterator when key exists
TEST_F(IptcDataTest_692, FindKeyFound_692) {
    iptcData_["Iptc.Application2.Caption"].setValue("Found me");
    IptcKey key("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Found me");
}

// Test findId returns end() when dataset/record not found
TEST_F(IptcDataTest_692, FindIdNotFound_692) {
    auto it = iptcData_.findId(120, 2);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes an element
TEST_F(IptcDataTest_692, EraseRemovesElement_692) {
    iptcData_["Iptc.Application2.Caption"].setValue("To be erased");
    EXPECT_EQ(iptcData_.size(), 1u);
    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test erase in the middle of multiple elements
TEST_F(IptcDataTest_692, EraseMiddleElement_692) {
    iptcData_["Iptc.Application2.Caption"].setValue("First");
    iptcData_["Iptc.Application2.Keywords"].setValue("Second");
    iptcData_["Iptc.Application2.Byline"].setValue("Third");
    EXPECT_EQ(iptcData_.size(), 3u);

    IptcKey key("Iptc.Application2.Keywords");
    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 2u);

    // Verify Keywords is gone
    auto it2 = iptcData_.findKey(key);
    EXPECT_EQ(it2, iptcData_.end());
}

// Test clear removes all elements
TEST_F(IptcDataTest_692, ClearRemovesAll_692) {
    iptcData_["Iptc.Application2.Caption"];
    iptcData_["Iptc.Application2.Keywords"];
    EXPECT_EQ(iptcData_.size(), 2u);
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test clear on already empty data
TEST_F(IptcDataTest_692, ClearOnEmpty_692) {
    EXPECT_TRUE(iptcData_.empty());
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
}

// Test sortByKey does not change size
TEST_F(IptcDataTest_692, SortByKeyPreservesSize_692) {
    iptcData_["Iptc.Application2.Keywords"].setValue("keyword");
    iptcData_["Iptc.Application2.Caption"].setValue("caption");
    iptcData_["Iptc.Application2.Byline"].setValue("byline");
    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag does not change size
TEST_F(IptcDataTest_692, SortByTagPreservesSize_692) {
    iptcData_["Iptc.Application2.Keywords"].setValue("keyword");
    iptcData_["Iptc.Application2.Caption"].setValue("caption");
    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test count matches size for non-repeatable datasets
TEST_F(IptcDataTest_692, CountMatchesSize_692) {
    iptcData_["Iptc.Application2.Caption"].setValue("test");
    EXPECT_EQ(iptcData_.count(), iptcData_.size());
}

// Test detectCharset on empty data
TEST_F(IptcDataTest_692, DetectCharsetOnEmptyData_692) {
    const char* charset = iptcData_.detectCharset();
    // On empty data, charset detection may return nullptr or some default
    // We just verify it doesn't crash
    (void)charset;
}

// Test adding duplicate keys via add() allows multiple entries
TEST_F(IptcDataTest_692, AddDuplicateKeysAllowed_692) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue value1("keyword1");
    StringValue value2("keyword2");
    iptcData_.add(key, &value1);
    iptcData_.add(key, &value2);
    // Keywords is a repeatable dataset, so both should be stored
    EXPECT_GE(iptcData_.size(), 2u);
}

// Test operator[] with same key multiple times returns same entry
TEST_F(IptcDataTest_692, OperatorBracketIdempotent_692) {
    iptcData_["Iptc.Application2.Caption"].setValue("Value1");
    iptcData_["Iptc.Application2.Caption"].setValue("Value2");
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_EQ(iptcData_["Iptc.Application2.Caption"].toString(), "Value2");
}

// Test iteration over elements
TEST_F(IptcDataTest_692, IterationOverElements_692) {
    iptcData_["Iptc.Application2.Caption"].setValue("cap");
    iptcData_["Iptc.Application2.Byline"].setValue("by");

    int count = 0;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2);
}

// Test that operator[] with invalid key throws
TEST_F(IptcDataTest_692, OperatorBracketInvalidKeyThrows_692) {
    EXPECT_THROW(iptcData_["InvalidKey"], std::exception);
}

// Test findKey with const IptcData
TEST_F(IptcDataTest_692, ConstFindKey_692) {
    iptcData_["Iptc.Application2.Caption"].setValue("test");
    const IptcData& constData = iptcData_;
    IptcKey key("Iptc.Application2.Caption");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "test");
}

// Test const findKey returns end when not found
TEST_F(IptcDataTest_692, ConstFindKeyNotFound_692) {
    const IptcData& constData = iptcData_;
    IptcKey key("Iptc.Application2.Caption");
    auto it = constData.findKey(key);
    EXPECT_EQ(it, constData.end());
}

// Test add with null value pointer
TEST_F(IptcDataTest_692, AddWithNullValue_692) {
    IptcKey key("Iptc.Application2.Caption");
    int result = iptcData_.add(key, nullptr);
    // Should succeed but have no value set, or handle gracefully
    (void)result;
    // Just ensure no crash
}

// Test size after multiple adds and erases
TEST_F(IptcDataTest_692, SizeAfterAddsAndErases_692) {
    iptcData_["Iptc.Application2.Caption"];
    iptcData_["Iptc.Application2.Keywords"];
    iptcData_["Iptc.Application2.Byline"];
    EXPECT_EQ(iptcData_.size(), 3u);

    iptcData_.erase(iptcData_.begin());
    EXPECT_EQ(iptcData_.size(), 2u);

    iptcData_.erase(iptcData_.begin());
    EXPECT_EQ(iptcData_.size(), 1u);

    iptcData_.erase(iptcData_.begin());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test that key() of datum created by operator[] matches the input key
TEST_F(IptcDataTest_692, DatumKeyMatchesInput_692) {
    Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}
