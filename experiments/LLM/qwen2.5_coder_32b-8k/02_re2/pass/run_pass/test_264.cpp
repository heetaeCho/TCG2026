#include <gtest/gtest.h>

#include <absl/strings/string_view.h>

#include "re2/re2.h"



namespace re2 {



class RE2Test_264 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(RE2Test_264, MaxSubmatch_NoBackreferences_264) {

    absl::string_view rewrite = "no backrefs";

    EXPECT_EQ(RE2::MaxSubmatch(rewrite), 0);

}



TEST_F(RE2Test_264, MaxSubmatch_SingleDigitBackreference_264) {

    absl::string_view rewrite = "\\1";

    EXPECT_EQ(RE2::MaxSubmatch(rewrite), 1);

}



TEST_F(RE2Test_264, MaxSubmatch_MultipleSingleDigitBackreferences_264) {

    absl::string_view rewrite = "\\1\\2\\3";

    EXPECT_EQ(RE2::MaxSubmatch(rewrite), 3);

}



TEST_F(RE2Test_264, MaxSubmatch_MixedContent_264) {

    absl::string_view rewrite = "prefix \\4 suffix \\2";

    EXPECT_EQ(RE2::MaxSubmatch(rewrite), 4);

}



TEST_F(RE2Test_264, MaxSubmatch_EscapedBackslash_264) {

    absl::string_view rewrite = "\\\\1";

    EXPECT_EQ(RE2::MaxSubmatch(rewrite), 0);

}



TEST_F(RE2Test_264, MaxSubmatch_NoDigitsAfterBackslash_264) {

    absl::string_view rewrite = "\\";

    EXPECT_EQ(RE2::MaxSubmatch(rewrite), 0);

}



TEST_F(RE2Test_264, MaxSubmatch_BoundaryConditionSingleChar_264) {

    absl::string_view rewrite = "a\\9b";

    EXPECT_EQ(RE2::MaxSubmatch(rewrite), 9);

}



TEST_F(RE2Test_264, MaxSubmatch_BoundaryConditionEmptyString_264) {

    absl::string_view rewrite = "";

    EXPECT_EQ(RE2::MaxSubmatch(rewrite), 0);

}



} // namespace re2
