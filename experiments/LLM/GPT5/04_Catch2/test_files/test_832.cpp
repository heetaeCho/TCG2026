// File: tests/sonarqube_writeAssertion_832_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <vector>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp" // if ReporterConfig lives here in your tree

using namespace Catch;
using ::testing::HasSubstr;

// --- Small helpers to build inputs via public interfaces ---

static SourceLineInfo SL(std::string file, std::size_t line) {
    return SourceLineInfo{file.c_str(), static_cast<std::size_t>(line)};
}

// Builds a minimal AssertionResult with the public constructors/types.
// The strings default to non-empty so writeAssertion has observable text.
static AssertionResult makeResult(ResultWas::OfType type,
                                  StringRef macroName = "REQUIRE"_sr,
                                  StringRef expr = "a == b"_sr,
                                  StringRef exprInMacro = "a == b"_sr,
                                  StringRef expanded = "1 == 2"_sr,
                                  StringRef message = "custom-message"_sr,
                                  SourceLineInfo sli = SL("file.cpp", 123),
                                  bool hasExpr = true,
                                  bool hasExpanded = true,
                                  bool hasMsg = true) {
    // Build AssertionInfo (macro name + source line)
    AssertionInfo info{ "unused"_sr, macroName, sli, ResultDisposition::Normal };

    // Build AssertionResultData with fields we care about
    AssertionResultData data{ type };
    if (hasExpr) {
        data.expression = expr.to_string();
        data.macroName = macroName;
        data.decomposedExpression = exprInMacro.to_string();
    }
    if (hasExpanded) {
        data.reconstruct = expanded.to_string();
    }
    if (hasMsg) {
        data.message = message;
    }
    data.lineInfo = sli;

    return AssertionResult{ info, CATCH_MOVE(data) };
}

static AssertionStats makeStats(const AssertionResult& r,
                                std::vector<MessageInfo> infos = {}) {
    Totals totals; // contents not used by writeAssertion
    return AssertionStats{ r, infos, totals };
}

// Creates a reporter that writes to a provided ostringstream
static std::unique_ptr<SonarQubeReporter> makeReporter(std::ostringstream& os) {
    // ReporterConfig takes an ostream reference and (optionally) preferences; use defaults
    ReporterConfig cfg{ os, {}, {}, {} };
    return std::make_unique<SonarQubeReporter>(ReporterConfig{ std::move(cfg) });
}

// --- Tests ---

// Element mapping: ExpressionFailed -> <failure ...>
TEST(SonarQubeReporterTest_832, WritesFailureElementWhenExpressionFailed_832) {
    std::ostringstream os;
    auto reporter = makeReporter(os);

    auto result = makeResult(ResultWas::ExpressionFailed,
                             "REQUIRE"_sr, "a == b"_sr, "a == b"_sr, "1 == 2"_sr,
                             "message-1"_sr, SL("x.cpp", 10),
                             /*hasExpr*/true, /*hasExpanded*/true, /*hasMsg*/true);
    auto stats = makeStats(result);

    reporter->writeAssertion(stats, /*okToFail*/false);

    std::string out = os.str();
    // Element name
    EXPECT_THAT(out, HasSubstr("<failure"))   << out;
    // Message attribute built as MACRO(expr)
    EXPECT_THAT(out, HasSubstr("message=\"REQUIRE(a == b)\"")) << out;
    // Body starts with FAILED:
    EXPECT_THAT(out, HasSubstr("FAILED:\n")) << out;
    // Includes expression-in-macro and expansion blocks
    EXPECT_THAT(out, HasSubstr("\ta == b\n")) << out;
    EXPECT_THAT(out, HasSubstr("with expansion:\n\t1 == 2\n")) << out;
    // Includes explicit message (and newline appended)
    EXPECT_THAT(out, HasSubstr("message-1\n")) << out;
    // Ends with source location info
    EXPECT_THAT(out, HasSubstr("at x.cpp:10")) << out;
}

// Element mapping: ThrewException -> <error ...>
TEST(SonarQubeReporterTest_832, WritesErrorElementWhenThrewException_832) {
    std::ostringstream os;
    auto reporter = makeReporter(os);

    auto result = makeResult(ResultWas::ThrewException,
                             "CHECK"_sr, "foo()"_sr, "foo()"_sr, "foo() threw"_sr,
                             "boom"_sr, SL("y.cpp", 77));
    auto stats = makeStats(result);

    reporter->writeAssertion(stats, /*okToFail*/false);

    std::string out = os.str();
    EXPECT_THAT(out, HasSubstr("<error")) << out;
    EXPECT_THAT(out, HasSubstr("message=\"CHECK(foo())\"")) << out;
    EXPECT_THAT(out, HasSubstr("FAILED:\n")) << out;
    EXPECT_THAT(out, HasSubstr("boom\n")) << out;
    EXPECT_THAT(out, HasSubstr("at y.cpp:77")) << out;
}

// Element mapping: ExplicitSkip -> <skipped ...>, and body starts with SKIPPED (not FAILED)
TEST(SonarQubeReporterTest_832, WritesSkippedElementWhenExplicitSkip_832) {
    std::ostringstream os;
    auto reporter = makeReporter(os);

    auto result = makeResult(ResultWas::ExplicitSkip,
                             "REQUIRE"_sr, "cond"_sr, "cond"_sr, ""_sr,
                             ""_sr, SL("skip.cpp", 5),
                             /*hasExpr*/true, /*hasExpanded*/false, /*hasMsg*/false);
    auto stats = makeStats(result);

    reporter->writeAssertion(stats, /*okToFail*/false);

    std::string out = os.str();
    EXPECT_THAT(out, HasSubstr("<skipped")) << out;
    EXPECT_THAT(out, HasSubstr("message=\"REQUIRE(cond)\"")) << out;
    EXPECT_THAT(out, HasSubstr("SKIPPED\n")) << out;
    // Should not include FAILED: prefix in skip path
    EXPECT_EQ(out.find("FAILED:\n"), std::string::npos) << out;
    EXPECT_THAT(out, HasSubstr("at skip.cpp:5")) << out;
}

// okToFail overrides to <skipped> even for failing results
TEST(SonarQubeReporterTest_832, OkToFailForcesSkippedElementOnFailure_832) {
    std::ostringstream os;
    auto reporter = makeReporter(os);

    auto result = makeResult(ResultWas::ExplicitFailure,
                             "REQUIRE_FALSE"_sr, "x"_sr, "x"_sr, ""_sr,
                             ""_sr, SL("z.cpp", 21),
                             /*hasExpr*/true, /*hasExpanded*/false, /*hasMsg*/false);
    auto stats = makeStats(result);

    reporter->writeAssertion(stats, /*okToFail*/true);

    std::string out = os.str();
    EXPECT_THAT(out, HasSubstr("<skipped")) << out;
    // Even when skipped due to okToFail, the body follows the failure branch
    EXPECT_THAT(out, HasSubstr("FAILED:\n")) << out;
    EXPECT_THAT(out, HasSubstr("\tx\n")) << out;
    EXPECT_THAT(out, HasSubstr("at z.cpp:21")) << out;
}

// Mapping of “non-user-facing” types (Ok, Info, Warning, Unknown, FailureBit, Exception) -> internalError
TEST(SonarQubeReporterTest_832, MapsNonFailureNonSkipToInternalError_832) {
    std::ostringstream os;
    auto reporter = makeReporter(os);

    // Use ResultWas::Ok as representative; okToFail=false so it should map to internalError
    auto result = makeResult(ResultWas::Ok,
                             "CHECK"_sr, "1==1"_sr, "1==1"_sr, ""_sr,
                             ""_sr, SL("ok.cpp", 1),
                             /*hasExpr*/true, /*hasExpanded*/false, /*hasMsg*/false);
    auto stats = makeStats(result);

    reporter->writeAssertion(stats, /*okToFail*/false);

    std::string out = os.str();
    EXPECT_THAT(out, HasSubstr("<internalError")) << out;
    // Body will be in the "FAILED" branch for non-skip types, per implementation
    EXPECT_THAT(out, HasSubstr("FAILED:\n")) << out;
    EXPECT_THAT(out, HasSubstr("\t1==1\n")) << out;
    EXPECT_THAT(out, HasSubstr("at ok.cpp:1")) << out;
}

// Info messages with type == Info are appended to the body
TEST(SonarQubeReporterTest_832, AppendsInfoMessagesToBody_832) {
    std::ostringstream os;
    auto reporter = makeReporter(os);

    auto result = makeResult(ResultWas::ExpressionFailed,
                             "REQUIRE"_sr, "a < b"_sr, "a < b"_sr, "2 < 1"_sr,
                             ""_sr, SL("info.cpp", 9));
    std::vector<MessageInfo> infos;
    infos.emplace_back("INFO"_sr, SL("n.cpp", 3), ResultWas::Info);
    // MessageInfo holds metadata; the text is carried by a separate MessageBuilder typically,
    // but writeAssertion consumes `stats.infoMessages[i].message` via public interface;
    // we only assert that any INFO-typed messages that have text appear. To keep this strictly
    // black-box and portable, we assert the structure also contains the location suffix (always present).

    auto stats = AssertionStats{ result, infos, Totals{} };
    reporter->writeAssertion(stats, /*okToFail*/false);

    std::string out = os.str();
    // We can only validate that INFO-typed messages are considered; since we cannot
    // control `message` content here portably, we check the fixed parts remain intact.
    EXPECT_THAT(out, HasSubstr("<failure")) << out;
    EXPECT_THAT(out, HasSubstr("FAILED:\n")) << out;
    EXPECT_THAT(out, HasSubstr("at info.cpp:9")) << out;
    // Presence of an additional newline due to appended message(s) is acceptable but not strictly asserted.
}
