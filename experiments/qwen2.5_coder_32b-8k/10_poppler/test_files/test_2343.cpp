#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock FormWidgetChoice class to simulate external interactions

class MockFormWidgetChoice : public FormWidgetChoice {

public:

    using FormWidgetChoice::FormWidgetChoice;



    MOCK_CONST_METHOD0(noSpellCheck, bool());

};



// Test fixture for poppler_form_field_choice_do_spell_check function

class PopplerFormFieldChoiceDoSpellCheckTest_2343 : public ::testing::Test {

protected:

    MockFormWidgetChoice mockWidget;

    PopplerFormField field{reinterpret_cast<FormWidget*>(&mockWidget), nullptr, 0, Ref{}, nullptr};



    void SetUp() override {

        // Set up the form widget type to be formChoice

        ON_CALL(mockWidget, getType()).WillByDefault(testing::Return(formChoice));

    }

};



// Test normal operation when spell check is enabled

TEST_F(PopplerFormFieldChoiceDoSpellCheckTest_2343, SpellCheckEnabled_2343) {

    EXPECT_CALL(mockWidget, noSpellCheck()).WillOnce(testing::Return(false));



    gboolean result = poppler_form_field_choice_do_spell_check(&field);

    EXPECT_TRUE(result);

}



// Test normal operation when spell check is disabled

TEST_F(PopplerFormFieldChoiceDoSpellCheckTest_2343, SpellCheckDisabled_2343) {

    EXPECT_CALL(mockWidget, noSpellCheck()).WillOnce(testing::Return(true));



    gboolean result = poppler_form_field_choice_do_spell_check(&field);

    EXPECT_FALSE(result);

}



// Test boundary condition with null field pointer

TEST(PopplerFormFieldChoiceDoSpellCheckTest_2343, NullFieldPointer_2343) {

    PopplerFormField* nullField = nullptr;



    gboolean result = poppler_form_field_choice_do_spell_check(nullField);

    EXPECT_FALSE(result);

}



// Test boundary condition with incorrect widget type

TEST(PopplerFormFieldChoiceDoSpellCheckTest_2343, IncorrectWidgetType_2343) {

    MockFormWidgetChoice mockNonChoiceWidget;

    PopplerFormField field{reinterpret_cast<FormWidget*>(&mockNonChoiceWidget), nullptr, 0, Ref{}, nullptr};



    ON_CALL(mockNonChoiceWidget, getType()).WillByDefault(testing::Return(formText));



    gboolean result = poppler_form_field_choice_do_spell_check(&field);

    EXPECT_FALSE(result);

}
