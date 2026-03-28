#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>

using namespace Exiv2;

class IptcDataFindKeyTest_696 : public ::testing::Test {
protected:
    IptcData iptcData_;

    void SetUp() override {
    }
};

// Test that findKey on an empty IptcData returns end()
TEST_F(IptcDataFindKeyTest_696, FindKeyInEmptyData_696) {
    IptcKey key("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(key);
    EXPECT_EQ(it, iptcData_.end());
}

// Test that findKey on const empty IptcData returns end()
TEST_F(IptcDataFindKeyTest_696, FindKeyConstInEmptyData_696) {
    const IptcData& constData = iptcData_;
    IptcKey key("Iptc.Application2.Caption");
    auto it = constData.findKey(key);
    EXPECT_EQ(it, constData.end());
}

// Test that findKey finds an existing entry
TEST_F(IptcDataFindKeyTest_696, FindKeyExistingEntry_696) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    iptcData_.add(key, &value);

    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->tag(), key.tag());
}

// Test that const findKey finds an existing entry
TEST_F(IptcDataFindKeyTest_696, ConstFindKeyExistingEntry_696) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    iptcData_.add(key, &value);

    const IptcData& constData = iptcData_;
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->tag(), key.tag());
}

// Test that findKey returns end() when key is not found
TEST_F(IptcDataFindKeyTest_696, FindKeyNonExistingEntry_696) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test caption");
    iptcData_.add(key1, &value);

    IptcKey key2("Iptc.Application2.Keywords");
    auto it = iptcData_.findKey(key2);
    EXPECT_EQ(it, iptcData_.end());
}

// Test that findKey finds the first occurrence when multiple entries exist with the same key
TEST_F(IptcDataFindKeyTest_696, FindKeyFirstOccurrence_696) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue value1;
    value1.read("keyword1");
    iptcData_.add(key, &value1);

    StringValue value2;
    value2.read("keyword2");
    iptcData_.add(key, &value2);

    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "keyword1");
}

// Test findKey with multiple different keys, ensuring correct one is found
TEST_F(IptcDataFindKeyTest_696, FindKeyAmongMultipleDifferentKeys_696) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1;
    val1.read("Caption text");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2;
    val2.read("keyword1");
    iptcData_.add(key2, &val2);

    IptcKey key3("Iptc.Application2.Byline");
    StringValue val3;
    val3.read("Author");
    iptcData_.add(key3, &val3);

    // Find the second key
    auto it = iptcData_.findKey(key2);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->tag(), key2.tag());
    EXPECT_EQ(it->toString(), "keyword1");

    // Find the third key
    auto it3 = iptcData_.findKey(key3);
    EXPECT_NE(it3, iptcData_.end());
    EXPECT_EQ(it3->tag(), key3.tag());
}

// Test that adding via operator[] and then finding works
TEST_F(IptcDataFindKeyTest_696, FindKeyAfterOperatorBracket_696) {
    iptcData_["Iptc.Application2.Caption"] = "Some caption";

    IptcKey key("Iptc.Application2.Caption");
    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());
}

// Test findKey after erasing the matching entry
TEST_F(IptcDataFindKeyTest_696, FindKeyAfterErase_696) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    iptcData_.add(key, &value);

    auto it = iptcData_.findKey(key);
    EXPECT_NE(it, iptcData_.end());

    iptcData_.erase(it);

    auto it2 = iptcData_.findKey(key);
    EXPECT_EQ(it2, iptcData_.end());
}

// Test findKey after clearing all data
TEST_F(IptcDataFindKeyTest_696, FindKeyAfterClear_696) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    iptcData_.add(key, &value);

    iptcData_.clear();

    auto it = iptcData_.findKey(key);
    EXPECT_EQ(it, iptcData_.end());
    EXPECT_TRUE(iptcData_.empty());
}

// Test findKey using tag/record constructor for IptcKey
TEST_F(IptcDataFindKeyTest_696, FindKeyUsingTagRecordConstructor_696) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Caption value");
    iptcData_.add(key, &value);

    // Create key using tag and record values
    IptcKey searchKey(key.tag(), key.record());
    auto it = iptcData_.findKey(searchKey);
    EXPECT_NE(it, iptcData_.end());
}

// Test findId as a related method
TEST_F(IptcDataFindKeyTest_696, FindIdExisting_696) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Caption");
    iptcData_.add(key, &value);

    auto it = iptcData_.findId(key.tag(), key.record());
    EXPECT_NE(it, iptcData_.end());
}

// Test findId non-existing
TEST_F(IptcDataFindKeyTest_696, FindIdNonExisting_696) {
    auto it = iptcData_.findId(9999, 9999);
    EXPECT_EQ(it, iptcData_.end());
}

// Test size and count consistency
TEST_F(IptcDataFindKeyTest_696, SizeAfterAdditions_696) {
    EXPECT_EQ(iptcData_.size(), 0u);
    EXPECT_TRUE(iptcData_.empty());

    IptcKey key("Iptc.Application2.Caption");
    StringValue value;
    value.read("Test");
    iptcData_.add(key, &value);

    EXPECT_EQ(iptcData_.size(), 1u);
    EXPECT_FALSE(iptcData_.empty());
}

// Test sortByKey doesn't break findKey
TEST_F(IptcDataFindKeyTest_696, FindKeyAfterSortByKey_696) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue val1;
    val1.read("keyword");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue val2;
    val2.read("caption");
    iptcData_.add(key2, &val2);

    iptcData_.sortByKey();

    auto it = iptcData_.findKey(key2);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "caption");
}

// Test sortByTag doesn't break findKey
TEST_F(IptcDataFindKeyTest_696, FindKeyAfterSortByTag_696) {
    IptcKey key1("Iptc.Application2.Keywords");
    StringValue val1;
    val1.read("keyword");
    iptcData_.add(key1, &val1);

    IptcKey key2("Iptc.Application2.Caption");
    StringValue val2;
    val2.read("caption");
    iptcData_.add(key2, &val2);

    iptcData_.sortByTag();

    auto it = iptcData_.findKey(key1);
    EXPECT_NE(it, iptcData_.end());
    EXPECT_EQ(it->toString(), "keyword");
}
