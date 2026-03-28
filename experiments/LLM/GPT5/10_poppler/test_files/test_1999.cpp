#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/JPEG2000Stream.cc"

// Mock class for external dependencies (if needed)
class MockJPXData : public JPXData {
public:
    MOCK_METHOD(void, someExternalMethod, ());
};

class JPEG2000StreamTest_1999 : public ::testing::Test {
protected:
    JPXData jpxData;
};

TEST_F(JPEG2000StreamTest_1999, jpxSkipCallbackNormalOperation_1999) {
    // Setup
    const OPJ_OFF_T skip = 50;
    jpxData.pos = 0;
    jpxData.size = 100;

    // Call the callback function
    OPJ_OFF_T result = jpxSkip_callback(skip, &jpxData);

    // Check the observable behavior: pos should be increased by 'skip'
    EXPECT_EQ(jpxData.pos, 50);
    EXPECT_EQ(result, 50);  // Expected value from the callback should match the input
}

TEST_F(JPEG2000StreamTest_1999, jpxSkipCallbackBoundaryCondition_1999) {
    // Setup for boundary condition: Skip larger than remaining data
    const OPJ_OFF_T skip = 150;
    jpxData.pos = 0;
    jpxData.size = 100;

    // Call the callback function
    OPJ_OFF_T result = jpxSkip_callback(skip, &jpxData);

    // Check the observable behavior: pos should move to the size of the data (i.e., 100)
    EXPECT_EQ(jpxData.pos, 100);
    EXPECT_EQ(result, 100);  // Callback returns the same value as input
}

TEST_F(JPEG2000StreamTest_1999, jpxSkipCallbackExceedsSize_1999) {
    // Setup for boundary condition: Skip causing overrun
    const OPJ_OFF_T skip = 200;
    jpxData.pos = 0;
    jpxData.size = 150;

    // Call the callback function
    OPJ_OFF_T result = jpxSkip_callback(skip, &jpxData);

    // Check observable behavior: pos should only move up to the size limit
    EXPECT_EQ(jpxData.pos, 150);
    EXPECT_EQ(result, 150);  // The returned value should reflect the actual movement
}

TEST_F(JPEG2000StreamTest_1999, jpxSkipCallbackNegativeSkip_1999) {
    // Setup for exceptional case: Negative skip
    const OPJ_OFF_T skip = -50;
    jpxData.pos = 100;
    jpxData.size = 200;

    // Call the callback function
    OPJ_OFF_T result = jpxSkip_callback(skip, &jpxData);

    // Check the observable behavior: pos should not move backward, stays at 100
    EXPECT_EQ(jpxData.pos, 100);
    EXPECT_EQ(result, -50);  // The callback returns the same negative skip value
}

TEST_F(JPEG2000StreamTest_1999, jpxSkipCallbackFullSkip_1999) {
    // Setup for boundary case: Full skip within bounds
    const OPJ_OFF_T skip = 100;
    jpxData.pos = 0;
    jpxData.size = 100;

    // Call the callback function
    OPJ_OFF_T result = jpxSkip_callback(skip, &jpxData);

    // Verify the position after skip and the callback return value
    EXPECT_EQ(jpxData.pos, 100);
    EXPECT_EQ(result, 100);  // Skip moves the position to the end of the data
}