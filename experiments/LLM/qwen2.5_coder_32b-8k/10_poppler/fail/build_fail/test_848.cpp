#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Annot.h"



using namespace testing;



class AnnotPolygonTest_848 : public Test {

protected:

    PDFDoc* docA = nullptr;

    PDFRectangle* rect = nullptr;

    AnnotSubtype subType = annotSubtypeHighlight;

    std::unique_ptr<AnnotColor> interiorColor = std::make_unique<AnnotColor>(1.0, 0.0, 0.0); // Example color



    void SetUp() override {

        docA = new PDFDoc(); // Assuming PDFDoc has a default constructor

        rect = new PDFRectangle(0, 0, 100, 100);

    }



    void TearDown() override {

        delete docA;

        delete rect;

    }

};



TEST_F(AnnotPolygonTest_848, GetInteriorColor_ReturnsSetColor_848) {

    AnnotPolygon polygon(docA, rect, subType);

    polygon.setInteriorColor(std::move(interiorColor));

    EXPECT_EQ(polygon.getInteriorColor()->getRed(), 1.0f);

    EXPECT_EQ(polygon.getInteriorColor()->getGreen(), 0.0f);

    EXPECT_EQ(polygon.getInteriorColor()->getBlue(), 0.0f);

}



TEST_F(AnnotPolygonTest_848, GetInteriorColor_ReturnsNullptr_WhenNotSet_848) {

    AnnotPolygon polygon(docA, rect, subType);

    EXPECT_EQ(polygon.getInteriorColor(), nullptr);

}
