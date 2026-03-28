#include <gtest/gtest.h>

#include "Annot.h"



class AnnotTest_787 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    Annot* annot;



    void SetUp() override {

        doc = new PDFDoc();

        annot = new Annot(doc, &rect);

    }



    void TearDown() override {

        delete annot;

        delete doc;

    }

};



TEST_F(AnnotTest_787, GetModified_DefaultValueIsNull_787) {

    EXPECT_EQ(nullptr, annot->getModified());

}



TEST_F(AnnotTest_787, SetModifiedAndGetModified_NormalOperation_787) {

    auto modifiedStr = std::make_unique<GooString>("2023-10-05T14:48:00Z");

    annot->setModified(std::move(modifiedStr));

    EXPECT_EQ("2023-10-05T14:48:00Z", *(annot->getModified()));

}



TEST_F(AnnotTest_787, SetModifiedAndGetModified_BoundaryConditionEmptyString_787) {

    auto modifiedStr = std::make_unique<GooString>("");

    annot->setModified(std::move(modifiedStr));

    EXPECT_EQ("", *(annot->getModified()));

}



TEST_F(AnnotTest_787, SetModifiedAndGetModified_ErrorCaseNullPointer_787) {

    annot->setModified(nullptr);

    EXPECT_EQ(nullptr, annot->getModified());

}
