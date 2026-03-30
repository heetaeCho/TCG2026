// TEST_ID 1569
// File: test_asfvideo_headerextension_1569.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <deque>
#include <memory>
#include <stdexcept>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"  // DataBuf

namespace {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::InSequence;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SaveArg;

// Expose protected headerExtension() for testing via a public wrapper.
class TestableAsfVideo : public Exiv2::AsfVideo {
 public:
  using Exiv2::AsfVideo::AsfVideo;

  void CallHeaderExtension() const { this->headerExtension(); }
};

// A small helper to serve deterministic bytes to whichever BasicIo read API is used
// (read(size_t), read(byte*,size_t), or getb()).
class DwordProvider {
 public:
  explicit DwordProvider(std::array<Exiv2::byte, 4> bytes) : bytes_(bytes) {}

  Exiv2::DataBuf ReadBuf(size_t n) {
    Exiv2::DataBuf buf(n);
    for (size_t i = 0; i < n; ++i) {
      buf.data()[i] = NextByte();
    }
    return buf;
  }

  size_t ReadRaw(Exiv2::byte* out, size_t n) {
    for (size_t i = 0; i < n; ++i) {
      out[i] = NextByte();
    }
    return n;
  }

  int Getb() { return static_cast<int>(NextByte()); }

  void Reset() { idx_ = 0; }

 private:
  Exiv2::byte NextByte() {
    if (idx_ >= bytes_.size()) return bytes_.back();
    return bytes_[idx_++];
  }

  std::array<Exiv2::byte, 4> bytes_;
  size_t idx_ = 0;
};

class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
  MOCK_METHOD(const size_t, tell, (), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, getb, (), (override));
};

static uint32_t dwordAllBytesSame(Exiv2::byte b) {
  // 0xBBBBBBBB (endianness-independent if all bytes are identical)
  return (static_cast<uint32_t>(b) << 24) |
         (static_cast<uint32_t>(b) << 16) |
         (static_cast<uint32_t>(b) << 8)  |
         (static_cast<uint32_t>(b));
}

TEST(AsfVideoHeaderExtensionTest_1569, SeeksPastHeaderExtensionWithZeroLength_1569) {
  auto io = std::make_unique<MockBasicIo>();
  auto* ioRaw = io.get();

  // Provide DWORD = 0x00000000 so interpreted length is 0 regardless of endianness.
  DwordProvider provider({0x00, 0x00, 0x00, 0x00});

  // Provide a tell() sequence that can tolerate extra tell() calls:
  // the first "meaningful" tell should be 10, and later tell should be 100.
  std::deque<size_t> tells = {10u, 100u, 100u, 100u, 100u};

  ON_CALL(*ioRaw, tell()).WillByDefault(Invoke([&]() -> size_t {
    if (tells.empty()) return 100u;
    size_t v = tells.front();
    tells.pop_front();
    return v;
  }));

  // Support whichever read API the implementation uses.
  ON_CALL(*ioRaw, read(_)).WillByDefault(Invoke([&](size_t n) {
    provider.Reset();
    return provider.ReadBuf(n);
  }));
  ON_CALL(*ioRaw, read(_, _)).WillByDefault(Invoke([&](Exiv2::byte* out, size_t n) {
    provider.Reset();
    return provider.ReadRaw(out, n);
  }));
  ON_CALL(*ioRaw, getb()).WillByDefault(Invoke([&]() {
    return provider.Getb();
  }));

  int64_t firstSeekOffset = -1;
  int64_t secondSeekOffset = -1;

  {
    InSequence seq;

    EXPECT_CALL(*ioRaw, seek(_, Exiv2::BasicIo::beg))
        .WillOnce(DoAll(SaveArg<0>(&firstSeekOffset), Return(0)));

    EXPECT_CALL(*ioRaw, seek(_, Exiv2::BasicIo::beg))
        .WillOnce(DoAll(SaveArg<0>(&secondSeekOffset), Return(0)));
  }

  // Allow extra tell/read/getb calls beyond what we assert explicitly.
  EXPECT_CALL(*ioRaw, tell()).Times(AtLeast(1));
  EXPECT_CALL(*ioRaw, read(_)).Times(AnyNumber());
  EXPECT_CALL(*ioRaw, read(_, _)).Times(AnyNumber());
  EXPECT_CALL(*ioRaw, getb()).Times(AnyNumber());

  TestableAsfVideo video(std::move(io));
  video.CallHeaderExtension();

  // First seek should advance by GUID(16) + WORD(2) from the starting tell.
  // We don't assume any internal state beyond the public constants described.
  EXPECT_EQ(firstSeekOffset, static_cast<int64_t>(10u + 16u + 2u));

  // With a 0 length DWORD, second seek should be to (tell() + 0).
  EXPECT_EQ(secondSeekOffset, static_cast<int64_t>(100u));
}

TEST(AsfVideoHeaderExtensionTest_1569, SeeksPastHeaderExtensionWithEndianIndependentNonZeroLength_1569) {
  auto io = std::make_unique<MockBasicIo>();
  auto* ioRaw = io.get();

  // Provide DWORD bytes all identical (0x01 0x01 0x01 0x01),
  // so the interpreted value is the same regardless of endianness.
  constexpr Exiv2::byte kB = 0x01;
  const uint32_t kLen = dwordAllBytesSame(kB);
  DwordProvider provider({kB, kB, kB, kB});

  std::deque<size_t> tells = {0u, 200u, 200u, 200u, 200u};

  ON_CALL(*ioRaw, tell()).WillByDefault(Invoke([&]() -> size_t {
    if (tells.empty()) return 200u;
    size_t v = tells.front();
    tells.pop_front();
    return v;
  }));

  ON_CALL(*ioRaw, read(_)).WillByDefault(Invoke([&](size_t n) {
    provider.Reset();
    return provider.ReadBuf(n);
  }));
  ON_CALL(*ioRaw, read(_, _)).WillByDefault(Invoke([&](Exiv2::byte* out, size_t n) {
    provider.Reset();
    return provider.ReadRaw(out, n);
  }));
  ON_CALL(*ioRaw, getb()).WillByDefault(Invoke([&]() {
    return provider.Getb();
  }));

  int64_t firstSeekOffset = -1;
  int64_t secondSeekOffset = -1;

  {
    InSequence seq;
    EXPECT_CALL(*ioRaw, seek(_, Exiv2::BasicIo::beg))
        .WillOnce(DoAll(SaveArg<0>(&firstSeekOffset), Return(0)));
    EXPECT_CALL(*ioRaw, seek(_, Exiv2::BasicIo::beg))
        .WillOnce(DoAll(SaveArg<0>(&secondSeekOffset), Return(0)));
  }

  EXPECT_CALL(*ioRaw, tell()).Times(AtLeast(1));
  EXPECT_CALL(*ioRaw, read(_)).Times(AnyNumber());
  EXPECT_CALL(*ioRaw, read(_, _)).Times(AnyNumber());
  EXPECT_CALL(*ioRaw, getb()).Times(AnyNumber());

  TestableAsfVideo video(std::move(io));
  video.CallHeaderExtension();

  EXPECT_EQ(firstSeekOffset, static_cast<int64_t>(0u + 16u + 2u));
  EXPECT_EQ(secondSeekOffset, static_cast<int64_t>(200u + static_cast<size_t>(kLen)));
}

TEST(AsfVideoHeaderExtensionTest_1569, PropagatesExceptionFromFirstSeek_1569) {
  auto io = std::make_unique<MockBasicIo>();
  auto* ioRaw = io.get();

  ON_CALL(*ioRaw, tell()).WillByDefault(Return(0u));

  EXPECT_CALL(*ioRaw, seek(_, Exiv2::BasicIo::beg))
      .WillOnce(Invoke([](int64_t, Exiv2::BasicIo::Position) -> int {
        throw std::runtime_error("seek failed");
      }));

  TestableAsfVideo video(std::move(io));
  EXPECT_THROW(video.CallHeaderExtension(), std::runtime_error);
}

TEST(AsfVideoHeaderExtensionTest_1569, PropagatesExceptionFromReadingDword_1569) {
  auto io = std::make_unique<MockBasicIo>();
  auto* ioRaw = io.get();

  // Ensure first seek succeeds.
  ON_CALL(*ioRaw, tell()).WillByDefault(Return(0u));
  EXPECT_CALL(*ioRaw, seek(_, Exiv2::BasicIo::beg)).WillOnce(Return(0));

  // If readDWORDTag uses read(size_t), make it throw.
  EXPECT_CALL(*ioRaw, read(_))
      .WillOnce(Invoke([](size_t) -> Exiv2::DataBuf {
        throw std::runtime_error("read failed");
      }));

  // Also allow alternative read APIs; if the implementation uses them, we still fail by throwing.
  ON_CALL(*ioRaw, read(_, _)).WillByDefault(Invoke([](Exiv2::byte*, size_t) -> size_t {
    throw std::runtime_error("read failed");
  }));
  ON_CALL(*ioRaw, getb()).WillByDefault(Invoke([]() -> int {
    throw std::runtime_error("read failed");
  }));

  TestableAsfVideo video(std::move(io));
  EXPECT_THROW(video.CallHeaderExtension(), std::runtime_error);
}

}  // namespace