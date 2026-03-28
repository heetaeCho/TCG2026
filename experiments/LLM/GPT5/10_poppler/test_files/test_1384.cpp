#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annotation.h" // Assuming this header includes fillNormalizationMTX and necessary classes

using namespace testing;
using namespace Poppler;

// Mock classes for external dependencies
class MockPage : public Page {
public:
    MOCK_METHOD(const PDFRectangle*, getCropBox, (), (const, override));
    MOCK_METHOD(double, getCropWidth, (), (const, override));
    MOCK_METHOD(double, getCropHeight, (), (const, override));
};

class GfxStateMock : public GfxState {
public:
    GfxStateMock() : GfxState(72.0, 72.0, nullptr, 0, true) {}
    MOCK_METHOD(const std::array<double, 6>&, getCTM, (), (const, override));
};

// Test fixture for testing fillNormalizationMTX
class FillNormalizationMTXTest : public ::testing::Test {
protected:
    double MTX[6];  // Matrix to be filled in by the function
    MockPage* mockPage;
    GfxStateMock* gfxStateMock;

    void SetUp() override {
        mockPage = new MockPage();
        gfxStateMock = new GfxStateMock();
    }

    void TearDown() override {
        delete mockPage;
        delete gfxStateMock;
    }
};

// Test case for normal operation
TEST_F(FillNormalizationMTXTest, NormalOperation_1384) {
    // Set up expectations
    EXPECT_CALL(*mockPage, getCropWidth()).WillOnce(Return(100.0));
    EXPECT_CALL(*mockPage, getCropHeight()).WillOnce(Return(200.0));

    std::array<double, 6> expectedCTM = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_CALL(*gfxStateMock, getCTM()).WillOnce(ReturnRef(expectedCTM));

    // Call the function
    fillNormalizationMTX(mockPage, MTX, 90);

    // Assert the matrix values
    ASSERT_DOUBLE_EQ(MTX[0], expectedCTM[0] / 100.0);
    ASSERT_DOUBLE_EQ(MTX[1], expectedCTM[1] / 200.0);
    ASSERT_DOUBLE_EQ(MTX[2], expectedCTM[2] / 100.0);
    ASSERT_DOUBLE_EQ(MTX[3], expectedCTM[3] / 200.0);
    ASSERT_DOUBLE_EQ(MTX[4], expectedCTM[4] / 100.0);
    ASSERT_DOUBLE_EQ(MTX[5], expectedCTM[5] / 200.0);
}

// Test case for boundary condition with different page rotation
TEST_F(FillNormalizationMTXTest, BoundaryRotation_1384) {
    // Set up expectations
    EXPECT_CALL(*mockPage, getCropWidth()).WillOnce(Return(150.0));
    EXPECT_CALL(*mockPage, getCropHeight()).WillOnce(Return(250.0));

    std::array<double, 6> expectedCTM = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_CALL(*gfxStateMock, getCTM()).WillOnce(ReturnRef(expectedCTM));

    // Call the function with rotation angle 270
    fillNormalizationMTX(mockPage, MTX, 270);

    // Assert the matrix values for rotation 270
    ASSERT_DOUBLE_EQ(MTX[0], expectedCTM[0] / 250.0);
    ASSERT_DOUBLE_EQ(MTX[1], expectedCTM[1] / 150.0);
    ASSERT_DOUBLE_EQ(MTX[2], expectedCTM[2] / 250.0);
    ASSERT_DOUBLE_EQ(MTX[3], expectedCTM[3] / 150.0);
    ASSERT_DOUBLE_EQ(MTX[4], expectedCTM[4] / 250.0);
    ASSERT_DOUBLE_EQ(MTX[5], expectedCTM[5] / 150.0);
}

// Test case for exceptional condition where the page is null
TEST_F(FillNormalizationMTXTest, NullPage_1384) {
    // Call the function with a null page, expect no crash
    ASSERT_NO_THROW(fillNormalizationMTX(nullptr, MTX, 90));
}