#include <gtest/gtest.h>

#include "catch_amalgamated.cpp"



using namespace Catch;

using namespace Detail;



class TestCaseInfoTest_994 : public ::testing::Test {

protected:

    StringRef className = "TestClass";

    NameAndTags nameAndTags = {"TestName", "[Tag1][Tag2]"};

    SourceLineInfo lineInfo = {"test_file.cpp", 42};



    unique_ptr<TestCaseInfo> testCaseInfo;



    void SetUp() override {

        testCaseInfo = makeTestCaseInfo(className, nameAndTags, lineInfo);

    }

};



TEST_F(TestCaseInfoTest_994, ClassNameIsSetCorrectly_994) {

    EXPECT_EQ(testCaseInfo->getClassName(), className);

}



TEST_F(TestCaseInfoTest_994, NameAndTagsAreSetCorrectly_994) {

    EXPECT_EQ(testCaseInfo->getName(), nameAndTags.name);

    EXPECT_EQ(testCaseInfo->getTags(), nameAndTags.tags);

}



TEST_F(TestCaseInfoTest_994, SourceLineInfoIsSetCorrectly_994) {

    EXPECT_EQ(testCaseInfo->getLineInfo().file, lineInfo.file);

    EXPECT_EQ(testCaseInfo->getLineInfo().line, lineInfo.line);

}



TEST_F(TestCaseInfoTest_994, DefaultConstructorCreatesEmptyTestCaseInfo_994) {

    unique_ptr<TestCaseInfo> defaultTestCaseInfo = make_unique<TestCaseInfo>(StringRef(), NameAndTags(), SourceLineInfo());

    EXPECT_TRUE(defaultTestCaseInfo->getClassName().empty());

    EXPECT_TRUE(defaultTestCaseInfo->getName().empty());

    EXPECT_TRUE(defaultTestCaseInfo->getTags().empty());

    EXPECT_EQ(defaultTestCaseInfo->getLineInfo().file, nullptr);

    EXPECT_EQ(defaultTestCaseInfo->getLineInfo().line, 0);

}



TEST_F(TestCaseInfoTest_994, TestCaseInfoWithEmptyStrings_994) {

    StringRef emptyClassName;

    NameAndTags emptyNameAndTags = {"", ""};

    SourceLineInfo emptyLineInfo = {"", 0};



    unique_ptr<TestCaseInfo> emptyTestCaseInfo = makeTestCaseInfo(emptyClassName, emptyNameAndTags, emptyLineInfo);

    EXPECT_TRUE(emptyTestCaseInfo->getClassName().empty());

    EXPECT_TRUE(emptyTestCaseInfo->getName().empty());

    EXPECT_TRUE(emptyTestCaseInfo->getTags().empty());

    EXPECT_EQ(emptyTestCaseInfo->getLineInfo().file, nullptr);

    EXPECT_EQ(emptyTestCaseInfo->getLineInfo().line, 0);

}



TEST_F(TestCaseInfoTest_994, TestCaseInfoWithNullStrings_994) {

    StringRef nullClassName(nullptr);

    NameAndTags nullNameAndTags = {StringRef(nullptr), StringRef(nullptr)};

    SourceLineInfo nullLineInfo(nullptr, 0);



    unique_ptr<TestCaseInfo> nullTestCaseInfo = makeTestCaseInfo(nullClassName, nullNameAndTags, nullLineInfo);

    EXPECT_TRUE(nullTestCaseInfo->getClassName().empty());

    EXPECT_TRUE(nullTestCaseInfo->getName().empty());

    EXPECT_TRUE(nullTestCaseInfo->getTags().empty());

    EXPECT_EQ(nullTestCaseInfo->getLineInfo().file, nullptr);

    EXPECT_EQ(nullTestCaseInfo->getLineInfo().line, 0);

}
