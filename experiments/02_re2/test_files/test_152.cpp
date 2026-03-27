#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "absl/strings/string_view.h"



using namespace re2;



class RegexpTest_152 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_152, ParseValidRegex_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_TRUE(status.ok());

    EXPECT_NE(regexp, nullptr);

    delete regexp; // Clean up

}



TEST_F(RegexpTest_152, ParseInvalidRegex_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+(";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(regexp, nullptr);

}



TEST_F(RegexpTest_152, ParseWithFlag_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::Literal(), &status);

    EXPECT_TRUE(status.ok());

    EXPECT_NE(regexp, nullptr);

    delete regexp; // Clean up

}



TEST_F(RegexpTest_152, SimplifyValidRegex_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_TRUE(status.ok());

    Regexp* simplified = regexp->Simplify();

    EXPECT_NE(simplified, nullptr);

    delete simplified; // Clean up

    delete regexp; // Clean up

}



TEST_F(RegexpTest_152, SimplifyInvalidRegex_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+(";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(regexp, nullptr);

}



TEST_F(RegexpTest_152, NumCapturesZero_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(regexp->NumCaptures(), 0);

    delete regexp; // Clean up

}



TEST_F(RegexpTest_152, NumCapturesOne_152) {

    RegexpStatus status;

    absl::string_view pattern = "(a+)";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(regexp->NumCaptures(), 1);

    delete regexp; // Clean up

}



TEST_F(RegexpTest_152, RefCounting_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_TRUE(status.ok());

    int initial_ref_count = regexp->Ref();

    regexp->Incref();

    EXPECT_EQ(regexp->Ref(), initial_ref_count + 1);

    regexp->Decref();

    regexp->Decref(); // This should delete the object

}



TEST_F(RegexpTest_152, ToStringBasic_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_TRUE(status.ok());

    std::string result = regexp->ToString();

    EXPECT_EQ(result, "a+");

    delete regexp; // Clean up

}



TEST_F(RegexpTest_152, ToStringComplex_152) {

    RegexpStatus status;

    absl::string_view pattern = "(a+b*)*";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_TRUE(status.ok());

    std::string result = regexp->ToString();

    EXPECT_EQ(result, "(a+b*)*");

    delete regexp; // Clean up

}



TEST_F(RegexpTest_152, ParseFlagsDefault_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::NoFlags(), &status);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(regexp->parse_flags(), Regexp::NoFlags());

    delete regexp; // Clean up

}



TEST_F(RegexpTest_152, ParseFlagsLiteral_152) {

    RegexpStatus status;

    absl::string_view pattern = "a+";

    Regexp* regexp = Regexp::Parse(pattern, Regexp::Literal(), &status);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(regexp->parse_flags(), Regexp::Literal());

    delete regexp; // Clean up

}
