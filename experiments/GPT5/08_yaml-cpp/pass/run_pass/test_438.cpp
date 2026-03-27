// TEST_ID: 438
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>

#include "setting.h"

namespace {

template <typename T>
struct Samples;

template <>
struct Samples<int> {
  static int first() { return 123; }
  static int second() { return -456; }
};

template <>
struct Samples<bool> {
  static bool first() { return true; }
  static bool second() { return false; }
};

template <>
struct Samples<std::string> {
  static std::string first() { return "hello"; }
  static std::string second() { return std::string(1024, 'x'); }  // boundary-ish: large string
};

template <typename T>
class SettingSetTest_438 : public ::testing::Test {};

using TestedTypes_438 = ::testing::Types<int, bool, std::string>;
TYPED_TEST_SUITE(SettingSetTest_438, TestedTypes_438);

}  // namespace

TYPED_TEST(SettingSetTest_438, DefaultConstructedHasDefaultValue_438) {
  using T = TypeParam;

  YAML::Setting<T> setting;
  EXPECT_EQ(setting.get(), T{});
}

TYPED_TEST(SettingSetTest_438, SetUpdatesValueAndReturnsNonNullChange_438) {
  using T = TypeParam;

  YAML::Setting<T> setting;

  const T v = Samples<T>::first();
  std::unique_ptr<YAML::SettingChangeBase> change = setting.set(v);

  EXPECT_NE(change, nullptr);
  EXPECT_EQ(setting.get(), v);
}

TYPED_TEST(SettingSetTest_438, SetCanBeCalledMultipleTimesAndValueFollowsLastSet_438) {
  using T = TypeParam;

  YAML::Setting<T> setting;

  const T v1 = Samples<T>::first();
  const T v2 = Samples<T>::second();

  (void)setting.set(v1);
  EXPECT_EQ(setting.get(), v1);

  (void)setting.set(v2);
  EXPECT_EQ(setting.get(), v2);
}

TYPED_TEST(SettingSetTest_438, EachSetReturnsDistinctChangeObject_438) {
  using T = TypeParam;

  YAML::Setting<T> setting;

  const T v1 = Samples<T>::first();
  const T v2 = Samples<T>::second();

  std::unique_ptr<YAML::SettingChangeBase> c1 = setting.set(v1);
  std::unique_ptr<YAML::SettingChangeBase> c2 = setting.set(v2);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);
  EXPECT_NE(c1.get(), c2.get());
  EXPECT_EQ(setting.get(), v2);
}

TYPED_TEST(SettingSetTest_438, SetWithSameValueStillReturnsChangeAndKeepsValue_438) {
  using T = TypeParam;

  YAML::Setting<T> setting;

  const T v = Samples<T>::first();

  (void)setting.set(v);
  EXPECT_EQ(setting.get(), v);

  std::unique_ptr<YAML::SettingChangeBase> change2 = setting.set(v);
  EXPECT_NE(change2, nullptr);
  EXPECT_EQ(setting.get(), v);
}