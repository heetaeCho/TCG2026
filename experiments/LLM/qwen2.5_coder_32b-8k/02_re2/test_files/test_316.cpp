#include <gtest/gtest.h>

#include "re2/compile.cc"



namespace re2 {



class CompilerTest_316 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_316, AddRuneRangeUTF8_NormalRange_316) {

    // Test normal operation with a valid range

    compiler.AddRuneRangeUTF8(0x41, 0x5A, false);

}



TEST_F(CompilerTest_316, AddRuneRangeUTF8_FoldCase_316) {

    // Test normal operation with foldcase enabled

    compiler.AddRuneRangeUTF8(0x41, 0x5A, true);

}



TEST_F(CompilerTest_316, AddRuneRangeUTF8_EmptyRange_316) {

    // Test boundary condition with an empty range (lo > hi)

    compiler.AddRuneRangeUTF8(0x5A, 0x41, false);

}



TEST_F(CompilerTest_316, AddRuneRangeUTF8_FullUnicodeRange_316) {

    // Test boundary condition with the full Unicode range

    compiler.AddRuneRangeUTF8(0x80, 0x10FFFF, false);

}



TEST_F(CompilerTest_316, AddRuneRangeUTF8_SingleByteRange_316) {

    // Test normal operation with a single-byte range

    compiler.AddRuneRangeUTF8(0x20, 0x7F, false);

}



TEST_F(CompilerTest_316, AddRuneRangeUTF8_MultiByteRange_316) {

    // Test normal operation with a multi-byte range

    compiler.AddRuneRangeUTF8(0xC0, 0xFF, false);

}



}  // namespace re2
