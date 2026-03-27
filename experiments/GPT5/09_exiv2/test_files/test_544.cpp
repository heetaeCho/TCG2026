// File: test_basicio_readorthrow_544.cpp
// Unit tests for Exiv2::BasicIo::readOrThrow
//
// TEST_ID: 544

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArrayArgument;

namespace {

class MockBasicIo final : public Exiv2::BasicIo {
public:
  MockBasicIo() = default;
  ~MockBasicIo() override = default;

  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, error, (), (override));
};

class BasicIoReadOrThrowTest_544 : public ::testing::Test {
protected:
  MockBasicIo io_;
};

TEST_F(BasicIoReadOrThrowTest_544, SucceedsWhenReadExactAndNoError_544) {
  Exiv2::byte buf[4] = {0, 0, 0, 0};
  const Exiv2::byte expected[4] = {0x11, 0x22, 0x33, 0x44};

  EXPECT_CALL(io_, read(buf, sizeof(buf)))
      .WillOnce(DoAll(SetArrayArgument<0>(expected, expected + sizeof(expected)),
                      Return(sizeof(buf))));
  EXPECT_CALL(io_, error()).WillOnce(Return(0));

  EXPECT_NO_THROW(io_.readOrThrow(buf, sizeof(buf), Exiv2::ErrorCode::kerErrorMessage));

  EXPECT_THAT(buf, ::testing::ElementsAreArray(expected));
}

TEST_F(BasicIoReadOrThrowTest_544, SucceedsWithZeroCount_544) {
  Exiv2::byte buf[1] = {0xAB};

  EXPECT_CALL(io_, read(buf, 0)).WillOnce(Return(static_cast<size_t>(0)));
  EXPECT_CALL(io_, error()).WillOnce(Return(0));

  EXPECT_NO_THROW(io_.readOrThrow(buf, 0, Exiv2::ErrorCode::kerErrorMessage));

  // Buffer should remain unchanged (read count is zero).
  EXPECT_EQ(buf[0], 0xAB);
}

TEST_F(BasicIoReadOrThrowTest_544, ThrowsWhenShortReadAndDoesNotQueryError_544) {
  Exiv2::byte buf[8] = {};

  EXPECT_CALL(io_, read(buf, sizeof(buf))).WillOnce(Return(sizeof(buf) - 1));
  // If the first enforcement fails, error() should not be called.
  EXPECT_CALL(io_, error()).Times(0);

  EXPECT_ANY_THROW(io_.readOrThrow(buf, sizeof(buf), Exiv2::ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoReadOrThrowTest_544, ThrowsWhenReadExactButErrorFlagSet_544) {
  Exiv2::byte buf[8] = {};

  EXPECT_CALL(io_, read(buf, sizeof(buf))).WillOnce(Return(sizeof(buf)));
  EXPECT_CALL(io_, error()).WillOnce(Return(1));

  EXPECT_ANY_THROW(io_.readOrThrow(buf, sizeof(buf), Exiv2::ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoReadOrThrowTest_544, ThrowsPropagatesGivenErrorCodeWhenAvailable_544) {
  Exiv2::byte buf[2] = {};

  const auto err = Exiv2::ErrorCode::kerErrorMessage;

  EXPECT_CALL(io_, read(buf, sizeof(buf))).WillOnce(Return(sizeof(buf) - 1));
  EXPECT_CALL(io_, error()).Times(0);

  try {
    io_.readOrThrow(buf, sizeof(buf), err);
    FAIL() << "Expected an exception to be thrown";
  } catch (const Exiv2::Error& e) {
    // If the library throws Exiv2::Error, its code is an observable behavior.
    EXPECT_EQ(e.code(), err);
  } catch (...) {
    // If a different exception type is used in this build, that's still an error-path.
    SUCCEED();
  }
}

}  // namespace