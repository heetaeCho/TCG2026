#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_info.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_source_line_info.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



using namespace Catch;



TEST(TestCaseInfoTest_1113, Constructor_DefaultName_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("", NameAndTags(), lineInfo);



    EXPECT_EQ(testCase.name.empty(), true);

}



TEST(TestCaseInfoTest_1113, Constructor_CustomName_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags("test_name"), lineInfo);



    EXPECT_STREQ(testCase.name.c_str(), "test_name");

}



TEST(TestCaseInfoTest_1113, Constructor_CustomTags_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags("", "[tag1][tag2]"), lineInfo);



    EXPECT_EQ(testCase.tags.size(), 2);

    EXPECT_STREQ(testCase.tags[0].name.c_str(), "tag1");

    EXPECT_STREQ(testCase.tags[1].name.c_str(), "tag2");

}



TEST(TestCaseInfoTest_1113, IsHidden_Default_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags(""), lineInfo);



    EXPECT_EQ(testCase.isHidden(), false);

}



TEST(TestCaseInfoTest_1113, IsHidden_HiddenTag_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags("", "[.hidden]"), lineInfo);



    EXPECT_EQ(testCase.isHidden(), true);

}



TEST(TestCaseInfoTest_1113, TagsAsString_NoTags_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags(""), lineInfo);



    EXPECT_STREQ(testCase.tagsAsString().c_str(), "");

}



TEST(TestCaseInfoTest_1113, TagsAsString_MultipleTags_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags("", "[tag1][tag2]"), lineInfo);



    EXPECT_STREQ(testCase.tagsAsString().c_str(), "tag1,tag2");

}



TEST(TestCaseInfoTest_1113, InternalAppendTag_SingleTag_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags(""), lineInfo);



    testCase.internalAppendTag(StringRef("single_tag"));



    EXPECT_EQ(testCase.tags.size(), 1);

    EXPECT_STREQ(testCase.tags[0].name.c_str(), "single_tag");

}



TEST(TestCaseInfoTest_1113, InternalAppendTag_MultipleTags_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags("", "[tag1]"), lineInfo);



    testCase.internalAppendTag(StringRef("tag2"));



    EXPECT_EQ(testCase.tags.size(), 2);

    EXPECT_STREQ(testCase.tags[0].name.c_str(), "tag1");

    EXPECT_STREQ(testCase.tags[1].name.c_str(), "tag2");

}



TEST(TestCaseInfoTest_1113, InternalAppendTag_DuplicateTags_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags("", "[tag1]"), lineInfo);



    testCase.internalAppendTag(StringRef("tag1"));



    EXPECT_EQ(testCase.tags.size(), 1); // Tags are unique

    EXPECT_STREQ(testCase.tags[0].name.c_str(), "tag1");

}



TEST(TestCaseInfoTest_1113, AddFilenameTag_SingleTag_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags(""), lineInfo);



    testCase.addFilenameTag();



    EXPECT_EQ(testCase.tags.size(), 1);

    EXPECT_STREQ(testCase.tags[0].name.c_str(), "file_cpp");

}



TEST(TestCaseInfoTest_1113, AddFilenameTag_MultipleTags_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase("ClassName", NameAndTags("", "[tag1]"), lineInfo);



    testCase.addFilenameTag();



    EXPECT_EQ(testCase.tags.size(), 2);

    EXPECT_STREQ(testCase.tags[0].name.c_str(), "tag1");

    EXPECT_STREQ(testCase.tags[1].name.c_str(), "file_cpp");

}



TEST(TestCaseInfoTest_1113, Comparison_OperatorLessThan_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase1("ClassName", NameAndTags("test1"), lineInfo);

    TestCaseInfo testCase2("ClassName", NameAndTags("test2"), lineInfo);



    EXPECT_EQ(testCase1 < testCase2, true);

}



TEST(TestCaseInfoTest_1113, Comparison_OperatorEqual_1113) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TestCaseInfo testCase1("ClassName", NameAndTags("test"), lineInfo);

    TestCaseInfo testCase2("ClassName", NameAndTags("test"), lineInfo);



    EXPECT_EQ(testCase1 == testCase2, true);

}
