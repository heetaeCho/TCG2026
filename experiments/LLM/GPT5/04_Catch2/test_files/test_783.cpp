// File: tests/TeamCityReporter_assertionEnded_783.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <memory>

// Catch2 includes — adjust paths to your tree if needed
#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_result_type.hpp"

// If these two are in different headers in your tree, include those instead:
#include "catch2/interfaces/catch_interfaces_reporter.hpp"   // for AssertionStats
#include "catch2/internal/catch_source_line_info.hpp"        // if needed for SourceLineInfo
#include "catch2/internal/catch_stringref.hpp"               // if needed for StringRef

using namespace Catch;
using ::testing::HasSubstr;
using ::testing::AllOf;

// ------------------------
// Minimal test scaffolding
// ------------------------

// Adapter that feeds a std::ostream to Catch::IStream expected by ReporterBase
class OssAdapter : public IStream {
public:
    explicit OssAdapter(std::ostream& os) : m_os(os) {}
    std::ostream& stream() override { return m_os; }
private:
    std::ostream& m_os;
};

// A tiny, inert IConfig to satisfy ReporterConfig -> ReporterBase ctor.
// If your tree already provides a convenient stub, use it instead.
#include "catch2/interfaces/catch_interfaces_config.hpp"
class DumbConfig : public IConfig {
public:
    // Return safe defaults; tests do not depend on any of these.
    ~DumbConfig() override = default;
    bool allowThrows() const override { return true; }
    IConfig::DetailLevel detailLevel() const override { return IConfig::DetailLevel::Normal; }
    bool includeSuccessfulResults() const override { return true; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    TestSpec const& testSpec() const override { static TestSpec s; return s; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> s; return s; }
    bool filenameReporting() const override { return true; }
    bool diagnostics() const override { return false; }
    bool benchmarking() const override { return false; }
    bool listTestNamesOnly() const override { return false; }
    std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> s; return s; }
    std::set<std::string> const& getReporterNames() const override { static std::set<std::string> s; return s; }
    std::set<std::string> const& getListenerNames() const override { static std::set<std::string> s; return s; }
    std::set<ColourMode> const& getColourModeSet() const override { static std::set<ColourMode> s; return s; }
    ColourMode colourMode() const override { return ColourMode::None; }
    std::vector<std::string> const& getOptionalReporterOutputPaths() const override { static std::vector<std::string> s; return s; }
    // Newer Catch2 versions may have more methods; add trivial defaults if needed.
};

// Reporter under test, with a small test helper to set the current test case info
class TestableTeamCityReporter : public TeamCityReporter {
public:
    explicit TestableTeamCityReporter(std::ostream& os)
    : TeamCityReporter( ReporterConfig(
          &m_cfg,
          Detail::unique_ptr<IStream>(new OssAdapter(os)),
          ColourMode::None
      ) ) {}

    void setCurrentTestCaseInfo(TestCaseInfo const& info) {
        // streaming base exposes this protected pointer; we only set it.
        this->currentTestCaseInfo = &info;
    }

private:
    DumbConfig m_cfg;
};

// Helper to build a minimal TestCaseInfo for the reporter (name + properties toggles)
static TestCaseInfo MakeTCI(const std::string& name, TestCaseProperties props = TestCaseProperties::None) {
    NameAndTags nat;
    nat.name = name;
    nat.tags = "";
    TestCaseInfo tci(StringRef(), nat, SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)});
    tci.properties = props; // public field; okToFail() will reflect this.
    return tci;
}

// Helper to build AssertionResult with just the bits the reporter queries.
// Stays within public interface shown in your partials.
static AssertionResult MakeAssertionResult(ResultWas::OfType type,
                                           const SourceLineInfo& sli,
                                           StringRef exprInMacro = StringRef(),
                                           StringRef expanded = StringRef()) {
    // Compose AssertionInfo + AssertionResultData according to your headers.
    // These names/ctors match Catch2 v3.x public API from your partials.
    AssertionInfo ai;
    ai.macroName = StringRef("REQUIRE");
    ai.lineInfo = sli;
    ai.capturedExpression = exprInMacro;
    ai.resultDisposition = ResultDisposition::Normal;

    AssertionResultData data;
    data.resultType = type;
    data.reconstructedExpression = LazyExpression(exprInMacro, expanded);
    data.message = StringRef(); // no primary message; info messages are carried separately

    return AssertionResult(ai, CATCH_MOVE(data));
}

// Minimal Totals used by AssertionStats; values are not used by the SUT path.
static Totals MakeTotals() {
    return Totals{};
}

// --------------
// Test Fixture
// --------------
class TeamCityReporter_783 : public ::testing::Test {
protected:
    std::ostringstream oss;
    TestableTeamCityReporter reporter{oss};
};

// ------------------------------------------------------
// Tests — names include TEST_ID as requested (…_783).
// We check only observable output, never private state.
// ------------------------------------------------------

// 1) ExplicitSkip -> must emit testIgnored with "explicit skip"
TEST_F(TeamCityReporter_783, ExplicitSkip_IsReportedAsIgnored_783) {
    auto tci = MakeTCI("skip_case");
    reporter.setCurrentTestCaseInfo(tci);

    AssertionResult ar = MakeAssertionResult(ResultWas::ExplicitSkip,
                                             SourceLineInfo{ "x.cpp", 123u });
    AssertionStats stats{ ar, /*infoMessages*/{}, MakeTotals() };

    reporter.assertionEnded(stats);

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr("##teamcity[testIgnored"));
    EXPECT_THAT(out, HasSubstr("name='"));            // name is present (escaped by reporter)
    EXPECT_THAT(out, HasSubstr("message='"));         // message field present
    EXPECT_THAT(out, HasSubstr("explicit skip"));     // switch(message) content
}

// 2) ExpressionFailed, okToFail = false -> testFailed with "expression failed"
TEST_F(TeamCityReporter_783, ExpressionFailed_IsReportedAsFailed_783) {
    auto tci = MakeTCI("fails_normally", TestCaseProperties::None);
    reporter.setCurrentTestCaseInfo(tci);

    AssertionResult ar = MakeAssertionResult(ResultWas::ExpressionFailed,
                                             SourceLineInfo{ "y.cpp", 77u });
    AssertionStats stats{ ar, {}, MakeTotals() };

    reporter.assertionEnded(stats);

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr("##teamcity[testFailed"));
    EXPECT_THAT(out, HasSubstr("expression failed"));
}

// 3) ExpressionFailed, okToFail = true -> testIgnored and note about ignore
TEST_F(TeamCityReporter_783, ExpressionFailed_OkToFail_IsIgnoredWithNote_783) {
    auto tci = MakeTCI("may_fail", TestCaseProperties::OkToFail);
    reporter.setCurrentTestCaseInfo(tci);

    AssertionResult ar = MakeAssertionResult(ResultWas::ExpressionFailed,
                                             SourceLineInfo{ "z.cpp", 5u });
    AssertionStats stats{ ar, {}, MakeTotals() };

    reporter.assertionEnded(stats);

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr("##teamcity[testIgnored"));
    EXPECT_THAT(out, HasSubstr("expression failed"));
    EXPECT_THAT(out, HasSubstr("failure ignore as test marked as 'ok to fail'"));
}

// 4) ThrewException -> maps to "unexpected exception"
TEST_F(TeamCityReporter_783, ThrewException_MessageIsUnexpectedException_783) {
    auto tci = MakeTCI("throws_case");
    reporter.setCurrentTestCaseInfo(tci);

    AssertionResult ar = MakeAssertionResult(ResultWas::ThrewException,
                                             SourceLineInfo{ "ex.cpp", 42u });
    AssertionStats stats{ ar, {}, MakeTotals() };

    reporter.assertionEnded(stats);

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr("##teamcity[testFailed"));
    EXPECT_THAT(out, HasSubstr("unexpected exception"));
}

// 5) Info messages: 1 -> "with message:" + quoted payload
TEST_F(TeamCityReporter_783, OneInfoMessage_UsesSingularLabel_783) {
    auto tci = MakeTCI("info_singular");
    reporter.setCurrentTestCaseInfo(tci);

    AssertionResult ar = MakeAssertionResult(ResultWas::ExpressionFailed,
                                             SourceLineInfo{ "m.cpp", 9u });

    std::vector<MessageInfo> infos;
    infos.emplace_back(StringRef("INFO"), SourceLineInfo{"m.cpp", 10u}, ResultWas::Info);
    // The actual payload string is taken from MessageBuilder usually, but reporter prints MessageInfo.message
    // Your MessageInfo in partials does not show a 'message' field, but AssertionStats carries messages
    // with .message set. If in your tree MessageInfo stores the string in a field named `message`, this works.

    // Attach the actual string that reporter will read and print.
    // If your struct uses a different field name, adjust here:
    // (This line assumes public field `message` exists, as referenced in reporter source.)
    struct MessageInfo& mi = infos.back();
    mi.message = StringRef("one fish"); // public, per reporter code access

    AssertionStats stats{ ar, infos, MakeTotals() };

    reporter.assertionEnded(stats);

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr(" with message:"));
    EXPECT_THAT(out, HasSubstr("\n \"one fish\""));
}

// 6) Info messages: 2 -> "with messages:" + two quoted lines
TEST_F(TeamCityReporter_783, MultipleInfoMessages_UsesPluralLabel_783) {
    auto tci = MakeTCI("info_plural");
    reporter.setCurrentTestCaseInfo(tci);

    AssertionResult ar = MakeAssertionResult(ResultWas::ExpressionFailed,
                                             SourceLineInfo{ "n.cpp", 1u });

    std::vector<MessageInfo> infos;
    infos.emplace_back(StringRef("INFO"), SourceLineInfo{"n.cpp", 2u}, ResultWas::Info);
    infos.emplace_back(StringRef("INFO"), SourceLineInfo{"n.cpp", 3u}, ResultWas::Info);

    infos[0].message = StringRef("alpha");
    infos[1].message = StringRef("beta");

    AssertionStats stats{ ar, infos, MakeTotals() };

    reporter.assertionEnded(stats);

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr(" with messages:"));
    EXPECT_THAT(out, AllOf(HasSubstr("\n \"alpha\""), HasSubstr("\n \"beta\"")));
}

// 7) If expression is present -> prints expression & expansion block
TEST_F(TeamCityReporter_783, WithExpression_PrintsExpressionAndExpansion_783) {
    auto tci = MakeTCI("has_expr");
    reporter.setCurrentTestCaseInfo(tci);

    AssertionResult ar = MakeAssertionResult(
        ResultWas::ExpressionFailed,
        SourceLineInfo{ "e.cpp", 11u },
        /*exprInMacro*/ StringRef("a == b"),
        /*expanded*/   StringRef("1 == 2")
    );

    AssertionStats stats{ ar, {}, MakeTotals() };
    reporter.assertionEnded(stats);

    const std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr("\n a == b\nwith expansion:\n 1 == 2\n"));
}
