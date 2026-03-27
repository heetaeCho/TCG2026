#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"

#include "./TestProjects/poppler/poppler/Form.h"



using namespace testing;



class PopplerFormFieldMock : public FormWidgetText {

public:

    PopplerFormFieldMock(PDFDoc* docA, Object* dictObj, unsigned int num, Ref ref, FormField* p)

        : FormWidgetText(docA, dictObj, num, ref, p) {}



    MOCK_CONST_METHOD0(noSpellCheck, bool());

};



class PopplerFormFieldTest_2336 : public Test {

protected:

    PDFDoc mockPDFDoc;

    Object mockDictObj;

    Ref mockRef;

    FormField mockFormField;



    PopplerFormFieldMock* formWidgetText;

    PopplerFormField field;



    void SetUp() override {

        formWidgetText = new PopplerFormFieldMock(&mockPDFDoc, &mockDictObj, 0, mockRef, &mockFormField);

        field.widget = static_cast<FormWidget*>(formWidgetText);

    }



    void TearDown() override {

        delete formWidgetText;

    }

};



TEST_F(PopplerFormFieldTest_2336, SpellCheckEnabled_2336) {

    EXPECT_CALL(*formWidgetText, noSpellCheck()).WillOnce(Return(false));

    EXPECT_EQ(poppler_form_field_text_do_spell_check(&field), TRUE);

}



TEST_F(PopplerFormFieldTest_2336, SpellCheckDisabled_2336) {

    EXPECT_CALL(*formWidgetText, noSpellCheck()).WillOnce(Return(true));

    EXPECT_EQ(poppler_form_field_text_do_spell_check(&field), FALSE);

}
