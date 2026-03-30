#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "DistinguishedNameParser.h"



using namespace DN::detail;



class RemoveTrailingSpacesTest : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed.

};



TEST_F(RemoveTrailingSpacesTest_1938, NoTrailingSpaces_1938) {

    std::string_view input = "HelloWorld";

    std::string_view expected_output = "HelloWorld";

    EXPECT_EQ(removeTrailingSpaces(input), expected_output);

}



TEST_F(RemoveTrailingSpacesTest_1938, SingleTrailingSpace_1938) {

    std::string_view input = "HelloWorld ";

    std::string_view expected_output = "HelloWorld";

    EXPECT_EQ(removeTrailingSpaces(input), expected_output);

}



TEST_F(RemoveTrailingSpacesTest_1938, MultipleTrailingSpaces_1938) {

    std::string_view input = "HelloWorld   ";

    std::string_view expected_output = "HelloWorld";

    EXPECT_EQ(removeTrailingSpaces(input), expected_output);

}



TEST_F(RemoveTrailingSpacesTest_1938, AllSpaces_1938) {

    std::string_view input = "     ";

    std::string_view expected_output = "";

    EXPECT_EQ(removeTrailingSpaces(input), expected_output);

}



TEST_F(RemoveTrailingSpacesTest_1938, EmptyString_1938) {

    std::string_view input = "";

    std::string_view expected_output = "";

    EXPECT_EQ(removeTrailingSpaces(input), expected_output);

}
