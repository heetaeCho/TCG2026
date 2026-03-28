// File: ./TestProjects/yaml-cpp/test/dragonbox_signed_significand_bits_test_284.cpp

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Alias the type under test namespace (as used in yaml-cpp).
namespace db = YAML::jkj::dragonbox;

// A pure traits type suitable for constexpr/static_assert checks.
struct PureFormatTraits_284 {
  static constexpr bool is_positive(db::carrier_uint u) noexcept {
    // Arbitrary rule for testing: even -> positive.
    return (u % 2u) == 0u;
  }
};

// A capturing traits type to verify the forwarding/external interaction.
// (This acts like an external collaborator because the class calls into FormatTraits.)
struct CapturingFormatTraits_284 {
  static inline int calls = 0;
  static inline db::carrier_uint last_u = 0;

  static bool is_positive(db::carrier_uint u) noexcept {
    ++calls;
    last_u = u;
    // Arbitrary rule for testing: LSB 0 -> positive.
    return (u & 1u) == 0u;
  }

  static void Reset() {
    calls = 0;
    last_u = 0;
  }
};

class SignedSignificandBitsTest_284 : public ::testing::Test {
protected:
  void SetUp() override { CapturingFormatTraits_284::Reset(); }
};

}  // namespace

// ---- Compile-time / noexcept checks ----
TEST(SignedSignificandBitsTest_284, IsPositiveIsNoexcept_284) {
  using S = db::signed_significand_bits<PureFormatTraits_284>;
  S s{};
  static_assert(noexcept(s.is_positive()),
                "signed_significand_bits::is_positive() must be noexcept");
  (void)s;
}

TEST(SignedSignificandBitsTest_284, IsPositiveWorksInConstexprContext_284) {
  using S = db::signed_significand_bits<PureFormatTraits_284>;

  constexpr db::carrier_uint even = db::carrier_uint{42};
  constexpr db::carrier_uint odd  = db::carrier_uint{43};

  constexpr S s_even(even);
  constexpr S s_odd(odd);

  static_assert(s_even.is_positive() == true, "Even should be positive by PureFormatTraits_284 rule");
  static_assert(s_odd.is_positive() == false, "Odd should be negative by PureFormatTraits_284 rule");
}

// ---- Observable behavior & interaction verification ----
TEST_F(SignedSignificandBitsTest_284, ExplicitCtorStoresBitPattern_284) {
  using S = db::signed_significand_bits<CapturingFormatTraits_284>;

  const db::carrier_uint pattern = db::carrier_uint{0x1234u};
  S s(pattern);

  // 'u' is public per provided interface, so it's an observable part of the type.
  EXPECT_EQ(s.u, pattern);
}

TEST_F(SignedSignificandBitsTest_284, IsPositiveForwardsToFormatTraitsWithStoredU_284) {
  using S = db::signed_significand_bits<CapturingFormatTraits_284>;

  const db::carrier_uint pattern = db::carrier_uint{10u};  // even -> true by CapturingFormatTraits_284
  S s(pattern);

  const bool result = s.is_positive();

  EXPECT_TRUE(result);
  EXPECT_EQ(CapturingFormatTraits_284::calls, 1);
  EXPECT_EQ(CapturingFormatTraits_284::last_u, pattern);
}

TEST_F(SignedSignificandBitsTest_284, IsPositiveCallsFormatTraitsEachTime_284) {
  using S = db::signed_significand_bits<CapturingFormatTraits_284>;

  const db::carrier_uint pattern = db::carrier_uint{11u};  // odd -> false
  S s(pattern);

  EXPECT_FALSE(s.is_positive());
  EXPECT_FALSE(s.is_positive());

  EXPECT_EQ(CapturingFormatTraits_284::calls, 2);
  EXPECT_EQ(CapturingFormatTraits_284::last_u, pattern);
}

TEST_F(SignedSignificandBitsTest_284, IsPositiveHandlesBoundaryValues_284) {
  using S = db::signed_significand_bits<CapturingFormatTraits_284>;

  const db::carrier_uint zero = db::carrier_uint{0};
  const db::carrier_uint maxv = (std::numeric_limits<db::carrier_uint>::max)();

  {
    CapturingFormatTraits_284::Reset();
    S s(zero);
    // zero is even -> true by our traits rule
    EXPECT_TRUE(s.is_positive());
    EXPECT_EQ(CapturingFormatTraits_284::calls, 1);
    EXPECT_EQ(CapturingFormatTraits_284::last_u, zero);
  }

  {
    CapturingFormatTraits_284::Reset();
    S s(maxv);
    // expected result depends on LSB of maxv under the rule; compute expected without assuming internals.
    const bool expected = ((maxv & 1u) == 0u);
    EXPECT_EQ(s.is_positive(), expected);
    EXPECT_EQ(CapturingFormatTraits_284::calls, 1);
    EXPECT_EQ(CapturingFormatTraits_284::last_u, maxv);
  }
}