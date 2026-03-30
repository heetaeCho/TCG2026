#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



// Mock class for AnnotBorderEffect if needed

class MockAnnotBorderEffect : public AnnotBorderEffect {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



TEST_F(AnnotPolygonTest_849, GetBorderEffect_ReturnsNonNullPointer_849) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotPolygon polygon(&doc, &rect, AnnotSubtype::annotSubtypeHighlight);



    EXPECT_NE(polygon.getBorderEffect(), nullptr);

}



TEST_F(AnnotPolygonTest_849, GetBorderEffect_ReturnsSamePointerOnConsecutiveCalls_849) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotPolygon polygon(&doc, &rect, AnnotSubtype::annotSubtypeHighlight);



    auto* effect1 = polygon.getBorderEffect();

    auto* effect2 = polygon.getBorderEffect();



    EXPECT_EQ(effect1, effect2);

}



TEST_F(AnnotPolygonTest_849, GetBorderEffect_ReturnsDifferentPointerForDifferentInstances_849) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotPolygon polygon1(&doc, &rect, AnnotSubtype::annotSubtypeHighlight);

    AnnotPolygon polygon2(&doc, &rect, AnnotSubtype::annotSubtypeHighlight);



    auto* effect1 = polygon1.getBorderEffect();

    auto* effect2 = polygon2.getBorderEffect();



    EXPECT_NE(effect1, effect2);

}
