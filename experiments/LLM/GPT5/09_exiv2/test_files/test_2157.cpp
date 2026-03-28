// =================================================================================================
// TEST_ID: 2157
// File: test_iowrapper_2157.cpp
// Unit tests for Exiv2::Internal::IoWrapper (constructor-dependent observable behavior)
// =================================================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"
#include "tiffcomposite_int.hpp"

using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockBasicIo : public Exiv2::BasicIo {
public:
  ~MockBasicIo() override = default;

  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
  MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
};

class IoWrapperTest_2157 : public ::testing::Test {
protected:
  static constexpr Exiv2::byte kHeader2_[2] = {0xAA, 0xBB};
  static constexpr Exiv2::byte kData3_[3] = {0x01, 0x02, 0x03};
};

constexpr Exiv2::byte IoWrapperTest_2157::kHeader2_[2];
constexpr Exiv2::byte IoWrapperTest_2157::kData3_[3];

}  // namespace

// -------------------------------------------------------------------------------------------------
// Constructor cases where wroteHeader_ becomes true immediately:
//  - pHeader == nullptr
//  - size == 0
// Observable expectation (black-box): write/putb should not emit a header in these cases.
// -------------------------------------------------------------------------------------------------

TEST_F(IoWrapperTest_2157, Write_WithNullHeader_ForwardsDataOnly_2157) {
  StrictMock<MockBasicIo> io;

  Exiv2::Internal::IoWrapper w(io, /*pHeader=*/nullptr, /*size=*/2, /*pow=*/nullptr);

  EXPECT_CALL(io, write(IoWrapperTest_2157::kData3_, 3)).WillOnce(Return(3));

  const size_t ret = w.write(IoWrapperTest_2157::kData3_, 3);
  EXPECT_EQ(ret, 3u);
}

TEST_F(IoWrapperTest_2157, Write_WithZeroHeaderSize_ForwardsDataOnly_2157) {
  StrictMock<MockBasicIo> io;

  // Non-null header pointer but size==0 should behave like "no header to write".
  Exiv2::Internal::IoWrapper w(io, /*pHeader=*/IoWrapperTest_2157::kHeader2_, /*size=*/0, /*pow=*/nullptr);

  EXPECT_CALL(io, write(IoWrapperTest_2157::kData3_, 3)).WillOnce(Return(3));

  const size_t ret = w.write(IoWrapperTest_2157::kData3_, 3);
  EXPECT_EQ(ret, 3u);
}

TEST_F(IoWrapperTest_2157, Putb_WithNullHeader_ForwardsByteOnly_2157) {
  StrictMock<MockBasicIo> io;

  Exiv2::Internal::IoWrapper w(io, /*pHeader=*/nullptr, /*size=*/2, /*pow=*/nullptr);

  EXPECT_CALL(io, putb(static_cast<Exiv2::byte>(0x7F))).WillOnce(Return(0));

  const int rc = w.putb(static_cast<Exiv2::byte>(0x7F));
  EXPECT_EQ(rc, 0);
}

TEST_F(IoWrapperTest_2157, Putb_WithZeroHeaderSize_ForwardsByteOnly_2157) {
  StrictMock<MockBasicIo> io;

  Exiv2::Internal::IoWrapper w(io, /*pHeader=*/IoWrapperTest_2157::kHeader2_, /*size=*/0, /*pow=*/nullptr);

  EXPECT_CALL(io, putb(static_cast<Exiv2::byte>(0x00))).WillOnce(Return(0));

  const int rc = w.putb(static_cast<Exiv2::byte>(0x00));
  EXPECT_EQ(rc, 0);
}

// -------------------------------------------------------------------------------------------------
// Constructor case where a header is present and size>0.
// Observable expectation (black-box): the wrapper may emit the header prior to first payload output.
// These tests verify external interactions (BasicIo calls and ordering/parameters).
// -------------------------------------------------------------------------------------------------

TEST_F(IoWrapperTest_2157, Write_WithHeaderAndNonZeroSize_EmitsHeaderThenData_2157) {
  StrictMock<MockBasicIo> io;

  Exiv2::Internal::IoWrapper w(io, /*pHeader=*/IoWrapperTest_2157::kHeader2_, /*size=*/2, /*pow=*/nullptr);

  InSequence seq;
  EXPECT_CALL(io, write(IoWrapperTest_2157::kHeader2_, 2)).WillOnce(Return(2));
  EXPECT_CALL(io, write(IoWrapperTest_2157::kData3_, 3)).WillOnce(Return(3));

  (void)w.write(IoWrapperTest_2157::kData3_, 3);
}

TEST_F(IoWrapperTest_2157, Putb_WithHeaderAndNonZeroSize_EmitsHeaderThenByte_2157) {
  StrictMock<MockBasicIo> io;

  Exiv2::Internal::IoWrapper w(io, /*pHeader=*/IoWrapperTest_2157::kHeader2_, /*size=*/2, /*pow=*/nullptr);

  InSequence seq;
  EXPECT_CALL(io, write(IoWrapperTest_2157::kHeader2_, 2)).WillOnce(Return(2));
  EXPECT_CALL(io, putb(static_cast<Exiv2::byte>(0xCC))).WillOnce(Return(0));

  (void)w.putb(static_cast<Exiv2::byte>(0xCC));
}