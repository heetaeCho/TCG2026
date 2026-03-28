#include <gtest/gtest.h>

#include "tags_int.cpp"



namespace Exiv2 {

namespace Internal {



class MpfTagListTest : public ::testing::Test {

protected:

    const TagInfo* mpfTags;

    

    void SetUp() override {

        mpfTags = mpfTagList();

    }

};



TEST_F(MpfTagListTest_1360, ReturnsNonNullPointer_1360) {

    EXPECT_NE(mpfTags, nullptr);

}



TEST_F(MpfTagListTest_1360, CorrectNumberOfTags_1360) {

    int count = 0;

    while (mpfTags[count].tag != 65535) { // Assuming the last entry has tag 65535

        ++count;

    }

    EXPECT_EQ(count, 20);

}



TEST_F(MpfTagListTest_1360, FirstTagCorrect_1360) {

    EXPECT_EQ(mpfTags[0].tag, 45056);

    EXPECT_STREQ(mpfTags[0].name, "MPFVersion");

    EXPECT_STREQ(mpfTags[0].title, "MPF Version");

}



TEST_F(MpfTagListTest_1360, LastTagCorrect_1360) {

    const TagInfo& lastTag = mpfTags[19];

    EXPECT_EQ(lastTag.tag, 65535);

    EXPECT_STREQ(lastTag.name, "(UnknownMpfTag)");

    EXPECT_STREQ(lastTag.title, "Unknown MPF tag");

}



TEST_F(MpfTagListTest_1360, KnownTagCorrect_1360) {

    const TagInfo& knownTag = mpfTags[5];

    EXPECT_EQ(knownTag.tag, 45313);

    EXPECT_STREQ(knownTag.name, "MPFIndividualNum");

    EXPECT_STREQ(knownTag.title, "MPF Individual Num");

}



TEST_F(MpfTagListTest_1360, BoundaryCondition_FirstEntry_1360) {

    EXPECT_EQ(mpfTags[0].tag, 45056);

    EXPECT_NE(mpfTags[0].name, nullptr);

    EXPECT_NE(mpfTags[0].title, nullptr);

}



TEST_F(MpfTagListTest_1360, BoundaryCondition_LastEntry_1360) {

    const TagInfo& lastTag = mpfTags[19];

    EXPECT_EQ(lastTag.tag, 65535);

    EXPECT_NE(lastTag.name, nullptr);

    EXPECT_NE(lastTag.title, nullptr);

}



} // namespace Internal

} // namespace Exiv2
