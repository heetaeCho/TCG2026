#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgInstTest : public ::testing::Test {

protected:

    Inst inst;

};



TEST_F(ProgInstTest_107, InitByteRange_SetsCorrectValues_107) {

    int lo = 1;

    int hi = 5;

    int foldcase = 3;

    uint32_t out = 10;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.lo(), lo);

    EXPECT_EQ(inst.hi(), hi);

    EXPECT_EQ(inst.foldcase(), foldcase);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_107, InitCapture_SetsCorrectValues_107) {

    int cap = 2;

    uint32_t out = 8;



    inst.InitCapture(cap, out);



    EXPECT_EQ(inst.cap(), cap);

    EXPECT_EQ(inst.out(), static_cast<int>(out));

}



TEST_F(ProgInstTest_107, InitMatch_SetsCorrectValues_107) {

    int id = 4;



    inst.InitMatch(id);



    EXPECT_EQ(inst.match_id(), id);

}



TEST_F(ProgInstTest_107, Hint_ReturnsCorrectValueForByteRange_107) {

    int lo = 1;

    int hi = 5;

    int foldcase = 6; // Binary: 110 -> hint_foldcase_: 2304 (110 << 1)

    uint32_t out = 10;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.hint(), foldcase >> 1);

}



TEST_F(ProgInstTest_107, Opcode_ReturnsCorrectValueAfterInitialization_107) {

    int lo = 1;

    int hi = 5;

    int foldcase = 3;

    uint32_t out = 10;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_EQ(inst.opcode(), kInstByteRange);

}



TEST_F(ProgInstTest_107, Matches_ReturnsTrueForInRangeValue_107) {

    int lo = 3;

    int hi = 7;

    int foldcase = 0; // No folding

    uint32_t out = 10;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_TRUE(inst.Matches(5));

}



TEST_F(ProgInstTest_107, Matches_ReturnsFalseForOutOfRangeValue_107) {

    int lo = 3;

    int hi = 7;

    int foldcase = 0; // No folding

    uint32_t out = 10;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_FALSE(inst.Matches(8));

}



TEST_F(ProgInstTest_107, Matches_ReturnsTrueForInRangeValueWithFoldCase_107) {

    int lo = 65; // 'A'

    int hi = 90; // 'Z'

    int foldcase = 3; // Binary: 11 -> hint_foldcase_: 224 (11 << 1)

    uint32_t out = 10;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_TRUE(inst.Matches(97)); // 'a', which is in range after folding

}



TEST_F(ProgInstTest_107, Matches_ReturnsFalseForOutOfRangeValueWithFoldCase_107) {

    int lo = 65; // 'A'

    int hi = 90; // 'Z'

    int foldcase = 3; // Binary: 11 -> hint_foldcase_: 224 (11 << 1)

    uint32_t out = 10;



    inst.InitByteRange(lo, hi, foldcase, out);



    EXPECT_FALSE(inst.Matches(98)); // 'b', which is out of range even after folding

}
