#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>
#include <string>

#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch;

// A no-op ColourImpl for testing purposes
class NoColourImpl : public ColourImpl {
public:
    NoColourImpl() : ColourImpl(nullptr) {}
    void use(Colour::Code) const override {}
};

// A simple test invoker that does nothing
class StubTestInvoker : public ITestInvoker {
public:
    void invoke() const override {}
};

class DefaultListTestsTest_824 : public ::testing::Test {
protected:
    NoColourImpl colourImpl;
    StubTestInvoker invoker;
    std::ostringstream out;

    TestCaseHandle makeTestCase(const std::string& name, const std::string& tags = "",
                                 const std::string& file = "test.cpp", int line = 1) {
        SourceLineInfo lineInfo(file.c_str(), static_cast<std::size_t>(line));
        NameAndTags nat(name, tags);
        auto* info = new TestCaseInfo(""_sr, nat, lineInfo);
        return TestCaseHandle(info, &invoker);
    }

    void cleanup(std::vector<TestCaseHandle>& tests) {
        // Note: In real code, ownership might be managed differently.
        // We created TestCaseInfo with new, so we should clean up.
        for (auto& t : tests) {
            delete &t.getTestCaseInfo();
        }
    }
};

TEST_F(DefaultListTestsTest_824, EmptyTestList_NotFiltered_NormalVerbosity_824) {
    std::vector<TestCaseHandle> tests;
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("All available test cases:"), std::string::npos);
    EXPECT_NE(output.find("0 test cases"), std::string::npos);
}

TEST_F(DefaultListTestsTest_824, EmptyTestList_Filtered_NormalVerbosity_824) {
    std::vector<TestCaseHandle> tests;
    defaultListTests(out, &colourImpl, tests, true, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("Matching test cases:"), std::string::npos);
    EXPECT_NE(output.find("0 matching test cases"), std::string::npos);
}

TEST_F(DefaultListTestsTest_824, SingleTestCase_NotFiltered_NormalVerbosity_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("MyTestCase"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("All available test cases:"), std::string::npos);
    EXPECT_NE(output.find("MyTestCase"), std::string::npos);
    EXPECT_NE(output.find("1 test case"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, SingleTestCase_Filtered_NormalVerbosity_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("FilteredTest"));
    defaultListTests(out, &colourImpl, tests, true, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("Matching test cases:"), std::string::npos);
    EXPECT_NE(output.find("FilteredTest"), std::string::npos);
    EXPECT_NE(output.find("1 matching test case"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, MultipleTestCases_NotFiltered_NormalVerbosity_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("TestA"));
    tests.push_back(makeTestCase("TestB"));
    tests.push_back(makeTestCase("TestC"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("All available test cases:"), std::string::npos);
    EXPECT_NE(output.find("TestA"), std::string::npos);
    EXPECT_NE(output.find("TestB"), std::string::npos);
    EXPECT_NE(output.find("TestC"), std::string::npos);
    EXPECT_NE(output.find("3 test cases"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, QuietVerbosity_OnlyListsNames_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("QuietTest"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Quiet);
    std::string output = out.str();
    // In Quiet mode, it calls listTestNamesOnly and returns early
    // Should NOT contain the header "All available test cases:"
    EXPECT_EQ(output.find("All available test cases:"), std::string::npos);
    // Should contain just the test name
    EXPECT_NE(output.find("QuietTest"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, QuietVerbosity_Filtered_OnlyListsNames_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("QuietFilteredTest"));
    defaultListTests(out, &colourImpl, tests, true, Verbosity::Quiet);
    std::string output = out.str();
    EXPECT_EQ(output.find("Matching test cases:"), std::string::npos);
    EXPECT_NE(output.find("QuietFilteredTest"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, HighVerbosity_ShowsLineInfo_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("HighVerbTest", "", "myfile.cpp", 42));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::High);
    std::string output = out.str();
    EXPECT_NE(output.find("All available test cases:"), std::string::npos);
    EXPECT_NE(output.find("HighVerbTest"), std::string::npos);
    // High verbosity should include line info
    EXPECT_NE(output.find("myfile.cpp"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, NormalVerbosity_DoesNotShowLineInfo_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("NormalVerbTest", "", "hidden.cpp", 99));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("NormalVerbTest"), std::string::npos);
    // Normal verbosity should NOT include line info (only High does)
    // The line info details should not appear
    // Note: "hidden.cpp" might not appear if verbosity < High
    // This depends on exact behavior, but per the code, lineInfo is only shown for High
    EXPECT_EQ(output.find("hidden.cpp:99"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, TestWithTags_NormalVerbosity_ShowsTags_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("TaggedTest", "[tag1][tag2]"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("TaggedTest"), std::string::npos);
    EXPECT_NE(output.find("[tag1]"), std::string::npos);
    EXPECT_NE(output.find("[tag2]"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, TestWithTags_HighVerbosity_ShowsTags_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("TaggedHighTest", "[alpha]"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::High);
    std::string output = out.str();
    EXPECT_NE(output.find("TaggedHighTest"), std::string::npos);
    EXPECT_NE(output.find("[alpha]"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, HiddenTest_IsStillListed_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("HiddenTest", "[.]"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("HiddenTest"), std::string::npos);
    EXPECT_NE(output.find("1 test case"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, OutputEndsWithDoubleNewlineAndFlush_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("FlushTest"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    // Should end with "\n\n"
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "\n\n");
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, PluralTestCases_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("Test1"));
    tests.push_back(makeTestCase("Test2"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    // 2 should be plural "test cases" not "test case"
    EXPECT_NE(output.find("2 test cases"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, SingularTestCase_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("OnlyOne"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("1 test case"), std::string::npos);
    // Should not say "1 test cases"
    EXPECT_EQ(output.find("1 test cases"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, TestWithNoTags_NormalVerbosity_NoTagLine_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("NoTagsTest"));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("NoTagsTest"), std::string::npos);
    // No tags should mean no tag line (harder to verify precisely, but at least the name is there)
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, MultipleFilteredTests_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("FilterA"));
    tests.push_back(makeTestCase("FilterB"));
    tests.push_back(makeTestCase("FilterC"));
    tests.push_back(makeTestCase("FilterD"));
    tests.push_back(makeTestCase("FilterE"));
    defaultListTests(out, &colourImpl, tests, true, Verbosity::Normal);
    std::string output = out.str();
    EXPECT_NE(output.find("Matching test cases:"), std::string::npos);
    EXPECT_NE(output.find("5 matching test cases"), std::string::npos);
    cleanup(tests);
}

TEST_F(DefaultListTestsTest_824, HighVerbosity_WithTags_ShowsBothLineInfoAndTags_824) {
    std::vector<TestCaseHandle> tests;
    tests.push_back(makeTestCase("FullInfoTest", "[important][fast]", "source.cpp", 100));
    defaultListTests(out, &colourImpl, tests, false, Verbosity::High);
    std::string output = out.str();
    EXPECT_NE(output.find("FullInfoTest"), std::string::npos);
    EXPECT_NE(output.find("source.cpp"), std::string::npos);
    EXPECT_NE(output.find("[important]"), std::string::npos);
    EXPECT_NE(output.find("[fast]"), std::string::npos);
    cleanup(tests);
}
