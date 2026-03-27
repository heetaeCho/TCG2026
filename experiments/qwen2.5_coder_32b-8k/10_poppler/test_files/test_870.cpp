#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Form.h"



using namespace testing;



// Mock class for FormField to use in tests

class MockFormField : public FormField {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



class FormWidgetTest_870 : public ::testing::Test {

protected:

    void SetUp() override {

        field = std::make_unique<MockFormField>();

        widgetAnnotation = std::make_shared<AnnotWidget>();

        formWidget = new FormWidget(nullptr, nullptr, 1, Ref(), field.get());

        formWidget->setWidgetAnnotation(widgetAnnotation);

    }



    void TearDown() override {

        delete formWidget;

    }



    MockFormField* field;

    std::shared_ptr<AnnotWidget> widgetAnnotation;

    FormWidget* formWidget;

};



TEST_F(FormWidgetTest_870, getField_ReturnsCorrectField_870) {

    EXPECT_EQ(formWidget->getField(), field);

}



TEST_F(FormWidgetTest_870, inRect_ReturnsFalseForOutOfRangeCoordinates_870) {

    EXPECT_FALSE(formWidget->inRect(-1.0, -1.0));

}



TEST_F(FormWidgetTest_870, getRect_SetsCorrectValues_870) {

    double x1, y1, x2, y2;

    formWidget->getRect(&x1, &y1, &x2, &y2);

    // Assuming default values for a new widget annotation

    EXPECT_DOUBLE_EQ(x1, 0.0);

    EXPECT_DOUBLE_EQ(y1, 0.0);

    EXPECT_DOUBLE_EQ(x2, 0.0);

    EXPECT_DOUBLE_EQ(y2, 0.0);

}



TEST_F(FormWidgetTest_870, getPartialName_ReturnsEmptyStringByDefault_870) {

    EXPECT_STREQ(formWidget->getPartialName()->c_str(), "");

}



TEST_F(FormWidgetTest_870, setPartialName_SetsCorrectValue_870) {

    GooString expected("testName");

    formWidget->setPartialName(expected);

    EXPECT_STREQ(formWidget->getPartialName()->c_str(), "testName");

}



TEST_F(FormWidgetTest_870, getAlternateUiName_ReturnsEmptyStringByDefault_870) {

    EXPECT_STREQ(formWidget->getAlternateUiName()->c_str(), "");

}



TEST_F(FormWidgetTest_870, getMappingName_ReturnsEmptyStringByDefault_870) {

    EXPECT_STREQ(formWidget->getMappingName()->c_str(), "");

}



TEST_F(FormWidgetTest_870, getFullyQualifiedName_ReturnsCorrectValue_870) {

    GooString expected("testFullName");

    field->setFullyQualifiedName(expected);

    EXPECT_STREQ(formWidget->getFullyQualifiedName()->c_str(), "testFullName");

}



TEST_F(FormWidgetTest_870, isModified_ReturnsFalseByDefault_870) {

    EXPECT_FALSE(formWidget->isModified());

}



TEST_F(FormWidgetTest_870, isReadOnly_ReturnsFalseByDefault_870) {

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_870, setReadOnly_SetsCorrectValue_870) {

    formWidget->setReadOnly(true);

    EXPECT_TRUE(formWidget->isReadOnly());



    formWidget->setReadOnly(false);

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_870, getActivationAction_ReturnsNullptrByDefault_870) {

    EXPECT_EQ(formWidget->getActivationAction(), nullptr);

}



TEST_F(FormWidgetTest_870, getAdditionalAction_ReturnsNullptrForUnknownType_870) {

    EXPECT_EQ(formWidget->getAdditionalAction(Annot::FormAdditionalActionsType::A), nullptr);

}



TEST_F(FormWidgetTest_870, setAdditionalAction_SetsCorrectValue_870) {

    std::string js = "app.alert('Hello');";

    EXPECT_TRUE(formWidget->setAdditionalAction(Annot::FormAdditionalActionsType::A, js));

    auto action = formWidget->getAdditionalAction(Annot::FormAdditionalActionsType::A);

    ASSERT_NE(action, nullptr);

    // Assuming there is a method to get the JavaScript string from LinkAction

    // EXPECT_STREQ(action->getJavaScript()->c_str(), js.c_str());

}



TEST_F(FormWidgetTest_870, encodeID_ReturnsCorrectEncodedValue_870) {

    unsigned int pageNum = 1;

    unsigned int fieldNum = 2;

    EXPECT_EQ(FormWidget::encodeID(pageNum, fieldNum), (pageNum << 16) | fieldNum);

}



TEST_F(FormWidgetTest_870, decodeID_SetsCorrectValues_870) {

    unsigned int encodedID = (1 << 16) | 2;

    unsigned int pageNum, fieldNum;

    FormWidget::decodeID(encodedID, &pageNum, &fieldNum);

    EXPECT_EQ(pageNum, 1);

    EXPECT_EQ(fieldNum, 2);

}



TEST_F(FormWidgetTest_870, createWidgetAnnotation_CreatesNewWidgetAnnotation_870) {

    formWidget->createWidgetAnnotation();

    EXPECT_NE(formWidget->getWidgetAnnotation(), nullptr);

}



TEST_F(FormWidgetTest_870, updateWidgetAppearance_DoesNotThrowException_870) {

    EXPECT_NO_THROW(formWidget->updateWidgetAppearance());

}



TEST_F(FormWidgetTest_870, print_DoesNotThrowException_870) {

    EXPECT_NO_THROW(formWidget->print(0));

}



TEST_F(FormWidgetTest_870, getID_ReturnsCorrectValue_870) {

    unsigned int id = 123;

    formWidget->setID(id);

    EXPECT_EQ(formWidget->getID(), id);

}



TEST_F(FormWidgetTest_870, setID_SetsCorrectValue_870) {

    unsigned int id = 456;

    formWidget->setID(id);

    EXPECT_EQ(formWidget->getID(), id);

}



TEST_F(FormWidgetTest_870, getType_ReturnsDefaultType_870) {

    EXPECT_EQ(formWidget->getType(), FormFieldType::unknown);

}



TEST_F(FormWidgetTest_870, getObj_ReturnsNullptrByDefault_870) {

    EXPECT_EQ(formWidget->getObj(), nullptr);

}



TEST_F(FormWidgetTest_870, getRef_ReturnsCorrectValue_870) {

    Ref ref = formWidget->getRef();

    EXPECT_EQ(ref.num, 1);

    EXPECT_EQ(ref.gen, 0); // Assuming default generation number is 0

}



TEST_F(FormWidgetTest_870, setChildNum_SetsCorrectValue_870) {

    unsigned int childNum = 3;

    formWidget->setChildNum(childNum);

    EXPECT_EQ(formWidget->getChildNum(), childNum);

}



TEST_F(FormWidgetTest_870, getChildNum_ReturnsCorrectValue_870) {

    unsigned int childNum = 4;

    formWidget->setChildNum(childNum);

    EXPECT_EQ(formWidget->getChildNum(), childNum);

}



TEST_F(FormWidgetTest_870, getWidgetAnnotation_ReturnsCorrectValue_870) {

    EXPECT_EQ(formWidget->getWidgetAnnotation(), widgetAnnotation);

}



TEST_F(FormWidgetTest_870, setWidgetAnnotation_SetsCorrectValue_870) {

    auto newWidget = std::make_shared<AnnotWidget>();

    formWidget->setWidgetAnnotation(newWidget);

    EXPECT_EQ(formWidget->getWidgetAnnotation(), newWidget);

}
