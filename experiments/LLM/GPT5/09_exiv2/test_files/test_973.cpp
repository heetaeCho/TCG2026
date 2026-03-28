// TEST_ID 973
// Unit tests for internal helper: Exiv2::readChunk(DataBuf&, BasicIo&)
//
// Notes:
// - readChunk() is a static function in pngimage.cpp (internal linkage). To test it as a black box,
//   we include the implementation file so the symbol is visible in this TU.
// - We do NOT infer any internal logic beyond observable behavior: throws vs no-throw and buffer effects.

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

// Include the .cpp to access the internal-linkage function in this translation unit.
#include "pngimage.cpp"

namespace {

// Small helper: check Exiv2::Error has a .code() accessor (if available in this build),
// otherwise just skip the exact-code assertion to keep tests robust across variations.
template <typename T, typename = void>
struct HasCodeMethod : std::false_type {};
template <typename T>
struct HasCodeMethod<T, std::void_t<decltype(std::declval<const T&>().code())>> : std::true_type {};

static void ExpectErrorCodeIfAvailable(const Exiv2::Error& e, Exiv2::ErrorCode expected) {
  if constexpr (HasCodeMethod<Exiv2::Error>::value) {
    EXPECT_EQ(e.code(), expected);
  } else {
    (void)e;
    (void)expected;
    SUCCEED();
  }
}

// A minimal controllable BasicIo test double.
// We only override what readChunk() uses: read(byte*, size_t) and error().
class FakeBasicIo final : public Exiv2::BasicIo {
 public:
  explicit FakeBasicIo(std::vector<Exiv2::byte> data,
                       size_t bytes_to_return,
                       int error_flag = 0)
      : data_(std::move(data)), bytes_to_return_(bytes_to_return), error_flag_(error_flag) {}

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    ++read_calls_;
    last_read_count_ = rcount;

    const size_t n = (std::min)({rcount, bytes_to_return_, data_.size()});
    if (n > 0) {
      std::memcpy(buf, data_.data(), n);
    }
    return n;
  }

  const int error() override { return error_flag_; }

  // Introspection for verifying external interaction (read call count and rcount parameter).
  int read_calls() const { return read_calls_; }
  size_t last_read_count() const { return last_read_count_; }

 private:
  std::vector<Exiv2::byte> data_;
  size_t bytes_to_return_{0};
  int error_flag_{0};

  int read_calls_{0};
  size_t last_read_count_{0};
};

}  // namespace

TEST(ReadChunkTest_973, ReadsExactBytesAndDoesNotThrow_973) {
  Exiv2::DataBuf buffer(4);

  const std::vector<Exiv2::byte> src = {0xDE, 0xAD, 0xBE, 0xEF};
  FakeBasicIo io(src, /*bytes_to_return=*/src.size(), /*error_flag=*/0);

  EXPECT_NO_THROW(Exiv2::readChunk(buffer, io));

  ASSERT_EQ(io.read_calls(), 1);
  EXPECT_EQ(io.last_read_count(), buffer.size());

  ASSERT_EQ(buffer.size(), src.size());
  EXPECT_EQ(std::memcmp(buffer.data(), src.data(), src.size()), 0);
}

TEST(ReadChunkTest_973, ZeroSizeBufferDoesNotThrowAndReadsZero_973) {
  Exiv2::DataBuf buffer(0);

  const std::vector<Exiv2::byte> src = {0x01, 0x02, 0x03};
  FakeBasicIo io(src, /*bytes_to_return=*/src.size(), /*error_flag=*/0);

  EXPECT_NO_THROW(Exiv2::readChunk(buffer, io));

  ASSERT_EQ(io.read_calls(), 1);
  EXPECT_EQ(io.last_read_count(), 0u);
}

TEST(ReadChunkTest_973, PartialReadThrowsInputDataReadFailed_973) {
  Exiv2::DataBuf buffer(5);

  const std::vector<Exiv2::byte> src = {0x10, 0x20, 0x30, 0x40, 0x50};
  FakeBasicIo io(src, /*bytes_to_return=*/3, /*error_flag=*/0);

  try {
    Exiv2::readChunk(buffer, io);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCodeIfAvailable(e, Exiv2::ErrorCode::kerInputDataReadFailed);
  }

  ASSERT_EQ(io.read_calls(), 1);
  EXPECT_EQ(io.last_read_count(), buffer.size());
}

TEST(ReadChunkTest_973, IoErrorThrowsFailedToReadImageData_973) {
  Exiv2::DataBuf buffer(4);

  const std::vector<Exiv2::byte> src = {0xAA, 0xBB, 0xCC, 0xDD};
  FakeBasicIo io(src, /*bytes_to_return=*/src.size(), /*error_flag=*/1);

  try {
    Exiv2::readChunk(buffer, io);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCodeIfAvailable(e, Exiv2::ErrorCode::kerFailedToReadImageData);
  }

  ASSERT_EQ(io.read_calls(), 1);
  EXPECT_EQ(io.last_read_count(), buffer.size());
}

TEST(ReadChunkTest_973, IoErrorTakesPrecedenceOverShortRead_973) {
  Exiv2::DataBuf buffer(6);

  const std::vector<Exiv2::byte> src = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  FakeBasicIo io(src, /*bytes_to_return=*/2, /*error_flag=*/1);

  try {
    Exiv2::readChunk(buffer, io);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Observable behavior: error condition is reported as a read failure of image data.
    ExpectErrorCodeIfAvailable(e, Exiv2::ErrorCode::kerFailedToReadImageData);
  }

  ASSERT_EQ(io.read_calls(), 1);
  EXPECT_EQ(io.last_read_count(), buffer.size());
}