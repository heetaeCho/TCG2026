#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-form-field.cc"

#include "TestProjects/poppler/poppler/Form.h"

#include "TestProjects/poppler/glib/poppler-private.h"



using namespace testing;



class PopplerFormFieldTest_2317 : public ::testing::Test {

protected:

    std::shared_ptr<MockFormWidget> mock_widget;

    PopplerFormField field;



    class MockFormWidget : public FormWidget {

    public:

        MOCK_CONST_METHOD0(getPartialName, const GooString*());

        MOCK_METHOD1(setPartialName, void(const GooString & name));

        MOCK_METHOD0(getID, unsigned());



        MockFormWidget(PDFDoc * docA, Object * aobj, unsigned int num, Ref aref, FormField * fieldA)

            : FormWidget(docA, aobj, num, aref, fieldA) {}

    };



    PopplerFormFieldTest_2317() {

        mock_widget = std::make_shared<MockFormWidget>(nullptr, nullptr, 0, Ref(), nullptr);

        field.widget = mock_widget.get();

    }

};



TEST_F(PopplerFormFieldTest_2317, GetPartialName_NormalOperation_2317) {

    const char* expected_name = "testPartialName";

    GooString goo_string(expected_name);



    EXPECT_CALL(*mock_widget, getPartialName())

        .WillOnce(Return(&goo_string));



    gchar* result = poppler_form_field_get_partial_name(&field);

    ASSERT_STREQ(result, expected_name);

    g_free(result);

}



TEST_F(PopplerFormFieldTest_2317, GetPartialName_ReturnsNull_2317) {

    EXPECT_CALL(*mock_widget, getPartialName())

        .WillOnce(Return(nullptr));



    gchar* result = poppler_form_field_get_partial_name(&field);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerFormFieldTest_2317, GetPartialName_NullField_2317) {

    PopplerFormField null_field{nullptr};

    gchar* result = poppler_form_field_get_partial_name(&null_field);

    ASSERT_EQ(result, nullptr);

}
