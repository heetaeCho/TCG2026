// File: tests/XmlReporter_SectionEnded_840.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

#include <catch2/reporters/catch_reporter_xml.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_totals.hpp>

// Minimal includes for SectionInfo/SourceLineInfo if needed by your setup:
#include <catch2/catch_test_common.hpp>
#include <catch2/catch_user_config.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>

using ::testing::Return;
using ::testing::NiceMock;

namespace {

// ---- Mock config that lets us control showDurations() ----
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));

    // The base in this project snapshot declares virtuals but not pure-virtuals.
    // We can simply inherit defaults for everything else.
};

// Helper to make a basic SectionInfo with dummy values.
// Only the name & line are typically needed; description can be empty.
inline Catch::SectionInfo makeSectionInfo(const char* name = "S", const char* file = "file.cpp", std::size_t line = 123) {
    return Catch::SectionInfo{
        Catch::StringRef{name},
        Catch::SourceLineInfo{file, static_cast<std::uint32_t>(line)},
        Catch::StringRef{} // description
    };
}

// Helper to build SectionStats with given counts & duration
inline Catch::SectionStats makeSectionStats(const Catch::Counts& counts,
                                            double durationSec = 0.0,
                                            bool missing = false) {
    return Catch::SectionStats{
        makeSectionInfo(),
        counts,
        durationSec,
        missing
    };
}

// Construct an XmlReporter that writes to an ostringstream and uses our mock config.
struct XmlReporterFixture : public ::testing::Test {
    std::ostringstream out;
    NiceMock<MockConfig> cfg;

    // ReporterConfig is movable; construct with (config*, stream).
    std::unique_ptr<Catch::XmlReporter> makeReporter() {
        Catch::ReporterConfig rc{ &cfg, out };
        return std::make_unique<Catch::XmlReporter>(std::move(rc));
    }

    // Drive sectionStarting to increase section depth without asserting on its output.
    static void pushSection(Catch::XmlReporter& rep, const char* name = "S") {
        rep.sectionStarting(makeSectionInfo(name));
    }
};

} // namespace

// --- Tests ---

// Normal path: depth after decrement remains > 0 -> <OverallResults> is emitted,
// and with ShowDurations::Always the duration attribute must be present.
// Also validates skipped="true" when counts.skipped > 0.
TEST_F(XmlReporterFixture, SectionEnded_EmitsOverallResults_WithDuration_AndSkippedTrue_840) {
    using namespace Catch;

    ON_CALL(cfg, showDurations()).WillByDefault(Return(ShowDurations::Always));

    auto rep = makeReporter();

    // Prepare depth: start 2 nested sections so that after one end, depth > 0
    pushSection(*rep, "outer");
    pushSection(*rep, "inner");

    Counts c;
    c.passed = 2;
    c.failed = 1;
    c.failedButOk = 3;
    c.skipped = 5; // > 0 -> skipped="true"

    rep->sectionEnded(makeSectionStats(c, /*durationSec*/ 1.2345, /*missing*/ false));

    const std::string xml = out.str();
    // Presence of OverallResults with expected attributes (order not enforced)
    EXPECT_THAT(xml, ::testing::HasSubstr("<OverallResults"));
    EXPECT_THAT(xml, ::testing::HasSubstr("successes=\"2\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("failures=\"1\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("expectedFailures=\"3\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("skipped=\"true\""));

    // Duration attribute present when ShowDurations::Always
    EXPECT_THAT(xml, ::testing::HasSubstr("durationInSeconds=\""));
}

// Boundary: when skipped == 0, the attribute should be "false".
// Duration is still Always, so durationInSeconds should appear.
TEST_F(XmlReporterFixture, SectionEnded_SkippedFalse_WhenZero_840) {
    using namespace Catch;

    ON_CALL(cfg, showDurations()).WillByDefault(Return(ShowDurations::Always));

    auto rep = makeReporter();

    // Make sure depth after decrement stays > 0
    pushSection(*rep, "outer");
    pushSection(*rep, "inner");

    Counts c;
    c.passed = 0;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0; // -> skipped="false"

    rep->sectionEnded(makeSectionStats(c, /*durationSec*/ 0.0, /*missing*/ false));

    const std::string xml = out.str();
    EXPECT_THAT(xml, ::testing::HasSubstr("<OverallResults"));
    EXPECT_THAT(xml, ::testing::HasSubstr("successes=\"0\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("failures=\"0\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("expectedFailures=\"0\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("skipped=\"false\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("durationInSeconds=\""));
}

// Exceptional-ish observable: when ending the *last* open section (depth becomes 0),
// XmlReporter::sectionEnded SHOULD NOT emit <OverallResults> (per provided code path).
TEST_F(XmlReporterFixture, SectionEnded_DoesNotEmitOverallResults_WhenClosingLastSection_840) {
    using namespace Catch;

    // Duration setting irrelevant here; verify absence of OverallResults.
    ON_CALL(cfg, showDurations()).WillByDefault(Return(ShowDurations::Always));

    auto rep = makeReporter();

    // Only one open section -> after --m_sectionDepth, result is 0
    pushSection(*rep, "only");

    Counts c;
    c.passed = 1;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;

    rep->sectionEnded(makeSectionStats(c, /*durationSec*/ 0.5, /*missing*/ false));

    const std::string xml = out.str();
    EXPECT_THAT(xml, ::testing::Not(::testing::HasSubstr("<OverallResults")));
}

// Duration visibility: if config->showDurations() is not Always,
// durationInSeconds attribute should not be present even when depth > 0.
TEST_F(XmlReporterFixture, SectionEnded_OmitsDuration_WhenNotAlways_840) {
    using namespace Catch;

    ON_CALL(cfg, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));

    auto rep = makeReporter();

    // Ensure depth after decrement > 0
    pushSection(*rep, "outer");
    pushSection(*rep, "inner");

    Counts c;
    c.passed = 4;
    c.failed = 0;
    c.failedButOk = 1;
    c.skipped = 0;

    rep->sectionEnded(makeSectionStats(c, /*durationSec*/ 9.99, /*missing*/ false));

    const std::string xml = out.str();
    EXPECT_THAT(xml, ::testing::HasSubstr("<OverallResults"));
    EXPECT_THAT(xml, ::testing::HasSubstr("successes=\"4\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("expectedFailures=\"1\""));
    // No duration attribute when not Always
    EXPECT_THAT(xml, ::testing::Not(::testing::HasSubstr("durationInSeconds=\"")));
}

