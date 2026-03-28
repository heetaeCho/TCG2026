#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/WXMPUtils.cpp"



class WXMPUtils_RemoveProperties_Test_1956 : public ::testing::Test {

protected:

    XMPMeta* xmpObj;

    WXMP_Result wResult;



    void SetUp() override {

        xmpObj = new XMPMeta();

    }



    void TearDown() override {

        delete xmpObj;

    }

};



TEST_F(WXMPUtils_RemoveProperties_Test_1956, NullWXMPObject_1956) {

    WXMPUtils_RemoveProperties_1(nullptr, "schemaNS", "propName", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Output XMP pointer is null");

}



TEST_F(WXMPUtils_RemoveProperties_Test_1956, NullSchemaNS_1956) {

    WXMPUtils_RemoveProperties_1(xmpObj, nullptr, "propName", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // No error expected as schemaNS is set to ""

}



TEST_F(WXMPUtils_RemoveProperties_Test_1956, NullPropertyName_1956) {

    WXMPUtils_RemoveProperties_1(xmpObj, "schemaNS", nullptr, 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // No error expected as propName is set to ""

}



TEST_F(WXMPUtils_RemoveProperties_Test_1956, NormalOperation_1956) {

    WXMPUtils_RemoveProperties_1(xmpObj, "schemaNS", "propName", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // No error expected for normal operation

}
