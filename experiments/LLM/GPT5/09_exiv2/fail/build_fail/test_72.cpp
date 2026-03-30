#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "webpimage.h"  // Include the necessary header for Exiv2::Image, Exiv2::WebPImage, and BasicIo classes.

namespace Exiv2 {

    // Mock class for BasicIo to simulate different behaviors.
    class MockBasicIo : public BasicIo {
    public:
        MOCK_METHOD(bool, isGood, (), (const override));  // Mock the isGood() method.
    };

    // Unit test for newWebPInstance
    TEST_F(WebPImageTest_72, TestNormalOperation_72) {
        // Create a mock io object.
        auto mockIo = std::make_unique<MockBasicIo>();

        // Simulate a good IO object by making isGood return true.
        EXPECT_CALL(*mockIo, isGood()).WillOnce(testing::Return(true));

        // Call the function and verify the result.
        auto result = newWebPInstance(std::move(mockIo), true);
        
        // Check that the image is valid and not null.
        EXPECT_NE(result, nullptr);
        EXPECT_TRUE(result->good());
    }

    // Test case where the image is not good (bad IO).
    TEST_F(WebPImageTest_72, TestBadIo_72) {
        // Create a mock io object.
        auto mockIo = std::make_unique<MockBasicIo>();

        // Simulate a bad IO object by making isGood return false.
        EXPECT_CALL(*mockIo, isGood()).WillOnce(testing::Return(false));

        // Call the function and verify the result.
        auto result = newWebPInstance(std::move(mockIo), true);

        // Expect the result to be nullptr since the image creation failed.
        EXPECT_EQ(result, nullptr);
    }

    // Boundary test case: testing with empty io object (nullptr).
    TEST_F(WebPImageTest_72, TestEmptyIo_72) {
        // Pass nullptr as the io object.
        auto result = newWebPInstance(nullptr, true);

        // Expect the result to be nullptr as the io is empty.
        EXPECT_EQ(result, nullptr);
    }

    // Exceptional case: verifying behavior when the image creation fails.
    TEST_F(WebPImageTest_72, TestImageCreationFailure_72) {
        // Create a mock io object.
        auto mockIo = std::make_unique<MockBasicIo>();

        // Simulate an IO failure by having isGood return false.
        EXPECT_CALL(*mockIo, isGood()).WillOnce(testing::Return(false));

        // Call the function with a failure case.
        auto result = newWebPInstance(std::move(mockIo), true);

        // Expect the image creation to fail, returning nullptr.
        EXPECT_EQ(result, nullptr);
    }

}  // namespace Exiv2