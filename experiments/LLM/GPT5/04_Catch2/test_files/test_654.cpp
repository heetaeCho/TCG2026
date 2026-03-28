// File: convert_into_bool_tests_654.cpp

#include <gtest/gtest.h>
#include <string>

// Pull in the public interface (ParserResult, ParseResultType, etc.)
#include "catch2/internal/catch_clara.hpp"

// We assume convertInto is declared in the headers associated with Clara.
// If it isn't, and only the cpp defines it, you can add this forward decl:
//
// namespace Catch { namespace Clara { namespace Detail {
//     // Return type is declared in the header as ParserResult.
//     ParserResult convertInto(std::string const& source, bool& target);
// }}}

using Catch::Clara::Detail::convertInto;

namespace {

TEST(ConvertIntoBool_654, AcceptsTrueTokens_654) {
    bool target = false;

    auto r1 = convertInto("y", target);
    EXPECT_TRUE(static_cast<bool>(r1));
    EXPECT_TRUE(target);

    target = false;
    auto r2 = convertInto("1", target);
    EXPECT_TRUE(static_cast<bool>(r2));
    EXPECT_TRUE(target);

    target = false;
    auto r3 = convertInto("true", target);
    EXPECT_TRUE(static_cast<bool>(r3));
    EXPECT_TRUE(target);

    target = false;
    auto r4 = convertInto("yes", target);
    EXPECT_TRUE(static_cast<bool>(r4));
    EXPECT_TRUE(target);

    target = false;
    auto r5 = convertInto("on", target);
    EXPECT_TRUE(static_cast<bool>(r5));
    EXPECT_TRUE(target);
}

TEST(ConvertIntoBool_654, AcceptsFalseTokens_654) {
    bool target = true;

    auto r1 = convertInto("n", target);
    EXPECT_TRUE(static_cast<bool>(r1));
    EXPECT_FALSE(target);

    target = true;
    auto r2 = convertInto("0", target);
    EXPECT_TRUE(static_cast<bool>(r2));
    EXPECT_FALSE(target);

    target = true;
    auto r3 = convertInto("false", target);
    EXPECT_TRUE(static_cast<bool>(r3));
    EXPECT_FALSE(target);

    target = true;
    auto r4 = convertInto("no", target);
    EXPECT_TRUE(static_cast<bool>(r4));
    EXPECT_FALSE(target);

    target = true;
    auto r5 = convertInto("off", target);
    EXPECT_TRUE(static_cast<bool>(r5));
    EXPECT_FALSE(target);
}

TEST(ConvertIntoBool_654, IsCaseInsensitiveForRecognizedValues_654) {
    bool target = false;

    auto r1 = convertInto("TrUe", target);
    EXPECT_TRUE(static_cast<bool>(r1));
    EXPECT_TRUE(target);

    target = true;
    auto r2 = convertInto("FaLsE", target);
    EXPECT_TRUE(static_cast<bool>(r2));
    EXPECT_FALSE(target);

    target = false;
    auto r3 = convertInto("YeS", target);
    EXPECT_TRUE(static_cast<bool>(r3));
    EXPECT_TRUE(target);

    target = true;
    auto r4 = convertInto("oFf", target);
    EXPECT_TRUE(static_cast<bool>(r4));
    EXPECT_FALSE(target);
}

TEST(ConvertIntoBool_654, ReturnsErrorForUnrecognizedToken_654) {
    bool target = true;
    auto res = convertInto("maybe", target);

    // Observable behavior: result converts to false on error,
    // and provides an error message describing the issue.
    EXPECT_FALSE(static_cast<bool>(res));

    // errorMessage() is part of the public result interface.
    // We verify that it mentions the expectation and the original source.
    // (Do not assert exact message equality to avoid coupling to wording.)
    auto const& msg = res.errorMessage();
    EXPECT_NE(msg.find("Expected a boolean value"), std::string::npos);
    EXPECT_NE(msg.find("maybe"), std::string::npos);
}

TEST(ConvertIntoBool_654, ErrorDoesNotModifyTarget_654) {
    bool target = false;             // known initial value
    auto res = convertInto("unknown-token", target);

    EXPECT_FALSE(static_cast<bool>(res));
    // No observable write to target on error path.
    EXPECT_FALSE(target);
}

TEST(ConvertIntoBool_654, EmptyStringIsError_654) {
    bool target = true;
    auto res = convertInto("", target);

    EXPECT_FALSE(static_cast<bool>(res));
    auto const& msg = res.errorMessage();
    EXPECT_NE(msg.find("Expected a boolean value"), std::string::npos);
    // Target should remain unchanged on error.
    EXPECT_TRUE(target);
}

TEST(ConvertIntoBool_654, NumericAndWhitespaceEdgeCases_654) {
    // Confirm known-accepted numerics still work.
    bool target = false;
    auto ok1 = convertInto("1", target);
    EXPECT_TRUE(static_cast<bool>(ok1));
    EXPECT_TRUE(target);

    target = true;
    auto ok0 = convertInto("0", target);
    EXPECT_TRUE(static_cast<bool>(ok0));
    EXPECT_FALSE(target);

    // Unrecognized numeric should error.
    target = true;
    auto errNum = convertInto("2", target);
    EXPECT_FALSE(static_cast<bool>(errNum));
    EXPECT_TRUE(target); // unchanged on error

    // Leading/trailing spaces are not among recognized literals -> error.
    target = false;
    auto errWs1 = convertInto(" true", target);
    EXPECT_FALSE(static_cast<bool>(errWs1));
    EXPECT_FALSE(target);

    auto errWs2 = convertInto("false ", target);
    EXPECT_FALSE(static_cast<bool>(errWs2));
    EXPECT_FALSE(target);
}

} // namespace
