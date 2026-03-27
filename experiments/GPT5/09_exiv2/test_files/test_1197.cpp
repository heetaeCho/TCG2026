// ============================================================================
// TestProjects/exiv2/tests/bmffimage_parsetiff_test_1197.cpp
//
// Unit tests for Exiv2::BmffImage::parseTiff(uint32_t root_tag, uint64_t length)
// TEST_ID: 1197
// ============================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"
#include "exiv2/bmffimage.hpp"
#include "exiv2/error.hpp"

#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <vector>

namespace {

using ::testing::_;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;

class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(const size_t, tell, (), (override));
  MOCK_METHOD(const size_t, size, (), (override));
  MOCK_METHOD(const int, error, (), (override));
};

class BmffImageParseTiffTest_1197 : public ::testing::Test {
protected:
  static std::unique_ptr<Exiv2::BmffImage> MakeImage(std::unique_ptr<Exiv2::BasicIo> io) {
    // max_box_depth is irrelevant for parseTiff(root_tag, length) tests here.
    return std::make_unique<Exiv2::BmffImage>(std::move(io), /*create=*/false, /*max_box_depth=*/16U);
  }
};

TEST_F(BmffImageParseTiffTest_1197, LengthZero_NoReadNoThrow_1197) {
  auto io = std::make_unique<NiceMock<MockBasicIo>>();
  // If parseTiff is a no-op for length <= 8, it must not call into io_.
  EXPECT_CALL(*io, read(_, _)).Times(0);
  EXPECT_CALL(*io, tell()).Times(0);
  EXPECT_CALL(*io, size()).Times(0);
  EXPECT_CALL(*io, error()).Times(0);

  auto image = MakeImage(std::move(io));
  EXPECT_NO_THROW(image->parseTiff(/*root_tag=*/0U, /*length=*/0U));
}

TEST_F(BmffImageParseTiffTest_1197, LengthEight_NoReadNoThrow_1197) {
  auto io = std::make_unique<NiceMock<MockBasicIo>>();
  EXPECT_CALL(*io, read(_, _)).Times(0);
  EXPECT_CALL(*io, tell()).Times(0);
  EXPECT_CALL(*io, size()).Times(0);
  EXPECT_CALL(*io, error()).Times(0);

  auto image = MakeImage(std::move(io));
  EXPECT_NO_THROW(image->parseTiff(/*root_tag=*/0U, /*length=*/8U));
}

TEST_F(BmffImageParseTiffTest_1197, LengthTooLargeForRemainingBytes_ThrowsError_1197) {
  auto io = std::make_unique<NiceMock<MockBasicIo>>();

  // remaining = size - tell = 100 - 50 = 50
  // requested = length - 8 = 72  -> enforce should fail and throw
  ON_CALL(*io, size()).WillByDefault(Return(static_cast<size_t>(100)));
  ON_CALL(*io, tell()).WillByDefault(Return(static_cast<size_t>(50)));

  // Should fail before reading
  EXPECT_CALL(*io, read(_, _)).Times(0);
  // size/tell should be consulted at least once
  EXPECT_CALL(*io, size()).Times(testing::AtLeast(1));
  EXPECT_CALL(*io, tell()).Times(testing::AtLeast(1));

  auto image = MakeImage(std::move(io));
  EXPECT_THROW(image->parseTiff(/*root_tag=*/0U, /*length=*/80U), Exiv2::Error);
}

TEST_F(BmffImageParseTiffTest_1197, ReadSetsIoError_ThrowsFailedToReadImageData_1197) {
  auto io = std::make_unique<NiceMock<MockBasicIo>>();

  ON_CALL(*io, size()).WillByDefault(Return(static_cast<size_t>(1000)));
  ON_CALL(*io, tell()).WillByDefault(Return(static_cast<size_t>(0)));

  const uint64_t length = 8U + 14U; // request 14 bytes
  const size_t expectedRead = static_cast<size_t>(length - 8U);

  // Return full read count, but report io_->error() afterwards.
  EXPECT_CALL(*io, read(_, expectedRead))
      .WillOnce(Return(expectedRead));
  EXPECT_CALL(*io, error()).WillOnce(Return(1));

  auto image = MakeImage(std::move(io));
  EXPECT_THROW(image->parseTiff(/*root_tag=*/0U, length), Exiv2::Error);
}

TEST_F(BmffImageParseTiffTest_1197, ShortRead_ThrowsInputDataReadFailed_1197) {
  auto io = std::make_unique<NiceMock<MockBasicIo>>();

  ON_CALL(*io, size()).WillByDefault(Return(static_cast<size_t>(1000)));
  ON_CALL(*io, tell()).WillByDefault(Return(static_cast<size_t>(0)));

  const uint64_t length = 8U + 14U; // request 14 bytes
  const size_t expectedRead = static_cast<size_t>(length - 8U);

  // Short read (no io error) => should throw.
  EXPECT_CALL(*io, read(_, expectedRead))
      .WillOnce(Return(expectedRead - 1));
  EXPECT_CALL(*io, error()).WillOnce(Return(0));

  auto image = MakeImage(std::move(io));
  EXPECT_THROW(image->parseTiff(/*root_tag=*/0U, length), Exiv2::Error);
}

TEST_F(BmffImageParseTiffTest_1197, ValidMinimalTiffPayload_ReadsExpectedBytes_NoThrow_1197) {
  auto io = std::make_unique<NiceMock<MockBasicIo>>();

  ON_CALL(*io, size()).WillByDefault(Return(static_cast<size_t>(1000)));
  ON_CALL(*io, tell()).WillByDefault(Return(static_cast<size_t>(0)));
  ON_CALL(*io, error()).WillByDefault(Return(0));

  // Minimal TIFF header + empty IFD:
  // 0-1: 'I''I' (little endian)
  // 2-3: 42 (0x2A00)
  // 4-7: offset to first IFD = 8
  // 8-9: number of directory entries = 0
  // 10-13: next IFD offset = 0
  const std::vector<Exiv2::byte> tiff = {
      0x49, 0x49, 0x2A, 0x00,
      0x08, 0x00, 0x00, 0x00,
      0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
  };

  const uint64_t length = 8U + static_cast<uint64_t>(tiff.size());
  const size_t expectedRead = tiff.size();

  EXPECT_CALL(*io, read(_, expectedRead))
      .WillOnce(Invoke([&](Exiv2::byte* buf, size_t rcount) -> size_t {
        std::memcpy(buf, tiff.data(), std::min(rcount, tiff.size()));
        return expectedRead; // full read
      }));

  auto image = MakeImage(std::move(io));
  EXPECT_NO_THROW(image->parseTiff(/*root_tag=*/0U, length));
}

TEST_F(BmffImageParseTiffTest_1197, LengthExceedsSizeTMax_ThrowsOn32BitPlatforms_1197) {
  // This behavior is only observable on platforms where size_t is smaller than uint64_t.
  if (sizeof(size_t) >= sizeof(uint64_t)) {
    GTEST_SKIP() << "size_t is 64-bit; length-8 <= size_t::max is always satisfied for uint64_t length.";
  }

  auto io = std::make_unique<NiceMock<MockBasicIo>>();
  ON_CALL(*io, size()).WillByDefault(Return(static_cast<size_t>(1000)));
  ON_CALL(*io, tell()).WillByDefault(Return(static_cast<size_t>(0)));

  // Force (length - 8) > size_t::max
  const uint64_t tooBig = static_cast<uint64_t>(std::numeric_limits<size_t>::max()) + 9ULL;

  // Should fail before reading
  EXPECT_CALL(*io, read(_, _)).Times(0);

  auto image = MakeImage(std::move(io));
  EXPECT_THROW(image->parseTiff(/*root_tag=*/0U, tooBig), Exiv2::Error);
}

} // namespace