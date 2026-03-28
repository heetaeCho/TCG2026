// File: test_quicktimevideo_readstring_659.cpp
// TEST_ID: 659

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

// Many Exiv2 builds expose Exiv2::Error (thrown by enforce/readOrThrow paths).
// We keep code checks SFINAE-safe so this test stays compatible across versions.
#include "exiv2/exceptions.hpp"

// Include the TU under test so the TU-local `static` function is visible here.
#include "quicktimevideo.cpp"

namespace {

// Minimal BasicIo implementation to drive observable behavior of readString().
class FakeBasicIo_659 : public Exiv2::BasicIo {
 public:
  explicit FakeBasicIo_659(std::vector<Exiv2::byte> data) : data_(std::move(data)) {}

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (!buf && rcount != 0) return 0;
    const size_t remaining = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t to_read = std::min(rcount, remaining);
    if (to_read > 0) {
      std::copy_n(data_.data() + pos_, to_read, buf);
      pos_ += to_read;
    }
    return to_read;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    // Minimal, deterministic seek behavior for tests that need it.
    // We only support Begin/Current/End typical semantics.
    int64_t base = 0;
    switch (pos) {
      case Exiv2::Position::beg:
        base = 0;
        break;
      case Exiv2::Position::cur:
        base = static_cast<int64_t>(pos_);
        break;
      case Exiv2::Position::end:
        base = static_cast<int64_t>(data_.size());
        break;
      default:
        base = static_cast<int64_t>(pos_);
        break;
    }
    int64_t np = base + offset;
    if (np < 0) np = 0;
    if (np > static_cast<int64_t>(data_.size())) np = static_cast<int64_t>(data_.size());
    pos_ = static_cast<size_t>(np);
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }

  // Keep other behavior simple and stable.
  const bool isopen() override { return true; }

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};
};

// --- SFINAE helpers for optional error-code verification ---
template <typename T, typename = void>
struct HasCodeMethod : std::false_type {};
template <typename T>
struct HasCodeMethod<T, std::void_t<decltype(std::declval<const T&>().code())>> : std::true_type {};

template <typename T>
static void ExpectErrorCodeIfAvailable_659(const T& err, Exiv2::ErrorCode expected) {
  if constexpr (HasCodeMethod<T>::value) {
    EXPECT_EQ(err.code(), expected);
  } else {
    (void)err;
    (void)expected;
  }
}

class QuicktimeReadStringTest_659 : public ::testing::Test {};

}  // namespace

TEST_F(QuicktimeReadStringTest_659, ReadsExactBytesAndAdvancesPosition_659) {
  std::vector<Exiv2::byte> bytes = {'a', 'b', 'c', 'd', 'e'};
  FakeBasicIo_659 io(bytes);

  EXPECT_EQ(io.tell(), 0u);
  const std::string s = Exiv2::readString(io, 3);

  EXPECT_EQ(s, "abc");
  EXPECT_EQ(io.tell(), 3u);
}

TEST_F(QuicktimeReadStringTest_659, SizeZeroReturnsEmptyStringAndDoesNotAdvance_659) {
  std::vector<Exiv2::byte> bytes = {'x', 'y', 'z'};
  FakeBasicIo_659 io(bytes);

  EXPECT_EQ(io.tell(), 0u);
  const std::string s = Exiv2::readString(io, 0);

  EXPECT_TRUE(s.empty());
  EXPECT_EQ(io.tell(), 0u);
}

TEST_F(QuicktimeReadStringTest_659, ReadsUpToEndWhenSizeEqualsRemaining_659) {
  std::vector<Exiv2::byte> bytes = {'h', 'i', '!'};
  FakeBasicIo_659 io(bytes);

  const std::string s = Exiv2::readString(io, 3);

  EXPECT_EQ(s, "hi!");
  EXPECT_EQ(io.tell(), 3u);
}

TEST_F(QuicktimeReadStringTest_659, ThrowsWhenRequestedSizeExceedsRemaining_659) {
  std::vector<Exiv2::byte> bytes = {'1', '2', '3'};
  FakeBasicIo_659 io(bytes);

  // Move position so remaining bytes are fewer than requested.
  ASSERT_EQ(io.seek(2, Exiv2::Position::beg), 0);
  ASSERT_EQ(io.tell(), 2u);
  ASSERT_EQ(io.size(), 3u);

  try {
    (void)Exiv2::readString(io, 2);  // remaining is 1; should fail before reading.
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCodeIfAvailable_659(e, Exiv2::ErrorCode::kerCorruptedMetadata);
    // Ensure position did not advance on failure (observable state).
    EXPECT_EQ(io.tell(), 2u);
  }
}

TEST_F(QuicktimeReadStringTest_659, ReadingConsumesExactlyRequestedBytesAcrossMultipleCalls_659) {
  std::vector<Exiv2::byte> bytes = {'A', 'B', 'C', 'D'};
  FakeBasicIo_659 io(bytes);

  const std::string s1 = Exiv2::readString(io, 2);
  EXPECT_EQ(s1, "AB");
  EXPECT_EQ(io.tell(), 2u);

  const std::string s2 = Exiv2::readString(io, 2);
  EXPECT_EQ(s2, "CD");
  EXPECT_EQ(io.tell(), 4u);
}