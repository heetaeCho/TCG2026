#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotFreeTextTest_821 : public ::testing::Test {

protected:

    PDFDoc* doc;

    std::unique_ptr<PDFRectangle> rect;



    void SetUp() override {

        // Initialize any necessary resources here

        doc = new PDFDoc();

        rect = std::make_unique<PDFRectangle>();

    }



    void TearDown() override {

        // Clean up resources if needed

        delete doc;

    }

};



TEST_F(AnnotFreeTextTest_821, GetBorderEffect_ReturnsNonNullPointer_821) {

    AnnotFreeText annot(doc, rect.get());

    EXPECT_NE(annot.getBorderEffect(), nullptr);

}



TEST_F(AnnotFreeTextTest_821, GetBorderEffect_ReturnsSamePointerOnMultipleCalls_821) {

    AnnotFreeText annot(doc, rect.get());

    auto effect1 = annot.getBorderEffect();

    auto effect2 = annot.getBorderEffect();

    EXPECT_EQ(effect1, effect2);

}



TEST_F(AnnotFreeTextTest_821, GetBorderEffect_BehaviorWithNullPointer_821) {

    // This test case assumes that passing a nullptr might be a boundary condition

    AnnotFreeText annot(doc, nullptr);

    EXPECT_NE(annot.getBorderEffect(), nullptr); // Assuming implementation can handle null and still provide valid effect pointer

}
