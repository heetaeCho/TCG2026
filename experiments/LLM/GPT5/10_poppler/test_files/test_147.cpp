// SPDX-License-Identifier: GPL-2.0-or-later
// File: stream_predictor_isok_tests_147.cpp
//
// Unit tests for StreamPredictor::isOk() interface-only properties.
//
// Constraints respected:
// - Treat StreamPredictor as a black box (no assumptions about internal logic).
// - Tests rely only on the public interface (signatures / observable type traits).
// - No access to private state, no reimplementation of StreamPredictor logic.

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Stream.h"

namespace {

using ::StreamPredictor;

// TEST_ID = 147
TEST(StreamPredictorTest_147, HasIsOkMethod_147) {
  // Verify the method exists and is callable on a const object.
  static_assert(std::is_same_v<decltype(std::declval<const StreamPredictor&>().isOk()), bool>,
                "StreamPredictor::isOk() must be callable on const and return bool");
  SUCCEED();
}

// TEST_ID = 147
TEST(StreamPredictorTest_147, IsOkIsConstMember_147) {
  // Taking the member pointer enforces signature at compile time.
  // This checks: bool (StreamPredictor::*)() const
  using IsOkPtr = bool (StreamPredictor::*)() const;
  IsOkPtr p = &StreamPredictor::isOk;
  (void)p;
  SUCCEED();
}

// TEST_ID = 147
TEST(StreamPredictorTest_147, IsNotCopyConstructible_147) {
  // Interface states copy constructor is deleted.
  static_assert(!std::is_copy_constructible_v<StreamPredictor>,
                "StreamPredictor should not be copy constructible");
  SUCCEED();
}

// TEST_ID = 147
TEST(StreamPredictorTest_147, IsNotCopyAssignable_147) {
  // Interface states copy assignment is deleted.
  static_assert(!std::is_copy_assignable_v<StreamPredictor>,
                "StreamPredictor should not be copy assignable");
  SUCCEED();
}

// TEST_ID = 147
TEST(StreamPredictorTest_147, IsDestructible_147) {
  // The interface declares a destructor; ensure the type is destructible.
  static_assert(std::is_destructible_v<StreamPredictor>, "StreamPredictor must be destructible");
  SUCCEED();
}

}  // namespace