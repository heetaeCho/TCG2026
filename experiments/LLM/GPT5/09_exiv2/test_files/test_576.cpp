// File: test_memio_destructor_576.cpp
// TEST_ID: 576
//
// Unit tests for Exiv2::MemIo public interface (black-box).
// Focus: observable behavior via public API; no reliance on internal state.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

using Exiv2::BasicIo;
using Exiv2::byte;
using Exiv2::MemIo;

// Helper to get a "begin" position token without assuming where Position enum lives.
static BasicIo::Position BegPos() { return BasicIo::beg; }
static BasicIo::Position CurPos() { return BasicIo::cur; }
static BasicIo::Position EndPos() { return BasicIo::end; }

class MemIoTest_576 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeBytes(const char* s) {
    std::vector<byte> out;
    const size_t n = std::strlen(s);
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) out.push_back(static_cast<byte>(s[i]));
    return out;
  }
};

TEST_F(MemIoTest_576, DefaultCtor_OpenClose_TogglesIsOpen_576) {
  MemIo io;

  // Open/close should be callable and should toggle isopen() in a consistent manner.
  (void)io.open();
  EXPECT_TRUE(io.isopen());

  (void)io.close();
  EXPECT_FALSE(io.isopen());
}

TEST_F(MemIoTest_576, WriteThenSeekToBeginningThenRead_RoundTripsBytes_576) {
  MemIo io;
  ASSERT_NO_THROW((void)io.open());

  const auto payload = MakeBytes("hello memio");
  const size_t written = io.write(payload.data(), payload.size());
  EXPECT_EQ(written, payload.size());

  // Seek to beginning and read back.
  (void)io.seek(0, BegPos());
  std::vector<byte> buf(payload.size(), 0);
  const size_t readCount = io.read(buf.data(), buf.size());
  EXPECT_EQ(readCount, payload.size());
  EXPECT_TRUE(std::equal(buf.begin(), buf.end(), payload.begin()));

  (void)io.close();
}

TEST_F(MemIoTest_576, PutbThenGetb_ReadsBackSameByte_576) {
  MemIo io;
  ASSERT_NO_THROW((void)io.open());

  const byte v = static_cast<byte>(0xAB);
  const int putRes = io.putb(v);
  (void)putRes;  // Do not assume concrete success code; behavior validated via getb.

  (void)io.seek(0, BegPos());
  const int got = io.getb();
  ASSERT_GE(got, 0);  // Observably, a byte value should be returned.
  EXPECT_EQ(static_cast<byte>(got), v);

  (void)io.close();
}

TEST_F(MemIoTest_576, CtorWithInitialData_ReadReturnsThatData_576) {
  const auto initial = MakeBytes("seed");
  MemIo io(initial.data(), initial.size());
  ASSERT_NO_THROW((void)io.open());

  (void)io.seek(0, BegPos());
  std::vector<byte> buf(initial.size(), 0);
  const size_t readCount = io.read(buf.data(), buf.size());
  EXPECT_EQ(readCount, initial.size());
  EXPECT_TRUE(std::equal(buf.begin(), buf.end(), initial.begin()));

  (void)io.close();
}

TEST_F(MemIoTest_576, SeekToEndThenRead_ReturnsZeroAndOrSetsEof_576) {
  MemIo io;
  ASSERT_NO_THROW((void)io.open());

  const auto payload = MakeBytes("abc");
  ASSERT_EQ(io.write(payload.data(), payload.size()), payload.size());

  // Seek to end, then read one byte: should return 0 bytes read.
  (void)io.seek(0, EndPos());
  byte b = 0;
  const size_t readCount = io.read(&b, 1);
  EXPECT_EQ(readCount, 0u);

  // eof() should be observable; we don't assume it must be true in all implementations,
  // but it should be callable without throwing/crashing.
  EXPECT_NO_THROW((void)io.eof());

  (void)io.close();
}

TEST_F(MemIoTest_576, TransferFromAnotherMemIo_CopiesReadableContent_576) {
  MemIo src;
  MemIo dst;

  ASSERT_NO_THROW((void)src.open());
  ASSERT_NO_THROW((void)dst.open());

  const auto payload = MakeBytes("transfer payload");
  ASSERT_EQ(src.write(payload.data(), payload.size()), payload.size());

  // Reset source read position and transfer into destination.
  (void)src.seek(0, BegPos());
  EXPECT_NO_THROW(dst.transfer(src));

  // Destination should now have readable bytes matching payload.
  (void)dst.seek(0, BegPos());
  std::vector<byte> buf(payload.size(), 0);
  const size_t readCount = dst.read(buf.data(), buf.size());
  EXPECT_EQ(readCount, payload.size());
  EXPECT_TRUE(std::equal(buf.begin(), buf.end(), payload.begin()));

  (void)src.close();
  (void)dst.close();
}

TEST_F(MemIoTest_576, MmapProvidesDirectAccessWhenAvailable_576) {
  MemIo io;
  ASSERT_NO_THROW((void)io.open());

  const auto payload = MakeBytes("mmap!");
  ASSERT_EQ(io.write(payload.data(), payload.size()), payload.size());

  // mmap() may return nullptr depending on platform/implementation; do not assume.
  byte* p = nullptr;
  EXPECT_NO_THROW(p = io.mmap(/*unnamed*/ true));

  if (p != nullptr) {
    // If mapping is provided, first bytes should reflect written content.
    for (size_t i = 0; i < payload.size(); ++i) {
      EXPECT_EQ(p[i], payload[i]);
    }
  }

  // munmap() should be callable regardless of mapping availability.
  EXPECT_NO_THROW((void)io.munmap());

  (void)io.close();
}

TEST_F(MemIoTest_576, CloseIsIdempotentOrAtLeastSafeToCallTwice_576) {
  MemIo io;
  ASSERT_NO_THROW((void)io.open());

  EXPECT_NO_THROW((void)io.close());
  // Some implementations may return an error code on second close; we only require safety.
  EXPECT_NO_THROW((void)io.close());
  EXPECT_FALSE(io.isopen());
}

TEST_F(MemIoTest_576, ReadWithZeroCount_ReturnsZero_576) {
  MemIo io;
  ASSERT_NO_THROW((void)io.open());

  byte b = 0xFF;
  const size_t readCount = io.read(&b, 0);
  EXPECT_EQ(readCount, 0u);

  (void)io.close();
}

TEST_F(MemIoTest_576, WriteWithZeroCount_ReturnsZero_576) {
  MemIo io;
  ASSERT_NO_THROW((void)io.open());

  const byte dummy = 0x11;
  const size_t written = io.write(&dummy, 0);
  EXPECT_EQ(written, 0u);

  (void)io.close();
}

TEST_F(MemIoTest_576, TellAndSize_AreConsistentAfterWritesAndSeeks_576) {
  MemIo io;
  ASSERT_NO_THROW((void)io.open());

  EXPECT_NO_THROW((void)io.tell());
  EXPECT_NO_THROW((void)io.size());

  const auto payload = MakeBytes("12345");
  ASSERT_EQ(io.write(payload.data(), payload.size()), payload.size());

  const size_t sz = io.size();
  EXPECT_GE(sz, payload.size());

  (void)io.seek(0, BegPos());
  EXPECT_EQ(io.tell(), 0u);

  (void)io.seek(0, EndPos());
  EXPECT_EQ(io.tell(), io.size());

  (void)io.close();
}

}  // namespace