// SPDX-License-Identifier: GPL-2.0-or-later
// Single-file unit tests for Exiv2::isRw2Type (rw2image.cpp)
//
// TEST_ID: 1583

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

// Exiv2 headers
#include "basicio.hpp"
#include "rw2image_int.hpp"  // Exiv2::Internal::Rw2Header
#include "types.hpp"         // Exiv2::byte, Exiv2::DataBuf (typically)

namespace Exiv2 {
// Function under test (defined in rw2image.cpp)
bool isRw2Type(BasicIo& iIo, bool advance);
}  // namespace Exiv2

namespace {

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
  MOCK_METHOD(int, error, (), (override));
  MOCK_METHOD(bool, eof, (), (override));
};

// Helper: copy from a byte vector into the provided buffer and report as if rcount bytes were read.
static auto ReadFromBytes(const std::vector<Exiv2::byte>& bytes) {
  return [bytes](Exiv2::byte* out, size_t rcount) -> size_t {
    const size_t n = std::min(rcount, bytes.size());
    if (n > 0) {
      std::copy(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(n), out);
    }
    // The production code does not check the returned size_t, only error()/eof().
    return rcount;
  };
}

// Helper: obtain a "known-good" RW2 header byte sequence using the existing implementation.
static std::vector<Exiv2::byte> MakeValidRw2HeaderBytes() {
  Exiv2::Internal::Rw2Header hdr;
  Exiv2::DataBuf db = hdr.write();

  // DataBuf layout is part of Exiv2 public API in the codebase (commonly pData_/size_).
  // If your DataBuf uses different accessors, adjust here accordingly.
  std::vector<Exiv2::byte> out;
  out.resize(static_cast<size_t>(db.size_));
  std::copy(db.pData_, db.pData_ + db.size_, out.begin());
  return out;
}

class Rw2TypeTest_1583 : public ::testing::Test {};

TEST_F(Rw2TypeTest_1583, ReturnsFalseWhenIoError_NoSeek_1583) {
  StrictMock<MockBasicIo> io;

  EXPECT_CALL(io, read(_, 24)).WillOnce(Return(24));
  EXPECT_CALL(io, error()).WillOnce(Return(1));
  EXPECT_CALL(io, eof()).Times(0);
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isRw2Type(io, /*advance=*/false));
}

TEST_F(Rw2TypeTest_1583, ReturnsFalseWhenEof_NoSeek_1583) {
  StrictMock<MockBasicIo> io;

  EXPECT_CALL(io, read(_, 24)).WillOnce(Return(24));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(true));
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isRw2Type(io, /*advance=*/true));
}

TEST_F(Rw2TypeTest_1583, AdvanceFalse_ValidHeader_SeeksBackAndReturnsTrue_1583) {
  StrictMock<MockBasicIo> io;

  const auto valid = MakeValidRw2HeaderBytes();
  ASSERT_GE(valid.size(), 24u);

  EXPECT_CALL(io, read(_, 24)).WillOnce(Invoke(ReadFromBytes(valid)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  // When advance == false and header parsing succeeds, function must seek back by -24 from cur.
  EXPECT_CALL(io, seek(-24, Exiv2::BasicIo::cur)).WillOnce(Return(0));

  EXPECT_TRUE(Exiv2::isRw2Type(io, /*advance=*/false));
}

TEST_F(Rw2TypeTest_1583, AdvanceTrue_ValidHeader_DoesNotSeekAndReturnsTrue_1583) {
  StrictMock<MockBasicIo> io;

  const auto valid = MakeValidRw2HeaderBytes();
  ASSERT_GE(valid.size(), 24u);

  EXPECT_CALL(io, read(_, 24)).WillOnce(Invoke(ReadFromBytes(valid)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  // When advance == true and parsing succeeds, no rewind is expected.
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_TRUE(Exiv2::isRw2Type(io, /*advance=*/true));
}

TEST_F(Rw2TypeTest_1583, AdvanceTrue_InvalidHeader_SeeksBackAndReturnsFalse_1583) {
  StrictMock<MockBasicIo> io;

  auto invalid = MakeValidRw2HeaderBytes();
  ASSERT_GE(invalid.size(), 24u);

  // Corrupt a byte (without assuming which fields are checked; we just mutate the buffer).
  invalid[0] = static_cast<Exiv2::byte>(invalid[0] ^ 0xFF);

  EXPECT_CALL(io, read(_, 24)).WillOnce(Invoke(ReadFromBytes(invalid)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  // When parsing fails, function rewinds regardless of advance flag.
  EXPECT_CALL(io, seek(-24, Exiv2::BasicIo::cur)).WillOnce(Return(0));

  EXPECT_FALSE(Exiv2::isRw2Type(io, /*advance=*/true));
}

TEST_F(Rw2TypeTest_1583, Boundary_ReadCalledWithExactLength24_1583) {
  StrictMock<MockBasicIo> io;

  // Provide any bytes; behavior is not asserted beyond verifying the requested read size.
  std::vector<Exiv2::byte> bytes(24, 0);

  EXPECT_CALL(io, read(_, 24)).WillOnce(Invoke(ReadFromBytes(bytes)));
  EXPECT_CALL(io, error()).WillOnce(Return(1));  // force early return independent of header parsing
  EXPECT_CALL(io, eof()).Times(0);
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isRw2Type(io, /*advance=*/false));
}

}  // namespace