// TEST_ID: 90
#include <gtest/gtest.h>

#include <type_traits>
#include <string>

#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/mark.h"

namespace {

// Detection: E::mark()
template <class E, class = void>
struct HasMarkMethod : std::false_type {};
template <class E>
struct HasMarkMethod<E, std::void_t<decltype(std::declval<const E&>().mark())>>
    : std::true_type {};

// Detection: E::key()
template <class E, class = void>
struct HasKeyMethod : std::false_type {};
template <class E>
struct HasKeyMethod<E, std::void_t<decltype(std::declval<const E&>().key())>>
    : std::true_type {};

template <class MarkLike>
void ExpectSameMarkFields(const MarkLike& a, const YAML::Mark& b) {
  EXPECT_EQ(a.pos, b.pos);
  EXPECT_EQ(a.line, b.line);
  EXPECT_EQ(a.column, b.column);
}

}  // namespace

class MakeTypedKeyNotFoundTest_90 : public ::testing::Test {};

TEST_F(MakeTypedKeyNotFoundTest_90, ReturnsTypedKeyNotFoundForIntKey_90) {
  YAML::Mark m;
  constexpr int key = 7;

  auto ex = YAML::MakeTypedKeyNotFound(m, key);

  // Type-level expectations (observable at compile-time).
  static_assert(std::is_base_of_v<std::exception, decltype(ex)>,
                "Returned exception type should derive from std::exception.");

  // If the exception exposes mark() publicly, verify it matches the input Mark.
  if constexpr (HasMarkMethod<decltype(ex)>::value) {
    const auto ex_mark = ex.mark();
    ExpectSameMarkFields(ex_mark, m);
  }

  // If the exception exposes key() publicly, verify it matches the input key.
  if constexpr (HasKeyMethod<decltype(ex)>::value) {
    EXPECT_EQ(ex.key(), key);
  }
}

TEST_F(MakeTypedKeyNotFoundTest_90, ReturnsTypedKeyNotFoundForStringKey_90) {
  YAML::Mark m;
  const std::string key = "alpha";

  auto ex = YAML::MakeTypedKeyNotFound(m, key);

  static_assert(std::is_base_of_v<std::exception, decltype(ex)>,
                "Returned exception type should derive from std::exception.");

  if constexpr (HasMarkMethod<decltype(ex)>::value) {
    const auto ex_mark = ex.mark();
    ExpectSameMarkFields(ex_mark, m);
  }

  if constexpr (HasKeyMethod<decltype(ex)>::value) {
    EXPECT_EQ(ex.key(), key);
  }
}

TEST_F(MakeTypedKeyNotFoundTest_90, AcceptsNullMarkAndEmptyKey_90) {
  const YAML::Mark null_m = YAML::Mark::null_mark();
  const std::string empty_key;

  EXPECT_NO_THROW({
    auto ex = YAML::MakeTypedKeyNotFound(null_m, empty_key);

    if constexpr (HasMarkMethod<decltype(ex)>::value) {
      const auto ex_mark = ex.mark();
      ExpectSameMarkFields(ex_mark, null_m);
    }
    if constexpr (HasKeyMethod<decltype(ex)>::value) {
      EXPECT_EQ(ex.key(), empty_key);
    }
  });
}

TEST_F(MakeTypedKeyNotFoundTest_90, WorksWithLargeKeyPayload_90) {
  YAML::Mark m;
  const std::string big_key(1024 * 64, 'x');  // boundary-ish: large key

  EXPECT_NO_THROW({
    auto ex = YAML::MakeTypedKeyNotFound(m, big_key);

    if constexpr (HasKeyMethod<decltype(ex)>::value) {
      EXPECT_EQ(ex.key(), big_key);
    }
  });
}

TEST_F(MakeTypedKeyNotFoundTest_90, CanBeThrownAndCaughtAsStdException_90) {
  YAML::Mark m;
  const std::string key = "k";

  try {
    throw YAML::MakeTypedKeyNotFound(m, key);
  } catch (const std::exception& e) {
    // Minimal observable behavior: it is catchable as std::exception.
    (void)e;
    SUCCEED();
  } catch (...) {
    FAIL() << "Expected exception to be catchable as std::exception";
  }
}
