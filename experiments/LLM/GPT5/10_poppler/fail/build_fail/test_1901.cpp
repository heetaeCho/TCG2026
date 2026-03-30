#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GlobalParams.h"
#include "GooString.h"
#include "GfxFont.h"

// Mocking external dependencies for testing
class MockGfxFont : public GfxFont {
public:
    MOCK_CONST_METHOD0(isFixedWidth, bool());
    MOCK_CONST_METHOD0(isBold, bool());
    MOCK_CONST_METHOD0(isItalic, bool());
    MOCK_CONST_METHOD0(getFamily, const GooString*());
    MOCK_CONST_METHOD0(getWeight, int());
    MOCK_CONST_METHOD0(getStretch, int());
    MOCK_CONST_METHOD0(getNameWithoutSubsetTag, std::string());
};

class GlobalParamsTest_1901 : public ::testing::Test {
protected:
    // Helper function to create a GfxFont mock
    std::shared_ptr<MockGfxFont> createMockFont() {
        return std::make_shared<MockGfxFont>();
    }
};

TEST_F(GlobalParamsTest_1901, BuildFcPattern_NormalOperation_1901) {
    // Set up a mock GfxFont object and its expectations
    auto mockFont = createMockFont();
    EXPECT_CALL(*mockFont, isFixedWidth()).WillOnce(testing::Return(false));
    EXPECT_CALL(*mockFont, isBold()).WillOnce(testing::Return(true));
    EXPECT_CALL(*mockFont, isItalic()).WillOnce(testing::Return(false));
    EXPECT_CALL(*mockFont, getFamily()).WillOnce(testing::Return(nullptr));
    EXPECT_CALL(*mockFont, getWeight()).WillOnce(testing::Return(GfxFont::W700));
    EXPECT_CALL(*mockFont, getStretch()).WillOnce(testing::Return(GfxFont::Normal));
    EXPECT_CALL(*mockFont, getNameWithoutSubsetTag()).WillOnce(testing::Return("Arial-Bold"));

    GooString base14Name("Arial");

    // Call the function under test
    FcPattern *pattern = buildFcPattern(*mockFont, &base14Name);

    ASSERT_NE(pattern, nullptr);  // Ensure the pattern is built successfully

    // Additional assertions can be added to verify specific pattern attributes if needed
}

TEST_F(GlobalParamsTest_1901, BuildFcPattern_BoundaryConditions_1901) {
    // Test with null base14Name
    auto mockFont = createMockFont();
    EXPECT_CALL(*mockFont, getNameWithoutSubsetTag()).WillOnce(testing::Return("Arial-Regular"));

    GooString *base14Name = nullptr;  // Null pointer edge case

    FcPattern *pattern = buildFcPattern(*mockFont, base14Name);
    ASSERT_NE(pattern, nullptr);  // Ensure the pattern is built

    // Additional assertions for null input handling
}

TEST_F(GlobalParamsTest_1901, BuildFcPattern_ErrorHandling_1901) {
    // Set up a mock GfxFont object that produces an invalid result
    auto mockFont = createMockFont();
    EXPECT_CALL(*mockFont, getNameWithoutSubsetTag()).WillOnce(testing::Return("InvalidFontName"));

    GooString base14Name("InvalidName");

    // Call with mock that simulates error scenario (e.g., unsupported font)
    FcPattern *pattern = buildFcPattern(*mockFont, &base14Name);
    ASSERT_EQ(pattern, nullptr);  // Expecting null pattern on error
}

TEST_F(GlobalParamsTest_1901, BuildFcPattern_VerifyExternalInteractions_1901) {
    // Mock external interactions like method calls on GooString
    GooString base14Name("Arial");
    auto mockFont = createMockFont();

    // Verify that the method getFamily is called during buildFcPattern
    EXPECT_CALL(*mockFont, getFamily()).WillOnce(testing::Return(&base14Name));

    FcPattern *pattern = buildFcPattern(*mockFont, &base14Name);
    ASSERT_NE(pattern, nullptr);  // Ensure that pattern is created

    // You can further add verifications for the specific interactions if needed
}