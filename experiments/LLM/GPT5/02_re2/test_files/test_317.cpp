// File: compiler_copy_test_317.cc
#include <gtest/gtest.h>

#include "re2/regexp.h"   // If your project exposes Compiler/Frag via a header, include it.
#include "re2/compile.h"  // Adjust includes to wherever Compiler/Frag are declared in your tree.

using namespace re2;

class CompilerCopyTest_317 : public ::testing::Test {
protected:
  // Helper to compare two Frags by observable public fields.
  static void ExpectFragEq(const Frag& a, const Frag& b) {
    EXPECT_EQ(a.begin, b.begin);
    // PatchList is an opaque type here; comparison via equality may not be available.
    // We only compare via what we can observe: assuming equality can be checked by value.
    // If PatchList has no operator==, compare a sentinel property or skip—
    // but we can still check address-size equality by memcmp if allowed.
    // To remain within interface-only constraints, we will not dig into PatchList internals.
    // So we omit 'end' comparison unless operator== is available. If it is, uncomment:
    // EXPECT_EQ(a.end, b.end);
    EXPECT_EQ(a.nullable, b.nullable);
  }
};

// Normal operation: Copy returns the same fragment as NoMatch(), regardless of input.
TEST_F(CompilerCopyTest_317, CopyReturnsNoMatch_317) {
  Compiler c;

  // Expected result based on the public interface: Copy returns NoMatch().
  Frag expected = c.NoMatch();

  // Use a valid Frag obtained from the public API as input.
  Frag input = expected;  // Any Frag is acceptable; we use a valid one from NoMatch().
  Frag actual = c.Copy(input);

  ExpectFragEq(actual, expected);
}

// Boundary-ish input: Using a default-constructed Frag as input should still yield NoMatch().
TEST_F(CompilerCopyTest_317, CopyWithDefaultConstructedFragReturnsNoMatch_317) {
  Compiler c;

  Frag expected = c.NoMatch();

  // Default-constructed Frag (constructed via public constructor).
  Frag default_input;
  Frag actual = c.Copy(default_input);

  ExpectFragEq(actual, expected);
}

// Repeated calls: Copy can be called multiple times and should consistently return NoMatch().
TEST_F(CompilerCopyTest_317, CopyIsConsistentAcrossMultipleCalls_317) {
  Compiler c;

  Frag expected = c.NoMatch();

  Frag input = expected;   // Use a known-valid Frag.
  Frag a = c.Copy(input);
  Frag b = c.Copy(input);
  Frag c2 = c.Copy(expected);  // Call again with same value for good measure.

  ExpectFragEq(a, expected);
  ExpectFragEq(b, expected);
  ExpectFragEq(c2, expected);
}
