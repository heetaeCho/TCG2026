#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_1309 : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_1309, EmptyInitially_1309) {

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1309, CountZeroInitially_1309) {

    EXPECT_EQ(0L, xmpData.count());

}



TEST_F(XmpDataTest_1309, BeginEqualsEndInitially_1309) {

    EXPECT_EQ(xmpData.begin(), xmpData.end());

}



TEST_F(XmpDataTest_1309, UsePacketDefaultFalse_1309) {

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1309, SetAndGetUsePacket_1309) {

    xmpData.usePacket(true);

    EXPECT_TRUE(xmpData.usePacket());

    xmpData.usePacket(false);

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1309, SetAndGetXmpPacket_1309) {

    std::string packet = "<x:xmpmeta xmlns:x='adobe:ns:meta/'/>";



    xmpData.setPacket(packet);

    EXPECT_EQ(packet, xmpData.xmpPacket());

}



TEST_F(XmpDataTest_1309, AddXmpDatumIncreasesCount_1309) {

    Xmpdatum datum("test:key", "value");

    xmpData.add(datum);

    EXPECT_EQ(1L, xmpData.count());

}



TEST_F(XmpDataTest_1309, FindKeyReturnsEndIfNotFound_1309) {

    XmpKey key("nonexistent:key");

    EXPECT_EQ(xmpData.end(), xmpData.findKey(key));

}



TEST_F(XmpDataTest_1309, ClearResetsCountAndEmptiness_1309) {

    Xmpdatum datum("test:key", "value");

    xmpData.add(datum);

    xmpData.clear();

    EXPECT_EQ(0L, xmpData.count());

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1309, SortByKeyDoesNotChangeCount_1309) {

    Xmpdatum datum("test:key", "value");

    xmpData.add(datum);

    long initialCount = xmpData.count();

    xmpData.sortByKey();

    EXPECT_EQ(initialCount, xmpData.count());

}



TEST_F(XmpDataTest_1309, EraseDecreasesCount_1309) {

    Xmpdatum datum("test:key", "value");

    xmpData.add(datum);

    auto it = xmpData.begin();

    xmpData.erase(it);

    EXPECT_EQ(0L, xmpData.count());

}



TEST_F(XmpDataTest_1309, EraseFamilyDecreasesCount_1309) {

    Xmpdatum datum("test:key", "value");

    xmpData.add(datum);

    auto it = xmpData.begin();

    xmpData.eraseFamily(it);

    EXPECT_EQ(0L, xmpData.count());

}



TEST_F(XmpDataTest_1309, OperatorBracketAddsNewEntry_1309) {

    xmpData["test:key"] = Xmpdatum("test:key", "value");

    EXPECT_EQ(1L, xmpData.count());

}
