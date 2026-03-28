// TEST_ID: 435
#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "setting.h"

namespace {

class SettingTest_435 : public ::testing::Test {};

template <typename T>
using SettingT = YAML::Setting<T>;

// --- Compile-time interface checks (non-behavioral, no internal assumptions) ---

TEST_F(SettingTest_435, GetIsCallableOnConst_435) {
  const SettingT<int> s{};
  (void)s.get();  // should compile
  SUCCEED();
}

TEST_F(SettingTest_435, GetReturnTypeIsTByValue_435) {
  using S = SettingT<int>;
  static_assert(std::is_same_v<decltype(std::declval<const S&>().get()), const int>,
                "Expected get() to return 'const T' by value (as declared).");
  SUCCEED();
}

// --- Observable behavior tests ---

TEST_F(SettingTest_435, DefaultConstructedIntReturnsValue_435) {
  SettingT<int> s{};
  // Black-box expectation: default construction should yield the default-initialized value for T.
  EXPECT_EQ(s.get(), int{});
}

TEST_F(SettingTest_435, DefaultConstructedStringReturnsValue_435) {
  SettingT<std::string> s{};
  EXPECT_EQ(s.get(), std::string{});
}

TEST_F(SettingTest_435, ValueConstructedIntReturnsValue_435) {
  const int v = 12345;
  SettingT<int> s{v};
  EXPECT_EQ(s.get(), v);
}

TEST_F(SettingTest_435, ValueConstructedStringReturnsValue_435) {
  const std::string v = "yaml-cpp";
  SettingT<std::string> s{v};
  EXPECT_EQ(s.get(), v);
}

TEST_F(SettingTest_435, SetUpdatesValueForInt_435) {
  SettingT<int> s{};
  auto change = s.set(7);
  (void)change;  // returned object is implementation-defined; we only verify visible effects.
  EXPECT_EQ(s.get(), 7);
}

TEST_F(SettingTest_435, SetUpdatesValueForString_435) {
  SettingT<std::string> s{};
  auto change = s.set(std::string("updated"));
  (void)change;
  EXPECT_EQ(s.get(), "updated");
}

TEST_F(SettingTest_435, RestoreRestoresPreviousSettingValue_Int_435) {
  SettingT<int> s{1};
  SettingT<int> oldSetting = s;  // capture current observable state via public interface
  (void)s.set(2);

  s.restore(oldSetting);
  EXPECT_EQ(s.get(), oldSetting.get());
}

TEST_F(SettingTest_435, RestoreRestoresPreviousSettingValue_String_435) {
  SettingT<std::string> s{"a"};
  SettingT<std::string> oldSetting = s;
  (void)s.set(std::string("b"));

  s.restore(oldSetting);
  EXPECT_EQ(s.get(), oldSetting.get());
}

// Boundary-ish values (still purely through public API)
TEST_F(SettingTest_435, SetAndGetLargeIntValue_435) {
  SettingT<long long> s{};
  const long long v = (std::numeric_limits<long long>::max)();
  (void)s.set(v);
  EXPECT_EQ(s.get(), v);
}

TEST_F(SettingTest_435, SetAndGetEmptyString_435) {
  SettingT<std::string> s{"non-empty"};
  (void)s.set(std::string{});
  EXPECT_EQ(s.get(), "");
}

// Error/exceptional cases (only what’s observable): ensure calls are safe for common scenarios.
TEST_F(SettingTest_435, SetSameValueDoesNotCrashAndKeepsValue_Int_435) {
  SettingT<int> s{10};
  EXPECT_NO_THROW({
    auto change = s.set(10);
    (void)change;
  });
  EXPECT_EQ(s.get(), 10);
}

TEST_F(SettingTest_435, RestoreSelfDoesNotCrashAndKeepsValue_435) {
  SettingT<int> s{42};
  EXPECT_NO_THROW({ s.restore(s); });
  EXPECT_EQ(s.get(), 42);
}

}  // namespace