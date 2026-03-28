#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.cc"

#include "absl/strings/string_view.h"



namespace re2 {



class TruncFunctionTest_241 : public ::testing::Test {

protected:

    // No additional setup needed for this simple function

};



TEST_F(TruncFunctionTest_241, NormalOperationShortString_241) {

    absl::string_view pattern = "short";

    EXPECT_EQ(trunc(pattern), "short");

}



TEST_F(TruncFunctionTest_241, NormalOperationLongString_241) {

    std::string long_pattern(150, 'a'); // 150 'a' characters

    absl::string_view pattern(long_pattern);

    EXPECT_EQ(trunc(pattern), std::string(100, 'a') + "...");

}



TEST_F(TruncFunctionTest_241, BoundaryConditionExactLength_241) {

    std::string exact_length_pattern(100, 'b'); // exactly 100 'b' characters

    absl::string_view pattern(exact_length_pattern);

    EXPECT_EQ(trunc(pattern), exact_length_pattern); // should not truncate

}



TEST_F(TruncFunctionTest_241, BoundaryConditionJustOverLength_241) {

    std::string just_over_pattern(101, 'c'); // 101 'c' characters

    absl::string_view pattern(just_over_pattern);

    EXPECT_EQ(trunc(pattern), std::string(100, 'c') + "...");

}



TEST_F(TruncFunctionTest_241, EmptyString_241) {

    absl::string_view pattern = "";

    EXPECT_EQ(trunc(pattern), "");

}



} // namespace re2
