#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <sstream>

namespace {

class IptcDataTest_44 : public ::testing::Test {
protected:
    Exiv2::IptcData iptcData_;
};

// Test that a newly constructed IptcData is empty
TEST_F(IptcDataTest_44, DefaultConstructedIsEmpty_44) {
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_EQ(iptcData_.count(), 0u);
}

// Test that begin() == end() for empty container
TEST_F(IptcDataTest_44, BeginEqualsEndWhenEmpty_44) {
    EXPECT_EQ(iptcData_.begin(), iptcData_.end());
}

// Test adding an Iptcdatum via IptcKey and Value
TEST_F(IptcDataTest_44, AddWithKeyAndValue_44) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test caption");
    int result = iptcData_.add(key, value.get());
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test adding an Iptcdatum directly
TEST_F(IptcDataTest_44, AddIptcdatum_44) {
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Hello World");
    int result = iptcData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(iptcData_.size(), 1u);
}

// Test adding multiple entries increases size
TEST_F(IptcDataTest_44, AddMultipleEntries_44) {
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum1.setValue("Caption");
    iptcData_.add(datum1);

    Exiv2::Iptcdatum datum2(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum2.setValue("Keyword1");
    iptcData_.add(datum2);

    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test clear empties the container
TEST_F(IptcDataTest_44, ClearEmptiesData_44) {
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test");
    iptcData_.add(datum);
    EXPECT_FALSE(iptcData_.empty());

    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test operator[] creates entry if not present
TEST_F(IptcDataTest_44, OperatorBracketCreatesEntry_44) {
    EXPECT_TRUE(iptcData_.empty());
    Exiv2::Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    (void)datum;
    EXPECT_FALSE(iptcData_.empty());
    EXPECT_GE(iptcData_.size(), 1u);
}

// Test operator[] returns existing entry
TEST_F(IptcDataTest_44, OperatorBracketReturnsExisting_44) {
    iptcData_["Iptc.Application2.Caption"].setValue("First");
    Exiv2::Iptcdatum& datum = iptcData_["Iptc.Application2.Caption"];
    EXPECT_EQ(datum.toString(), "First");
}

// Test findKey on existing key
TEST_F(IptcDataTest_44, FindKeyExisting_44) {
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Found me");
    iptcData_.add(datum);

    Exiv2::IptcKey key("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "Found me");
}

// Test findKey on non-existing key returns end
TEST_F(IptcDataTest_44, FindKeyNonExisting_44) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(key);
    EXPECT_EQ(it, iptcData_.end());
}

// Test findId on existing dataset/record
TEST_F(IptcDataTest_44, FindIdExisting_44) {
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test");
    iptcData_.add(datum);

    // Caption is dataset 120, record 2
    auto it = iptcData_.findId(120, 2);
    EXPECT_NE(it, iptcData_.end());
}

// Test findId on non-existing dataset/record returns end
TEST_F(IptcDataTest_44, FindIdNonExisting_44) {
    auto it = iptcData_.findId(9999, 9999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test erase removes an element
TEST_F(IptcDataTest_44, EraseRemovesElement_44) {
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("To be erased");
    iptcData_.add(datum);
    EXPECT_EQ(iptcData_.size(), 1u);

    auto it = iptcData_.begin();
    iptcData_.erase(it);
    EXPECT_TRUE(iptcData_.empty());
}

// Test erase returns valid iterator
TEST_F(IptcDataTest_44, EraseReturnsValidIterator_44) {
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum1.setValue("First");
    iptcData_.add(datum1);

    Exiv2::Iptcdatum datum2(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum2.setValue("Second");
    iptcData_.add(datum2);

    auto it = iptcData_.erase(iptcData_.begin());
    EXPECT_EQ(iptcData_.size(), 1u);
    // The returned iterator should be valid (either pointing to next or end)
    EXPECT_TRUE(it == iptcData_.begin() || it == iptcData_.end());
}

// Test sortByKey does not change size
TEST_F(IptcDataTest_44, SortByKeyPreservesSize_44) {
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum1.setValue("Keyword");
    iptcData_.add(datum1);

    Exiv2::Iptcdatum datum2(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum2.setValue("Caption");
    iptcData_.add(datum2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByKey();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test sortByTag does not change size
TEST_F(IptcDataTest_44, SortByTagPreservesSize_44) {
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum1.setValue("Keyword");
    iptcData_.add(datum1);

    Exiv2::Iptcdatum datum2(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum2.setValue("Caption");
    iptcData_.add(datum2);

    size_t sizeBefore = iptcData_.size();
    iptcData_.sortByTag();
    EXPECT_EQ(iptcData_.size(), sizeBefore);
}

// Test count returns the number of elements
TEST_F(IptcDataTest_44, CountMatchesSize_44) {
    EXPECT_EQ(iptcData_.count(), iptcData_.size());

    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test");
    iptcData_.add(datum);

    EXPECT_EQ(iptcData_.count(), iptcData_.size());
}

// Test clear on already empty container
TEST_F(IptcDataTest_44, ClearOnEmptyIsNoOp_44) {
    EXPECT_TRUE(iptcData_.empty());
    iptcData_.clear();
    EXPECT_TRUE(iptcData_.empty());
    EXPECT_EQ(iptcData_.size(), 0u);
}

// Test adding duplicate keys (IPTC allows repeatable datasets like Keywords)
TEST_F(IptcDataTest_44, AddDuplicateRepeatableKeys_44) {
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum1.setValue("Keyword1");
    iptcData_.add(datum1);

    Exiv2::Iptcdatum datum2(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum2.setValue("Keyword2");
    iptcData_.add(datum2);

    EXPECT_EQ(iptcData_.size(), 2u);
}

// Test detectCharset on empty data
TEST_F(IptcDataTest_44, DetectCharsetOnEmpty_44) {
    const char* charset = iptcData_.detectCharset();
    // On empty data, detectCharset may return nullptr or some default
    // We just ensure it doesn't crash
    (void)charset;
}

// Test detectCharset with data containing CodedCharacterSet
TEST_F(IptcDataTest_44, DetectCharsetWithData_44) {
    // Add a CodedCharacterSet entry for UTF-8 (ESC % G = 0x1B 0x25 0x47)
    Exiv2::IptcKey key("Iptc.Envelope.CharacterSet");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("\033%G");
    iptcData_.add(key, value.get());

    const char* charset = iptcData_.detectCharset();
    // With UTF-8 coded character set, should detect UTF-8
    if (charset != nullptr) {
        EXPECT_STREQ(charset, "UTF-8");
    }
}

// Test const findKey
TEST_F(IptcDataTest_44, ConstFindKey_44) {
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Const test");
    iptcData_.add(datum);

    const Exiv2::IptcData& constData = iptcData_;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "Const test");
}

// Test const findId
TEST_F(IptcDataTest_44, ConstFindId_44) {
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test");
    iptcData_.add(datum);

    const Exiv2::IptcData& constData = iptcData_;
    // Caption is dataset 120, record 2
    auto it = constData.findId(120, 2);
    EXPECT_NE(it, constData.end());
}

// Test iteration over elements
TEST_F(IptcDataTest_44, IterateOverElements_44) {
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum1.setValue("Caption");
    iptcData_.add(datum1);

    Exiv2::Iptcdatum datum2(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum2.setValue("Keyword");
    iptcData_.add(datum2);

    size_t count = 0;
    for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2u);
}

// Test sortByKey actually sorts
TEST_F(IptcDataTest_44, SortByKeyOrdering_44) {
    // Add in reverse order
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum1.setValue("KW");
    iptcData_.add(datum1);

    Exiv2::Iptcdatum datum2(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum2.setValue("Cap");
    iptcData_.add(datum2);

    iptcData_.sortByKey();

    // After sorting by key, Caption should come before Keywords alphabetically
    auto it = iptcData_.begin();
    std::string firstKey = it->key();
    ++it;
    std::string secondKey = it->key();
    EXPECT_LE(firstKey, secondKey);
}

// Test adding with IptcKey and null value pointer behavior
TEST_F(IptcDataTest_44, AddWithNullValue_44) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    // Passing nullptr - testing boundary behavior
    // This may or may not throw; we test it doesn't crash if it returns error
    try {
        int result = iptcData_.add(key, nullptr);
        // If it succeeds, just check result
        (void)result;
    } catch (...) {
        // If it throws, that's also acceptable behavior
    }
}

}  // namespace
