#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"



using namespace std;



class AnnotWidgetTest_859 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dictObject;

    Object obj;

    FormField* field;

    AnnotWidget* annotWidget;



    void SetUp() override {

        doc = new PDFDoc();

        field = new FormField(doc, &dictObject);

        annotWidget = new AnnotWidget(doc, move(dictObject), &obj, field);

    }



    void TearDown() override {

        delete annotWidget;

        delete field;

        delete doc;

    }

};



TEST_F(AnnotWidgetTest_859, GetAppearCharacs_ReturnsNonNullPointer_859) {

    EXPECT_NE(nullptr, annotWidget->getAppearCharacs());

}



TEST_F(AnnotWidgetTest_859, SetAndGetAppearCharacs_CorrectlySetsAndReturnsPointer_859) {

    auto newAppearCharacs = make_unique<AnnotAppearanceCharacs>();

    AnnotAppearanceCharacs* expectedPointer = newAppearCharacs.get();

    annotWidget->setAppearCharacs(move(newAppearCharacs));

    EXPECT_EQ(expectedPointer, annotWidget->getAppearCharacs());

}



TEST_F(AnnotWidgetTest_859, SetAppearCharacs_LeavesOriginalUnmodified_859) {

    auto originalAppearCharacs = annotWidget->getAppearCharacs();

    auto newAppearCharacs = make_unique<AnnotAppearanceCharacs>();

    annotWidget->setAppearCharacs(move(newAppearCharacs));

    EXPECT_NE(originalAppearCharacs, annotWidget->getAppearCharacs());

}
