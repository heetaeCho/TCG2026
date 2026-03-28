// File: test_mrwimage_isMrwType_984.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

namespace Exiv2 {
// Function under test (implemented in the real codebase)
bool isMrwType(BasicIo& iIo, bool advance);
}  // namespace Exiv2

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
  MOCK_METHOD(int, error, (), (override));
  MOCK_METHOD(bool, eof, (), (override));
};

class MrwImageTest_984 : public ::testing::Test {
 protected:
  static constexpr size_t kLen = 4;

  static void Fill(Exiv2::byte* dst, const std::array<Exiv2::byte, kLen>& src) {
    for (size_t i = 0; i < kLen; ++i) dst[i] = src[i];
  }
};

TEST_F(MrwImageTest_984, ReturnsTrueAndDoesNotSeekWhenMrwAndAdvanceTrue_984) {
  StrictMock<MockBasicIo> io;

  const std::array<Exiv2::byte, kLen> kMrwId{0x00, 0x4d, 0x52, 0x4d};

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t) { Fill(buf, kMrwId); }),
                      Return(kLen)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_TRUE(Exiv2::isMrwType(io, /*advance=*/true));
}

TEST_F(MrwImageTest_984, ReturnsTrueAndSeeksBackWhenMrwAndAdvanceFalse_984) {
  StrictMock<MockBasicIo> io;

  const std::array<Exiv2::byte, kLen> kMrwId{0x00, 0x4d, 0x52, 0x4d};

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t) { Fill(buf, kMrwId); }),
                      Return(kLen)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));
  EXPECT_CALL(io, seek(-static_cast<int64_t>(kLen), Exiv2::BasicIo::cur))
      .WillOnce(Return(0));

  EXPECT_TRUE(Exiv2::isMrwType(io, /*advance=*/false));
}

TEST_F(MrwImageTest_984, ReturnsFalseAndSeeksBackWhenNotMrwEvenIfAdvanceTrue_984) {
  StrictMock<MockBasicIo> io;

  const std::array<Exiv2::byte, kLen> kNotMrw{0x01, 0x02, 0x03, 0x04};

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t) { Fill(buf, kNotMrw); }),
                      Return(kLen)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));
  EXPECT_CALL(io, seek(-static_cast<int64_t>(kLen), Exiv2::BasicIo::cur))
      .WillOnce(Return(0));

  EXPECT_FALSE(Exiv2::isMrwType(io, /*advance=*/true));
}

TEST_F(MrwImageTest_984, ReturnsFalseAndSeeksBackWhenNotMrwAndAdvanceFalse_984) {
  StrictMock<MockBasicIo> io;

  const std::array<Exiv2::byte, kLen> kNotMrw{0xaa, 0xbb, 0xcc, 0xdd};

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t) { Fill(buf, kNotMrw); }),
                      Return(kLen)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(false));
  EXPECT_CALL(io, seek(-static_cast<int64_t>(kLen), Exiv2::BasicIo::cur))
      .WillOnce(Return(0));

  EXPECT_FALSE(Exiv2::isMrwType(io, /*advance=*/false));
}

TEST_F(MrwImageTest_984, ReturnsFalseWithoutSeekWhenIoErrorAfterRead_984) {
  StrictMock<MockBasicIo> io;

  const std::array<Exiv2::byte, kLen> any{0x00, 0x4d, 0x52, 0x4d};

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t) { Fill(buf, any); }),
                      Return(kLen)));
  EXPECT_CALL(io, error()).WillOnce(Return(1));  // error observed
  EXPECT_CALL(io, eof()).Times(0);               // short-circuit via ||
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isMrwType(io, /*advance=*/true));
}

TEST_F(MrwImageTest_984, ReturnsFalseWithoutSeekWhenEofAfterRead_984) {
  StrictMock<MockBasicIo> io;

  const std::array<Exiv2::byte, kLen> any{0x00, 0x4d, 0x52, 0x4d};

  EXPECT_CALL(io, read(_, kLen))
      .WillOnce(DoAll(Invoke([&](Exiv2::byte* buf, size_t) { Fill(buf, any); }),
                      Return(kLen)));
  EXPECT_CALL(io, error()).WillOnce(Return(0));
  EXPECT_CALL(io, eof()).WillOnce(Return(true));  // eof observed
  EXPECT_CALL(io, seek(_, _)).Times(0);

  EXPECT_FALSE(Exiv2::isMrwType(io, /*advance=*/false));
}

}  // namespace