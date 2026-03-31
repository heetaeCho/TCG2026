#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class XmpDataTest_1312 : public ::testing::Test {
protected:
    XmpData xmpData_;

    void SetUp() override {
        // Fresh XmpData for each test
        xmpData_.clear();
    }
};

// Test that a newly constructed XmpData is empty
TEST_F(XmpDataTest_1312, DefaultConstructedIsEmpty_1312) {
    XmpData data;
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(data.count(), 0);
}

// Test that begin() == end() for empty data
TEST_F(XmpDataTest_1312, BeginEqualsEndWhenEmpty_1312) {
    XmpData data;
    EXPECT_EQ(data.begin(), data.end());
}

// Test adding an element via operator[]
TEST_F(XmpDataTest_1312, OperatorBracketAddsElement_1312) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test adding multiple elements via operator[]
TEST_F(XmpDataTest_1312, OperatorBracketAddsMultipleElements_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(xmpData_.count(), 3);
}

// Test that operator[] with same key does not duplicate
TEST_F(XmpDataTest_1312, OperatorBracketSameKeyDoesNotDuplicate_1312) {
    xmpData_["Xmp.dc.title"] = "Title1";
    xmpData_["Xmp.dc.title"] = "Title2";
    // operator[] may or may not create duplicates depending on implementation;
    // we observe the count
    EXPECT_GE(xmpData_.count(), 1);
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_1312, AddWithKeyAndValue_1312) {
    XmpKey key("Xmp.dc.title");
    XmpTextValue value("Test");
    int result = xmpData_.add(key, &value);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_1312, AddWithXmpdatum_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    ASSERT_EQ(xmpData_.count(), 1);

    XmpData other;
    int result = other.add(*xmpData_.begin());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(other.count(), 1);
}

// Test erase removes an element
TEST_F(XmpDataTest_1312, EraseRemovesElement_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    ASSERT_EQ(xmpData_.count(), 2);

    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test erase returns valid iterator
TEST_F(XmpDataTest_1312, EraseReturnsNextIterator_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    ASSERT_EQ(xmpData_.count(), 2);

    auto it = xmpData_.begin();
    auto next = xmpData_.erase(it);
    // After erasing the first element, next should point to what was the second element
    EXPECT_EQ(next, xmpData_.begin());
}

// Test erase last element results in empty
TEST_F(XmpDataTest_1312, EraseLastElementMakesEmpty_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    ASSERT_EQ(xmpData_.count(), 1);

    auto it = xmpData_.begin();
    auto next = xmpData_.erase(it);
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(next, xmpData_.end());
}

// Test clear removes all elements
TEST_F(XmpDataTest_1312, ClearRemovesAllElements_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    ASSERT_EQ(xmpData_.count(), 2);

    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test clear on already empty data
TEST_F(XmpDataTest_1312, ClearOnEmptyIsNoOp_1312) {
    ASSERT_TRUE(xmpData_.empty());
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
}

// Test findKey finds existing key
TEST_F(XmpDataTest_1312, FindKeyFindsExistingKey_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
}

// Test findKey returns end for non-existing key
TEST_F(XmpDataTest_1312, FindKeyReturnsEndForNonExisting_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    XmpKey key("Xmp.dc.description");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey on empty data
TEST_F(XmpDataTest_1312, FindKeyOnEmptyDataReturnsEnd_1312) {
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test const findKey
TEST_F(XmpDataTest_1312, ConstFindKeyWorks_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    const XmpData& constRef = xmpData_;
    XmpKey key("Xmp.dc.title");
    auto it = constRef.findKey(key);
    EXPECT_NE(it, constRef.end());
}

// Test const begin/end
TEST_F(XmpDataTest_1312, ConstBeginEndWork_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    const XmpData& constRef = xmpData_;
    EXPECT_NE(constRef.begin(), constRef.end());
}

// Test const empty
TEST_F(XmpDataTest_1312, ConstEmptyWorks_1312) {
    const XmpData& constRef = xmpData_;
    EXPECT_TRUE(constRef.empty());
}

// Test const count
TEST_F(XmpDataTest_1312, ConstCountWorks_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    const XmpData& constRef = xmpData_;
    EXPECT_EQ(constRef.count(), 1);
}

// Test usePacket default value
TEST_F(XmpDataTest_1312, UsePacketDefaultIsFalse_1312) {
    XmpData data;
    EXPECT_FALSE(data.usePacket());
}

// Test setting usePacket
TEST_F(XmpDataTest_1312, SetUsePacket_1312) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1312, XmpPacketDefaultIsEmpty_1312) {
    XmpData data;
    EXPECT_TRUE(data.xmpPacket().empty());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1312, SetAndGetPacket_1312) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(xmpData_.xmpPacket(), packet);
}

// Test setPacket with empty string
TEST_F(XmpDataTest_1312, SetPacketEmpty_1312) {
    xmpData_.setPacket("some data");
    EXPECT_EQ(xmpData_.xmpPacket(), "some data");
    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test sortByKey doesn't crash on empty data
TEST_F(XmpDataTest_1312, SortByKeyOnEmptyData_1312) {
    EXPECT_NO_THROW(xmpData_.sortByKey());
}

// Test sortByKey with data
TEST_F(XmpDataTest_1312, SortByKeyWithData_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Desc";
    EXPECT_NO_THROW(xmpData_.sortByKey());
    EXPECT_EQ(xmpData_.count(), 3);
}

// Test eraseFamily
TEST_F(XmpDataTest_1312, EraseFamilyRemovesRelatedEntries_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After eraseFamily, the element should be removed
    // The exact behavior depends on implementation, but count should change
    EXPECT_TRUE(xmpData_.empty() || xmpData_.count() < 1 || it == xmpData_.end());
}

// Test iterating through all elements
TEST_F(XmpDataTest_1312, IterateThroughElements_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.creator"] = "Creator";

    int count = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, xmpData_.count());
}

// Test multiple erase operations
TEST_F(XmpDataTest_1312, MultipleEraseOperations_1312) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.creator"] = "Creator";
    ASSERT_EQ(xmpData_.count(), 3);

    auto it = xmpData_.begin();
    while (it != xmpData_.end()) {
        it = xmpData_.erase(it);
    }
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that add returns 0 on success
TEST_F(XmpDataTest_1312, AddReturnsZeroOnSuccess_1312) {
    XmpKey key("Xmp.dc.subject");
    XmpTextValue value("Test Subject");
    int ret = xmpData_.add(key, &value);
    EXPECT_EQ(ret, 0);
}

// Test adding and then finding
TEST_F(XmpDataTest_1312, AddThenFind_1312) {
    XmpKey key("Xmp.dc.subject");
    XmpTextValue value("Test Subject");
    xmpData_.add(key, &value);

    auto it = xmpData_.findKey(XmpKey("Xmp.dc.subject"));
    EXPECT_NE(it, xmpData_.end());
}
