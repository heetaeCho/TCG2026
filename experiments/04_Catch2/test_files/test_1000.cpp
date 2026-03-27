#include <gtest/gtest.h>

#include "catch_test_case_info.hpp"

#include <string>



using namespace Catch;



TEST_F(TestCaseInfoTest_1000, EmptyTagsAsString_1000) {

    TestCaseInfo testCase(StringRef("ClassName"), NameAndTags(), SourceLineInfo("", 0));

    EXPECT_EQ(testCase.tagsAsString(), "");

}



TEST_F(TestCaseInfoTest_1000, SingleTagAsString_1000) {

    Tag tag(StringRef("[tag]"));

    TestCaseInfo testCase(StringRef("ClassName"), NameAndTags("[tag]"), SourceLineInfo("", 0));

    testCase.internalAppendTag(tag.original);

    EXPECT_EQ(testCase.tagsAsString(), "[tag]");

}



TEST_F(TestCaseInfoTest_1000, MultipleTagsAsString_1000) {

    Tag tag1(StringRef("[tag1]"));

    Tag tag2(StringRef("[tag2]"));

    TestCaseInfo testCase(StringRef("ClassName"), NameAndTags("[tag1][tag2]"), SourceLineInfo("", 0));

    testCase.internalAppendTag(tag1.original);

    testCase.internalAppendTag(tag2.original);

    EXPECT_EQ(testCase.tagsAsString(), "[tag1][tag2]");

}



TEST_F(TestCaseInfoTest_1000, TagsWithSpacesAsString_1000) {

    Tag tag(StringRef("[ tag ]"));

    TestCaseInfo testCase(StringRef("ClassName"), NameAndTags("[ tag ]"), SourceLineInfo("", 0));

    testCase.internalAppendTag(tag.original);

    EXPECT_EQ(testCase.tagsAsString(), "[tag]");

}



TEST_F(TestCaseInfoTest_1000, TagsWithSpecialCharactersAsString_1000) {

    Tag tag(StringRef("[@#$%^&*()]"));

    TestCaseInfo testCase(StringRef("ClassName"), NameAndTags("[@#$%^&*()]"), SourceLineInfo("", 0));

    testCase.internalAppendTag(tag.original);

    EXPECT_EQ(testCase.tagsAsString(), "[@#$%^&*()]]");

}



TEST_F(TestCaseInfoTest_1000, TagsWithEmptyString_1000) {

    Tag tag(StringRef(""));

    TestCaseInfo testCase(StringRef("ClassName"), NameAndTags(""), SourceLineInfo("", 0));

    testCase.internalAppendTag(tag.original);

    EXPECT_EQ(testCase.tagsAsString(), "[]");

}
