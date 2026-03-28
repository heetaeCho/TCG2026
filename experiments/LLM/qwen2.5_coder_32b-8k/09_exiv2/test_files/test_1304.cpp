#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest : public ::testing::Test {

protected:

    XmpData xmpData;

    Xmpdatum xmpDatum;

};



TEST_F(XmpDataTest_1304, AddXmpdatumReturnsZero_1304) {

    EXPECT_EQ(xmpData.add(xmpDatum), 0);

}



TEST_F(XmpDataTest_1304, CountIncreasesAfterAdd_1304) {

    long initialCount = xmpData.count();

    xmpData.add(xmpDatum);

    EXPECT_EQ(xmpData.count(), initialCount + 1);

}



TEST_F(XmpDataTest_1304, EmptyReturnsFalseAfterAdd_1304) {

    xmpData.add(xmpDatum);

    EXPECT_FALSE(xmpData.empty());

}



TEST_F(XmpDataTest_1304, ClearResetsCount_1304) {

    xmpData.add(xmpDatum);

    xmpData.clear();

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1304, EmptyReturnsTrueAfterClear_1304) {

    xmpData.add(xmpDatum);

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1304, EraseDecreasesCount_1304) {

    xmpData.add(xmpDatum);

    auto it = xmpData.begin();

    xmpData.erase(it);

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_1304, FindKeyReturnsValidIteratorWhenPresent_1304) {

    XmpKey key("some_key");

    Value value;

    xmpData.add(key, &value);



    auto it = xmpData.findKey(key);

    EXPECT_NE(it, xmpData.end());

}



TEST_F(XmpDataTest_1304, FindKeyReturnsEndWhenNotPresent_1304) {

    XmpKey key("nonexistent_key");

    auto it = xmpData.findKey(key);

    EXPECT_EQ(it, xmpData.end());

}
