// tests/reporter_automake_skip_test.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// These includes assume the usual Catch2 v3 layout in your repo.
// If your include paths differ, adjust accordingly.
#include "catch2/reporters/catch_reporter_automake.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// <iostream>, <sstream> are used by the test doubles
#include <sstream>

using ::testing::_;
using ::testing::StrEq;

namespace {

// -----------------------------
// Test doubles (external deps)
// -----------------------------

// Minimal stream wrapper that implements Catch2's IStream concept used by ReporterBase.
// We only expose .stream() and keep ownership semantics identical to production code.
class TestIStream : public Catch::IStream {
public:
    explicit TestIStream(std::ostream& os) : m_os(os) {}
    std::ostream& stream() override { return m_os; }
private:
    std::ostream& m_os;
};

// Dummy IConfig to satisfy ReporterConfig construction if needed.
// We only provide what ReporterBase/StreamingReporterBase/AutomakeReporter touch
// through public interfaces during construction. If your tree offers a ready-made
// config helper in tests, feel free to swap this out.
class DummyConfig : public Catch::IConfig {
public:
    // Implement only the pure-virtuals that ReporterBase might query through fullConfig().
    // The following set is sufficient for reporter construction in practice.
    bool allowThrows() const override { return true; }
    std::ostream& stream() const override {
        // Not used by ReporterBase because it gets stream via ReporterConfig->takeStream()
        // but provide a stub anyway.
        return std::cout;
    }
    // The rest return conservative defaults.
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1.0; }
    Catch::TestSpec const& testSpec() const override {
        static Catch::TestSpec empty;
        return empty;
    }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getPathToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    bool zeroTestsCountAsSuccess() const override { return true; }
    int benchmarkSamples() const override { return 0; }
    double benchmarkResamples() const override { return 0; }
    std::chrono::milliseconds benchmarkConfidenceInterval() const override { return std::chrono::milliseconds{0}; }
    unsigned int rngSeed() const override { return 0u; }
    // Newer Catch2 configs might have more pure virtuals; add trivial stubs if your build asks for them.
};

// Small helper: build a ReporterConfig that points the AutomakeReporter at our ostringstream.
static Catch::ReporterConfig makeConfigPointingTo(std::ostringstream& oss) {
    // ColourMode defaulting to Platform should be fine; customOptions left empty.
    auto streamHolder = Catch::Detail::make_unique<TestIStream>(oss);
    // Construct with bare-minimum pieces:
    // ReporterConfig(IConfig const*, Detail::unique_ptr<IStream>&&, ColourMode mode = ColourMode::Platform,
    //                std::map<std::string, std::string> customOptions = {})
    static DummyConfig dummy; // lifetime must exceed Reporter
    return Catch::ReporterConfig(&dummy, Catch::Detail::unique_ptr<Catch::IStream>(streamHolder.release()),
                                 Catch::ColourMode::Platform, {});
}

// Helper: construct a TestCaseInfo with a given name via public API.
// We do not rely on private state, only on the constructor contract.
static Catch::TestCaseInfo makeTCI(const std::string& name) {
    Catch::NameAndTags nat;
    nat.name = name;
    nat.tags = ""; // no tags
    Catch::SourceLineInfo sli{ __FILE__, __LINE__ };
    // className is empty
    return Catch::TestCaseInfo(Catch::StringRef{}, nat, sli);
}

} // namespace

// -----------------------------
// Test fixture
// -----------------------------
class AutomakeReporter_SkipTest_776 : public ::testing::Test {
protected:
    void SetUp() override {
        // Wire the reporter to our capture stream.
        m_config = makeConfigPointingTo(capture);
        reporter = std::make_unique<Catch::AutomakeReporter>(Catch::ReporterConfig(m_config));
    }

    std::ostringstream capture;
    Catch::ReporterConfig m_config{ makeConfigPointingTo(capture) }; // default-init; re-assigned in SetUp
    std::unique_ptr<Catch::AutomakeReporter> reporter;
};

// -------------- Tests --------------

// Normal: writes the exact prefix, name, and trailing newline.
TEST_F(AutomakeReporter_SkipTest_776, WritesSkipLineWithName_776) {
    auto tci = makeTCI("MyTest.Case");
    reporter->skipTest(tci);

    EXPECT_THAT(capture.str(), StrEq(":test-result: SKIP MyTest.Case\n"));
}

// Boundary: empty test name should still print the prefix and newline (with a space before newline).
TEST_F(AutomakeReporter_SkipTest_776, HandlesEmptyName_776) {
    auto tci = makeTCI("");
    reporter->skipTest(tci);

    EXPECT_THAT(capture.str(), StrEq(":test-result: SKIP \n"));
}

// Special characters: ensure name is forwarded verbatim (no escaping/alteration assumed).
TEST_F(AutomakeReporter_SkipTest_776, PreservesSpecialCharacters_776) {
    auto tci = makeTCI("weird name [tag]/#1");
    reporter->skipTest(tci);

    EXPECT_THAT(capture.str(), StrEq(":test-result: SKIP weird name [tag]/#1\n"));
}

// Unicode: validate UTF-8 names are streamed through intact.
TEST_F(AutomakeReporter_SkipTest_776, SupportsUnicodeNames_776) {
    auto tci = makeTCI(u8"테스트_Δοκιμή_試験");
    reporter->skipTest(tci);

    EXPECT_THAT(capture.str(), StrEq(u8":test-result: SKIP 테스트_Δοκιμή_試験\n"));
}

// Multiple calls: lines accumulate in order, one per skip.
TEST_F(AutomakeReporter_SkipTest_776, MultipleSkipsAccumulate_776) {
    reporter->skipTest(makeTCI("A"));
    reporter->skipTest(makeTCI("B"));
    reporter->skipTest(makeTCI("C"));

    EXPECT_THAT(capture.str(), StrEq(
        ":test-result: SKIP A\n"
        ":test-result: SKIP B\n"
        ":test-result: SKIP C\n"
    ));
}
