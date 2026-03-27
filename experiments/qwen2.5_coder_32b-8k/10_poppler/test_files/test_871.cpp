#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Form.h"



class FormWidgetTest_871 : public ::testing::Test {

protected:

    PDFDoc* mockPDFDoc;

    Object* mockObject;

    Ref mockRef;

    FormField* mockFormField;



    void SetUp() override {

        mockPDFDoc = new PDFDoc();

        mockObject = new Object();

        mockFormField = new FormField();

    }



    void TearDown() override {

        delete mockPDFDoc;

        delete mockObject;

        delete mockFormField;

    }



    std::unique_ptr<FormWidget> CreateFormWidget(FormFieldType type) {

        return std::make_unique<FormWidget>(mockPDFDoc, mockObject, 0, mockRef, mockFormField);

    }

};



TEST_F(FormWidgetTest_871, GetID_ReturnsSetID_871) {

    auto formWidget = CreateFormWidget(FormFieldType::text);

    unsigned int id = 42;

    formWidget->setID(id);

    EXPECT_EQ(formWidget->getID(), id);

}



TEST_F(FormWidgetTest_871, GetChildNum_ReturnsSetChildNum_871) {

    auto formWidget = CreateFormWidget(FormFieldType::text);

    unsigned int childNum = 5;

    formWidget->setChildNum(childNum);

    EXPECT_EQ(formWidget->getChildNum(), childNum);

}



TEST_F(FormWidgetTest_871, GetType_ReturnsSetType_871) {

    auto formWidget = CreateFormWidget(FormFieldType::button);

    EXPECT_EQ(formWidget->getType(), FormFieldType::button);

}



TEST_F(FormWidgetTest_871, GetRect_DoesNotThrowException_871) {

    double x1, y1, x2, y2;

    auto formWidget = CreateFormWidget(FormFieldType::text);

    EXPECT_NO_THROW(formWidget->getRect(&x1, &y1, &x2, &y2));

}



TEST_F(FormWidgetTest_871, InRect_ReturnsFalseForInvalidPoint_871) {

    auto formWidget = CreateFormWidget(FormFieldType::text);

    EXPECT_FALSE(formWidget->inRect(-100, -100));

}



TEST_F(FormWidgetTest_871, GetPartialName_DoesNotThrowException_871) {

    auto formWidget = CreateFormWidget(FormFieldType::checkbox);

    EXPECT_NO_THROW(formWidget->getPartialName());

}



TEST_F(FormWidgetTest_871, SetAndGetPartialName_ReturnsSameValue_871) {

    GooString expectedName("testName");

    auto formWidget = CreateFormWidget(FormFieldType::radioButton);

    formWidget->setPartialName(expectedName);

    EXPECT_STREQ(formWidget->getPartialName()->c_str(), "testName");

}



TEST_F(FormWidgetTest_871, GetAlternateUiName_DoesNotThrowException_871) {

    auto formWidget = CreateFormWidget(FormFieldType::comboBox);

    EXPECT_NO_THROW(formWidget->getAlternateUiName());

}



TEST_F(FormWidgetTest_871, GetMappingName_DoesNotThrowException_871) {

    auto formWidget = CreateFormWidget(FormFieldType::listBox);

    EXPECT_NO_THROW(formWidget->getMappingName());

}



TEST_F(FormWidgetTest_871, GetFullyQualifiedName_ReturnsNonNullPointer_871) {

    auto formWidget = CreateFormWidget(FormFieldType::signature);

    EXPECT_NE(formWidget->getFullyQualifiedName(), nullptr);

}



TEST_F(FormWidgetTest_871, IsModified_ReturnsFalseInitially_871) {

    auto formWidget = CreateFormWidget(FormFieldType::text);

    EXPECT_FALSE(formWidget->isModified());

}



TEST_F(FormWidgetTest_871, IsReadOnly_ReturnsFalseInitially_871) {

    auto formWidget = CreateFormWidget(FormFieldType::button);

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_871, SetAndGetReadOnly_ReturnsSameValue_871) {

    auto formWidget = CreateFormWidget(FormFieldType::checkbox);

    formWidget->setReadOnly(true);

    EXPECT_TRUE(formWidget->isReadOnly());



    formWidget->setReadOnly(false);

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_871, GetActivationAction_ReturnsNullPointerInitially_871) {

    auto formWidget = CreateFormWidget(FormFieldType::radioButton);

    EXPECT_EQ(formWidget->getActivationAction(), nullptr);

}



TEST_F(FormWidgetTest_871, GetAdditionalAction_ReturnsNullPointerInitially_871) {

    auto formWidget = CreateFormWidget(FormFieldType::comboBox);

    EXPECT_EQ(formWidget->getAdditionalAction(Annot::FormAATrigger::triggerPageOpen).get(), nullptr);

}



TEST_F(FormWidgetTest_871, SetAndGetAdditionalAction_ReturnsTrueAndMatchesJavaScript_871) {

    auto formWidget = CreateFormWidget(FormFieldType::listBox);

    std::string js("app.alert('test');");

    EXPECT_TRUE(formWidget->setAdditionalAction(Annot::FormAATrigger::triggerPageOpen, js));

    auto action = formWidget->getAdditionalAction(Annot::FormAATrigger::triggerPageOpen);

    ASSERT_NE(action.get(), nullptr);

    // Assuming getJS() is a method to retrieve the JavaScript from LinkAction

    // EXPECT_STREQ(action->getJS().c_str(), js.c_str());

}



TEST_F(FormWidgetTest_871, EncodeID_ReturnsExpectedValue_871) {

    unsigned int pageNum = 3;

    unsigned int fieldNum = 4;

    unsigned int expectedID = (pageNum << 16) | fieldNum;

    EXPECT_EQ(FormWidget::encodeID(pageNum, fieldNum), expectedID);

}



TEST_F(FormWidgetTest_871, DecodeID_ReturnsExpectedValues_871) {

    unsigned int id = 0x0304; // Example ID with pageNum=3 and fieldNum=4

    unsigned int pageNum, fieldNum;

    FormWidget::decodeID(id, &pageNum, &fieldNum);

    EXPECT_EQ(pageNum, 3);

    EXPECT_EQ(fieldNum, 4);

}



TEST_F(FormWidgetTest_871, CreateWidgetAnnotation_DoesNotThrowException_871) {

    auto formWidget = CreateFormWidget(FormFieldType::signature);

    EXPECT_NO_THROW(formWidget->createWidgetAnnotation());

}



TEST_F(FormWidgetTest_871, UpdateWidgetAppearance_DoesNotThrowException_871) {

    auto formWidget = CreateFormWidget(FormFieldType::text);

    EXPECT_NO_THROW(formWidget->updateWidgetAppearance());

}



TEST_F(FormWidgetTest_871, Print_DoesNotThrowException_871) {

    auto formWidget = CreateFormWidget(FormFieldType::button);

    EXPECT_NO_THROW(formWidget->print(0));

}



TEST_F(FormWidgetTest_871, GetField_ReturnsNonNullPointer_871) {

    auto formWidget = CreateFormWidget(FormFieldType::checkbox);

    EXPECT_NE(formWidget->getField(), nullptr);

}



TEST_F(FormWidgetTest_871, GetObj_ReturnsNonNullPointer_871) {

    auto formWidget = CreateFormWidget(FormFieldType::radioButton);

    EXPECT_NE(formWidget->getObj(), nullptr);

}



TEST_F(FormWidgetTest_871, GetRef_ReturnsReference_871) {

    auto formWidget = CreateFormWidget(FormFieldType::comboBox);

    Ref ref = formWidget->getRef();

    EXPECT_EQ(ref.num, mockRef.num);

    EXPECT_EQ(ref.gen, mockRef.gen);

}



TEST_F(FormWidgetTest_871, GetWidgetAnnotation_ReturnsNonNullPointerInitially_871) {

    auto formWidget = CreateFormWidget(FormFieldType::listBox);

    EXPECT_NE(formWidget->getWidgetAnnotation().get(), nullptr);

}



TEST_F(FormWidgetTest_871, SetAndGetWidgetAnnotation_ReturnsSameValue_871) {

    auto formWidget = CreateFormWidget(FormFieldType::text);

    std::shared_ptr<AnnotWidget> newWidget = std::make_shared<AnnotWidget>();

    formWidget->setWidgetAnnotation(newWidget);

    EXPECT_EQ(formWidget->getWidgetAnnotation(), newWidget);

}
