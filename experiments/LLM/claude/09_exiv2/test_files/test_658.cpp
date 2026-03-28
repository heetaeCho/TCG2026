#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/quicktimevideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <cstring>
#include <sstream>

// We'll use MemIo for creating in-memory IO objects with controlled data
#include <exiv2/basicio.hpp>

namespace {

// Helper to create a big-endian uint32 in a byte buffer
void writeUint32BE(uint8_t* buf, uint32_t val) {
    buf[0] = static_cast<uint8_t>((val >> 24) & 0xFF);
    buf[1] = static_cast<uint8_t>((val >> 16) & 0xFF);
    buf[2] = static_cast<uint8_t>((val >> 8) & 0xFF);
    buf[3] = static_cast<uint8_t>(val & 0xFF);
}

// Helper to create a big-endian uint64 in a byte buffer
void writeUint64BE(uint8_t* buf, uint64_t val) {
    for (int i = 7; i >= 0; --i) {
        buf[7 - i] = static_cast<uint8_t>((val >> (i * 8)) & 0xFF);
    }
}

// Helper to build a simple QuickTime atom/box
// Returns a vector of bytes representing: [size (4 bytes)] [type (4 bytes)] [payload]
std::vector<uint8_t> makeAtom(const std::string& type, const std::vector<uint8_t>& payload) {
    uint32_t totalSize = static_cast<uint32_t>(8 + payload.size());
    std::vector<uint8_t> atom(totalSize);
    writeUint32BE(atom.data(), totalSize);
    std::memcpy(atom.data() + 4, type.c_str(), 4);
    if (!payload.empty()) {
        std::memcpy(atom.data() + 8, payload.data(), payload.size());
    }
    return atom;
}

// Helper to build an extended size atom (size field = 1, followed by 8-byte real size)
std::vector<uint8_t> makeExtendedAtom(const std::string& type, const std::vector<uint8_t>& payload) {
    uint64_t totalSize = 16 + payload.size();
    std::vector<uint8_t> atom(static_cast<size_t>(totalSize));
    // size field = 1 (indicates extended size)
    writeUint32BE(atom.data(), 1);
    std::memcpy(atom.data() + 4, type.c_str(), 4);
    writeUint64BE(atom.data() + 8, totalSize);
    if (!payload.empty()) {
        std::memcpy(atom.data() + 16, payload.data(), payload.size());
    }
    return atom;
}

class QuickTimeVideoTest_658 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::QuickTimeVideo> createFromData(const std::vector<uint8_t>& data, size_t max_depth = 100) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), max_depth);
    }

    std::unique_ptr<Exiv2::QuickTimeVideo> createFromData(const uint8_t* data, size_t size, size_t max_depth = 100) {
        auto io = std::make_unique<Exiv2::MemIo>(data, size);
        return std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), max_depth);
    }
};

// Test: Constructor creates a valid object
TEST_F(QuickTimeVideoTest_658, ConstructorCreatesValidObject_658) {
    std::vector<uint8_t> emptyData;
    auto io = std::make_unique<Exiv2::MemIo>();
    auto qtv = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 100);
    ASSERT_NE(qtv, nullptr);
}

// Test: mimeType returns expected MIME type for QuickTime
TEST_F(QuickTimeVideoTest_658, MimeTypeReturnsCorrectValue_658) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    std::string mime = qtv.mimeType();
    EXPECT_EQ(mime, "video/quicktime");
}

// Test: writeMetadata throws (QuickTime writing typically not supported)
TEST_F(QuickTimeVideoTest_658, WriteMetadataThrows_658) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_THROW(qtv.writeMetadata(), Exiv2::Error);
}

// Test: readMetadata on empty data doesn't crash
TEST_F(QuickTimeVideoTest_658, ReadMetadataOnEmptyData_658) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    // Empty IO - readMetadata should handle gracefully (EOF immediately)
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: readMetadata on data too small to form valid atom
TEST_F(QuickTimeVideoTest_658, ReadMetadataOnTruncatedData_658) {
    // Only 3 bytes - not enough for the first 4-byte read of size
    std::vector<uint8_t> data = {0x00, 0x01, 0x02};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    // Should handle gracefully (read returns fewer bytes, treated as EOF)
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: readMetadata with a minimal valid ftyp atom
TEST_F(QuickTimeVideoTest_658, ReadMetadataWithFtypAtom_658) {
    // Create a minimal 'ftyp' atom
    std::vector<uint8_t> payload = {'q', 't', ' ', ' ', 0, 0, 0, 0};
    auto atom = makeAtom("ftyp", payload);
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: readMetadata with size=0 and not "meta" context should fail with enforce
TEST_F(QuickTimeVideoTest_658, ReadMetadataWithZeroSizeNonMeta_658) {
    // size = 0, type = "moov" - should trigger enforce(size >= hdrsize) failure
    // since size=0 and hdrsize=8
    std::vector<uint8_t> data(8, 0);
    data[4] = 'm'; data[5] = 'o'; data[6] = 'o'; data[7] = 'v';
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_THROW(qtv.readMetadata(), Exiv2::Error);
}

// Test: readMetadata with size that exceeds available data should fail
TEST_F(QuickTimeVideoTest_658, ReadMetadataWithSizeExceedingData_658) {
    // Create an atom header claiming size=1000 but only providing 8 bytes total
    std::vector<uint8_t> data(8);
    writeUint32BE(data.data(), 1000);
    data[4] = 'm'; data[5] = 'o'; data[6] = 'o'; data[7] = 'v';
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_THROW(qtv.readMetadata(), Exiv2::Error);
}

// Test: Max recursion depth of 0 should cause immediate failure on decodeBlock
TEST_F(QuickTimeVideoTest_658, MaxRecursionDepthZero_658) {
    // Create a valid-looking atom
    std::vector<uint8_t> payload(8, 0);
    auto atom = makeAtom("moov", payload);
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    // max_recursion_depth = 0 means decodeBlock(0, ...) should fail enforce
    Exiv2::QuickTimeVideo qtv(std::move(io), 0);
    EXPECT_THROW(qtv.readMetadata(), Exiv2::Error);
}

// Test: Max recursion depth of 1 allows at least one level
TEST_F(QuickTimeVideoTest_658, MaxRecursionDepthOne_658) {
    // Create a simple ftyp atom that doesn't recurse further
    std::vector<uint8_t> payload = {'q', 't', ' ', ' '};
    auto atom = makeAtom("ftyp", payload);
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 1);
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: Extended size atom (size field == 1) with valid extended size
TEST_F(QuickTimeVideoTest_658, ExtendedSizeAtom_658) {
    std::vector<uint8_t> payload = {'q', 't', ' ', ' '};
    auto atom = makeExtendedAtom("ftyp", payload);
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: Atom with size exactly equal to header size (no payload)
TEST_F(QuickTimeVideoTest_658, AtomWithNoPayload_658) {
    // size = 8, type = "free" (which should be in ignore list typically)
    std::vector<uint8_t> atom = makeAtom("free", {});
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: Multiple atoms in sequence
TEST_F(QuickTimeVideoTest_658, MultipleAtomsInSequence_658) {
    std::vector<uint8_t> payload1 = {'q', 't', ' ', ' '};
    auto atom1 = makeAtom("ftyp", payload1);

    std::vector<uint8_t> payload2(16, 0);
    auto atom2 = makeAtom("free", payload2);

    // Concatenate atoms
    std::vector<uint8_t> data;
    data.insert(data.end(), atom1.begin(), atom1.end());
    data.insert(data.end(), atom2.begin(), atom2.end());

    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: Size less than header size (size < 8) should throw
TEST_F(QuickTimeVideoTest_658, SizeLessThanHeaderSize_658) {
    // size = 4, type = "moov" -> enforce(size >= hdrsize) should fail (4 < 8)
    std::vector<uint8_t> data(8);
    writeUint32BE(data.data(), 4);
    data[4] = 'm'; data[5] = 'o'; data[6] = 'o'; data[7] = 'v';
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_THROW(qtv.readMetadata(), Exiv2::Error);
}

// Test: Size = 7 (less than 8) should throw
TEST_F(QuickTimeVideoTest_658, SizeSevenShouldThrow_658) {
    std::vector<uint8_t> data(8);
    writeUint32BE(data.data(), 7);
    data[4] = 'f'; data[5] = 'r'; data[6] = 'e'; data[7] = 'e';
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_THROW(qtv.readMetadata(), Exiv2::Error);
}

// Test: Extended size atom where extended size is less than 16 should throw
TEST_F(QuickTimeVideoTest_658, ExtendedSizeTooSmallShouldThrow_658) {
    // size=1 signals extended, but extended size = 10 which is < 16 (hdrsize)
    std::vector<uint8_t> data(16);
    writeUint32BE(data.data(), 1);
    data[4] = 'm'; data[5] = 'o'; data[6] = 'o'; data[7] = 'v';
    writeUint64BE(data.data() + 8, 10); // extended size too small
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_THROW(qtv.readMetadata(), Exiv2::Error);
}

// Test: Valid moov atom with some inner content
TEST_F(QuickTimeVideoTest_658, MoovAtomWithContent_658) {
    // Create a moov atom containing a mvhd-like inner atom
    // Inner atom: size=8 type="free" (no payload, ignored)
    auto innerAtom = makeAtom("free", {});
    auto moovAtom = makeAtom("moov", innerAtom);

    auto io = std::make_unique<Exiv2::MemIo>(moovAtom.data(), moovAtom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: Only 4 bytes available (can read size but EOF on type read)
TEST_F(QuickTimeVideoTest_658, OnlyFourBytesAvailable_658) {
    // 4 bytes for size, then io->readOrThrow for type will fail
    std::vector<uint8_t> data = {0x00, 0x00, 0x00, 0x10};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_THROW(qtv.readMetadata(), Exiv2::Error);
}

// Test: Exactly 8 bytes forming a "free" atom of size 8 (no payload)
TEST_F(QuickTimeVideoTest_658, ExactlyEightBytesAtom_658) {
    auto atom = makeAtom("free", {});
    ASSERT_EQ(atom.size(), 8u);
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: Extended size = 1 triggers extended read, need enough data for 8-byte extended size
TEST_F(QuickTimeVideoTest_658, ExtendedSizeAtomTruncatedExtendedField_658) {
    // size=1 (extended), type="moov", but not enough bytes for the 8-byte extended size
    std::vector<uint8_t> data(12);
    writeUint32BE(data.data(), 1);
    data[4] = 'm'; data[5] = 'o'; data[6] = 'o'; data[7] = 'v';
    // Only 4 bytes for extended size instead of 8
    writeUint32BE(data.data() + 8, 0);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_THROW(qtv.readMetadata(), Exiv2::Error);
}

// Test: Large max recursion depth works fine
TEST_F(QuickTimeVideoTest_658, LargeMaxRecursionDepth_658) {
    auto atom = makeAtom("ftyp", {'q', 't', ' ', ' '});
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 10000);
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test: Verify exifData and xmpData are accessible after readMetadata on minimal file
TEST_F(QuickTimeVideoTest_658, MetadataAccessibleAfterRead_658) {
    auto atom = makeAtom("ftyp", {'q', 't', ' ', ' '});
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    qtv.readMetadata();

    // Should be able to access metadata containers without crash
    EXPECT_NO_THROW(qtv.exifData());
    EXPECT_NO_THROW(qtv.xmpData());
}

// Test: good() returns true for valid IO
TEST_F(QuickTimeVideoTest_658, GoodReturnsTrueForValidIo_658) {
    auto atom = makeAtom("ftyp", {'q', 't', ' ', ' '});
    auto io = std::make_unique<Exiv2::MemIo>(atom.data(), atom.size());
    Exiv2::QuickTimeVideo qtv(std::move(io), 100);
    EXPECT_TRUE(qtv.good());
}

}  // namespace
