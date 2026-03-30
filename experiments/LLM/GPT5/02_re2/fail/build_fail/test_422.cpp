// File: simplify_test_422.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"

using re2::Regexp;

class SimplifyTest_422 : public ::testing::Test {
protected:
  // Helper to parse a pattern into a Regexp*. Returns non-null on success.
  Regexp* Parse(const std::string& pattern,
                Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0)) {
    re2::RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    return re;
  }

  // Safe Decref helper (accepts nullptr).
  void DecrefIf(Regexp* re) {
    if (re) re->Decref();
  }

  // Equality helper using the public testing-only comparator.
  bool StructurallyEqual(Regexp* a, Regexp* b) {
    // The comparator is an instance method; call it on one of the operands.
    return a->RegexpEqualTestingOnly(a, b);
  }
};

// --- Tests ---

// Basic smoke: Simplify returns a non-null Regexp* for a simple literal.
TEST_F(SimplifyTest_422, SimplifyReturnsNonNullForLiteral_422) {
  Regexp* original = Parse("abc");
  ASSERT_NE(original, nullptr) << "Parse should succeed for 'abc'";

  Regexp* simplified = original->Simplify();

  EXPECT_NE(simplified, nullptr) << "Simplify should return a non-null Regexp*";
  // Clean up
  DecrefIf(simplified);
  DecrefIf(original);
}

// Calling Simplify should not mutate the original object's observable string form.
TEST_F(SimplifyTest_422, SimplifyDoesNotMutateOriginalToString_422) {
  Regexp* original = Parse("(ab|ab)");
  ASSERT_NE(original, nullptr);

  const std::string before = original->ToString();

  Regexp* simplified = original->Simplify();
  ASSERT_NE(simplified, nullptr);

  const std::string after = original->ToString();

  EXPECT_EQ(before, after)
      << "Original Regexp's ToString() must remain stable after Simplify()";

  DecrefIf(simplified);
  DecrefIf(original);
}

// Idempotence: Simplifying an already-simplified regexp should yield an equivalent regexp.
TEST_F(SimplifyTest_422, SimplifyIsIdempotent_422) {
  Regexp* original = Parse("a(?:b)c|ab?c");
  ASSERT_NE(original, nullptr);

  Regexp* once = original->Simplify();
  ASSERT_NE(once, nullptr);

  Regexp* twice = once->Simplify();
  ASSERT_NE(twice, nullptr);

  // Compare structural equality via the testing-only comparator.
  EXPECT_TRUE(StructurallyEqual(once, twice))
      << "Simplify() should be idempotent (result structurally equal)";

  DecrefIf(twice);
  DecrefIf(once);
  DecrefIf(original);
}

// Flags preservation: parse flags observable via parse_flags() should be preserved by Simplify().
TEST_F(SimplifyTest_422, SimplifyPreservesParseFlags_422) {
  // Use a non-zero flag combination if available; fallback to 0 is fine too since we only
  // assert preservation (not specific values). Here we just pass 0 explicitly.
  auto flags = static_cast<Regexp::ParseFlags>(0);

  Regexp* original = Parse("[a-c]{1,3}", flags);
  ASSERT_NE(original, nullptr);

  const auto before_flags = original->parse_flags();

  Regexp* simplified = original->Simplify();
  ASSERT_NE(simplified, nullptr);

  const auto after_flags = simplified->parse_flags();
  EXPECT_EQ(before_flags, after_flags)
      << "Simplify() should preserve observable parse flags";

  DecrefIf(simplified);
  DecrefIf(original);
}

// Round-trip stability: ToString() of the simplified regexp should parse back and
// be structurally equal to the simplified form (i.e., produces a valid, equivalent regexp).
TEST_F(SimplifyTest_422, SimplifiedToStringParsesBackEquivalently_422) {
  Regexp* original = Parse("(?:a|a)b*");
  ASSERT_NE(original, nullptr);

  Regexp* simplified = original->Simplify();
  ASSERT_NE(simplified, nullptr);

  const std::string simp_str = simplified->ToString();

  Regexp* reparsed = Parse(simp_str);
  ASSERT_NE(reparsed, nullptr) << "Simplified ToString() should be parsable";

  EXPECT_TRUE(StructurallyEqual(simplified, reparsed))
      << "Re-parsed ToString() must be structurally equal to simplified regexp";

  DecrefIf(reparsed);
  DecrefIf(simplified);
  DecrefIf(original);
}

// Sanity on a few boundary-ish shapes: empty string, single char class, and simple repetition.
// We only assert non-null and basic well-formedness (no assumptions about specific rewrites).
TEST_F(SimplifyTest_422, SimplifyOnVariousSimpleShapes_422) {
  const char* patterns[] = {"", "[a]", "a{1,3}", "(?:)"};
  for (const char* pat : patterns) {
    Regexp* re = Parse(pat);
    ASSERT_NE(re, nullptr) << "Parse should succeed for pattern: " << pat;

    Regexp* simplified = re->Simplify();
    EXPECT_NE(simplified, nullptr) << "Simplify returned null for pattern: " << pat;

    // Basic invariant: Simplify twice stays equivalent.
    if (simplified) {
      Regexp* simplified2 = simplified->Simplify();
      ASSERT_NE(simplified2, nullptr);
      EXPECT_TRUE(StructurallyEqual(simplified, simplified2))
          << "Idempotence should hold for pattern: " << pat;
      DecrefIf(simplified2);
    }

    DecrefIf(simplified);
    DecrefIf(re);
  }
}
