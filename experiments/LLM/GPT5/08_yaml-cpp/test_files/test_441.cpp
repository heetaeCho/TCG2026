// TEST_ID: 441
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "setting.h"

namespace {

using ::testing::StrictMock;

class SettingChangesTest_441 : public ::testing::Test {};

// Mock external collaborator: SettingChangeBase
class MockSettingChange_441 : public YAML::SettingChangeBase {
 public:
  MOCK_METHOD(void, pop, (), (override));
  ~MockSettingChange_441() override = default;
};

TEST_F(SettingChangesTest_441, ClearOnEmptyDoesNotThrow_441) {
  YAML::SettingChanges changes;

  static_assert(noexcept(changes.clear()),
                "SettingChanges::clear() must be noexcept");

  EXPECT_NO_THROW(changes.clear());
}

TEST_F(SettingChangesTest_441, ClearCallsPopOnAllPushedChanges_441) {
  YAML::SettingChanges changes;

  auto c1 = std::make_unique<StrictMock<MockSettingChange_441>>();
  auto c2 = std::make_unique<StrictMock<MockSettingChange_441>>();
  auto* c1_raw = c1.get();
  auto* c2_raw = c2.get();

  EXPECT_CALL(*c1_raw, pop()).Times(1);
  EXPECT_CALL(*c2_raw, pop()).Times(1);

  changes.push(std::move(c1));
  changes.push(std::move(c2));

  EXPECT_NO_THROW(changes.clear());
}

TEST_F(SettingChangesTest_441, ClearIsIdempotent_441) {
  YAML::SettingChanges changes;

  auto c1 = std::make_unique<StrictMock<MockSettingChange_441>>();
  auto* c1_raw = c1.get();

  EXPECT_CALL(*c1_raw, pop()).Times(1);
  changes.push(std::move(c1));

  EXPECT_NO_THROW(changes.clear());
  // Second clear: nothing left to restore/pop; must not throw.
  EXPECT_NO_THROW(changes.clear());
}

TEST_F(SettingChangesTest_441, ClearRemovesPriorChangesSoRestoreDoesNothingAfterward_441) {
  YAML::SettingChanges changes;

  auto c1 = std::make_unique<StrictMock<MockSettingChange_441>>();
  auto* c1_raw = c1.get();

  EXPECT_CALL(*c1_raw, pop()).Times(1);
  changes.push(std::move(c1));

  changes.clear();

  // If clear() cleared internal storage, restore() should have no external effects.
  EXPECT_NO_THROW(changes.restore());
}

}  // namespace