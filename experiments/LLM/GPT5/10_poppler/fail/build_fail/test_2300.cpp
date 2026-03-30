#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-action.h"
#include "Link.h"
#include "poppler-action.cc"  // Include the file where the function is defined

// Mock class for LinkRendition
class MockLinkRendition : public LinkRendition {
public:
    MOCK_METHOD(RenditionOperation, getOperation, (), (const, override));
    MOCK_METHOD(const MediaRendition*, getMedia, (), (const, override));
};

// Test fixture class
class PopplerActionTest_2300 : public ::testing::Test {
protected:
    PopplerAction action;
    MockLinkRendition mockLinkRendition;

    void SetUp() override {
        // Setup necessary mock behavior here, if any.
    }
};

// Test case for normal operation
TEST_F(PopplerActionTest_2300, BuildRendition_NormalOperation_2300) {
    // Arrange
    RenditionOperation expectedOp = RenditionOperation::SomeOperation;  // Change to appropriate operation
    MediaRendition* mockMedia = nullptr;

    // Set expectations for the mock object
    EXPECT_CALL(mockLinkRendition, getOperation())
        .WillOnce(testing::Return(expectedOp));
    EXPECT_CALL(mockLinkRendition, getMedia())
        .WillOnce(testing::Return(mockMedia));

    // Act
    build_rendition(&action, &mockLinkRendition);

    // Assert
    EXPECT_EQ(action.rendition.op, expectedOp);
    EXPECT_EQ(action.rendition.media, nullptr);  // Assert the media field is set correctly
}

// Test case for boundary condition (media is non-null)
TEST_F(PopplerActionTest_2300, BuildRendition_WithMedia_2301) {
    // Arrange
    RenditionOperation expectedOp = RenditionOperation::SomeOperation;  // Change to appropriate operation
    MediaRendition* mockMedia = new MediaRendition();  // Assuming MediaRendition can be instantiated

    // Set expectations for the mock object
    EXPECT_CALL(mockLinkRendition, getOperation())
        .WillOnce(testing::Return(expectedOp));
    EXPECT_CALL(mockLinkRendition, getMedia())
        .WillOnce(testing::Return(mockMedia));

    // Act
    build_rendition(&action, &mockLinkRendition);

    // Assert
    EXPECT_EQ(action.rendition.op, expectedOp);
    EXPECT_EQ(action.rendition.media, mockMedia);  // Assert the media field is set correctly
}

// Test case for boundary condition (media is null)
TEST_F(PopplerActionTest_2300, BuildRendition_NoMedia_2302) {
    // Arrange
    RenditionOperation expectedOp = RenditionOperation::SomeOperation;
    MediaRendition* mockMedia = nullptr;

    // Set expectations for the mock object
    EXPECT_CALL(mockLinkRendition, getOperation())
        .WillOnce(testing::Return(expectedOp));
    EXPECT_CALL(mockLinkRendition, getMedia())
        .WillOnce(testing::Return(mockMedia));

    // Act
    build_rendition(&action, &mockLinkRendition);

    // Assert
    EXPECT_EQ(action.rendition.op, expectedOp);
    EXPECT_EQ(action.rendition.media, nullptr);  // Assert the media field is set correctly
}

// Test case for exceptional case (if getOperation fails)
TEST_F(PopplerActionTest_2300, BuildRendition_OperationFailure_2303) {
    // Arrange
    EXPECT_CALL(mockLinkRendition, getOperation())
        .WillOnce(testing::Throw(std::runtime_error("Operation failed")));
    
    // Act & Assert
    EXPECT_THROW(build_rendition(&action, &mockLinkRendition), std::runtime_error);
}