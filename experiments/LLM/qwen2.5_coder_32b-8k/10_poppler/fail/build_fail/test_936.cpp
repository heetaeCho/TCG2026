#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Form.h"

#include <memory>

#include <vector>



using namespace testing;



class FormPageWidgetsTest : public Test {

protected:

    FormPageWidgets* formPageWidgets;

    

    virtual void SetUp() {

        // Assuming Annots, unsigned int page, and Form are mockable or can be default constructed

        formPageWidgets = new FormPageWidgets(nullptr, 0, nullptr);

    }

    

    virtual void TearDown() {

        delete formPageWidgets;

    }

};



TEST_F(FormPageWidgetsTest_936, InitialWidgetCountIsZero_936) {

    EXPECT_EQ(formPageWidgets->getNumWidgets(), 0);

}



TEST_F(FormPageWidgetsTest_936, AddUniquePtrWidgetsIncreasesCount_936) {

    std::vector<std::unique_ptr<FormField>> addedWidgets;

    addedWidgets.push_back(std::make_unique<FormField>());

    addedWidgets.push_back(std::make_unique<FormField>());

    

    formPageWidgets->addWidgets(addedWidgets, 0);

    EXPECT_EQ(formPageWidgets->getNumWidgets(), 2);

}



TEST_F(FormPageWidgetsTest_936, AddIntWidgetsIncreasesCount_936) {

    int addedWidgets = 3;

    

    formPageWidgets->addWidgets(addedWidgets, 0);

    EXPECT_EQ(formPageWidgets->getNumWidgets(), 3);

}



TEST_F(FormPageWidgetsTest_936, GetWidgetReturnsValidPointer_936) {

    std::vector<std::unique_ptr<FormField>> addedWidgets;

    addedWidgets.push_back(std::make_unique<FormField>());

    

    formPageWidgets->addWidgets(addedWidgets, 0);

    EXPECT_NE(formPageWidgets->getWidget(0), nullptr);

}



TEST_F(FormPageWidgetsTest_936, GetWidgetIndexOutOfBoundsReturnsNullptr_936) {

    EXPECT_EQ(formPageWidgets->getWidget(0), nullptr);

}



TEST_F(FormPageWidgetsTest_936, AddMultipleWidgetsAndCheckCount_936) {

    std::vector<std::unique_ptr<FormField>> addedWidgets1;

    addedWidgets1.push_back(std::make_unique<FormField>());

    formPageWidgets->addWidgets(addedWidgets1, 0);



    int addedWidgets2 = 2;

    formPageWidgets->addWidgets(addedWidgets2, 0);

    

    EXPECT_EQ(formPageWidgets->getNumWidgets(), 3);

}



TEST_F(FormPageWidgetsTest_936, AddZeroWidgetsDoesNotChangeCount_936) {

    std::vector<std::unique_ptr<FormField>> addedWidgets;

    formPageWidgets->addWidgets(addedWidgets, 0);



    int zeroAddedWidgets = 0;

    formPageWidgets->addWidgets(zeroAddedWidgets, 0);

    

    EXPECT_EQ(formPageWidgets->getNumWidgets(), 0);

}
