#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/glib/poppler-form-field.cc"

}



using ::testing::_;

using ::testing::Return;

using ::testing::NotNull;



class MockFormWidget : public FormWidget {

public:

    MOCK_METHOD0(getMappingName, const GooString*());

};



class PopplerFormFieldTest_2318 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_widget = std::make_unique<MockFormWidget>();

        field.widget = mock_widget.get();

    }



    std::unique_ptr<MockFormWidget> mock_widget;

    _PopplerFormField field;

};



TEST_F(PopplerFormFieldTest_2318, GetMappingName_ReturnsValidString_2318) {

    const char* expected_mapping_name = "test_mapping_name";

    GooString goo_string(expected_mapping_name);



    EXPECT_CALL(*mock_widget, getMappingName()).WillOnce(Return(&goo_string));



    gchar* result = poppler_form_field_get_mapping_name(reinterpret_cast<PopplerFormField*>(&field));

    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, expected_mapping_name);

    g_free(result);

}



TEST_F(PopplerFormFieldTest_2318, GetMappingName_ReturnsNull_2318) {

    EXPECT_CALL(*mock_widget, getMappingName()).WillOnce(Return(nullptr));



    gchar* result = poppler_form_field_get_mapping_name(reinterpret_cast<PopplerFormField*>(&field));

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerFormFieldTest_2318, GetMappingName_NullField_ReturnsNull_2318) {

    gchar* result = poppler_form_field_get_mapping_name(nullptr);

    EXPECT_EQ(result, nullptr);

}
