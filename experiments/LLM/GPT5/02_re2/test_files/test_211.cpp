// File: walker_previsit_test_211.cc

#include <string>
#include <climits>
#include "gtest/gtest.h"

// Include the header under test (path per prompt)
#include "TestProjects/re2/re2/walker-inl.h"

namespace {

// Simple POD used to verify behavior with user-defined types.
struct Payload {
  int a;
  std::string b;
  bool operator==(const Payload& other) const {
    return a == other.a && b == other.b;
  }
};

}  // namespace

// --- Tests ---

// Verifies that PreVisit returns the parent_arg unchanged for an int.
// Also verifies the stop flag is not modified as an observable side effect.
TEST(WalkerPreVisitTest_211, ReturnsParentArg_Int_211) {
  using WalkerT = re2::Regexp::Walker<int>;
  WalkerT walker;

  re2::Regexp* re = nullptr;  // Treat as opaque; we don't rely on any internals.
  bool stop = false;

  const int parent_arg = 42;
  const int result = walker.PreVisit(re, parent_arg, &stop);

  EXPECT_EQ(result, parent_arg);
  EXPECT_FALSE(stop);  // no observable modification expected
}

// Verifies that PreVisit returns the parent_arg unchanged for std::string.
// Confirms empty string boundary case works.
TEST(WalkerPreVisitTest_211, ReturnsParentArg_String_Empty_211) {
  using WalkerT = re2::Regexp::Walker<std::string>;
  WalkerT walker;

  re2::Regexp* re = nullptr;
  bool stop = true;  // start as true; ensure not changed by PreVisit

  const std::string parent_arg = "";
  const std::string result = walker.PreVisit(re, parent_arg, &stop);

  EXPECT_EQ(result, parent_arg);
  EXPECT_TRUE(stop);
}

// Verifies that PreVisit returns the parent_arg for a non-empty string.
TEST(WalkerPreVisitTest_211, ReturnsParentArg_String_NonEmpty_211) {
  using WalkerT = re2::Regexp::Walker<std::string>;
  WalkerT walker;

  re2::Regexp* re = nullptr;
  bool stop = false;

  const std::string parent_arg = "abcXYZ";
  const std::string result = walker.PreVisit(re, parent_arg, &stop);

  EXPECT_EQ(result, parent_arg);
  EXPECT_FALSE(stop);
}

// Verifies behavior with a user-defined (copyable) type.
// Ensures the value returned equals the input value.
TEST(WalkerPreVisitTest_211, ReturnsParentArg_UserDefinedType_211) {
  using WalkerT = re2::Regexp::Walker<Payload>;
  WalkerT walker;

  re2::Regexp* re = nullptr;
  bool stop = false;

  const Payload parent_arg{123, "payload"};
  const Payload result = walker.PreVisit(re, parent_arg, &stop);

  EXPECT_EQ(result, parent_arg);
  EXPECT_FALSE(stop);
}

// Boundary test with extreme integer values to ensure no unexpected changes.
TEST(WalkerPreVisitTest_211, ReturnsParentArg_IntBoundaryValues_211) {
  using WalkerT = re2::Regexp::Walker<int>;
  WalkerT walker;

  re2::Regexp* re = nullptr;
  bool stop = false;

  const int cases[] = {0, -1, INT_MAX, INT_MIN};
  for (int parent_arg : cases) {
    stop = !stop;  // flip to see it remains unchanged by call
    const int before_stop = stop;
    const int result = walker.PreVisit(re, parent_arg, &stop);
    EXPECT_EQ(result, parent_arg);
    EXPECT_EQ(stop, before_stop);
  }
}

// Smoke test to confirm passing a null Regexp* does not crash and returns arg.
// (We only observe the return value per interface; no internals assumed.)
TEST(WalkerPreVisitTest_211, AcceptsNullRegexpPointer_211) {
  using WalkerT = re2::Regexp::Walker<std::string>;
  WalkerT walker;

  re2::Regexp* re = nullptr;
  bool stop = false;

  const std::string parent_arg = "safe";
  const std::string result = walker.PreVisit(re, parent_arg, &stop);

  EXPECT_EQ(result, parent_arg);
  EXPECT_FALSE(stop);
}
