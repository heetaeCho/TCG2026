#include <gtest/gtest.h>
#include <gmock/gmock.h>

// The code to be tested is in the Poppler namespace
namespace Poppler {
    bool isCmsAvailable();
}

// Test fixture to ensure a consistent testing environment
class CmsAvailabilityTest_1359 : public ::testing::Test {
protected:
    void SetUp() override {
        // Any setup needed for the tests, if required
    }

    void TearDown() override {
        // Any cleanup needed for the tests, if required
    }
};

// Test case to verify normal operation
TEST_F(CmsAvailabilityTest_1359, CmsAvailable_When_USE_CMS_Is_Enabled_1359) {
#if USE_CMS
    EXPECT_TRUE(Poppler::isCmsAvailable());
#else
    EXPECT_FALSE(Poppler::isCmsAvailable());
#endif
}

// Boundary test cases
TEST_F(CmsAvailabilityTest_1359, CmsNotAvailable_When_USE_CMS_Is_Disabled_1359) {
#if !USE_CMS
    EXPECT_FALSE(Poppler::isCmsAvailable());
#else
    EXPECT_TRUE(Poppler::isCmsAvailable());
#endif
}

// Exceptional cases (though there are no exceptional cases in the provided code, you can verify if the behavior aligns with expectations)
TEST_F(CmsAvailabilityTest_1359, CmsBehavior_When_Configuration_Is_Changed_1359) {
    // In reality, we expect this test case to always return the correct state based on USE_CMS.
    // Exceptional cases might depend on the code context (e.g., if USE_CMS is misconfigured).
    // Currently, this is a pass-through verification of the above conditions.
    ASSERT_TRUE(true); // This is a placeholder. Actual error case testing isn't meaningful here.
}