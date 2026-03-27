#include <gtest/gtest.h>

#include "CairoOutputDev.h"



class CairoOutputDevTest : public ::testing::Test {

protected:

    CairoOutputDev* cairo_output_dev;



    void SetUp() override {

        cairo_output_dev = new CairoOutputDev();

    }



    void TearDown() override {

        delete cairo_output_dev;

    }

};



TEST_F(CairoOutputDevTest_1735, GetType3GlyphBBox_ReturnsNonNullPointer_1735) {

    double* bbox = cairo_output_dev->getType3GlyphBBox();

    EXPECT_NE(bbox, nullptr);

}



TEST_F(CairoOutputDevTest_1735, GetType3GlyphBBox_ConsistentValuesAcrossCalls_1735) {

    double* bbox1 = cairo_output_dev->getType3GlyphBBox();

    double* bbox2 = cairo_output_dev->getType3GlyphBBox();

    EXPECT_EQ(bbox1, bbox2);

}



// Assuming boundary conditions and exceptional cases are not directly observable from the provided interface.

// If there are specific scenarios or states that should be tested, additional information would be needed.



TEST_F(CairoOutputDevTest_1735, GetType3GlyphBBox_UnmodifiedValuesAfterInitialization_1735) {

    double* bbox = cairo_output_dev->getType3GlyphBBox();

    EXPECT_DOUBLE_EQ(bbox[0], 0.0); // Assuming default value is (0,0,0,0)

    EXPECT_DOUBLE_EQ(bbox[1], 0.0);

    EXPECT_DOUBLE_EQ(bbox[2], 0.0);

    EXPECT_DOUBLE_EQ(bbox[3], 0.0);

}
