#include <gtest/gtest.h>
#include <memory>

// Mock classes to fulfill the external dependencies
class Annot {};

// The function we're testing
PopplerAnnot* _poppler_annot_line_new(const std::shared_ptr<Annot> &annot) {
    return _poppler_create_annot(POPPLER_TYPE_ANNOT_LINE, annot);
}

// Mocks for external collaborators if needed
class PopplerAnnotMock : public PopplerAnnot {
public:
    MOCK_METHOD(PopplerAnnot*, _poppler_create_annot, (int, const std::shared_ptr<Annot>&), ());
};

// Test class
class PopplerAnnotLineTest_2053 : public ::testing::Test {
protected:
    // Mock objects can be initialized here
    PopplerAnnotMock mock_annot;
};

// Test for normal operation
TEST_F(PopplerAnnotLineTest_2053, AnnotLineCreation_2053) {
    std::shared_ptr<Annot> annot = std::make_shared<Annot>();
    
    // Expect the call to _poppler_create_annot with specific arguments
    EXPECT_CALL(mock_annot, _poppler_create_annot(POPPLER_TYPE_ANNOT_LINE, annot))
        .Times(1)
        .WillOnce(testing::Return(new PopplerAnnot()));
    
    // Call the function under test
    PopplerAnnot* result = _poppler_annot_line_new(annot);

    // Validate that the result is not null
    ASSERT_NE(result, nullptr);
}

// Test boundary condition - passing a null pointer as Annot
TEST_F(PopplerAnnotLineTest_2053, NullAnnot_2053) {
    std::shared_ptr<Annot> annot = nullptr;
    
    // Expect the call to _poppler_create_annot with null annot
    EXPECT_CALL(mock_annot, _poppler_create_annot(POPPLER_TYPE_ANNOT_LINE, annot))
        .Times(1)
        .WillOnce(testing::Return(nullptr));
    
    // Call the function under test
    PopplerAnnot* result = _poppler_annot_line_new(annot);

    // Validate that the result is null
    ASSERT_EQ(result, nullptr);
}

// Test exceptional or error case - mocking the creation function to simulate failure
TEST_F(PopplerAnnotLineTest_2053, AnnotLineCreationFailure_2053) {
    std::shared_ptr<Annot> annot = std::make_shared<Annot>();
    
    // Simulate failure in creation (e.g., out of memory, etc.)
    EXPECT_CALL(mock_annot, _poppler_create_annot(POPPLER_TYPE_ANNOT_LINE, annot))
        .Times(1)
        .WillOnce(testing::Return(nullptr));

    // Call the function under test and expect failure (null return)
    PopplerAnnot* result = _poppler_annot_line_new(annot);

    // Validate that the result is null, indicating a failure
    ASSERT_EQ(result, nullptr);
}