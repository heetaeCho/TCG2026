#include <gtest/gtest.h>

#include "re2/regexp.h"



namespace re2 {



class RegexpTest_344 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_344, Capture_ReturnsValidPointer_344) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    Regexp* result = Regexp::Capture(sub, 0, 1);

    EXPECT_NE(result, nullptr);

    result->Decref();

}



TEST_F(RegexpTest_344, Capture_CorrectOp_344) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    Regexp* result = Regexp::Capture(sub, 0, 1);

    EXPECT_EQ(result->op(), kRegexpCapture);

    result->Decref();

}



TEST_F(RegexpTest_344, Capture_CorrectSubPointer_344) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    Regexp* result = Regexp::Capture(sub, 0, 1);

    EXPECT_EQ(result->sub()[0], sub);

    result->Decref();

}



TEST_F(RegexpTest_344, Capture_CorrectParseFlags_344) {

    Regexp* sub = new Regexp(kRegexpLiteral, ParseFlags::kParseCaseInsensitive);

    Regexp* result = Regexp::Capture(sub, ParseFlags::kParseCaseInsensitive, 1);

    EXPECT_EQ(result->parse_flags(), ParseFlags::kParseCaseInsensitive);

    result->Decref();

}



TEST_F(RegexpTest_344, Capture_CorrectCapValue_344) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    int cap_value = 5;

    Regexp* result = Regexp::Capture(sub, 0, cap_value);

    EXPECT_EQ(result->cap(), cap_value);

    result->Decref();

}



TEST_F(RegexpTest_344, Capture_IncrementsRefOnSub_344) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    EXPECT_EQ(sub->Ref(), 1);

    Regexp::Capture(sub, 0, 1);

    EXPECT_EQ(sub->Ref(), 2);

    sub->Decref();

}



TEST_F(RegexpTest_344, Capture_DecrementsRefOnSubAfterDelete_344) {

    Regexp* sub = new Regexp(kRegexpLiteral, 0);

    Regexp* result = Regexp::Capture(sub, 0, 1);

    EXPECT_EQ(sub->Ref(), 2);

    result->Decref();

    EXPECT_EQ(sub->Ref(), 1);

}



TEST_F(RegexpTest_344, Capture_NullSub_ReturnsNull_344) {

    Regexp* result = Regexp::Capture(nullptr, 0, 1);

    EXPECT_EQ(result, nullptr);

}



} // namespace re2
