#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_1311 : public ::testing::Test {

protected:

    XmpData xmp_data;

};



TEST_F(XmpDataTest_1311, InitialCountIsZero_1311) {

    EXPECT_EQ(xmp_data.count(), 0);

}



TEST_F(XmpDataTest_1311, AddIncreasesCount_1311) {

    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    int result = xmp_data.add(key, value);

    EXPECT_EQ(result, 0); // Assuming add returns 0 on success

    EXPECT_EQ(xmp_data.count(), 1);

}



TEST_F(XmpDataTest_1311, AddSameKeyDoesNotIncreaseCount_1311) {

    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmp_data.add(key, value);

    int result = xmp_data.add(key, value);

    EXPECT_NE(result, 0); // Assuming add returns non-zero on failure

    EXPECT_EQ(xmp_data.count(), 1);

}



TEST_F(XmpDataTest_1311, ClearResetsCount_1311) {

    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmp_data.add(key, value);

    xmp_data.clear();

    EXPECT_EQ(xmp_data.count(), 0);

}



TEST_F(XmpDataTest_1311, UsePacketInitialValueIsFalse_1311) {

    EXPECT_FALSE(xmp_data.usePacket());

}



TEST_F(XmpDataTest_1311, SetAndUsePacketReflectsChange_1311) {

    xmp_data.setPacket("<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"/>");

    EXPECT_TRUE(xmp_data.usePacket());

    EXPECT_EQ(xmp_data.xmpPacket(), "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"/>");

}



TEST_F(XmpDataTest_1311, EmptyInitiallyReturnsTrue_1311) {

    EXPECT_TRUE(xmp_data.empty());

}



TEST_F(XmpDataTest_1311, AddMakesEmptyReturnFalse_1311) {

    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmp_data.add(key, value);

    EXPECT_FALSE(xmp_data.empty());

}



TEST_F(XmpDataTest_1311, EraseReducesCount_1311) {

    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmp_data.add(key, value);

    auto it = xmp_data.begin();

    xmp_data.erase(it);

    EXPECT_EQ(xmp_data.count(), 0);

}



TEST_F(XmpDataTest_1311, FindKeyFindsExistingKey_1311) {

    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmp_data.add(key, value);

    auto it = xmp_data.findKey(key);

    EXPECT_NE(it, xmp_data.end());

}



TEST_F(XmpDataTest_1311, FindKeyReturnsEndForNonExistentKey_1311) {

    XmpKey key("Xmp.dc.title");

    auto it = xmp_data.findKey(key);

    EXPECT_EQ(it, xmp_data.end());

}
