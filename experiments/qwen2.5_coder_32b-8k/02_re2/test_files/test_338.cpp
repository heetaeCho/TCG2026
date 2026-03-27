#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class RegexpTest_338 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common resources if needed

    }



    void TearDown() override {

        // Cleanup any common resources if needed

    }

};



TEST_F(RegexpTest_338, PlusIncreasesReferenceCount_338) {

    Regexp* sub = Regexp::Parse("a", DefaultFlags(), nullptr);

    ASSERT_NE(sub, nullptr);



    int initial_ref_count = sub->Ref();

    Regexp* plus_regex = sub->Plus(sub, DefaultFlags());

    

    EXPECT_EQ(plus_regex->op(), kRegexpPlus);

    EXPECT_EQ(sub->Ref(), initial_ref_count + 1); // Plus should increase ref count of the subexpression



    sub->Decref();  // Decrement ref count for the original subexpression

    plus_regex->Decref();  // Decrement ref count for the new plus expression

}



TEST_F(RegexpTest_338, PlusHandlesNullSubExpression_338) {

    Regexp* plus_regex = Regexp::Plus(nullptr, DefaultFlags());

    

    EXPECT_EQ(plus_regex, nullptr); // Plus should return null if subexpression is null

}



TEST_F(RegexpTest_338, PlusPreservesParseFlags_338) {

    ParseFlags flags = DefaultFlags() | kFlagIgnoreCase;

    Regexp* sub = Regexp::Parse("a", flags, nullptr);

    ASSERT_NE(sub, nullptr);



    Regexp* plus_regex = sub->Plus(sub, flags);

    

    EXPECT_EQ(plus_regex->op(), kRegexpPlus);

    EXPECT_EQ(plus_regex->parse_flags() & kFlagIgnoreCase, flags & kFlagIgnoreCase); // Plus should preserve parse flags



    sub->Decref();  // Decrement ref count for the original subexpression

    plus_regex->Decref();  // Decrement ref count for the new plus expression

}



TEST_F(RegexpTest_338, PlusDoesNotModifyOriginalSubExpression_338) {

    Regexp* sub = Regexp::Parse("a", DefaultFlags(), nullptr);

    ASSERT_NE(sub, nullptr);



    int original_nsub = sub->nsub();

    uint8_t original_op = static_cast<uint8_t>(sub->op());



    Regexp* plus_regex = sub->Plus(sub, DefaultFlags());

    

    EXPECT_EQ(plus_regex->op(), kRegexpPlus);

    EXPECT_EQ(sub->op(), original_op); // Plus should not modify the original subexpression's op

    EXPECT_EQ(sub->nsub(), original_nsub); // Plus should not modify the original subexpression's nsub



    sub->Decref();  // Decrement ref count for the original subexpression

    plus_regex->Decref();  // Decrement ref count for the new plus expression

}



TEST_F(RegexpTest_338, PlusCreatesNewExpressionWithCorrectOp_338) {

    Regexp* sub = Regexp::Parse("a", DefaultFlags(), nullptr);

    ASSERT_NE(sub, nullptr);



    Regexp* plus_regex = sub->Plus(sub, DefaultFlags());

    

    EXPECT_EQ(plus_regex->op(), kRegexpPlus); // Plus should create a new expression with op kRegexpPlus



    sub->Decref();  // Decrement ref count for the original subexpression

    plus_regex->Decref();  // Decrement ref count for the new plus expression

}
