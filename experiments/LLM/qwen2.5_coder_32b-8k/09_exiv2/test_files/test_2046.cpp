#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"

#include "XMPMeta.hpp"



class WXMPMetaTest_2046 : public ::testing::Test {

protected:

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    void SetUp() override {

        xmpRef = new XMPMeta();

    }



    void TearDown() override {

        delete xmpRef;

    }

};



TEST_F(WXMPMetaTest_2046, SerializeToBuffer_NormalOperation_2046) {

    XMP_StringPtr rdfString = nullptr;

    XMP_StringLen rdfSize = 0;



    WXMPMeta_SerializeToBuffer_1(xmpRef, &rdfString, &rdfSize, 0, 0, "", "", 0, &wResult);



    EXPECT_NE(rdfString, nullptr);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPMetaTest_2046, SerializeToBuffer_NullRdfString_2046) {

    XMP_StringLen rdfSize = 0;



    WXMPMeta_SerializeToBuffer_1(xmpRef, nullptr, &rdfSize, 0, 0, "", "", 0, &wResult);



    EXPECT_NE(voidStringPtr, nullptr);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPMetaTest_2046, SerializeToBuffer_NullRdfSize_2046) {

    XMP_StringPtr rdfString = nullptr;



    WXMPMeta_SerializeToBuffer_1(xmpRef, &rdfString, nullptr, 0, 0, "", "", 0, &wResult);



    EXPECT_NE(rdfString, nullptr);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPMetaTest_2046, SerializeToBuffer_DefaultParameters_2046) {

    WXMPMeta_SerializeToBuffer_1(xmpRef, nullptr, nullptr, 0, 0, "", "", 0, &wResult);



    EXPECT_NE(voidStringPtr, nullptr);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPMetaTest_2046, SerializeToBuffer_CustomParameters_2046) {

    XMP_StringPtr rdfString = nullptr;

    XMP_StringLen rdfSize = 0;



    WXMPMeta_SerializeToBuffer_1(xmpRef, &rdfString, &rdfSize, kXMPCore_DebugFlag, 5, "\n", "  ", 2, &wResult);



    EXPECT_NE(rdfString, nullptr);

    EXPECT_EQ(wResult.errMessage, nullptr);

}
