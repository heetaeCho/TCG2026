#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/utils.cpp"



using namespace Exiv2::Internal;



TEST(lower_1272, NormalOperation_1272) {

    std::string_view input = "HelloWorld";

    std::string expected = "helloworld";

    EXPECT_EQ(lower(input), expected);

}



TEST(lower_1272, AlreadyLowerCase_1272) {

    std::string_view input = "helloworld";

    std::string expected = "helloworld";

    EXPECT_EQ(lower(input), expected);

}



TEST(lower_1272, UpperCase_1272) {

    std::string_view input = "HELLOWORLD";

    std::string expected = "helloworld";

    EXPECT_EQ(lower(input), expected);

}



TEST(lower_1272, MixedCaseWithNumbers_1272) {

    std::string_view input = "HeLLoWoRLD123";

    std::string expected = "helloworld123";

    EXPECT_EQ(lower(input), expected);

}



TEST(lower_1272, EmptyString_1272) {

    std::string_view input = "";

    std::string expected = "";

    EXPECT_EQ(lower(input), expected);

}



TEST(lower_1272, SingleUpperCaseLetter_1272) {

    std::string_view input = "A";

    std::string expected = "a";

    EXPECT_EQ(lower(input), expected);

}



TEST(lower_1272, SingleLowerCaseLetter_1272) {

    std::string_view input = "a";

    std::string expected = "a";

    EXPECT_EQ(lower(input), expected);

}



TEST(lower_1272, SpecialCharacters_1272) {

    std::string_view input = "!@#$%^&*()";

    std::string expected = "!@#$%^&*()";

    EXPECT_EQ(lower(input), expected);

}



TEST(lower_1272, MixedWithSpecialCharacters_1272) {

    std::string_view input = "HeLLo!WoRLD@123#";

    std::string expected = "helloworld!123#";

    EXPECT_EQ(lower(input), expected);

}
