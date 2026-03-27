#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "poppler-private.h"
#include "Annot.h"

using namespace testing;

class PopplerAnnotTest_2062 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup any necessary objects here
    }

    void TearDown() override {
        // Clean up after each test here
    }
};

TEST_F(PopplerAnnotTest_2062, TestUnknownAnnotType_2062) {
    // Test case where the PopplerAnnot is invalid (null)
    PopplerAnnot* poppler_annot = nullptr;
    EXPECT_EQ(poppler_annot_get_annot_type(poppler_annot), POPPLER_ANNOT_UNKNOWN);
}

TEST_F(PopplerAnnotTest_2062, TestValidAnnotType_2062) {
    // Test case where we pass a valid PopplerAnnot with a known type
    PopplerAnnot poppler_annot;
    auto mock_annot = std::make_shared<MockAnnot>();
    poppler_annot.annot = mock_annot;

    EXPECT_CALL(*mock_annot, getType()).WillOnce(Return(Annot::typeText));
    EXPECT_EQ(poppler_annot_get_annot_type(&poppler_annot), POPPLER_ANNOT_TEXT);

    EXPECT_CALL(*mock_annot, getType()).WillOnce(Return(Annot::typeLink));
    EXPECT_EQ(poppler_annot_get_annot_type(&poppler_annot), POPPLER_ANNOT_LINK);

    EXPECT_CALL(*mock_annot, getType()).WillOnce(Return(Annot::typeFreeText));
    EXPECT_EQ(poppler_annot_get_annot_type(&poppler_annot), POPPLER_ANNOT_FREE_TEXT);
}

TEST_F(PopplerAnnotTest_2062, TestInvalidAnnotType_2062) {
    // Test case where we pass a PopplerAnnot with an unsupported type
    PopplerAnnot poppler_annot;
    auto mock_annot = std::make_shared<MockAnnot>();
    poppler_annot.annot = mock_annot;

    EXPECT_CALL(*mock_annot, getType()).WillOnce(Return(static_cast<Annot::AnnotSubtype>(1000)));  // Invalid type

    EXPECT_EQ(poppler_annot_get_annot_type(&poppler_annot), POPPLER_ANNOT_UNKNOWN);
}

TEST_F(PopplerAnnotTest_2062, TestNullAnnotPointer_2062) {
    // Test case where the PopplerAnnot pointer is null
    PopplerAnnot* poppler_annot = nullptr;
    EXPECT_EQ(poppler_annot_get_annot_type(poppler_annot), POPPLER_ANNOT_UNKNOWN);
}

TEST_F(PopplerAnnotTest_2062, TestMockInteraction_2062) {
    // Verifying external interactions with MockAnnot
    PopplerAnnot poppler_annot;
    auto mock_annot = std::make_shared<MockAnnot>();
    poppler_annot.annot = mock_annot;

    // Setting expectations for the mock
    EXPECT_CALL(*mock_annot, getType()).WillOnce(Return(Annot::typeHighlight));

    // Call the function under test
    poppler_annot_get_annot_type(&poppler_annot);

    // Verifying the mock was called once
    verify(mock_annot, times(1)).getType();
}

class MockAnnot : public Annot {
public:
    MOCK_METHOD(Annot::AnnotSubtype, getType, (), (const, override));
};