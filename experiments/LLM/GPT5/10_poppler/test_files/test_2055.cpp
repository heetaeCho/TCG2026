#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Forward declaration of the classes based on the provided snippet
class Annot;
class PopplerAnnot;

// Mock dependencies if necessary
class MockAnnot : public Annot {
public:
    MOCK_METHOD(void, someFunction, (), (const));
};

// PopplerAnnot and _poppler_create_annot functions are assumed to be part of the codebase
PopplerAnnot* _poppler_create_annot(int annotType, const std::shared_ptr<Annot>& annot);

// The function to test
PopplerAnnot* _poppler_annot_circle_new(const std::shared_ptr<Annot>& annot) {
    return _poppler_create_annot(POPPLER_TYPE_ANNOT_CIRCLE, annot);
}

// Test suite for _poppler_annot_circle_new function
TEST_F(PopplerAnnotTest_2055, NormalOperation_2055) {
    // Arrange: Create a mock Annot
    std::shared_ptr<Annot> mockAnnot = std::make_shared<MockAnnot>();

    // Act: Call the function with the mock
    PopplerAnnot* result = _poppler_annot_circle_new(mockAnnot);

    // Assert: Check that the result is not nullptr, verifying the creation of a PopplerAnnot
    EXPECT_NE(result, nullptr);
}

TEST_F(PopplerAnnotTest_2055, NullAnnotPointer_2055) {
    // Act: Call the function with a null Annot pointer
    PopplerAnnot* result = _poppler_annot_circle_new(nullptr);

    // Assert: Check that the result is nullptr as it should not be created with a null annot
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerAnnotTest_2055, MockFunctionCall_2055) {
    // Arrange: Create a mock Annot
    MockAnnot mockAnnot;

    // Expect a function call on the mock Annot (if necessary for the test)
    EXPECT_CALL(mockAnnot, someFunction()).Times(1);

    // Act: Call the function with the mock
    _poppler_annot_circle_new(std::make_shared<MockAnnot>());

    // Assert: Verify that the expected function call occurred
    testing::Mock::VerifyAndClearExpectations(&mockAnnot);
}