#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_242 : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2OptionsTest_242, DefaultConstructorFlags_242) {

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl);

}



TEST_F(RE2OptionsTest_242, EncodingUTF8_242) {

    options.set_encoding(RE2::Options::EncodingUTF8);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl);

}



TEST_F(RE2OptionsTest_242, EncodingLatin1_242) {

    options.set_encoding(RE2::Options::EncodingLatin1);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl | Regexp::Latin1);

}



TEST_F(RE2OptionsTest_242, PosixSyntaxTrue_242) {

    options.set_posix_syntax(true);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL);

}



TEST_F(RE2OptionsTest_242, LiteralTrue_242) {

    options.set_literal(true);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl | Regexp::Literal);

}



TEST_F(RE2OptionsTest_242, NeverNLTrue_242) {

    options.set_never_nl(true);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl | Regexp::NeverNL);

}



TEST_F(RE2OptionsTest_242, DotNLTrue_242) {

    options.set_dot_nl(true);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl | Regexp::DotNL);

}



TEST_F(RE2OptionsTest_242, NeverCaptureTrue_242) {

    options.set_never_capture(true);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl | Regexp::NeverCapture);

}



TEST_F(RE2OptionsTest_242, CaseSensitiveFalse_242) {

    options.set_case_sensitive(false);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::FoldCase);

}



TEST_F(RE2OptionsTest_242, PerlClassesTrue_242) {

    options.set_perl_classes(true);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl | Regexp::PerlClasses);

}



TEST_F(RE2OptionsTest_242, WordBoundaryTrue_242) {

    options.set_word_boundary(true);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl | Regexp::PerlB);

}



TEST_F(RE2OptionsTest_242, OneLineTrue_242) {

    options.set_one_line(true);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::OneLine);

}



TEST_F(RE2OptionsTest_242, MultipleFlagsSet_242) {

    options.set_posix_syntax(true);

    options.set_dot_nl(true);

    options.set_case_sensitive(false);

    EXPECT_EQ(options.ParseFlags(), Regexp::ClassNL | Regexp::DotNL | Regexp::FoldCase);

}



TEST_F(RE2OptionsTest_242, CannedOptionsLatin1_242) {

    RE2::Options latin1_options(RE2::Latin1);

    EXPECT_EQ(latin1_options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl | Regexp::Latin1);

}



TEST_F(RE2OptionsTest_242, CannedOptionsPOSIX_242) {

    RE2::Options posix_options(RE2::POSIX);

    EXPECT_EQ(posix_options.ParseFlags(), Regexp::ClassNL);

}



TEST_F(RE2OptionsTest_242, CannedOptionsQuiet_242) {

    RE2::Options quiet_options(RE2::Quiet);

    EXPECT_EQ(quiet_options.ParseFlags(), Regexp::ClassNL | Regexp::LikePerl);

}
