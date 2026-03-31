#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/internal/catch_stream.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_tag_alias_autoregistrar.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_istream.hpp>

#include <sstream>
#include <memory>
#include <vector>
#include <string>

namespace {

// Helper to create a ReporterConfig with a stringstream-based stream
class StringStreamWrapper : public Catch::IStream {
public:
    std::ostream& stream() override { return m_ss; }
    std::stringstream m_ss;
};

// A concrete subclass of ReporterBase for testing, since ReporterBase
// may be abstract (inherits from IEventListener)
class TestableReporter : public Catch::ReporterBase {
public:
    using Catch::ReporterBase::ReporterBase;

    // Implement pure virtual methods from IEventListener that ReporterBase doesn't implement
    void testRunStarting(Catch::TestRunInfo const&) override {}
    void testCaseStarting(Catch::TestCaseInfo const&) override {}
    void testCasePartialStarting(Catch::TestCaseInfo const&, uint64_t) override {}
    void sectionStarting(Catch::SectionInfo const&) override {}
    void assertionStarting(Catch::AssertionInfo const&) override {}
    void assertionEnded(Catch::AssertionStats const&) override {}
    void sectionEnded(Catch::SectionStats const&) override {}
    void testCasePartialEnded(Catch::TestCaseStats const&, uint64_t) override {}
    void testCaseEnded(Catch::TestCaseStats const&) override {}
    void testRunEnded(Catch::TestRunStats const&) override {}
    void benchmarkPreparing(Catch::StringRef) override {}
    void benchmarkStarting(Catch::BenchmarkInfo const&) override {}
    void benchmarkEnded(Catch::BenchmarkStats<> const&) override {}
    void benchmarkFailed(Catch::StringRef) override {}
    void testGroupStarting(Catch::GroupInfo const&) override {}
    void testGroupEnded(Catch::TestGroupStats const&) override {}
    void fatalErrorEncountered(Catch::StringRef) override {}
    void noMatchingTestCases(Catch::StringRef) override {}
    void reportInvalidTestSpec(Catch::StringRef) override {}
    void skipTest(Catch::TestCaseInfo const&) override {}
};

class ReporterBaseTest_778 : public ::testing::Test {
protected:
    void SetUp() override {
        // Build minimal argv for Catch::Config
        const char* argv[] = {"test_app"};
        Catch::ConfigData configData;
        configData.showHelp = false;

        m_config = std::make_shared<Catch::Config>(configData);

        auto streamWrapper = Catch::Detail::make_unique<StringStreamWrapper>();
        m_rawStream = streamWrapper.get();

        Catch::ReporterConfig reporterConfig(
            m_config.get(),
            CATCH_MOVE(streamWrapper),
            Catch::ColourMode::None,
            {}
        );

        m_reporter = std::make_unique<TestableReporter>(CATCH_MOVE(reporterConfig));
    }

    StringStreamWrapper* m_rawStream = nullptr;
    std::shared_ptr<Catch::Config> m_config;
    std::unique_ptr<TestableReporter> m_reporter;

    std::string getOutput() const {
        return m_rawStream->m_ss.str();
    }
};

// Test: listListeners with empty vector produces some output (or at least doesn't crash)
TEST_F(ReporterBaseTest_778, ListListenersEmpty_778) {
    std::vector<Catch::ListenerDescription> descriptions;
    m_reporter->listListeners(descriptions);
    // Should not crash; output may or may not be empty depending on implementation
    // but the call should succeed
    SUCCEED();
}

// Test: listListeners with one entry produces output containing the listener name
TEST_F(ReporterBaseTest_778, ListListenersSingleEntry_778) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "TestListener";
    desc.description = "A test listener";
    descriptions.push_back(desc);

    m_reporter->listListeners(descriptions);
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("TestListener"));
}

// Test: listListeners with multiple entries produces output containing all names
TEST_F(ReporterBaseTest_778, ListListenersMultipleEntries_778) {
    std::vector<Catch::ListenerDescription> descriptions;

    Catch::ListenerDescription desc1;
    desc1.name = "ListenerAlpha";
    desc1.description = "First listener";
    descriptions.push_back(desc1);

    Catch::ListenerDescription desc2;
    desc2.name = "ListenerBeta";
    desc2.description = "Second listener";
    descriptions.push_back(desc2);

    m_reporter->listListeners(descriptions);
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("ListenerAlpha"));
    EXPECT_THAT(output, ::testing::HasSubstr("ListenerBeta"));
}

// Test: listReporters with empty vector
TEST_F(ReporterBaseTest_778, ListReportersEmpty_778) {
    std::vector<Catch::ReporterDescription> descriptions;
    m_reporter->listReporters(descriptions);
    SUCCEED();
}

// Test: listReporters with one entry
TEST_F(ReporterBaseTest_778, ListReportersSingleEntry_778) {
    std::vector<Catch::ReporterDescription> descriptions;
    Catch::ReporterDescription desc;
    desc.name = "TestReporter";
    desc.description = "A test reporter";
    descriptions.push_back(desc);

    m_reporter->listReporters(descriptions);
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("TestReporter"));
}

// Test: listReporters with multiple entries
TEST_F(ReporterBaseTest_778, ListReportersMultipleEntries_778) {
    std::vector<Catch::ReporterDescription> descriptions;

    Catch::ReporterDescription desc1;
    desc1.name = "ReporterOne";
    desc1.description = "First reporter";
    descriptions.push_back(desc1);

    Catch::ReporterDescription desc2;
    desc2.name = "ReporterTwo";
    desc2.description = "Second reporter";
    descriptions.push_back(desc2);

    m_reporter->listReporters(descriptions);
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("ReporterOne"));
    EXPECT_THAT(output, ::testing::HasSubstr("ReporterTwo"));
}

// Test: listTags with empty vector
TEST_F(ReporterBaseTest_778, ListTagsEmpty_778) {
    std::vector<Catch::TagInfo> tags;
    m_reporter->listTags(tags);
    SUCCEED();
}

// Test: listTags with entries
TEST_F(ReporterBaseTest_778, ListTagsSingleEntry_778) {
    std::vector<Catch::TagInfo> tags;
    Catch::TagInfo tagInfo;
    tagInfo.add("test-tag"_catch_sr);
    tags.push_back(tagInfo);

    m_reporter->listTags(tags);
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("test-tag"));
}

// Test: listTests with empty vector
TEST_F(ReporterBaseTest_778, ListTestsEmpty_778) {
    std::vector<Catch::TestCaseHandle> tests;
    m_reporter->listTests(tests);
    SUCCEED();
}

// Test: listListeners description appears in output
TEST_F(ReporterBaseTest_778, ListListenersDescriptionInOutput_778) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "MyListener";
    desc.description = "Does important things";
    descriptions.push_back(desc);

    m_reporter->listListeners(descriptions);
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("Does important things"));
}

// Test: listReporters description appears in output
TEST_F(ReporterBaseTest_778, ListReportersDescriptionInOutput_778) {
    std::vector<Catch::ReporterDescription> descriptions;
    Catch::ReporterDescription desc;
    desc.name = "FancyReporter";
    desc.description = "Produces fancy output";
    descriptions.push_back(desc);

    m_reporter->listReporters(descriptions);
    std::string output = getOutput();
    EXPECT_THAT(output, ::testing::HasSubstr("Produces fancy output"));
}

// Test: Destructor doesn't crash
TEST_F(ReporterBaseTest_778, DestructorDoesNotCrash_778) {
    m_reporter.reset();
    SUCCEED();
}

} // anonymous namespace
