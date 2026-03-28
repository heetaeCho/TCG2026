#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"

#include <string>



class VerbatimTagTest_15 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed

    }



    void TearDown() override {

        // Cleanup can be done here if needed

    }

};



TEST_F(VerbatimTagTest_15, VerbatimTag_ReturnsCorrectType_15) {

    YAML::_Tag tag = YAML::VerbatimTag("test");

    EXPECT_EQ(tag.type(), YAML::_Tag::Type::Verbatim);

}



TEST_F(VerbatimTagTest_15, VerbatimTag_CorrectlySetsContent_15) {

    std::string content = "sample_content";

    YAML::_Tag tag = YAML::VerbatimTag(content);

    EXPECT_EQ(tag.content(), content);

}



TEST_F(VerbatimTagTest_15, VerbatimTag_EmptyStringAsContent_15) {

    YAML::_Tag tag = YAML::VerbatimTag("");

    EXPECT_EQ(tag.content(), "");

}



TEST_F(VerbatimTagTest_15, VerbatimTag_LargeStringContent_15) {

    std::string large_content(1024, 'a'); // Large string of 1024 'a's

    YAML::_Tag tag = YAML::VerbatimTag(large_content);

    EXPECT_EQ(tag.content(), large_content);

}
