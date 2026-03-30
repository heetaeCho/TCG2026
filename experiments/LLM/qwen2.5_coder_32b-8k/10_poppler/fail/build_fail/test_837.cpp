#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotLineTest_837 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotCoord> coord1;

    std::unique_ptr<AnnotCoord> coord2;



    void SetUp() override {

        coord1 = std::make_unique<AnnotCoord>(1.0, 2.0);

        coord2 = std::make_unique<AnnotCoord>(3.0, 4.0);

    }



    AnnotLine createAnnotLine(double x1, double y1, double x2, double y2) {

        auto docA = new PDFDoc(); // Assuming PDFDoc is mockable or has a default constructor

        auto rect = new PDFRectangle(); // Assuming PDFRectangle is mockable or has a default constructor

        AnnotLine line(docA, rect);

        line.setVertices(x1, y1, x2, y2);

        return line;

    }

};



TEST_F(AnnotLineTest_837, GetY1_ReturnsCorrectValue_837) {

    AnnotLine line = createAnnotLine(1.0, 2.0, 3.0, 4.0);

    EXPECT_EQ(line.getY1(), 2.0);

}



TEST_F(AnnotLineTest_837, GetY2_ReturnsCorrectValue_837) {

    AnnotLine line = createAnnotLine(1.0, 2.0, 3.0, 4.0);

    EXPECT_EQ(line.getY2(), 4.0);

}



TEST_F(AnnotLineTest_837, SetVertices_UpdatesCoordinates_837) {

    AnnotLine line = createAnnotLine(1.0, 2.0, 3.0, 4.0);

    line.setVertices(5.0, 6.0, 7.0, 8.0);

    EXPECT_EQ(line.getY1(), 6.0);

    EXPECT_EQ(line.getY2(), 8.0);

}



TEST_F(AnnotLineTest_837, BoundaryCondition_SetVertices_ZeroValues_837) {

    AnnotLine line = createAnnotLine(1.0, 2.0, 3.0, 4.0);

    line.setVertices(0.0, 0.0, 0.0, 0.0);

    EXPECT_EQ(line.getY1(), 0.0);

    EXPECT_EQ(line.getY2(), 0.0);

}



TEST_F(AnnotLineTest_837, BoundaryCondition_SetVertices_NegativeValues_837) {

    AnnotLine line = createAnnotLine(1.0, 2.0, 3.0, 4.0);

    line.setVertices(-1.0, -2.0, -3.0, -4.0);

    EXPECT_EQ(line.getY1(), -2.0);

    EXPECT_EQ(line.getY2(), -4.0);

}
