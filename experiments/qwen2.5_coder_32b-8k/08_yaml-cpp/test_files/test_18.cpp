#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"



// Test fixture for _Tag related tests

class TagTest_18 : public ::testing::Test {

protected:

    using TagType = YAML::_Tag;

};



// Test to verify that SecondaryTag constructs a _Tag with correct parameters - Normal operation

TEST_F(TagTest_18, SecondaryTag_ConstructsCorrectly_18) {

    std::string content = "testContent";

    TagType tag = YAML::SecondaryTag(content);

    EXPECT_EQ(tag.handle(), "");

    EXPECT_EQ(tag.content(), content);

    EXPECT_EQ(tag.type(), TagType::Type::NamedHandle);

}



// Test to verify that SecondaryTag handles empty string correctly - Boundary condition

TEST_F(TagTest_18, SecondaryTag_EmptyString_18) {

    std::string content = "";

    TagType tag = YAML::SecondaryTag(content);

    EXPECT_EQ(tag.handle(), "");

    EXPECT_EQ(tag.content(), content);

    EXPECT_EQ(tag.type(), TagType::Type::NamedHandle);

}



// Test to verify that SecondaryTag handles long string correctly - Boundary condition

TEST_F(TagTest_18, SecondaryTag_LongString_18) {

    std::string content(1024, 'a'); // Long string of 1024 'a's

    TagType tag = YAML::SecondaryTag(content);

    EXPECT_EQ(tag.handle(), "");

    EXPECT_EQ(tag.content(), content);

    EXPECT_EQ(tag.type(), TagType::Type::NamedHandle);

}
