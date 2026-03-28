// File: tests/assertion_result_get_message_tests.cpp

#include <gtest/gtest.h>

#include <string>

// Catch2 headers (interfaces only; treat class under test as a black box)
#include <catch2/catch_assertion_result.hpp>
#include <catch2/catch_result_type.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/catch_tostring.hpp>      // (commonly brings in StringRef)
#include <catch2/catch_lazy_expression.hpp>
#include <catch2/catch_source_line_info.hpp>

namespace {

using Catch::AssertionResult;
using Catch::AssertionResultData;
using Catch::AssertionInfo;
using Catch::LazyExpression;
using Catch::ResultDisposition;
using Catch::ResultWas;
using Catch::SourceLineInfo;
using Catch::StringRef;

// Helper to build a minimal, valid AssertionResult that carries a message.
// This uses only public constructors / fields and does not infer or simulate
// any internal behavior of AssertionResult.
static AssertionResult MakeAssertionResultWithMessage(
    const std::string& msg,
    ResultWas::OfType resultType = ResultWas::Ok) {

    // Minimal assertion site info (arbitrary but valid)
    const SourceLineInfo lineInfo{"dummy_file.cpp", 123};
    const AssertionInfo info{
        StringRef("REQUIRE"),         // test macro name
        lineInfo,                     // source location
        StringRef("dummy_expr"),      // captured expression
        ResultDisposition::Normal     // result disposition
    };

    // Minimal lazy expression; constructed without simulating internals
    const LazyExpression lazyExpr{};

    // Build data solely via public interface; set the public 'message' field
    AssertionResultData data{resultType, lazyExpr};
    data.message = msg;

    // Build the object under test
    return AssertionResult{info, std::move(data)};
}

} // namespace

// -------- Test Fixture --------
class AssertionResultGetMessageTest_300 : public ::testing::Test {};

// [Normal] Empty message should be observed as empty via the public API.
TEST_F(AssertionResultGetMessageTest_300, ReturnsEmptyWhenNoMessage_300) {
    auto ar = MakeAssertionResultWithMessage("");
    const auto msg = ar.getMessage();

    EXPECT_TRUE(msg.empty());
    EXPECT_EQ(msg.size(), 0u);
    EXPECT_TRUE(msg == ""); // compare via StringRef==const char*
}

// [Normal] Non-empty ASCII message should be returned verbatim.
TEST_F(AssertionResultGetMessageTest_300, ReturnsExactAsciiMessage_300) {
    const std::string expected = "simple message";
    auto ar = MakeAssertionResultWithMessage(expected);
    const auto msg = ar.getMessage();

    EXPECT_FALSE(msg.empty());
    EXPECT_EQ(msg.size(), expected.size());
    EXPECT_TRUE(msg == expected.c_str());
}

// [Boundary] Message with whitespace and newlines should be preserved exactly.
TEST_F(AssertionResultGetMessageTest_300, PreservesWhitespaceAndNewlines_300) {
    const std::string expected = " line 1 \n\tline 2\n\nline 4  ";
    auto ar = MakeAssertionResultWithMessage(expected);
    const auto msg = ar.getMessage();

    EXPECT_EQ(msg.size(), expected.size());
    EXPECT_TRUE(msg == expected.c_str());
}

// [Boundary] Large message should not be truncated.
TEST_F(AssertionResultGetMessageTest_300, HandlesLargeMessage_300) {
    std::string expected(4096, 'A'); // a reasonably large message
    expected.replace(100, 5, "HELLO"); // add a small variation

    auto ar = MakeAssertionResultWithMessage(expected);
    const auto msg = ar.getMessage();

    EXPECT_EQ(msg.size(), expected.size());
    EXPECT_TRUE(msg == expected.c_str());
}

// [Boundary/Internationalization] UTF-8 message should be returned intact.
// (We validate size in bytes and content equality via StringRef comparison.)
TEST_F(AssertionResultGetMessageTest_300, ReturnsUtf8MessageIntact_300) {
    const std::string expected = u8"메시지: 성공 ✅ — Καλημέρα — Привет";
    auto ar = MakeAssertionResultWithMessage(expected);
    const auto msg = ar.getMessage();

    EXPECT_EQ(msg.size(), expected.size());     // byte-size equality
    EXPECT_TRUE(msg == expected.c_str());      // content equality
}
