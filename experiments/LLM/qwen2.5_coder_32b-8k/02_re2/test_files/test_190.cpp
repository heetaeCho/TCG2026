#include <gtest/gtest.h>

#include "pcre.h"



namespace re2 {

class PCRETest : public ::testing::Test {

protected:

    void SetUp() override {

        pattern = "abc";

        pcre_obj = std::make_unique<PCRE>(pattern);

    }



    std::string pattern;

    std::unique_ptr<PCRE> pcre_obj;

};



TEST_F(PCRETest_190, MatchSimplePattern_190) {

    size_t consumed = 0;

    EXPECT_TRUE(pcre_obj->DoMatch("abc", UNANCHORED, &consumed, nullptr, 0));

    EXPECT_EQ(consumed, 3);

}



TEST_F(PCRETest_190, NoMatchDifferentText_190) {

    size_t consumed = 0;

    EXPECT_FALSE(pcre_obj->DoMatch("def", UNANCHORED, &consumed, nullptr, 0));

    EXPECT_EQ(consumed, 0);

}



TEST_F(PCRETest_190, MatchWithAnchor_190) {

    size_t consumed = 0;

    EXPECT_TRUE(pcre_obj->DoMatch("^abc$", ANCHOR_BOTH, &consumed, nullptr, 0));

    EXPECT_EQ(consumed, 3);



    EXPECT_FALSE(pcre_obj->DoMatch("abc", ANCHOR_START, &consumed, nullptr, 0));

    EXPECT_EQ(consumed, 0);

}



TEST_F(PCRETest_190, MatchWithArgs_190) {

    size_t consumed = 0;

    char buffer[4];

    PCRE::Arg arg(buffer, PCRE::Arg::parse_string);



    EXPECT_TRUE(pcre_obj->DoMatch("abc", UNANCHORED, &consumed, &arg, 1));

    EXPECT_EQ(consumed, 3);

    EXPECT_STREQ(buffer, "abc");

}



TEST_F(PCRETest_190, MatchWithMaxArgs_190) {

    size_t consumed = 0;

    PCRE::Arg args[re2::kMaxArgs];

    for (int i = 0; i < re2::kMaxArgs; ++i) {

        new(&args[i]) PCRE::Arg();

    }



    EXPECT_TRUE(pcre_obj->DoMatch("abc", UNANCHORED, &consumed, args, re2::kMaxArgs));

    EXPECT_EQ(consumed, 3);

}



TEST_F(PCRETest_190, MatchBoundaryConditionEmptyText_190) {

    size_t consumed = 0;

    EXPECT_FALSE(pcre_obj->DoMatch("", UNANCHORED, &consumed, nullptr, 0));

    EXPECT_EQ(consumed, 0);

}



TEST_F(PCRETest_190, MatchWithNullArgs_190) {

    size_t consumed = 0;

    PCRE::Arg* args[re2::kMaxArgs] = {nullptr};



    EXPECT_TRUE(pcre_obj->DoMatch("abc", UNANCHORED, &consumed, args, re2::kMaxArgs));

    EXPECT_EQ(consumed, 3);

}



TEST_F(PCRETest_190, MatchWithTooManyArgs_190) {

    size_t consumed = 0;

    PCRE::Arg* args[re2::kMaxArgs + 1];

    for (int i = 0; i <= re2::kMaxArgs; ++i) {

        new(&args[i]) PCRE::Arg();

    }



    EXPECT_FALSE(pcre_obj->DoMatch("abc", UNANCHORED, &consumed, args, re2::kMaxArgs + 1));

}



TEST_F(PCRETest_190, PartialMatchFunctorNormalOperation_190) {

    size_t consumed = 0;

    PCRE::PartialMatchFunctor functor;



    EXPECT_TRUE(functor("abc", *pcre_obj, PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                        PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                        PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                        PCRE::Arg(), PCRE::Arg()));

    EXPECT_EQ(consumed, 3);

}



TEST_F(PCRETest_190, PartialMatchFunctorNoMatch_190) {

    size_t consumed = 0;

    PCRE::PartialMatchFunctor functor;



    EXPECT_FALSE(functor("def", *pcre_obj, PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg()));

    EXPECT_EQ(consumed, 0);

}



TEST_F(PCRETest_190, PartialMatchFunctorWithArgs_190) {

    size_t consumed = 0;

    char buffer[4];

    PCRE::PartialMatchFunctor functor;

    PCRE::Arg arg(buffer, PCRE::Arg::parse_string);



    EXPECT_TRUE(functor("abc", *pcre_obj, arg, PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                        PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                        PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                        PCRE::Arg(), PCRE::Arg()));

    EXPECT_EQ(consumed, 3);

    EXPECT_STREQ(buffer, "abc");

}



TEST_F(PCRETest_190, PartialMatchFunctorBoundaryConditionEmptyText_190) {

    size_t consumed = 0;

    PCRE::PartialMatchFunctor functor;



    EXPECT_FALSE(functor("", *pcre_obj, PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg()));

    EXPECT_EQ(consumed, 0);

}



TEST_F(PCRETest_190, PartialMatchFunctorWithTooManyArgs_190) {

    size_t consumed = 0;

    PCRE::PartialMatchFunctor functor;



    EXPECT_FALSE(functor("abc", *pcre_obj, PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),

                         PCRE::Arg(), PCRE::Arg(), PCRE::Arg()));

}

}  // namespace re2
