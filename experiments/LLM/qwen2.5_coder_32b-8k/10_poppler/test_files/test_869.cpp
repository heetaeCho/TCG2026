#include <gtest/gtest.h>

#include "Form.h"



class FormWidgetTest_869 : public ::testing::Test {

protected:

    std::shared_ptr<FormWidget> formWidget;



    void SetUp() override {

        // Assuming a mock PDFDoc, Object, and FormField are available or can be created

        // For the sake of this example, we will assume they are provided in some way.

        formWidget = std::make_shared<FormWidget>(nullptr, nullptr, 0, Ref(), nullptr);

    }

};



TEST_F(FormWidgetTest_869, SetIDAndGetID_NormalOperation_869) {

    unsigned int testID = 123;

    formWidget->setID(testID);

    EXPECT_EQ(formWidget->getID(), testID);

}



TEST_F(FormWidgetTest_869, SetIDBoundaryCondition_Zero_869) {

    unsigned int testID = 0;

    formWidget->setID(testID);

    EXPECT_EQ(formWidget->getID(), testID);

}



TEST_F(FormWidgetTest_869, SetIDBoundaryCondition_MaxUnsignedInt_869) {

    unsigned int testID = UINT_MAX;

    formWidget->setID(testID);

    EXPECT_EQ(formWidget->getID(), testID);

}
