#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"



using namespace Catch;

using ::testing::Eq;



TEST(TestCaseInfoTest_1001, DefaultConstructorInitializesValues_1001) {

    TestCaseInfo info(StringRef("TestClass"), NameAndTags(), SourceLineInfo());

    EXPECT_EQ(info.className.empty(), true);

    EXPECT_EQ(info.tags.size(), 0);

}



TEST(TestCaseInfoTest_1001, ConstructorWithClassNameSetsClassName_1001) {

    TestCaseInfo info(StringRef("TestClass"), NameAndTags(), SourceLineInfo());

    EXPECT_EQ(info.className, StringRef("TestClass"));

}



TEST(TestCaseInfoTest_1001, ConstructorWithNameAndTagsSetsName_1001) {

    NameAndTags nameAndTags;

    nameAndTags.name = "MyTestCase";

    TestCaseInfo info(StringRef("TestClass"), nameAndTags, SourceLineInfo());

    EXPECT_EQ(info.name, StringRef("MyTestCase"));

}



TEST(TestCaseInfoTest_1001, ConstructorWithEmptyNameCreatesDefaultName_1001) {

    NameAndTags nameAndTags;

    TestCaseInfo info(StringRef("TestClass"), nameAndTags, SourceLineInfo());

    EXPECT_FALSE(info.name.empty());

}



TEST(TestCaseInfoTest_1001, CompareOperatorComparesNamesFirst_1001) {

    TestCaseInfo info1(StringRef("TestClass"), NameAndTags(), SourceLineInfo());

    NameAndTags nameAndTags;

    nameAndTags.name = "MyTestCase";

    TestCaseInfo info2(StringRef("TestClass"), nameAndTags, SourceLineInfo());



    EXPECT_TRUE(info1 < info2);

}



TEST(TestCaseInfoTest_1001, CompareOperatorComparesClassNamesIfNamesAreEqual_1001) {

    NameAndTags nameAndTags;

    nameAndTags.name = "MyTestCase";

    TestCaseInfo info1(StringRef("TestClass1"), nameAndTags, SourceLineInfo());

    TestCaseInfo info2(StringRef("TestClass2"), nameAndTags, SourceLineInfo());



    EXPECT_TRUE(info1 < info2);

}



TEST(TestCaseInfoTest_1001, CompareOperatorComparesTagsIfClassNamesAndNamesAreEqual_1001) {

    NameAndTags nameAndTags;

    nameAndTags.name = "MyTestCase";

    TestCaseInfo info1(StringRef("TestClass"), nameAndTags, SourceLineInfo());

    TestCaseInfo info2(StringRef("TestClass"), nameAndTags, SourceLineInfo());



    // Tags are still empty but this test is to demonstrate the concept

    EXPECT_FALSE(info1 < info2);

}



TEST(TestCaseInfoTest_1001, AddFilenameTagAppendsFilenameTag_1001) {

    TestCaseInfo info(StringRef("TestClass"), NameAndTags(), SourceLineInfo());

    info.addFilenameTag();

    EXPECT_TRUE(info.tagsAsString().find("[file:") != std::string::npos);

}



TEST(TestCaseInfoTest_1001, IsHiddenReturnsFalseByDefault_1001) {

    TestCaseInfo info(StringRef("TestClass"), NameAndTags(), SourceLineInfo());

    EXPECT_FALSE(info.isHidden());

}



TEST(TestCaseInfoTest_1001, ThrowsReturnsFalseByDefault_1001) {

    TestCaseInfo info(StringRef("TestClass"), NameAndTags(), SourceLineInfo());

    EXPECT_FALSE(info.throws());

}



TEST(TestCaseInfoTest_1001, OkToFailReturnsFalseByDefault_1001) {

    TestCaseInfo info(StringRef("TestClass"), NameAndTags(), SourceLineInfo());

    EXPECT_FALSE(info.okToFail());

}



TEST(TestCaseInfoTest_1001, ExpectedToFailReturnsFalseByDefault_1001) {

    TestCaseInfo info(StringRef("TestClass"), NameAndTags(), SourceLineInfo());

    EXPECT_FALSE(info.expectedToFail());

}
