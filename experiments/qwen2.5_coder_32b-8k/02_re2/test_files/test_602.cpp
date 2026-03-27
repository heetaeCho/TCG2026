#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ByteMapBuilderTest_602 : public ::testing::Test {

protected:

    ByteMapBuilder builder;

};



TEST_F(ByteMapBuilderTest_602, MarkIncreasesColormapSize_602) {

    int initial_size = builder.colormap_.size();

    builder.Mark(1, 10);

    EXPECT_GT(builder.colormap_.size(), initial_size);

}



TEST_F(ByteMapBuilderTest_602, MergeDoesNotCrash_602) {

    builder.Mark(1, 5);

    builder.Mark(6, 10);

    EXPECT_NO_THROW(builder.Merge());

}



TEST_F(ByteMapBuilderTest_602, BuildPopulatesBytemapAndRange_602) {

    uint8_t bytemap[256] = {0};

    int bytemap_range[2] = {0};

    builder.Mark(10, 20);

    builder.Build(bytemap, bytemap_range);

    for (int i = 10; i <= 20; ++i) {

        EXPECT_NE(bytemap[i], 0);

    }

    EXPECT_LE(bytemap_range[0], 10);

    EXPECT_GE(bytemap_range[1], 20);

}



TEST_F(ByteMapBuilderTest_602, MarkWithInvalidRangeDoesNotCrash_602) {

    EXPECT_NO_THROW(builder.Mark(300, 400)); // Out of bounds range

}



TEST_F(ByteMapBuilderTest_602, BuildWithNullPointersDoesNotCrash_602) {

    builder.Mark(1, 5);

    EXPECT_NO_THROW(builder.Build(nullptr, nullptr));

}
