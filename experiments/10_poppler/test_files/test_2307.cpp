#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-form-field.cc"

#include "TestProjects/poppler/Form.h"

#include "TestProjects/poppler/glib/poppler-private.h"



using namespace testing;



class PopplerFormFieldTest : public ::testing::Test {

protected:

    NiceMock<StrictMock<class FormWidget>>* mockFormWidget;

    PopplerDocument* document;



    void SetUp() override {

        mockFormWidget = new NiceMock<StrictMock<class FormWidget>>(nullptr, nullptr, 0, Ref(), nullptr);

        document = reinterpret_cast<PopplerDocument*>(g_malloc(sizeof(PopplerDocument)));

        document->parent_instance = 0;

        document->initer = 0;

        document->layers_rbgroups = nullptr;

        document->output_dev = nullptr;

    }



    void TearDown() override {

        delete mockFormWidget;

        g_free(document);

    }

};



TEST_F(PopplerFormFieldTest, NewFieldWithValidParameters_2307) {

    PopplerFormField* field = _poppler_form_field_new(document, mockFormWidget);

    ASSERT_NE(field, nullptr);

    EXPECT_EQ(field->document, document);

    EXPECT_EQ(field->widget, mockFormWidget);

    g_object_unref(field);

}



TEST_F(PopplerFormFieldTest, NewFieldWithNullDocument_2307) {

    PopplerFormField* field = _poppler_form_field_new(nullptr, mockFormWidget);

    EXPECT_EQ(field, nullptr);

}



TEST_F(PopplerFormFieldTest, NewFieldWithNullFormWidget_2307) {

    PopplerFormField* field = _poppler_form_field_new(document, nullptr);

    EXPECT_EQ(field, nullptr);

}
