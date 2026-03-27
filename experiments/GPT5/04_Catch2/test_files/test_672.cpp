// File: tests/parser_parse_672.cpp
#include <gtest/gtest.h>

#include <catch2/internal/catch_clara.hpp>

using Catch::Clara::Parser;
using Catch::Clara::ParseResultType;
namespace Detail = Catch::Clara::Detail;

namespace {

// Helper to build a TokenStream over a local vector that stays alive
struct TokenStreamBuilder {
    std::vector<Detail::Token> storage;
    Detail::TokenStream make() {
        // Construct TokenStream over the storage iterators
        return Detail::TokenStream(storage.begin(), storage.end());
    }
    void pushToken(const std::string& s) {
        Detail::Token t{};
        // We do not rely on TokenType value; Parser::parse only uses token text
        // in the error path we validate.
        t.type = static_cast<Detail::TokenType>(0);
        // StringRef is part of Catch2 and can be constructed from const char*
        t.token = Catch::StringRef(s.c_str());
        storage.push_back(t);
    }
};

} // namespace

// ---------- Tests ----------

TEST(ClaraParserParseTest_672, EmptyTokens_ReturnsOkNoMatch_672) {
    Parser p;

    TokenStreamBuilder builder; // no tokens
    auto ts = builder.make();

    auto result = p.parse("prog", std::move(ts));
    ASSERT_TRUE(static_cast<bool>(result)) << "Expected ok result";
    EXPECT_EQ(result.value().type(), ParseResultType::NoMatch);
}

TEST(ClaraParserParseTest_672, UnknownSingleToken_ReturnsRuntimeErrorWithMessage_672) {
    Parser p;

    TokenStreamBuilder builder;
    builder.pushToken("--unknown");
    auto ts = builder.make();

    auto result = p.parse("prog", std::move(ts));
    ASSERT_FALSE(static_cast<bool>(result)) << "Expected runtime error for unrecognised token";
    // Error message must include the token text from the remaining tokens
    EXPECT_NE(result.errorMessage().find("Unrecognised token: --unknown"), std::string::npos);
}

TEST(ClaraParserParseTest_672, UnknownMultipleTokens_FailsOnFirstTokenOnly_672) {
    Parser p;

    TokenStreamBuilder builder;
    builder.pushToken("--first");
    builder.pushToken("--second");
    auto ts = builder.make();

    auto result = p.parse("prog", std::move(ts));
    ASSERT_FALSE(static_cast<bool>(result));
    // Should report only the first unrecognised token at the point of failure
    EXPECT_NE(result.errorMessage().find("Unrecognised token: --first"), std::string::npos);
    EXPECT_EQ(result.errorMessage().find("--second"), std::string::npos)
        << "Parser should fail on the first unrecognised token without advancing";
}
