#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotGeometryTest_843 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> doc;

    std::unique_ptr<PDFRectangle> rect;

    std::unique_ptr<AnnotGeometry> annotGeometry;



    void SetUp() override {

        doc = std::make_unique<PDFDoc>();

        rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);

        annotGeometry = std::make_unique<AnnotGeometry>(doc.get(), rect.release(), AnnotSubtype::Square);

    }

};



TEST_F(AnnotGeometryTest_843, GetBorderEffect_ReturnsValidPointer_843) {

    ASSERT_NE(annotGeometry->getBorderEffect(), nullptr);

}



TEST_F(AnnotGeometryTest_843, GetBorderEffect_ConsistentAcrossCalls_843) {

    AnnotBorderEffect* firstCall = annotGeometry->getBorderEffect();

    AnnotBorderEffect* secondCall = annotGeometry->getBorderEffect();

    EXPECT_EQ(firstCall, secondCall);

}



TEST_F(AnnotGeometryTest_843, GetInteriorColor_ReturnsNullptrByDefault_843) {

    EXPECT_EQ(annotGeometry->getInteriorColor(), nullptr);

}
