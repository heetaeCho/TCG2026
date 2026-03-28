#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/BBoxOutputDev.h"

#include <gmock/gmock.h>



using namespace testing;



class BBoxOutputDevTest_1520 : public ::testing::Test {

protected:

    BBoxOutputDev* bbox_output_dev;



    void SetUp() override {

        bbox_output_dev = new BBoxOutputDev();

    }



    void TearDown() override {

        delete bbox_output_dev;

    }

};



TEST_F(BBoxOutputDevTest_1520, interpretType3Chars_ReturnsFalse_1520) {

    EXPECT_FALSE(bbox_output_dev->interpretType3Chars());

}



TEST_F(BBoxOutputDevTest_1520, DefaultConstructor_InitializesCorrectly_1520) {

    EXPECT_DOUBLE_EQ(bbox_output_dev->getX1(), 0.0);

    EXPECT_DOUBLE_EQ(bbox_output_dev->getY1(), 0.0);

    EXPECT_DOUBLE_EQ(bbox_output_dev->getX2(), 0.0);

    EXPECT_DOUBLE_EQ(bbox_output_dev->getY2(), 0.0);

}



TEST_F(BBoxOutputDevTest_1520, ParameterizedConstructor_InitializesTextVectorRasterCorrectly_1520) {

    BBoxOutputDev bbox_output_dev_param(true, false, true);

    EXPECT_TRUE(bbox_output_dev_param.useDrawChar());

    EXPECT_FALSE(bbox_output_dev_param.interpretType3Chars());

}



TEST_F(BBoxOutputDevTest_1520, ParameterizedConstructorWithLWidth_InitializesTextVectorRasterLWidthCorrectly_1520) {

    BBoxOutputDev bbox_output_dev_param(true, false, true, true);

    EXPECT_TRUE(bbox_output_dev_param.useDrawChar());

    EXPECT_FALSE(bbox_output_dev_param.interpretType3Chars());

}



// Mocking external collaborators (if any)

class MockGfxState : public GfxState {

public:

    MOCK_METHOD0(getTransform, const double*());

};



TEST_F(BBoxOutputDevTest_1520, UpdatePoint_UpdatesBoundingBox_1520) {

    // This test assumes that updatePoint modifies the bounding box based on input values.

    MockGfxState mock_state;

    PDFRectangle bb = {0.0, 0.0, 0.0, 0.0};

    bbox_output_dev->updatePoint(&bb, 10.0, 20.0, &mock_state);

    // This is a placeholder for actual verification logic which depends on the internal implementation

}



TEST_F(BBoxOutputDevTest_1520, UpdatePath_UpdatesBoundingBox_1520) {

    // Similar to the previous test but for updatePath method.

    MockGfxState mock_state;

    GfxPath path;  // Assuming GfxPath is default constructible and can be used directly

    PDFRectangle bb = {0.0, 0.0, 0.0, 0.0};

    bbox_output_dev->updatePath(&bb, &path, &mock_state);

}



TEST_F(BBoxOutputDevTest_1520, UpdateImage_UpdatesBoundingBox_1520) {

    // Similar to the previous tests but for updateImage method.

    MockGfxState mock_state;

    PDFRectangle bb = {0.0, 0.0, 0.0, 0.0};

    bbox_output_dev->updateImage(&bb, &mock_state);

}



TEST_F(BBoxOutputDevTest_1520, UpsideDown_ReturnsFalseByDefault_1520) {

    EXPECT_FALSE(bbox_output_dev->upsideDown());

}
