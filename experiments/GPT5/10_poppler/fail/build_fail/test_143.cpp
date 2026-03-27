// TEST_ID = 143
// File: FilterStream_getDictObject_tests_143.cc

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/Stream.h"

using ::testing::Return;

namespace {

class MockStream : public Stream {
public:
  MOCK_METHOD(Object *, getDictObject, (), (override));
};

class FilterStreamTest_143 : public ::testing::Test {};

TEST_F(FilterStreamTest_143, GetDictObject_ForwardsCallAndReturnsSamePointer_143) {
  MockStream mock;
  auto *expected = reinterpret_cast<Object *>(0x1234);

  EXPECT_CALL(mock, getDictObject()).Times(1).WillOnce(Return(expected));

  FilterStream fs(&mock);
  EXPECT_EQ(fs.getDictObject(), expected);
}

TEST_F(FilterStreamTest_143, GetDictObject_PropagatesNullptr_143) {
  MockStream mock;

  EXPECT_CALL(mock, getDictObject()).Times(1).WillOnce(Return(nullptr));

  FilterStream fs(&mock);
  EXPECT_EQ(fs.getDictObject(), nullptr);
}

TEST_F(FilterStreamTest_143, GetDictObject_MultipleCallsForwardEachTime_143) {
  MockStream mock;
  auto *expected = reinterpret_cast<Object *>(0xBEEF);

  EXPECT_CALL(mock, getDictObject()).Times(3).WillRepeatedly(Return(expected));

  FilterStream fs(&mock);
  EXPECT_EQ(fs.getDictObject(), expected);
  EXPECT_EQ(fs.getDictObject(), expected);
  EXPECT_EQ(fs.getDictObject(), expected);
}

} // namespace