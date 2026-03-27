#include "gtest/gtest.h"

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_340 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_340, QuestReturnsNonNullPointer_340) {

    Regexp* sub = Regexp::Parse("a", DefaultFlags(), nullptr);

    ASSERT_NE(sub, nullptr);



    Regexp* result = sub->Quest(DefaultFlags());

    EXPECT_NE(result, nullptr);



    result->Decref();

    sub->Decref();

}



TEST_F(RegexpTest_340, QuestIncreasesReferenceCount_340) {

    Regexp* sub = Regexp::Parse("a", DefaultFlags(), nullptr);

    ASSERT_NE(sub, nullptr);

    int initialRef = sub->Ref();



    Regexp* result = sub->Quest(DefaultFlags());

    EXPECT_NE(result, nullptr);



    int finalSubRef = sub->Ref();

    int finalResultRef = result->Ref();



    EXPECT_EQ(finalSubRef, initialRef + 1); // Sub's ref count should increase by 1

    EXPECT_EQ(finalResultRef, 1); // Result's ref count should be 1 initially



    result->Decref();

    sub->Decref();

}



TEST_F(RegexpTest_340, QuestWithNullSubPointer_ReturnsNull_340) {

    Regexp* result = Regexp::Quest(nullptr, DefaultFlags());

    EXPECT_EQ(result, nullptr);

}



TEST_F(RegexpTest_340, QuestOpTypeIsCorrect_340) {

    Regexp* sub = Regexp::Parse("a", DefaultFlags(), nullptr);

    ASSERT_NE(sub, nullptr);



    Regexp* result = sub->Quest(DefaultFlags());

    EXPECT_NE(result, nullptr);



    EXPECT_EQ(result->op(), kRegexpQuest);



    result->Decref();

    sub->Decref();

}



TEST_F(RegexpTest_340, QuestWithDefaultFlags_ReturnsValidRegexp_340) {

    Regexp* sub = Regexp::Parse("a", DefaultFlags(), nullptr);

    ASSERT_NE(sub, nullptr);



    Regexp* result = sub->Quest(DefaultFlags());

    EXPECT_NE(result, nullptr);



    std::string expected = "(?:a)?";

    EXPECT_EQ(result->ToString(), expected);



    result->Decref();

    sub->Decref();

}
