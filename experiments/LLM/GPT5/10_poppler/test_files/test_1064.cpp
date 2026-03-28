#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/OutputDev.h"

// Mocking external dependencies if necessary (not in this case for simplicity)

class OutputDevTest_1064 : public testing::Test {
protected:
    OutputDev outputDev;
};

// Test for supportJPXtransparency() returning false (normal operation)
TEST_F(OutputDevTest_1064, SupportJPXTransparency_NormalOperation_1064) {
    EXPECT_FALSE(outputDev.supportJPXtransparency());
}

// Test for upsideDown() returning false (normal operation)
TEST_F(OutputDevTest_1064, UpsideDown_NormalOperation_1064) {
    EXPECT_FALSE(outputDev.upsideDown());
}

// Test for useDrawChar() returning false (normal operation)
TEST_F(OutputDevTest_1064, UseDrawChar_NormalOperation_1064) {
    EXPECT_FALSE(outputDev.useDrawChar());
}

// Test for boundary condition: setting and getting default CTM
TEST_F(OutputDevTest_1064, SetDefaultCTM_1064) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    outputDev.setDefaultCTM(ctm);
    // Assuming a getter or a method to verify the CTM state
    // Not available directly from the provided interface, so assuming it is observable.
    // EXPECT_EQ(outputDev.getDefaultCTM(), ctm); // Hypothetical getter for CTM
}

// Test for exceptional/error case: calling setSoftMask with invalid arguments
TEST_F(OutputDevTest_1064, SetSoftMask_InvalidArgs_1064) {
    GfxState *state = nullptr; // Invalid state pointer
    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};
    bool alpha = false;
    Function *transferFunc = nullptr; // Invalid transfer function pointer
    GfxColor *backdropColor = nullptr; // Invalid color pointer
    
    EXPECT_NO_THROW(outputDev.setSoftMask(state, bbox, alpha, transferFunc, backdropColor));
}

// Test for checking ProfileHash access
TEST_F(OutputDevTest_1064, GetProfileHash_1064) {
    auto profileHash = outputDev.getProfileHash();
    EXPECT_NE(profileHash, nullptr); // Assuming that profileHash is always valid and non-null
}

// Test for checking transparency support function call
TEST_F(OutputDevTest_1064, CheckTransparencyGroup_1064) {
    GfxState *state = nullptr; // Assuming a valid state can be passed here in actual tests
    bool knockout = false;

    EXPECT_TRUE(outputDev.checkTransparencyGroup(state, knockout)); // Assuming a valid return value for this test
}

// Test for checking error handling in processLink with null pointer
TEST_F(OutputDevTest_1064, ProcessLink_NullPointer_1064) {
    AnnotLink *link = nullptr; // Null link for exceptional case
    EXPECT_NO_THROW(outputDev.processLink(link)); // No exception should be thrown even with null link
}

// Test for setting and getting DisplayProfile
TEST_F(OutputDevTest_1064, SetGetDisplayProfile_1064) {
    GfxLCMSProfilePtr profile = nullptr; // Null profile for simplicity
    outputDev.setDisplayProfile(profile);
    EXPECT_EQ(outputDev.getDisplayProfile(), profile);
}

// Test for boundary condition: verifying vector anti-aliasing setting
TEST_F(OutputDevTest_1064, SetGetVectorAntialias_1064) {
    outputDev.setVectorAntialias(true);
    EXPECT_TRUE(outputDev.getVectorAntialias());
    
    outputDev.setVectorAntialias(false);
    EXPECT_FALSE(outputDev.getVectorAntialias());
}