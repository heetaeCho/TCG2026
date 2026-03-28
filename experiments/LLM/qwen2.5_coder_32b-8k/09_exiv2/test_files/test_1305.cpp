#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_1305 : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_1305, FindKey_NormalOperation_1305) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, nullptr);

    auto it = xmpData.findKey(key);

    EXPECT_NE(it, xmpData.end());

}



TEST_F(XmpDataTest_1305, FindKey_NotFound_1305) {

    XmpKey key("Xmp.dc.title");

    auto it = xmpData.findKey(key);

    EXPECT_EQ(it, xmpData.end());

}



TEST_F(XmpDataTest_1305, Add_NormalOperation_1305) {

    XmpKey key("Xmp.dc.title");

    int result = xmpData.add(key, nullptr);

    EXPECT_GE(result, 0);

}



TEST_F(XmpDataTest_1305, Count_AfterAdd_1305) {

    long initialCount = xmpData.count();

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, nullptr);

    EXPECT_EQ(xmpData.count(), initialCount + 1);

}



TEST_F(XmpDataTest_1305, Count_BoundaryConditions_1305) {

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1305, Clear_NormalOperation_1305) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, nullptr);

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1305, Empty_AfterClear_1305) {

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1305, SortByKey_NormalOperation_1305) {

    XmpKey key1("Xmp.dc.title");

    XmpKey key2("Xmp.dc.description");

    xmpData.add(key1, nullptr);

    xmpData.add(key2, nullptr);

    xmpData.sortByKey();

    auto it = xmpData.begin();

    EXPECT_EQ(it->key(), "Xmp.dc.description");

    ++it;

    EXPECT_EQ(it->key(), "Xmp.dc.title");

}



TEST_F(XmpDataTest_1305, Iterator_BeginEnd_1305) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, nullptr);

    auto it = xmpData.begin();

    EXPECT_NE(it, xmpData.end());

    ++it;

    EXPECT_EQ(it, xmpData.end());

}



TEST_F(XmpDataTest_1305, OperatorBracket_NormalOperation_1305) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, nullptr);

    Xmpdatum& datum = xmpData[key.key()];

    EXPECT_EQ(datum.key(), key.key());

}



TEST_F(XmpDataTest_1305, Erase_NormalOperation_1305) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, nullptr);

    auto it = xmpData.findKey(key);

    EXPECT_NE(it, xmpData.end());

    xmpData.erase(it);

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1305, EraseFamily_NormalOperation_1305) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, nullptr);

    auto it = xmpData.begin();

    EXPECT_NE(it, xmpData.end());

    xmpData.eraseFamily(it);

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1305, UsePacket_SetGet_1305) {

    bool initialValue = xmpData.usePacket();

    xmpData.usePacket(!initialValue);

    EXPECT_EQ(xmpData.usePacket(), !initialValue);

}



TEST_F(XmpDataTest_1305, XmpPacket_SetGet_1305) {

    std::string packet("XMP Packet");

    xmpData.setPacket(packet);

    EXPECT_EQ(xmpData.xmpPacket(), packet);

}
