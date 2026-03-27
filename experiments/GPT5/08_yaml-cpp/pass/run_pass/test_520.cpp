// TEST_ID: 520
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "yaml-cpp/emitter.h"

namespace {

using ::YAML::Emitter;
using ::YAML::EMITTER_MANIP;

// Helper to build an "unlikely to be valid" EMITTER_MANIP without relying on any specific manipulator
// names/constants (treating implementation as a black box).
static EMITTER_MANIP MakeVeryLargeManip() {
  using U = std::underlying_type_t<EMITTER_MANIP>;
  return static_cast<EMITTER_MANIP>(std::numeric_limits<U>::max());
}

class EmitterSetNullFormatTest_520 : public ::testing::Test {
 protected:
  Emitter emitter_;
};

TEST_F(EmitterSetNullFormatTest_520, SetNullFormat_IsIdempotentForSameValue_520) {
  const auto before_size = emitter_.size();
  const std::string before_str = emitter_.c_str();

  const EMITTER_MANIP v = static_cast<EMITTER_MANIP>(0);

  const bool r1 = emitter_.SetNullFormat(v);
  const bool r2 = emitter_.SetNullFormat(v);

  // Calling with the same value repeatedly should behave consistently.
  EXPECT_EQ(r1, r2);

  // Setting a format should not emit output by itself.
  EXPECT_EQ(before_size, emitter_.size());
  EXPECT_EQ(before_str, std::string(emitter_.c_str()));
}

TEST_F(EmitterSetNullFormatTest_520, SetNullFormat_AllowsDifferentValuesWithoutEmittingOutput_520) {
  const auto before_size = emitter_.size();
  const std::string before_str = emitter_.c_str();

  const EMITTER_MANIP v1 = static_cast<EMITTER_MANIP>(0);
  const EMITTER_MANIP v2 = static_cast<EMITTER_MANIP>(1);

  (void)emitter_.SetNullFormat(v1);
  (void)emitter_.SetNullFormat(v2);

  // Regardless of success/failure, just setting formatting should not change the output buffer.
  EXPECT_EQ(before_size, emitter_.size());
  EXPECT_EQ(before_str, std::string(emitter_.c_str()));
}

TEST_F(EmitterSetNullFormatTest_520, SetNullFormat_InvalidValueIsHandledAndIsRepeatable_520) {
  const EMITTER_MANIP invalid = MakeVeryLargeManip();

  const auto before_good = emitter_.good();
  const std::string before_error = emitter_.GetLastError();
  const auto before_size = emitter_.size();
  const std::string before_str = emitter_.c_str();

  const bool r1 = emitter_.SetNullFormat(invalid);
  const bool r2 = emitter_.SetNullFormat(invalid);

  // Whatever the implementation does for an invalid value, it should be consistent.
  EXPECT_EQ(r1, r2);

  // Setting a format should not emit output by itself, even on error paths.
  EXPECT_EQ(before_size, emitter_.size());
  EXPECT_EQ(before_str, std::string(emitter_.c_str()));

  // If the call reports failure, it should be observable through the public error surface
  // (either good() flips false or GetLastError changes from prior state).
  if (!r1) {
    const bool after_good = emitter_.good();
    const std::string after_error = emitter_.GetLastError();
    EXPECT_TRUE((after_good != before_good) || (after_error != before_error));
  }
}

}  // namespace