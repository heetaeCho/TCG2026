// File: test_filterstream_getbasestream_140.cpp
// The TEST_ID is 140

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/Stream.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace {

// We only mock what we need for these tests (public virtual interface).
class MockStream : public Stream {
public:
  MOCK_METHOD(BaseStream *, getBaseStream, (), (override));
};

class FilterStreamTest_140 : public ::testing::Test {
protected:
  // NOTE: Ownership/lifetime of the wrapped Stream is intentionally not assumed here.
  // We allocate on heap and "release" to avoid double-delete risks if FilterStream takes ownership.
  MockStream *makeWrappedStream() {
    wrapped_.reset(new NiceMock<MockStream>());
    return wrapped_.get();
  }

  void releaseWrappedStreamOwnership() { (void)wrapped_.release(); }

private:
  std::unique_ptr<MockStream> wrapped_;
};

} // namespace

TEST_F(FilterStreamTest_140, GetBaseStreamDelegatesAndReturnsSamePointer_140)
{
  auto *wrapped = makeWrappedStream();
  FilterStream fs(wrapped);

  auto *expected = reinterpret_cast<BaseStream *>(0x1234);
  EXPECT_CALL(*wrapped, getBaseStream()).WillOnce(Return(expected));

  EXPECT_EQ(fs.getBaseStream(), expected);

  // Avoid assuming ownership semantics (FilterStream may or may not delete wrapped).
  releaseWrappedStreamOwnership();
}

TEST_F(FilterStreamTest_140, GetBaseStreamPropagatesNullptr_140)
{
  auto *wrapped = makeWrappedStream();
  FilterStream fs(wrapped);

  EXPECT_CALL(*wrapped, getBaseStream()).WillOnce(Return(nullptr));

  EXPECT_EQ(fs.getBaseStream(), nullptr);

  releaseWrappedStreamOwnership();
}

TEST_F(FilterStreamTest_140, GetBaseStreamForwardsEachCall_140)
{
  auto *wrapped = makeWrappedStream();
  FilterStream fs(wrapped);

  auto *p1 = reinterpret_cast<BaseStream *>(0x1111);
  auto *p2 = reinterpret_cast<BaseStream *>(0x2222);

  EXPECT_CALL(*wrapped, getBaseStream()).WillOnce(Return(p1)).WillOnce(Return(p2));

  EXPECT_EQ(fs.getBaseStream(), p1);
  EXPECT_EQ(fs.getBaseStream(), p2);

  releaseWrappedStreamOwnership();
}