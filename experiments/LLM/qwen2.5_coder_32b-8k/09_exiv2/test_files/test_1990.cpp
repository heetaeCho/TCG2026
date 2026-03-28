#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"



class WXMPMetaTest_1990 : public ::testing::Test {

protected:

    WXMP_Result result;



    void SetUp() override {

        WXMPMeta_CTor_1(&result);

    }



    void TearDown() override {

        // Assuming there is a way to delete the XMPMeta object, which is not provided in the interface

        // For this test, we will assume that the object needs to be manually deleted

        if (result.ptrResult != nullptr) {

            XMPMeta* xmpObj = static_cast<XMPMeta*>(result.ptrResult);

            delete xmpObj;

        }

    }

};



TEST_F(WXMPMetaTest_1990, ConstructorSuccess_1990) {

    EXPECT_NE(result.ptrResult, nullptr);

    XMPMeta* xmpObj = static_cast<XMPMeta*>(result.ptrResult);

    EXPECT_EQ(xmpObj->clientRefs, 1);

}



TEST_F(WXMPMetaTest_1990, ClientRefsInitialization_1990) {

    XMPMeta* xmpObj = static_cast<XMPMeta*>(result.ptrResult);

    EXPECT_EQ(xmpObj->clientRefs, 1);

}



// Assuming there is no error message set on success

TEST_F(WXMPMetaTest_1990, NoErrorMessageOnSuccess_1990) {

    EXPECT_EQ(result.errMessage, nullptr);

}
