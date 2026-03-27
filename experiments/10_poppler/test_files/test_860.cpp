#include <gtest/gtest.h>

#include "poppler/Annot.h"

#include "poppler/AnnotAppearanceCharacs.h"



class AnnotWidgetTest_860 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object dictObject;

    const Object obj;

    FormField field;



    void SetUp() override {

        // Assuming PDFDoc, Object and FormField have appropriate default constructors

        doc = new PDFDoc();

        dictObject = Object();

        setField(&field);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(AnnotWidgetTest_860, SetAppearCharacs_ValidPointer_860) {

    auto appearCharacs = std::make_unique<AnnotAppearanceCharacs>();

    AnnotWidget annotWidget(doc, std::move(dictObject), &obj);

    EXPECT_NO_THROW(annotWidget.setAppearCharacs(std::move(appearCharacs)));

}



TEST_F(AnnotWidgetTest_860, SetAppearCharacs_NullPointer_860) {

    AnnotWidget annotWidget(doc, std::move(dictObject), &obj);

    EXPECT_NO_THROW(annotWidget.setAppearCharacs(nullptr));

}



TEST_F(AnnotWidgetTest_860, GetAppearCharacs_AfterSet_860) {

    auto appearCharacs = std::make_unique<AnnotAppearanceCharacs>();

    AnnotWidget annotWidget(doc, std::move(dictObject), &obj);

    annotWidget.setAppearCharacs(std::move(appearCharacs));

    EXPECT_NE(annotWidget.getAppearCharacs(), nullptr);

}



TEST_F(AnnotWidgetTest_860, GetAppearCharacs_AfterSetNull_860) {

    AnnotWidget annotWidget(doc, std::move(dictObject), &obj);

    annotWidget.setAppearCharacs(nullptr);

    EXPECT_EQ(annotWidget.getAppearCharacs(), nullptr);

}
