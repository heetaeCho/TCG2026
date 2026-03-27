// File: tests/SonarQubeReporter_writeAssertions_831.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>

// Headers under test (paths follow your snippets; adjust include paths as needed)
#include "catch2/reporters/catch_reporter_sonarqube.hpp"
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"

using ::testing::_;
using ::testing::Exactly;
using ::testing::InSequence;
using ::testing::Sequence;

// Minimal aliases to shorten names in tests
using Catch::SonarQubeReporter;
using Catch::CumulativeReporterBase;
using Catch::Detail::AssertionOrBenchmarkResult;

// If writeAssertion is not virtual in your build, add a test seam by deriving
// and declaring writeAssertion as virtual in this test-only subclass.
class MockSonarQubeReporter : public SonarQubeReporter {
public:
    // Helper: forward a minimal ReporterConfig to base.
    // Adjust this to your actual ReporterConfig signature if needed.
    explicit MockSonarQubeReporter(Catch::ReporterConfig&& cfg)
        : SonarQubeReporter(std::move(cfg)) {}

    // Test seam to observe calls coming from writeAssertions
    MOCK_METHOD(void, writeAssertion, (const Catch::AssertionStats& stats, bool okToFail), (override));
};

// --- Tiny helpers to build inputs purely via the public interfaces ---

// Builds a SectionNode with the provided AssertionOrBenchmarkResult items
static CumulativeReporterBase::SectionNode makeSectionNodeWith(
    const std::vector<AssertionOrBenchmarkResult>& items,
    const Catch::SectionStats& stats = Catch::SectionStats{}
) {
    CumulativeReporterBase::SectionNode node(stats);
    node.assertionsAndBenchmarks = items; // public per interface
    return node;
}

// Creates AOBR from assertion stats (public ctor per interface)
static AssertionOrBenchmarkResult asA(const Catch::AssertionStats& s) {
    return AssertionOrBenchmarkResult(s);
}

// Creates AOBR from benchmark stats (public ctor per interface)
static AssertionOrBenchmarkResult asB(const Catch::BenchmarkStats<>& b) {
    return AssertionOrBenchmarkResult(b);
}

// Helper to create a minimally valid ReporterConfig for SonarQubeReporter.
// Adjust to your codebase’s actual ReporterConfig ctor if signatures differ.
static Catch::ReporterConfig makeConfig(std::ostream& os) {
    // The real Catch2 ReporterConfig typically needs IConfig, a stream ref, and maybe colour mode.
    // Provide the simplest viable setup here; tweak as required in your tree.
    // If you have a factory/helper already, prefer using it instead.
    struct DummyConfig : Catch::IConfig {
        // Provide no-op implementations as needed by your Catch version.
        // Keep this minimal and *only* to satisfy type requirements.
        bool allowThrows() const override { return true; }
        // Add other required pure-virtuals for your version if compilation demands it.
    };
    static DummyConfig dummyCfg;
    return Catch::ReporterConfig(dummyCfg, os);
}

// ========================= TESTS =========================

TEST(SonarQubeReporter_writeAssertions_831, EmptySection_NoCalls_831) {
    std::ostringstream oss;
    MockSonarQubeReporter rep(makeConfig(oss));

    auto section = makeSectionNodeWith({});
    EXPECT_CALL(rep, writeAssertion(_, _)).Times(0);

    rep.writeAssertions(section, /*okToFail=*/false);
}

TEST(SonarQubeReporter_writeAssertions_831, OnlyBenchmarks_NoCalls_831) {
    std::ostringstream oss;
    MockSonarQubeReporter rep(makeConfig(oss));

    Catch::BenchmarkStats<> b1{}, b2{};
    auto section = makeSectionNodeWith({ asB(b1), asB(b2) });

    EXPECT_CALL(rep, writeAssertion(_, _)).Times(0);
    rep.writeAssertions(section, /*okToFail=*/true);
}

TEST(SonarQubeReporter_writeAssertions_831, OnlyAssertions_ForwardsOkToFailTrue_AndCountMatches_831) {
    std::ostringstream oss;
    MockSonarQubeReporter rep(makeConfig(oss));

    Catch::AssertionStats a1{}, a2{}, a3{};
    auto section = makeSectionNodeWith({ asA(a1), asA(a2), asA(a3) });

    // okToFail must be forwarded unchanged
    EXPECT_CALL(rep, writeAssertion(_, true)).Times(Exactly(3));
    rep.writeAssertions(section, /*okToFail=*/true);
}

TEST(SonarQubeReporter_writeAssertions_831, Mixed_OnlyAssertionsCalled_InInputOrder_AndForwardsOkToFailFalse_831) {
    std::ostringstream oss;
    MockSonarQubeReporter rep(makeConfig(oss));

    Catch::AssertionStats a1{}, a2{};
    Catch::BenchmarkStats<> b{};
    // Intentionally interleave: A, B, A
    auto section = makeSectionNodeWith({ asA(a1), asB(b), asA(a2) });

    // Calls should happen only for assertions and in the same order they appear
    Sequence seq;
    EXPECT_CALL(rep, writeAssertion(_, false)).InSequence(seq);
    EXPECT_CALL(rep, writeAssertion(_, false)).InSequence(seq);

    rep.writeAssertions(section, /*okToFail=*/false);
}
