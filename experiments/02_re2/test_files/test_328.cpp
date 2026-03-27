#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



namespace re2 {



class RegexpTest_328 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(RegexpTest_328, CompileToReverseProg_NormalOperation_328) {

    Regexp* regexp = Regexp::Parse("abc", Regexp::SimpleFlag, nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToReverseProg(1024);

    EXPECT_NE(prog, nullptr);



    delete prog;

    regexp->Decref();

}



TEST_F(RegexpTest_328, CompileToReverseProg_MaxMemZero_328) {

    Regexp* regexp = Regexp::Parse("abc", Regexp::SimpleFlag, nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToReverseProg(0);

    EXPECT_EQ(prog, nullptr);



    regexp->Decref();

}



TEST_F(RegexpTest_328, CompileToReverseProg_MaxMemBoundary_328) {

    Regexp* regexp = Regexp::Parse("abc", Regexp::SimpleFlag, nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToReverseProg(10); // Assuming 10 is a boundary condition

    EXPECT_EQ(prog, nullptr);



    regexp->Decref();

}



TEST_F(RegexpTest_328, CompileToReverseProg_EmptyString_328) {

    Regexp* regexp = Regexp::Parse("", Regexp::SimpleFlag, nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToReverseProg(1024);

    EXPECT_NE(prog, nullptr);



    delete prog;

    regexp->Decref();

}



TEST_F(RegexpTest_328, CompileToReverseProg_InvalidRegex_328) {

    Regexp* regexp = Regexp::Parse("[", Regexp::SimpleFlag, nullptr);

    ASSERT_EQ(regexp, nullptr); // Invalid regex pattern



    // No need to compile if parse fails

}



TEST_F(RegexpTest_328, CompileToReverseProg_LargeRegex_328) {

    std::string large_regex(100000, 'a'); // A very large regex

    Regexp* regexp = Regexp::Parse(large_regex, Regexp::SimpleFlag, nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToReverseProg(1024); // Assuming 1024 is too small for this regex

    EXPECT_EQ(prog, nullptr);



    regexp->Decref();

}



} // namespace re2
