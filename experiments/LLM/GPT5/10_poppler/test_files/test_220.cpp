// RunLengthEncoder_tests.cpp
// TEST_ID: 220
//
// Unit tests for RunLengthEncoder (poppler/Stream.h)
// Constraints:
// - Treat implementation as a black box
// - Test only observable behavior through public interface
// - Use GoogleMock only for external interactions (the wrapped Stream)

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Stream.h"

using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Return;

namespace {

class MockStream : public Stream {
public:
  MOCK_METHOD(StreamKind, getKind, (), (const, override));
  MOCK_METHOD(bool, rewind, (), (override));
  MOCK_METHOD(int, getChar, (), (override));
  MOCK_METHOD(int, lookChar, (), (override));
  MOCK_METHOD(int, getUnfilteredChar, (), (override));
  MOCK_METHOD(bool, unfilteredRewind, (), (override));
  MOCK_METHOD(Goffset, getPos, (), (override));
  MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
  MOCK_METHOD(bool, isBinary, (bool last), (const, override));
  MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
  MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
  MOCK_METHOD(Dict*, getDict, (), (override));
  MOCK_METHOD(Object*, getDictObject, (), (override));
};

static MockStream* MakeNiceEOFStream_220(bool isEncoderValue = true) {
  auto* s = new NiceMock<MockStream>();

  // Provide safe defaults for pure virtuals.
  ON_CALL(*s, getKind()).WillByDefault(Return(strWeird));
  ON_CALL(*s, rewind()).WillByDefault(Return(true));
  ON_CALL(*s, getChar()).WillByDefault(Return(EOF));
  ON_CALL(*s, lookChar()).WillByDefault(Return(EOF));
  ON_CALL(*s, getUnfilteredChar()).WillByDefault(Return(EOF));
  ON_CALL(*s, unfilteredRewind()).WillByDefault(Return(true));
  ON_CALL(*s, getPos()).WillByDefault(Return(static_cast<Goffset>(0)));
  ON_CALL(*s, setPos(testing::_, testing::_)).WillByDefault(Return());
  ON_CALL(*s, isBinary(testing::_)).WillByDefault(Return(true));
  ON_CALL(*s, getBaseStream()).WillByDefault(Return(nullptr));
  ON_CALL(*s, getUndecodedStream()).WillByDefault(Return(nullptr));
  ON_CALL(*s, getDict()).WillByDefault(Return(nullptr));
  ON_CALL(*s, getDictObject()).WillByDefault(Return(nullptr));

  // Stream::isEncoder() is non-pure (default false), but RunLengthEncoder dtor
  // checks wrapped stream's isEncoder(). We control that via mocking.
  ON_CALL(*s, isEncoder()).WillByDefault(Return(isEncoderValue));

  return s;
}

// We mock isEncoder() too (non-pure) to verify destructor behavior.
// Need to declare it after the class in the same namespace to keep it clear.
// (GoogleMock allows mocking non-virtual? Stream::isEncoder is virtual.)
class MockStreamWithEncoderFlag : public MockStream {
public:
  MOCK_METHOD(bool, isEncoder, (), (const, override));
};

static MockStreamWithEncoderFlag* MakeStrictStream_220(bool isEncoderValue) {
  auto* s = new StrictMock<MockStreamWithEncoderFlag>();

  // Safe defaults for all pure virtuals.
  ON_CALL(*s, getKind()).WillByDefault(Return(strWeird));
  ON_CALL(*s, rewind()).WillByDefault(Return(true));
  ON_CALL(*s, getChar()).WillByDefault(Return(EOF));
  ON_CALL(*s, lookChar()).WillByDefault(Return(EOF));
  ON_CALL(*s, getUnfilteredChar()).WillByDefault(Return(EOF));
  ON_CALL(*s, unfilteredRewind()).WillByDefault(Return(true));
  ON_CALL(*s, getPos()).WillByDefault(Return(static_cast<Goffset>(0)));
  ON_CALL(*s, setPos(testing::_, testing::_)).WillByDefault(Return());
  ON_CALL(*s, isBinary(testing::_)).WillByDefault(Return(true));
  ON_CALL(*s, getBaseStream()).WillByDefault(Return(nullptr));
  ON_CALL(*s, getUndecodedStream()).WillByDefault(Return(nullptr));
  ON_CALL(*s, getDict()).WillByDefault(Return(nullptr));
  ON_CALL(*s, getDictObject()).WillByDefault(Return(nullptr));

  ON_CALL(*s, isEncoder()).WillByDefault(Return(isEncoderValue));
  return s;
}

class RunLengthEncoderTest_220 : public ::testing::Test {};

} // namespace

TEST_F(RunLengthEncoderTest_220, GetKindReturnsStrWeird_220) {
  // External dependency: wrapped Stream (not expected to be called for getKind()).
  Stream* wrapped = MakeNiceEOFStream_220(/*isEncoderValue=*/true);

  RunLengthEncoder enc(wrapped);
  EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(RunLengthEncoderTest_220, GetKindIsStableAcrossMultipleCalls_220) {
  Stream* wrapped = MakeNiceEOFStream_220(/*isEncoderValue=*/true);

  RunLengthEncoder enc(wrapped);
  EXPECT_EQ(enc.getKind(), strWeird);
  EXPECT_EQ(enc.getKind(), strWeird);
  EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(RunLengthEncoderTest_220, RewindForwardsToWrappedStreamAndPropagatesTrue_220) {
  auto* wrapped = MakeStrictStream_220(/*isEncoderValue=*/true);

  // Verify external interaction and returned value propagation.
  EXPECT_CALL(*wrapped, rewind()).WillOnce(Return(true));
  // RunLengthEncoder destructor should query isEncoder() on wrapped stream.
  EXPECT_CALL(*wrapped, isEncoder()).WillOnce(Return(true));

  RunLengthEncoder enc(wrapped);
  EXPECT_TRUE(enc.rewind());
  EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(RunLengthEncoderTest_220, RewindForwardsToWrappedStreamAndPropagatesFalse_220) {
  auto* wrapped = MakeStrictStream_220(/*isEncoderValue=*/true);

  EXPECT_CALL(*wrapped, rewind()).WillOnce(Return(false));
  EXPECT_CALL(*wrapped, isEncoder()).WillOnce(Return(true));

  RunLengthEncoder enc(wrapped);
  EXPECT_FALSE(enc.rewind());
}

TEST_F(RunLengthEncoderTest_220, EncoderReportsIsEncoderTrue_220) {
  Stream* wrapped = MakeNiceEOFStream_220(/*isEncoderValue=*/true);

  RunLengthEncoder enc(wrapped);
  EXPECT_TRUE(enc.isEncoder());
}

TEST_F(RunLengthEncoderTest_220, DestructorChecksWrappedIsEncoder_220) {
  auto* wrapped = MakeStrictStream_220(/*isEncoderValue=*/true);

  // Observable external interaction: destructor checks wrapped->isEncoder().
  EXPECT_CALL(*wrapped, isEncoder()).WillOnce(Return(true));

  {
    RunLengthEncoder enc(wrapped);
    (void)enc.getKind();
  }
  // If wrapped stream wasn't deleted, this would leak; deletion is handled by encoder.
}

TEST_F(RunLengthEncoderTest_220, DestructorDoesNotDeleteWrappedWhenWrappedIsNotEncoder_220) {
  auto* wrapped = MakeStrictStream_220(/*isEncoderValue=*/false);

  // Destructor still checks wrapped->isEncoder().
  EXPECT_CALL(*wrapped, isEncoder()).WillOnce(Return(false));

  {
    RunLengthEncoder enc(wrapped);
    EXPECT_EQ(enc.getKind(), strWeird);
  }

  // Since wrapped->isEncoder() returned false, encoder should not delete it.
  // We must delete it ourselves to avoid leaks.
  delete wrapped;
}