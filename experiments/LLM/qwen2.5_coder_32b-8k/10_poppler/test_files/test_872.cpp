#include <gtest/gtest.h>

#include "Form.h"



class FormWidgetTest_872 : public ::testing::Test {

protected:

    PDFDoc* docA;

    Object aobj;

    unsigned int num;

    Ref aref;

    FormField fieldA;



    std::unique_ptr<FormWidget> formWidget;



    void SetUp() override {

        docA = new PDFDoc();

        num = 1;

        aref.num = 1;

        aref.gen = 0;

        formWidget.reset(new FormWidget(docA, &aobj, num, aref, &fieldA));

    }



    void TearDown() override {

        delete docA;

    }

};



TEST_F(FormWidgetTest_872, GetObjReturnsValidObject_872) {

    Object* obj = formWidget->getObj();

    EXPECT_EQ(obj, &aobj);

}



TEST_F(FormWidgetTest_872, InRectFalseWhenOutside_872) {

    EXPECT_FALSE(formWidget->inRect(-10, -10));

}



TEST_F(FormWidgetTest_872, GetRectSetsCoordinates_872) {

    double x1, y1, x2, y2;

    formWidget->getRect(&x1, &y1, &x2, &y2);

    // Assuming default coordinates are (0, 0, 0, 0) for a new FormWidget

    EXPECT_EQ(x1, 0);

    EXPECT_EQ(y1, 0);

    EXPECT_EQ(x2, 0);

    EXPECT_EQ(y2, 0);

}



TEST_F(FormWidgetTest_872, GetPartialNameReturnsDefault_872) {

    const GooString* partialName = formWidget->getPartialName();

    // Assuming default partial name is empty

    EXPECT_TRUE(partialName->isEmpty());

}



TEST_F(FormWidgetTest_872, SetAndGetPartialName_872) {

    GooString name("NewPartialName");

    formWidget->setPartialName(name);

    const GooString* returnedName = formWidget->getPartialName();

    EXPECT_EQ(*returnedName, *name.c_str());

}



TEST_F(FormWidgetTest_872, GetAlternateUiNameReturnsDefault_872) {

    const GooString* alternateName = formWidget->getAlternateUiName();

    // Assuming default alternate UI name is empty

    EXPECT_TRUE(alternateName->isEmpty());

}



TEST_F(FormWidgetTest_872, GetMappingNameReturnsDefault_872) {

    const GooString* mappingName = formWidget->getMappingName();

    // Assuming default mapping name is empty

    EXPECT_TRUE(mappingName->isEmpty());

}



TEST_F(FormWidgetTest_872, GetFullyQualifiedNameReturnsDefault_872) {

    const GooString* fullyQualifiedName = formWidget->getFullyQualifiedName();

    // Assuming default fully qualified name is empty

    EXPECT_TRUE(fullyQualifiedName->isEmpty());

}



TEST_F(FormWidgetTest_872, IsModifiedInitiallyFalse_872) {

    EXPECT_FALSE(formWidget->isModified());

}



TEST_F(FormWidgetTest_872, IsReadOnlyInitiallyFalse_872) {

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_872, SetAndGetReadOnly_872) {

    formWidget->setReadOnly(true);

    EXPECT_TRUE(formWidget->isReadOnly());



    formWidget->setReadOnly(false);

    EXPECT_FALSE(formWidget->isReadOnly());

}



TEST_F(FormWidgetTest_872, GetActivationActionInitiallyNull_872) {

    LinkAction* action = formWidget->getActivationAction();

    EXPECT_EQ(action, nullptr);

}



TEST_F(FormWidgetTest_872, GetAdditionalActionInitiallyNull_872) {

    std::unique_ptr<LinkAction> action = formWidget->getAdditionalAction(Annot::FormAdditionalActionsType::FieldFormatting);

    EXPECT_EQ(action.get(), nullptr);

}



TEST_F(FormWidgetTest_872, SetAdditionalActionReturnsTrue_872) {

    bool result = formWidget->setAdditionalAction(Annot::FormAdditionalActionsType::FieldFormatting, "javascript:;");

    EXPECT_TRUE(result);

}



TEST_F(FormWidgetTest_872, EncodeIDAndDecodeIDConsistency_872) {

    unsigned int pageNum = 1;

    unsigned int fieldNum = 42;

    unsigned int encodedID = FormWidget::encodeID(pageNum, fieldNum);

    unsigned int decodedPageNum, decodedFieldNum;

    FormWidget::decodeID(encodedID, &decodedPageNum, &decodedFieldNum);

    EXPECT_EQ(decodedPageNum, pageNum);

    EXPECT_EQ(decodedFieldNum, fieldNum);

}



TEST_F(FormWidgetTest_872, CreateWidgetAnnotationDoesNotThrow_872) {

    EXPECT_NO_THROW(formWidget->createWidgetAnnotation());

}



TEST_F(FormWidgetTest_872, UpdateWidgetAppearanceDoesNotThrow_872) {

    EXPECT_NO_THROW(formWidget->updateWidgetAppearance());

}



TEST_F(FormWidgetTest_872, PrintDoesNotThrow_872) {

    EXPECT_NO_THROW(formWidget->print(0));

}



TEST_F(FormWidgetTest_872, GetIDInitiallyZero_872) {

    EXPECT_EQ(formWidget->getID(), 0);

}



TEST_F(FormWidgetTest_872, SetAndGetID_872) {

    unsigned int newID = 100;

    formWidget->setID(newID);

    EXPECT_EQ(formWidget->getID(), newID);

}



TEST_F(FormWidgetTest_872, GetFieldReturnsDefault_872) {

    FormField* field = formWidget->getField();

    EXPECT_EQ(field, &fieldA);

}



TEST_F(FormWidgetTest_872, GetTypeInitiallyUnknown_872) {

    EXPECT_EQ(formWidget->getType(), FormFieldType::unknown);

}



TEST_F(FormWidgetTest_872, GetRefReturnsDefault_872) {

    Ref ref = formWidget->getRef();

    EXPECT_EQ(ref.num, aref.num);

    EXPECT_EQ(ref.gen, aref.gen);

}



TEST_F(FormWidgetTest_872, SetAndGetChildNum_872) {

    unsigned int newChildNum = 5;

    formWidget->setChildNum(newChildNum);

    EXPECT_EQ(formWidget->getChildNum(), newChildNum);

}



TEST_F(FormWidgetTest_872, GetWidgetAnnotationInitiallyNull_872) {

    std::shared_ptr<AnnotWidget> widget = formWidget->getWidgetAnnotation();

    EXPECT_EQ(widget, nullptr);

}



TEST_F(FormWidgetTest_872, SetAndGetWidgetAnnotation_872) {

    auto newWidget = std::make_shared<AnnotWidget>();

    formWidget->setWidgetAnnotation(newWidget);

    std::shared_ptr<AnnotWidget> returnedWidget = formWidget->getWidgetAnnotation();

    EXPECT_EQ(returnedWidget, newWidget);

}
