// File: tests/cumulative_reporter_sectionEnded_859_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

// Catch2 headers — paths may differ slightly in your tree
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"

using namespace Catch;

// A tiny concrete reporter we can instantiate for testing. We don’t
// override any behavior; we only need a public constructor that forwards
// to CumulativeReporterBase’s ctor so we can call sectionStarting/Ended.
class TestCumulativeReporter_859 final : public CumulativeReporterBase {
public:
    explicit TestCumulativeReporter_859( ReporterConfig&& cfg )
        : CumulativeReporterBase( std::move(cfg) ) {}
};

// Small helpers to create minimal-but-valid SectionStats via public APIs.
// These do not re-implement any logic; they just construct the inputs.
static SectionInfo makeSectionInfo_859(const std::string& name) {
    // Description can be empty; line info can be a dummy file/line.
    return SectionInfo{
        SourceLineInfo{ "dummy.cpp", 123 },
        name,
        std::string{} // description
    };
}

static Counts makeCounts_859() {
    // Zero counts are fine for these tests; we are not asserting on them.
    return Counts{ 0, 0, 0, 0 };
}

static SectionStats makeSectionStats_859(const std::string& name) {
    SectionInfo si = makeSectionInfo_859(name);
    Counts cnt = makeCounts_859();
    // durationInSeconds can be zero; missingAssertions is arbitrary for our purpose.
    return SectionStats{ std::move(si), cnt, 0.0, false };
}

// Builds a minimal ReporterConfig required by CumulativeReporterBase.
// We use an ostringstream as the output sink; config uses defaults.
static ReporterConfig makeReporterConfig_859(std::ostream& os) {
    // Construct a minimal ConfigData and Config to satisfy ReporterConfig.
    // We rely on public Catch2 interfaces only.
    Catch::ConfigData data;
    auto cfg = Catch::Detail::make_unique<Catch::Config>(data);

    // ReporterConfig typically takes (Config const&, std::ostream&).
    // If your version differs, adjust this forwarding accordingly.
    return ReporterConfig{ *cfg, os };
}

// ---------- Tests ----------

TEST(CumulativeReporter_sectionEnded_859, SectionEndedWithoutPriorStart_TriggersAssert_859) {
#ifndef NDEBUG
    std::ostringstream sink;
    auto rc = makeReporterConfig_859(sink);
    TestCumulativeReporter_859 rep{ std::move(rc) };

    // No prior sectionStarting → sectionEnded must assert-crash.
    SectionStats stats = makeSectionStats_859("S1");

    ASSERT_DEATH_IF_SUPPORTED({
        rep.sectionEnded(stats);
    }, ""); // We don't rely on a specific assert message.
#else
    GTEST_SKIP() << "Asserts disabled in Release; skipping death test.";
#endif
}

TEST(CumulativeReporter_sectionEnded_859, EndingTwiceAfterSingleStart_DiesOnSecondEnd_859) {
#ifndef NDEBUG
    std::ostringstream sink;
    auto rc = makeReporterConfig_859(sink);
    TestCumulativeReporter_859 rep{ std::move(rc) };

    // Start one section
    SectionInfo si = makeSectionInfo_859("S1");
    rep.sectionStarting(si);

    // First end should be fine.
    SectionStats stats = makeSectionStats_859("S1");
    ASSERT_NO_FATAL_FAILURE(rep.sectionEnded(stats));

    // Second end without another start should assert (stack now empty if pop worked).
    ASSERT_DEATH_IF_SUPPORTED({
        rep.sectionEnded(stats);
    }, "");
#else
    GTEST_SKIP() << "Asserts disabled in Release; skipping death test.";
#endif
}

TEST(CumulativeReporter_sectionEnded_859, NestedSections_EndInLIFOOrder_NoDeath_859) {
    std::ostringstream sink;
    auto rc = makeReporterConfig_859(sink);
    TestCumulativeReporter_859 rep{ std::move(rc) };

    // Start nested sections: S1 -> S2
    SectionInfo s1 = makeSectionInfo_859("S1");
    SectionInfo s2 = makeSectionInfo_859("S2");
    rep.sectionStarting(s1);
    rep.sectionStarting(s2);

    // End innermost first (S2), then outer (S1) — should not assert.
    SectionStats st2 = makeSectionStats_859("S2");
    SectionStats st1 = makeSectionStats_859("S1");

    ASSERT_NO_FATAL_FAILURE(rep.sectionEnded(st2));
    ASSERT_NO_FATAL_FAILURE(rep.sectionEnded(st1));
}

