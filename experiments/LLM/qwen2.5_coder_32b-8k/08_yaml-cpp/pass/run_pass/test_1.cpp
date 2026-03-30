#include <gtest/gtest.h>

#include "directives.h"



namespace YAML {



class DirectivesTest_1 : public ::testing::Test {

protected:

    Directives directives;

};



TEST_F(DirectivesTest_1, TranslateTagHandle_UnknownHandle_ReturnsOriginal_1) {

    EXPECT_EQ(directives.TranslateTagHandle("!unknown"), "!unknown");

}



TEST_F(DirectivesTest_1, TranslateTagHandle_DefaultSecondaryHandle_ReturnsExpanded_1) {

    EXPECT_EQ(directives.TranslateTagHandle("!!"), "tag:yaml.org,2002:");

}



TEST_F(DirectivesTest_1, TranslateTagHandle_KnownHandle_ReturnsMappedValue_1) {

    directives.tags["!custom"] = "http://example.com/custom";

    EXPECT_EQ(directives.TranslateTagHandle("!custom"), "http://example.com/custom");

}



TEST_F(DirectivesTest_1, TranslateTagHandle_EmptyString_ReturnsEmptyString_1) {

    EXPECT_EQ(directives.TranslateTagHandle(""), "");

}



} // namespace YAML
