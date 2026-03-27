#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Form.h"



using namespace testing;



class FormWidgetTest_876 : public ::testing::Test {

protected:

    FormWidgetTest_876() 

        : doc(nullptr), aobj(nullptr), field(nullptr),

          formWidget(new FormWidget(doc, aobj, 1, Ref(), field)) {}



    ~FormWidgetTest_876() override = default;



    PDFDoc* doc;

    Object* aobj;

    FormField* field;

    std::shared_ptr<FormWidget> formWidget;

};



TEST_F(FormWidgetTest_876, GetWidgetAnnotation_ReturnsNullptr_876) {

    EXPECT_EQ(formWidget->getWidgetAnnotation(), nullptr);

}



TEST_F(FormWidgetTest_876, SetAndGetWidgetAnnotation_ConsistentBehavior_876) {

    auto mockWidget = std::make_shared<AnnotWidget>();

    formWidget->setWidgetAnnotation(mockWidget);

    EXPECT_EQ(formWidget->getWidgetAnnotation(), mockWidget);

}



TEST_F(FormWidgetTest_876, InRect_ReturnsFalseForInvalidCoordinates_876) {

    EXPECT_FALSE(formWidget->inRect(-100, -100));

}



TEST_F(FormWidgetTest_876, GetRect_SetsValuesToZeroByDefault_876) {

    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;

    formWidget->getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 0.0);

    EXPECT_DOUBLE_EQ(y1, 0.0);

    EXPECT_DOUBLE_EQ(x2, 0.0);

    EXPECT_DOUBLE_EQ(y2, 0.0);

}



TEST_F(FormWidgetTest_876, GetPartialName_ReturnsNullptrByDefault_876) {

    EXPECT_EQ(formWidget->getPartialName(), nullptr);

}



TEST_F(FormWidgetTest_876, SetAndGetPartialName_ConsistentBehavior_876) {

    GooString expected("testName");

    formWidget->setPartialName(expected);

    const GooString* actual = formWidget->getPartialName();

    EXPECT_STREQ(actual->getCString(), "testName");

}



TEST_F(FormWidgetTest_876, GetAlternateUiName_ReturnsNullptrByDefault_876) {

    EXPECT_EQ(formWidget->getAlternateUiName(), nullptr);

}



TEST_F(FormWidgetTest_876, GetMappingName_ReturnsNullptrByDefault_876) {

    EXPECT_EQ(formWidget->getMappingName(), nullptr);

}



TEST_F(FormWidgetTest_876, GetFullyQualifiedName_ReturnsNullptrByDefault_876) {

    EXPECT_EQ(formWidget->getFullyQualifiedName(), nullptr);

}



TEST_F(FormWidgetTest_876, IsModified_ReturnsFalseByDefault_876) {

    EXPECT_FALSE(formWidget->isModified());

}



TEST_F(FormWidgetTest_876, IsReadOnly_ReturnsFalseByDefault_876) {

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_876, SetAndGetReadOnly_ConsistentBehavior_876) {

    formWidget->setReadOnly(true);

    EXPECT_TRUE(formWidget->isReadOnly());

    formWidget->setReadOnly(false);

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_876, GetActivationAction_ReturnsNullptrByDefault_876) {

    EXPECT_EQ(formWidget->getActivationAction(), nullptr);

}



TEST_F(FormWidgetTest_876, GetAdditionalAction_ReturnsNullptrForInvalidType_876) {

    EXPECT_EQ(formWidget->getAdditionalAction(Annot::FormAdditionalActionsType::Unknown), nullptr);

}



TEST_F(FormWidgetTest_876, SetAndGetAdditionalAction_ConsistentBehavior_876) {

    const std::string js = "function() { return true; }";

    bool result = formWidget->setAdditionalAction(Annot::FormAdditionalActionsType::Format, js);

    EXPECT_TRUE(result);



    auto action = formWidget->getAdditionalAction(Annot::FormAdditionalActionsType::Format);

    EXPECT_NE(action.get(), nullptr);

}



TEST_F(FormWidgetTest_876, EncodeID_ReturnsCorrectValue_876) {

    unsigned int pageNum = 10;

    unsigned int fieldNum = 20;

    unsigned int expectedID = (pageNum << 16) | fieldNum;

    EXPECT_EQ(FormWidget::encodeID(pageNum, fieldNum), expectedID);

}



TEST_F(FormWidgetTest_876, DecodeID_ProducesOriginalValues_876) {

    unsigned int expectedPageNum = 10;

    unsigned int expectedFieldNum = 20;

    unsigned int id = FormWidget::encodeID(expectedPageNum, expectedFieldNum);



    unsigned int pageNum = 0, fieldNum = 0;

    FormWidget::decodeID(id, &pageNum, &fieldNum);

    EXPECT_EQ(pageNum, expectedPageNum);

    EXPECT_EQ(fieldNum, expectedFieldNum);

}



TEST_F(FormWidgetTest_876, CreateWidgetAnnotation_DoesNotThrowException_876) {

    EXPECT_NO_THROW(formWidget->createWidgetAnnotation());

}



TEST_F(FormWidgetTest_876, UpdateWidgetAppearance_DoesNotThrowException_876) {

    EXPECT_NO_THROW(formWidget->updateWidgetAppearance());

}



TEST_F(FormWidgetTest_876, Print_DoesNotThrowException_876) {

    EXPECT_NO_THROW(formWidget->print(0));

}
