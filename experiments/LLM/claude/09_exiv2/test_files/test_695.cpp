#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>

using namespace Exiv2;

class IptcDataTest_695 : public ::testing::Test {
protected:
    IptcData iptcData_;
};

// Test that a newly created IptcData is empty
TEST_F(IptcDataTest_695, DefaultConstructedIsEmpty_695) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.count(), 0u);
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test adding a single Iptcdatum returns 0 (success)
TEST_F(IptcDataTest_695, AddSingleDatumReturnsZero_695) {
    // Keywords (dataset 25, record 2) is repeatable
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    int result = iptcData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test adding multiple repeatable entries succeeds
TEST_F(IptcDataTest_695, AddMultipleRepeatableEntries_695) {
    // Keywords is repeatable
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum1(key, nullptr);
    datum1.setValue("keyword1");
    Iptcdatum datum2(key, nullptr);
    datum2.setValue("keyword2");

    EXPECT_EQ(iptcData_.add(datum1), 0);
    EXPECT_EQ(iptcData_.add(datum2), 0);
    EXPECT_EQ(iptcData_.count(), 2u);
}

// Test adding a non-repeatable entry twice returns error code 6
TEST_F(IptcDataTest_695, AddNonRepeatableDuplicateReturnsError_695) {
    // ObjectName (dataset 5, record 2) is typically non-repeatable
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum1(key, nullptr);
    datum1.setValue("name1");
    Iptcdatum datum2(key, nullptr);
    datum2.setValue("name2");

    int result1 = iptcData_.add(datum1);
    EXPECT_EQ(result1, 0);

    int result2 = iptcData_.add(datum2);
    EXPECT_EQ(result2, 6);

    // Only one entry should exist
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test add(const IptcKey&, const Value*) overload
TEST_F(IptcDataTest_695, AddWithKeyAndValueReturnsZero_695) {
    IptcKey key("Iptc.Application2.Keywords");
    int result = iptcData_.add(key, nullptr);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test findKey returns end() for non-existent key
TEST_F(IptcDataTest_695, FindKeyNotFoundReturnsEnd_695) {
    IptcKey key("Iptc.Application2.Keywords");
    auto it = iptcData_.findKey(key);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findKey returns valid iterator for existing key
TEST_F(IptcDataTest_695, FindKeyFoundReturnsValidIterator_695) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum.setValue("testKeyword");
    iptcData_.add(datum);

    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->key(), "Iptc.Application2.Keywords");
}

// Test findId returns end() when no matching entry exists
TEST_F(IptcDataTest_695, FindIdNotFoundReturnsEnd_695) {
    auto it = iptcData_.findId(25, 2); // Keywords
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId returns valid iterator for existing entry
TEST_F(IptcDataTest_695, FindIdFoundReturnsValidIterator_695) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum.setValue("testKeyword");
    iptcData_.add(datum);

    auto it = iptcData_.findId(datum.tag(), datum.record());
    EXPECT_NE(it, iptcData_.end());
}

// Test erase removes entry
TEST_F(IptcDataTest_695, EraseRemovesEntry_695) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum.setValue("toDelete");
    iptcData_.add(datum);
    EXPECT_EQ(iptcData_.count(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_EQ(iptcData_.count(), 0u);
    EXPECT_TRUE(iptcData_.empty());
}

// Test clear removes all entries
TEST_F(IptcDataTest_695, ClearRemovesAllEntries_695) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum1(key, nullptr);
    datum1.setValue("kw1");
    Iptcdatum datum2(key, nullptr);
    datum2.setValue("kw2");

    iptcData_.add(datum1);
    iptcData_.add(datum2);
    EXPECT_EQ(iptcData_.count(), 2u);

    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test operator[] creates entry if not found
TEST_F(IptcDataTest_695, OperatorBracketCreatesEntry_695) {
    EXPECT_TRUE(iptcData_.empty());
    Iptcdatum& datum = iptcData_["Iptc.Application2.Keywords"];
    // After using operator[], the entry should exist
    EXPECT_FALSE(iptcData_.empty());
    EXPECT_EQ(datum.key(), "Iptc.Application2.Keywords");
}

// Test sortByKey does not change count
TEST_F(IptcDataTest_695, SortByKeyPreservesCount_695) {
    IptcKey key1("Iptc.Application2.Keywords");
    Iptcdatum datum1(key1, nullptr);
    datum1.setValue("beta");

    IptcKey key2("Iptc.Application2.Caption");
    Iptcdatum datum2(key2, nullptr);
    datum2.setValue("alpha");

    iptcData_.add(datum1);
    iptcData_.add(datum2);
    EXPECT_EQ(iptcData_.count(), 2u);

    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.count(), 2u);
}

// Test sortByTag does not change count
TEST_F(IptcDataTest_695, SortByTagPreservesCount_695) {
    IptcKey key1("Iptc.Application2.Keywords");
    Iptcdatum datum1(key1, nullptr);
    datum1.setValue("beta");

    IptcKey key2("Iptc.Application2.Caption");
    Iptcdatum datum2(key2, nullptr);
    datum2.setValue("alpha");

    iptcData_.add(datum1);
    iptcData_.add(datum2);

    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.count(), 2u);
}

// Test begin() == end() when empty
TEST_F(IptcDataTest_695, BeginEqualsEndWhenEmpty_695) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test begin() != end() after adding an entry
TEST_F(IptcDataTest_695, BeginNotEqualsEndAfterAdd_695) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    iptcData_.add(datum);
    EXPECT_NE(iptcData_.begin(), iptcData_.end());
}

// Test that after adding a non-repeatable entry once and erasing it, we can add it again
TEST_F(IptcDataTest_695, AddNonRepeatableAfterEraseSucceeds_695) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("name1");

    EXPECT_EQ(iptcData_.add(datum), 0);
    EXPECT_EQ(iptcData_.count(), 1u);

    iptcData_.erase(iptcData_.begin());
    EXPECT_TRUE(iptcData_.empty());

    // Should be able to add again after erase
    Iptcdatum datum2(key, nullptr);
    datum2.setValue("name2");
    EXPECT_EQ(iptcData_.add(datum2), 0);
    EXPECT_EQ(iptcData_.count(), 1u);
}

// Test Iptcdatum key, tag, record consistency
TEST_F(IptcDataTest_695, IptcdatumKeyTagRecordConsistency_695) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Keywords");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.tagName(), "Keywords");
    // tag() should return the dataset number for Keywords (25)
    EXPECT_EQ(datum.tag(), 25u);
    // record() should return the record id for Application2 (2)
    EXPECT_EQ(datum.record(), 2u);
}

// Test Iptcdatum setValue and toString
TEST_F(IptcDataTest_695, IptcdatumSetValueAndToString_695) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum.setValue("hello");
    EXPECT_EQ(datum.toString(), "hello");
}

// Test Iptcdatum copy constructor
TEST_F(IptcDataTest_695, IptcdatumCopyConstructor_695) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum.setValue("original");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "original");
}

// Test Iptcdatum assignment operator
TEST_F(IptcDataTest_695, IptcdatumAssignmentOperator_695) {
    IptcKey key1("Iptc.Application2.Keywords");
    Iptcdatum datum1(key1, nullptr);
    datum1.setValue("first");

    IptcKey key2("Iptc.Application2.Caption");
    Iptcdatum datum2(key2, nullptr);
    datum2.setValue("second");

    datum1 = datum2;
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), "second");
}

// Test detectCharset returns something (possibly null) on empty data
TEST_F(IptcDataTest_695, DetectCharsetOnEmptyData_695) {
    const char* charset = iptcData_.detectCharset();
    // Just verify it doesn't crash; charset may be nullptr for empty data
    (void)charset;
}

// Test size reflects data content
TEST_F(IptcDataTest_695, SizeReflectsContent_695) {
    size_t initialSize = iptcData_.size();
    EXPECT_EQ(initialSize, 0u);

    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    datum.setValue("test");
    iptcData_.add(datum);

    EXPECT_GT(iptcData_.size(), 0u);
}
