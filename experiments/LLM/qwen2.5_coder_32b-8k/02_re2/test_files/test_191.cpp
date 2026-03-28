#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/util/pcre.h"



using namespace re2;

using ::testing::_;

using ::testing::Invoke;



class PCRETest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PCRETest_191, DoMatch_SuccessfulMatch_191) {

    PCRE pattern("abc");

    absl::string_view input = "abcdef";

    size_t consumed;

    const Arg* args[kMaxArgs] = {};

    bool result = pattern.DoMatch(input, ANCHOR_START, &consumed, args, 0);

    EXPECT_TRUE(result);

    EXPECT_EQ(consumed, 3u);

}



TEST_F(PCRETest_191, DoMatch_NoMatch_191) {

    PCRE pattern("xyz");

    absl::string_view input = "abcdef";

    size_t consumed;

    const Arg* args[kMaxArgs] = {};

    bool result = pattern.DoMatch(input, ANCHOR_START, &consumed, args, 0);

    EXPECT_FALSE(result);

}



TEST_F(PCRETest_191, DoMatch_BoundaryCondition_EmptyInput_191) {

    PCRE pattern("abc");

    absl::string_view input = "";

    size_t consumed;

    const Arg* args[kMaxArgs] = {};

    bool result = pattern.DoMatch(input, ANCHOR_START, &consumed, args, 0);

    EXPECT_FALSE(result);

}



TEST_F(PCRETest_191, DoMatch_BoundaryCondition_EmptyPattern_191) {

    PCRE pattern("");

    absl::string_view input = "abcdef";

    size_t consumed;

    const Arg* args[kMaxArgs] = {};

    bool result = pattern.DoMatch(input, ANCHOR_START, &consumed, args, 0);

    EXPECT_TRUE(result); // An empty pattern should match the start of any string

}



TEST_F(PCRETest_191, DoMatch_Arguments_SuccessfulMatch_191) {

    PCRE pattern("a(b)c(d)");

    absl::string_view input = "abcd";

    size_t consumed;

    int arg0_value, arg1_value;

    Arg args[] = {Arg(&arg0_value), Arg(&arg1_value)};

    bool result = pattern.DoMatch(input, ANCHOR_START, &consumed, args, 2);

    EXPECT_TRUE(result);

    EXPECT_EQ(consumed, 4u);

    EXPECT_EQ(arg0_value, 'b');

    EXPECT_EQ(arg1_value, 'd');

}



TEST_F(PCRETest_191, DoMatch_Arguments_NoMatch_191) {

    PCRE pattern("a(b)c(d)");

    absl::string_view input = "abcf";

    size_t consumed;

    int arg0_value, arg1_value;

    Arg args[] = {Arg(&arg0_value), Arg(&arg1_value)};

    bool result = pattern.DoMatch(input, ANCHOR_START, &consumed, args, 2);

    EXPECT_FALSE(result);

}



TEST_F(PCRETest_191, HitLimit_DefaultState_191) {

    PCRE pattern("a(b)c(d)");

    EXPECT_FALSE(pattern.HitLimit());

}



TEST_F(PCRETest_191, ClearHitLimit_NoEffectWhenNotSet_191) {

    PCRE pattern("a(b)c(d)");

    pattern.ClearHitLimit();

    EXPECT_FALSE(pattern.HitLimit());

}



TEST_F(PCRETest_191, NumberOfCapturingGroups_ReturnsCorrectValue_191) {

    PCRE pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)(p)");

    EXPECT_EQ(pattern.NumberOfCapturingGroups(), 16);

}



TEST_F(PCRETest_191, NumberOfCapturingGroups_NoCapturingGroups_191) {

    PCRE pattern("abcdef");

    EXPECT_EQ(pattern.NumberOfCapturingGroups(), 0);

}
