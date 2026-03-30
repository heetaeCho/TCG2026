#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/prog.h"



namespace re2 {

class RegexpTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



TEST_F(RegexpTest_327, CompileToProg_NormalOperation_327) {

    Regexp* regexp = Regexp::Parse("abc", Regexp::NoFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToProg(1024);

    EXPECT_NE(prog, nullptr);



    prog->Decref();

    regexp->Decref();

}



TEST_F(RegexpTest_327, CompileToProg_BoundaryCondition_EmptyString_327) {

    Regexp* regexp = Regexp::Parse("", Regexp::NoFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToProg(1024);

    EXPECT_NE(prog, nullptr);



    prog->Decref();

    regexp->Decref();

}



TEST_F(RegexpTest_327, CompileToProg_BoundaryCondition_MaxMemory_327) {

    Regexp* regexp = Regexp::Parse("abc", Regexp::NoFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToProg(0);  // Minimal memory

    EXPECT_EQ(prog, nullptr);  // Expect failure due to insufficient memory



    regexp->Decref();

}



TEST_F(RegexpTest_327, CompileToProg_ExceptionalCase_InvalidRegex_327) {

    Regexp* regexp = Regexp::Parse("[", Regexp::NoFlags(), nullptr);

    EXPECT_EQ(regexp, nullptr);  // Invalid regex pattern

}



TEST_F(RegexpTest_327, CompileToProg_ExceptionalCase_LargePatternExceedingMemory_327) {

    std::string large_pattern(1024 * 1024, 'a');  // Large pattern



    Regexp* regexp = Regexp::Parse(large_pattern, Regexp::NoFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    Prog* prog = regexp->CompileToProg(1);  // Extremely limited memory

    EXPECT_EQ(prog, nullptr);  // Expect failure due to insufficient memory



    regexp->Decref();

}

}  // namespace re2
