#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers and definitions are included as per the given partial code



class MockTextOutputProc {

public:

    MOCK_METHOD2(mockOutProc, void(const char*, void*));

};



extern "C" void mockOutProcWrapper(const char* msg, void* refCon) {

    static_cast<MockTextOutputProc*>(refCon)->mockOutProc(msg, refCon);

}



class WXMPMetaTest : public ::testing::Test {

protected:

    MockTextOutputProc mockTextOutputProc;

    WXMP_Result wResult;



    void SetUp() override {

        memset(&wResult, 0, sizeof(WXMP_Result));

    }

};



TEST_F(WXMPMetaTest_1996, ValidOutProc_1996) {

    WXMPMeta_DumpAliases_1(mockOutProcWrapper, &mockTextOutputProc, &wResult);

    EXPECT_EQ(wResult.int32Result, 0); // Assuming success is indicated by status code 0

}



TEST_F(WXMPMetaTest_1996, NullOutProcThrowsBadParam_1996) {

    try {

        WXMPMeta_DumpAliases_1(nullptr, &mockTextOutputProc, &wResult);

        FAIL() << "Expected exception not thrown";

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);

        EXPECT_STREQ(e.GetErrMsg(), "Null client output routine");

    }

}



TEST_F(WXMPMetaTest_1996, VerifyOutProcCall_1996) {

    EXPECT_CALL(mockTextOutputProc, mockOutProc(::testing::_, &mockTextOutputProc)).Times(1);

    WXMPMeta_DumpAliases_1(mockOutProcWrapper, &mockTextOutputProc, &wResult);

}
