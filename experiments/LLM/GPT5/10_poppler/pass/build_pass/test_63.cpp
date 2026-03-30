// TEST_ID: 63
// File: object_ref_hash_test_63.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <functional>
#include <type_traits>

#include "poppler/Object.h"

namespace {

class RefHashTest_63 : public ::testing::Test {};

TEST_F(RefHashTest_63, HashIsCallableAndNoexcept_63) {
  // Verify the hashing functor is callable and marked noexcept (as declared).
  static_assert(std::is_default_constructible_v<std::hash<Ref>>,
                "std::hash<Ref> must be default constructible");
  static_assert(std::is_nothrow_invocable_r_v<std::size_t, std::hash<Ref>, Ref>,
                "std::hash<Ref>::operator()(Ref) should be noexcept and return size_t");

  std::hash<Ref> h;
  Ref r{1, 2};
  (void)h(r);  // Should compile and not throw.
}

TEST_F(RefHashTest_63, SameInputProducesSameHash_63) {
  std::hash<Ref> h;

  Ref r{123, 456};
  const std::size_t a = h(r);
  const std::size_t b = h(r);

  EXPECT_EQ(a, b);
}

TEST_F(RefHashTest_63, MatchesDocumentedCombinationForTypicalValues_63) {
  // The provided implementation combines std::hash<int> of (num, gen)
  // using XOR and a left shift of the gen hash.
  std::hash<Ref> href;

  Ref r{7, 11};

  const std::size_t expected =
      std::hash<int>{}(r.num) ^ (std::hash<int>{}(r.gen) << 1);

  EXPECT_EQ(href(r), expected);
}

TEST_F(RefHashTest_63, ChangingNumChangesHashPerCombination_63) {
  std::hash<Ref> href;

  Ref a{10, 20};
  Ref b{11, 20};

  const std::size_t expected_a =
      std::hash<int>{}(a.num) ^ (std::hash<int>{}(a.gen) << 1);
  const std::size_t expected_b =
      std::hash<int>{}(b.num) ^ (std::hash<int>{}(b.gen) << 1);

  EXPECT_EQ(href(a), expected_a);
  EXPECT_EQ(href(b), expected_b);
  EXPECT_NE(href(a), href(b));
}

TEST_F(RefHashTest_63, ChangingGenChangesHashPerCombination_63) {
  std::hash<Ref> href;

  Ref a{10, 20};
  Ref b{10, 21};

  const std::size_t expected_a =
      std::hash<int>{}(a.num) ^ (std::hash<int>{}(a.gen) << 1);
  const std::size_t expected_b =
      std::hash<int>{}(b.num) ^ (std::hash<int>{}(b.gen) << 1);

  EXPECT_EQ(href(a), expected_a);
  EXPECT_EQ(href(b), expected_b);
  EXPECT_NE(href(a), href(b));
}

TEST_F(RefHashTest_63, HashWorksForInvalidRef_63) {
  std::hash<Ref> href;

  // Ref::INVALID() is part of the public interface. This test only verifies
  // that hashing it is well-formed and consistent.
  const Ref invalid = Ref::INVALID();
  const std::size_t a = href(invalid);
  const std::size_t b = href(invalid);

  EXPECT_EQ(a, b);
}

}  // namespace