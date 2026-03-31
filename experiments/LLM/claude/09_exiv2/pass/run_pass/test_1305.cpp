#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class XmpDataTest_1305 : public ::testing::Test {
protected:
    XmpData xmpData_;

    void SetUp() override {
        // Fresh XmpData for each test
    }
};

// Test that a newly constructed XmpData is empty
TEST_F(XmpDataTest_1305, DefaultConstructor_IsEmpty_1305) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that begin() == end() for empty container
TEST_F(XmpDataTest_1305, BeginEqualsEnd_WhenEmpty_1305) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test adding an element via operator[] and verifying non-empty
TEST_F(XmpDataTest_1305, OperatorBracket_AddsElement_1305) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test findKey finds an existing key
TEST_F(XmpDataTest_1305, FindKey_ExistingKey_ReturnsValidIterator_1305) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
}

// Test findKey on const XmpData finds an existing key
TEST_F(XmpDataTest_1305, FindKey_ConstExistingKey_ReturnsValidIterator_1305) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    const XmpData& constData = xmpData_;
    XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
}

// Test findKey returns end() for non-existing key
TEST_F(XmpDataTest_1305, FindKey_NonExistingKey_ReturnsEnd_1305) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    XmpKey key("Xmp.dc.description");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey on const XmpData returns end() for non-existing key
TEST_F(XmpDataTest_1305, FindKey_ConstNonExistingKey_ReturnsEnd_1305) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    const XmpData& constData = xmpData_;
    XmpKey key("Xmp.dc.description");
    auto it = constData.findKey(key);
    EXPECT_EQ(it, constData.end());
}

// Test findKey on empty XmpData returns end()
TEST_F(XmpDataTest_1305, FindKey_EmptyData_ReturnsEnd_1305) {
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey on const empty XmpData returns end()
TEST_F(XmpDataTest_1305, FindKey_ConstEmptyData_ReturnsEnd_1305) {
    const XmpData& constData = xmpData_;
    XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_EQ(it, constData.end());
}

// Test adding multiple elements and finding each
TEST_F(XmpDataTest_1305, FindKey_MultipleElements_FindsEach_1305) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_["Xmp.dc.creator"] = "Creator";

    EXPECT_EQ(xmpData_.count(), 3);

    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.description");
    XmpKey key3("Xmp.dc.creator");

    EXPECT_NE(xmpData_.findKey(key1), xmpData_.end());
    EXPECT_NE(xmpData_.findKey(key2), xmpData_.end());
    EXPECT_NE(xmpData_.findKey(key3), xmpData_.end());
}

// Test clear empties the data
TEST_F(XmpDataTest_1305, Clear_RemovesAllElements_1305) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_FALSE(xmpData_.empty());

    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test findKey after clear returns end()
TEST_F(XmpDataTest_1305, FindKey_AfterClear_ReturnsEnd_1305) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_.clear();

    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(xmpData_.findKey(key), xmpData_.end());
}

// Test erase removes element and findKey no longer finds it
TEST_F(XmpDataTest_1305, Erase_RemovesElement_FindKeyReturnsEnd_1305) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";

    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    ASSERT_NE(it, xmpData_.end());

    xmpData_.erase(it);
    EXPECT_EQ(xmpData_.findKey(key), xmpData_.end());
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_1305, Add_WithKeyAndValue_IncreasesCount_1305) {
    XmpKey key("Xmp.dc.title");
    Value::UniquePtr val = Value::create(xmpText);
    val->read("Test");
    int result = xmpData_.add(key, val.get());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(xmpData_.count(), 1);
    EXPECT_NE(xmpData_.findKey(key), xmpData_.end());
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_1305, Add_WithXmpdatum_IncreasesCount_1305) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_EQ(xmpData_.count(), 1);

    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    ASSERT_NE(it, xmpData_.end());

    XmpData otherData;
    int result = otherData.add(*it);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(otherData.count(), 1);
}

// Test usePacket default value
TEST_F(XmpDataTest_1305, UsePacket_DefaultIsFalse_1305) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter and getter
TEST_F(XmpDataTest_1305, UsePacket_SetAndGet_1305) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1305, SetPacket_AndGetPacket_1305) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(xmpData_.xmpPacket(), packet);
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1305, XmpPacket_DefaultIsEmpty_1305) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test sortByKey doesn't crash and data remains intact
TEST_F(XmpDataTest_1305, SortByKey_DataRemains_1305) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Desc";

    long countBefore = xmpData_.count();
    xmpData_.sortByKey();
    EXPECT_EQ(xmpData_.count(), countBefore);

    // All keys should still be findable
    EXPECT_NE(xmpData_.findKey(XmpKey("Xmp.dc.title")), xmpData_.end());
    EXPECT_NE(xmpData_.findKey(XmpKey("Xmp.dc.creator")), xmpData_.end());
    EXPECT_NE(xmpData_.findKey(XmpKey("Xmp.dc.description")), xmpData_.end());
}

// Test findKey with const_iterator returns correct tag name
TEST_F(XmpDataTest_1305, FindKey_ReturnsCorrectElement_1305) {
    xmpData_["Xmp.dc.title"] = "MyTitle";
    xmpData_["Xmp.dc.description"] = "MyDesc";

    const XmpData& constData = xmpData_;
    XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    ASSERT_NE(it, constData.end());
    EXPECT_EQ(it->key(), "Xmp.dc.title");
}

// Test finding among many elements (boundary)
TEST_F(XmpDataTest_1305, FindKey_ManyElements_FindsCorrectOne_1305) {
    // Add several elements
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.subject"] = "Subject";
    xmpData_["Xmp.dc.date"] = "2023-01-01";

    const XmpData& constData = xmpData_;

    // Find the last added element
    XmpKey key("Xmp.dc.date");
    auto it = constData.findKey(key);
    ASSERT_NE(it, constData.end());
    EXPECT_EQ(it->key(), "Xmp.dc.date");
}

// Test that eraseFamily works and findKey returns end afterward
TEST_F(XmpDataTest_1305, EraseFamily_RemovesElements_1305) {
    xmpData_["Xmp.dc.title"] = "Title";

    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    ASSERT_NE(it, xmpData_.end());

    xmpData_.eraseFamily(it);
    // After erasing, findKey should return end
    EXPECT_EQ(xmpData_.findKey(key), xmpData_.end());
}

// Test count matches number of unique keys added
TEST_F(XmpDataTest_1305, Count_MatchesNumberOfAddedKeys_1305) {
    EXPECT_EQ(xmpData_.count(), 0);

    xmpData_["Xmp.dc.title"] = "A";
    EXPECT_EQ(xmpData_.count(), 1);

    xmpData_["Xmp.dc.description"] = "B";
    EXPECT_EQ(xmpData_.count(), 2);

    xmpData_["Xmp.dc.creator"] = "C";
    EXPECT_EQ(xmpData_.count(), 3);
}

// Test that operator[] on same key updates rather than adds
TEST_F(XmpDataTest_1305, OperatorBracket_SameKeyUpdatesValue_1305) {
    xmpData_["Xmp.dc.title"] = "First";
    long countAfterFirst = xmpData_.count();

    xmpData_["Xmp.dc.title"] = "Second";
    // Count should remain the same (update, not add)
    EXPECT_EQ(xmpData_.count(), countAfterFirst);

    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ(it->toString(), "Second");
}

// Test const begin and end iteration
TEST_F(XmpDataTest_1305, ConstIteration_AllElementsAccessible_1305) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";

    const XmpData& constData = xmpData_;
    long count = 0;
    for (auto it = constData.begin(); it != constData.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, constData.count());
}
