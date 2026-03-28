#include <gtest/gtest.h>

#include "XMP_Const.h"



class XMP_ErrorTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(XMP_ErrorTest_1274, ConstructorSetsErrorMessage_1274) {

    XMP_StringPtr expectedErrMsg = "Test Error Message";

    XMP_Error error(1, expectedErrMsg);

    EXPECT_STREQ(expectedErrMsg, error.GetErrMsg());

}



TEST_F(XMP_ErrorTest_1274, GetErrMsgReturnsCorrectMessage_1274) {

    XMP_StringPtr expectedErrMsg = "Another Test Message";

    XMP_Error error(2, expectedErrMsg);

    EXPECT_STREQ(expectedErrMsg, error.GetErrMsg());

}

```


