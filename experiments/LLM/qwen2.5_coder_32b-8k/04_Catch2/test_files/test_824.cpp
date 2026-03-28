#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Catch2/reporters/catch_reporter_helpers.hpp>

#include <Catch2/interfaces/catch_interfaces_config.hpp>

#include <Catch2/catch_test_case_info.hpp>

#include <iostream>

#include <vector>



using namespace Catch;

using ::testing::_;

using ::testing::InvokeWithoutArgs;

using ::testing::Return;



class MockColourImpl : public ColourImpl {

public:

    MockColourImpl(std::ostream* stream) : ColourImpl(stream) {}

    MOCK_METHOD(ColourGuard, guardColour, (struct Colour::Code), (override));

};



class MockTestCaseInfo : public TestCaseInfo {

public:

    MockTestCaseInfo(StringRef _className, NameAndTags const& _nameAndTags, SourceLineInfo const& _lineInfo)

        : TestCaseInfo(_className, _nameAndTags, _lineInfo) {}

    MOCK_CONST_METHOD0(isHidden, bool());

    MOCK_CONST_METHOD0(tagsAsString, std::string());

};



class MockTestCaseHandle {

public:

    MockTestCaseHandle() : m_info(new MockTestCaseInfo("", {}, SourceLineInfo())), m_invoker(nullptr) {}

    ~MockTestCaseHandle() { delete m_info; }

    MOCK_CONST_METHOD0(getTestCaseInfo, TestCaseInfo const&());



private:

    TestCaseInfo* m_info;

    ITestInvoker* m_invoker;

};



TEST_F(CatchReporterHelpersTest_824, OutputAllTestsNormalVerbosity_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {MockTestCaseHandle(), MockTestCaseHandle()};

    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);



    EXPECT_THAT(out.str(), testing::HasSubstr("All available test cases:"));

}



TEST_F(CatchReporterHelpersTest_824, OutputMatchingTestsFilteredVerbosity_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {MockTestCaseHandle(), MockTestCaseHandle()};

    defaultListTests(out, &colourImpl, tests, true, Verbosity::Normal);



    EXPECT_THAT(out.str(), testing::HasSubstr("Matching test cases:"));

}



TEST_F(CatchReporterHelpersTest_824, QuietVerbosityListsNamesOnly_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {MockTestCaseHandle(), MockTestCaseHandle()};

    defaultListTests(out, &colourImpl, tests, false, Verbosity::Quiet);



    EXPECT_THAT(out.str(), testing::Not(testing::HasSubstr("All available test cases:")));

}



TEST_F(CatchReporterHelpersTest_824, HighVerbosityIncludesLineInfo_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {MockTestCaseHandle(), MockTestCaseHandle()};

    defaultListTests(out, &colourImpl, tests, false, Verbosity::High);



    EXPECT_THAT(out.str(), testing::HasSubstr(":"));

}



TEST_F(CatchReporterHelpersTest_824, TagsIncludedWhenNotQuietAndVerbose_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {MockTestCaseHandle()};

    EXPECT_CALL(*tests[0].getTestCaseInfo().tagsAsString(), tagsAsString()).WillOnce(Return("tag1,tag2"));

    defaultListTests(out, &colourImpl, tests, false, Verbosity::High);



    EXPECT_THAT(out.str(), testing::HasSubstr("tag1,tag2"));

}



TEST_F(CatchReporterHelpersTest_824, HiddenTestCasesUseSecondaryTextColour_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {MockTestCaseHandle()};

    EXPECT_CALL(tests[0].getTestCaseInfo(), isHidden()).WillOnce(Return(true));

    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);



    EXPECT_CALL(colourImpl, guardColour(Colour::SecondaryText)).Times(1);

}



TEST_F(CatchReporterHelpersTest_824, NormalOperationWithNoTests_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {};

    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);



    EXPECT_THAT(out.str(), testing::HasSubstr("All available test cases:"));

    EXPECT_THAT(out.str(), testing::EndsWith("\n\n"));

}



TEST_F(CatchReporterHelpersTest_824, OutputPluralizationForOneTest_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {MockTestCaseHandle()};

    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);



    EXPECT_THAT(out.str(), testing::HasSubstr("1 test case"));

}



TEST_F(CatchReporterHelpersTest_824, OutputPluralizationForMultipleTests_824) {

    std::ostringstream out;

    MockColourImpl colourImpl(&out);

    std::vector<TestCaseHandle> tests = {MockTestCaseHandle(), MockTestCaseHandle()};

    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);



    EXPECT_THAT(out.str(), testing::HasSubstr("2 test cases"));

}
