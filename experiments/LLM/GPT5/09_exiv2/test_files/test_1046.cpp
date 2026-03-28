// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1046
//
// Unit tests for Exiv2::AsfVideo::HeaderReader (exiv2/asfvideo.hpp)
//
// Constraints respected:
// - Treat implementation as black box: only public interface is used.
// - No access to private state.
// - No re-implementation / inference of internal parsing logic.
// - Focus on observable behavior: construction, return types, idempotence, reference stability.

#include <gtest/gtest.h>

#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>

#include <cstdint>
#include <memory>

namespace {

class AsfVideoHeaderReaderTest_1046 : public ::testing::Test {
 protected:
  // Minimal in-memory IO to satisfy constructor requirements.
  // We intentionally do not assume any ASF structure; tests only verify safe usage and
  // stable observable behavior (e.g., reference stability, idempotence).
  static Exiv2::BasicIo::UniquePtr makeMemIoWithBytes(const Exiv2::byte* data, size_t size) {
    return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(data, static_cast<long>(size)));
  }
};

TEST_F(AsfVideoHeaderReaderTest_1046, ConstructWithMemIoDoesNotThrow_1046) {
  const Exiv2::byte bytes[] = {0x00};
  Exiv2::BasicIo::UniquePtr io = makeMemIoWithBytes(bytes, sizeof(bytes));

  EXPECT_NO_THROW({
    Exiv2::AsfVideo::HeaderReader reader(io);
    (void)reader;
  });
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetIdReturnsStableReference_1046) {
  const Exiv2::byte bytes[] = {0x00, 0x01, 0x02, 0x03};
  Exiv2::BasicIo::UniquePtr io = makeMemIoWithBytes(bytes, sizeof(bytes));

  Exiv2::AsfVideo::HeaderReader reader(io);

  Exiv2::DataBuf& id1 = reader.getId();
  Exiv2::DataBuf& id2 = reader.getId();

  // Observable behavior: getId() returns a reference to an internal DataBuf.
  // The reference should be stable across repeated calls.
  EXPECT_EQ(&id1, &id2);
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetSizeIsIdempotent_1046) {
  const Exiv2::byte bytes[] = {0x10, 0x20, 0x30};
  Exiv2::BasicIo::UniquePtr io = makeMemIoWithBytes(bytes, sizeof(bytes));

  Exiv2::AsfVideo::HeaderReader reader(io);

  const uint64_t s1 = reader.getSize();
  const uint64_t s2 = reader.getSize();

  // Observable contract expectation: const getter should not mutate observable state.
  EXPECT_EQ(s1, s2);
}

TEST_F(AsfVideoHeaderReaderTest_1046, GetRemainingSizeIsIdempotent_1046) {
  const Exiv2::byte bytes[] = {0xAA, 0xBB, 0xCC, 0xDD};
  Exiv2::BasicIo::UniquePtr io = makeMemIoWithBytes(bytes, sizeof(bytes));

  Exiv2::AsfVideo::HeaderReader reader(io);

  const uint64_t r1 = reader.getRemainingSize();
  const uint64_t r2 = reader.getRemainingSize();

  // Observable contract expectation: const getter should not mutate observable state.
  EXPECT_EQ(r1, r2);
}

TEST_F(AsfVideoHeaderReaderTest_1046, CallingGettersInSequenceDoesNotThrow_1046) {
  const Exiv2::byte bytes[] = {0x00};
  Exiv2::BasicIo::UniquePtr io = makeMemIoWithBytes(bytes, sizeof(bytes));

  Exiv2::AsfVideo::HeaderReader reader(io);

  EXPECT_NO_THROW({
    (void)reader.getId();
    (void)reader.getSize();
    (void)reader.getRemainingSize();
    (void)reader.getId();            // repeat to ensure stability under multiple calls
    (void)reader.getRemainingSize(); // repeat
    (void)reader.getSize();          // repeat
  });
}

}  // namespace