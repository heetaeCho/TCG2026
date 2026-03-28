#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-annotation.h"  // Include the relevant header

namespace Poppler {

class MockTextAnnotationPrivate : public TextAnnotationPrivate {
public:
    MOCK_METHOD(void, setDefaultAppearanceToNative, (), (override));
    MOCK_METHOD(std::unique_ptr<DefaultAppearance>, getDefaultAppearanceFromNative, (), (const, override));
};

// TEST for setDefaultAppearanceToNative
TEST_F(MockTextAnnotationPrivate_1397, SetDefaultAppearanceToNative_1397) {
    MockTextAnnotationPrivate mockTextAnnotationPrivate;

    // Set expectations for the method call
    EXPECT_CALL(mockTextAnnotationPrivate, setDefaultAppearanceToNative())
        .Times(1);

    // Act: Call the function
    mockTextAnnotationPrivate.setDefaultAppearanceToNative();
}

// TEST for getDefaultAppearanceFromNative
TEST_F(MockTextAnnotationPrivate_1397, GetDefaultAppearanceFromNative_1397) {
    MockTextAnnotationPrivate mockTextAnnotationPrivate;

    // Create a mock DefaultAppearance object
    auto mockDefaultAppearance = std::make_unique<DefaultAppearance>("Arial", 12.0, 0x000000);

    // Set expectations for the method call and return value
    EXPECT_CALL(mockTextAnnotationPrivate, getDefaultAppearanceFromNative())
        .Times(1)
        .WillOnce(testing::Return(std::move(mockDefaultAppearance)));

    // Act: Call the function
    auto result = mockTextAnnotationPrivate.getDefaultAppearanceFromNative();

    // Assert: Check if the returned object is the mock one
    ASSERT_EQ(result->getFontName(), "Arial");
    ASSERT_EQ(result->getFontPtSize(), 12.0);
    ASSERT_EQ(result->getFontColor()->getColor(), 0x000000);
}

}  // namespace Poppler