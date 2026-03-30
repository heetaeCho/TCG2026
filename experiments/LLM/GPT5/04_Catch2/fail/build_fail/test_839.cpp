// File: tests/XmlReporter_assertionEnded_839.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>
#include <vector>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp" // if your ReporterConfig lives here

using ::testing::Return;
using ::testing::NiceMock;
using Catch::ResultWas;

namespace {

// --- Minimal mock for external collaborator: IConfig ---
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));

    // Keep everything else default (non-pure virtual in provided iface),
    // so we don't need to override other methods.
};

// Helper: construct a public, observable AssertionResult with desired shape.
static Catch::AssertionResult makeAssertionResult(
    ResultWas::OfType type,
    bool success,
    bool hasExpr,
    Catch::StringRef macroName,
    Catch::StringRef expr = {},
    Catch::StringRef expanded = {},
    Catch::StringRef message = {},
    Catch::SourceLineInfo src = Catch::SourceLineInfo{ "file.cpp", 123 }
) {
    using namespace Catch;

    // Build AssertionInfo
    // NOTE: Adjust constructor args if your local AssertionInfo signature differs
    AssertionInfo info(
        "captured-expression",   // capturedExpression (name varies across versions)
        src,
        macroName,               // macroName
        ResultWas::Unknown       // resultType hint in info; actual type lives in data
    );

    // Build AssertionResultData (public struct in Catch2)
    AssertionResultData data;
    data.resultType = type;
    data.message = std::string(message);
    data.reconstructedExpression = std::string(expr);
    data.reconstructedExpressionInMacro = std::string(expr);
    data.expandedExpression = std::string(expanded);
    data.decomposedExpression = nullptr; // no decomposed expr here
    data.shouldThrow = false;
    data.maybeEmpty = false;

    // Wire flags derived from inputs using only public booleans the engine consults
    // (XmlReporter reads via accessors; success is inferred via result type + succeeded()).
    // In Catch2, succeeded() depends on result type; we’ll set by choosing OfType and rely
    // on the implementation’s own accessors (black-box).

    // If you need `hasExpression()` to be false, leave `reconstructedExpression` empty.
    if (!hasExpr) {
        data.reconstructedExpression.clear();
        data.expandedExpression.clear();
    }

    return AssertionResult(info, std::move(data));
}

// Helper: make MessageInfo (Info/Warning) with line info
static Catch::MessageInfo makeMsg(ResultWas::OfType t,
                                  Catch::StringRef macro = "MACRO",
                                  Catch::SourceLineInfo src = { "m.cpp", 45 }) {
    // MessageInfo’s ctor increments a global counter; fine in tests.
    return Catch::MessageInfo(macro, src, t);
}

// Build AssertionStats wrapper
static Catch::AssertionStats makeStats(const Catch::AssertionResult& ar,
                                       const std::vector<Catch::MessageInfo>& msgs) {
    // Totals are not inspected by XmlReporter::assertionEnded in provided snippet,
    // so we can pass a default-initialized Totals.
    Catch::Totals totals;
    return Catch::AssertionStats(ar, msgs, totals);
}

// Fixture that owns stream + reporter under a configurable MockConfig
class XmlReporterAssertionEnded_839 : public ::testing::Test {
protected:
    std::ostringstream oss;
    NiceMock<MockConfig> mockCfg;

    // NOTE: ReporterConfig exact signature/namespace can vary slightly by Catch2 version.
    // In most recent Catch2, ReporterConfig takes (IConfig const*, std::ostream&, ColourImpl*)
    // or a wrapper that contains stream + config. Adjust include/ctor as needed in your tree.
    std::unique_ptr<Catch::XmlReporter> makeReporter() {
        // Minimal ReporterConfig: config*, stream, (maybe) colour impl, etc.
        Catch::ReporterConfig rconf{ &mockCfg, oss };
        return std::make_unique<Catch::XmlReporter>(std::move(rconf));
    }

    // Small helper to normalize output for assertions
    static std::string squish(std::string s) {
        // Remove CRs and collapse multiple spaces for robust contains checks
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        return s;
    }
};

} // namespace

// ===================== TESTS =====================

// 1) Info/Warning messages gate: Info is emitted only when includeSuccessfulResults()
//     OR when overall result is not OK; Warning messages are emitted regardless.
TEST_F(XmlReporterAssertionEnded_839, InfoAndWarningMessageInclusion_839) {
    using namespace Catch;

    // Overall assertion result is OK with no expression; success path.
    auto ar = makeAssertionResult(ResultWas::Ok, /*success*/true, /*hasExpr*/false, "REQUIRE");

    // Two messages: INFO and WARNING
    auto infoMsg = makeMsg(ResultWas::Info);
    auto warnMsg = makeMsg(ResultWas::Warning);
    std::vector<MessageInfo> msgs = { infoMsg, warnMsg };
    auto stats = makeStats(ar, msgs);

    // Case A: includeSuccessfulResults == false -> expect only <Warning>, no <Info>
    ON_CALL(mockCfg, includeSuccessfulResults()).WillByDefault(Return(false));
    {
        auto rep = makeReporter();
        rep->assertionEnded(stats);
        auto out = squish(oss.str());
        EXPECT_THAT(out, ::testing::HasSubstr("<Warning>")) << out;
        EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("<Info>"))) << out;
    }

    // Reset buffer
    oss.str(""); oss.clear();

    // Case B: includeSuccessfulResults == true -> expect both <Info> and <Warning>
    ON_CALL(mockCfg, includeSuccessfulResults()).WillByDefault(Return(true));
    {
        auto rep = makeReporter();
        rep->assertionEnded(stats);
        auto out = squish(oss.str());
        EXPECT_THAT(out, ::testing::HasSubstr("<Info>")) << out;
        EXPECT_THAT(out, ::testing::HasSubstr("<Warning>")) << out;
    }
}

// 2) Early-return path: when includeSuccessfulResults == false and result is neither
//    Warning nor ExplicitSkip, reporter returns early (no Expression/Failure/Exception blocks).
TEST_F(XmlReporterAssertionEnded_839, EarlyReturnSkipsBodyWhenNotIncludingSuccess_839) {
    using namespace Catch;

    // Result is Ok (or some success), no expression.
    auto ar = makeAssertionResult(ResultWas::Ok, /*success*/true, /*hasExpr*/false, "CHECK");
    std::vector<MessageInfo> msgs; // no messages -> nothing emitted before early return
    auto stats = makeStats(ar, msgs);

    ON_CALL(mockCfg, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = makeReporter();
    rep->assertionEnded(stats);
    auto out = squish(oss.str());

    // Expect nothing meaningful (no Expression, Failure, Exception, etc.)
    EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("<Expression"))) << out;
    EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("<Failure"))) << out;
    EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("<Exception"))) << out;
    EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("<FatalErrorCondition"))) << out;
    EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("<Skip"))) << out;
}

// 3) Expression block: when assertion has expression, reporter prints <Expression>
//    with attributes success + type, plus <Original> and <Expanded> children.
TEST_F(XmlReporterAssertionEnded_839, WritesExpressionBlockWhenHasExpression_839) {
    using namespace Catch;

    auto ar = makeAssertionResult(
        ResultWas::ExpressionFailed, /*success*/false,
        /*hasExpr*/true, "REQUIRE",
        /*expr*/"a == b", /*expanded*/"1 == 2", /*message*/"boom",
        /*source*/SourceLineInfo{"exp.cpp", 7}
    );
    std::vector<MessageInfo> msgs;
    auto stats = makeStats(ar, msgs);

    ON_CALL(mockCfg, includeSuccessfulResults()).WillByDefault(Return(true));

    auto rep = makeReporter();
    rep->assertionEnded(stats);
    auto out = squish(oss.str());

    EXPECT_THAT(out, ::testing::HasSubstr("<Expression")) << out;
    EXPECT_THAT(out, ::testing::HasSubstr("success=")) << out;
    EXPECT_THAT(out, ::testing::HasSubstr("type=")) << out;
    EXPECT_THAT(out, ::testing::HasSubstr("<Original>")) << out;
    EXPECT_THAT(out, ::testing::HasSubstr("a == b")) << out;
    EXPECT_THAT(out, ::testing::HasSubstr("<Expanded>")) << out;
    EXPECT_THAT(out, ::testing::HasSubstr("1 == 2")) << out;
}

// 4) ThrewException branch: reporter prints <Exception> with source info and message.
TEST_F(XmlReporterAssertionEnded_839, WritesExceptionElementOnThrow_839) {
    using namespace Catch;

    auto ar = makeAssertionResult(
        ResultWas::ThrewException, /*success*/false,
        /*hasExpr*/false, "REQUIRE",
        /*expr*/"", /*expanded*/"", /*message*/"std::runtime_error: oops",
        /*source*/SourceLineInfo{"throw.cpp", 11}
    );
    auto stats = makeStats(ar, {});

    ON_CALL(mockCfg, includeSuccessfulResults()).WillByDefault(Return(true));

    auto rep = makeReporter();
    rep->assertionEnded(stats);
    auto out = squish(oss.str());

    EXPECT_THAT(out, ::testing::HasSubstr("<Exception>")) << out;
    EXPECT_THAT(out, ::testing::HasSubstr("oops")) << out;
    EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("<Failure>"))) << out;
}

// 5) ExplicitSkip branch: should still output <Skip> even if includeSuccessfulResults == false
//    (the code explicitly allows skip to pass through).
TEST_F(XmlReporterAssertionEnded_839, WritesSkipEvenWhenNotIncludingSuccess_839) {
    using namespace Catch;

    auto ar = makeAssertionResult(
        ResultWas::ExplicitSkip, /*success*/true,
        /*hasExpr*/false, "SKIP",
        /*expr*/"", /*expanded*/"", /*message*/"skipped due to filter",
        /*source*/SourceLineInfo{"t.cpp", 42}
    );
    auto stats = makeStats(ar, {});

    ON_CALL(mockCfg, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = makeReporter();
    rep->assertionEnded(stats);
    auto out = squish(oss.str());

    EXPECT_THAT(out, ::testing::HasSubstr("<Skip>")) << out;
    EXPECT_THAT(out, ::testing::HasSubstr("skipped due to filter")) << out;
    EXPECT_THAT(out, ::testing::Not(::testing::HasSubstr("<Expression"))) << out;
}
