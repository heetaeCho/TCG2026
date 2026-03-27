#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ByteMapBuilderTest_408 : public ::testing::Test {

protected:

    ByteMapBuilder builder;

};



TEST_F(ByteMapBuilderTest_408, MarkNormalRange_408) {

    builder.Mark(10, 20);

    // No observable way to verify the internal state, but we can assume if no assertion fails, it works.

}



TEST_F(ByteMapBuilderTest_408, MarkFullRange_408) {

    builder.Mark(0, 255);

    // Since Mark does nothing for full range, no observable effect should be seen.

}



TEST_F(ByteMapBuilderTest_408, MarkBoundaryConditionLow_408) {

    builder.Mark(0, 0);

    // Similar to above, no internal state change is verifiable directly.

}



TEST_F(ByteMapBuilderTest_408, MarkBoundaryConditionHigh_408) {

    builder.Mark(255, 255);

    // Similar to above, no internal state change is verifiable directly.

}



TEST_F(ByteMapBuilderTest_408, MarkInvalidRangeLoNegative_408) {

    EXPECT_DEATH(builder.Mark(-1, 10), ".*lo.*");

}



TEST_F(ByteMapBuilderTest_408, MarkInvalidRangeHiNegative_408) {

    EXPECT_DEATH(builder.Mark(10, -1), ".*hi.*");

}



TEST_F(ByteMapBuilderTest_408, MarkInvalidRangeLoTooHigh_408) {

    EXPECT_DEATH(builder.Mark(256, 257), ".*lo.*");

}



TEST_F(ByteMapBuilderTest_408, MarkInvalidRangeHiTooHigh_408) {

    EXPECT_DEATH(builder.Mark(10, 256), ".*hi.*");

}



TEST_F(ByteMapBuilderTest_408, MarkInvalidRangeLoGreaterThanHi_408) {

    EXPECT_DEATH(builder.Mark(20, 10), ".*lo.*le.*hi.*");

}
