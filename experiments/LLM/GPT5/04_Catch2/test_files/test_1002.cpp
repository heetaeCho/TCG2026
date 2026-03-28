// File: test_testspec_pattern_name_1002.cpp

#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include <utility>

#if __has_include("catch2/catch_test_spec.hpp")
  #include "catch2/catch_test_spec.hpp"
#else
  // Fallback to the path provided in your repo layout
  #include "Catch2/src/catch2/catch_test_spec.hpp"
#endif

using Catch::TestSpec::Pattern;

// ---- Interface-level compile-time checks (no internal logic inferred) ----
namespace {
  // Verify the exact signature: const std::string& name() const
  static_assert(
      std::is_same_v<const std::string&, decltype(std::declval<const Pattern&>().name())>,
      "Pattern::name() must return const std::string& and be const-qualified");
}

// ---- Test fixture ----
class PatternTest_1002 : public ::testing::Test {
protected:
  // Helper to create a Pattern with a given name without inferring internal behavior
  std::unique_ptr<Pattern> makePattern(const std::string& n) {
    return std::make_unique<Pattern>(n);
  }
};

// [Normal operation] Returns the same value as provided at construction
TEST_F(PatternTest_1002, NameReturnsConstructorValue_1002) {
  auto p = makePattern("MyPattern");
  EXPECT_EQ(p->name(), std::string("MyPattern"));
}

// [Boundary] Empty string is preserved
TEST_F(PatternTest_1002, NameWithEmptyString_1002) {
  auto p = makePattern("");
  EXPECT_TRUE(p->name().empty());
  EXPECT_EQ(p->name().size(), 0u);
}

// [Boundary] Unicode / spaces / punctuation are preserved as bytes in std::string
TEST_F(PatternTest_1002, NameWithUnicodeAndSpaces_1002) {
  const std::string fancy = u8"  태그-패턴 🔧  ";
  auto p = makePattern(fancy);
  EXPECT_EQ(p->name(), fancy);
}

// [Observable behavior] Repeated calls return the same reference (no temporary)
TEST_F(PatternTest_1002, NameReturnsSameReferenceAcrossCalls_1002) {
  auto p = makePattern("Alpha");
  const std::string* ref1 = &p->name();
  const std::string* ref2 = &p->name();
  EXPECT_EQ(ref1, ref2);           // same address => same referenced object
  EXPECT_EQ(*ref1, "Alpha");
  EXPECT_EQ(*ref2, "Alpha");
}

// [Observable behavior] Reference remains valid during object lifetime
TEST_F(PatternTest_1002, NameReferenceStableDuringLifetime_1002) {
  auto p = makePattern("Stable");
  const std::string* ref = &p->name();
  // Other interactions that should not affect the returned reference's identity
  (void)p->name(); // another call
  EXPECT_EQ(ref, &p->name());
  EXPECT_EQ(*ref, "Stable");
}
