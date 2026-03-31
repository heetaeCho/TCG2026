#include <catch2/reporters/catch_reporter_compact.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_istream.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_totals.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <memory>
#include <string>

using namespace Catch;

// We need a way to create a CompactReporter with a controlled config and stream.
// The approach: create a real config that controls showDurations, and capture stream output.

namespace {

// A simple stream wrapper that writes to a given ostream
class StringStream : public Catch::IStream {
public:
    StringStream(std::ostream& os) : m_os(os) {}
    std::ostream& stream() override { return m_os; }
private:
    std::ostream& m_os;
};

// Helper to create SectionInfo
SectionInfo makeSectionInfo(const std::string& name) {
    return SectionInfo(SourceLineInfo("file.cpp", 1), name);
}

// Helper to create SectionStats
SectionStats makeSectionStats(const std::string& name, double duration) {
    return SectionStats(
        SectionInfo(SourceLineInfo("file.cpp", 1), name),
        Counts(),
        duration,
        false
    );
}

} // anonymous namespace

class CompactReporterTest_815 : public ::testing::Test {
protected:
    void SetUp() override {}

    std::unique_ptr<CompactReporter> createReporter(
        bool showDurations,
        std::ostream& os)
    {
        // Build argv for config
        // If showDurations is true, pass --durations yes
        std::vector<const char*> args;
        args.push_back("test");
        if (showDurations) {
            args.push_back("--durations");
            args.push_back("yes");
        }

        // We need to create a real config. This is tricky since Catch2's config
        // requires specific setup. Let's try using ConfigData directly.
        auto configData = Catch::ConfigData();
        if (showDurations) {
            configData.showDurations = Catch::ShowDurations::Always;
        } else {
            configData.showDurations = Catch::ShowDurations::Never;
        }

        m_config = std::make_shared<Catch::Config>(configData);

        auto streamPtr = Catch::Detail::make_unique<StringStream>(os);

        auto reporterConfig = ReporterConfig(
            m_config.get(),
            std::move(streamPtr),
            Catch::ColourMode::None,
            std::map<std::string, std::string>{}
        );

        return std::make_unique<CompactReporter>(std::move(reporterConfig));
    }

    std::shared_ptr<Catch::Config> m_config;
};

TEST_F(CompactReporterTest_815, SectionEndedShowsDurationWhenEnabled_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats = makeSectionStats("TestSection", 1.5);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    // Should contain the section name and duration info
    EXPECT_TRUE(output.find("TestSection") != std::string::npos)
        << "Output was: " << output;
    EXPECT_TRUE(output.find("s:") != std::string::npos)
        << "Output was: " << output;
}

TEST_F(CompactReporterTest_815, SectionEndedHidesDurationWhenDisabled_815) {
    std::ostringstream oss;
    auto reporter = createReporter(false, oss);

    auto stats = makeSectionStats("TestSection", 0.0);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    // With durations set to Never and 0.0 duration, should not show
    EXPECT_TRUE(output.find("TestSection") == std::string::npos)
        << "Output was: " << output;
}

TEST_F(CompactReporterTest_815, SectionEndedWithZeroDurationShowsWhenAlways_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats = makeSectionStats("ZeroDuration", 0.0);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("ZeroDuration") != std::string::npos)
        << "Output was: " << output;
}

TEST_F(CompactReporterTest_815, SectionEndedWithVerySmallDuration_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats = makeSectionStats("SmallDuration", 0.000001);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("SmallDuration") != std::string::npos)
        << "Output was: " << output;
    EXPECT_TRUE(output.find("s:") != std::string::npos)
        << "Output was: " << output;
}

TEST_F(CompactReporterTest_815, SectionEndedWithLargeDuration_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats = makeSectionStats("LargeDuration", 9999.999);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("LargeDuration") != std::string::npos)
        << "Output was: " << output;
}

TEST_F(CompactReporterTest_815, SectionEndedOutputEndsWithNewline_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats = makeSectionStats("NewlineTest", 1.0);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    if (!output.empty()) {
        EXPECT_EQ(output.back(), '\n')
            << "Output was: " << output;
    }
}

TEST_F(CompactReporterTest_815, SectionEndedWithEmptySectionName_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats = makeSectionStats("", 1.0);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    // Should still produce output with "s:" even if name is empty
    EXPECT_TRUE(output.find("s:") != std::string::npos)
        << "Output was: " << output;
}

TEST_F(CompactReporterTest_815, SectionEndedMultipleCallsAppendOutput_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats1 = makeSectionStats("First", 1.0);
    auto stats2 = makeSectionStats("Second", 2.0);
    reporter->sectionEnded(stats1);
    reporter->sectionEnded(stats2);

    std::string output = oss.str();
    EXPECT_TRUE(output.find("First") != std::string::npos)
        << "Output was: " << output;
    EXPECT_TRUE(output.find("Second") != std::string::npos)
        << "Output was: " << output;
}

TEST_F(CompactReporterTest_815, SectionEndedNoDurationNeverShows_815) {
    std::ostringstream oss;
    auto reporter = createReporter(false, oss);

    auto stats = makeSectionStats("Hidden", 5.0);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    // With ShowDurations::Never, even non-zero durations may not be shown
    // (depends on shouldShowDuration logic, but we test observable behavior)
    // This is a boundary test for the "never show" mode
    // We just verify the output doesn't crash and is consistent
    // Note: with Never mode, shouldShowDuration should return false
    EXPECT_TRUE(output.find("Hidden") == std::string::npos)
        << "Expected no output but got: " << output;
}

TEST_F(CompactReporterTest_815, GetDescriptionReturnsNonEmpty_815) {
    std::string desc = CompactReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(CompactReporterTest_815, SectionEndedWithNegativeDuration_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats = makeSectionStats("NegativeDuration", -1.0);
    reporter->sectionEnded(stats);

    // Should not crash; output behavior is implementation-defined
    // but we verify no exception is thrown
    std::string output = oss.str();
    // Just verify it didn't crash
    SUCCEED();
}

TEST_F(CompactReporterTest_815, SectionEndedOutputContainsDurationValue_815) {
    std::ostringstream oss;
    auto reporter = createReporter(true, oss);

    auto stats = makeSectionStats("DurationCheck", 2.5);
    reporter->sectionEnded(stats);

    std::string output = oss.str();
    // The output should contain some representation of the duration
    // and the " s: " separator
    EXPECT_TRUE(output.find(" s: ") != std::string::npos)
        << "Output was: " << output;
    EXPECT_TRUE(output.find("DurationCheck") != std::string::npos)
        << "Output was: " << output;
}
