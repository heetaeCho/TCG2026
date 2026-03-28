// Stream_isEncoder_tests_123.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Stream.h"

using ::testing::Return;

namespace {

class StreamTest_123 : public ::testing::Test {};

// Simple derived class using the base implementation.
class DefaultStream_123 : public Stream {};

// Derived class overriding behavior.
class EncoderStream_123 : public Stream {
public:
  bool isEncoder() const override { return true; }
};

// Mock to verify virtual dispatch and call count/return value.
class MockStream_123 : public Stream {
public:
  MOCK_METHOD(bool, isEncoder, (), (const, override));
};

}  // namespace

TEST_F(StreamTest_123, DefaultIsEncoderReturnsFalse_123) {
  DefaultStream_123 s;
  EXPECT_FALSE(s.isEncoder());
}

TEST_F(StreamTest_123, OverriddenIsEncoderReturnsTrue_123) {
  EncoderStream_123 s;
  EXPECT_TRUE(s.isEncoder());
}

TEST_F(StreamTest_123, PolymorphicCallUsesDynamicType_123) {
  EncoderStream_123 derived;
  const Stream& baseRef = derived;
  EXPECT_TRUE(baseRef.isEncoder());
}

TEST_F(StreamTest_123, ConstStreamObjectCanCallIsEncoder_123) {
  const DefaultStream_123 s;
  EXPECT_FALSE(s.isEncoder());
}

TEST_F(StreamTest_123, MockVerifiesIsEncoderIsCalledAndReturnValueIsUsed_123) {
  MockStream_123 s;
  EXPECT_CALL(s, isEncoder()).Times(1).WillOnce(Return(true));

  const Stream& baseRef = s;
  EXPECT_TRUE(baseRef.isEncoder());
}