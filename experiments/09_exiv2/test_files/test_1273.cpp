#include <gtest/gtest.h>

#include "XMP_Const.h"



class XMP_ErrorTest_1273 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(XMP_ErrorTest_1273, GetID_ReturnsCorrectID_1273) {

    XMP_Error error(404, "Not Found");

    EXPECT_EQ(error.GetID(), 404);

}



TEST_F(XMP_ErrorTest_1273, GetID_ZeroID_1273) {

    XMP_Error error(0, "Success");

    EXPECT_EQ(error.GetID(), 0);

}



TEST_F(XMP_ErrorTest_1273, GetID_NegativeID_1273) {

    XMP_Error error(-1, "Error");

    EXPECT_EQ(error.GetID(), -1);

}



// Assuming GetErrMsg is part of the interface as per known dependencies

TEST_F(XMP_ErrorTest_1273, GetErrMsg_ReturnsCorrectMessage_1273) {

    XMP_Error error(404, "Not Found");

    EXPECT_STREQ(error.GetErrMsg(), "Not Found");

}



TEST_F(XMP_ErrorTest_1273, GetErrMsg_EmptyMessage_1273) {

    XMP_Error error(200, "");

    EXPECT_STREQ(error.GetErrMsg(), "");

}
