#include <gtest/gtest.h>

#include "poppler/Annot.h"

#include <memory>



using namespace poppler;



class AnnotFreeTextTest_822 : public ::testing::Test {

protected:

    std::unique_ptr<PDFRectangle> rect;

    std::unique_ptr<AnnotFreeText> annot;



    void SetUp() override {

        rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);

        annot = std::make_unique<AnnotFreeText>(nullptr, rect.get());

    }

};



TEST_F(AnnotFreeTextTest_822, GetRectangle_ReturnsCorrectPointer_822) {

    EXPECT_EQ(rect.get(), annot->getRectangle());

}



TEST_F(AnnotFreeTextTest_822, GetRectangle_NotNullAfterConstruction_822) {

    EXPECT_NE(nullptr, annot->getRectangle());

}
