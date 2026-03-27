// File: CharClassBuilder_interface_tests_600.cc

#include <gtest/gtest.h>
#include <type_traits>
#include "re2/regexp.h"

namespace {

using re2::CharClassBuilder;

TEST(CharClassBuilderTest_600, TypeTraits_CopyAndAssignAreDeleted_600) {
  static_assert(!std::is_copy_constructible<CharClassBuilder>::value,
                "CharClassBuilder must not be copy-constructible");
  static_assert(!std::is_copy_assignable<CharClassBuilder>::value,
                "CharClassBuilder must not be copy-assignable");
}

TEST(CharClassBuilderTest_600, DefaultConstructible_600) {
  // Verifies that default construction is available via the public interface.
  EXPECT_NO_THROW({
    CharClassBuilder ccb;
    (void)ccb;
  });
}

TEST(CharClassBuilderTest_600, PublicMethodReturnTypes_600) {
  using IteratorT = CharClassBuilder::iterator;

  // Instantiate an object to use decltype on member calls.
  CharClassBuilder ccb;

  // These expressions are not executed; only their types are examined.
  // Still, keep them in a noexcept block to ensure they are ODR-used safely.
  EXPECT_NO_THROW({
    // begin/end types
    static_assert(std::is_same<decltype(ccb.begin()), IteratorT>::value,
                  "begin() must return CharClassBuilder::iterator");
    static_assert(std::is_same<decltype(ccb.end()), IteratorT>::value,
                  "end() must return CharClassBuilder::iterator");

    // size/empty/full
    static_assert(std::is_same<decltype(ccb.size()), int>::value,
                  "size() must return int");
    static_assert(std::is_same<decltype(ccb.empty()), bool>::value,
                  "empty() must return bool");
    static_assert(std::is_same<decltype(ccb.full()), bool>::value,
                  "full() must return bool");
  });
}

TEST(CharClassBuilderTest_600, CallableSignatures_BasicOperations_600) {
  CharClassBuilder ccb;
  // Use Rune as provided by the production headers.
  // We only rely on the type name; no assumptions about internal behavior.
  re2::Rune r0 = 0;
  re2::Rune r1 = 1;

  EXPECT_NO_FATAL_FAILURE({
    // AddRange and Contains should be callable and return bool
    bool added1 = ccb.AddRange(r0, r1);
    (void)added1;

    bool contains0 = ccb.Contains(r0);
    (void)contains0;

    // FoldsASCII should be callable and return bool
    bool folds = ccb.FoldsASCII();
    (void)folds;
  });
}

TEST(CharClassBuilderTest_600, IteratorPresenceAndUsability_600) {
  CharClassBuilder ccb;

  EXPECT_NO_FATAL_FAILURE({
    auto it = ccb.begin();
    auto it_end = ccb.end();
    // We do not assume anything about ordering or contents; just that
    // iterator objects are obtainable and comparable for equality/inequality.
    // If inequality is not supported, the following lines will fail to compile,
    // which is correct for an interface conformance test.
    (void)(it == it_end);
    (void)(it != it_end);
  });
}

TEST(CharClassBuilderTest_600, CompositeOperations_AreCallable_600) {
  CharClassBuilder ccbA;
  CharClassBuilder ccbB;

  EXPECT_NO_FATAL_FAILURE({
    // AddCharClass accepts a pointer to another CharClassBuilder
    ccbA.AddCharClass(&ccbB);

    // RemoveAbove & Negate should be callable
    ccbA.RemoveAbove(static_cast<re2::Rune>(0x7F));
    ccbA.Negate();
  });
}

TEST(CharClassBuilderTest_600, CopyFactory_ReturnsPointerTypes_600) {
  CharClassBuilder ccb;

  EXPECT_NO_FATAL_FAILURE({
    // Copy and GetCharClass are callable and return pointer types.
    CharClassBuilder* clone = ccb.Copy();
    // We do not assume ownership or lifetime semantics here.
    // Simply ensure the type is correct and pointer value is observable.
    (void)clone;

    re2::CharClass* cls = ccb.GetCharClass();
    (void)cls;
  });
}

TEST(CharClassBuilderTest_600, AddRangeFlags_IsCallable_600) {
  CharClassBuilder ccb;

  // We do not depend on specific flag values; use a default-initialized one.
  re2::Regexp::ParseFlags flags = static_cast<re2::Regexp::ParseFlags>(0);

  EXPECT_NO_FATAL_FAILURE({
    ccb.AddRangeFlags(static_cast<re2::Rune>(0), static_cast<re2::Rune>(0x10), flags);
  });
}

TEST(CharClassBuilderTest_600, BoundaryCalls_DoNotAssumeBehavior_600) {
  CharClassBuilder ccb;

  EXPECT_NO_FATAL_FAILURE({
    // Call with lo == hi (single code point)
    (void)ccb.AddRange(static_cast<re2::Rune>(0x41), static_cast<re2::Rune>(0x41));

    // Call with potential edge values; we do not assume outcomes,
    // only that these are valid invocations per the interface.
    (void)ccb.AddRange(static_cast<re2::Rune>(0), static_cast<re2::Rune>(0));
    (void)ccb.AddRange(static_cast<re2::Rune>(0x10FFFF), static_cast<re2::Rune>(0x10FFFF));

    // Contains on the same boundary values is callable
    (void)ccb.Contains(static_cast<re2::Rune>(0));
    (void)ccb.Contains(static_cast<re2::Rune>(0x10FFFF));
  });
}

}  // namespace
