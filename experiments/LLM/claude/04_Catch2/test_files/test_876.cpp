#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_istream.hpp"

using namespace Catch;

namespace {

// Helper to create a minimal config for the reporter
class MockConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_sr; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    unsigned int rngSeed() const override { return 0; }
    UseColour colourMode() const override { return UseColour::No; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<TestSpec> const& getTestsOrTags() const override {
        static std::vector<TestSpec> empty;
        return empty;
    }
    bool hasTestFilters() const override { return false; }
    bool isFiltered() const override { return false; }
    Verbosity verbosity() const override { return Verbosity::Normal; }
};

// Simple test invoker stub
class StubInvoker : public ITestInvoker {
public:
    void invoke() const override {}
};

class JsonReporterTest_876 : public ::testing::Test {
protected:
    void SetUp() override {
        m_stream = std::make_unique<std::ostringstream>();
        m_config = std::make_shared<MockConfig>();
    }

    std::unique_ptr<JsonReporter> createReporter() {
        // We need to create ReporterConfig with our stream and config
        auto reporterConfig = ReporterConfig(m_config.get(), m_stream.get(), ColourMode::None, {});
        auto reporter = std::make_unique<JsonReporter>(std::move(reporterConfig));
        return reporter;
    }

    std::string getOutput() const {
        return m_stream->str();
    }

    std::unique_ptr<std::ostringstream> m_stream;
    std::shared_ptr<MockConfig> m_config;
};

} // anonymous namespace

TEST_F(JsonReporterTest_876, ListTestsEmptyVector_876) {
    auto reporter = createReporter();
    std::vector<TestCaseHandle> tests;
    
    reporter->listTests(tests);
    
    std::string output = getOutput();
    // With empty tests, we should still get valid JSON structure with an empty tests array
    EXPECT_THAT(output, ::testing::HasSubstr("tests"));
}

TEST_F(JsonReporterTest_876, ListTestsSingleTest_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    SourceLineInfo lineInfo("test_file.cpp", 42);
    NameAndTags nameAndTags("TestName", "[tag1]");
    TestCaseInfo info("TestClass", nameAndTags, lineInfo);
    TestCaseHandle handle(&info, &invoker);
    
    std::vector<TestCaseHandle> tests;
    tests.push_back(handle);
    
    reporter->listTests(tests);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("TestName"));
    EXPECT_THAT(output, ::testing::HasSubstr("TestClass"));
    EXPECT_THAT(output, ::testing::HasSubstr("test_file.cpp"));
    EXPECT_THAT(output, ::testing::HasSubstr("tag1"));
}

TEST_F(JsonReporterTest_876, ListTestsMultipleTests_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    
    SourceLineInfo lineInfo1("file1.cpp", 10);
    NameAndTags nameAndTags1("Test1", "[tag1]");
    TestCaseInfo info1("Class1", nameAndTags1, lineInfo1);
    TestCaseHandle handle1(&info1, &invoker);
    
    SourceLineInfo lineInfo2("file2.cpp", 20);
    NameAndTags nameAndTags2("Test2", "[tag2]");
    TestCaseInfo info2("Class2", nameAndTags2, lineInfo2);
    TestCaseHandle handle2(&info2, &invoker);
    
    std::vector<TestCaseHandle> tests;
    tests.push_back(handle1);
    tests.push_back(handle2);
    
    reporter->listTests(tests);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("Test1"));
    EXPECT_THAT(output, ::testing::HasSubstr("Test2"));
    EXPECT_THAT(output, ::testing::HasSubstr("Class1"));
    EXPECT_THAT(output, ::testing::HasSubstr("Class2"));
    EXPECT_THAT(output, ::testing::HasSubstr("file1.cpp"));
    EXPECT_THAT(output, ::testing::HasSubstr("file2.cpp"));
}

TEST_F(JsonReporterTest_876, ListTestsWithMultipleTags_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    SourceLineInfo lineInfo("test.cpp", 5);
    NameAndTags nameAndTags("TaggedTest", "[alpha][beta][gamma]");
    TestCaseInfo info("MyClass", nameAndTags, lineInfo);
    TestCaseHandle handle(&info, &invoker);
    
    std::vector<TestCaseHandle> tests;
    tests.push_back(handle);
    
    reporter->listTests(tests);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("TaggedTest"));
    EXPECT_THAT(output, ::testing::HasSubstr("alpha"));
    EXPECT_THAT(output, ::testing::HasSubstr("beta"));
    EXPECT_THAT(output, ::testing::HasSubstr("gamma"));
    EXPECT_THAT(output, ::testing::HasSubstr("tags"));
}

TEST_F(JsonReporterTest_876, ListTestsWithNoTags_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    SourceLineInfo lineInfo("notags.cpp", 1);
    NameAndTags nameAndTags("NoTagTest", "");
    TestCaseInfo info("NoTagClass", nameAndTags, lineInfo);
    TestCaseHandle handle(&info, &invoker);
    
    std::vector<TestCaseHandle> tests;
    tests.push_back(handle);
    
    reporter->listTests(tests);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("NoTagTest"));
    EXPECT_THAT(output, ::testing::HasSubstr("NoTagClass"));
    EXPECT_THAT(output, ::testing::HasSubstr("tags"));
}

TEST_F(JsonReporterTest_876, ListTestsContainsNameField_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    SourceLineInfo lineInfo("src.cpp", 100);
    NameAndTags nameAndTags("SpecificTestName", "");
    TestCaseInfo info("SpecificClassName", nameAndTags, lineInfo);
    TestCaseHandle handle(&info, &invoker);
    
    std::vector<TestCaseHandle> tests;
    tests.push_back(handle);
    
    reporter->listTests(tests);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("\"name\""));
    EXPECT_THAT(output, ::testing::HasSubstr("\"class-name\""));
    EXPECT_THAT(output, ::testing::HasSubstr("\"tags\""));
}

TEST_F(JsonReporterTest_876, ListTestsContainsSourceInfo_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    SourceLineInfo lineInfo("myfile.cpp", 256);
    NameAndTags nameAndTags("SourceInfoTest", "");
    TestCaseInfo info("SrcClass", nameAndTags, lineInfo);
    TestCaseHandle handle(&info, &invoker);
    
    std::vector<TestCaseHandle> tests;
    tests.push_back(handle);
    
    reporter->listTests(tests);
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("myfile.cpp"));
    EXPECT_THAT(output, ::testing::HasSubstr("256"));
}

TEST_F(JsonReporterTest_876, ListTestsOutputIsValidStructure_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    SourceLineInfo lineInfo("valid.cpp", 1);
    NameAndTags nameAndTags("ValidTest", "[valid]");
    TestCaseInfo info("ValidClass", nameAndTags, lineInfo);
    TestCaseHandle handle(&info, &invoker);
    
    std::vector<TestCaseHandle> tests;
    tests.push_back(handle);
    
    reporter->listTests(tests);
    
    std::string output = getOutput();
    // JSON output should contain braces and brackets
    EXPECT_THAT(output, ::testing::HasSubstr("{"));
    EXPECT_THAT(output, ::testing::HasSubstr("}"));
    EXPECT_THAT(output, ::testing::HasSubstr("["));
    EXPECT_THAT(output, ::testing::HasSubstr("]"));
}

TEST_F(JsonReporterTest_876, GetDescriptionReturnsNonEmpty_876) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(JsonReporterTest_876, ListTestsWithSpecialCharactersInName_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    SourceLineInfo lineInfo("special.cpp", 1);
    NameAndTags nameAndTags("Test with \"quotes\" and \\backslash", "");
    TestCaseInfo info("ClassName", nameAndTags, lineInfo);
    TestCaseHandle handle(&info, &invoker);
    
    std::vector<TestCaseHandle> tests;
    tests.push_back(handle);
    
    // Should not crash
    EXPECT_NO_THROW(reporter->listTests(tests));
    
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_876, ListTestsLargeNumberOfTests_876) {
    auto reporter = createReporter();
    
    StubInvoker invoker;
    
    std::vector<std::unique_ptr<TestCaseInfo>> infos;
    std::vector<TestCaseHandle> tests;
    
    for (int i = 0; i < 100; ++i) {
        std::string name = "Test_" + std::to_string(i);
        std::string className = "Class_" + std::to_string(i);
        SourceLineInfo lineInfo("bulk.cpp", static_cast<std::size_t>(i + 1));
        NameAndTags nameAndTags(name, "[bulk]");
        auto info = std::make_unique<TestCaseInfo>(StringRef(className), nameAndTags, lineInfo);
        tests.push_back(TestCaseHandle(info.get(), &invoker));
        infos.push_back(std::move(info));
    }
    
    EXPECT_NO_THROW(reporter->listTests(tests));
    
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("Test_0"));
    EXPECT_THAT(output, ::testing::HasSubstr("Test_99"));
}
