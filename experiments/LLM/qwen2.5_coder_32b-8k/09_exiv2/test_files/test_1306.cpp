#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_1306, ClearEmptiesData_1306) {

    // Add some data to ensure it's not empty

    xmpData.add(XmpKey("Xmp.test.key"), nullptr);

    EXPECT_FALSE(xmpData.empty());



    // Clear the data and check if it becomes empty

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1306, CountReturnsZeroAfterClear_1306) {

    // Add some data to ensure count is not zero

    xmpData.add(XmpKey("Xmp.test.key"), nullptr);

    EXPECT_EQ(xmpData.count(), 1);



    // Clear the data and check if count becomes zero

    xmpData.clear();

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1306, UsePacketSetsAndGetCorrectly_1306) {

    // Default value should be false

    EXPECT_FALSE(xmpData.usePacket());



    // Set to true and check

    xmpData.usePacket(true);

    EXPECT_TRUE(xmpData.usePacket());



    // Set back to false and check

    xmpData.usePacket(false);

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1306, PacketSetsAndGetCorrectly_1306) {

    const std::string testPacket = "<x:xmpmeta></x:xmpmeta>";



    // Default value should be empty

    EXPECT_TRUE(xmpData.xmpPacket().empty());



    // Set a packet and check if it's set correctly

    xmpData.setPacket(testPacket);

    EXPECT_EQ(xmpData.xmpPacket(), testPacket);

}



TEST_F(XmpDataTest_1306, AddIncreasesCount_1306) {

    // Initially count should be zero

    EXPECT_EQ(xmpData.count(), 0);



    // Add one item and check if count increases

    xmpData.add(XmpKey("Xmp.test.key"), nullptr);

    EXPECT_EQ(xmpData.count(), 1);



    // Add another item and check again

    xmpData.add(XmpKey("Xmp.test.anotherkey"), nullptr);

    EXPECT_EQ(xmpData.count(), 2);

}



TEST_F(XmpDataTest_1306, EraseDecreasesCount_1306) {

    // Add two items

    Xmpdatum datum1 = xmpData.add(XmpKey("Xmp.test.key1"), nullptr);

    Xmpdatum datum2 = xmpData.add(XmpKey("Xmp.test.key2"), nullptr);

    EXPECT_EQ(xmpData.count(), 2);



    // Erase one item and check if count decreases

    xmpData.erase(datum1.first);

    EXPECT_EQ(xmpData.count(), 1);



    // Erase the other item and check again

    xmpData.erase(datum2.first);

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1306, EraseFamilyDecreasesCount_1306) {

    // Add multiple items with the same namespace

    Xmpdatum datum1 = xmpData.add(XmpKey("Xmp.test.key1"), nullptr);

    Xmpdatum datum2 = xmpData.add(XmpKey("Xmp.test.key2"), nullptr);

    EXPECT_EQ(xmpData.count(), 2);



    // Erase family of items and check if count decreases

    xmpData.eraseFamily(datum1.first);

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1306, IteratorFunctionsWorkCorrectly_1306) {

    // Add some data

    Xmpdatum datum1 = xmpData.add(XmpKey("Xmp.test.key1"), nullptr);

    Xmpdatum datum2 = xmpData.add(XmpKey("Xmp.test.key2"), nullptr);



    // Check if begin and end work correctly

    EXPECT_NE(xmpData.begin(), xmpData.end());



    // Iterate through data and check if it contains added items

    bool found1 = false;

    bool found2 = false;

    for (auto it = xmpData.begin(); it != xmpData.end(); ++it) {

        if (it->key() == "Xmp.test.key1") found1 = true;

        if (it->key() == "Xmp.test.key2") found2 = true;

    }

    EXPECT_TRUE(found1);

    EXPECT_TRUE(found2);

}



TEST_F(XmpDataTest_1306, FindKeyReturnsCorrectIterator_1306) {

    // Add some data

    xmpData.add(XmpKey("Xmp.test.key"), nullptr);



    // Find the key and check if iterator is correct

    auto it = xmpData.findKey(XmpKey("Xmp.test.key"));

    EXPECT_NE(it, xmpData.end());

    EXPECT_EQ(it->key(), "Xmp.test.key");



    // Find a non-existing key and check if iterator points to end

    auto notFoundIt = xmpData.findKey(XmpKey("Xmp.test.nonexisting"));

    EXPECT_EQ(notFoundIt, xmpData.end());

}



TEST_F(XmpDataTest_1306, SortByKeyOrdersCorrectly_1306) {

    // Add some data in unordered way

    xmpData.add(XmpKey("Xmp.test.key2"), nullptr);

    xmpData.add(XmpKey("Xmp.test.key1"), nullptr);



    // Sort the data by key

    xmpData.sortByKey();



    // Iterate through data and check if it's ordered correctly

    auto it = xmpData.begin();

    EXPECT_EQ(it->key(), "Xmp.test.key1");

    ++it;

    EXPECT_EQ(it->key(), "Xmp.test.key2");

}



TEST_F(XmpDataTest_1306, EmptyReturnsCorrectly_1306) {

    // Initially should be empty

    EXPECT_TRUE(xmpData.empty());



    // Add one item and check again

    xmpData.add(XmpKey("Xmp.test.key"), nullptr);

    EXPECT_FALSE(xmpData.empty());



    // Clear the data and check if it's empty

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}
