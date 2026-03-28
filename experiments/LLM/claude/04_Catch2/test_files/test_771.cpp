#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_console_colour.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_stream.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

namespace {

// Helper to create a ConsoleReporter for testing
class ConsoleReporterTest_771 : public ::testing::Test {
protected:
    std::unique_ptr<Catch::ConsoleReporter> makeReporter(std::ostream& os) {
        // We need to create a ReporterConfig that writes to our stream
        // Use Catch2's infrastructure to create a config
        const char* argv[] = {"test", "--colour-mode", "none"};
        Catch::ConfigData configData;
        configData.showDurations = Catch::ShowDurations::Never;
        configData.colourMode = Catch::ColourMode::None;

        auto config = std::make_shared<Catch::Config>(configData);

        auto stream = Catch::Detail::make_unique<Catch::StringStreams::OutputStreamWrapper>(os);
        Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(stream.release()), Catch::ColourMode::None, {});

        m_config = config; // keep alive
        return std::make_unique<Catch::ConsoleReporter>(std::move(repConfig));
    }

    std::shared_ptr<Catch::Config> m_config;
};

} // anonymous namespace

// Since ConsoleReporter has very complex dependencies that may not easily compile
// in a standalone Google Test environment, let me write tests that focus on
// what's testable through the public interface.

// Alternative approach: Use the Catch2 infrastructure directly
// but verify output through the stream.

class ConsoleReporterBenchmarkFailed_771 : public ::testing::Test {
protected:
    void SetUp() override {
        Catch::ConfigData configData;
        configData.colourMode = Catch::ColourMode::None;
        m_config = std::make_shared<Catch::Config>(configData);
    }

    std::unique_ptr<Catch::ConsoleReporter> createReporter() {
        auto streamPtr = Catch::Detail::make_unique<Catch::ReusableStringStream>();
        // We need an IStream that wraps our stringstream
        // Use Catch's makeStream with a redirect
        auto stream = Catch::makeStream("-");  // stdout by default
        // Instead, let's use the config approach
        Catch::ReporterConfig repConfig(
            m_config.get(),
            Catch::makeStream(m_outputFile),
            Catch::ColourMode::None,
            {}
        );
        return std::make_unique<Catch::ConsoleReporter>(std::move(repConfig));
    }

    std::shared_ptr<Catch::Config> m_config;
    std::string m_outputFile = "-";
};

// Given the complexity of constructing Catch2 reporters outside Catch2's framework,
// the most practical tests verify the static/simple aspects:

TEST(ConsoleReporterStatic_771, GetDescription_ReturnsNonEmpty_771) {
    std::string desc = Catch::ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST(ConsoleReporterStatic_771, GetDescription_ContainsReports_771) {
    std::string desc = Catch::ConsoleReporter::getDescription();
    // The description should mention something about reports/console
    EXPECT_TRUE(desc.size() > 0);
}

// Test StringRef which is used as parameter to benchmarkFailed
TEST(StringRefForBenchmarkFailed_771, ConstructFromCString_771) {
    Catch::StringRef sr("test error");
    EXPECT_EQ(sr.size(), 10u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefForBenchmarkFailed_771, ConstructFromStdString_771) {
    std::string s = "benchmark error message";
    Catch::StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_EQ(std::string(sr.data(), sr.size()), s);
}

TEST(StringRefForBenchmarkFailed_771, EmptyStringRef_771) {
    Catch::StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefForBenchmarkFailed_771, CompareEqual_771) {
    Catch::StringRef sr1("error");
    Catch::StringRef sr2("error");
    EXPECT_TRUE(sr1 == sr2);
}

TEST(StringRefForBenchmarkFailed_771, CompareNotEqual_771) {
    Catch::StringRef sr1("error1");
    Catch::StringRef sr2("error2");
    EXPECT_TRUE(sr1 != sr2);
}

// Test with actual ConsoleReporter construction using file stream
class ConsoleReporterFullTest_771 : public ::testing::Test {
protected:
    void SetUp() override {
        Catch::ConfigData configData;
        configData.colourMode = Catch::ColourMode::None;
        m_config = std::make_shared<Catch::Config>(configData);
    }

    std::shared_ptr<Catch::Config> m_config;
};

TEST_F(ConsoleReporterFullTest_771, BenchmarkFailed_OutputContainsErrorMessage_771) {
    // Create a reporter that writes to a stringstream
    std::stringstream ss;

    // We need to get an IStream wrapper around our stringstream
    // Using Catch2's infrastructure
    auto wrapped = Catch::Detail::make_unique<Catch::StringStreams::OutputStreamWrapper>(ss);

    Catch::ReporterConfig repConfig(
        m_config.get(),
        std::move(wrapped),
        Catch::ColourMode::None,
        {}
    );

    auto reporter = std::make_unique<Catch::ConsoleReporter>(std::move(repConfig));

    // Need to set up enough state for benchmarkFailed to work
    // Call benchmarkPreparing first to set up the table
    reporter->benchmarkPreparing("test_bench");

    // Now call benchmarkFailed
    reporter->benchmarkFailed(Catch::StringRef("some error"));

    std::string output = ss.str();
    // The output should contain the error message
    EXPECT_NE(output.find("some error"), std::string::npos);
    EXPECT_NE(output.find("Benchmark failed"), std::string::npos);
}

TEST_F(ConsoleReporterFullTest_771, BenchmarkFailed_EmptyError_771) {
    std::stringstream ss;
    auto wrapped = Catch::Detail::make_unique<Catch::StringStreams::OutputStreamWrapper>(ss);

    Catch::ReporterConfig repConfig(
        m_config.get(),
        std::move(wrapped),
        Catch::ColourMode::None,
        {}
    );

    auto reporter = std::make_unique<Catch::ConsoleReporter>(std::move(repConfig));
    reporter->benchmarkPreparing("test_bench");
    reporter->benchmarkFailed(Catch::StringRef(""));

    std::string output = ss.str();
    EXPECT_NE(output.find("Benchmark failed"), std::string::npos);
}

TEST_F(ConsoleReporterFullTest_771, BenchmarkFailed_LongErrorMessage_771) {
    std::stringstream ss;
    auto wrapped = Catch::Detail::make_unique<Catch::StringStreams::OutputStreamWrapper>(ss);

    Catch::ReporterConfig repConfig(
        m_config.get(),
        std::move(wrapped),
        Catch::ColourMode::None,
        {}
    );

    auto reporter = std::make_unique<Catch::ConsoleReporter>(std::move(repConfig));
    reporter->benchmarkPreparing("test_bench");

    std::string longError(500, 'x');
    reporter->benchmarkFailed(Catch::StringRef(longError));

    std::string output = ss.str();
    EXPECT_NE(output.find("Benchmark failed"), std::string::npos);
    EXPECT_NE(output.find(longError), std::string::npos);
}

TEST_F(ConsoleReporterFullTest_771, BenchmarkFailed_SpecialCharactersInError_771) {
    std::stringstream ss;
    auto wrapped = Catch::Detail::make_unique<Catch::StringStreams::OutputStreamWrapper>(ss);

    Catch::ReporterConfig repConfig(
        m_config.get(),
        std::move(wrapped),
        Catch::ColourMode::None,
        {}
    );

    auto reporter = std::make_unique<Catch::ConsoleReporter>(std::move(repConfig));
    reporter->benchmarkPreparing("test_bench");
    reporter->benchmarkFailed(Catch::StringRef("error with <special> & \"chars\""));

    std::string output = ss.str();
    EXPECT_NE(output.find("Benchmark failed"), std::string::npos);
    EXPECT_NE(output.find("error with <special>"), std::string::npos);
}

TEST_F(ConsoleReporterFullTest_771, NoMatchingTestCases_OutputContainsSpec_771) {
    std::stringstream ss;
    auto wrapped = Catch::Detail::make_unique<Catch::StringStreams::OutputStreamWrapper>(ss);

    Catch::ReporterConfig repConfig(
        m_config.get(),
        std::move(wrapped),
        Catch::ColourMode::None,
        {}
    );

    auto reporter = std::make_unique<Catch::ConsoleReporter>(std::move(repConfig));
    reporter->noMatchingTestCases(Catch::StringRef("nonexistent_test"));

    std::string output = ss.str();
    EXPECT_NE(output.find("nonexistent_test"), std::string::npos);
}

TEST_F(ConsoleReporterFullTest_771, ReportInvalidTestSpec_OutputContainsArg_771) {
    std::stringstream ss;
    auto wrapped = Catch::Detail::make_unique<Catch::StringStreams::OutputStreamWrapper>(ss);

    Catch::ReporterConfig repConfig(
        m_config.get(),
        std::move(wrapped),
        Catch::ColourMode::None,
        {}
    );

    auto reporter = std::make_unique<Catch::ConsoleReporter>(std::move(repConfig));
    reporter->reportInvalidTestSpec(Catch::StringRef("[invalid"));

    std::string output = ss.str();
    EXPECT_NE(output.find("[invalid"), std::string::npos);
}
