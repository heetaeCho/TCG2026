#include <gtest/gtest.h>

#include "Form.h"



class FormWidgetTest_874 : public ::testing::Test {

protected:

    std::shared_ptr<AnnotWidget> mock_widget;

    PDFDoc* mock_doc;

    Object* mock_obj;

    Ref mock_ref;

    FormField* mock_field;



    void SetUp() override {

        mock_widget = std::make_shared<AnnotWidget>();

        mock_doc = nullptr; // Assuming PDFDoc is an abstract class or interface, we cannot instantiate it directly.

        mock_obj = nullptr; // Assuming Object is an abstract class or interface, we cannot instantiate it directly.

        mock_ref = Ref();   // Default constructor for Ref, assuming it's a simple struct-like class.

        mock_field = nullptr; // Assuming FormField is an abstract class or interface, we cannot instantiate it directly.

    }



    FormWidget* createFormWidget() {

        return new FormWidget(mock_doc, mock_obj, 0, mock_ref, mock_field);

    }

};



TEST_F(FormWidgetTest_874, SetChildNumAndGetChildNum_NormalOperation_874) {

    auto formWidget = createFormWidget();

    unsigned int testValue = 5;

    formWidget->setChildNum(testValue);

    EXPECT_EQ(formWidget->getChildNum(), testValue);

}



TEST_F(FormWidgetTest_874, SetChildNumAndGetChildNum_BoundaryCondition_874) {

    auto formWidget = createFormWidget();

    unsigned int maxUnsignedInt = std::numeric_limits<unsigned int>::max();

    formWidget->setChildNum(maxUnsignedInt);

    EXPECT_EQ(formWidget->getChildNum(), maxUnsignedInt);

}



TEST_F(FormWidgetTest_874, GetID_DefaultValue_874) {

    auto formWidget = createFormWidget();

    unsigned int defaultID = 0; // Assuming the default value for ID is 0

    EXPECT_EQ(formWidget->getID(), defaultID);

}



TEST_F(FormWidgetTest_874, SetIDAndGetID_NormalOperation_874) {

    auto formWidget = createFormWidget();

    unsigned int testValue = 123;

    formWidget->setID(testValue);

    EXPECT_EQ(formWidget->getID(), testValue);

}



TEST_F(FormWidgetTest_874, SetIDAndGetID_BoundaryCondition_874) {

    auto formWidget = createFormWidget();

    unsigned int maxUnsignedInt = std::numeric_limits<unsigned int>::max();

    formWidget->setID(maxUnsignedInt);

    EXPECT_EQ(formWidget->getID(), maxUnsignedInt);

}



TEST_F(FormWidgetTest_874, GetWidgetAnnotation_DefaultValue_874) {

    auto formWidget = createFormWidget();

    EXPECT_TRUE(!formWidget->getWidgetAnnotation());

}



TEST_F(FormWidgetTest_874, SetAndGetWidgetAnnotation_NormalOperation_874) {

    auto formWidget = createFormWidget();

    std::shared_ptr<AnnotWidget> testWidget = std::make_shared<AnnotWidget>();

    formWidget->setWidgetAnnotation(testWidget);

    EXPECT_EQ(formWidget->getWidgetAnnotation(), testWidget);

}
