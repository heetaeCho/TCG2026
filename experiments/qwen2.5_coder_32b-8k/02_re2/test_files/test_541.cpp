#include <gtest/gtest.h>

#include "prefilter.h"



namespace re2 {

class PrefilterTest_541 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(PrefilterTest_541, Alt_ReturnsValidInfoPtr_541) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Alt(a, b);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, Concat_ReturnsValidInfoPtr_541) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Concat(a, b);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, And_ReturnsValidInfoPtr_541) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::And(a, b);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, Star_ReturnsValidInfoPtr_541) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Star(a);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, Plus_ReturnsValidInfoPtr_541) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Plus(a);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, Quest_ReturnsValidInfoPtr_541) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Quest(a);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, EmptyString_ReturnsValidInfoPtr_541) {

    Prefilter::Info* result = Prefilter::Info::EmptyString();

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, NoMatch_ReturnsValidInfoPtr_541) {

    Prefilter::Info* result = Prefilter::Info::NoMatch();

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, AnyCharOrAnyByte_ReturnsValidInfoPtr_541) {

    Prefilter::Info* result = Prefilter::Info::AnyCharOrAnyByte();

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, Literal_ReturnsValidInfoPtr_541) {

    Rune r = 'a';

    Prefilter::Info* result = Prefilter::Info::Literal(r);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, LiteralLatin1_ReturnsValidInfoPtr_541) {

    Rune r = 'b';

    Prefilter::Info* result = Prefilter::Info::LiteralLatin1(r);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, AnyMatch_ReturnsValidInfoPtr_541) {

    Prefilter::Info* result = Prefilter::Info::AnyMatch();

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, CClass_ReturnsValidInfoPtr_541) {

    CharClass cc;

    bool latin1 = false;

    Prefilter::Info* result = Prefilter::Info::CClass(&cc, latin1);

    EXPECT_NE(result, nullptr);

    delete result;

}



TEST_F(PrefilterTest_541, TakeMatch_ReturnsNullptrIfNoMatch_541) {

    Prefilter::Info info;

    Prefilter* match = info.TakeMatch();

    EXPECT_EQ(match, nullptr);

}



TEST_F(PrefilterTest_541, ToString_ReturnsNonEmptyString_541) {

    Prefilter::Info info;

    std::string result = info.ToString();

    EXPECT_FALSE(result.empty());

}



}  // namespace re2
