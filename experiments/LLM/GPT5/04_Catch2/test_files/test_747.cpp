// File: tests/reporter_tap_assertionEnded_747.cpp

#include <gtest/gtest.h>
#include <sstream>

// Catch2 public headers (names follow Catch2 v3 layout; adjust includes if your tree differs)
#include <catch2/reporters/catch_reporter_tap.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/internal/catch_stream.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/catch_message.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_result_type.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>

using namespace Catch;

namespace {

class TAPReporterAssertionEndedTest_747 : public ::testing::Test {
protected:
    std::unique_ptr<Config> cfg_;
    std::ostringstream out_;
    std::unique_ptr<TAPReporter> reporter_;

    void SetUp() override {
        // Build a real IConfig via Config(ConfigData{})
        ConfigData data;
        cfg_ = std::make_unique<Config>(data);

        // Direct reporter output into our stringstream
        Detail::unique_ptr<IStream> stream = makeStream(&out_);

        // Reporter configuration: no colour needed for stream assertions
        ReporterConfig rcfg(
            cfg_.get(),                  // full config
            CATCH_MOVE(stream),          // stream sink
            ColourMode::None,            // color mode
            {}                           // custom options
        );

        reporter_ = std::make_unique<TAPReporter>(CATCH_MOVE(rcfg));
    }

    // Helper: create a minimal TestCaseInfo with the given visible name
    static TestCaseInfo makeTestCaseInfo(const std::string& name) {
        NameAndTags nt;
        nt.name = name;
        nt.tags = ""; // no tags needed
        SourceLineInfo sli{ __FILE__, static_cast<std::size_t>(__LINE__) };
        return TestCaseInfo(StringRef{}, nt, sli);
    }

    // Helper: fabricate a valid, simple AssertionStats (pass or fail) so TapAssertionPrinter can print.
    static AssertionStats makeAssertionStats(ResultWas::OfType resultType,
                                             StringRef expr = "1==1",
                                             StringRef msg = StringRef{}) {
        // Minimal assertion info
        AssertionInfo ainfo{
            "TEST"_sr,
            SourceLineInfo{ __FILE__, static_cast<std::size_t>(__LINE__) },
            expr,
            ResultDisposition::Normal
        };

        // Minimal result data
        AssertionResultData data{ resultType };
        data.reconstructedExpression = expr.to_string();
        if (!msg.empty()) {
            data.message = msg.to_string();
        }

        AssertionResult result(ainfo, data);

        std::vector<MessageInfo> infos; // empty
        Totals totals;                  // default totals are fine

        return AssertionStats(result, infos, totals);
    }
};

} // namespace

// ───────────────────────────────────────────────────────────────────────────────
// Normal operation: prints header "# <current test case name>" before assertion details
TEST_F(TAPReporterAssertionEndedTest_747, WritesHeaderWithCurrentTestCaseName_747) {
    auto tci = makeTestCaseInfo("AlphaCase");
    reporter_->testCaseStarting(tci);

    auto stats = makeAssertionStats(ResultWas::Ok);
    reporter_->assertionEnded(stats);

    const std::string s = out_.str();

    // Must contain the test case header exactly once for this single assertion
    const std::string expectedHeader = "# AlphaCase\n";
    ASSERT_NE(s.find(expectedHeader), std::string::npos)
        << "Expected header '" << expectedHeader << "' not found in output:\n" << s;

    // The function appends a trailing newline after the printer; ensure final char is '\n'
    ASSERT_FALSE(s.empty());
    EXPECT_EQ(s.back(), '\n');
}

// ───────────────────────────────────────────────────────────────────────────────
// Boundary: if multiple assertions happen in the same case, we get multiple headers
TEST_F(TAPReporterAssertionEndedTest_747, PrintsHeaderForEachAssertion_747) {
    auto tci = makeTestCaseInfo("Multi");
    reporter_->testCaseStarting(tci);

    reporter_->assertionEnded(makeAssertionStats(ResultWas::Ok));
    reporter_->assertionEnded(makeAssertionStats(ResultWas::ExpressionFailed)); // mix pass/fail

    const std::string s = out_.str();
    const std::string expectedHeader = "# Multi\n";

    // Expect 2 occurrences of the header (one per call)
    size_t pos = 0;
    int count = 0;
    while ((pos = s.find(expectedHeader, pos)) != std::string::npos) {
        ++count;
        pos += expectedHeader.size();
    }
    EXPECT_EQ(count, 2) << "Header '# Multi' should appear once per assertionEnded call.";
}

// ───────────────────────────────────────────────────────────────────────────────
// Behavior with changing current test case between assertions
TEST_F(TAPReporterAssertionEndedTest_747, UsesLatestCurrentTestCaseName_747) {
    auto first = makeTestCaseInfo("CaseA");
    reporter_->testCaseStarting(first);
    reporter_->assertionEnded(makeAssertionStats(ResultWas::Ok));

    auto second = makeTestCaseInfo("CaseB");
    reporter_->testCaseStarting(second);
    reporter_->assertionEnded(makeAssertionStats(ResultWas::Ok));

    const std::string s = out_.str();
    // We should see headers for both CaseA and CaseB (in that order)
    const auto firstPos  = s.find("# CaseA\n");
    const auto secondPos = s.find("# CaseB\n");
    ASSERT_NE(firstPos,  std::string::npos) << "Missing '# CaseA' header.";
    ASSERT_NE(secondPos, std::string::npos) << "Missing '# CaseB' header.";
    EXPECT_LT(firstPos, secondPos) << "Headers should appear in call order.";
}

// ───────────────────────────────────────────────────────────────────────────────
// Exceptional-ish but observable: message text present in AssertionStats should not
// prevent header emission. We don't check printer internals, only that header still prints.
TEST_F(TAPReporterAssertionEndedTest_747, HeaderPrintedEvenWithInfoMessage_747) {
    auto tci = makeTestCaseInfo("WithMsg");
    reporter_->testCaseStarting(tci);

    auto stats = makeAssertionStats(ResultWas::Ok, "2+2==4"_sr, "note: hello world"_sr);
    reporter_->assertionEnded(stats);

    const std::string s = out_.str();
    const std::string expectedHeader = "# WithMsg\n";
    ASSERT_NE(s.find(expectedHeader), std::string::npos)
        << "Header should be printed even when messages are present.";
}
