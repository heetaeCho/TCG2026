// File: tests/ArgParseTests_661.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 Clara internals used by the provided snippet
#include <catch2/internal/catch_clara.hpp>

// The snippet refers to these namespaces/types
using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

// ---- Minimal mocks/wrappers for collaborators the Arg::parse interacts with ----

// Mock for BoundValueRefBase used by Arg::parse via m_ref
// It must provide isFlag() and setValue(std::string const&).
struct MockBoundValueRefBase : Catch::Clara::Detail::BoundValueRefBase {
    MOCK_METHOD(bool, isFlag, (), (const, override));
    MOCK_METHOD(Catch::Clara::Detail::Result, setValue, (std::string const&), (override));
};

// Utility to create a TokenStream with a single token.
static Catch::Clara::Detail::TokenStream oneTokenStream(
    Catch::Clara::Detail::TokenType ttype,
    std::string const& text)
{
    using Catch::Clara::Detail::Token;
    using Catch::Clara::Detail::TokenStream;

    std::vector<Token> toks;
    toks.emplace_back(Token{ttype, text});
    return TokenStream(toks);
}

// Utility to create a TokenStream with a non-argument token first.
static Catch::Clara::Detail::TokenStream nonArgFirstStream() {
    using Catch::Clara::Detail::Token;
    using Catch::Clara::Detail::TokenType;
    using Catch::Clara::Detail::TokenStream;

    std::vector<Token> toks;
    toks.emplace_back(Token{TokenType::Unknown, "--flaglike"}); // anything not Argument
    toks.emplace_back(Token{TokenType::Argument, "won't be reached"});
    return TokenStream(toks);
}

// Helper to access the ParseResultType from InternalParseResult if available.
// If your InternalParseResult exposes different API, adapt the accessor here only.
static Catch::Clara::Detail::ParseResultType getType(const Catch::Clara::Detail::InternalParseResult& r) {
    // Clara exposes InternalParseResult::type() in recent Catch2 versions; if yours differs,
    // you can instead call r.value().type() or r.parseState().type(), depending on the API.
    return r.type();
}

// Factory helpers for Clara::Detail::Result (success/failure) returned by setValue() or validate().
static Catch::Clara::Detail::Result OkResult() {
    return Catch::Clara::Detail::Result::ok();
}
static Catch::Clara::Detail::Result FailResult(std::string const& msg = "fail") {
    return Catch::Clara::Detail::Result::logicError(msg);
}

// Construct an Arg bound to our mock value reference.
// Depending on your Clara version, Arg can be constructed via e.g. Catch::Clara::Arg(*ref) or a builder.
// This helper centralizes that small variation so only this spot needs adjustment in your tree.
static Catch::Clara::Arg makeArgWithRef(std::shared_ptr<MockBoundValueRefBase> const& mockRef) {
    // In Clara, Arg typically takes shared_ptr<Detail::BoundRef> internally.
    // There is usually a constructor overload that accepts Detail::BoundRef (value) as a target.
    // If your version differs, adapt to the appropriate constructor/factory.
    return Catch::Clara::Arg(mockRef);
}

// Some Clara versions perform validate() internally and always succeed for well-formed Arg.
// If you need to force validate() failure, you may need a dedicated ctor or builder flag in your version.
// The tests below primarily verify observable interactions and outcomes reachable without forcing validate() to fail.

} // namespace

// ------------------------------ Tests ------------------------------

//
// NoMatch when next token is NOT an Argument
//
TEST(ClaraArgParseTest_661, ReturnsNoMatchWhenNextTokenIsNotArgument_661) {
    using namespace Catch::Clara;
    using namespace Catch::Clara::Detail;

    auto ref = std::make_shared<StrictMock<MockBoundValueRefBase>>();
    // Parse should NOT treat this as a flag path; it won't reach setValue at all.
    EXPECT_CALL(*ref, isFlag()).Times(0);
    EXPECT_CALL(*ref, setValue(_)).Times(0);

    Arg arg = makeArgWithRef(ref);
    TokenStream ts = nonArgFirstStream();

    auto result = arg.parse("prog", ts);

    // Expect: NoMatch and no token consumption for the returned state.
    EXPECT_EQ(getType(result), ParseResultType::NoMatch);
}

//
// Matched + consumes one token when Argument and setValue succeeds
//
TEST(ClaraArgParseTest_661, MatchedAndConsumesOneOnSuccess_661) {
    using namespace Catch::Clara;
    using namespace Catch::Clara::Detail;

    auto ref = std::make_shared<StrictMock<MockBoundValueRefBase>>();

    // Value-style arg (not a flag)
    EXPECT_CALL(*ref, isFlag()).Times(0); // isFlag() is only used inside an assert; won't be called in success path.

    // Expect setValue called with the token string, and succeed.
    EXPECT_CALL(*ref, setValue("hello"))
        .WillOnce(Return(OkResult()));

    Arg arg = makeArgWithRef(ref);
    TokenStream ts = oneTokenStream(TokenType::Argument, "hello");

    auto result = arg.parse("prog", ts);

    EXPECT_EQ(getType(result), ParseResultType::Matched);
    // If your InternalParseResult exposes remaining token count or a next-token accessor,
    // you can assert consumption here (e.g., result.remainingTokens() is empty).
    // The essential observable here is that setValue was called with "hello" and result is Matched.
}

//
// Propagates failure if setValue fails
//
TEST(ClaraArgParseTest_661, ReturnsFailureWhenSetValueFails_661) {
    using namespace Catch::Clara;
    using namespace Catch::Clara::Detail;

    auto ref = std::make_shared<StrictMock<MockBoundValueRefBase>>();

    EXPECT_CALL(*ref, setValue("bad"))
        .WillOnce(Return(FailResult("boom")));

    Arg arg = makeArgWithRef(ref);
    TokenStream ts = oneTokenStream(TokenType::Argument, "bad");

    auto result = arg.parse("prog", ts);

    // On failure, parse should return a failure-type InternalParseResult (not Matched/NoMatch).
    // Many Clara builds report this as ParseResultType::ShortCircuitAll or Error; check your enum.
    // The important part is: it's not Matched/NoMatch and indicates failure.
    auto type = getType(result);
    EXPECT_NE(type, ParseResultType::Matched);
    EXPECT_NE(type, ParseResultType::NoMatch);
}

//
// Asserts if bound reference is a flag (Arg expects a value, not a flag)
// This mirrors the `assert(!m_ref->isFlag());` in the provided snippet.
//
TEST(ClaraArgParseTest_661, DeathWhenRefIsFlag_661) {
    using namespace Catch::Clara;
    using namespace Catch::Clara::Detail;

    auto ref = std::make_shared<StrictMock<MockBoundValueRefBase>>();

    // The parse contains: assert(!m_ref->isFlag());
    EXPECT_CALL(*ref, isFlag())
        .WillOnce(Return(true));

    // setValue should NOT be reached
    EXPECT_CALL(*ref, setValue(_)).Times(0);

    Arg arg = makeArgWithRef(ref);
    TokenStream ts = oneTokenStream(TokenType::Argument, "any");

#if GTEST_HAS_DEATH_TEST
    EXPECT_DEATH({ (void)arg.parse("prog", ts); }, "");
#else
    GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

//
// No setValue interaction if the token is not Argument (boundary interaction check)
//
TEST(ClaraArgParseTest_661, NoSetValueCalledOnNonArgumentToken_661) {
    using namespace Catch::Clara;
    using namespace Catch::Clara::Detail;

    auto ref = std::make_shared<StrictMock<MockBoundValueRefBase>>();

    EXPECT_CALL(*ref, setValue(_)).Times(0);

    Arg arg = makeArgWithRef(ref);
    TokenStream ts = nonArgFirstStream();

    auto result = arg.parse("prog", ts);
    EXPECT_EQ(getType(result), ParseResultType::NoMatch);
}
