// File: tests/tokenstream_tests_1097.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_clara.hpp"  // uses the public interface only

using namespace Catch::Clara::Detail;

class TokenStreamTest_1097 : public ::testing::Test {
protected:
    // Helper to build an Args from argc/argv without assuming any internal details.
    // We intentionally do not construct Tokens directly (that would infer internals).
    static Args makeArgsFromVector(const std::vector<std::string>& v) {
        // Build a stable argv array whose char* pointers remain valid for the duration
        // of the call to Args' ctor.
        std::vector<std::unique_ptr<char[]>> storage;
        std::vector<char*> argvPtr;
        argvPtr.reserve(v.size());
        storage.reserve(v.size());
        for (const auto& s : v) {
            auto buf = std::make_unique<char[]>(s.size() + 1);
            std::memcpy(buf.get(), s.c_str(), s.size() + 1);
            argvPtr.push_back(buf.get());
            storage.push_back(std::move(buf));
        }

        // Construct Args in the most conservative, black-box-friendly way:
        // (int argc, const char* const* argv)
        // We do not rely on any other overloads or internal conventions.
        Args args(static_cast<int>(argvPtr.size()),
                  const_cast<const char* const*>(argvPtr.data()));
        return args; // return-by-value; Args is expected to be copyable/movable
    }
};

// --- Normal operation: construction from Args, iteration, and count agreement
TEST_F(TokenStreamTest_1097, IterateMatchesCount_1097) {
    // Given a typical argv-like input (program + options + values + positional)
    auto args = TokenStreamTest_1097::makeArgsFromVector(
        {"prog", "--opt", "val", "-f", "x", "pos1", "pos2"}
    );

    TokenStream ts(args);

    // Observable behavior: count() returns a stable size and iterating via ++ consumes that many.
    const size_t initialCount = ts.count();
    size_t seen = 0;
    while (static_cast<bool>(ts)) {
        // We only verify that dereferencing yields a Token object (no internal field checks).
        Token current = *ts;      // operator*()
        (void)current;            // suppress unused var warning
        const Token* ptr = ts.operator->(); // operator->()
        ASSERT_NE(ptr, nullptr);  // pointer form should be non-null while valid

        ++ts;                     // operator++()
        ++seen;
    }
    EXPECT_EQ(seen, initialCount);
}

// --- Boundary: empty/near-empty input should lead to zero tokens available
TEST_F(TokenStreamTest_1097, EmptyArgsYieldsNoTokens_1097) {
    // If only a program name is present, the stream may have no consumable tokens.
    // We do not assert exact policy; we assert consistent observable behavior.
    auto args = TokenStreamTest_1097::makeArgsFromVector({"prog"});

    TokenStream ts(args);
    const size_t c = ts.count();

    // On empty input, either count() is 0, or operator bool() is false (or both).
    if (c == 0) {
        EXPECT_FALSE(static_cast<bool>(ts));
    } else {
        // If count() reports > 0 (implementation-defined), ensure iteration matches.
        size_t steps = 0;
        while (ts) { (void)*ts; ++ts; ++steps; }
        EXPECT_EQ(steps, c);
    }
}

// --- Boundary: repeated incrementing past end should keep stream "false"
TEST_F(TokenStreamTest_1097, IncrementPastEndRemainsFalse_1097) {
    auto args = TokenStreamTest_1097::makeArgsFromVector({"prog", "--flag"});
    TokenStream ts(args);

    // Drain the stream completely.
    while (ts) { (void)*ts; ++ts; }

    // Now ts should be "false". Further increments should keep it non-usable/false.
    EXPECT_FALSE(static_cast<bool>(ts));

    // Apply multiple increments; behavior should remain stable (still false).
    for (int i = 0; i < 3; ++i) {
        ++ts;
        EXPECT_FALSE(static_cast<bool>(ts));
    }
}

// --- Operator semantics: prefix ++ chaining returns a reference (allows multiple ++)
TEST_F(TokenStreamTest_1097, PrefixIncrementIsChainable_1097) {
    auto args = TokenStreamTest_1097::makeArgsFromVector({"prog", "-a", "v", "p"});
    TokenStream ts(args);

    // If there are at least two tokens, "++ ++ts" should be well-formed.
    // We do not depend on how many tokens precisely; we guard via operator bool().
    if (ts) {
        TokenStream& r1 = ++ts;
        (void)r1;
        // Chaining another ++ should still be valid if tokens remain.
        if (ts) {
            TokenStream& r2 = ++ts;
            (void)r2;
        }
        // No specific state assertions beyond "no crash" and "bool" remains consistent.
        (void)ts ? (void)0 : (void)0;
    } else {
        SUCCEED() << "Stream empty; chainability not applicable but test remains valid.";
    }
}

// --- Smoke: constructing via (Iterator, Iterator) should be available and usable.
// NOTE: We DO NOT construct Tokens directly (that would rely on internal Token details).
//       Instead, we obtain the iterator range from Args's underlying container by
//       creating a temporary TokenStream and reusing its public iteration to capture
//       tokens, then feed them back in as an iterator range if the public Iterator
//       type is compatible. If not, we gracefully skip without failing.
TEST_F(TokenStreamTest_1097, IteratorConstructorSmoke_1097) {
    auto args = TokenStreamTest_1097::makeArgsFromVector({"prog", "--x", "1", "y"});
    TokenStream fromArgs(args);

    // Collect tokens through the public interface (black-box).
    std::vector<Token> collected;
    while (fromArgs) {
        collected.push_back(*fromArgs);
        ++fromArgs;
    }

    // If no tokens were produced, the iterator-ctor test is vacuous but still valid.
    if (collected.empty()) {
        SUCCEED() << "No tokens available from Args; iterator-ctor smoke test skipped.";
        return;
    }

    // Construct via iterator range using the standard vector iterators.
    // This assumes the public 'Iterator' is compatible with std::vector<Token>::const_iterator.
    // If not in your codebase, feel free to adjust the container type to match 'Iterator'.
    TokenStream fromIter(collected.cbegin(), collected.cend());

    // Observable behavior: iterating should reproduce the same count.
    const size_t expected = collected.size();
    size_t seen = 0;
    while (fromIter) {
        (void)*fromIter;
        ++fromIter;
        ++seen;
    }
    EXPECT_EQ(seen, expected);
}
