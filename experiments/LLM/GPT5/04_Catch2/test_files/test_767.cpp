// File: tests/console_reporter_sectionEnded_767.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/internal/catch_console_colour.hpp>
#include <catch2/internal/catch_config.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>
#include <sstream>

using ::testing::HasSubstr;

namespace {

struct OStringStreamWrapper : Catch::IStream {
    std::ostringstream oss;
    std::ostream& stream() override { return oss; }
    ~OStringStreamWrapper() override = default;
};

// Helper to build a real ConsoleReporter with a controllable output stream
// and a configurable ShowDurations mode (purely via public interfaces).
struct ReporterUnderTest {
    std::unique_ptr<Catch::ConsoleReporter> reporter;
    OStringStreamWrapper* out = nullptr; // non-owning
    std::shared_ptr<Catch::Config> cfg;  // keep config alive

    explicit ReporterUnderTest(Catch::ShowDurations showDurations) {
        Catch::ConfigData data;
        data.showDurations = showDurations; // controls shouldShowDuration via IConfig
        cfg = std::make_shared<Catch::Config>(data);

        auto streamPtr = new OStringStreamWrapper();
        out = streamPtr;

        Catch::Detail::unique_ptr<Catch::IStream> ustream(streamPtr);
        Catch::ReporterConfig rc(
            cfg.get(),
            CATCH_MOVE(ustream),
            Catch::ColourMode::None,
            {} /* custom options */
        );
        reporter = std::make_unique<Catch::ConsoleReporter>(std::move(rc));
    }
};

// Convenience for creating SectionStats via the public constructor
static Catch::SectionStats makeStats(const std::string& name,
                                     double durationSeconds,
                                     bool missingAssertions) {
    Catch::SectionInfo info{ Catch::SourceLineInfo{ "file.cpp", 123 }, name };
    Catch::Counts counts{}; // default counts; content is not relevant for these tests
    return Catch::SectionStats{ std::move(info), counts, durationSeconds, missingAssertions };
}

} // namespace

// ============== Tests ==============

TEST(ConsoleReporterSectionEnded_767, MissingAssertions_PrintsNoAssertionsInTestCase_WhenTopLevel_767) {
    ReporterUnderTest rut{ Catch::ShowDurations::Never }; // avoid duration noise

    // Simulate a single (top-level) section so size() <= 1 at the moment of sectionEnded
    Catch::SectionInfo topInfo{ Catch::SourceLineInfo{ "t.cpp", 10 }, "TopCase" };
    rut.reporter->sectionStarting(topInfo);

    auto stats = makeStats("TopCase", /*dur*/0.0, /*missingAssertions*/true);
    rut.reporter->sectionEnded(stats);

    const std::string out = rut.out->oss.str();
    // Observable behavior: exact message prefix + quoted section/test case name
    EXPECT_THAT(out, HasSubstr("\nNo assertions in test case 'TopCase'"));
}

TEST(ConsoleReporterSectionEnded_767, MissingAssertions_PrintsNoAssertionsInSection_WhenNested_767) {
    ReporterUnderTest rut{ Catch::ShowDurations::Never }; // avoid duration noise

    // Push an outer and an inner section before ending the inner to ensure stack size > 1
    Catch::SectionInfo outer{ Catch::SourceLineInfo{ "t.cpp", 11 }, "Outer" };
    Catch::SectionInfo inner{ Catch::SourceLineInfo{ "t.cpp", 12 }, "Inner" };
    rut.reporter->sectionStarting(outer);
    rut.reporter->sectionStarting(inner);

    auto stats = makeStats("Inner", /*dur*/0.0, /*missingAssertions*/true);
    rut.reporter->sectionEnded(stats);

    const std::string out = rut.out->oss.str();
    EXPECT_THAT(out, HasSubstr("\nNo assertions in section 'Inner'"));
}

TEST(ConsoleReporterSectionEnded_767, Duration_PrintsWhenConfiguredAlways_767) {
    ReporterUnderTest rut{ Catch::ShowDurations::Always }; // request durations

    Catch::SectionInfo si{ Catch::SourceLineInfo{ "t.cpp", 20 }, "Durable" };
    rut.reporter->sectionStarting(si);

    // Non-missing assertions so only duration line is relevant
    auto stats = makeStats("Durable", /*dur*/0.123, /*missingAssertions*/false);
    rut.reporter->sectionEnded(stats);

    const std::string out = rut.out->oss.str();
    // We do not assert on exact numeric formatting from getFormattedDuration,
    // only that the " s: <name>" pattern appears (observable contract).
    EXPECT_THAT(out, HasSubstr(" s: Durable"));
}
