// ============================================================================
// TEST_ID: 640
// File: test_iptckey_640.cpp
// Unit tests for Exiv2::IptcKey (datasets.cpp / datasets.hpp)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>

// Include the real Exiv2 header that declares Exiv2::IptcKey.
// Adjust include path if your test target uses a different include root.
#include <exiv2/datasets.hpp>

namespace {

// Helper: SFINAE probe for clone() presence without calling it.
template <typename T>
class HasClone {
 private:
  template <typename U>
  static auto test(int) -> decltype(std::declval<const U&>().clone(), std::true_type{});
  template <typename>
  static auto test(...) -> std::false_type;

 public:
  static constexpr bool value = decltype(test<T>(0))::value;
};

// Helper: SFINAE probe for tag() / record() const presence.
template <typename T>
class HasTagAndRecord {
 private:
  template <typename U>
  static auto test(int)
      -> decltype(std::declval<const U&>().tag(), std::declval<const U&>().record(), std::true_type{});
  template <typename>
  static auto test(...) -> std::false_type;

 public:
  static constexpr bool value = decltype(test<T>(0))::value;
};

}  // namespace

class IptcKeyTest_640 : public ::testing::Test {
 protected:
  // Keep a couple of representative inputs.
  static std::string SomeKey() { return "Iptc.Application2.Caption"; }
  static std::string WeirdKey() { return std::string("Iptc.") + "Application2" + ".ObjectName"; }
};

// ---------------------------------------------------------------------------
// Normal operation
// ---------------------------------------------------------------------------

TEST_F(IptcKeyTest_640, KeyReturnsSameStringWhenConstructedFromString_640) {
  const std::string input = SomeKey();
  Exiv2::IptcKey k(input);

  // Observable behavior from partial implementation: key() returns stored key_.
  EXPECT_EQ(k.key(), input);
}

TEST_F(IptcKeyTest_640, KeyReturnsEmptyWhenConstructedFromEmptyString_640) {
  const std::string input;
  Exiv2::IptcKey k(input);

  EXPECT_TRUE(k.key().empty());
  EXPECT_EQ(k.key(), input);
}

TEST_F(IptcKeyTest_640, KeyIsStableAcrossMultipleCalls_640) {
  const std::string input = WeirdKey();
  Exiv2::IptcKey k(input);

  const std::string first = k.key();
  const std::string second = k.key();
  const std::string third = k.key();

  EXPECT_EQ(first, input);
  EXPECT_EQ(second, input);
  EXPECT_EQ(third, input);
}

TEST_F(IptcKeyTest_640, KeyUnaffectedByMutatingOriginalInputAfterConstruction_640) {
  std::string input = SomeKey();
  Exiv2::IptcKey k(input);

  // Mutate original string; object should retain its own copy/moved state.
  input.assign("Iptc.Application2.Headline");

  EXPECT_EQ(k.key(), SomeKey());
}

// ---------------------------------------------------------------------------
// Boundary conditions
// ---------------------------------------------------------------------------

TEST_F(IptcKeyTest_640, KeyPreservesSpecialCharactersAndWhitespace_640) {
  const std::string input = "Iptc.Application2.Credit  \t\n\r!@#$%^&*()[]{}";
  Exiv2::IptcKey k(input);

  EXPECT_EQ(k.key(), input);
}

TEST_F(IptcKeyTest_640, KeyHandlesVeryLongString_640) {
  std::string input = "Iptc.Application2.";
  input.append(4096, 'A');  // long but reasonable for unit test

  Exiv2::IptcKey k(input);
  EXPECT_EQ(k.key().size(), input.size());
  EXPECT_EQ(k.key(), input);
}

// ---------------------------------------------------------------------------
// Error / exceptional cases (observable through interface)
//
// NOTE: The provided partial code does not indicate any throws. We therefore
// only assert "no-throw" for basic operations that are visible.
// ---------------------------------------------------------------------------

TEST_F(IptcKeyTest_640, ConstructionAndKeyDoNotThrowForTypicalInputs_640) {
  EXPECT_NO_THROW({
    Exiv2::IptcKey k1(SomeKey());
    (void)k1.key();

    Exiv2::IptcKey k2(std::string{});
    (void)k2.key();

    Exiv2::IptcKey k3(WeirdKey());
    (void)k3.key();
  });
}

// ---------------------------------------------------------------------------
// Interface conformance / interactions (no external collaborators here)
//
// If clone() exists and returns a smart pointer, verify that the clone is a
// distinct object and preserves key() for string-constructed keys.
// (We do not assume internal decomposition/makeKey behavior.)
// ---------------------------------------------------------------------------

TEST_F(IptcKeyTest_640, ClonePreservesKeyWhenAvailable_640) {
  if constexpr (HasClone<Exiv2::IptcKey>::value) {
    const std::string input = SomeKey();
    const Exiv2::IptcKey original(input);

    auto cloned = original.clone();

    // We only rely on observable behavior:
    // - clone() returns a non-null owning pointer
    // - cloned object reports same key string
    ASSERT_TRUE(static_cast<bool>(cloned));
    EXPECT_EQ(cloned->key(), original.key());
    EXPECT_EQ(cloned->key(), input);

    // Distinct object (pointer inequality). We can't compare addresses directly
    // to 'original' because it's stack, but we can at least ensure clone owns
    // something and not null; address comparison isn't meaningful here.
  } else {
    GTEST_SKIP() << "Exiv2::IptcKey::clone() not available in this build.";
  }
}

// ---------------------------------------------------------------------------
// Constructor from (tag, record) exists per header. We avoid inferring how the
// key string is constructed; we only assert that key() is callable and stable.
// ---------------------------------------------------------------------------

TEST_F(IptcKeyTest_640, TagRecordConstructorKeyIsCallableAndStable_640) {
  Exiv2::IptcKey k(static_cast<uint16_t>(1), static_cast<uint16_t>(2));

  // We do not assume what it returns, only that repeated calls are consistent.
  const std::string a = k.key();
  const std::string b = k.key();
  EXPECT_EQ(a, b);
}

TEST_F(IptcKeyTest_640, TagAndRecordAccessorsAreCallableWhenAvailable_640) {
  if constexpr (HasTagAndRecord<Exiv2::IptcKey>::value) {
    const uint16_t tag = 0;
    const uint16_t record = 0;
    Exiv2::IptcKey k(tag, record);

    // Observable: accessors return uint16_t; do not assume semantics.
    EXPECT_EQ(k.tag(), tag);
    EXPECT_EQ(k.record(), record);
  } else {
    GTEST_SKIP() << "Exiv2::IptcKey::tag()/record() not available in this build.";
  }
}