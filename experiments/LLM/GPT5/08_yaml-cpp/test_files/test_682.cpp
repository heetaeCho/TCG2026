// TEST_ID: 682
#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "setting.h"

namespace {

class SettingTest_682 : public ::testing::Test {};

// Compile-time sanity checks that do not assume implementation details.
TEST_F(SettingTest_682, DefaultConstructibleAndCopyable_682) {
  EXPECT_TRUE((std::is_default_constructible<YAML::Setting<int>>::value));
  EXPECT_TRUE((std::is_copy_constructible<YAML::Setting<int>>::value));
  EXPECT_TRUE((std::is_copy_assignable<YAML::Setting<int>>::value));
}

TEST_F(SettingTest_682, CtorValueInitializesGet_Int_682) {
  YAML::Setting<int> s(123);
  EXPECT_EQ(s.get(), 123);
}

TEST_F(SettingTest_682, CtorValueInitializesGet_String_682) {
  YAML::Setting<std::string> s(std::string("hello"));
  EXPECT_EQ(s.get(), "hello");
}

TEST_F(SettingTest_682, SetUpdatesValue_Int_682) {
  YAML::Setting<int> s(1);

  // We treat returned object as opaque; only verify observable state via get().
  auto change = s.set(2);
  (void)change;

  EXPECT_EQ(s.get(), 2);
}

TEST_F(SettingTest_682, SetUpdatesValue_String_682) {
  YAML::Setting<std::string> s(std::string("a"));

  auto change = s.set(std::string("b"));
  (void)change;

  EXPECT_EQ(s.get(), "b");
}

TEST_F(SettingTest_682, SetCanBeCalledWithSameValue_NoObservableChange_682) {
  YAML::Setting<int> s(7);

  auto change = s.set(7);
  (void)change;

  EXPECT_EQ(s.get(), 7);
}

TEST_F(SettingTest_682, RestoreRevertsToOldSetting_Int_682) {
  YAML::Setting<int> s(10);
  YAML::Setting<int> old = s;  // snapshot via public copy semantics

  auto change = s.set(42);
  (void)change;
  ASSERT_EQ(s.get(), 42);

  s.restore(old);
  EXPECT_EQ(s.get(), old.get());
  EXPECT_EQ(s.get(), 10);
}

TEST_F(SettingTest_682, RestoreRevertsToOldSetting_String_682) {
  YAML::Setting<std::string> s(std::string("first"));
  YAML::Setting<std::string> old = s;

  auto change = s.set(std::string("second"));
  (void)change;
  ASSERT_EQ(s.get(), "second");

  s.restore(old);
  EXPECT_EQ(s.get(), old.get());
  EXPECT_EQ(s.get(), "first");
}

TEST_F(SettingTest_682, RestoreWithCurrentSettingLeavesValueUnchanged_682) {
  YAML::Setting<int> s(99);
  YAML::Setting<int> current = s;

  s.restore(current);
  EXPECT_EQ(s.get(), 99);
}

TEST_F(SettingTest_682, SetReturnValueIsMoveableUniquePtrLike_682) {
  YAML::Setting<int> s(1);

  // Verify that the returned object can be moved (observable behavior: compiles and runs).
  auto change1 = s.set(2);
  auto change2 = std::move(change1);

  // No assumptions about null/non-null; just ensure moving doesn't crash and state is as expected.
  (void)change2;
  EXPECT_EQ(s.get(), 2);
}

TEST_F(SettingTest_682, NoThrowOnBasicOperations_Int_682) {
  // "Exceptional or error cases" are only testable if observable; here we only assert no-throw
  // for common types/values (doesn't assume how errors are handled internally).
  EXPECT_NO_THROW({
    YAML::Setting<int> s;
    (void)s.get();
    auto ch = s.set(5);
    (void)ch;
    YAML::Setting<int> old = s;
    s.restore(old);
  });
}

TEST_F(SettingTest_682, BoundaryValues_IntMinMax_682) {
  YAML::Setting<int> s(0);

  auto c1 = s.set(std::numeric_limits<int>::min());
  (void)c1;
  EXPECT_EQ(s.get(), std::numeric_limits<int>::min());

  auto c2 = s.set(std::numeric_limits<int>::max());
  (void)c2;
  EXPECT_EQ(s.get(), std::numeric_limits<int>::max());
}

TEST_F(SettingTest_682, BoundaryValues_LargeString_682) {
  std::string big(10000, 'x');
  YAML::Setting<std::string> s(std::string("start"));

  auto change = s.set(big);
  (void)change;

  EXPECT_EQ(s.get().size(), big.size());
  EXPECT_EQ(s.get(), big);
}

}  // namespace