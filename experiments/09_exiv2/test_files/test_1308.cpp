#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_1308 : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_1308, DefaultConstructorInitializesEmpty_1308) {

    EXPECT_TRUE(xmpData.empty());

    EXPECT_EQ(0, xmpData.count());

}



TEST_F(XmpDataTest_1308, AddKeyAndValueIncreasesCount_1308) {

    XmpKey key("Xmp.dc.subject");

    Value* value = new StringValue("test");

    int result = xmpData.add(key, value);

    EXPECT_EQ(0, result); // Assuming add returns 0 on success

    EXPECT_FALSE(xmpData.empty());

    EXPECT_EQ(1, xmpData.count());

}



TEST_F(XmpDataTest_1308, AddXmpdatumIncreasesCount_1308) {

    Xmpdatum datum("Xmp.dc.subject", "test");

    int result = xmpData.add(datum);

    EXPECT_EQ(0, result); // Assuming add returns 0 on success

    EXPECT_FALSE(xmpData.empty());

    EXPECT_EQ(1, xmpData.count());

}



TEST_F(XmpDataTest_1308, EraseElementDecreasesCount_1308) {

    XmpKey key("Xmp.dc.subject");

    Value* value = new StringValue("test");

    xmpData.add(key, value);

    auto it = xmpData.findKey(key);

    EXPECT_NE(xmpData.end(), it);



    xmpData.erase(it);

    EXPECT_TRUE(xmpData.empty());

    EXPECT_EQ(0, xmpData.count());

}



TEST_F(XmpDataTest_1308, FindExistingKeyReturnsValidIterator_1308) {

    XmpKey key("Xmp.dc.subject");

    Value* value = new StringValue("test");

    xmpData.add(key, value);



    auto it = xmpData.findKey(key);

    EXPECT_NE(xmpData.end(), it);

}



TEST_F(XmpDataTest_1308, FindNonExistingKeyReturnsEndIterator_1308) {

    XmpKey key("Xmp.dc.subject");



    auto it = xmpData.findKey(key);

    EXPECT_EQ(xmpData.end(), it);

}



TEST_F(XmpDataTest_1308, ClearRemovesAllElements_1308) {

    XmpKey key("Xmp.dc.subject");

    Value* value = new StringValue("test");

    xmpData.add(key, value);



    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

    EXPECT_EQ(0, xmpData.count());

}



TEST_F(XmpDataTest_1308, SortByKeyOrdersElements_1308) {

    XmpKey key1("Xmp.dc.subject");

    Value* value1 = new StringValue("test1");

    xmpData.add(key1, value1);



    XmpKey key2("Xmp.dc.creator");

    Value* value2 = new StringValue("test2");

    xmpData.add(key2, value2);



    xmpData.sortByKey();

    auto it = xmpData.begin();

    EXPECT_EQ("Xmp.dc.creator", (*it).key());

}



TEST_F(XmpDataTest_1308, UsePacketSetsAndReturnsCorrectValue_1308) {

    xmpData.usePacket(true);

    EXPECT_TRUE(xmpData.usePacket());



    xmpData.usePacket(false);

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1308, SetAndGetPacketWorksCorrectly_1308) {

    std::string packet = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">...</x:xmpmeta>";

    xmpData.setPacket(packet);

    EXPECT_EQ(packet, xmpData.xmpPacket());

}



TEST_F(XmpDataTest_1308, OperatorBracketSetsAndRetrievesValue_1308) {

    Xmpdatum& datum = xmpData["Xmp.dc.subject"];

    datum.setValue(new StringValue("test"));



    EXPECT_EQ("test", (*xmpData.findKey("Xmp.dc.subject")).value().toString());

}
