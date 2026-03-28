// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_asfvideo_headerreader_1044.cpp

#include <gtest/gtest.h>

#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>

#include <cstdint>
#include <memory>

namespace {

class AsfVideoHeaderReaderTest_1044 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr makeEmptyMemIo() {
    // Use an in-memory IO object with no data. The HeaderReader implementation is treated as a black box,
    // so tests must not assume how it parses/consumes input.
    return std::make_unique<Exiv2::MemIo>();
  }
};

TEST_F(AsfVideoHeaderReaderTest_1044, ConstructWithEmptyIo_DoesNotThrow_1044) {
  auto io = makeEmptyMemIo();
  EXPECT_NO_THROW({
    Exiv2::AsfVideo::HeaderReader reader(io);
    (void)reader;
  });
}

TEST_F(AsfVideoHeaderReaderTest_1044, GetSize_IsStableAcrossCalls_1044) {
  auto io = makeEmptyMemIo();
  Exiv2::AsfVideo::HeaderReader reader(io);

  const uint64_t s1 = reader.getSize();
  const uint64_t s2 = reader.getSize();

  EXPECT_EQ(s1, s2);
}

TEST_F(AsfVideoHeaderReaderTest_1044, GetRemainingSize_IsStableAcrossCalls_1044) {
  auto io = makeEmptyMemIo();
  Exiv2::AsfVideo::HeaderReader reader(io);

  const uint64_t r1 = reader.getRemainingSize();
  const uint64_t r2 = reader.getRemainingSize();

  EXPECT_EQ(r1, r2);
}

TEST_F(AsfVideoHeaderReaderTest_1044, GetId_ReturnsSameBufferReference_1044) {
  auto io = makeEmptyMemIo();
  Exiv2::AsfVideo::HeaderReader reader(io);

  Exiv2::DataBuf& id1 = reader.getId();
  Exiv2::DataBuf& id2 = reader.getId();

  // Observable behavior: repeated calls return a reference; it should refer to the same object.
  EXPECT_EQ(&id1, &id2);
}

TEST_F(AsfVideoHeaderReaderTest_1044, ConstGetters_AreCallableAndStable_1044) {
  auto io = makeEmptyMemIo();
  Exiv2::AsfVideo::HeaderReader reader(io);
  const Exiv2::AsfVideo::HeaderReader& cref = reader;

  const uint64_t s1 = cref.getSize();
  const uint64_t s2 = cref.getSize();
  EXPECT_EQ(s1, s2);

  const uint64_t r1 = cref.getRemainingSize();
  const uint64_t r2 = cref.getRemainingSize();
  EXPECT_EQ(r1, r2);
}

}  // namespace