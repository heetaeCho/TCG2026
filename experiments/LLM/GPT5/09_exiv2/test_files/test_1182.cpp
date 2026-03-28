// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// TEST_ID 1182
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

#include "tiffimage_int.hpp"
#include "basicio.hpp"
#include "types.hpp"

namespace {

using Exiv2::Internal::OffsetWriter;

// Helper: snapshot MemIo bytes (observable public API via mmap/size).
static std::vector<Exiv2::byte> snapshotMemIo(const Exiv2::MemIo& io) {
    const long sz = io.size();
    if (sz <= 0) return {};
    const Exiv2::byte* p = io.mmap();
    return std::vector<Exiv2::byte>(p, p + sz);
}

// Helper: count differing bytes between two buffers (same size).
static size_t countDiff(const std::vector<Exiv2::byte>& a, const std::vector<Exiv2::byte>& b) {
    if (a.size() != b.size()) return std::max(a.size(), b.size());
    size_t diff = 0;
    for (size_t i = 0; i < a.size(); ++i) diff += (a[i] != b[i]) ? 1u : 0u;
    return diff;
}

class OffsetWriterTest_1182 : public ::testing::Test {};

}  // namespace

TEST_F(OffsetWriterTest_1182, SetOriginDoesNotThrow_1182) {
    OffsetWriter w;

    // Use a default-constructed id. This keeps the test interface-driven and avoids
    // guessing enumerators.
    Exiv2::Internal::OffsetId id{};

    EXPECT_NO_THROW(w.setOrigin(id, 0u, Exiv2::littleEndian));
    EXPECT_NO_THROW(w.setOrigin(id, 1234u, Exiv2::bigEndian));
}

TEST_F(OffsetWriterTest_1182, SetTargetDoesNotThrow_1182) {
    OffsetWriter w;
    Exiv2::Internal::OffsetId id{};

    // Even if origin wasn't set first, setTarget is part of the public interface.
    EXPECT_NO_THROW(w.setTarget(id, 0u));
    EXPECT_NO_THROW(w.setTarget(id, 0xFFFFFFFFu));
}

TEST_F(OffsetWriterTest_1182, WriteOffsetsWithEmptyWriterDoesNotThrowAndDoesNotChangeIo_1182) {
    OffsetWriter w;
    Exiv2::MemIo io;

    // Prepare some content so changes are observable.
    std::vector<Exiv2::byte> initial(16, static_cast<Exiv2::byte>(0xAA));
    ASSERT_EQ(static_cast<long>(initial.size()),
              io.write(initial.data(), static_cast<long>(initial.size())));

    const auto before = snapshotMemIo(io);
    ASSERT_EQ(before.size(), initial.size());

    EXPECT_NO_THROW(w.writeOffsets(io));

    const auto after = snapshotMemIo(io);
    EXPECT_EQ(after.size(), before.size());
    EXPECT_EQ(after, before);
}

TEST_F(OffsetWriterTest_1182, WriteOffsetsModifiesSomeBytesWhenConfigured_1182) {
    OffsetWriter w;
    Exiv2::Internal::OffsetId id{};

    Exiv2::MemIo io;
    std::vector<Exiv2::byte> initial(32, static_cast<Exiv2::byte>(0x11));
    ASSERT_EQ(static_cast<long>(initial.size()),
              io.write(initial.data(), static_cast<long>(initial.size())));

    const auto before = snapshotMemIo(io);

    // Configure an origin well within the buffer, set a non-trivial target, then write.
    ASSERT_NO_THROW(w.setOrigin(id, 8u, Exiv2::littleEndian));
    ASSERT_NO_THROW(w.setTarget(id, 0x11223344u));
    EXPECT_NO_THROW(w.writeOffsets(io));

    const auto after = snapshotMemIo(io);
    ASSERT_EQ(after.size(), before.size());

    // Black-box assertion: writing offsets should have an observable effect on the IO buffer
    // in typical usage (without asserting exact encoding).
    EXPECT_GT(countDiff(before, after), 0u);
}

TEST_F(OffsetWriterTest_1182, WriteOffsetsSupportsMultipleIds_1182) {
    OffsetWriter w;

    Exiv2::Internal::OffsetId id1{};
    Exiv2::Internal::OffsetId id2{};
    // Keep ids distinct without relying on enumerators by using different objects.
    // (If OffsetId is an enum, default init yields same value; this still stays within
    // interface constraints and the test remains valid as a robustness check.)

    Exiv2::MemIo io;
    std::vector<Exiv2::byte> initial(64, static_cast<Exiv2::byte>(0x5A));
    ASSERT_EQ(static_cast<long>(initial.size()),
              io.write(initial.data(), static_cast<long>(initial.size())));

    const auto before = snapshotMemIo(io);

    ASSERT_NO_THROW(w.setOrigin(id1, 4u, Exiv2::littleEndian));
    ASSERT_NO_THROW(w.setTarget(id1, 0xA1B2C3D4u));

    ASSERT_NO_THROW(w.setOrigin(id2, 40u, Exiv2::bigEndian));
    ASSERT_NO_THROW(w.setTarget(id2, 0x01020304u));

    EXPECT_NO_THROW(w.writeOffsets(io));

    const auto after = snapshotMemIo(io);
    ASSERT_EQ(after.size(), before.size());
    EXPECT_GT(countDiff(before, after), 0u);
}

TEST_F(OffsetWriterTest_1182, WriteOffsetsAtBufferBoundaryDoesNotGrowIo_1182) {
    OffsetWriter w;
    Exiv2::Internal::OffsetId id{};

    Exiv2::MemIo io;
    std::vector<Exiv2::byte> initial(16, static_cast<Exiv2::byte>(0x00));
    ASSERT_EQ(static_cast<long>(initial.size()),
              io.write(initial.data(), static_cast<long>(initial.size())));

    const auto before = snapshotMemIo(io);
    const long beforeSize = io.size();

    // Place origin at the last byte position (boundary). We only require it doesn't throw
    // and doesn't unexpectedly grow the IO in this scenario.
    ASSERT_NO_THROW(w.setOrigin(id, 15u, Exiv2::littleEndian));
    ASSERT_NO_THROW(w.setTarget(id, 0xDEADBEEFu));
    EXPECT_NO_THROW(w.writeOffsets(io));

    EXPECT_EQ(io.size(), beforeSize);

    // Buffer may or may not change depending on implementation details (e.g., whether it writes
    // a fixed-width value and how it handles boundary). We avoid asserting exact changes.
    const auto after = snapshotMemIo(io);
    ASSERT_EQ(after.size(), before.size());
}

TEST_F(OffsetWriterTest_1182, ByteOrderCanAffectObservableOutput_1182) {
    // This test avoids asserting exact byte patterns; it only checks that, for a value with
    // non-symmetric bytes, using different byte orders can lead to a different buffer state.
    Exiv2::Internal::OffsetId id{};

    // little endian run
    OffsetWriter wLE;
    Exiv2::MemIo ioLE;
    std::vector<Exiv2::byte> initialLE(24, static_cast<Exiv2::byte>(0xFF));
    ASSERT_EQ(static_cast<long>(initialLE.size()),
              ioLE.write(initialLE.data(), static_cast<long>(initialLE.size())));
    ASSERT_NO_THROW(wLE.setOrigin(id, 8u, Exiv2::littleEndian));
    ASSERT_NO_THROW(wLE.setTarget(id, 0x01020304u));
    EXPECT_NO_THROW(wLE.writeOffsets(ioLE));
    const auto afterLE = snapshotMemIo(ioLE);

    // big endian run
    OffsetWriter wBE;
    Exiv2::MemIo ioBE;
    std::vector<Exiv2::byte> initialBE(24, static_cast<Exiv2::byte>(0xFF));
    ASSERT_EQ(static_cast<long>(initialBE.size()),
              ioBE.write(initialBE.data(), static_cast<long>(initialBE.size())));
    ASSERT_NO_THROW(wBE.setOrigin(id, 8u, Exiv2::bigEndian));
    ASSERT_NO_THROW(wBE.setTarget(id, 0x01020304u));
    EXPECT_NO_THROW(wBE.writeOffsets(ioBE));
    const auto afterBE = snapshotMemIo(ioBE);

    ASSERT_EQ(afterLE.size(), afterBE.size());

    // If byte order is used by the implementation, the resulting buffers are expected
    // to differ for this target value. If they don't, the implementation may normalize,
    // defer, or ignore byte order for this operation; in that case this expectation can be
    // relaxed by the maintainer.
    EXPECT_NE(afterLE, afterBE);
}