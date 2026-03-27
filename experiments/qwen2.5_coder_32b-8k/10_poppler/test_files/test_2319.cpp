#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"

#include "poppler-private.h"



using namespace testing;



class MockGooString {

public:

    MOCK_METHOD0(c_str, const char*());

};



TEST_F(PopplerFormFieldTest_2319, GetNameReturnsNullIfFieldIsNull_2319) {

    EXPECT_EQ(poppler_form_field_get_name(nullptr), nullptr);

}



TEST_F(PopplerFormFieldTest_2319, GetNameReturnsUtf8String_2319) {

    auto mockGooString = std::make_unique<MockGooString>();

    const GooString* gooStringPtr = mockGooString.get();



    EXPECT_CALL(*mockGooString, c_str()).WillOnce(Return("FullyQualifiedName"));



    PopplerFormField field;

    field.widget = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr);

    ON_CALL(*field.widget, getFullyQualifiedName()).WillByDefault(Return(gooStringPtr));



    gchar* name = poppler_form_field_get_name(&field);

    EXPECT_STREQ(name, "FullyQualifiedName");

    g_free(name);



    delete field.widget;

}



TEST_F(PopplerFormFieldTest_2319, GetNameReturnsNullIfGooStringIsNull_2319) {

    PopplerFormField field;

    field.widget = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr);

    ON_CALL(*field.widget, getFullyQualifiedName()).WillByDefault(Return(static_cast<const GooString*>(nullptr)));



    EXPECT_EQ(poppler_form_field_get_name(&field), nullptr);



    delete field.widget;

}
