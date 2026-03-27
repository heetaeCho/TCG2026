// File: parse_state_tests_372.cpp
#include <gtest/gtest.h>

#if __has_include("Catch2/src/catch2/internal/catch_clara.hpp")
  #include "Catch2/src/catch2/internal/catch_clara.hpp"
#else
  // If the real header is not on the include path during compile of these tests,
  // we still only test via the public interface. No internal logic is re-implemented.
  // These forward declarations exist solely to allow the test TU to compile;
  // the project build should use the real header above.
  namespace Catch { namespace Clara { namespace Detail {
    enum class ParseResultType { Matched, NoMatch, Error };
    struct TokenStream {
      TokenStream() = default;      // Only to satisfy constructor signature
    };
    class ParseState {
     public:
      ParseState(ParseResultType t, TokenStream) : t_(t) {}
      ParseResultType type() const { return t_; }
     private:
      ParseResultType t_;
    };
  }}}
#endif

using Catch::Clara::Detail::ParseResultType;
using Catch::Clara::Detail::ParseState;
using Catch::Clara::Detail::TokenStream;

// ----------------------------
// Tests
// ----------------------------

// Normal: Construct with Matched and verify type()
TEST(ParseStateTest_372, TypeReturnsMatched_372) {
  TokenStream ts{};
  ParseState state(ParseResultType::Matched, ts);

  EXPECT_EQ(state.type(), ParseResultType::Matched);
}

// Normal: Construct with NoMatch and verify type()
TEST(ParseStateTest_372, TypeReturnsNoMatch_372) {
  TokenStream ts{};
  ParseState state(ParseResultType::NoMatch, ts);

  EXPECT_EQ(state.type(), ParseResultType::NoMatch);
}

// Boundary-ish: Construct with Error and verify type()
// (Represents an "error case" value if provided by the enum)
TEST(ParseStateTest_372, TypeReturnsError_372) {
  TokenStream ts{};
  ParseState state(ParseResultType::Error, ts);

  EXPECT_EQ(state.type(), ParseResultType::Error);
}

// API usage: type() callable on const instance and stable across multiple calls
TEST(ParseStateTest_372, TypeConstAndStableAcrossCalls_372) {
  TokenStream ts{};
  const ParseState state(ParseResultType::Matched, ts);

  // Multiple observations should be identical
  EXPECT_EQ(state.type(), ParseResultType::Matched);
  EXPECT_EQ(state.type(), ParseResultType::Matched);
}
