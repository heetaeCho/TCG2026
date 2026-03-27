// File: regexp_alternate_test_342.cc

#include <gtest/gtest.h>

namespace re2 {

// --- Minimal declarations needed for observing call forwarding ---
// These match the interface names/types used by Alternate(...).
// We do NOT re-implement internal logic.

enum RegexpOp {
  // Only the value under test is required here.
  kRegexpAlternate = 6
};

// ParseFlags is an internal type in re2; we only need a compatible placeholder
// to compile our test double signature without touching internals.
using ParseFlags = int;

// Forward declaration for the class type so we can define our test double.
// We are not accessing any private fields or behavior.
class Regexp;

// Storage for capturing the most recent invocation to ConcatOrAlternate.
struct ConcatOrAltCall {
  bool         called = false;
  RegexpOp     op{};
  Regexp**     subs = nullptr;
  int          nsubs = 0;
  ParseFlags   flags = 0;
  bool         can_factor = false;
};

// Expose a single global capture for assertions in tests.
inline ConcatOrAltCall g_last_call;

// A unique sentinel pointer to verify return-value propagation.
// We never dereference this; it’s just for identity comparison.
inline Regexp* const kSentinelReturn =
    reinterpret_cast<Regexp*>(static_cast<uintptr_t>(0x1D00F342));

// ---- Test double for the private helper ----
// We define the same qualified name so the linker binds the call from
// Regexp::Alternate(...) here. This only records parameters & returns a
// known pointer; it does NOT simulate internal behavior.
Regexp* Regexp::ConcatOrAlternate(RegexpOp op,
                                  Regexp** subs,
                                  int nsubs,
                                  ParseFlags flags,
                                  bool can_factor) {
  g_last_call = {};
  g_last_call.called = true;
  g_last_call.op = op;
  g_last_call.subs = subs;
  g_last_call.nsubs = nsubs;
  g_last_call.flags = flags;
  g_last_call.can_factor = can_factor;
  return kSentinelReturn;
}

}  // namespace re2

// We now include only the declaration that provides Regexp::Alternate.
// We do NOT include internal headers; we don't need them for black-box testing.
// Declare just enough of the API surface to call Alternate(...) from tests.

namespace re2 {

// Provide a minimal declaration of Regexp that exposes ONLY the public
// Alternate(...) we are testing, and declares the helper for our test double.
// This keeps us from touching or depending on any private state.
class Regexp {
public:
  // The method under test:
  Regexp* Alternate(Regexp** sub, int nsub, ParseFlags flags);

  // Declaration matching our test double (defined above).
  static Regexp* ConcatOrAlternate(RegexpOp op,
                                   Regexp** subs,
                                   int nsubs,
                                   ParseFlags flags,
                                   bool can_factor);
};

// We don’t construct/destroy any real instances that require internals —
// to call a non-static member Alternate(...) we still need an object. Since
// we never touch internals, a trivial object is sufficient for the call site.
// (No dereference/teardown of the result happens in tests.)

}  // namespace re2

using re2::Regexp;
using re2::RegexpOp;
using re2::kRegexpAlternate;
using re2::g_last_call;
using re2::kSentinelReturn;
using re2::ParseFlags;

// ----------------------- Tests -----------------------

TEST(RegexpAlternate_342, ForwardsParametersAndSetsOpAndCanFactor_342) {
  Regexp re;  // Trivial instance, we only need to invoke the method.

  // Arrange: a small array of dummy subexpressions (we never dereference).
  Regexp* subs_storage[3] = {reinterpret_cast<Regexp*>(0x10),
                             reinterpret_cast<Regexp*>(0x20),
                             reinterpret_cast<Regexp*>(0x30)};
  Regexp** subs = subs_storage;
  const int nsubs = 3;
  const ParseFlags flags = 0x1234;

  // Act
  (void)re.Alternate(subs, nsubs, flags);

  // Assert (observable via our call-capture test double)
  ASSERT_TRUE(g_last_call.called) << "ConcatOrAlternate was not invoked";
  EXPECT_EQ(g_last_call.op, kRegexpAlternate);
  EXPECT_EQ(g_last_call.subs, subs);
  EXPECT_EQ(g_last_call.nsubs, nsubs);
  EXPECT_EQ(g_last_call.flags, flags);
  EXPECT_TRUE(g_last_call.can_factor) << "Alternate must pass can_factor=true";
}

TEST(RegexpAlternate_342, PropagatesReturnValueFromHelper_342) {
  Regexp re;

  Regexp* subs_storage[1] = {reinterpret_cast<Regexp*>(0xAA)};
  Regexp** subs = subs_storage;

  // Act
  Regexp* out = re.Alternate(subs, /*nsub=*/1, /*flags=*/0);

  // Assert
  // We only check identity: the public method should return exactly what the
  // helper returned (sentinel), without modification or extra allocations.
  EXPECT_EQ(out, kSentinelReturn);
}

