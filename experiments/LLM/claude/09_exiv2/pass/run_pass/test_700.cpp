#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <sstream>

namespace {

using namespace Exiv2;

class IptcDataTest_700 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that a newly constructed IptcData is empty
TEST_F(IptcDataTest_700, DefaultConstructorCreatesEmptyContainer_700) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(IptcDataTest_700, BeginEqualsEndWhenEmpty_700) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding an Iptcdatum and checking size
TEST_F(IptcDataTest_700, AddIptcdatumIncreasesSize_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test caption");
    EXPECT_EQ(iptcData_.add(key, &value), 0);
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test adding multiple entries
TEST_F(IptcDataTest_700, AddMultipleEntriesIncreasesSize_700) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1("Caption 1");
    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2("Keyword 1");

    EXPECT_EQ(iptcData_.add(key1, &value1), 0);
    EXPECT_EQ(iptcData_.add(key2, &value2), 0);
    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test finding a key that exists
TEST_F(IptcDataTest_700, FindKeyReturnsIteratorToExistingEntry_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test caption");
    iptcData_.add(key, &value);

    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_NE(it, iptcData_.end());
}

// Test finding a key that does not exist
TEST_F(IptcDataTest_700, FindKeyReturnsEndForNonExistingEntry_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test caption");
    iptcData_.add(key, &value);

    IptcKey searchKey("Iptc.Application2.Keywords");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase reduces size
TEST_F(IptcDataTest_700, EraseReducesSize_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test caption");
    iptcData_.add(key, &value);
    EXPECT_EQ(iptcData_.size(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test erase returns valid iterator
TEST_F(IptcDataTest_700, EraseReturnsNextIterator_700) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1("Caption");
    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2("Keyword");

    iptcData_.add(key1, &value1);
    iptcData_.add(key2, &value2);

    auto it = iptcData_.begin();
    auto nextIt = iptcData_.erase(it);
    // After erasing the first element, next should point to what was the second
    EXPECT_EQ(iptcData_.size(), 1u);
    // nextIt should be valid (either begin or end depending on implementation)
    if (iptcData_.size() > 0) {
        EXPECT_EQ(nextIt, iptcData_.begin());
    }
}

// Test clear empties the container
TEST_F(IptcDataTest_700, ClearEmptiesContainer_700) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1("Caption");
    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2("Keyword");

    iptcData_.add(key1, &value1);
    iptcData_.add(key2, &value2);
    EXPECT_EQ(iptcData_.size(), 2u);

    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test operator[] access by key string
TEST_F(IptcDataTest_700, OperatorBracketCreatesEntry_700) {
    iptcData_["Iptc.Application2.Caption"] = "Hello";
    EXPECT_FALSE(iptcData_.empty());
    EXPECT_GE(iptcData_.size(), 1u);
}

// Test operator[] modifies existing entry
TEST_F(IptcDataTest_700, OperatorBracketModifiesExistingEntry_700) {
    iptcData_["Iptc.Application2.Caption"] = "First";
    iptcData_["Iptc.Application2.Caption"] = "Second";

    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(searchKey);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Second");
}

// Test findId with dataset and record
TEST_F(IptcDataTest_700, FindIdFindsExistingEntry_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test caption");
    iptcData_.add(key, &value);

    // Caption is dataset 120, record 2
    auto it = iptcData_.findId(120, 2);
    EXPECT_NE(it, iptcData_.end());
}

// Test findId returns end when not found
TEST_F(IptcDataTest_700, FindIdReturnsEndWhenNotFound_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test caption");
    iptcData_.add(key, &value);

    // Use a dataset/record combination that doesn't exist
    auto it = iptcData_.findId(999, 999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test sortByKey does not change size
TEST_F(IptcDataTest_700, SortByKeyPreservesSize_700) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1("Keyword");
    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2("Caption");

    iptcData_.add(key1, &value1);
    iptcData_.add(key2, &value2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag does not change size
TEST_F(IptcDataTest_700, SortByTagPreservesSize_700) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1("Keyword");
    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2("Caption");

    iptcData_.add(key1, &value1);
    iptcData_.add(key2, &value2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test count returns correct number
TEST_F(IptcDataTest_700, CountMatchesSize_700) {
    EXPECT_EQ(iptcData_.count(), iptcData_.size());

    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test");
    iptcData_.add(key, &value);

    EXPECT_EQ(iptcData_.count(), iptcData_.size());
}

// Test adding duplicate repeatable keys
TEST_F(IptcDataTest_700, AddDuplicateRepeatableKeysAllowed_700) {
    // Keywords is a repeatable IPTC field
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1("Keyword1");
    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2("Keyword2");

    EXPECT_EQ(iptcData_.add(key1, &value1), 0);
    EXPECT_EQ(iptcData_.add(key2, &value2), 0);
    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test detectCharset on empty data
TEST_F(IptcDataTest_700, DetectCharsetOnEmptyData_700) {
    const char* charset = iptcData_.detectCharset();
    // For empty data, charset detection may return nullptr or some default
    // We just verify it doesn't crash
    (void)charset;
}

// Test detectCharset after adding data
TEST_F(IptcDataTest_700, DetectCharsetAfterAddingData_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("ASCII text");
    iptcData_.add(key, &value);

    const char* charset = iptcData_.detectCharset();
    // We just verify it doesn't crash; result depends on data
    (void)charset;
}

// Test erasing all elements one by one
TEST_F(IptcDataTest_700, EraseAllElementsOneByOne_700) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value1("Caption");
    IptcKey key2("Iptc.Application2.Keywords");
    StringValue value2("Keyword");
    IptcKey key3("Iptc.Application2.City");
    StringValue value3("City");

    iptcData_.add(key1, &value1);
    iptcData_.add(key2, &value2);
    iptcData_.add(key3, &value3);
    EXPECT_EQ(iptcData_.size(), 3u);

    while (!iptcData_.empty()) {
        iptcData_.erase(iptcData_.begin());
    }
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test that add with Iptcdatum works
TEST_F(IptcDataTest_700, AddIptcdatumDirectly_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test");
    iptcData_.add(key, &value);

    // Copy first datum
    auto it = iptcData_.begin();
    Iptcdatum datum(*it);

    IptcData other;
    EXPECT_EQ(other.add(datum), 0);
    EXPECT_EQ(other.size(), 1u);
}

// Test sortByKey actually sorts
TEST_F(IptcDataTest_700, SortByKeyActuallySorts_700) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue value1("Keyword");
    IptcKey key2("Iptc.Application2.Caption");
    StringValue value2("Caption");

    iptcData_.add(key1, &value1);
    iptcData_.add(key2, &value2);

    iptcData_.sortByKey();

    // After sorting by key, Caption should come before Keywords alphabetically
    auto it = iptcData_.begin();
    std::string firstKey = it->key();
    ++it;
    std::string secondKey = it->key();
    EXPECT_LE(firstKey, secondKey);
}

// Test findKey on empty container
TEST_F(IptcDataTest_700, FindKeyOnEmptyContainerReturnsEnd_700) {
    IptcKey key("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(key);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId on empty container
TEST_F(IptcDataTest_700, FindIdOnEmptyContainerReturnsEnd_700) {
    auto it = iptcData_.findId(120, 2);
    EXPECT_EQ(it, iptcData_.end());
}

// Test clear on already empty container
TEST_F(IptcDataTest_700, ClearOnEmptyContainerIsNoOp_700) {
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test sortByKey on empty container doesn't crash
TEST_F(IptcDataTest_700, SortByKeyOnEmptyContainerIsNoOp_700) {
    EXPECT_NO_THROW(iptcData_.sortByKey());
    EXPECT_TRUE(iptcData_.empty());
}

// Test sortByTag on empty container doesn't crash
TEST_F(IptcDataTest_700, SortByTagOnEmptyContainerIsNoOp_700) {
    EXPECT_NO_THROW(iptcData_.sortByTag());
    EXPECT_TRUE(iptcData_.empty());
}

// Test sortByKey on single element
TEST_F(IptcDataTest_700, SortByKeyOnSingleElementIsNoOp_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test");
    iptcData_.add(key, &value);

    EXPECT_NO_THROW(iptcData_.sortByKey());
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test value retrieval through iterator
TEST_F(IptcDataTest_700, ValueRetrievableThroughIterator_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Hello World");
    iptcData_.add(key, &value);

    auto it = iptcData_.begin();
    EXPECT_EQ(it->toString(), "Hello World");
}

// Test const findKey
TEST_F(IptcDataTest_700, ConstFindKeyWorks_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test");
    iptcData_.add(key, &value);

    const IptcData& constData = iptcData_;
    IptcKey searchKey("Iptc.Application2.Caption");
    auto it = constData.findKey(searchKey);
    EXPECT_NE(it, constData.end());
}

// Test const findId
TEST_F(IptcDataTest_700, ConstFindIdWorks_700) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value("Test");
    iptcData_.add(key, &value);

    const IptcData& constData = iptcData_;
    auto it = constData.findId(120, 2);
    EXPECT_NE(it, constData.end());
}

}  // namespace
