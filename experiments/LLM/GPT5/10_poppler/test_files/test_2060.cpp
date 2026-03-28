#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Forward declaration of the dependencies and types.
class Annot;
class PopplerAnnot;

// Mock for external collaborators (if any).
class MockAnnot : public Annot {
public:
    MOCK_METHOD(void, someMethod, (), (const));
};

// The function to be tested.
PopplerAnnot *_poppler_annot_stamp_new(const std::shared_ptr<Annot> &annot);

// Test Fixture Class
class PopplerAnnotTest_2060 : public ::testing::Test {
protected:
    // Optional: Set up common resources needed for all tests
    void SetUp() override {
        annot = std::make_shared<MockAnnot>();
    }

    // Mocked object for Annot
    std::shared_ptr<MockAnnot> annot;
};

// Normal operation test case
TEST_F(PopplerAnnotTest_2060, StampAnnotCreation_2060) {
    // Expectations: Ensure _poppler_create_annot is called correctly.
    EXPECT_CALL(*annot, someMethod()).Times(1);

    PopplerAnnot* poppler_annot = _poppler_annot_stamp_new(annot);

    // Validate the result, assuming that the return value should not be null in normal operation
    ASSERT_NE(poppler_annot, nullptr);
}

// Boundary condition test case
TEST_F(PopplerAnnotTest_2060, NullAnnotPointer_2061) {
    // Ensure behavior when the input is null
    std::shared_ptr<Annot> null_annot = nullptr;

    PopplerAnnot* poppler_annot = _poppler_annot_stamp_new(null_annot);

    // Check for the expected behavior when passing a null pointer
    ASSERT_EQ(poppler_annot, nullptr);
}

// Exceptional case test: simulate an error if _poppler_create_annot fails
TEST_F(PopplerAnnotTest_2060, AnnotCreationFails_2062) {
    // Simulate the case where creation fails, possibly by mocking failure conditions (if applicable)
    EXPECT_CALL(*annot, someMethod()).WillOnce(::testing::Throw(std::runtime_error("Creation failed")));

    try {
        PopplerAnnot* poppler_annot = _poppler_annot_stamp_new(annot);
        FAIL() << "Expected std::runtime_error to be thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Creation failed");
    }
}