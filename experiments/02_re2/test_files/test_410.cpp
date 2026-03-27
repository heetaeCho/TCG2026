#include <gtest/gtest.h>

#include "re2/prog.h"

#include "re2/bitmap256.h"



using namespace re2;



class ByteMapBuilderTest_410 : public ::testing::Test {

protected:

    ByteMapBuilder builder_;

};



TEST_F(ByteMapBuilderTest_410, BuildInitializesBytemapAndRange_410) {

    uint8_t bytemap[256] = {0};

    int bytemap_range = 0;

    

    builder_.Build(bytemap, &bytemap_range);

    

    EXPECT_EQ(bytemap_range, 0);

    for (int i = 0; i < 256; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

}



TEST_F(ByteMapBuilderTest_410, BuildWithSingleMarkedRange_410) {

    uint8_t bytemap[256] = {0};

    int bytemap_range = 0;

    

    builder_.Mark(10, 20);

    builder_.Build(bytemap, &bytemap_range);

    

    EXPECT_EQ(bytemap_range, 1);

    for (int i = 0; i < 10; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

    for (int i = 10; i <= 20; ++i) {

        EXPECT_EQ(bytemap[i], 1);

    }

    for (int i = 21; i < 256; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

}



TEST_F(ByteMapBuilderTest_410, BuildWithMultipleMarkedRanges_410) {

    uint8_t bytemap[256] = {0};

    int bytemap_range = 0;

    

    builder_.Mark(10, 20);

    builder_.Mark(30, 40);

    builder_.Build(bytemap, &bytemap_range);

    

    EXPECT_EQ(bytemap_range, 2);

    for (int i = 0; i < 10; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

    for (int i = 10; i <= 20; ++i) {

        EXPECT_EQ(bytemap[i], 1);

    }

    for (int i = 21; i < 30; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

    for (int i = 30; i <= 40; ++i) {

        EXPECT_EQ(bytemap[i], 2);

    }

    for (int i = 41; i < 256; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

}



TEST_F(ByteMapBuilderTest_410, BuildWithOverlappingMarkedRanges_410) {

    uint8_t bytemap[256] = {0};

    int bytemap_range = 0;

    

    builder_.Mark(10, 20);

    builder_.Mark(15, 30);

    builder_.Build(bytemap, &bytemap_range);

    

    EXPECT_EQ(bytemap_range, 1);

    for (int i = 0; i < 10; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

    for (int i = 10; i <= 30; ++i) {

        EXPECT_EQ(bytemap[i], 1);

    }

    for (int i = 31; i < 256; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

}



TEST_F(ByteMapBuilderTest_410, BuildWithFullRangeMarked_410) {

    uint8_t bytemap[256] = {0};

    int bytemap_range = 0;

    

    builder_.Mark(0, 255);

    builder_.Build(bytemap, &bytemap_range);

    

    EXPECT_EQ(bytemap_range, 1);

    for (int i = 0; i < 256; ++i) {

        EXPECT_EQ(bytemap[i], 1);

    }

}



TEST_F(ByteMapBuilderTest_410, BuildWithNoMarks_410) {

    uint8_t bytemap[256] = {1};

    int bytemap_range = 1;

    

    builder_.Build(bytemap, &bytemap_range);

    

    EXPECT_EQ(bytemap_range, 0);

    for (int i = 0; i < 256; ++i) {

        EXPECT_EQ(bytemap[i], 0);

    }

}
