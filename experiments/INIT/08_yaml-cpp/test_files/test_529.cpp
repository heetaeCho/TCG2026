// TEST_ID: 529
#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "yaml-cpp/emitter.h"

namespace {

static std::string Snapshot(const YAML::Emitter& e) {
  const char* p = e.c_str();
  const std::size_t n = e.size();
  if (!p || n == 0) return std::string();
  return std::string(p, p + n);
}

class EmitterRestoreGlobalModifiedSettingsTest_529 : public ::testing::Test {
 protected:
  YAML::Emitter emitter_;
};

}  // namespace

TEST_F(EmitterRestoreGlobalModifiedSettingsTest_529,
       RestoreWithoutPriorChanges_DoesNotThrow_529) {
  // Should be safe to call at any time.
  EXPECT_NO_THROW(emitter_.RestoreGlobalModifiedSettings());
}

TEST_F(EmitterRestoreGlobalModifiedSettingsTest_529,
       RestoreDoesNotModifyAlreadyEmittedContent_529) {
  emitter_.Write("alpha");
  const std::string before = Snapshot(emitter_);

  emitter_.RestoreGlobalModifiedSettings();

  const std::string after = Snapshot(emitter_);
  EXPECT_EQ(before, after);
}

TEST_F(EmitterRestoreGlobalModifiedSettingsTest_529,
       RestoreIsIdempotent_OutputStableAcrossMultipleCalls_529) {
  emitter_.Write("beta");
  const std::string before = Snapshot(emitter_);

  emitter_.RestoreGlobalModifiedSettings();
  const std::string after_first = Snapshot(emitter_);

  emitter_.RestoreGlobalModifiedSettings();
  const std::string after_second = Snapshot(emitter_);

  EXPECT_EQ(before, after_first);
  EXPECT_EQ(after_first, after_second);
}

TEST_F(EmitterRestoreGlobalModifiedSettingsTest_529,
       RestoreAfterSomeSettingCalls_DoesNotCorruptEmitterState_529) {
  // We don't assert specific formatting (black-box), only that the emitter
  // remains usable and that restoration doesn't break observable invariants.
  (void)emitter_.SetIndent(2);
  (void)emitter_.SetPreCommentIndent(1);
  (void)emitter_.SetPostCommentIndent(1);
  (void)emitter_.SetFloatPrecision(3);
  (void)emitter_.SetDoublePrecision(5);

  emitter_.Write("gamma");
  const std::string before_restore = Snapshot(emitter_);
  const bool good_before = emitter_.good();

  EXPECT_NO_THROW(emitter_.RestoreGlobalModifiedSettings());

  // Previously emitted content should remain unchanged.
  const std::string after_restore = Snapshot(emitter_);
  EXPECT_EQ(before_restore, after_restore);

  // Emitter should remain usable for subsequent writes.
  emitter_.Write("delta");
  const std::string after_more_writes = Snapshot(emitter_);
  EXPECT_GE(after_more_writes.size(), after_restore.size());

  // If it was good before, restoration should not make it bad.
  if (good_before) {
    EXPECT_TRUE(emitter_.good());
  }
}