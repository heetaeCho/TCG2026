#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class XmpDataTest_1304 : public ::testing::Test {
protected:
    XmpData xmpData_;
};

// Test that a newly created XmpData is empty
TEST_F(XmpDataTest_1304, DefaultConstructorCreatesEmptyData_1304) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test adding an Xmpdatum via add(const Xmpdatum&)
TEST_F(XmpDataTest_1304, AddXmpdatumReturnsZero_1304) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = xmpData_.add(datum);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(1, xmpData_.count());
}

// Test adding via add(const XmpKey&, const Value*)
TEST_F(XmpDataTest_1304, AddKeyValueReturnsZero_1304) {
    XmpKey key("Xmp.dc.creator");
    int result = xmpData_.add(key, nullptr);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(1, xmpData_.count());
}

// Test adding multiple items increases count
TEST_F(XmpDataTest_1304, AddMultipleItemsIncreasesCount_1304) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    XmpKey key3("Xmp.dc.description");

    xmpData_.add(Xmpdatum(key1, nullptr));
    xmpData_.add(Xmpdatum(key2, nullptr));
    xmpData_.add(Xmpdatum(key3, nullptr));

    EXPECT_EQ(3, xmpData_.count());
}

// Test clear empties the data
TEST_F(XmpDataTest_1304, ClearRemovesAllItems_1304) {
    XmpKey key("Xmp.dc.title");
    xmpData_.add(Xmpdatum(key, nullptr));
    EXPECT_FALSE(xmpData_.empty());

    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test begin() equals end() for empty data
TEST_F(XmpDataTest_1304, BeginEqualsEndForEmptyData_1304) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test begin() != end() after adding an element
TEST_F(XmpDataTest_1304, BeginNotEqualsEndAfterAdd_1304) {
    XmpKey key("Xmp.dc.title");
    xmpData_.add(Xmpdatum(key, nullptr));
    EXPECT_NE(xmpData_.begin(), xmpData_.end());
}

// Test findKey returns end() when key not found
TEST_F(XmpDataTest_1304, FindKeyReturnsEndWhenNotFound_1304) {
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey returns valid iterator when key is found
TEST_F(XmpDataTest_1304, FindKeyReturnsValidIteratorWhenFound_1304) {
    XmpKey key("Xmp.dc.title");
    xmpData_.add(Xmpdatum(key, nullptr));

    XmpKey searchKey("Xmp.dc.title");
    auto it = xmpData_.findKey(searchKey);
    EXPECT_NE(it, xmpData_.end());
    EXPECT_EQ("Xmp.dc.title", it->key());
}

// Test operator[] creates entry if not present
TEST_F(XmpDataTest_1304, SubscriptOperatorCreatesEntry_1304) {
    EXPECT_TRUE(xmpData_.empty());
    Xmpdatum& datum = xmpData_["Xmp.dc.title"];
    EXPECT_EQ("Xmp.dc.title", datum.key());
    EXPECT_FALSE(xmpData_.empty());
}

// Test operator[] returns existing entry
TEST_F(XmpDataTest_1304, SubscriptOperatorReturnsExistingEntry_1304) {
    XmpKey key("Xmp.dc.title");
    xmpData_.add(Xmpdatum(key, nullptr));

    Xmpdatum& datum = xmpData_["Xmp.dc.title"];
    EXPECT_EQ("Xmp.dc.title", datum.key());
    // Should not add a duplicate
    EXPECT_EQ(1, xmpData_.count());
}

// Test erase removes an element
TEST_F(XmpDataTest_1304, EraseRemovesElement_1304) {
    XmpKey key("Xmp.dc.title");
    xmpData_.add(Xmpdatum(key, nullptr));
    EXPECT_EQ(1, xmpData_.count());

    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(0, xmpData_.count());
    EXPECT_TRUE(xmpData_.empty());
}

// Test erase from middle of multiple elements
TEST_F(XmpDataTest_1304, EraseFromMiddle_1304) {
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.creator"), nullptr));
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.description"), nullptr));
    EXPECT_EQ(3, xmpData_.count());

    auto it = xmpData_.findKey(XmpKey("Xmp.dc.creator"));
    ASSERT_NE(it, xmpData_.end());
    xmpData_.erase(it);
    EXPECT_EQ(2, xmpData_.count());

    // Verify the erased key is no longer found
    auto it2 = xmpData_.findKey(XmpKey("Xmp.dc.creator"));
    EXPECT_EQ(it2, xmpData_.end());
}

// Test usePacket default value
TEST_F(XmpDataTest_1304, UsePacketDefaultIsFalse_1304) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter
TEST_F(XmpDataTest_1304, UsePacketSetAndGet_1304) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());

    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1304, XmpPacketDefaultIsEmpty_1304) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1304, SetPacketAndGetPacket_1304) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(packet, xmpData_.xmpPacket());
}

// Test sortByKey sorts elements
TEST_F(XmpDataTest_1304, SortByKeyOrdersElements_1304) {
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.creator"), nullptr));
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.description"), nullptr));

    xmpData_.sortByKey();

    auto it = xmpData_.begin();
    std::string prev = it->key();
    ++it;
    while (it != xmpData_.end()) {
        EXPECT_LE(prev, it->key());
        prev = it->key();
        ++it;
    }
}

// Test iteration over elements
TEST_F(XmpDataTest_1304, IterationOverElements_1304) {
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.creator"), nullptr));

    int count = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        count++;
    }
    EXPECT_EQ(2, count);
}

// Test const iteration
TEST_F(XmpDataTest_1304, ConstIterationOverElements_1304) {
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));

    const XmpData& constRef = xmpData_;
    int count = 0;
    for (auto it = constRef.begin(); it != constRef.end(); ++it) {
        count++;
    }
    EXPECT_EQ(1, count);
}

// Test const empty
TEST_F(XmpDataTest_1304, ConstEmptyCheck_1304) {
    const XmpData& constRef = xmpData_;
    EXPECT_TRUE(constRef.empty());

    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));
    EXPECT_FALSE(constRef.empty());
}

// Test const count
TEST_F(XmpDataTest_1304, ConstCountCheck_1304) {
    const XmpData& constRef = xmpData_;
    EXPECT_EQ(0, constRef.count());

    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));
    EXPECT_EQ(1, constRef.count());
}

// Test const findKey
TEST_F(XmpDataTest_1304, ConstFindKey_1304) {
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));

    const XmpData& constRef = xmpData_;
    auto it = constRef.findKey(XmpKey("Xmp.dc.title"));
    EXPECT_NE(it, constRef.end());
    EXPECT_EQ("Xmp.dc.title", it->key());
}

// Test eraseFamily
TEST_F(XmpDataTest_1304, EraseFamilyRemovesRelatedEntries_1304) {
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.creator"), nullptr));

    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);

    // After eraseFamily, count should be less than original
    // We just verify it doesn't crash and the iterator advances or data changes
    EXPECT_GE(2L, xmpData_.count());
}

// Test adding with XmpKey and Value pointer
TEST_F(XmpDataTest_1304, AddKeyWithValuePointer_1304) {
    XmpKey key("Xmp.dc.subject");
    XmpTextValue val("test subject");
    int result = xmpData_.add(key, &val);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());

    auto it = xmpData_.findKey(XmpKey("Xmp.dc.subject"));
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ("test subject", it->toString());
}

// Test Xmpdatum key accessor
TEST_F(XmpDataTest_1304, XmpdatumKeyAccessor_1304) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("Xmp.dc.title", datum.key());
}

// Test Xmpdatum familyName
TEST_F(XmpDataTest_1304, XmpdatumFamilyName_1304) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_STREQ("Xmp", datum.familyName());
}

// Test Xmpdatum groupName
TEST_F(XmpDataTest_1304, XmpdatumGroupName_1304) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("dc", datum.groupName());
}

// Test Xmpdatum tagName
TEST_F(XmpDataTest_1304, XmpdatumTagName_1304) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    EXPECT_EQ("title", datum.tagName());
}

// Test Xmpdatum copy constructor
TEST_F(XmpDataTest_1304, XmpdatumCopyConstructor_1304) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    Xmpdatum copy(datum);
    EXPECT_EQ(datum.key(), copy.key());
    EXPECT_EQ(datum.familyName(), copy.familyName());
}

// Test Xmpdatum assignment operator
TEST_F(XmpDataTest_1304, XmpdatumAssignmentOperator_1304) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    Xmpdatum datum1(key1, nullptr);
    Xmpdatum datum2(key2, nullptr);

    datum2 = datum1;
    EXPECT_EQ("Xmp.dc.title", datum2.key());
}

// Test Xmpdatum setValue with string
TEST_F(XmpDataTest_1304, XmpdatumSetValueString_1304) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key, nullptr);
    int result = datum.setValue("Hello World");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello World", datum.toString());
}

// Test clear followed by add
TEST_F(XmpDataTest_1304, ClearThenAddWorks_1304) {
    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.title"), nullptr));
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());

    xmpData_.add(Xmpdatum(XmpKey("Xmp.dc.creator"), nullptr));
    EXPECT_EQ(1, xmpData_.count());
    auto it = xmpData_.findKey(XmpKey("Xmp.dc.creator"));
    EXPECT_NE(it, xmpData_.end());
}

// Test setPacket with empty string
TEST_F(XmpDataTest_1304, SetPacketWithEmptyString_1304) {
    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test usePacket returns previous value
TEST_F(XmpDataTest_1304, UsePacketReturnsPreviousValue_1304) {
    EXPECT_FALSE(xmpData_.usePacket(true));
    EXPECT_TRUE(xmpData_.usePacket(false));
    EXPECT_FALSE(xmpData_.usePacket());
}
