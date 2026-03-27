#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "XMP_Const.h"



class WXMPUtilsTest_1953 : public ::testing::Test {

protected:

    XMPMetaRef wfullXMP;

    XMPMetaRef wextendedXMP;

    WXMP_Result wResult;



    void SetUp() override {

        // Initialize the XMPMetaRef objects

        wfullXMP = new XMPMeta();

        wextendedXMP = new XMPMeta();

        memset(&wResult, 0, sizeof(WXMP_Result));

    }



    void TearDown() override {

        // Clean up the XMPMetaRef objects

        delete wfullXMP;

        delete wextendedXMP;

    }

};



TEST_F(WXMPUtilsTest_1953, MergeFromJPEG_Success_1953) {

    WXMPUtils_MergeFromJPEG_1(wfullXMP, wextendedXMP, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPUtilsTest_1953, MergeFromJPEG_NullFullXMPOutput_1953) {

    WXMPUtils_MergeFromJPEG_1(nullptr, wextendedXMP, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Output XMP pointer is null");

}



TEST_F(WXMPUtilsTest_1953, MergeFromJPEG_NullExtendedXMPInput_1953) {

    WXMPUtils_MergeFromJPEG_1(wfullXMP, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr); // Assuming the function does not throw for null extendedXMP

}
