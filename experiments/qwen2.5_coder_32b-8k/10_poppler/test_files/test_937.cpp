#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Form.h"



using namespace testing;



class FormPageWidgetsTest : public Test {

protected:

    Annots* mockAnnots;

    unsigned int page = 0;

    Form* mockForm;



    void SetUp() override {

        mockAnnots = new Annots();

        mockForm = new Form();

    }



    void TearDown() override {

        delete mockAnnots;

        delete mockForm;

    }

};



TEST_F(FormPageWidgetsTest_937, GetNumWidgets_ReturnsZeroInitially_937) {

    FormPageWidgets formPageWidgets(mockAnnots, page, mockForm);

    EXPECT_EQ(formPageWidgets.getNumWidgets(), 0);

}



TEST_F(FormPageWidgetsTest_937, AddWidgets_IncreasesWidgetCount_937) {

    FormPageWidgets formPageWidgets(mockAnnots, page, mockForm);

    std::vector<std::unique_ptr<FormField>> addedWidgets(2); // Adding two widgets

    formPageWidgets.addWidgets(addedWidgets, page);

    EXPECT_EQ(formPageWidgets.getNumWidgets(), 2);

}



TEST_F(FormPageWidgetsTest_937, GetWidget_ReturnsCorrectWidget_937) {

    FormPageWidgets formPageWidgets(mockAnnots, page, mockForm);

    std::vector<std::unique_ptr<FormField>> addedWidgets(1); // Adding one widget

    formPageWidgets.addWidgets(addedWidgets, page);

    EXPECT_NE(formPageWidgets.getWidget(0), nullptr);

}



TEST_F(FormPageWidgetsTest_937, GetWidget_OutOfBounds_ReturnsNullptr_937) {

    FormPageWidgets formPageWidgets(mockAnnots, page, mockForm);

    std::vector<std::unique_ptr<FormField>> addedWidgets(1); // Adding one widget

    formPageWidgets.addWidgets(addedWidgets, page);

    EXPECT_EQ(formPageWidgets.getWidget(1), nullptr);

}



TEST_F(FormPageWidgetsTest_937, AddWidgets_WithNegativeCount_DoesNotAddWidgets_937) {

    FormPageWidgets formPageWidgets(mockAnnots, page, mockForm);

    int negativeCount = -1;

    formPageWidgets.addWidgets(negativeCount, page);

    EXPECT_EQ(formPageWidgets.getNumWidgets(), 0);

}



TEST_F(FormPageWidgetsTest_937, GetWidget_NegativeIndex_ReturnsNullptr_937) {

    FormPageWidgets formPageWidgets(mockAnnots, page, mockForm);

    std::vector<std::unique_ptr<FormField>> addedWidgets(1); // Adding one widget

    formPageWidgets.addWidgets(addedWidgets, page);

    EXPECT_EQ(formPageWidgets.getWidget(-1), nullptr);

}
