#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"



using namespace testing;



class PopplerFormFieldChoiceTest_2344 : public Test {

protected:

    class MockFormWidgetChoice : public FormWidgetChoice {

    public:

        MOCK_METHOD(bool, commitOnSelChange, (), (const override));

        MockFormWidgetChoice(PDFDoc* docA, Object* dictObj, unsigned int num, Ref ref, FormField* p)

            : FormWidgetChoice(docA, dictObj, num, ref, p) {}

    };



    PDFDoc* mockPDFDoc;

    Object* mockObject;

    PopplerFormField formField;



    void SetUp() override {

        mockPDFDoc = static_cast<PDFDoc*>(mock());

        mockObject = static_cast<Object*>(mock());

        auto mockWidget = std::make_unique<MockFormWidgetChoice>(mockPDFDoc, mockObject, 0, Ref(), nullptr);

        formField.widget = mockWidget.release();

    }



    void TearDown() override {

        delete formField.widget;

    }

};



TEST_F(PopplerFormFieldChoiceTest_2344, CommitOnSelChange_ReturnsTrue_2344) {

    MockFormWidgetChoice* widget = static_cast<MockFormWidgetChoice*>(formField.widget);

    EXPECT_CALL(*widget, commitOnSelChange()).WillOnce(Return(true));

    

    gboolean result = poppler_form_field_choice_commit_on_change(&formField);

    EXPECT_TRUE(result);

}



TEST_F(PopplerFormFieldChoiceTest_2344, CommitOnSelChange_ReturnsFalse_2344) {

    MockFormWidgetChoice* widget = static_cast<MockFormWidgetChoice*>(formField.widget);

    EXPECT_CALL(*widget, commitOnSelChange()).WillOnce(Return(false));

    

    gboolean result = poppler_form_field_choice_commit_on_change(&formField);

    EXPECT_FALSE(result);

}



TEST_F(PopplerFormFieldChoiceTest_2344, NullField_ReturnsFalse_2344) {

    formField.widget = nullptr;

    gboolean result = poppler_form_field_choice_commit_on_change(&formField);

    EXPECT_FALSE(result);

}
