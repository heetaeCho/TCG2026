#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers and namespace usings are included



class PopplerFormFieldTest_2338 : public ::testing::Test {

protected:

    struct _PopplerFormField formField;

    FormWidgetText* mockFormWidgetText;



    void SetUp() override {

        mockFormWidgetText = new testing::NiceMock<FormWidgetText>(nullptr, nullptr, 0, Ref(), nullptr);

        formField.widget = mockFormWidgetText;

    }



    void TearDown() override {

        delete mockFormWidgetText;

    }

};



TEST_F(PopplerFormFieldTest_2338, IsRichText_ReturnsTrueWhenRichTextEnabled_2338) {

    EXPECT_CALL(*mockFormWidgetText, isRichText()).WillOnce(testing::Return(true));

    EXPECT_TRUE(poppler_form_field_text_is_rich_text(&formField));

}



TEST_F(PopplerFormFieldTest_2338, IsRichText_ReturnsFalseWhenRichTextDisabled_2338) {

    EXPECT_CALL(*mockFormWidgetText, isRichText()).WillOnce(testing::Return(false));

    EXPECT_FALSE(poppler_form_field_text_is_rich_text(&formField));

}



TEST_F(PopplerFormFieldTest_2338, IsRichText_ThrowsErrorWhenFieldIsNotFormText_2338) {

    formField.widget->setType(formButton); // Assuming there's a setType method for testing purposes

    EXPECT_DEATH(poppler_form_field_text_is_rich_text(&formField), ".*");

}
