// ============================================================================
// tests_pngimage_isPngType_977.cpp
// Unit tests for Exiv2::isPngType (./src/pngimage.cpp)
// ============================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace Exiv2 {
// Function under test (implemented in src/pngimage.cpp)
bool isPngType(BasicIo& iIo, bool advance);
}  // namespace Exiv2

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

constexpr int32_t kPngSigLen_977 = 8;

// PNG signature as provided in the prompt.
const std::array<unsigned char, kPngSigLen_977> kPngSignature_977 = {
    137, 80, 78, 71, 13, 10, 26, 10
};

class MockBasicIo_977 : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, error, (), (override));
  MOCK_METHOD(bool, eof, (), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
};

// Simple fixture to centralize default behavior.
class IsPngTypeTest_977 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default: no error, not eof.
    ON_CALL(io_, error()).WillByDefault(Return(0));
    ON_CALL(io_, eof()).WillByDefault(Return(false));
    // Default seek/read return values (overridden per-test when needed).
    ON_CALL(io_, seek(_, _)).WillByDefault(Return(0));
    ON_CALL(io_, read(_, _)).WillByDefault(Return(static_cast<size_t>(kPngSigLen_977)));
  }

  NiceMock<MockBasicIo_977> io_;
};

TEST_F(IsPngTypeTest_977, ThrowsIfInitialError_977) {
  EXPECT_CALL(io_, error()).WillOnce(Return(1));
  // isPngType checks error/eof before attempting to read.
  EXPECT_THROW((void)Exiv2::isPngType(io_, /*advance=*/true), Exiv2::Error);
}

TEST_F(IsPngTypeTest_977, ThrowsIfInitialEof_977) {
  EXPECT_CALL(io_, error()).WillOnce(Return(0));
  EXPECT_CALL(io_, eof()).WillOnce(Return(true));
  // isPngType checks error/eof before attempting to read.
  EXPECT_THROW((void)Exiv2::isPngType(io_, /*advance=*/false), Exiv2::Error);
}

TEST_F(IsPngTypeTest_977, ReturnsTrueAndDoesNotSeekBackWhenSignatureMatchesAndAdvanceTrue_977) {
  EXPECT_CALL(io_, read(_, kPngSigLen_977))
      .WillOnce(Invoke([](Exiv2::byte* buf, size_t rcount) -> size_t {
        // Fill buffer with the PNG signature.
        const size_t n = (rcount < kPngSignature_977.size()) ? rcount : kPngSignature_977.size();
        std::memcpy(buf, kPngSignature_977.data(), n);
        return rcount;
      }));

  // When advance==true and signature matches, it should NOT seek back.
  EXPECT_CALL(io_, seek(_, _)).Times(0);

  const bool rc = Exiv2::isPngType(io_, /*advance=*/true);
  EXPECT_TRUE(rc);
}

TEST_F(IsPngTypeTest_977, ReturnsTrueAndSeeksBackWhenSignatureMatchesAndAdvanceFalse_977) {
  EXPECT_CALL(io_, read(_, kPngSigLen_977))
      .WillOnce(Invoke([](Exiv2::byte* buf, size_t rcount) -> size_t {
        const size_t n = (rcount < kPngSignature_977.size()) ? rcount : kPngSignature_977.size();
        std::memcpy(buf, kPngSignature_977.data(), n);
        return rcount;
      }));

  EXPECT_CALL(io_, seek(static_cast<int64_t>(-kPngSigLen_977), Exiv2::BasicIo::cur)).Times(1);

  const bool rc = Exiv2::isPngType(io_, /*advance=*/false);
  EXPECT_TRUE(rc);
}

TEST_F(IsPngTypeTest_977, ReturnsFalseAndSeeksBackWhenSignatureDoesNotMatchAdvanceTrue_977) {
  EXPECT_CALL(io_, read(_, kPngSigLen_977))
      .WillOnce(Invoke([](Exiv2::byte* buf, size_t rcount) -> size_t {
        // Fill with something that is not the PNG signature.
        std::memset(buf, 0, rcount);
        return rcount;
      }));

  // If signature doesn't match, it seeks back regardless of advance.
  EXPECT_CALL(io_, seek(static_cast<int64_t>(-kPngSigLen_977), Exiv2::BasicIo::cur)).Times(1);

  const bool rc = Exiv2::isPngType(io_, /*advance=*/true);
  EXPECT_FALSE(rc);
}

TEST_F(IsPngTypeTest_977, ReturnsFalseAndSeeksBackWhenSignatureDoesNotMatchAdvanceFalse_977) {
  EXPECT_CALL(io_, read(_, kPngSigLen_977))
      .WillOnce(Invoke([](Exiv2::byte* buf, size_t rcount) -> size_t {
        std::memset(buf, 0xFF, rcount);
        // Flip first byte so it's clearly not the PNG signature.
        if (rcount > 0) buf[0] = 0;
        return rcount;
      }));

  EXPECT_CALL(io_, seek(static_cast<int64_t>(-kPngSigLen_977), Exiv2::BasicIo::cur)).Times(1);

  const bool rc = Exiv2::isPngType(io_, /*advance=*/false);
  EXPECT_FALSE(rc);
}

TEST_F(IsPngTypeTest_977, ReturnsFalseWithoutSeekingWhenReadLeavesIoInError_977) {
  // Simulate a read call occurring, then error() reporting an error afterward.
  EXPECT_CALL(io_, read(_, kPngSigLen_977)).WillOnce(Return(static_cast<size_t>(kPngSigLen_977)));

  // After read, isPngType checks (error || eof) and returns false early.
  // Provide: first checks (pre-read) => ok, then post-read => error.
  EXPECT_CALL(io_, error()).WillOnce(Return(0))  // pre-read
                           .WillOnce(Return(1)); // post-read
  EXPECT_CALL(io_, eof()).WillRepeatedly(Return(false));

  // Because it returns false early after read error/eof, it should not seek.
  EXPECT_CALL(io_, seek(_, _)).Times(0);

  const bool rc = Exiv2::isPngType(io_, /*advance=*/true);
  EXPECT_FALSE(rc);
}

TEST_F(IsPngTypeTest_977, ReturnsFalseWithoutSeekingWhenReadHitsEof_977) {
  EXPECT_CALL(io_, read(_, kPngSigLen_977)).WillOnce(Return(static_cast<size_t>(kPngSigLen_977)));

  // pre-read ok; post-read eof true -> returns false early.
  EXPECT_CALL(io_, error()).WillOnce(Return(0)).WillOnce(Return(0));
  EXPECT_CALL(io_, eof()).WillOnce(Return(false))  // pre-read
                         .WillOnce(Return(true));  // post-read

  EXPECT_CALL(io_, seek(_, _)).Times(0);

  const bool rc = Exiv2::isPngType(io_, /*advance=*/false);
  EXPECT_FALSE(rc);
}

}  // namespace