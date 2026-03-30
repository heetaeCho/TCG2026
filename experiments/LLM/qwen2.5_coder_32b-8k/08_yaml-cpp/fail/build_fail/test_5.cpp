#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tag.h"

#include "directives.h"



using namespace YAML;

using ::testing::Return;



class TagTest_5 : public ::testing::Test {

protected:

    Directives directivesMock;

};



TEST_F(TagTest_5, TranslateVerbatimTag_5) {

    Tag tag{VERBATIM, "", "example"};

    EXPECT_EQ(tag.Translate(directivesMock), "example");

}



TEST_F(TagTest_5, TranslatePrimaryHandleTag_5) {

    EXPECT_CALL(directivesMock, TranslateTagHandle("!")).WillOnce(Return("http://primary/"));

    Tag tag{PRIMARY_HANDLE, "", "example"};

    EXPECT_EQ(tag.Translate(directivesMock), "http://primary/example");

}



TEST_F(TagTest_5, TranslateSecondaryHandleTag_5) {

    EXPECT_CALL(directivesMock, TranslateTagHandle("!!")).WillOnce(Return("http://secondary/"));

    Tag tag{SECONDARY_HANDLE, "", "example"};

    EXPECT_EQ(tag.Translate(directivesMock), "http://secondary/example");

}



TEST_F(TagTest_5, TranslateNamedHandleTag_5) {

    EXPECT_CALL(directivesMock, TranslateTagHandle("!custom!")).WillOnce(Return("http://custom/"));

    Tag tag{NAMED_HANDLE, "custom", "example"};

    EXPECT_EQ(tag.Translate(directivesMock), "http://custom/example");

}



TEST_F(TagTest_5, TranslateNonSpecificTag_5) {

    Tag tag{NON_SPECIFIC, "", ""};

    EXPECT_EQ(tag.Translate(directivesMock), "!");

}



TEST_F(TagTest_5, TranslateInvalidTagTypeThrowsException_5) {

    Tag invalidTag{static_cast<TYPE>(5), "", ""}; // Assuming 5 is an invalid type

    EXPECT_THROW(invalidTag.Translate(directivesMock), std::runtime_error);

}
