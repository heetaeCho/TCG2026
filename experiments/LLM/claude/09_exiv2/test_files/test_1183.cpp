#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffimage_int.hpp"
#include "basicio.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for OffsetWriter tests
class OffsetWriterTest_1183 : public ::testing::Test {
protected:
    OffsetWriter writer_;
};

// Test that setTarget on a non-existent ID does not crash
TEST_F(OffsetWriterTest_1183, SetTargetNonExistentId_1183) {
    // Setting target for an ID that hasn't been added via setOrigin should be a no-op
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(0), 100));
}

// Test that setOrigin followed by setTarget works without crash
TEST_F(OffsetWriterTest_1183, SetOriginThenSetTarget_1183) {
    writer_.setOrigin(OffsetId(0), 0, littleEndian);
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(0), 42));
}

// Test that setOrigin can be called with littleEndian byte order
TEST_F(OffsetWriterTest_1183, SetOriginLittleEndian_1183) {
    EXPECT_NO_THROW(writer_.setOrigin(OffsetId(0), 100, littleEndian));
}

// Test that setOrigin can be called with bigEndian byte order
TEST_F(OffsetWriterTest_1183, SetOriginBigEndian_1183) {
    EXPECT_NO_THROW(writer_.setOrigin(OffsetId(0), 200, bigEndian));
}

// Test that setTarget can update the target value after setOrigin
TEST_F(OffsetWriterTest_1183, SetTargetUpdatesExistingEntry_1183) {
    writer_.setOrigin(OffsetId(0), 10, littleEndian);
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(0), 500));
    // Update again
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(0), 1000));
}

// Test multiple different IDs can be set
TEST_F(OffsetWriterTest_1183, MultipleIds_1183) {
    writer_.setOrigin(OffsetId(0), 10, littleEndian);
    writer_.setOrigin(OffsetId(1), 20, bigEndian);
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(0), 100));
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(1), 200));
}

// Test that setTarget with zero target value works
TEST_F(OffsetWriterTest_1183, SetTargetZeroValue_1183) {
    writer_.setOrigin(OffsetId(0), 10, littleEndian);
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(0), 0));
}

// Test that setTarget with max uint32_t value works
TEST_F(OffsetWriterTest_1183, SetTargetMaxValue_1183) {
    writer_.setOrigin(OffsetId(0), 10, littleEndian);
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(0), 0xFFFFFFFF));
}

// Test that setOrigin with zero origin works
TEST_F(OffsetWriterTest_1183, SetOriginZeroOrigin_1183) {
    EXPECT_NO_THROW(writer_.setOrigin(OffsetId(0), 0, littleEndian));
}

// Test that setOrigin with max uint32_t origin works
TEST_F(OffsetWriterTest_1183, SetOriginMaxOrigin_1183) {
    EXPECT_NO_THROW(writer_.setOrigin(OffsetId(0), 0xFFFFFFFF, bigEndian));
}

// Test writeOffsets with an empty offset list does not crash
TEST_F(OffsetWriterTest_1183, WriteOffsetsEmptyList_1183) {
    Exiv2::MemIo io;
    EXPECT_NO_THROW(writer_.writeOffsets(io));
}

// Test writeOffsets after setting origin and target
TEST_F(OffsetWriterTest_1183, WriteOffsetsAfterSetOriginAndTarget_1183) {
    // Create a memory-backed IO with enough space
    Exiv2::MemIo io;
    // Write some dummy data first so there's space at the origin offset
    std::vector<byte> buffer(100, 0);
    io.write(buffer.data(), buffer.size());

    writer_.setOrigin(OffsetId(0), 10, littleEndian);
    writer_.setTarget(OffsetId(0), 42);

    EXPECT_NO_THROW(writer_.writeOffsets(io));
}

// Test writeOffsets with big endian byte order
TEST_F(OffsetWriterTest_1183, WriteOffsetsBigEndian_1183) {
    Exiv2::MemIo io;
    std::vector<byte> buffer(100, 0);
    io.write(buffer.data(), buffer.size());

    writer_.setOrigin(OffsetId(0), 10, bigEndian);
    writer_.setTarget(OffsetId(0), 42);

    EXPECT_NO_THROW(writer_.writeOffsets(io));
}

// Test that calling setOrigin twice for same ID overwrites the origin
TEST_F(OffsetWriterTest_1183, SetOriginTwiceSameId_1183) {
    writer_.setOrigin(OffsetId(0), 10, littleEndian);
    EXPECT_NO_THROW(writer_.setOrigin(OffsetId(0), 20, bigEndian));
    EXPECT_NO_THROW(writer_.setTarget(OffsetId(0), 50));
}

// Test writeOffsets verifies correct data written for little endian
TEST_F(OffsetWriterTest_1183, WriteOffsetsCorrectDataLittleEndian_1183) {
    Exiv2::MemIo io;
    std::vector<byte> buffer(100, 0);
    io.write(buffer.data(), buffer.size());

    uint32_t origin = 10;
    uint32_t target = 0x12345678;

    writer_.setOrigin(OffsetId(0), origin, littleEndian);
    writer_.setTarget(OffsetId(0), target);
    writer_.writeOffsets(io);

    // Read back the 4 bytes at offset 10
    io.seek(origin, BasicIo::beg);
    byte readBuf[4] = {};
    io.read(readBuf, 4);

    // Little endian: least significant byte first
    uint32_t readValue = static_cast<uint32_t>(readBuf[0]) |
                         (static_cast<uint32_t>(readBuf[1]) << 8) |
                         (static_cast<uint32_t>(readBuf[2]) << 16) |
                         (static_cast<uint32_t>(readBuf[3]) << 24);

    EXPECT_EQ(readValue, target);
}

// Test writeOffsets verifies correct data written for big endian
TEST_F(OffsetWriterTest_1183, WriteOffsetsCorrectDataBigEndian_1183) {
    Exiv2::MemIo io;
    std::vector<byte> buffer(100, 0);
    io.write(buffer.data(), buffer.size());

    uint32_t origin = 20;
    uint32_t target = 0xAABBCCDD;

    writer_.setOrigin(OffsetId(0), origin, bigEndian);
    writer_.setTarget(OffsetId(0), target);
    writer_.writeOffsets(io);

    // Read back the 4 bytes at offset 20
    io.seek(origin, BasicIo::beg);
    byte readBuf[4] = {};
    io.read(readBuf, 4);

    // Big endian: most significant byte first
    uint32_t readValue = (static_cast<uint32_t>(readBuf[0]) << 24) |
                         (static_cast<uint32_t>(readBuf[1]) << 16) |
                         (static_cast<uint32_t>(readBuf[2]) << 8) |
                         static_cast<uint32_t>(readBuf[3]);

    EXPECT_EQ(readValue, target);
}

// Test writing multiple offsets
TEST_F(OffsetWriterTest_1183, WriteMultipleOffsets_1183) {
    Exiv2::MemIo io;
    std::vector<byte> buffer(200, 0);
    io.write(buffer.data(), buffer.size());

    writer_.setOrigin(OffsetId(0), 10, littleEndian);
    writer_.setTarget(OffsetId(0), 100);
    writer_.setOrigin(OffsetId(1), 50, bigEndian);
    writer_.setTarget(OffsetId(1), 200);

    EXPECT_NO_THROW(writer_.writeOffsets(io));

    // Verify first offset (little endian at position 10)
    io.seek(10, BasicIo::beg);
    byte readBuf[4] = {};
    io.read(readBuf, 4);
    uint32_t val1 = static_cast<uint32_t>(readBuf[0]) |
                    (static_cast<uint32_t>(readBuf[1]) << 8) |
                    (static_cast<uint32_t>(readBuf[2]) << 16) |
                    (static_cast<uint32_t>(readBuf[3]) << 24);
    EXPECT_EQ(val1, 100u);

    // Verify second offset (big endian at position 50)
    io.seek(50, BasicIo::beg);
    io.read(readBuf, 4);
    uint32_t val2 = (static_cast<uint32_t>(readBuf[0]) << 24) |
                    (static_cast<uint32_t>(readBuf[1]) << 16) |
                    (static_cast<uint32_t>(readBuf[2]) << 8) |
                    static_cast<uint32_t>(readBuf[3]);
    EXPECT_EQ(val2, 200u);
}
