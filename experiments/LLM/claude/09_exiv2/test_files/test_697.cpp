#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

namespace {

class IptcDataTest_697 : public ::testing::Test {
protected:
    Exiv2::IptcData iptcData_;
};

// Test that a newly created IptcData is empty
TEST_F(IptcDataTest_697, DefaultConstructorCreatesEmptyContainer_697) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test begin == end for empty container
TEST_F(IptcDataTest_697, BeginEqualsEndWhenEmpty_697) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding a datum using IptcKey and Value
TEST_F(IptcDataTest_697, AddWithKeyAndValueIncreasesSize_697) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test caption");
    int result = iptcData_.add(key, value.get());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test adding an Iptcdatum directly
TEST_F(IptcDataTest_697, AddIptcdatumIncreasesSize_697) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test caption");
    Exiv2::Iptcdatum datum(key, value.get());
    int result = iptcData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test operator[] creates entry if not present
TEST_F(IptcDataTest_697, OperatorBracketCreatesEntry_697) {
    iptcData_["Iptc.Application2.Caption"] = "Hello World";
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test operator[] retrieves existing entry
TEST_F(IptcDataTest_697, OperatorBracketRetrievesExistingEntry_697) {
    iptcData_["Iptc.Application2.Caption"] = "Hello World";
    std::string val = iptcData_["Iptc.Application2.Caption"].toString();
    EXPECT_EQ(val, "Hello World");
}

// Test findKey on existing key
TEST_F(IptcDataTest_697, FindKeyReturnsIteratorToExistingEntry_697) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test");
    iptcData_.add(key, value.get());

    auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Test");
}

// Test findKey on non-existing key returns end
TEST_F(IptcDataTest_697, FindKeyReturnsEndForNonExistingKey_697) {
    auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId on existing dataset and record
TEST_F(IptcDataTest_697, FindIdReturnsIteratorToExistingEntry_697) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test caption");
    iptcData_.add(key, value.get());

    // Caption is dataset 120, record 2
    auto it = iptcData_.findId(120, 2);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Test caption");
}

// Test findId returns end when not found
TEST_F(IptcDataTest_697, FindIdReturnsEndWhenNotFound_697) {
    auto it = iptcData_.findId(9999, 9999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId on empty container
TEST_F(IptcDataTest_697, FindIdOnEmptyContainerReturnsEnd_697) {
    auto it = iptcData_.findId(120, 2);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes an element
TEST_F(IptcDataTest_697, EraseRemovesElement_697) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("To be erased");
    iptcData_.add(key, value.get());
    EXPECT_EQ(iptcData_.size(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test clear empties the container
TEST_F(IptcDataTest_697, ClearEmptiesContainer_697) {
    iptcData_["Iptc.Application2.Caption"] = "Value1";
    iptcData_["Iptc.Application2.Keywords"] = "Value2";
    EXPECT_GE(iptcData_.size(), 1u);

    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test adding multiple entries
TEST_F(IptcDataTest_697, AddMultipleEntriesIncreasesSize_697) {
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
    val1->read("Caption");
    iptcData_.add(key1, val1.get());

    Exiv2::IptcKey key2("Iptc.Application2.Keywords");
    Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
    val2->read("Keyword1");
    iptcData_.add(key2, val2.get());

    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test adding duplicate keys (IPTC allows repeatable datasets like Keywords)
TEST_F(IptcDataTest_697, AddDuplicateRepeatableKeysAllowed_697) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
    val1->read("Keyword1");
    iptcData_.add(key, val1.get());

    Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
    val2->read("Keyword2");
    iptcData_.add(key, val2.get());

    EXPECT_GE(iptcData_.size(), 2u);
}

// Test sortByKey does not crash and doesn't change size
TEST_F(IptcDataTest_697, SortByKeyPreservesSize_697) {
    iptcData_["Iptc.Application2.Keywords"] = "Keyword";
    iptcData_["Iptc.Application2.Caption"] = "Caption";
    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag does not crash and doesn't change size
TEST_F(IptcDataTest_697, SortByTagPreservesSize_697) {
    iptcData_["Iptc.Application2.Keywords"] = "Keyword";
    iptcData_["Iptc.Application2.Caption"] = "Caption";
    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByKey on empty container doesn't crash
TEST_F(IptcDataTest_697, SortByKeyOnEmptyDoesNotCrash_697) {
    EXPECT_NO_THROW(iptcData_.sortByKey());
}

// Test sortByTag on empty container doesn't crash
TEST_F(IptcDataTest_697, SortByTagOnEmptyDoesNotCrash_697) {
    EXPECT_NO_THROW(iptcData_.sortByTag());
}

// Test count returns correct value
TEST_F(IptcDataTest_697, CountReturnsCorrectValue_697) {
    EXPECT_EQ(iptcData_.count(), 0u);
    iptcData_["Iptc.Application2.Caption"] = "Test";
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test detectCharset on empty container
TEST_F(IptcDataTest_697, DetectCharsetOnEmptyReturnsNullOrValid_697) {
    const char* charset = iptcData_.detectCharset();
    // On empty data, charset may be nullptr or a valid string
    // We just ensure it doesn't crash
    (void)charset;
}

// Test findKey with const IptcData
TEST_F(IptcDataTest_697, FindKeyConstVersion_697) {
    iptcData_["Iptc.Application2.Caption"] = "ConstTest";
    const Exiv2::IptcData& constData = iptcData_;
    auto it = constData.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "ConstTest");
}

// Test findId with const IptcData
TEST_F(IptcDataTest_697, FindIdConstVersion_697) {
    iptcData_["Iptc.Application2.Caption"] = "ConstIdTest";
    const Exiv2::IptcData& constData = iptcData_;
    // Caption is dataset 120, record 2
    auto it = constData.findId(120, 2);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "ConstIdTest");
}

// Test erase in the middle of multiple elements
TEST_F(IptcDataTest_697, EraseMiddleElement_697) {
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
    val1->read("First");
    iptcData_.add(key1, val1.get());

    Exiv2::IptcKey key2("Iptc.Application2.Keywords");
    Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::string);
    val2->read("Second");
    iptcData_.add(key2, val2.get());

    Exiv2::IptcKey key3("Iptc.Application2.City");
    Exiv2::Value::UniquePtr val3 = Exiv2::Value::create(Exiv2::string);
    val3->read("Third");
    iptcData_.add(key3, val3.get());

    EXPECT_EQ(iptcData_.size(), 3u);

    // Find and erase the second element
    auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    ASSERT_NE(it, iptcData_.end());
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.size(), 2u);

    // Verify second element is gone
    it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    EXPECT_EQ(it, iptcData_.end());
}

// Test iteration over elements
TEST_F(IptcDataTest_697, IterationOverElements_697) {
    iptcData_["Iptc.Application2.Caption"] = "Cap";
    iptcData_["Iptc.Application2.Keywords"] = "Key";

    int count = 0;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        count++;
    }
    EXPECT_EQ(static_cast<size_t>(count), iptcData_.size());
}

// Test adding non-repeatable key twice via operator[]
TEST_F(IptcDataTest_697, OperatorBracketOverwritesNonRepeatable_697) {
    iptcData_["Iptc.Application2.Caption"] = "First";
    iptcData_["Iptc.Application2.Caption"] = "Second";
    
    auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    ASSERT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Second");
}

// Test clear followed by add works correctly
TEST_F(IptcDataTest_697, ClearThenAddWorks_697) {
    iptcData_["Iptc.Application2.Caption"] = "Before clear";
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());

    iptcData_["Iptc.Application2.Caption"] = "After clear";
    EXPECT_EQ(iptcData_.size(), 1u);
    auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    ASSERT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "After clear");
}

// Test findId with record 0 (envelope record)
TEST_F(IptcDataTest_697, FindIdWithEnvelopeRecord_697) {
    // dataset 0 doesn't typically exist, should return end
    auto it = iptcData_.findId(0, 1);
    EXPECT_EQ(it, iptcData_.end());
}

// Test size and count consistency
TEST_F(IptcDataTest_697, SizeAndCountConsistency_697) {
    EXPECT_EQ(iptcData_.size(), iptcData_.count());
    
    iptcData_["Iptc.Application2.Caption"] = "Test";
    EXPECT_EQ(iptcData_.size(), iptcData_.count());
    
    iptcData_["Iptc.Application2.Keywords"] = "Key";
    EXPECT_EQ(iptcData_.size(), iptcData_.count());
}

}  // namespace
