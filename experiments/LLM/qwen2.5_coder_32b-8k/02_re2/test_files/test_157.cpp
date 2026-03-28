#include "gtest/gtest.h"

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_157 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(RegexpTest_157, ParseValidRegex_157) {

    RegexpStatus status;

    Regexp* regex = Regexp::Parse("abc", Regexp::NoParseFlags(), &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(regex, nullptr);

    regex->Decref();

}



TEST_F(RegexpTest_157, ParseInvalidRegex_157) {

    RegexpStatus status;

    Regexp* regex = Regexp::Parse("(*", Regexp::NoParseFlags(), &status);

    EXPECT_FALSE(status.ok());

    ASSERT_EQ(regex, nullptr);

}



TEST_F(RegexpTest_157, SimplifyRegex_157) {

    RegexpStatus status;

    Regexp* regex = Regexp::Parse("(abc){2}", Regexp::NoParseFlags(), &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(regex, nullptr);



    Regexp* simplified_regex = regex->Simplify();

    ASSERT_NE(simplified_regex, nullptr);



    simplified_regex->Decref();

    regex->Decref();

}



TEST_F(RegexpTest_157, NumCapturesBasic_157) {

    RegexpStatus status;

    Regexp* regex = Regexp::Parse("abc", Regexp::NoParseFlags(), &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(regex, nullptr);



    int num_captures = regex->NumCaptures();

    EXPECT_EQ(num_captures, 0);



    regex->Decref();

}



TEST_F(RegexpTest_157, NumCapturesWithCaptureGroups_157) {

    RegexpStatus status;

    Regexp* regex = Regexp::Parse("(abc)(def)", Regexp::NoParseFlags(), &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(regex, nullptr);



    int num_captures = regex->NumCaptures();

    EXPECT_EQ(num_captures, 2);



    regex->Decref();

}



TEST_F(RegexpTest_157, CharClassValidRegex_157) {

    RegexpStatus status;

    Regexp* regex = Regexp::Parse("[abc]", Regexp::NoParseFlags(), &status);

    EXPECT_TRUE(status.ok());

    ASSERT_NE(regex, nullptr);



    EXPECT_EQ(regex->op(), kRegexpCharClass);

    CharClass* cc = regex->cc();

    ASSERT_NE(cc, nullptr);



    regex->Decref();

}



TEST_F(RegexpTest_157, CharClassInvalidRegex_157) {

    RegexpStatus status;

    Regexp* regex = Regexp::Parse("[abc", Regexp::NoParseFlags(), &status);

    EXPECT_FALSE(status.ok());

    ASSERT_EQ(regex, nullptr);

}
