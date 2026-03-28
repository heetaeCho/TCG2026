#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_1310 : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_1310, EmptyReturnsTrueWhenNoElements_1310) {

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1310, CountReturnsZeroWhenEmpty_1310) {

    EXPECT_EQ(0, xmpData.count());

}



TEST_F(XmpDataTest_1310, EmptyReturnsFalseAfterAddingElement_1310) {

    XmpKey key("Xmp.dc.creator");

    Value* value = new StringValue("John Doe");

    xmpData.add(key, value);

    EXPECT_FALSE(xmpData.empty());

}



TEST_F(XmpDataTest_1310, CountReturnsOneAfterAddingElement_1310) {

    XmpKey key("Xmp.dc.creator");

    Value* value = new StringValue("John Doe");

    xmpData.add(key, value);

    EXPECT_EQ(1, xmpData.count());

}



TEST_F(XmpDataTest_1310, ClearRemovesAllElements_1310) {

    XmpKey key("Xmp.dc.creator");

    Value* value = new StringValue("John Doe");

    xmpData.add(key, value);

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1310, ClearSetsCountToZero_1310) {

    XmpKey key("Xmp.dc.creator");

    Value* value = new StringValue("John Doe");

    xmpData.add(key, value);

    xmpData.clear();

    EXPECT_EQ(0, xmpData.count());

}



TEST_F(XmpDataTest_1310, FindKeyReturnsEndWhenNotFound_1310) {

    XmpKey key("Xmp.dc.creator");

    auto it = xmpData.findKey(key);

    EXPECT_EQ(xmpData.end(), it);

}



TEST_F(XmpDataTest_1310, FindKeyReturnsIteratorToElementWhenFound_1310) {

    XmpKey key("Xmp.dc.creator");

    Value* value = new StringValue("John Doe");

    xmpData.add(key, value);

    auto it = xmpData.findKey(key);

    EXPECT_NE(xmpData.end(), it);

}



TEST_F(XmpDataTest_1310, UsePacketReturnsDefaultValue_1310) {

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1310, UsePacketSetsAndReturnsNewValue_1310) {

    xmpData.usePacket(true);

    EXPECT_TRUE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1310, SetPacketAndGetPacketRoundTrip_1310) {

    std::string packet = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"/>";

    xmpData.setPacket(packet);

    EXPECT_EQ(packet, xmpData.xmpPacket());

}



TEST_F(XmpDataTest_1310, EraseRemovesElementAndDecreasesCount_1310) {

    XmpKey key("Xmp.dc.creator");

    Value* value = new StringValue("John Doe");

    auto it = xmpData.add(key, value);

    EXPECT_EQ(1, xmpData.count());

    xmpData.erase(it);

    EXPECT_EQ(0, xmpData.count());

}



TEST_F(XmpDataTest_1310, EraseFamilyRemovesAllElementsWithSamePrefixAndDecreasesCount_1310) {

    XmpKey key1("Xmp.dc.creator");

    Value* value1 = new StringValue("John Doe");

    xmpData.add(key1, value1);



    XmpKey key2("Xmp.dc.rights");

    Value* value2 = new StringValue("Copyright 2023");

    xmpData.add(key2, value2);



    auto it = xmpData.findKey(key1);

    xmpData.eraseFamily(it);

    EXPECT_EQ(0, xmpData.count());

}



TEST_F(XmpDataTest_1310, SortByKeyOrdersElementsCorrectly_1310) {

    XmpKey key1("Xmp.dc.rights");

    Value* value1 = new StringValue("Copyright 2023");

    xmpData.add(key1, value1);



    XmpKey key2("Xmp.dc.creator");

    Value* value2 = new StringValue("John Doe");

    xmpData.add(key2, value2);



    xmpData.sortByKey();

    auto it = xmpData.begin();

    EXPECT_EQ(key2, (*it).key());

    ++it;

    EXPECT_EQ(key1, (*it).key());

}



TEST_F(XmpDataTest_1310, OperatorBracketAddsNewElement_1310) {

    Xmpdatum& datum = xmpData["Xmp.dc.creator"];

    datum.setValue(new StringValue("John Doe"));

    EXPECT_FALSE(xmpData.empty());

    EXPECT_EQ(1, xmpData.count());

}



TEST_F(XmpDataTest_1310, OperatorBracketUpdatesExistingElement_1310) {

    XmpKey key("Xmp.dc.creator");

    Value* value = new StringValue("John Doe");

    xmpData.add(key, value);



    Xmpdatum& datum = xmpData["Xmp.dc.creator"];

    datum.setValue(new StringValue("Jane Doe"));

    auto it = xmpData.findKey(key);

    EXPECT_EQ("Jane Doe", (*it).toString());

}
