#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"



using namespace re2;



class InstTest : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(InstTest_391, InitByteRange_SetsCorrectValues_391) {

    int lo = 48; // '0'

    int hi = 57; // '9'

    int foldcase = 0;

    uint32_t out = 1;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.lo(), lo & 0xFF);

    EXPECT_EQ(inst.hi(), hi & 0xFF);

    EXPECT_EQ(inst.foldcase(), foldcase & 1);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(InstTest_391, InitByteRange_BoundaryValues_391) {

    int lo = 0;

    int hi = 255;

    int foldcase = 1;

    uint32_t out = 2;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.lo(), lo & 0xFF);

    EXPECT_EQ(inst.hi(), hi & 0xFF);

    EXPECT_EQ(inst.foldcase(), foldcase & 1);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(InstTest_391, InitByteRange_OutOfBoundsValues_391) {

    int lo = -1;

    int hi = 256;

    int foldcase = 2; // Invalid value, but will be masked to 0

    uint32_t out = 3;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.lo(), (lo & 0xFF));

    EXPECT_EQ(inst.hi(), (hi & 0xFF));

    EXPECT_EQ(inst.foldcase(), foldcase & 1);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(InstTest_391, InitByteRange_FoldCaseMasking_391) {

    int lo = 65; // 'A'

    int hi = 90; // 'Z'

    int foldcase = 1;

    uint32_t out = 4;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.lo(), lo & 0xFF);

    EXPECT_EQ(inst.hi(), hi & 0xFF);

    EXPECT_EQ(inst.foldcase(), foldcase & 1); // Should be 1

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}
