#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.h"

#include "Link.h"



class PopplerActionTest_2295 : public ::testing::Test {

protected:

    PopplerAction action;

};



TEST_F(PopplerActionTest_2295, BuildNamedWithValidName_2295) {

    const char* expectedName = "valid_name";

    Object nameObj; // Assume this is properly initialized with the expectedName

    LinkNamed link(&nameObj);

    build_named(&action, &link);



    EXPECT_STREQ(action.named.named_dest, expectedName);

    g_free(action.named.named_dest); // Clean up allocated memory

}



TEST_F(PopplerActionTest_2295, BuildNamedWithEmptyName_2295) {

    const char* expectedName = "";

    Object nameObj; // Assume this is properly initialized with the expectedName

    LinkNamed link(&nameObj);

    build_named(&action, &link);



    EXPECT_STREQ(action.named.named_dest, expectedName);

    g_free(action.named.named_dest); // Clean up allocated memory

}



TEST_F(PopplerActionTest_2295, BuildNamedWithNullName_2295) {

    Object nameObj; // Assume this is properly initialized to result in nullptr

    LinkNamed link(&nameObj);

    build_named(&action, &link);



    EXPECT_EQ(action.named.named_dest, nullptr);

}



TEST_F(PopplerActionTest_2295, BuildNamedWithLongName_2295) {

    const char* expectedName = "a_very_long_name_that_might_test_the_boundaries_of_string_handling_in_this_function";

    Object nameObj; // Assume this is properly initialized with the expectedName

    LinkNamed link(&nameObj);

    build_named(&action, &link);



    EXPECT_STREQ(action.named.named_dest, expectedName);

    g_free(action.named.named_dest); // Clean up allocated memory

}
