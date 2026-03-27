#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch::Clara;



TEST_F(OptTest_663, IsMatch_ReturnsTrueForExactMatch_663) {

    Opt opt(false);

    opt["--option"];

    EXPECT_TRUE(opt.isMatch(StringRef("--option")));

}



TEST_F(OptTest_663, IsMatch_ReturnsFalseForNonMatchingOption_663) {

    Opt opt(false);

    opt["--option"];

    EXPECT_FALSE(opt.isMatch(StringRef("--another-option")));

}



TEST_F(OptTest_663, IsMatch_ReturnsTrueForCaseInsensitiveMatch_663) {

    Opt opt(false);

    opt["--Option"];

    EXPECT_TRUE(opt.isMatch(StringRef("--option")));

}



TEST_F(OptTest_663, IsMatch_ReturnsTrueForMultipleMatchingOptions_663) {

    Opt opt(false);

    opt["--option1"]["--option2"];

    EXPECT_TRUE(opt.isMatch(StringRef("--option1")));

    EXPECT_TRUE(opt.isMatch(StringRef("--option2")));

}



TEST_F(OptTest_663, IsMatch_ReturnsFalseForEmptyOptionToken_663) {

    Opt opt(false);

    opt["--option"];

    EXPECT_FALSE(opt.isMatch(StringRef("")));

}



TEST_F(OptTest_663, IsMatch_ReturnsTrueForLongestPrefixMatch_663) {

    Opt opt(false);

    opt["--long-option"];

    EXPECT_TRUE(opt.isMatch(StringRef("--long-option")));

    EXPECT_FALSE(opt.isMatch(StringRef("--lon")));

}



TEST_F(OptTest_663, IsMatch_ReturnsFalseForPartialMatch_663) {

    Opt opt(false);

    opt["--option"];

    EXPECT_FALSE(opt.isMatch(StringRef("opt")));

}
