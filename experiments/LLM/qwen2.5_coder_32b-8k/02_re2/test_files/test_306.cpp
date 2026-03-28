#include <gtest/gtest.h>

#include "re2/compile.h"



using namespace re2;



class CompilerTest_306 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_306, CachedRuneByteSuffix_CacheHit_306) {

    uint8_t lo = 0x41;

    uint8_t hi = 0x5A;

    bool foldcase = false;

    int next = 1;



    // Simulate a cache hit by calling the function twice with the same parameters

    compiler.CachedRuneByteSuffix(lo, hi, foldcase, next);

    EXPECT_EQ(compiler.CachedRuneByteSuffix(lo, hi, foldcase, next), compiler.CachedRuneByteSuffix(lo, hi, foldcase, next));

}



TEST_F(CompilerTest_306, CachedRuneByteSuffix_CacheMiss_306) {

    uint8_t lo = 0x41;

    uint8_t hi = 0x5A;

    bool foldcase = false;

    int next = 1;



    // Simulate a cache miss by calling with different parameters

    int result1 = compiler.CachedRuneByteSuffix(lo, hi, foldcase, next);

    int result2 = compiler.CachedRuneByteSuffix(lo + 1, hi, foldcase, next);



    EXPECT_NE(result1, result2);

}



TEST_F(CompilerTest_306, CachedRuneByteSuffix_BoundaryConditions_LowestValues_306) {

    uint8_t lo = 0x00;

    uint8_t hi = 0x01;

    bool foldcase = false;

    int next = 1;



    compiler.CachedRuneByteSuffix(lo, hi, foldcase, next);

}



TEST_F(CompilerTest_306, CachedRuneByteSuffix_BoundaryConditions_HighestValues_306) {

    uint8_t lo = 0xFE;

    uint8_t hi = 0xFF;

    bool foldcase = false;

    int next = 1;



    compiler.CachedRuneByteSuffix(lo, hi, foldcase, next);

}



TEST_F(CompilerTest_306, CachedRuneByteSuffix_BoundaryConditions_EqualRange_306) {

    uint8_t lo = 0x41;

    uint8_t hi = 0x41;

    bool foldcase = false;

    int next = 1;



    compiler.CachedRuneByteSuffix(lo, hi, foldcase, next);

}



TEST_F(CompilerTest_306, CachedRuneByteSuffix_BoundaryConditions_MaxNextValue_306) {

    uint8_t lo = 0x41;

    uint8_t hi = 0x5A;

    bool foldcase = false;

    int next = std::numeric_limits<int>::max();



    compiler.CachedRuneByteSuffix(lo, hi, foldcase, next);

}



TEST_F(CompilerTest_306, CachedRuneByteSuffix_FoldCaseTrue_306) {

    uint8_t lo = 0x41;

    uint8_t hi = 0x5A;

    bool foldcase = true;

    int next = 1;



    compiler.CachedRuneByteSuffix(lo, hi, foldcase, next);

}



TEST_F(CompilerTest_306, CachedRuneByteSuffix_FoldCaseFalse_306) {

    uint8_t lo = 0x41;

    uint8_t hi = 0x5A;

    bool foldcase = false;

    int next = 1;



    compiler.CachedRuneByteSuffix(lo, hi, foldcase, next);

}
