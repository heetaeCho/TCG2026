#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



namespace re2 {



class NumCapturesWalkerMock : public NumCapturesWalker {

public:

    MOCK_METHOD(Ignored, PreVisit, (Regexp* re, Ignored ignored, bool* stop), (override));

    MOCK_METHOD(Ignored, ShortVisit, (Regexp* re, Ignored ignored), (override));

};



class RegexpTest_355 : public ::testing::Test {

protected:

    void SetUp() override {

        status = new RegexpStatus();

    }



    void TearDown() override {

        delete status;

    }



    RegexpStatus *status;

};



TEST_F(RegexpTest_355, NumCaptures_ReturnsZeroForNoCaptures_355) {

    const std::string pattern = "abc";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    EXPECT_EQ(re->NumCaptures(), 0);

    re->Decref();

}



TEST_F(RegexpTest_355, NumCaptures_ReturnsCorrectNumberOfCaptures_355) {

    const std::string pattern = "(abc)(def)";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    EXPECT_EQ(re->NumCaptures(), 2);

    re->Decref();

}



TEST_F(RegexpTest_355, NumCaptures_ReturnsCorrectNumberOfNestedCaptures_355) {

    const std::string pattern = "((abc)(def))";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    EXPECT_EQ(re->NumCaptures(), 2);

    re->Decref();

}



TEST_F(RegexpTest_355, NumCaptures_HandlesMultipleNestedCapturesCorrectly_355) {

    const std::string pattern = "((a(b)c)d)e";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    EXPECT_EQ(re->NumCaptures(), 4);

    re->Decref();

}



TEST_F(RegexpTest_355, NumCaptures_ReturnsZeroForEmptyString_355) {

    const std::string pattern = "";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    EXPECT_EQ(re->NumCaptures(), 0);

    re->Decref();

}



TEST_F(RegexpTest_355, NumCaptures_ReturnsCorrectNumberOfCapturesWithNamedGroups_355) {

    const std::string pattern = "(?<name1>abc)(?<name2>def)";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    EXPECT_EQ(re->NumCaptures(), 2);

    re->Decref();

}



TEST_F(RegexpTest_355, NumCaptures_ReturnsZeroForInvalidPattern_355) {

    const std::string pattern = "abc(";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    EXPECT_EQ(re, nullptr);

}



TEST_F(RegexpTest_355, NumCaptures_WalkerShortVisitNotCalledForNonCaptureGroups_355) {

    const std::string pattern = "abc";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    NumCapturesWalkerMock walker;

    EXPECT_CALL(walker, ShortVisit(testing::_, testing::_)).Times(0);

    walker.Walk(re);

    re->Decref();

}



TEST_F(RegexpTest_355, NumCaptures_WalkerShortVisitCalledForCaptureGroups_355) {

    const std::string pattern = "(abc)";

    Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags(), status);

    NumCapturesWalkerMock walker;

    EXPECT_CALL(walker, ShortVisit(testing::_, testing::_)).Times(1);

    walker.Walk(re);

    re->Decref();

}



}  // namespace re2
