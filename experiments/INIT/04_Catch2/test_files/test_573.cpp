// File: tests/TeamCityReporter_sectionStarting_573.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 public headers used by the reporter interface
#include <catch2/reporters/catch_reporter_teamcity.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/catch_test_macros.hpp> // for SourceLineInfo in most Catch2 layouts
#include <catch2/reporters/catch_reporter_streaming_base.hpp>

// NOTE:
// - We only use public types (SectionInfo, SourceLineInfo) and the reporter's public API.
// - No assumptions about internal state are made; we only assert callability and lack of exceptions.
// - Construction of ReporterConfig is done via Catch2's public API. If your project provides a helper
//   to create ReporterConfig, feel free to adapt the fixture's SetUp accordingly.

namespace {

using namespace Catch;

class TeamCityReporterSectionStartingTest_573 : public ::testing::Test {
protected:
    // Minimal plumbing to create a TeamCityReporter with an ostreams sink.
    // Adjust this to match your project's ReporterConfig construction utilities, if needed.
    std::unique_ptr<TeamCityReporter> reporter;
    std::ostringstream sink;

    // Helper to build ReporterConfig using common Catch2 constructs.
    static ReporterConfig makeConfig(std::ostream& os) {
        // In typical Catch2 setups, ReporterConfig takes:
        //   - IConfig const*,
        //   - ColourMode,
        //   - std::ostream&,
        //   - std::vector<ConsoleReporter::ReporterPreferences::CustomOption> (optional),
        // … However the exact ctor varies between Catch2 revisions.
        //
        // For portability across typical Catch2 forks used in CI exercises, we use a light-weight
        // configuration that writes to `os` and relies on defaults elsewhere.
        //
        // If your codebase exposes a helper to assemble ReporterConfig, replace this with it.
        // This keeps the test focused strictly on the public interface of the reporter.
        return ReporterConfig{ /* IConfig* */ nullptr, ColourMode::None, os };
    }

    void SetUp() override {
        ReporterConfig cfg = makeConfig(sink);
        reporter = std::make_unique<TeamCityReporter>(std::move(cfg));
    }

    static SectionInfo makeSectionInfo(const char* file, std::size_t line, std::string name) {
        return SectionInfo{ SourceLineInfo{ file, static_cast<std::size_t>(line) }, std::move(name) };
    }
};

} // namespace

// ----------------------------- Tests ---------------------------------

// Normal path: calling sectionStarting with a typical SectionInfo should be valid and non-throwing.
TEST_F(TeamCityReporterSectionStartingTest_573, SectionStarting_NormalDoesNotThrow_573) {
    auto s = makeSectionInfo("file.cpp", 42, "regular section");
    EXPECT_NO_THROW(reporter->sectionStarting(s));
}

// Boundary: empty section name is accepted by the interface and should not throw.
TEST_F(TeamCityReporterSectionStartingTest_573, SectionStarting_EmptyNameDoesNotThrow_573) {
    auto s = makeSectionInfo("empty.cpp", 1, "");
    EXPECT_NO_THROW(reporter->sectionStarting(s));
}

// Boundary: long section name (stress typical formatting/printing paths). Should not throw.
TEST_F(TeamCityReporterSectionStartingTest_573, SectionStarting_VeryLongNameDoesNotThrow_573) {
    std::string longName(10'000, 'X'); // large but reasonable for a stress boundary
    auto s = makeSectionInfo("long.cpp", 10, longName);
    EXPECT_NO_THROW(reporter->sectionStarting(s));
}

// Unicode / non-ASCII names should be accepted as SectionInfo::name is std::string.
TEST_F(TeamCityReporterSectionStartingTest_573, SectionStarting_NonAsciiNameDoesNotThrow_573) {
    std::string utf8 = u8"섹션🔧/Δ/тест";
    auto s = makeSectionInfo("utf8.cpp", 7, utf8);
    EXPECT_NO_THROW(reporter->sectionStarting(s));
}

// Reentrancy-like usage: multiple sequential sectionStarting calls for different sections
// (e.g., nested or consecutive sections) should not throw via the public interface.
TEST_F(TeamCityReporterSectionStartingTest_573, SectionStarting_MultipleSequentialCalls_573) {
    auto a = makeSectionInfo("a.cpp", 11, "A");
    auto b = makeSectionInfo("b.cpp", 22, "B");
    auto c = makeSectionInfo("c.cpp", 33, "C");

    EXPECT_NO_THROW(reporter->sectionStarting(a));
    EXPECT_NO_THROW(reporter->sectionStarting(b));
    EXPECT_NO_THROW(reporter->sectionStarting(c));
}

// Idempotence expectation at API level: calling sectionStarting twice with the same SectionInfo
// should be a valid operation from caller perspective (no crash/throw). We do not assert any
// internal side-effects.
TEST_F(TeamCityReporterSectionStartingTest_573, SectionStarting_SameSectionTwiceDoesNotThrow_573) {
    auto s = makeSectionInfo("dup.cpp", 5, "duplicate");
    EXPECT_NO_THROW(reporter->sectionStarting(s));
    EXPECT_NO_THROW(reporter->sectionStarting(s));
}
