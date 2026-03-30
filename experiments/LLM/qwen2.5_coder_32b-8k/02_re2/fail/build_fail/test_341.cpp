#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_341 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_341, ConcatNormalOperation_341) {

    Regexp* sub1 = Regexp::LiteralString(reinterpret_cast<Rune*>("abc"), 3, 0);

    Regexp* sub2 = Regexp::LiteralString(reinterpret_cast<Rune*>("def"), 3, 0);

    Regexp** subs = new Regexp*[2];

    subs[0] = sub1;

    subs[1] = sub2;



    Regexp* result = Regexp::Concat(subs, 2, 0);



    EXPECT_EQ(result->op(), kRegexpConcat);

    EXPECT_EQ(result->nsub(), 2);

    EXPECT_EQ(result->sub()[0], sub1);

    EXPECT_EQ(result->sub()[1], sub2);



    delete[] subs;

    result->Decref();

}



TEST_F(RegexpTest_341, ConcatEmptyArray_341) {

    Regexp** subs = new Regexp*[0];



    Regexp* result = Regexp::Concat(subs, 0, 0);



    EXPECT_EQ(result, nullptr);



    delete[] subs;

}



TEST_F(RegexpTest_341, ConcatSingleElement_341) {

    Regexp* sub1 = Regexp::LiteralString(reinterpret_cast<Rune*>("abc"), 3, 0);

    Regexp** subs = new Regexp*[1];

    subs[0] = sub1;



    Regexp* result = Regexp::Concat(subs, 1, 0);



    EXPECT_EQ(result->op(), kRegexpLiteralString);

    EXPECT_EQ(result->nsub(), 0);

    EXPECT_STREQ(reinterpret_cast<const char*>(result->runes()), "abc");



    delete[] subs;

    result->Decref();

}



TEST_F(RegexpTest_341, ConcatNullSubArray_341) {

    Regexp** subs = nullptr;



    Regexp* result = Regexp::Concat(subs, 2, 0);



    EXPECT_EQ(result, nullptr);

}
