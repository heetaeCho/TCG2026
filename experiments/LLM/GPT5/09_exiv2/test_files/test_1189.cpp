// =================================================================================================
// TEST_ID: 1189
// File: test_psdimage_ispsdtype_1189.cpp
// Unit tests for: Exiv2::isPsdType(BasicIo& iIo, bool advance)
// =================================================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

#include "exiv2/basicio.hpp"

namespace Exiv2 {
// Forward declaration (function is defined in src/psdimage.cpp)
bool isPsdType(BasicIo& iIo, bool advance);
}  // namespace Exiv2

namespace {

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;

class MockBasicIo : public Exiv2::BasicIo {
 public:
  ~MockBasicIo() override = default;

  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
};

class IsPsdTypeTest_1189 : public ::testing::Test {
 protected:
  static constexpr int32_t kLen = 6;

  static std::array<Exiv2::byte, kLen> PsdHeader() {
    return std::array<Exiv2::byte, kLen>{'8', 'B', 'P', 'S', 0, 1};
  }

  static std::array<Exiv2::byte, kLen> NotPsdHeader() {
    return std::array<Exiv2::byte, kLen>{'8', 'B', 'P', 'S', 0, 2};
  }

  static void FillReadBuffer(Exiv2::byte* dst, const std::array<Exiv2::byte, kLen>& src) {
    std::memcpy(dst, src.data(), src.size());
  }
};

// Normal: header matches, advance=true => returns true and does NOT rewind.
TEST_F(IsPsdTypeTest_1189, ReturnsTrueAndDoesNotSeekBackWhenAdvanceTrueAndHeaderMatches_1189) {
  MockBasicIo io;

  const auto header = PsdHeader();

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t /*rcount*/) { FillReadBuffer(buf, header); }),
                      Return(static_cast<size_t>(kLen))));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_TRUE(Exiv2::isPsdType(io, /*advance=*/true));
}

// Normal: header matches, advance=false => returns true and rewinds by -6 from current.
TEST_F(IsPsdTypeTest_1189, ReturnsTrueAndSeeksBackWhenAdvanceFalseAndHeaderMatches_1189) {
  MockBasicIo io;

  const auto header = PsdHeader();

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t /*rcount*/) { FillReadBuffer(buf, header); }),
                      Return(static_cast<size_t>(kLen))));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  EXPECT_CALL(io, seek(-kLen, Exiv2::BasicIo::cur)).WillOnce(Return(0));

  EXPECT_TRUE(Exiv2::isPsdType(io, /*advance=*/false));
}

// Normal: header does not match, advance=true => returns false and rewinds by -6 from current.
TEST_F(IsPsdTypeTest_1189, ReturnsFalseAndSeeksBackWhenAdvanceTrueAndHeaderDoesNotMatch_1189) {
  MockBasicIo io;

  const auto notHeader = NotPsdHeader();

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t /*rcount*/) { FillReadBuffer(buf, notHeader); }),
                      Return(static_cast<size_t>(kLen))));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  EXPECT_CALL(io, seek(-kLen, Exiv2::BasicIo::cur)).WillOnce(Return(0));

  EXPECT_FALSE(Exiv2::isPsdType(io, /*advance=*/true));
}

// Boundary/behavioral: header does not match, advance=false => returns false and still rewinds by -6.
TEST_F(IsPsdTypeTest_1189, ReturnsFalseAndSeeksBackWhenAdvanceFalseAndHeaderDoesNotMatch_1189) {
  MockBasicIo io;

  const auto notHeader = NotPsdHeader();

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t /*rcount*/) { FillReadBuffer(buf, notHeader); }),
                      Return(static_cast<size_t>(kLen))));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  EXPECT_CALL(io, seek(-kLen, Exiv2::BasicIo::cur)).WillOnce(Return(0));

  EXPECT_FALSE(Exiv2::isPsdType(io, /*advance=*/false));
}

// Error case: io.error() true after read => returns false and does NOT attempt to seek back.
TEST_F(IsPsdTypeTest_1189, ReturnsFalseAndDoesNotSeekWhenIoErrorIsSetAfterRead_1189) {
  MockBasicIo io;

  const auto header = PsdHeader();

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t /*rcount*/) { FillReadBuffer(buf, header); }),
                      Return(static_cast<size_t>(kLen))));
  EXPECT_CALL(io, error()).WillOnce(Return(1));
  EXPECT_CALL(io, eof()).Times(0);

  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isPsdType(io, /*advance=*/true));
}

// Error case: io.eof() true after read => returns false and does NOT attempt to seek back.
TEST_F(IsPsdTypeTest_1189, ReturnsFalseAndDoesNotSeekWhenIoEofIsSetAfterRead_1189) {
  MockBasicIo io;

  const auto header = PsdHeader();

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t /*rcount*/) { FillReadBuffer(buf, header); }),
                      Return(static_cast<size_t>(kLen))));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(true));

  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isPsdType(io, /*advance=*/false));
}

}  // namespace