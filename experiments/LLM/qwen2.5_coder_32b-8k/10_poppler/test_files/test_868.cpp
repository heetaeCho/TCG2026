#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Form.h"

#include "GooString.h"



using namespace testing;



class FormWidgetTest_868 : public Test {

protected:

    PDFDoc* mockPdfDoc;

    Object* mockObject;

    Ref mockRef;

    FormField* mockFormField;

    std::shared_ptr<AnnotWidget> mockWidgetAnnotation;

    FormWidget* formWidget;



    void SetUp() override {

        mockPdfDoc = static_cast<PDFDoc*>(mock());

        mockObject = static_cast<Object*>(mock());

        mockFormField = static_cast<FormField*>(mock());

        mockRef = Ref{1, 0};

        mockWidgetAnnotation = std::make_shared<AnnotWidget>(mockPdfDoc, mockObject, mockRef);



        formWidget = new FormWidget(mockPdfDoc, mockObject, 42, mockRef, mockFormField);

    }



    void TearDown() override {

        delete formWidget;

    }

};



TEST_F(FormWidgetTest_868, GetID_ReturnsInitializedValue_868) {

    EXPECT_EQ(formWidget->getID(), 0U);

}



TEST_F(FormWidgetTest_868, SetID_ChangesIDValue_868) {

    unsigned int newId = 12345;

    formWidget->setID(newId);

    EXPECT_EQ(formWidget->getID(), newId);

}



TEST_F(FormWidgetTest_868, InRect_ReturnsFalseForInvalidPoint_868) {

    EXPECT_FALSE(formWidget->inRect(-1.0, -1.0));

}



TEST_F(FormWidgetTest_868, GetPartialName_ReturnsNullptrByDefault_868) {

    EXPECT_EQ(formWidget->getPartialName(), nullptr);

}



TEST_F(FormWidgetTest_868, SetAndGetPartialName_WorksCorrectly_868) {

    GooString name("testName");

    formWidget->setPartialName(name);

    EXPECT_STREQ(formWidget->getPartialName()->getCString(), "testName");

}



TEST_F(FormWidgetTest_868, GetAlternateUiName_ReturnsNullptrByDefault_868) {

    EXPECT_EQ(formWidget->getAlternateUiName(), nullptr);

}



TEST_F(FormWidgetTest_868, GetMappingName_ReturnsNullptrByDefault_868) {

    EXPECT_EQ(formWidget->getMappingName(), nullptr);

}



TEST_F(FormWidgetTest_868, GetFullyQualifiedName_ReturnsNullptrByDefault_868) {

    EXPECT_EQ(formWidget->getFullyQualifiedName(), nullptr);

}



TEST_F(FormWidgetTest_868, IsModified_ReturnsFalseInitially_868) {

    EXPECT_FALSE(formWidget->isModified());

}



TEST_F(FormWidgetTest_868, IsReadOnly_ReturnsFalseInitially_868) {

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_868, SetReadOnly_ChangesStateCorrectly_868) {

    formWidget->setReadOnly(true);

    EXPECT_TRUE(formWidget->isReadOnly());



    formWidget->setReadOnly(false);

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_868, GetActivationAction_ReturnsNullptrByDefault_868) {

    EXPECT_EQ(formWidget->getActivationAction(), nullptr);

}



TEST_F(FormWidgetTest_868, GetAdditionalAction_ReturnsNullptrForUnknownType_868) {

    EXPECT_EQ(formWidget->getAdditionalAction(Annot::FormAAFormat), nullptr);

}



TEST_F(FormWidgetTest_868, SetAndGetAdditionalAction_WorksCorrectly_868) {

    Annot::FormAdditionalActionsType type = Annot::FormAAFormat;

    std::string js("app.alert('Hello');");

    EXPECT_TRUE(formWidget->setAdditionalAction(type, js));

    auto action = formWidget->getAdditionalAction(type);

    ASSERT_NE(action, nullptr);

    // Assuming getJS() is available to retrieve the script

    // EXPECT_STREQ(action->getJS()->getCString(), "app.alert('Hello');");

}



TEST_F(FormWidgetTest_868, EncodeID_CreatesValidID_868) {

    unsigned int pageNum = 10;

    unsigned int fieldNum = 20;

    unsigned int id = FormWidget::encodeID(pageNum, fieldNum);

    EXPECT_NE(id, 0U);



    unsigned int decodedPageNum = 0;

    unsigned int decodedFieldNum = 0;

    FormWidget::decodeID(id, &decodedPageNum, &decodedFieldNum);

    EXPECT_EQ(decodedPageNum, pageNum);

    EXPECT_EQ(decodedFieldNum, fieldNum);

}



TEST_F(FormWidgetTest_868, GetChildNum_ReturnsInitializedValue_868) {

    EXPECT_EQ(formWidget->getChildNum(), 42U);

}



TEST_F(FormWidgetTest_868, SetAndGetChildNum_WorksCorrectly_868) {

    unsigned int newChildNum = 50;

    formWidget->setChildNum(newChildNum);

    EXPECT_EQ(formWidget->getChildNum(), newChildNum);

}



TEST_F(FormWidgetTest_868, GetWidgetAnnotation_ReturnsNullptrInitially_868) {

    EXPECT_EQ(formWidget->getWidgetAnnotation(), nullptr);

}



TEST_F(FormWidgetTest_868, SetAndGetWidgetAnnotation_WorksCorrectly_868) {

    formWidget->setWidgetAnnotation(mockWidgetAnnotation);

    EXPECT_EQ(formWidget->getWidgetAnnotation(), mockWidgetAnnotation);

}
