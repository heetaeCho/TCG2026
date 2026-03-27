#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Form.h"

#include "AnnotWidget.h"



using namespace testing;



class FormWidgetTest_877 : public ::testing::Test {

protected:

    std::shared_ptr<AnnotWidget> mockWidget;

    FormWidget* formWidget;



    void SetUp() override {

        mockWidget = std::make_shared<NiceMock<AnnotWidget>>();

        formWidget = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr);

    }



    void TearDown() override {

        delete formWidget;

    }

};



TEST_F(FormWidgetTest_877, SetWidgetAnnotation_ValidWidget_877) {

    formWidget->setWidgetAnnotation(mockWidget);

    EXPECT_EQ(formWidget->getWidgetAnnotation(), mockWidget);

}



TEST_F(FormWidgetTest_877, GetWidgetAnnotation_ReturnsSetWidget_877) {

    formWidget->setWidgetAnnotation(mockWidget);

    EXPECT_EQ(formWidget->getWidgetAnnotation(), mockWidget);

}



TEST_F(FormWidgetTest_877, SetWidgetAnnotation_Nullptr_877) {

    formWidget->setWidgetAnnotation(nullptr);

    EXPECT_EQ(formWidget->getWidgetAnnotation(), nullptr);

}



TEST_F(FormWidgetTest_877, GetWidgetAnnotation_DefaultNullptr_877) {

    EXPECT_EQ(formWidget->getWidgetAnnotation(), nullptr);

}
