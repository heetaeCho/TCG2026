// TEST_ID: 124
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Stream.h"

using ::testing::Return;

namespace {

class StreamTest_124 : public ::testing::Test {};

class DerivedStreamReturnsNext_124 : public Stream {
public:
  explicit DerivedStreamReturnsNext_124(Stream *next) : next_(next) {}
  Stream *getNextStream() const override { return next_; }

private:
  Stream *next_;
};

class MockStream_124 : public Stream {
public:
  MOCK_METHOD(Stream *, getNextStream, (), (const, override));
};

TEST_F(StreamTest_124, DefaultGetNextStreamReturnsNullptr_124) {
  Stream s;
  EXPECT_EQ(nullptr, s.getNextStream());
}

TEST_F(StreamTest_124, GetNextStreamIsVirtualAndCanBeOverridden_124) {
  Stream next;
  DerivedStreamReturnsNext_124 s(&next);

  Stream *ret = s.getNextStream();
  EXPECT_EQ(&next, ret);
}

TEST_F(StreamTest_124, PolymorphicCallThroughBasePointerUsesOverride_124) {
  Stream next;
  DerivedStreamReturnsNext_124 derived(&next);

  const Stream *basePtr = &derived;  // const to match signature
  Stream *ret = basePtr->getNextStream();

  EXPECT_EQ(&next, ret);
}

TEST_F(StreamTest_124, GetNextStreamInvokesOverrideOnMock_124) {
  MockStream_124 mock;

  EXPECT_CALL(mock, getNextStream()).Times(1).WillOnce(Return(nullptr));

  const Stream *basePtr = &mock;
  EXPECT_EQ(nullptr, basePtr->getNextStream());
}

}  // namespace