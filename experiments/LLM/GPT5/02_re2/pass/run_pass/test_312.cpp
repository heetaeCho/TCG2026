// File: compiler_endrange_test_312.cc
#include <gtest/gtest.h>
#include <type_traits>
#include <cstring>

// We include the implementation unit directly to obtain the public interface
// shown in the prompt. If your build exposes a header instead, switch to that.
#include "re2/compile.cc"

namespace re2 {

// A small helper that compares two Frags by value without relying on
// any private state or undocumented behavior. If Frag is trivially
// copyable, we can memcmp the bytes; otherwise we only assert that
// creating/copying Frags works and that EndRange is callable.
static bool FragBitwiseEqual(const Frag& a, const Frag& b) {
#if defined(__cpp_lib_is_trivially_copyable) || __cplusplus >= 201103L
  if (std::is_trivially_copyable<Frag>::value) {
    return std::memcmp(&a, &b, sizeof(Frag)) == 0;
  }
#endif
  // If Frag is not trivially copyable, fall back to address/alias check
  // by copying into two temporaries and comparing sizeof to avoid UB.
  // We cannot assert "equality" in that case; return false to skip equality
  // specific assertions in tests (they will guard on trivially-copyable).
  (void)a; (void)b;
  return false;
}

class CompilerEndRangeTest_312 : public ::testing::Test {
 protected:
  Compiler c_;  // Fresh compiler per test
};

// --- Normal operation ---

// After beginning a range and adding a simple Latin-1 rune interval,
// EndRange should return a Frag that (observably) stabilizes for repeated calls.
TEST_F(CompilerEndRangeTest_312, EndRange_ReturnsStableFragAfterSimpleLatin1_312) {
  c_.BeginRange();
  c_.AddRuneRangeLatin1('a', 'z', /*foldcase=*/false);

  Frag f1 = c_.EndRange();
  Frag f2 = c_.EndRange();  // repeated call without mutation

  // EndRange should be idempotent between calls when the underlying range
  // hasn't changed. If Frag is trivially copyable, compare by bits.
  if (std::is_trivially_copyable<Frag>::value) {
    EXPECT_TRUE(FragBitwiseEqual(f1, f2));
  } else {
    // At minimum, verify that the API is callable and returns objects.
    SUCCEED();
  }
}

// UTF-8 path: adding a non-Latin1 range and folding flag should still
// produce a consistent Frag via EndRange.
TEST_F(CompilerEndRangeTest_312, EndRange_ReturnsStableFragAfterUTF8_312) {
  c_.BeginRange();
  // Example: basic BMP slice; values chosen to be valid runes without
  // assuming any internal semantics.
  c_.AddRuneRangeUTF8(0x0400 /*Cyrillic*/, 0x04FF, /*foldcase=*/true);

  Frag f1 = c_.EndRange();
  Frag f2 = c_.EndRange();

  if (std::is_trivially_copyable<Frag>::value) {
    EXPECT_TRUE(FragBitwiseEqual(f1, f2));
  } else {
    SUCCEED();
  }
}

// Mixing helpers: Latin1 + UTF8 additions before EndRange should be supported.
TEST_F(CompilerEndRangeTest_312, EndRange_AcceptsMixedAdds_312) {
  c_.BeginRange();
  c_.AddRuneRangeLatin1('A', 'Z', /*foldcase=*/true);
  c_.AddRuneRangeUTF8(0x0100, 0x017F, /*foldcase=*/false); // Latin Extended-A

  Frag f = c_.EndRange();

  // We can't assert internal contents; ensure the Frag is well-formed/usable
  // as an argument to other public combinators (black-box composition).
  // Using Nop() and Cat() verifies Frag can participate in composition.
  Frag nop = c_.Nop();
  Frag cat = c_.Cat(f, nop);
  (void)cat;

  SUCCEED();
}

// --- Boundary-like behavior ---

// Calling EndRange() without a preceding BeginRange(): the API should be callable
// and return *some* Frag. We don't assume what it contains; we only assert that
// it composes and is stable across repeated calls if no mutations happen.
TEST_F(CompilerEndRangeTest_312, EndRange_WithoutBeginRange_IsCallableAndStable_312) {
  Frag f1 = c_.EndRange();
  Frag f2 = c_.EndRange();

  if (std::is_trivially_copyable<Frag>::value) {
    EXPECT_TRUE(FragBitwiseEqual(f1, f2));
  } else {
    SUCCEED();
  }

  // Ensure it's usable in other public methods without crashing.
  Frag alt = c_.Alt(f1, f2);
  (void)alt;
  SUCCEED();
}

// Re-beginning a range after having finalized one should change the result
// once we add different data before calling EndRange again.
TEST_F(CompilerEndRangeTest_312, EndRange_ChangesAfterNewBeginAndDifferentAdds_312) {
  // First range
  c_.BeginRange();
  c_.AddRuneRangeLatin1('0', '9', /*foldcase=*/false);
  Frag first = c_.EndRange();

  // Second, different range
  c_.BeginRange();
  c_.AddRuneRangeLatin1('a', 'f', /*foldcase=*/false);
  Frag second = c_.EndRange();

  if (std::is_trivially_copyable<Frag>::value) {
    EXPECT_FALSE(FragBitwiseEqual(first, second));
  } else {
    // If we can't compare by bits portably, just ensure both are usable.
    Frag combined = c_.Alt(first, second);
    (void)combined;
    SUCCEED();
  }
}

// --- Idempotence under no-op API usage ---

// Ensures that calling EndRange, then using unrelated combinators that do not
// mutate the active rune range state, doesn't alter subsequent EndRange output
// unless we call BeginRange/Add* again.
TEST_F(CompilerEndRangeTest_312, EndRange_UnchangedByUnrelatedCombinators_312) {
  c_.BeginRange();
  c_.AddRuneRangeLatin1('x', 'x', /*foldcase=*/false);
  Frag base = c_.EndRange();

  // Use other public methods that should not mutate the current rune-range bucket.
  Frag n = c_.Nop();
  Frag m = c_.Match(123);
  (void)c_.Cat(n, m);
  (void)c_.Alt(n, m);
  (void)c_.Quest(n, /*nongreedy=*/false);
  (void)c_.Star(n, /*nongreedy=*/true);
  (void)c_.Plus(n, /*nongreedy=*/false);

  Frag again = c_.EndRange();
  if (std::is_trivially_copyable<Frag>::value) {
    EXPECT_TRUE(FragBitwiseEqual(base, again));
  } else {
    SUCCEED();
  }
}

}  // namespace re2
