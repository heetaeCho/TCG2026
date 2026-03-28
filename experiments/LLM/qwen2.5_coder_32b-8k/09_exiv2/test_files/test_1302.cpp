#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_1302 : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_1302, OperatorBracket_NewKey_1302) {

    const std::string key = "Xmp.dc.title";

    Xmpdatum& datum = xmpData[key];

    EXPECT_EQ(datum.key(), key);

}



TEST_F(XmpDataTest_1302, OperatorBracket_ExistingKey_1302) {

    const std::string key = "Xmp.dc.description";

    Xmpdatum& firstAccess = xmpData[key];

    Xmpdatum& secondAccess = xmpData[key];

    EXPECT_EQ(&firstAccess, &secondAccess);

}



TEST_F(XmpDataTest_1302, Add_SingleKey_1302) {

    const std::string key = "Xmp.dc.creator";

    XmpKey xmpKey(key);

    int result = xmpData.add(xmpKey, nullptr);

    EXPECT_EQ(result, 0); // Assuming add returns 0 on success

}



TEST_F(XmpDataTest_1302, Add_MultipleKeys_1302) {

    const std::string key1 = "Xmp.dc.creator";

    const std::string key2 = "Xmp.dc.rights";

    XmpKey xmpKey1(key1);

    XmpKey xmpKey2(key2);

    int result1 = xmpData.add(xmpKey1, nullptr);

    int result2 = xmpData.add(xmpKey2, nullptr);

    EXPECT_EQ(result1, 0); // Assuming add returns 0 on success

    EXPECT_EQ(result2, 0); // Assuming add returns 0 on success

}



TEST_F(XmpDataTest_1302, Clear_AllKeys_1302) {

    const std::string key = "Xmp.dc.title";

    XmpKey xmpKey(key);

    xmpData.add(xmpKey, nullptr);

    EXPECT_FALSE(xmpData.empty());

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1302, Count_AfterAdd_1302) {

    const std::string key = "Xmp.dc.title";

    XmpKey xmpKey(key);

    xmpData.add(xmpKey, nullptr);

    EXPECT_EQ(xmpData.count(), 1);

}



TEST_F(XmpDataTest_1302, Count_AfterClear_1302) {

    const std::string key = "Xmp.dc.title";

    XmpKey xmpKey(key);

    xmpData.add(xmpKey, nullptr);

    xmpData.clear();

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1302, FindKey_ExistingKey_1302) {

    const std::string key = "Xmp.dc.title";

    Xmpdatum& datum = xmpData[key];

    XmpKey xmpKey(key);

    auto pos = xmpData.findKey(xmpKey);

    EXPECT_NE(pos, xmpData.end());

}



TEST_F(XmpDataTest_1302, FindKey_NonExistingKey_1302) {

    const std::string key = "Xmp.dc.title";

    XmpKey xmpKey(key);

    auto pos = xmpData.findKey(xmpKey);

    EXPECT_EQ(pos, xmpData.end());

}



TEST_F(XmpDataTest_1302, Empty_AfterConstruction_1302) {

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1302, Empty_AfterAdd_1302) {

    const std::string key = "Xmp.dc.title";

    XmpKey xmpKey(key);

    xmpData.add(xmpKey, nullptr);

    EXPECT_FALSE(xmpData.empty());

}



TEST_F(XmpDataTest_1302, Begin_End_Iteration_1302) {

    const std::string key = "Xmp.dc.title";

    Xmpdatum& datum = xmpData[key];

    auto itBegin = xmpData.begin();

    auto itEnd = xmpData.end();

    EXPECT_NE(itBegin, itEnd);

}



TEST_F(XmpDataTest_1302, SortByKey_SingleKey_1302) {

    const std::string key = "Xmp.dc.title";

    Xmpdatum& datum = xmpData[key];

    xmpData.sortByKey();

    EXPECT_EQ(xmpData.begin()->key(), key);

}



TEST_F(XmpDataTest_1302, SortByKey_MultipleKeys_1302) {

    const std::string key1 = "Xmp.dc.creator";

    const std::string key2 = "Xmp.dc.rights";

    Xmpdatum& datum1 = xmpData[key1];

    Xmpdatum& datum2 = xmpData[key2];

    xmpData.sortByKey();

    auto itBegin = xmpData.begin();

    EXPECT_EQ(itBegin->key(), key1);

    ++itBegin;

    EXPECT_EQ(itBegin->key(), key2);

}



TEST_F(XmpDataTest_1302, Erase_SingleKey_1302) {

    const std::string key = "Xmp.dc.title";

    Xmpdatum& datum = xmpData[key];

    XmpKey xmpKey(key);

    auto pos = xmpData.findKey(xmpKey);

    EXPECT_NE(pos, xmpData.end());

    xmpData.erase(pos);

    pos = xmpData.findKey(xmpKey);

    EXPECT_EQ(pos, xmpData.end());

}



TEST_F(XmpDataTest_1302, EraseFamily_SingleKey_1302) {

    const std::string key = "Xmp.dc.title";

    Xmpdatum& datum = xmpData[key];

    XmpKey xmpKey(key);

    auto pos = xmpData.findKey(xmpKey);

    EXPECT_NE(pos, xmpData.end());

    xmpData.eraseFamily(pos);

    pos = xmpData.findKey(xmpKey);

    EXPECT_EQ(pos, xmpData.end());

}



TEST_F(XmpDataTest_1302, UsePacket_DefaultValue_1302) {

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1302, UsePacket_SetTrue_1302) {

    xmpData.usePacket(true);

    EXPECT_TRUE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1302, UsePacket_SetFalse_1302) {

    xmpData.usePacket(false);

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_1302, SetPacket_GetPacket_1302) {

    const std::string packet = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">...</x:xmpmeta>";

    xmpData.setPacket(packet);

    EXPECT_EQ(xmpData.xmpPacket(), packet);

}
