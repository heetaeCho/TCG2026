#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotGeometryTest_844 : public ::testing::Test {

protected:

    PDFRectangle* mockRect;

    std::unique_ptr<AnnotGeometry> annotGeom;



    void SetUp() override {

        mockRect = new PDFRectangle(); // Assuming PDFRectangle has a default constructor

        annotGeom = std::make_unique<AnnotGeometry>(nullptr, mockRect, AnnotSubtype::text);

    }



    void TearDown() override {

        delete mockRect;

    }

};



TEST_F(AnnotGeometryTest_844, GetGeometryRect_ReturnsCorrectPointer_844) {

    EXPECT_EQ(annotGeom->getGeometryRect(), mockRect);

}



TEST_F(AnnotGeometryTest_844, GetGeometryRect_ReturnsNullptrWhenInternalPtrIsReset_844) {

    annotGeom.reset();

    EXPECT_EQ(nullptr, annotGeom->getGeometryRect());

}

```


