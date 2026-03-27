#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/PSOutputDev.h"

using ::testing::Test;
using ::testing::Mock;

class PSOutputDevTest_1308 : public Test {
protected:
    PSOutputDev psOutputDev{"TestFile.ps", nullptr, "TestTitle", 1, PSOutMode::Mode1, 800, 600, false, false, 0, 0, 0, 0, PSForceRasterize::None, false, nullptr, nullptr, PSLevel::Level1};

    // This will allow mocking external callbacks if necessary
    void SetUp() override {
        // You can set up mock behaviors or other pre-test setup code here
    }
};

TEST_F(PSOutputDevTest_1308, SetPSExpandSmaller_True_1308) {
    psOutputDev.setPSExpandSmaller(true);
    // You would need to verify if the internal behavior is as expected
    // Since `psExpandSmaller` is private, you can only verify it indirectly
    // via observable effects or interactions, which will depend on actual
    // implementation details visible through other functions
}

TEST_F(PSOutputDevTest_1308, SetPSExpandSmaller_False_1308) {
    psOutputDev.setPSExpandSmaller(false);
    // Verify expected behavior
}

TEST_F(PSOutputDevTest_1308, SetPSExpandSmaller_UsingDefaultConstructor_1308) {
    PSOutputDev psOutputDevDefault;
    psOutputDevDefault.setPSExpandSmaller(true);
    // Verify expected behavior with default constructor
}

TEST_F(PSOutputDevTest_1308, SetPSExpandSmaller_ThenCallMethodThatUsesExpand_1308) {
    psOutputDev.setPSExpandSmaller(true);
    // Add a call that triggers PSExpandSmaller to affect output
    // Verify the result
}

TEST_F(PSOutputDevTest_1308, SetPSExpandSmaller_ExceptionHandling_1308) {
    try {
        psOutputDev.setPSExpandSmaller(true);
        // Add additional code that may throw exceptions
        FAIL() << "Expected exception not thrown";
    } catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "Expected exception message");
    }
}

TEST_F(PSOutputDevTest_1308, SetPSExpandSmaller_MultipleCalls_1308) {
    psOutputDev.setPSExpandSmaller(true);
    psOutputDev.setPSExpandSmaller(false);
    // Verify the state change works as expected
}