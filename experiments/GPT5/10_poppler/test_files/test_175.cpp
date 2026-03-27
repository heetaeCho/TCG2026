// File: test_basememstream_unfilteredrewind_175.cpp
// TEST_ID: 175

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler/Stream.h"
#include "poppler/Object.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockMemStream_175 : public BaseMemStream<unsigned char> {
public:
  MockMemStream_175(unsigned char* bufA, Goffset startA, Goffset lengthA, Object&& dictA)
      : BaseMemStream<unsigned char>(bufA, startA, lengthA, std::move(dictA)) {}

  MOCK_METHOD(bool, rewind, (), (override));
};

class BaseMemStreamTest_175 : public ::testing::Test {
protected:
  static constexpr int kBufSize = 8;
  unsigned char buf[kBufSize] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};

  static Object MakeDict() {
    // Keep this minimal and non-assumptive: BaseMemStream ctor takes an Object rvalue.
    // A default-constructed Object is sufficient for constructing the stream in this test.
    return Object();
  }
};

TEST_F(BaseMemStreamTest_175, UnfilteredRewindReturnsTrueWhenRewindReturnsTrue_175) {
  StrictMock<MockMemStream_175> stream(buf, /*startA=*/0, /*lengthA=*/kBufSize, MakeDict());

  EXPECT_CALL(stream, rewind()).WillOnce(Return(true));

  EXPECT_TRUE(stream.unfilteredRewind());
}

TEST_F(BaseMemStreamTest_175, UnfilteredRewindReturnsFalseWhenRewindReturnsFalse_175) {
  StrictMock<MockMemStream_175> stream(buf, /*startA=*/0, /*lengthA=*/kBufSize, MakeDict());

  EXPECT_CALL(stream, rewind()).WillOnce(Return(false));

  EXPECT_FALSE(stream.unfilteredRewind());
}

TEST_F(BaseMemStreamTest_175, UnfilteredRewindDelegatesToRewindEachCall_175) {
  StrictMock<MockMemStream_175> stream(buf, /*startA=*/0, /*lengthA=*/kBufSize, MakeDict());

  EXPECT_CALL(stream, rewind())
      .Times(2)
      .WillRepeatedly(Return(true));

  EXPECT_TRUE(stream.unfilteredRewind());
  EXPECT_TRUE(stream.unfilteredRewind());
}

} // namespace