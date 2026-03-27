#include <gtest/gtest.h>
#include "exiv2/xmp_exiv2.hpp"

namespace Exiv2 {

// Test Fixture for XmpData class
class XmpDataTest_49 : public ::testing::Test {
protected:
    XmpData xmpData;

    // Optional setup and teardown can be added here if necessary
    void SetUp() override {}
    void TearDown() override {}
};

// TEST: Check that usePacket() returns the initial value of usePacket_ (false)
TEST_F(XmpDataTest_49, UsePacketReturnsDefault_49) {
    EXPECT_FALSE(xmpData.usePacket());
}

// TEST: Check setting usePacket value to true
TEST_F(XmpDataTest_49, UsePacketSetsTrue_49) {
    xmpData.usePacket(true);
    EXPECT_TRUE(xmpData.usePacket());
}

// TEST: Check setting usePacket value to false
TEST_F(XmpDataTest_49, UsePacketSetsFalse_49) {
    xmpData.usePacket(false);
    EXPECT_FALSE(xmpData.usePacket());
}

// TEST: Test setPacket() and xmpPacket() functions for consistency
TEST_F(XmpDataTest_49, SetAndGetXmpPacket_49) {
    std::string packet = "testPacket";
    xmpData.setPacket(packet);
    EXPECT_EQ(xmpData.xmpPacket(), packet);
}

// TEST: Verify empty() method (initial state should be empty)
TEST_F(XmpDataTest_49, EmptyReturnsTrueInitially_49) {
    EXPECT_TRUE(xmpData.empty());
}

// TEST: Test count() function (should return 0 initially)
TEST_F(XmpDataTest_49, CountReturnsZeroInitially_49) {
    EXPECT_EQ(xmpData.count(), 0);
}

// TEST: Test clear() function (should clear all entries)
TEST_F(XmpDataTest_49, ClearClearsAllData_49) {
    // Add some data to the XmpData instance
    xmpData.add(XmpKey("key1"), new XmpValue("value1"));
    xmpData.add(XmpKey("key2"), new XmpValue("value2"));
    EXPECT_FALSE(xmpData.empty());
    xmpData.clear();
    EXPECT_TRUE(xmpData.empty());
}

// TEST: Test add() function with valid data
TEST_F(XmpDataTest_49, AddValidData_49) {
    XmpKey key("key");
    XmpValue value("value");
    int result = xmpData.add(key, &value);
    EXPECT_EQ(result, 0);  // Assuming successful addition returns 0
}

// TEST: Test add() function with invalid data
TEST_F(XmpDataTest_49, AddInvalidData_49) {
    XmpKey key("invalidKey");
    XmpValue value("");  // Invalid empty value
    int result = xmpData.add(key, &value);
    EXPECT_NE(result, 0);  // Assuming failure returns non-zero
}

// TEST: Test findKey() method to retrieve a key
TEST_F(XmpDataTest_49, FindKeyReturnsCorrectValue_49) {
    XmpKey key("key1");
    XmpValue value("value1");
    xmpData.add(key, &value);
    auto found = xmpData.findKey(key);
    EXPECT_EQ(found->second, value);  // Assuming we get the correct value associated with the key
}

// TEST: Test erase() function
TEST_F(XmpDataTest_49, EraseRemovesKey_49) {
    XmpKey key("keyToErase");
    XmpValue value("value");
    xmpData.add(key, &value);
    auto it = xmpData.findKey(key);
    xmpData.erase(it);
    EXPECT_TRUE(xmpData.findKey(key) == xmpData.end());
}

}  // namespace Exiv2