#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "Annot.h"

class PopplerAnnotTextTest_2090 : public ::testing::Test {
protected:
    PopplerAnnotText *poppler_annot;
    AnnotText *annot;

    void SetUp() override {
        // Assuming there is a way to create or mock PopplerAnnotText
        poppler_annot = /* create or mock PopplerAnnotText object */;
        annot = static_cast<AnnotText *>(POPPLER_ANNOT(poppler_annot)->annot.get());
    }

    void TearDown() override {
        // Clean up the PopplerAnnotText if needed
    }
};

// Test normal operation for setting the 'open' state
TEST_F(PopplerAnnotTextTest_2090, SetOpenTrue_2090) {
    // Mock expected behavior
    EXPECT_CALL(*annot, setOpen(true))
        .Times(1);

    // Call the function under test
    poppler_annot_text_set_is_open(poppler_annot, TRUE);
}

// Test normal operation for setting the 'closed' state
TEST_F(PopplerAnnotTextTest_2090, SetOpenFalse_2090) {
    // Mock expected behavior
    EXPECT_CALL(*annot, setOpen(false))
        .Times(1);

    // Call the function under test
    poppler_annot_text_set_is_open(poppler_annot, FALSE);
}

// Test that function fails when poppler_annot is NULL
TEST_F(PopplerAnnotTextTest_2090, SetOpenFailsOnNullAnnot_2090) {
    // Expect no calls if poppler_annot is NULL
    EXPECT_CALL(*annot, setOpen(testing::_)).Times(0);

    // Call the function under test with a NULL poppler_annot
    poppler_annot_text_set_is_open(nullptr, TRUE);
}

// Test the behavior when POPPLER_IS_ANNOT_TEXT fails (g_return_if_fail)
TEST_F(PopplerAnnotTextTest_2090, SetOpenFailsOnInvalidAnnot_2090) {
    // Simulate invalid PopplerAnnotText
    PopplerAnnotText *invalid_annot = nullptr;

    // Expect no interaction with annot's setOpen method
    EXPECT_CALL(*annot, setOpen(testing::_)).Times(0);

    // Call the function with an invalid annot (nullptr or invalid type)
    poppler_annot_text_set_is_open(invalid_annot, TRUE);
}

// Test that setOpen is called with the correct value
TEST_F(PopplerAnnotTextTest_2090, SetOpenCalledWithCorrectValue_2090) {
    // Simulate a valid case where the 'open' value is set to true
    poppler_annot_text_set_is_open(poppler_annot, TRUE);
    EXPECT_TRUE(annot->getOpen());

    // Set 'open' to false
    poppler_annot_text_set_is_open(poppler_annot, FALSE);
    EXPECT_FALSE(annot->getOpen());
}