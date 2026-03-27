// TEST_ID: 442
// File: settingchanges_restore_test_442.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "setting.h"

using ::testing::StrictMock;

namespace {

class MockSettingChange_442 : public YAML::SettingChangeBase {
public:
  MOCK_METHOD(void, pop, (), (override));
};

class SettingChangesRestoreTest_442 : public ::testing::Test {};

TEST_F(SettingChangesRestoreTest_442, RestoreOnEmptyDoesNothing_442) {
  YAML::SettingChanges changes;
  EXPECT_NO_THROW(changes.restore());
}

TEST_F(SettingChangesRestoreTest_442, RestoreCallsPopOncePerPushedChange_442) {
  YAML::SettingChanges changes;

  auto sc1 = std::make_unique<StrictMock<MockSettingChange_442>>();
  auto sc2 = std::make_unique<StrictMock<MockSettingChange_442>>();
  auto sc3 = std::make_unique<StrictMock<MockSettingChange_442>>();

  auto* p1 = sc1.get();
  auto* p2 = sc2.get();
  auto* p3 = sc3.get();

  changes.push(std::move(sc1));
  changes.push(std::move(sc2));
  changes.push(std::move(sc3));

  EXPECT_CALL(*p1, pop()).Times(1);
  EXPECT_CALL(*p2, pop()).Times(1);
  EXPECT_CALL(*p3, pop()).Times(1);

  EXPECT_NO_THROW(changes.restore());
}

TEST_F(SettingChangesRestoreTest_442, RestoreCallsPopForManyChanges_442) {
  YAML::SettingChanges changes;

  constexpr int kCount = 50;
  StrictMock<MockSettingChange_442>* ptrs[kCount]{};

  for (int i = 0; i < kCount; ++i) {
    auto sc = std::make_unique<StrictMock<MockSettingChange_442>>();
    ptrs[i] = sc.get();
    changes.push(std::move(sc));
  }

  for (int i = 0; i < kCount; ++i) {
    EXPECT_CALL(*ptrs[i], pop()).Times(1);
  }

  EXPECT_NO_THROW(changes.restore());
}

TEST_F(SettingChangesRestoreTest_442, RestoreAfterMoveConstructionCallsPopOnMovedTo_442) {
  YAML::SettingChanges original;

  auto sc1 = std::make_unique<StrictMock<MockSettingChange_442>>();
  auto sc2 = std::make_unique<StrictMock<MockSettingChange_442>>();
  auto* p1 = sc1.get();
  auto* p2 = sc2.get();

  original.push(std::move(sc1));
  original.push(std::move(sc2));

  YAML::SettingChanges moved_to(std::move(original));

  EXPECT_CALL(*p1, pop()).Times(1);
  EXPECT_CALL(*p2, pop()).Times(1);

  EXPECT_NO_THROW(moved_to.restore());
}

TEST_F(SettingChangesRestoreTest_442, RestoreAfterMoveAssignmentCallsPopOnAssignedTo_442) {
  YAML::SettingChanges source;

  auto sc1 = std::make_unique<StrictMock<MockSettingChange_442>>();
  auto sc2 = std::make_unique<StrictMock<MockSettingChange_442>>();
  auto* p1 = sc1.get();
  auto* p2 = sc2.get();

  source.push(std::move(sc1));
  source.push(std::move(sc2));

  YAML::SettingChanges dest;
  dest = std::move(source);

  EXPECT_CALL(*p1, pop()).Times(1);
  EXPECT_CALL(*p2, pop()).Times(1);

  EXPECT_NO_THROW(dest.restore());
}

// If a SettingChangeBase::pop() throws, restore() is declared noexcept.
// Throwing from within restore() should result in std::terminate().
// This is an observable error-case via process death.
class ThrowingSettingChange_442 : public YAML::SettingChangeBase {
public:
  void pop() override { throw std::runtime_error("pop failed"); }
};

TEST_F(SettingChangesRestoreTest_442, RestoreTerminatesIfPopThrows_442) {
  YAML::SettingChanges changes;
  changes.push(std::make_unique<ThrowingSettingChange_442>());

  EXPECT_DEATH(
      {
        // In a death-test subprocess; any exception escaping noexcept should terminate.
        changes.restore();
      },
      "");
}

}  // namespace
`