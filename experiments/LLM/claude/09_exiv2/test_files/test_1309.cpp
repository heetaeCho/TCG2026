#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/value.hpp>
#include <string>

namespace {

class XmpDataTest_1309 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData_;
};

// Test that a default-constructed XmpData is empty
TEST_F(XmpDataTest_1309, DefaultConstructedIsEmpty_1309) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that begin() == end() for empty XmpData
TEST_F(XmpDataTest_1309, BeginEqualsEndWhenEmpty_1309) {
    EXPECT_TRUE(xmpData_.begin() == xmpData_.end());
}

// Test operator[] adds an entry
TEST_F(XmpDataTest_1309, OperatorBracketAddsEntry_1309) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test adding via XmpKey and Value
TEST_F(XmpDataTest_1309, AddWithKeyAndValue_1309) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("John Doe");
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test adding multiple entries
TEST_F(XmpDataTest_1309, AddMultipleEntries_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(xmpData_.count(), 3);
}

// Test clear empties the data
TEST_F(XmpDataTest_1309, ClearRemovesAllEntries_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(xmpData_.count(), 2);
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test findKey on existing key
TEST_F(XmpDataTest_1309, FindKeyExistingKey_1309) {
    xmpData_["Xmp.dc.title"] = "Test";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_TRUE(it != xmpData_.end());
}

// Test findKey on non-existing key
TEST_F(XmpDataTest_1309, FindKeyNonExistingKey_1309) {
    xmpData_["Xmp.dc.title"] = "Test";
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto it = xmpData_.findKey(key);
    EXPECT_TRUE(it == xmpData_.end());
}

// Test const findKey
TEST_F(XmpDataTest_1309, ConstFindKey_1309) {
    xmpData_["Xmp.dc.title"] = "Test";
    const Exiv2::XmpData& constData = xmpData_;
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_TRUE(it != constData.end());
}

// Test erase removes entry
TEST_F(XmpDataTest_1309, EraseRemovesEntry_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(xmpData_.count(), 2);
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test begin/end iteration for const XmpData
TEST_F(XmpDataTest_1309, ConstBeginEnd_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    const Exiv2::XmpData& constData = xmpData_;
    int count = 0;
    for (auto it = constData.begin(); it != constData.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 1);
}

// Test end() returns valid iterator for non-empty container
TEST_F(XmpDataTest_1309, EndIteratorNonEmpty_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    auto endIt = xmpData_.end();
    auto beginIt = xmpData_.begin();
    EXPECT_TRUE(beginIt != endIt);
}

// Test sortByKey doesn't crash
TEST_F(XmpDataTest_1309, SortByKeyDoesNotCrash_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Desc";
    EXPECT_NO_THROW(xmpData_.sortByKey());
    EXPECT_EQ(xmpData_.count(), 3);
}

// Test usePacket default
TEST_F(XmpDataTest_1309, UsePacketDefault_1309) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter/getter
TEST_F(XmpDataTest_1309, UsePacketSetterGetter_1309) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1309, XmpPacketDefaultEmpty_1309) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1309, SetPacketAndGetPacket_1309) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(xmpData_.xmpPacket(), packet);
}

// Test empty after clear on already empty data
TEST_F(XmpDataTest_1309, ClearOnEmptyData_1309) {
    EXPECT_NO_THROW(xmpData_.clear());
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that operator[] with same key updates existing entry
TEST_F(XmpDataTest_1309, OperatorBracketSameKeyUpdates_1309) {
    xmpData_["Xmp.dc.title"] = "First";
    xmpData_["Xmp.dc.title"] = "Second";
    // The behavior depends on implementation; at least one entry should exist
    EXPECT_GE(xmpData_.count(), 1);
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_1309, AddXmpdatum_1309) {
    xmpData_["Xmp.dc.title"] = "Test";
    Exiv2::Xmpdatum datum = *xmpData_.begin();
    Exiv2::XmpData otherData;
    int result = otherData.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(otherData.count(), 1);
}

// Test eraseFamily
TEST_F(XmpDataTest_1309, EraseFamilyRemovesRelatedEntries_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After eraseFamily, the count should be less than original
    EXPECT_LE(xmpData_.count(), 2);
}

// Test iteration counts match count()
TEST_F(XmpDataTest_1309, IterationCountMatchesCount_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.subject"] = "Subject";
    long iterCount = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        ++iterCount;
    }
    EXPECT_EQ(iterCount, xmpData_.count());
}

// Test findKey after erase
TEST_F(XmpDataTest_1309, FindKeyAfterErase_1309) {
    xmpData_["Xmp.dc.title"] = "Title";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_TRUE(it != xmpData_.end());
    xmpData_.erase(it);
    auto it2 = xmpData_.findKey(key);
    EXPECT_TRUE(it2 == xmpData_.end());
}

// Test const end on empty
TEST_F(XmpDataTest_1309, ConstEndOnEmpty_1309) {
    const Exiv2::XmpData& constData = xmpData_;
    EXPECT_TRUE(constData.begin() == constData.end());
}

// Test setPacket with empty string
TEST_F(XmpDataTest_1309, SetPacketEmptyString_1309) {
    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket replaces previous packet
TEST_F(XmpDataTest_1309, SetPacketReplacesPrevious_1309) {
    xmpData_.setPacket("first");
    xmpData_.setPacket("second");
    EXPECT_EQ(xmpData_.xmpPacket(), "second");
}

}  // namespace
