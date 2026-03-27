// File: test_orfimage_isOrfType_1556.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <vector>
#include <algorithm>

// Exiv2 headers (as available in your tree)
#include "exiv2/basicio.hpp"

// The function under test lives in src/orfimage.cpp (no public header provided here),
// so we forward-declare it.
namespace Exiv2 {
bool isOrfType(BasicIo& iIo, bool advance);
}  // namespace Exiv2

using ::testing::_;
using ::testing::DoAll;
using ::testing::InSequence;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArrayArgument;
using ::testing::StrictMock;

namespace {

// A strict mock to verify external interactions (read/seek/error/eof).
class MockBasicIo final : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
};

static std::vector<Exiv2::byte> MakeLikelyValidOrfHeader8_LE() {
  // Based only on observable constructor constants shown for OrfHeader:
  // - 0x4f52 and first IFD offset 0x00000008, size=8, TIFF-style layout.
  // Little-endian "II" + 0x4f52 as bytes "RO" -> "IIRO" + offset 8.
  return {
      static_cast<Exiv2::byte>(0x49), static_cast<Exiv2::byte>(0x49),
      static_cast<Exiv2::byte>(0x52), static_cast<Exiv2::byte>(0x4f),
      static_cast<Exiv2::byte>(0x08), static_cast<Exiv2::byte>(0x00),
      static_cast<Exiv2::byte>(0x00), static_cast<Exiv2::byte>(0x00),
  };
}

static std::vector<Exiv2::byte> MakeInvalidHeader8() {
  return std::vector<Exiv2::byte>(8, static_cast<Exiv2::byte>(0x00));
}

}  // namespace

class OrfImageIsOrfTypeTest_1556 : public ::testing::Test {
 protected:
  static constexpr size_t kLen = 8;
};

TEST_F(OrfImageIsOrfTypeTest_1556, ReturnsFalseWhenIoErrorAfterRead_1556) {
  StrictMock<MockBasicIo> io;

  // read happens first, then error()/eof() are checked.
  EXPECT_CALL(io, read(_, kLen)).WillOnce(Return(kLen));
  EXPECT_CALL(io, error()).WillOnce(Return(1));
  EXPECT_CALL(io, eof()).Times(0);
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isOrfType(io, /*advance=*/false));
}

TEST_F(OrfImageIsOrfTypeTest_1556, ReturnsFalseWhenIoEofAfterRead_1556) {
  StrictMock<MockBasicIo> io;

  EXPECT_CALL(io, read(_, kLen)).WillOnce(Return(kLen));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(true));
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isOrfType(io, /*advance=*/true));
}

TEST_F(OrfImageIsOrfTypeTest_1556, SeeksBackWhenHeaderNotRecognized_RegardlessOfAdvance_1556) {
  StrictMock<MockBasicIo> io;
  const auto invalid = MakeInvalidHeader8();

  {
    InSequence seq;

    EXPECT_CALL(io, read(_, kLen))
        .WillOnce(DoAll(SetArrayArgument<0>(invalid.begin(), invalid.end()), Return(kLen)));
    EXPECT_CALL(io, error()).WillOnce(Return(0));
    EXPECT_CALL(io, eof()).WillOnce(Return(false));
    // If header read fails (rc == false), function seeks back even if advance==true.
    EXPECT_CALL(io, seek(-static_cast<int64_t>(kLen), Exiv2::BasicIo::cur)).WillOnce(Return(0));
  }

  EXPECT_FALSE(Exiv2::isOrfType(io, /*advance=*/true));
}

TEST_F(OrfImageIsOrfTypeTest_1556, WhenAdvanceFalseAndHeaderRecognized_SeeksBackAndReturnsTrue_1556) {
  StrictMock<MockBasicIo> io;
  const auto hdr = MakeLikelyValidOrfHeader8_LE();

  {
    InSequence seq;

    EXPECT_CALL(io, read(_, kLen))
        .WillOnce(DoAll(SetArrayArgument<0>(hdr.begin(), hdr.end()), Return(kLen)));
    EXPECT_CALL(io, error()).WillOnce(Return(0));
    EXPECT_CALL(io, eof()).WillOnce(Return(false));
    // advance==false => should seek back even on success.
    EXPECT_CALL(io, seek(-static_cast<int64_t>(kLen), Exiv2::BasicIo::cur)).WillOnce(Return(0));
  }

  EXPECT_TRUE(Exiv2::isOrfType(io, /*advance=*/false));
}

TEST_F(OrfImageIsOrfTypeTest_1556, WhenAdvanceTrueAndHeaderRecognized_DoesNotSeekBackAndReturnsTrue_1556) {
  StrictMock<MockBasicIo> io;
  const auto hdr = MakeLikelyValidOrfHeader8_LE();

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(SetArrayArgument<0>(hdr.begin(), hdr.end()), Return(kLen)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));
  // advance==true and rc==true => no seek back.
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_TRUE(Exiv2::isOrfType(io, /*advance=*/true));
}

TEST_F(OrfImageIsOrfTypeTest_1556, AlwaysReadsExactlyEightBytes_1556) {
  StrictMock<MockBasicIo> io;
  const auto invalid = MakeInvalidHeader8();

  // Verify the fixed-length read behavior (boundary: exactly 8).
  EXPECT_CALL(io, read(_, 8))
      .WillOnce(DoAll(SetArrayArgument<0>(invalid.begin(), invalid.end()), Return(8)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));
  EXPECT_CALL(io, seek(-static_cast<int64_t>(8), Exiv2::BasicIo::cur)).WillOnce(Return(0));

  (void)Exiv2::isOrfType(io, /*advance=*/false);
}