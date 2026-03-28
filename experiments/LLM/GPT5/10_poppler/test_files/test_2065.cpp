#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/glib/poppler-annot.h"
#include "./TestProjects/poppler/glib/poppler-private.h"

// Mocking necessary external dependencies
class MockAnnot {
public:
    MOCK_METHOD(GooString*, getName, (), (const));
};

// Mock class to simulate PopplerAnnot
class MockPopplerAnnot {
public:
    std::shared_ptr<MockAnnot> annot;
};

// Test fixture for PopplerAnnot
class PopplerAnnotTest_2065 : public ::testing::Test {
protected:
    // Helper function to create a PopplerAnnot mock
    PopplerAnnot* createMockPopplerAnnot() {
        auto mockAnnot = std::make_shared<MockAnnot>();
        auto popplerAnnot = new PopplerAnnot;
        popplerAnnot->annot = mockAnnot;
        return popplerAnnot;
    }
};

// Test case for valid PopplerAnnot with a valid name
TEST_F(PopplerAnnotTest_2065, GetNameValidAnnot_2065) {
    // Setup mock behavior for getName
    auto popplerAnnot = createMockPopplerAnnot();
    auto mockAnnot = popplerAnnot->annot;
    GooString testName("ValidName");
    
    EXPECT_CALL(*mockAnnot, getName())
        .WillOnce(testing::Return(&testName)); // Simulate a valid name

    gchar* result = poppler_annot_get_name(popplerAnnot);

    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result, "ValidName");
}

// Test case for invalid PopplerAnnot (null name)
TEST_F(PopplerAnnotTest_2065, GetNameNullAnnot_2065) {
    // Setup mock behavior for getName
    auto popplerAnnot = createMockPopplerAnnot();
    auto mockAnnot = popplerAnnot->annot;

    EXPECT_CALL(*mockAnnot, getName())
        .WillOnce(testing::Return(nullptr)); // Simulate a null name

    gchar* result = poppler_annot_get_name(popplerAnnot);

    ASSERT_EQ(result, nullptr);
}

// Test case for invalid PopplerAnnot (null object)
TEST_F(PopplerAnnotTest_2065, GetNameNullObject_2065) {
    PopplerAnnot* nullPopplerAnnot = nullptr;

    gchar* result = poppler_annot_get_name(nullPopplerAnnot);

    ASSERT_EQ(result, nullptr);
}

// Test case for PopplerAnnot with an empty name
TEST_F(PopplerAnnotTest_2065, GetNameEmptyAnnot_2065) {
    // Setup mock behavior for getName
    auto popplerAnnot = createMockPopplerAnnot();
    auto mockAnnot = popplerAnnot->annot;
    GooString emptyName("");

    EXPECT_CALL(*mockAnnot, getName())
        .WillOnce(testing::Return(&emptyName)); // Simulate an empty name

    gchar* result = poppler_annot_get_name(popplerAnnot);

    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result, "");
}

// Test case for invalid PopplerAnnot (not an annotation)
TEST_F(PopplerAnnotTest_2065, GetNameInvalidAnnotType_2065) {
    PopplerAnnot* invalidPopplerAnnot = nullptr;

    gchar* result = poppler_annot_get_name(invalidPopplerAnnot);

    ASSERT_EQ(result, nullptr);
}