#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {



class RE2OptionsTest_24 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(RE2OptionsTest_24, DefaultConstructorInitializesValues_24) {

    EXPECT_EQ(options.max_mem(), 10 << 20); // Assuming kDefaultMaxMem is 10<<20

    EXPECT_EQ(options.encoding(), EncodingUTF8);

    EXPECT_FALSE(options.posix_syntax());

    EXPECT_FALSE(options.longest_match());

    EXPECT_TRUE(options.log_errors());

    EXPECT_FALSE(options.literal());

    EXPECT_FALSE(options.never_nl());

    EXPECT_FALSE(options.dot_nl());

    EXPECT_FALSE(options.never_capture());

    EXPECT_TRUE(options.case_sensitive());

    EXPECT_FALSE(options.perl_classes());

    EXPECT_FALSE(options.word_boundary());

    EXPECT_FALSE(options.one_line());

}



TEST_F(RE2OptionsTest_24, SettersModifyValuesCorrectly_24) {

    options.set_max_mem(50 << 20);

    options.set_encoding(EncodingLatin1);

    options.set_posix_syntax(true);

    options.set_longest_match(true);

    options.set_log_errors(false);

    options.set_literal(true);

    options.set_never_nl(true);

    options.set_dot_nl(true);

    options.set_never_capture(true);

    options.set_case_sensitive(false);

    options.set_perl_classes(true);

    options.set_word_boundary(true);

    options.set_one_line(true);



    EXPECT_EQ(options.max_mem(), 50 << 20);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

    EXPECT_TRUE(options.posix_syntax());

    EXPECT_TRUE(options.longest_match());

    EXPECT_FALSE(options.log_errors());

    EXPECT_TRUE(options.literal());

    EXPECT_TRUE(options.never_nl());

    EXPECT_TRUE(options.dot_nl());

    EXPECT_TRUE(options.never_capture());

    EXPECT_FALSE(options.case_sensitive());

    EXPECT_TRUE(options.perl_classes());

    EXPECT_TRUE(options.word_boundary());

    EXPECT_TRUE(options.one_line());

}



TEST_F(RE2OptionsTest_24, CopyFunctionCopiesValuesProperly_24) {

    Options source;

    source.set_max_mem(150 << 20);

    source.set_encoding(EncodingLatin1);

    source.set_posix_syntax(true);



    options.Copy(source);



    EXPECT_EQ(options.max_mem(), 150 << 20);

    EXPECT_EQ(options.encoding(), EncodingLatin1);

    EXPECT_TRUE(options.posix_syntax());

}



TEST_F(RE2OptionsTest_24, ParseFlagsReturnsCorrectValue_24) {

    // This test assumes that ParseFlags returns an integer encoding the state of options.

    int flags = options.ParseFlags();

    EXPECT_EQ(flags, 0); // Assuming default values map to 0



    options.set_posix_syntax(true);

    options.set_log_errors(false);



    flags = options.ParseFlags();

    EXPECT_NE(flags, 0); // Assuming setting some options changes the flag value

}



TEST_F(RE2OptionsTest_24, CannedOptionsSetCorrectValues_24) {

    Options latin1_opt(RE2::Latin1);

    EXPECT_EQ(latin1_opt.encoding(), EncodingLatin1);



    Options posix_opt(RE2::POSIX);

    EXPECT_TRUE(posix_opt.posix_syntax());

    EXPECT_TRUE(posix_opt.longest_match());



    Options quiet_opt(RE2::Quiet);

    EXPECT_FALSE(quiet_opt.log_errors());

}



TEST_F(RE2OptionsTest_24, BoundaryConditionsWithSetters_24) {

    options.set_max_mem(INT64_MAX);

    EXPECT_EQ(options.max_mem(), INT64_MAX);



    options.set_max_mem(INT64_MIN);

    EXPECT_EQ(options.max_mem(), INT64_MIN);

}



} // namespace re2
