#include <gtest/gtest.h>

#include "re2/compile.cc"



namespace re2 {



class CompilerTest_304 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_304, UncachedRuneByteSuffix_NormalOperation_304) {

    int result = compiler.UncachedRuneByteSuffix('a', 'z', false, 1);

    EXPECT_GE(result, 0); // Assuming the return value is a valid instruction index

}



TEST_F(CompilerTest_304, UncachedRuneByteSuffix_BoundaryConditions_LoEqHi_304) {

    int result = compiler.UncachedRuneByteSuffix('a', 'a', false, 1);

    EXPECT_GE(result, 0); // Assuming the return value is a valid instruction index

}



TEST_F(CompilerTest_304, UncachedRuneByteSuffix_BoundaryConditions_LoHiWraparound_304) {

    int result = compiler.UncachedRuneByteSuffix(255, 0, false, 1);

    EXPECT_GE(result, 0); // Assuming the return value is a valid instruction index

}



TEST_F(CompilerTest_304, UncachedRuneByteSuffix_ExceptionalCase_NextZero_304) {

    int result = compiler.UncachedRuneByteSuffix('a', 'z', false, 0);

    EXPECT_GE(result, 0); // Assuming the return value is a valid instruction index

}



TEST_F(CompilerTest_304, UncachedRuneByteSuffix_ExceptionalCase_FoldcaseTrue_304) {

    int result = compiler.UncachedRuneByteSuffix('a', 'z', true, 1);

    EXPECT_GE(result, 0); // Assuming the return value is a valid instruction index

}



} // namespace re2
