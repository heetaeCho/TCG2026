#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {

class RegexpTest_155 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(RegexpTest_155, Max_ReturnsExpectedValueForRepeatOp_155) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a{2,5}", DefaultParseFlags(), &status);

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(5, regexp->max());

    regexp->Decref();

}



TEST_F(RegexpTest_155, Max_ReturnsZeroForNonRepeatOp_155) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a", DefaultParseFlags(), &status);

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(0, regexp->max());

    regexp->Decref();

}



TEST_F(RegexpTest_155, Max_ReturnsExpectedValueForMaxRepeatCount_155) {

    Regexp::FUZZING_ONLY_set_maximum_repeat_count(3);

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a{2,}", DefaultParseFlags(), &status);

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(3, regexp->max());

    regexp->Decref();

}



TEST_F(RegexpTest_155, Max_ReturnsMaxIntForUnboundedRepeat_155) {

    Regexp::FUZZING_ONLY_set_maximum_repeat_count(std::numeric_limits<int>::max());

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a{2,}", DefaultParseFlags(), &status);

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(std::numeric_limits<int>::max(), regexp->max());

    regexp->Decref();

}



TEST_F(RegexpTest_155, Max_ReturnsZeroForEmptyString_155) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("", DefaultParseFlags(), &status);

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(0, regexp->max());

    regexp->Decref();

}



TEST_F(RegexpTest_155, Max_ReturnsZeroForInvalidPattern_155) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("[", DefaultParseFlags(), &status);

    EXPECT_EQ(regexp, nullptr);

    EXPECT_EQ(status.code(), kRegexpBadBackslash); // Assuming this is the error code for invalid patterns

}



}  // namespace re2
