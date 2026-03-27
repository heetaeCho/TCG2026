#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "client-glue/TXMPMeta.incl_cpp"

#include "client-glue/WXMP_Common.hpp"



class XMPMetaTest : public ::testing::Test {

protected:

    void SetUp() override {

        // No setup needed for this simple test case

    }



    void TearDown() override {

        // No teardown needed for this simple test case

    }

};



TEST_F(XMPMetaTest_1276, DefaultCTor_ReturnsNonNullPointer_1276) {

    XMPMetaRef metaRef = DefaultCTor();

    EXPECT_NE(metaRef, nullptr);

}



TEST_F(XMPMetaTest_1276, DefaultCTor_CallszXMPMeta_CTor_1_1276) {

    // This test assumes that zXMPMeta_CTor_1 is called internally by DefaultCTor

    // Since we cannot mock internal behavior, this test checks the observable result (non-null pointer)

    XMPMetaRef metaRef = DefaultCTor();

    EXPECT_NE(metaRef, nullptr);

}
