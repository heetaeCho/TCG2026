#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



// Mock class for Object if needed

class MockObject : public Object {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



TEST_F(GfxTilingPatternTest_493, GetTilingType_ReturnsExpectedValue_493) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    MockObject resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 1.0, 1.0, &resDict, matrix, &contentStream, 1);



    EXPECT_EQ(pattern.getTilingType(), 2);

}



TEST_F(GfxTilingPatternTest_493, GetPaintType_ReturnsExpectedValue_493) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    MockObject resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 1.0, 1.0, &resDict, matrix, &contentStream, 1);



    EXPECT_EQ(pattern.getPaintType(), 1);

}



TEST_F(GfxTilingPatternTest_493, GetBBox_ReturnsExpectedValue_493) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    MockObject resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 1.0, 1.0, &resDict, matrix, &contentStream, 1);



    EXPECT_EQ(pattern.getBBox(), bbox);

}



TEST_F(GfxTilingPatternTest_493, GetXStep_ReturnsExpectedValue_493) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    MockObject resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 10.5, 1.0, &resDict, matrix, &contentStream, 1);



    EXPECT_EQ(pattern.getXStep(), 10.5);

}



TEST_F(GfxTilingPatternTest_493, GetYStep_ReturnsExpectedValue_493) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    MockObject resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 1.0, 20.5, &resDict, matrix, &contentStream, 1);



    EXPECT_EQ(pattern.getYStep(), 20.5);

}



TEST_F(GfxTilingPatternTest_493, GetResDict_ReturnsExpectedPointer_493) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    MockObject resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 1.0, 1.0, &resDict, matrix, &contentStream, 1);



    EXPECT_EQ(pattern.getResDict(), &resDict);

}



TEST_F(GfxTilingPatternTest_493, GetMatrix_ReturnsExpectedValue_493) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    MockObject resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 1.0, 1.0, &resDict, matrix, &contentStream, 1);



    EXPECT_EQ(pattern.getMatrix(), matrix);

}



TEST_F(GfxTilingPatternTest_493, GetContentStream_ReturnsExpectedPointer_493) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    MockObject resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 1.0, 1.0, &resDict, matrix, &contentStream, 1);



    EXPECT_EQ(pattern.getContentStream(), &contentStream);

}
