// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1184
//
// Unit tests for Exiv2::Internal::OffsetWriter::writeOffsets(BasicIo&)
//
// Constraints respected:
// - Treat implementation as a black box
// - Verify only observable behavior via BasicIo interactions (seek/write)

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <vector>

#include "exiv2/types.hpp"
#include "exiv2/basicio.hpp"
#include "tiffimage_int.hpp"

namespace {

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
};

// Helper to create OffsetId without relying on specific enumerators.
static inline Exiv2::Internal::OffsetId MakeOffsetId(int v) {
  return static_cast<Exiv2::Internal::OffsetId>(v);
}

TEST(OffsetWriterTest_1184, NoOffsetsDoesNotInteractWithIo_1184) {
  Exiv2::Internal::OffsetWriter w;
  MockBasicIo io;

  EXPECT_CALL(io, seek(_, _)).Times(0);
  EXPECT_CALL(io, write(_, _)).Times(0);

  w.writeOffsets(io);
}

TEST(OffsetWriterTest_1184, SingleOffsetSeeksToOriginBegAndWritesFourBytes_1184) {
  Exiv2::Internal::OffsetWriter w;
  MockBasicIo io;

  const auto id = MakeOffsetId(0);
  const uint32_t origin = 0u;
  const uint32_t target = 0u;

  w.setOrigin(id, origin, Exiv2::littleEndian);
  w.setTarget(id, target);

  std::vector<int64_t> seenSeeks;
  std::vector<size_t> seenWriteCounts;
  std::vector<std::array<Exiv2::byte, 4>> seenWriteBytes;

  EXPECT_CALL(io, seek(_, Exiv2::BasicIo::beg))
      .Times(1)
      .WillOnce(Invoke([&](int64_t off, Exiv2::BasicIo::Position) {
        seenSeeks.push_back(off);
        return 0;
      }));

  EXPECT_CALL(io, write(_, 4))
      .Times(1)
      .WillOnce(Invoke([&](const Exiv2::byte* data, size_t wcount) -> size_t {
        seenWriteCounts.push_back(wcount);
        std::array<Exiv2::byte, 4> b{{0, 0, 0, 0}};
        if (data != nullptr && wcount >= 4) {
          b[0] = data[0];
          b[1] = data[1];
          b[2] = data[2];
          b[3] = data[3];
        }
        seenWriteBytes.push_back(b);
        return wcount;
      }));

  w.writeOffsets(io);

  ASSERT_EQ(seenSeeks.size(), 1u);
  EXPECT_EQ(seenSeeks[0], static_cast<int64_t>(origin));

  ASSERT_EQ(seenWriteCounts.size(), 1u);
  EXPECT_EQ(seenWriteCounts[0], 4u);

  ASSERT_EQ(seenWriteBytes.size(), 1u);
  // Target was 0, so a robust boundary-friendly expectation is "all bytes are 0".
  EXPECT_EQ(seenWriteBytes[0], (std::array<Exiv2::byte, 4>{{0, 0, 0, 0}}));
}

TEST(OffsetWriterTest_1184, MultipleOffsetsCauseMatchingSeekAndWriteCounts_1184) {
  Exiv2::Internal::OffsetWriter w;
  MockBasicIo io;

  const auto id0 = MakeOffsetId(0);
  const auto id1 = MakeOffsetId(1);

  const uint32_t origin0 = 10u;
  const uint32_t origin1 = 200u;
  const uint32_t target0 = 0u;
  const uint32_t target1 = 0xFFFFFFFFu;

  w.setOrigin(id0, origin0, Exiv2::littleEndian);
  w.setTarget(id0, target0);

  w.setOrigin(id1, origin1, Exiv2::bigEndian);
  w.setTarget(id1, target1);

  std::vector<int64_t> seenSeeks;
  size_t writeCalls = 0;

  EXPECT_CALL(io, seek(_, Exiv2::BasicIo::beg))
      .Times(2)
      .WillRepeatedly(Invoke([&](int64_t off, Exiv2::BasicIo::Position) {
        seenSeeks.push_back(off);
        return 0;
      }));

  EXPECT_CALL(io, write(_, 4))
      .Times(2)
      .WillRepeatedly(Invoke([&](const Exiv2::byte*, size_t wcount) -> size_t {
        ++writeCalls;
        return wcount;
      }));

  w.writeOffsets(io);

  ASSERT_EQ(seenSeeks.size(), 2u);
  // Order is not part of the public contract; verify set membership.
  EXPECT_THAT(seenSeeks,
              ::testing::UnorderedElementsAre(static_cast<int64_t>(origin0),
                                             static_cast<int64_t>(origin1)));
  EXPECT_EQ(writeCalls, 2u);
}

TEST(OffsetWriterTest_1184, BoundaryOriginsAndTargetsStillAttemptIoWrites_1184) {
  Exiv2::Internal::OffsetWriter w;
  MockBasicIo io;

  const auto id = MakeOffsetId(42);

  const uint32_t origin = 0xFFFFFFFFu;  // boundary origin
  const uint32_t target = 0xFFFFFFFFu;  // boundary target

  w.setOrigin(id, origin, Exiv2::littleEndian);
  w.setTarget(id, target);

  EXPECT_CALL(io, seek(static_cast<int64_t>(origin), Exiv2::BasicIo::beg))
      .Times(1)
      .WillOnce(Return(0));

  EXPECT_CALL(io, write(_, 4)).Times(1).WillOnce(Return(4));

  w.writeOffsets(io);
}

}  // namespace