// File: opt_parse_tests_664.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>
#include <vector>
#include <utility>

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::Exactly;

// -----------------------------
// Minimal public-facing scaffolding to exercise Opt::parse as a black box.
// We define only what the provided snippet touches, without re-implementing
// internal logic. The behavior under test is only what's observable via
// return values and collaborator calls.
// -----------------------------
namespace Catch {
namespace Clara {
namespace Detail {

enum class TokenType { Option, Argument };

// A simple token used by the TokenStream
struct Token {
    TokenType type;
    std::string token;
};

// Iterator-like TokenStream supporting the operations used by parse()
class TokenStream {
public:
    TokenStream() = default;
    explicit TokenStream(std::vector<Token> t) : tok_(std::move(t)), i_(0) {}

    // bool-check: "if (tokens)"
    explicit operator bool() const { return i_ < tok_.size(); }

    // Dereference to get the current token: "*tokens"
    const Token& operator*() const { return tok_[i_]; }

    // Arrow to access current token fields: "tokens->type", "tokens->token"
    const Token* operator->() const { return &tok_[i_]; }

    // Pre-increment: "++tokens"
    TokenStream& operator++() {
        if (i_ < tok_.size()) ++i_;
        return *this;
    }

    // For tests: remaining count + current index
    size_t index() const { return i_; }
    size_t remaining() const { return (i_ < tok_.size()) ? (tok_.size() - i_) : 0; }

private:
    std::vector<Token> tok_;
    size_t i_{0};
};

// Parse outcome kinds
enum class ParseResultType { Matched, NoMatch, ShortCircuitAll };

// Parse state holds the result and (moved) stream
struct ParseState {
    ParseState(ParseResultType t, TokenStream s)
        : type(t), tokens(std::move(s)) {}
    ParseResultType type;
    TokenStream tokens;
};

// A lightweight Result type used by collaborator setters & validate()
struct Result {
    Result(bool ok = true, ParseResultType v = ParseResultType::Matched, std::string e = {})
        : ok_(ok), val_(v), err_(std::move(e)) {}
    explicit operator bool() const { return ok_; }
    ParseResultType value() const { return val_; }
    const std::string& errorMessage() const { return err_; }
private:
    bool ok_;
    ParseResultType val_;
    std::string err_;
};

// The return object from Opt::parse with helpers used in the snippet
class InternalParseResult {
public:
    // Construct from a Result (used on validation/setFlag/setValue failures)
    explicit InternalParseResult(const Result& r)
        : success_(static_cast<bool>(r)), state_(ParseResultType::NoMatch, TokenStream{}), error_(r.errorMessage()) {}

    // Success helper
    static InternalParseResult ok(ParseState s) {
        InternalParseResult r;
        r.success_ = true;
        r.state_ = std::move(s);
        return r;
    }

    // Error helper (runtime error path)
    static InternalParseResult runtimeError(std::string msg) {
        InternalParseResult r;
        r.success_ = false;
        r.error_ = std::move(msg);
        return r;
    }

    bool success() const { return success_; }
    const ParseState& state() const { return state_; }
    const std::string& errorMessage() const { return error_; }

private:
    InternalParseResult() : success_(false), state_(ParseResultType::NoMatch, TokenStream{}) {}
    bool success_;
    ParseState state_;
    std::string error_;
};

// Bound reference base classes the Opt holds internally.
// We only declare the surface used by parse(); tests will mock these.
struct BoundRefBase {
    virtual ~BoundRefBase() = default;
    virtual bool isFlag() const = 0;
};

struct BoundFlagRefBase : BoundRefBase {
    ~BoundFlagRefBase() override = default;
    virtual Result setFlag(bool) = 0;
};

struct BoundValueRefBase : BoundRefBase {
    ~BoundValueRefBase() override = default;
    virtual Result setValue(std::string) = 0;
};

} // namespace Detail

// Testable Opt: we include the provided parse() definition verbatim,
// and expose deterministic knobs for validate() and isMatch() ONLY
// to drive parse() branches in a black-box way.
class Opt {
public:
    // Controls (observable only via parse() behavior)
    void setValidateResult(Detail::Result r) { validateResult_ = std::move(r); }
    void setMatchToken(bool b) { match_ = b; }
    void setBoundRef(std::unique_ptr<Detail::BoundRefBase> p) { m_ref = std::move(p); }

    // The method under test (from the prompt)
    Detail::InternalParseResult parse(std::string const&, Detail::TokenStream tokens) const {
        auto validationResult = validate();
        if (!validationResult)
            return Detail::InternalParseResult(validationResult);

        if (tokens && tokens->type == Detail::TokenType::Option) {
            auto const& token = *tokens;
            if (isMatch(token.token)) {
                if (m_ref->isFlag()) {
                    auto flagRef = static_cast<Detail::BoundFlagRefBase*>( m_ref.get());
                    auto result = flagRef->setFlag(true);
                    if (!result)
                        return Detail::InternalParseResult(result);
                    if (result.value() == Detail::ParseResultType::ShortCircuitAll)
                        return Detail::InternalParseResult::ok(
                            Detail::ParseState(result.value(), CATCH_MOVE(tokens)));
                } else {
                    auto valueRef = static_cast<Detail::BoundValueRefBase*>( m_ref.get());
                    ++tokens;
                    if (!tokens)
                        return Detail::InternalParseResult::runtimeError(
                            "Expected argument following " + token.token);
                    auto const& argToken = *tokens;
                    if (argToken.type != Detail::TokenType::Argument)
                        return Detail::InternalParseResult::runtimeError(
                            "Expected argument following " + token.token);
                    const auto result = valueRef->setValue(static_cast<std::string>(argToken.token));
                    if (!result)
                        return Detail::InternalParseResult(result);
                    if (result.value() == Detail::ParseResultType::ShortCircuitAll)
                        return Detail::InternalParseResult::ok(
                            Detail::ParseState(result.value(), CATCH_MOVE(tokens)));
                }
                return Detail::InternalParseResult::ok(
                    Detail::ParseState(Detail::ParseResultType::Matched, CATCH_MOVE(++tokens)));
            }
        }
        return Detail::InternalParseResult::ok(
            Detail::ParseState(Detail::ParseResultType::NoMatch, CATCH_MOVE(tokens)));
    }

private:
    // The "black-box" helpers used by parse(); we let tests configure their outcomes.
    Detail::Result validate() const { return validateResult_; }
    bool isMatch(const std::string&) const { return match_; }

    // Members used by parse()
    std::unique_ptr<Detail::BoundRefBase> m_ref;
    Detail::Result validateResult_{true, Detail::ParseResultType::Matched, {}};
    bool match_{false};
};

} // namespace Clara
} // namespace Catch

// -----------------------------
// Google Mock collaborators
// -----------------------------
namespace Catch { namespace Clara { namespace Detail {

class MockFlagRef : public BoundFlagRefBase {
public:
    MOCK_METHOD(bool, isFlag, (), (const, override));
    MOCK_METHOD(Result, setFlag, (bool), (override));
};

class MockValueRef : public BoundValueRefBase {
public:
    MOCK_METHOD(bool, isFlag, (), (const, override));
    MOCK_METHOD(Result, setValue, (std::string), (override));
};

}}} // namespace Catch::Clara::Detail

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// -----------------------------
// Tests
// -----------------------------

// No tokens at all -> NoMatch, success
TEST(OptParseTest_664, ReturnsNoMatchWhenNoTokens_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    // ref is required but won't be used (no tokens): give any valid mock
    auto ref = std::make_unique<MockFlagRef>();
    EXPECT_CALL(*ref, isFlag()).Times(0);
    opt.setBoundRef(std::move(ref));

    TokenStream ts{}; // empty
    auto res = opt.parse("--ignored", ts);

    EXPECT_TRUE(res.success());
    EXPECT_EQ(res.state().type, ParseResultType::NoMatch);
    EXPECT_EQ(res.state().tokens.index(), 0u);
}

// First token is Option but does not match -> NoMatch, success and no collaborator calls
TEST(OptParseTest_664, OptionTokenButNotMatching_YieldsNoMatch_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(false); // not matched

    auto ref = std::make_unique<MockFlagRef>();
    EXPECT_CALL(*ref, isFlag()).Times(0);
    opt.setBoundRef(std::move(ref));

    TokenStream ts({{TokenType::Option, "--alpha"}});
    auto res = opt.parse("", ts);

    EXPECT_TRUE(res.success());
    EXPECT_EQ(res.state().type, ParseResultType::NoMatch);
    // Iterator advanced? Not matched path returns original tokens unchanged
    EXPECT_EQ(res.state().tokens.index(), 0u);
}

// Validation fails -> returns error immediately, no collaborator calls
TEST(OptParseTest_664, ValidationFailureShortCircuits_664) {
    Opt opt;
    opt.setValidateResult(Result(false, ParseResultType::Matched, "validation failed"));

    auto ref = std::make_unique<MockFlagRef>();
    EXPECT_CALL(*ref, isFlag()).Times(0);
    opt.setBoundRef(std::move(ref));

    TokenStream ts({{TokenType::Option, "--flag"}});
    auto res = opt.parse("", ts);

    EXPECT_FALSE(res.success());
    EXPECT_THAT(res.errorMessage(), ::testing::HasSubstr("validation failed"));
}

// Flag option: setFlag(true) ok -> Matched and iterator moves past option
TEST(OptParseTest_664, FlagOption_SetsFlagAndMatches_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(true);

    auto ref = std::make_unique<MockFlagRef>();
    EXPECT_CALL(*ref, isFlag()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*ref, setFlag(true))
        .Times(1)
        .WillOnce(Return(Result(true, ParseResultType::Matched)));

    opt.setBoundRef(std::move(ref));

    TokenStream ts({{TokenType::Option, "--verbose"}, {TokenType::Argument, "extra"}});
    auto res = opt.parse("", ts);

    EXPECT_TRUE(res.success());
    EXPECT_EQ(res.state().type, ParseResultType::Matched);
    // After success path, parse returns ++tokens (past the option)
    EXPECT_EQ(res.state().tokens.index(), 1u);
}

// Flag option: setFlag returns ShortCircuitAll -> returns that type without consuming another token
TEST(OptParseTest_664, FlagOption_ShortCircuitsAll_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(true);

    auto ref = std::make_unique<MockFlagRef>();
    EXPECT_CALL(*ref, isFlag()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*ref, setFlag(true))
        .Times(1)
        .WillOnce(Return(Result(true, ParseResultType::ShortCircuitAll)));

    opt.setBoundRef(std::move(ref));

    TokenStream ts({{TokenType::Option, "-q"}});
    auto res = opt.parse("", ts);

    EXPECT_TRUE(res.success());
    EXPECT_EQ(res.state().type, ParseResultType::ShortCircuitAll);
    // In short-circuit branch for flag, tokens are returned without advancing
    EXPECT_EQ(res.state().tokens.index(), 0u);
}

// Flag option: setFlag fails -> error propagated
TEST(OptParseTest_664, FlagOption_SetFlagFailurePropagates_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(true);

    auto ref = std::make_unique<MockFlagRef>();
    EXPECT_CALL(*ref, isFlag()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*ref, setFlag(true))
        .Times(1)
        .WillOnce(Return(Result(false, ParseResultType::Matched, "cannot set flag")));

    opt.setBoundRef(std::move(ref));

    TokenStream ts({{TokenType::Option, "--badflag"}});
    auto res = opt.parse("", ts);

    EXPECT_FALSE(res.success());
    EXPECT_THAT(res.errorMessage(), ::testing::HasSubstr("cannot set flag"));
}

// Value option: missing argument after option -> runtimeError
TEST(OptParseTest_664, ValueOption_MissingArgument_YieldsRuntimeError_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(true);

    auto ref = std::make_unique<MockValueRef>();
    EXPECT_CALL(*ref, isFlag()).Times(1).WillOnce(Return(false));
    // setValue must NOT be called when missing argument
    EXPECT_CALL(*ref, setValue(_)).Times(0);

    opt.setBoundRef(std::move(ref));

    TokenStream ts({{TokenType::Option, "--output"}});
    auto res = opt.parse("", ts);

    EXPECT_FALSE(res.success());
    EXPECT_THAT(res.errorMessage(), ::testing::HasSubstr("Expected argument following --output"));
}

// Value option: next token is not an Argument -> runtimeError
TEST(OptParseTest_664, ValueOption_NonArgumentFollowing_YieldsRuntimeError_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(true);

    auto ref = std::make_unique<MockValueRef>();
    EXPECT_CALL(*ref, isFlag()).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*ref, setValue(_)).Times(0);

    opt.setBoundRef(std::move(ref));

    TokenStream ts({
        {TokenType::Option, "--file"},
        {TokenType::Option, "--oops"} // not an argument
    });
    auto res = opt.parse("", ts);

    EXPECT_FALSE(res.success());
    EXPECT_THAT(res.errorMessage(), ::testing::HasSubstr("Expected argument following --file"));
}

// Value option: happy path -> setValue called with the argument string; Matched and iterator unchanged beyond the argument (due to ++tokens then final ++tokens)
TEST(OptParseTest_664, ValueOption_SetValueAndMatches_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(true);

    auto ref = std::make_unique<MockValueRef>();
    EXPECT_CALL(*ref, isFlag()).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*ref, setValue("out.txt"))
        .Times(1)
        .WillOnce(Return(Result(true, ParseResultType::Matched)));

    opt.setBoundRef(std::move(ref));

    TokenStream ts({
        {TokenType::Option,  "--out"},
        {TokenType::Argument, "out.txt"},
        {TokenType::Argument, "ignored"}
    });
    auto res = opt.parse("", ts);

    EXPECT_TRUE(res.success());
    EXPECT_EQ(res.state().type, ParseResultType::Matched);
    // Flow: ++ to the argument (index 1), consume value, then return ++tokens (index 2)
    EXPECT_EQ(res.state().tokens.index(), 2u);
}

// Value option: setValue returns ShortCircuitAll -> that result is returned and tokens are not advanced past the argument
TEST(OptParseTest_664, ValueOption_ShortCircuitAll_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(true);

    auto ref = std::make_unique<MockValueRef>();
    EXPECT_CALL(*ref, isFlag()).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*ref, setValue("now"))
        .Times(1)
        .WillOnce(Return(Result(true, ParseResultType::ShortCircuitAll)));

    opt.setBoundRef(std::move(ref));

    TokenStream ts({
        {TokenType::Option,   "--time"},
        {TokenType::Argument, "now"}
    });
    auto res = opt.parse("", ts);

    EXPECT_TRUE(res.success());
    EXPECT_EQ(res.state().type, ParseResultType::ShortCircuitAll);
    // In short-circuit branch (value case), tokens are returned at current position (after ++ to arg, but without the final ++)
    EXPECT_EQ(res.state().tokens.index(), 1u);
}

// Value option: setValue failure -> error propagated
TEST(OptParseTest_664, ValueOption_SetValueFailurePropagates_664) {
    Opt opt;
    opt.setValidateResult(Result(true));
    opt.setMatchToken(true);

    auto ref = std::make_unique<MockValueRef>();
    EXPECT_CALL(*ref, isFlag()).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*ref, setValue("bad"))
        .Times(1)
        .WillOnce(Return(Result(false, ParseResultType::Matched, "invalid value")));

    opt.setBoundRef(std::move(ref));

    TokenStream ts({
        {TokenType::Option,   "--mode"},
        {TokenType::Argument, "bad"}
    });
    auto res = opt.parse("", ts);

    EXPECT_FALSE(res.success());
    EXPECT_THAT(res.errorMessage(), ::testing::HasSubstr("invalid value"));
}
