#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-form-field.cc"

#include "TestProjects/poppler/poppler/Form.h"



using ::testing::NiceMock;

using ::testing::Return;



class MockFormWidgetText : public FormWidgetText {

public:

    MOCK_CONST_METHOD0(getContent, const GooString*());

};



class PopplerFormFieldTextGetTextTest_2333 : public testing::Test {

protected:

    std::unique_ptr<MockFormWidgetText> mock_text_widget;

    PopplerFormField form_field;



    void SetUp() override {

        mock_text_widget = std::make_unique<NiceMock<MockFormWidgetText>>();

        form_field.widget = mock_text_widget.get();

    }

};



TEST_F(PopplerFormFieldTextGetTextTest_2333, NormalOperation_ReturnsContent_2333) {

    const GooString expected_content("test content");

    EXPECT_CALL(*mock_text_widget, getContent()).WillOnce(Return(&expected_content));



    gchar* result = poppler_form_field_text_get_text(&form_field);

    ASSERT_STREQ(result, "test content");



    g_free(result);

}



TEST_F(PopplerFormFieldTextGetTextTest_2333, ContentIsNull_ReturnsNull_2333) {

    EXPECT_CALL(*mock_text_widget, getContent()).WillOnce(Return(nullptr));



    gchar* result = poppler_form_field_text_get_text(&form_field);

    ASSERT_EQ(result, nullptr);



    g_free(result); // Safe to call on null

}



TEST_F(PopplerFormFieldTextGetTextTest_2333, WidgetTypeMismatch_ReturnsNull_2333) {

    form_field.widget->setType(formButton); // Mismatched type



    gchar* result = poppler_form_field_text_get_text(&form_field);

    ASSERT_EQ(result, nullptr);



    g_free(result); // Safe to call on null

}



TEST_F(PopplerFormFieldTextGetTextTest_2333, BoundaryCondition_EmptyString_ReturnsEmptyString_2333) {

    const GooString empty_content("");

    EXPECT_CALL(*mock_text_widget, getContent()).WillOnce(Return(&empty_content));



    gchar* result = poppler_form_field_text_get_text(&form_field);

    ASSERT_STREQ(result, "");



    g_free(result);

}



TEST_F(PopplerFormFieldTextGetTextTest_2333, BoundaryCondition_MaxLengthString_ReturnsMaxLengthString_2333) {

    std::string max_length_content(65535, 'a'); // Assuming a reasonable max length for GooString

    const GooString goo_max_length_content(max_length_content.c_str());

    EXPECT_CALL(*mock_text_widget, getContent()).WillOnce(Return(&goo_max_length_content));



    gchar* result = poppler_form_field_text_get_text(&form_field);

    ASSERT_STREQ(result, max_length_content.c_str());



    g_free(result);

}
