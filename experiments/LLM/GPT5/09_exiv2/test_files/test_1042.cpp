// File: test_bmpimage_isBmptype_1042.cpp
// TEST_ID: 1042

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>

#include "exiv2/basicio.hpp"

namespace Exiv2 {
// Function under test (implemented in bmpimage.cpp in the real codebase)
bool isBmpType(BasicIo& iIo, bool advance);
}  // namespace Exiv2

namespace {

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArrayArgument;

class MockBasicIo_1042 : public Exiv2::BasicIo {
 public:
  MockBasicIo_1042() = default;
  ~MockBasicIo_1042() override = default;

  MOCK_METHOD(std::size_t, read, (Exiv2::byte* buf, std::size_t rcount), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
};

// Helper to make bytes easily.
constexpr Exiv2::byte B(char c) { return static_cast<Exiv2::byte>(c); }

class BmpImageTest_1042 : public ::testing::Test {};

TEST_F(BmpImageTest_1042, ReturnsTrueWhenHeaderIsBMAndAdvanceTrue_NoSeekBack_1042) {
  MockBasicIo_1042 io;

  const std::array<Exiv2::byte, 2> bm{{B('B'), B('M')}};

  EXPECT_CALL(io, read(_, 2))
      .WillOnce(DoAll(SetArrayArgument<0>(bm.begin(), bm.end()), Return(2)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  // When advance==true and matched, function should NOT seek back.
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_TRUE(Exiv2::isBmpType(io, /*advance=*/true));
}

TEST_F(BmpImageTest_1042, ReturnsTrueWhenHeaderIsBMAndAdvanceFalse_SeeksBack_1042) {
  MockBasicIo_1042 io;

  const std::array<Exiv2::byte, 2> bm{{B('B'), B('M')}};

  EXPECT_CALL(io, read(_, 2))
      .WillOnce(DoAll(SetArrayArgument<0>(bm.begin(), bm.end()), Return(2)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  // When advance==false, even if matched, it should seek back by 2 from current.
  EXPECT_CALL(io, seek(-2, Exiv2::BasicIo::cur)).WillOnce(Return(0));

  EXPECT_TRUE(Exiv2::isBmpType(io, /*advance=*/false));
}

TEST_F(BmpImageTest_1042, ReturnsFalseWhenHeaderNotBM_AdvanceTrue_SeeksBack_1042) {
  MockBasicIo_1042 io;

  const std::array<Exiv2::byte, 2> not_bm{{B('B'), B('X')}};

  EXPECT_CALL(io, read(_, 2))
      .WillOnce(DoAll(SetArrayArgument<0>(not_bm.begin(), not_bm.end()), Return(2)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  // Not matched => seek back regardless of advance value.
  EXPECT_CALL(io, seek(-2, Exiv2::BasicIo::cur)).WillOnce(Return(0));

  EXPECT_FALSE(Exiv2::isBmpType(io, /*advance=*/true));
}

TEST_F(BmpImageTest_1042, ReturnsFalseWhenHeaderNotBM_AdvanceFalse_SeeksBack_1042) {
  MockBasicIo_1042 io;

  const std::array<Exiv2::byte, 2> not_bm{{B('X'), B('M')}};

  EXPECT_CALL(io, read(_, 2))
      .WillOnce(DoAll(SetArrayArgument<0>(not_bm.begin(), not_bm.end()), Return(2)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));

  EXPECT_CALL(io, seek(-2, Exiv2::BasicIo::cur)).WillOnce(Return(0));

  EXPECT_FALSE(Exiv2::isBmpType(io, /*advance=*/false));
}

TEST_F(BmpImageTest_1042, ReturnsFalseWhenIoReportsError_NoSeekBack_1042) {
  MockBasicIo_1042 io;

  const std::array<Exiv2::byte, 2> bm{{B('B'), B('M')}};

  EXPECT_CALL(io, read(_, 2))
      .WillOnce(DoAll(SetArrayArgument<0>(bm.begin(), bm.end()), Return(2)));

  // If error() is set, function should return false immediately (no seek).
  EXPECT_CALL(io, error()).WillOnce(Return(1));
  // eof() may or may not be queried depending on implementation order; allow any.
  EXPECT_CALL(io, eof()).Times(::testing::AnyNumber());

  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isBmpType(io, /*advance=*/true));
}

TEST_F(BmpImageTest_1042, ReturnsFalseWhenIoReportsEof_NoSeekBack_1042) {
  MockBasicIo_1042 io;

  const std::array<Exiv2::byte, 2> bm{{B('B'), B('M')}};

  EXPECT_CALL(io, read(_, 2))
      .WillOnce(DoAll(SetArrayArgument<0>(bm.begin(), bm.end()), Return(2)));

  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(true));

  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isBmpType(io, /*advance=*/false));
}

}  // namespace