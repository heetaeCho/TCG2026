#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



using namespace testing;



TEST(GfxTilingPatternTest_499, GetContentStream_ReturnsNonNullPointer_499) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    Object resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 10.0, 10.0, &resDict, matrix, &contentStream, 42);



    EXPECT_NE(pattern.getContentStream(), nullptr);

}



TEST(GfxTilingPatternTest_499, GetContentStream_ReturnsSamePointerAsProvided_499) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    Object resDict;

    Object contentStream;



    auto pattern = GfxTilingPattern(1, 2, bbox, 10.0, 10.0, &resDict, matrix, &contentStream, 42);



    EXPECT_EQ(pattern.getContentStream(), &contentStream);

}
