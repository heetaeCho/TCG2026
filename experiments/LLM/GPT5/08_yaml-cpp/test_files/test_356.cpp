// TEST_ID: 356
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

#include <type_traits>

namespace {

using nearest_to_even_t =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_t;
using symmetric_boundary = YAML::jkj::dragonbox::interval_type::symmetric_boundary;

// --- Minimal detection utilities (no C++17 required) ---
template <typename...>
struct voider {
  using type = void;
};
template <typename... Ts>
using void_t = typename voider<Ts...>::type;

template <typename T, typename = void>
struct has_member_is_closed : std::false_type {};
template <typename T>
struct has_member_is_closed<T, void_t<decltype(std::declval<const T&>().is_closed)>>
    : std::true_type {};

template <typename T, typename = void>
struct has_member_closed : std::false_type {};
template <typename T>
struct has_member_closed<T, void_t<decltype(std::declval<const T&>().closed)>> : std::true_type {};

template <typename T, typename = void>
struct has_member_is_open : std::false_type {};
template <typename T>
struct has_member_is_open<T, void_t<decltype(std::declval<const T&>().is_open)>>
    : std::true_type {};

template <typename T, typename = void>
struct has_operator_eq_bool_constructible : std::false_type {};
template <typename T>
struct has_operator_eq_bool_constructible<
    T,
    void_t<decltype(std::declval<const T&>() == T{true}), decltype(T{true})>> : std::true_type {};

// Extract the stored bool-like flag from symmetric_boundary in a way that adapts to
// multiple possible public interfaces. If none match, we fall back to operator==
// against an aggregate/value-initialized object, if supported.
template <typename B>
typename std::enable_if<has_member_is_closed<B>::value, bool>::type ExtractFlag(
    const B& b) {
  return static_cast<bool>(b.is_closed);
}

template <typename B>
typename std::enable_if<!has_member_is_closed<B>::value && has_member_closed<B>::value,
                        bool>::type
ExtractFlag(const B& b) {
  return static_cast<bool>(b.closed);
}

template <typename B>
typename std::enable_if<!has_member_is_closed<B>::value && !has_member_closed<B>::value &&
                            has_member_is_open<B>::value,
                        bool>::type
ExtractFlag(const B& b) {
  // If the type stores "is_open", invert to match the bool we pass into { ... }.
  return !static_cast<bool>(b.is_open);
}

template <typename B>
typename std::enable_if<!has_member_is_closed<B>::value && !has_member_closed<B>::value &&
                            !has_member_is_open<B>::value &&
                            has_operator_eq_bool_constructible<B>::value,
                        bool>::type
ExtractFlag(const B& b) {
  // If we can compare, detect whether this boundary equals the "true" instance.
  return (b == B{true});
}

template <typename B>
typename std::enable_if<!has_member_is_closed<B>::value && !has_member_closed<B>::value &&
                            !has_member_is_open<B>::value &&
                            !has_operator_eq_bool_constructible<B>::value,
                        bool>::type
ExtractFlag(const B&) {
  // If this triggers, the public interface of symmetric_boundary is not something
  // this test knows how to observe without touching internals.
  static_assert(sizeof(B) == 0,
                "Unable to observe symmetric_boundary state via public interface. "
                "Update ExtractFlag() with the appropriate public accessor/member.");
  return false;
}

// Dummy "SignedSignificandBits" test doubles:
struct EvenBits {
  constexpr bool has_even_significand_bits() const noexcept { return true; }
};
struct OddBits {
  constexpr bool has_even_significand_bits() const noexcept { return false; }
};
struct IntReturningBits {
  // Convertible-to-bool return type.
  constexpr int has_even_significand_bits() const noexcept { return 1; }
};

class NearestToEvenTest_356 : public ::testing::Test {};

TEST_F(NearestToEvenTest_356, NormalIntervalReturnsTrueWhenEvenSignificandBits_356) {
  const EvenBits s{};
  const auto interval = nearest_to_even_t::normal_interval(s);

  EXPECT_TRUE(ExtractFlag(interval));
}

TEST_F(NearestToEvenTest_356, NormalIntervalReturnsFalseWhenOddSignificandBits_356) {
  const OddBits s{};
  const auto interval = nearest_to_even_t::normal_interval(s);

  EXPECT_FALSE(ExtractFlag(interval));
}

TEST_F(NearestToEvenTest_356, NormalIntervalIsNoexcept_356) {
  const EvenBits s{};
  static_assert(noexcept(nearest_to_even_t::normal_interval(s)),
                "normal_interval(...) must be noexcept");
  (void)s;
}

TEST_F(NearestToEvenTest_356, NormalIntervalReturnTypeIsSymmetricBoundary_356) {
  const EvenBits s{};
  using Ret = decltype(nearest_to_even_t::normal_interval(s));
  EXPECT_TRUE((std::is_same<Ret, symmetric_boundary>::value));
}

TEST_F(NearestToEvenTest_356, NormalIntervalWorksInConstexprContext_356) {
  constexpr EvenBits s{};
  constexpr auto interval = nearest_to_even_t::normal_interval(s);

  // If ExtractFlag is constexpr-capable for the detected interface, this will be constexpr too.
  // Otherwise, we still validate via a runtime EXPECT below.
#if defined(__cpp_constexpr) && (__cpp_constexpr >= 200704)
  // Best-effort: some interfaces/operators might not be constexpr; keep runtime check regardless.
#endif
  EXPECT_TRUE(ExtractFlag(interval));
}

TEST_F(NearestToEvenTest_356, NormalIntervalAcceptsBoolConvertibleReturnFromHasEven_356) {
  const IntReturningBits s{};
  const auto interval = nearest_to_even_t::normal_interval(s);

  EXPECT_TRUE(ExtractFlag(interval));
}

}  // namespace