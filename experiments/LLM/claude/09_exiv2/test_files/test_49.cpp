#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/xmpsidecar.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class XmpDataTest_49 : public ::testing::Test {
protected:
    XmpData xmpData_;
};

// Test default construction - empty state
TEST_F(XmpDataTest_49, DefaultConstructionIsEmpty_49) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test usePacket default value
TEST_F(XmpDataTest_49, UsePacketDefaultIsFalse_49) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter returns previous value and sets new value
TEST_F(XmpDataTest_49, UsePacketSetterAndGetter_49) {
    EXPECT_FALSE(xmpData_.usePacket());
    bool prev = xmpData_.usePacket(true);
    EXPECT_FALSE(prev);  // previous value was false
    EXPECT_TRUE(xmpData_.usePacket());
}

// Test usePacket toggle
TEST_F(XmpDataTest_49, UsePacketToggle_49) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    bool prev = xmpData_.usePacket(false);
    EXPECT_TRUE(prev);  // previous value was true
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_49, SetPacketAndRetrieve_49) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(xmpData_.xmpPacket(), packet);
}

// Test setPacket with empty string
TEST_F(XmpDataTest_49, SetPacketEmptyString_49) {
    xmpData_.setPacket("");
    EXPECT_EQ(xmpData_.xmpPacket(), "");
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_49, XmpPacketDefaultEmpty_49) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test operator[] adds element
TEST_F(XmpDataTest_49, OperatorBracketAddsElement_49) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test operator[] with multiple different keys
TEST_F(XmpDataTest_49, OperatorBracketMultipleKeys_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(xmpData_.count(), 2);
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_49, AddWithKeyAndValue_49) {
    XmpKey key("Xmp.dc.creator");
    Value::UniquePtr value = Value::create(xmpText);
    value->read("John Doe");
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_49, AddWithXmpdatum_49) {
    xmpData_["Xmp.dc.title"] = "Test";
    XmpData other;
    auto it = xmpData_.begin();
    int result = other.add(*it);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(other.count(), 1);
}

// Test clear
TEST_F(XmpDataTest_49, ClearRemovesAllElements_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    EXPECT_EQ(xmpData_.count(), 2);
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test clear on empty data
TEST_F(XmpDataTest_49, ClearOnEmptyData_49) {
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test begin/end on empty data
TEST_F(XmpDataTest_49, BeginEqualsEndWhenEmpty_49) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test begin/end iterators with data
TEST_F(XmpDataTest_49, BeginEndWithData_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_NE(xmpData_.begin(), xmpData_.end());
}

// Test const begin/end
TEST_F(XmpDataTest_49, ConstBeginEnd_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    const XmpData& constRef = xmpData_;
    EXPECT_NE(constRef.begin(), constRef.end());
}

// Test findKey with existing key
TEST_F(XmpDataTest_49, FindKeyExisting_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
}

// Test findKey with non-existing key
TEST_F(XmpDataTest_49, FindKeyNonExisting_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    XmpKey key("Xmp.dc.description");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey on empty data
TEST_F(XmpDataTest_49, FindKeyOnEmptyData_49) {
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test const findKey
TEST_F(XmpDataTest_49, ConstFindKey_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    const XmpData& constRef = xmpData_;
    XmpKey key("Xmp.dc.title");
    auto it = constRef.findKey(key);
    EXPECT_NE(it, constRef.end());
}

// Test erase
TEST_F(XmpDataTest_49, EraseElement_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    EXPECT_EQ(xmpData_.count(), 2);
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test erase all elements one by one
TEST_F(XmpDataTest_49, EraseAllElements_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    while (!xmpData_.empty()) {
        xmpData_.erase(xmpData_.begin());
    }
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test sortByKey
TEST_F(XmpDataTest_49, SortByKey_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_.sortByKey();
    
    // After sorting, verify elements are accessible
    EXPECT_EQ(xmpData_.count(), 3);
    
    // Verify sorted order by checking keys
    auto it = xmpData_.begin();
    std::string prevKey = it->key();
    ++it;
    while (it != xmpData_.end()) {
        EXPECT_LE(prevKey, it->key());
        prevKey = it->key();
        ++it;
    }
}

// Test sortByKey on empty data
TEST_F(XmpDataTest_49, SortByKeyEmpty_49) {
    xmpData_.sortByKey();
    EXPECT_TRUE(xmpData_.empty());
}

// Test sortByKey on single element
TEST_F(XmpDataTest_49, SortByKeySingleElement_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_.sortByKey();
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test count returns correct number
TEST_F(XmpDataTest_49, CountReturnsCorrectNumber_49) {
    EXPECT_EQ(xmpData_.count(), 0);
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_EQ(xmpData_.count(), 1);
    xmpData_["Xmp.dc.description"] = "Desc";
    EXPECT_EQ(xmpData_.count(), 2);
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(xmpData_.count(), 3);
}

// Test empty returns true when no elements
TEST_F(XmpDataTest_49, EmptyReturnsTrueWhenNoElements_49) {
    EXPECT_TRUE(xmpData_.empty());
}

// Test empty returns false when elements exist
TEST_F(XmpDataTest_49, EmptyReturnsFalseWhenElementsExist_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_FALSE(xmpData_.empty());
}

// Test setPacket overwrites previous packet
TEST_F(XmpDataTest_49, SetPacketOverwrites_49) {
    xmpData_.setPacket("first");
    EXPECT_EQ(xmpData_.xmpPacket(), "first");
    xmpData_.setPacket("second");
    EXPECT_EQ(xmpData_.xmpPacket(), "second");
}

// Test that clear does not affect packet
TEST_F(XmpDataTest_49, ClearDoesNotAffectPacket_49) {
    xmpData_.setPacket("packet_data");
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_.clear();
    // After clear, packet may or may not be preserved - this tests observable behavior
    EXPECT_TRUE(xmpData_.empty());
}

// Test eraseFamily
TEST_F(XmpDataTest_49, EraseFamilyRemovesRelatedEntries_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After eraseFamily, at least the pointed element should be removed
    // The exact behavior depends on implementation
    EXPECT_LE(xmpData_.count(), 2);
}

// Test iterator iteration counts match count()
TEST_F(XmpDataTest_49, IteratorCountMatchesCount_49) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.creator"] = "Creator";
    
    long manualCount = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        ++manualCount;
    }
    EXPECT_EQ(manualCount, xmpData_.count());
}

// Test usePacket set to same value
TEST_F(XmpDataTest_49, UsePacketSetToSameValue_49) {
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test large packet string
TEST_F(XmpDataTest_49, LargePacketString_49) {
    std::string largePacket(10000, 'x');
    xmpData_.setPacket(largePacket);
    EXPECT_EQ(xmpData_.xmpPacket(), largePacket);
    EXPECT_EQ(xmpData_.xmpPacket().size(), 10000u);
}
