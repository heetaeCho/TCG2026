#include <gtest/gtest.h>

#include "re2/compile.cc"

#include "re2/util/utf.h"



namespace re2 {



class CompilerTest_320 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_320, LiteralDefaultEncoding_320) {

    Rune r = 'a';

    bool foldcase = false;

    Frag result = compiler.Literal(r, foldcase);

    EXPECT_EQ(result.nullable, true);  // Assuming an empty fragment is nullable

}



TEST_F(CompilerTest_320, LiteralLatin1Encoding_320) {

    compiler.encoding_ = kEncodingLatin1;

    Rune r = 'a';

    bool foldcase = false;

    Frag result = compiler.Literal(r, foldcase);

    EXPECT_EQ(result.nullable, false);  // Assuming ByteRange creates a non-empty fragment

}



TEST_F(CompilerTest_320, LiteralUTF8SingleByte_320) {

    compiler.encoding_ = kEncodingUTF8;

    Rune r = 'a';

    bool foldcase = false;

    Frag result = compiler.Literal(r, foldcase);

    EXPECT_EQ(result.nullable, false);  // Assuming ByteRange creates a non-empty fragment

}



TEST_F(CompilerTest_320, LiteralUTF8MultiByte_320) {

    compiler.encoding_ = kEncodingUTF8;

    Rune r = 0x263A;  // Unicode character for smiley face

    bool foldcase = false;

    Frag result = compiler.Literal(r, foldcase);

    EXPECT_EQ(result.nullable, false);  // Assuming ByteRange creates a non-empty fragment

}



TEST_F(CompilerTest_320, LiteralUTF8BoundaryCondition_320) {

    compiler.encoding_ = kEncodingUTF8;

    Rune r = Runeself - 1;  // Boundary condition for single byte UTF-8

    bool foldcase = false;

    Frag result = compiler.Literal(r, foldcase);

    EXPECT_EQ(result.nullable, false);  // Assuming ByteRange creates a non-empty fragment

}



TEST_F(CompilerTest_320, LiteralUTF8MaxValue_320) {

    compiler.encoding_ = kEncodingUTF8;

    Rune r = Runemax;  // Maximum valid Unicode value

    bool foldcase = false;

    Frag result = compiler.Literal(r, foldcase);

    EXPECT_EQ(result.nullable, false);  // Assuming ByteRange creates a non-empty fragment

}



TEST_F(CompilerTest_320, LiteralUTF8InvalidValue_320) {

    compiler.encoding_ = kEncodingUTF8;

    Rune r = Runemax + 1;  // Invalid Unicode value

    bool foldcase = false;

    Frag result = compiler.Literal(r, foldcase);

    EXPECT_EQ(result.nullable, true);  // Assuming an invalid rune results in an empty fragment

}



}  // namespace re2
