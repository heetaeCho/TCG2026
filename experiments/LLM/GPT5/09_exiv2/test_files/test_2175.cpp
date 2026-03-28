// ============================================================================
// Test file for Exiv2::PngImage constructor behavior (pngimage.cpp)
// TEST_ID: 2175
// ============================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"
#include "exiv2/pngimage.hpp"

namespace {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));

  // The rest are not needed for these tests; allow accidental calls if any.
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::Position pos), (override));
  MOCK_METHOD(Exiv2::byte*, mmap, (bool isWriteable), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(const size_t, tell, (), (override));
  MOCK_METHOD(const size_t, size, (), (override));
  MOCK_METHOD(const bool, isopen, (), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
  MOCK_METHOD(const std::string&, path, (), (override));
  MOCK_METHOD(void, populateFakeData, (), (override));
  MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
};

class PngImageCtorTest_2175 : public ::testing::Test {
 protected:
  static constexpr size_t kPngBlankSize = 103;  // from provided snippet (pngBlank[103])
};

TEST_F(PngImageCtorTest_2175, CreateFalse_DoesNotOpenOrWrite_2175) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();
  auto* ioPtr = io.get();

  // Constructor should not attempt to create PNG when create==false.
  EXPECT_CALL(*ioPtr, open()).Times(0);
  EXPECT_CALL(*ioPtr, write(_, _)).Times(0);

  // Be permissive about close in case other layers close during destruction.
  EXPECT_CALL(*ioPtr, close()).Times(AnyNumber()).WillRepeatedly(Return(0));

  Exiv2::PngImage image(std::move(io), /*create=*/false);
}

TEST_F(PngImageCtorTest_2175, CreateTrue_OpenSuccess_WritesBlankPngSize_2175) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();
  auto* ioPtr = io.get();

  // Only verify observable interactions: open() then write() of the expected size.
  {
    InSequence seq;
    EXPECT_CALL(*ioPtr, open()).WillOnce(Return(0));
    EXPECT_CALL(*ioPtr, write(_, kPngBlankSize)).WillOnce(Return(kPngBlankSize));
  }

  // Allow close any number (IoCloser and/or other destructors may close).
  EXPECT_CALL(*ioPtr, close()).Times(AnyNumber()).WillRepeatedly(Return(0));

  Exiv2::PngImage image(std::move(io), /*create=*/true);
}

TEST_F(PngImageCtorTest_2175, CreateTrue_OpenFailure_DoesNotWrite_2175) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();
  auto* ioPtr = io.get();

  EXPECT_CALL(*ioPtr, open()).WillOnce(Return(1));  // non-zero => open failure
  EXPECT_CALL(*ioPtr, write(_, _)).Times(0);

  // Close behavior is not asserted here (implementation-dependent outside the shown block).
  EXPECT_CALL(*ioPtr, close()).Times(AnyNumber()).WillRepeatedly(Return(0));

  Exiv2::PngImage image(std::move(io), /*create=*/true);
}

TEST_F(PngImageCtorTest_2175, CreateTrue_OpenSuccess_WriteShort_IsStillAttemptedOnce_2175) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();
  auto* ioPtr = io.get();

  {
    InSequence seq;
    EXPECT_CALL(*ioPtr, open()).WillOnce(Return(0));
    // If write fails/short-writes, constructor does not throw (based on provided code),
    // but we can still verify it attempted a single write of the blank size.
    EXPECT_CALL(*ioPtr, write(_, kPngBlankSize)).WillOnce(Return(kPngBlankSize - 1));
  }

  EXPECT_CALL(*ioPtr, close()).Times(AnyNumber()).WillRepeatedly(Return(0));

  Exiv2::PngImage image(std::move(io), /*create=*/true);
}

}  // namespace