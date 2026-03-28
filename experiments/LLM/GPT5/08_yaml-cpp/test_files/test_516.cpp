// TEST_ID: 516
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterGetLastErrorTest_516 : public ::testing::Test {
 protected:
  YAML::Emitter emitter_;
};

TEST_F(EmitterGetLastErrorTest_516, GetLastError_IsCallableOnConst_516) {
  const YAML::Emitter& cemit = emitter_;
  const std::string err = cemit.GetLastError();
  (void)err;  // Just verifying it compiles and is callable on const.
  SUCCEED();
}

TEST_F(EmitterGetLastErrorTest_516, GetLastError_IsStableAcrossMultipleCalls_516) {
  const YAML::Emitter& cemit = emitter_;
  const std::string e1 = cemit.GetLastError();
  const std::string e2 = cemit.GetLastError();
  EXPECT_EQ(e1, e2);
}

TEST_F(EmitterGetLastErrorTest_516, GetLastError_DoesNotThrow_516) {
  const YAML::Emitter& cemit = emitter_;
  EXPECT_NO_THROW({
    const std::string err = cemit.GetLastError();
    (void)err;
  });
}

TEST_F(EmitterGetLastErrorTest_516, GetLastError_ReflectsObservableErrorIfSetterFails_516) {
  const std::string before = emitter_.GetLastError();
  const bool was_good = emitter_.good();

  // Try a commonly-invalid boundary value; behavior is treated as black-box.
  const bool ok = emitter_.SetIndent(0);

  const std::string after = emitter_.GetLastError();
  const bool is_good = emitter_.good();

  // Only assert effects when they are observable through the public interface.
  // If the call reports failure or emitter becomes not-good, we expect an error message.
  if (!ok || (was_good && !is_good)) {
    EXPECT_FALSE(after.empty());
  } else {
    // If no failure is reported, at least ensure the API remains consistent/stable.
    EXPECT_NO_THROW({ (void)emitter_.GetLastError(); });
  }

  // Also ensure repeated calls are stable post-operation.
  EXPECT_EQ(after, emitter_.GetLastError());

  // Avoid asserting "clearing" semantics since they aren't guaranteed by the interface.
  (void)before;
}

TEST_F(EmitterGetLastErrorTest_516, GetLastError_ReflectsObservableErrorIfWriteCausesBadState_516) {
  const std::string before = emitter_.GetLastError();
  const bool was_good = emitter_.good();

  // Provide a boundary write (empty string). Should not crash regardless of internal logic.
  EXPECT_NO_THROW({
    emitter_.Write("", 0);
  });

  const std::string after = emitter_.GetLastError();
  const bool is_good = emitter_.good();

  // If an error is observable (emitter not good), it should surface in GetLastError.
  if (was_good && !is_good) {
    EXPECT_FALSE(after.empty());
  } else {
    // Otherwise, keep expectations minimal and black-box friendly.
    EXPECT_NO_THROW({ (void)emitter_.GetLastError(); });
  }

  EXPECT_EQ(after, emitter_.GetLastError());
  (void)before;
}

TEST_F(EmitterGetLastErrorTest_516, GetLastError_WorksForEmitterConstructedWithStream_516) {
  std::stringstream ss;
  YAML::Emitter e(ss);

  const YAML::Emitter& ce = e;
  EXPECT_NO_THROW({
    const std::string err = ce.GetLastError();
    (void)err;
  });

  // Idempotence on const access.
  EXPECT_EQ(ce.GetLastError(), ce.GetLastError());
}

}  // namespace