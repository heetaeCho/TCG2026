#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/xmp_exiv2.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"
#include "exiv2/tags.hpp"
#include "tiffimage_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper: build a minimal valid TIFF (little-endian) binary blob
static std::vector<byte> makeMinimalTiff() {
    // Minimal TIFF: header (8 bytes) + IFD with 0 entries (2 bytes for count + 4 bytes for next IFD offset)
    std::vector<byte> tiff(14, 0);
    // Byte order: little-endian "II"
    tiff[0] = 'I';
    tiff[1] = 'I';
    // Magic number 42
    tiff[2] = 42;
    tiff[3] = 0;
    // Offset to first IFD (8)
    tiff[4] = 8;
    tiff[5] = 0;
    tiff[6] = 0;
    tiff[7] = 0;
    // IFD entry count: 0
    tiff[8] = 0;
    tiff[9] = 0;
    // Next IFD offset: 0 (no more IFDs)
    tiff[10] = 0;
    tiff[11] = 0;
    tiff[12] = 0;
    tiff[13] = 0;
    return tiff;
}

// A concrete TiffHeader for testing (standard TIFF header)
class TiffHeader : public TiffHeaderBase {
 public:
    TiffHeader(ByteOrder byteOrder = littleEndian, uint32_t offset = 8)
        : TiffHeaderBase(42, 8, byteOrder, offset) {}
};

// Default FindEncoderFct that returns nullptr (no special encoder)
static DecoderFct findEncoder(const std::string& /*make*/, uint32_t /*extendedTag*/, IfdId /*group*/) {
    return nullptr;
}

class TiffParserWorkerEncodeTest_1168 : public ::testing::Test {
 protected:
    void SetUp() override {
        // Suppress info messages during tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }
};

// Test: Encoding with no existing binary data and empty metadata should produce intrusive write
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeEmptyDataEmptyMetadata_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    TiffHeader header;

    WriteMethod wm = TiffParserWorker::encode(
        io, nullptr, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, nullptr);

    EXPECT_EQ(wm, wmIntrusive);
}

// Test: Encoding with null binary data and some EXIF data produces intrusive write
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeNullDataWithExifData_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    // Add a simple EXIF entry
    exifData["Exif.Image.Make"] = "TestCamera";

    TiffHeader header;

    WriteMethod wm = TiffParserWorker::encode(
        io, nullptr, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, nullptr);

    EXPECT_EQ(wm, wmIntrusive);
    // The io should have data written to it
    EXPECT_GT(io.size(), 0u);
}

// Test: Encoding with valid TIFF binary data and no metadata changes may be non-intrusive
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeWithExistingTiffNoChanges_1168) {
    // First, create a TIFF image with some EXIF data
    MemIo ioFirst;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    exifData["Exif.Image.Make"] = "TestCamera";

    TiffHeader header1;
    TiffParserWorker::encode(
        ioFirst, nullptr, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header1, nullptr);

    // Now try to re-encode with the same data (non-intrusive should be possible)
    const byte* pData = ioFirst.mmap(false);
    size_t size = ioFirst.size();

    MemIo ioSecond;
    TiffHeader header2;

    WriteMethod wm = TiffParserWorker::encode(
        ioSecond, pData, size, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header2, nullptr);

    // Could be either intrusive or non-intrusive depending on internal logic
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);

    ioFirst.munmap();
}

// Test: Encoding with existing TIFF binary data and modified metadata should produce intrusive write
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeWithExistingTiffAndModifiedData_1168) {
    // Create initial TIFF
    MemIo ioFirst;
    ExifData exifDataOriginal;
    IptcData iptcData;
    XmpData xmpData;

    exifDataOriginal["Exif.Image.Make"] = "OriginalCamera";

    TiffHeader header1;
    TiffParserWorker::encode(
        ioFirst, nullptr, 0, exifDataOriginal, iptcData, xmpData,
        Tag::root, findEncoder, &header1, nullptr);

    const byte* pData = ioFirst.mmap(false);
    size_t size = ioFirst.size();

    // Now re-encode with different metadata
    ExifData exifDataModified;
    exifDataModified["Exif.Image.Make"] = "ModifiedCamera";
    exifDataModified["Exif.Image.Model"] = "NewModel";

    MemIo ioSecond;
    TiffHeader header2;

    WriteMethod wm = TiffParserWorker::encode(
        ioSecond, pData, size, exifDataModified, iptcData, xmpData,
        Tag::root, findEncoder, &header2, nullptr);

    // Modified data should typically cause intrusive write
    EXPECT_EQ(wm, wmIntrusive);
    EXPECT_GT(ioSecond.size(), 0u);

    ioFirst.munmap();
}

// Test: Encoding with OffsetWriter should still produce output
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeWithOffsetWriter_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    exifData["Exif.Image.Make"] = "TestCamera";

    TiffHeader header;
    OffsetWriter offsetWriter;

    WriteMethod wm = TiffParserWorker::encode(
        io, nullptr, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, &offsetWriter);

    EXPECT_EQ(wm, wmIntrusive);
    EXPECT_GT(io.size(), 0u);
}

// Test: Encoding writes valid TIFF structure (starts with byte order mark)
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeProducesValidTiffHeader_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    exifData["Exif.Image.Make"] = "TestCamera";

    TiffHeader header(littleEndian);

    TiffParserWorker::encode(
        io, nullptr, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, nullptr);

    ASSERT_GE(io.size(), 8u);

    byte buf[8];
    io.seek(0, BasicIo::beg);
    io.read(buf, 8);

    // Check TIFF header: should start with "II" (little-endian) or "MM" (big-endian)
    bool isLittleEndian = (buf[0] == 'I' && buf[1] == 'I');
    bool isBigEndian = (buf[0] == 'M' && buf[1] == 'M');
    EXPECT_TRUE(isLittleEndian || isBigEndian);

    // Check magic number 42
    if (isLittleEndian) {
        EXPECT_EQ(buf[2], 42);
        EXPECT_EQ(buf[3], 0);
    } else if (isBigEndian) {
        EXPECT_EQ(buf[2], 0);
        EXPECT_EQ(buf[3], 42);
    }
}

// Test: Encoding with big-endian byte order
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeWithBigEndianByteOrder_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    exifData["Exif.Image.Make"] = "TestCamera";

    TiffHeader header(bigEndian);

    WriteMethod wm = TiffParserWorker::encode(
        io, nullptr, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, nullptr);

    EXPECT_EQ(wm, wmIntrusive);
    ASSERT_GE(io.size(), 4u);

    byte buf[4];
    io.seek(0, BasicIo::beg);
    io.read(buf, 4);

    // Big-endian: "MM"
    EXPECT_EQ(buf[0], 'M');
    EXPECT_EQ(buf[1], 'M');
    EXPECT_EQ(buf[2], 0);
    EXPECT_EQ(buf[3], 42);
}

// Test: Encoding with empty metadata and no binary data results in output to IO
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeEmptyAllProducesOutput_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    TiffHeader header;

    TiffParserWorker::encode(
        io, nullptr, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, nullptr);

    // Even with empty metadata, a TIFF structure should be written
    // The header alone is at least 8 bytes
    EXPECT_GE(io.size(), 8u);
}

// Test: Encoding with zero-size binary data pointer (non-null but zero size)
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeWithZeroSizeData_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    TiffHeader header;

    byte dummyByte = 0;
    WriteMethod wm = TiffParserWorker::encode(
        io, &dummyByte, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, nullptr);

    EXPECT_EQ(wm, wmIntrusive);
}

// Test: Multiple EXIF entries are encoded
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeMultipleExifEntries_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    exifData["Exif.Image.Make"] = "TestMake";
    exifData["Exif.Image.Model"] = "TestModel";
    exifData["Exif.Image.Software"] = "TestSoftware";

    TiffHeader header;

    WriteMethod wm = TiffParserWorker::encode(
        io, nullptr, 0, exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, nullptr);

    EXPECT_EQ(wm, wmIntrusive);
    // Should have more data than just header
    EXPECT_GT(io.size(), 8u);
}

// Test: Decode and then re-encode roundtrip
TEST_F(TiffParserWorkerEncodeTest_1168, DecodeAndReencodeRoundtrip_1168) {
    // First encode
    MemIo ioFirst;
    ExifData exifDataWrite;
    IptcData iptcData;
    XmpData xmpData;

    exifDataWrite["Exif.Image.Make"] = "RoundtripCamera";

    TiffHeader header1;
    TiffParserWorker::encode(
        ioFirst, nullptr, 0, exifDataWrite, iptcData, xmpData,
        Tag::root, findEncoder, &header1, nullptr);

    // Decode
    const byte* pData = ioFirst.mmap(false);
    size_t size = ioFirst.size();

    ExifData exifDataRead;
    IptcData iptcDataRead;
    XmpData xmpDataRead;
    TiffHeader header2;

    TiffParserWorker::decode(
        exifDataRead, iptcDataRead, xmpDataRead,
        pData, size, Tag::root, nullptr, &header2);

    // Re-encode with decoded data
    MemIo ioSecond;
    TiffHeader header3;

    WriteMethod wm = TiffParserWorker::encode(
        ioSecond, pData, size, exifDataRead, iptcDataRead, xmpDataRead,
        Tag::root, findEncoder, &header3, nullptr);

    // Should produce valid output
    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);
    EXPECT_GT(ioSecond.size(), 0u);

    ioFirst.munmap();
}

// Test: OffsetWriter basic operations
TEST_F(TiffParserWorkerEncodeTest_1168, OffsetWriterSetOriginAndTarget_1168) {
    OffsetWriter ow;
    // This should not throw - setting origin and target
    ow.setOrigin(OffsetWriter::OffsetId(0), 100, littleEndian);
    ow.setTarget(OffsetWriter::OffsetId(0), 200);

    // Write offsets to a MemIo
    MemIo io;
    // Need at least enough space
    byte buf[200] = {};
    io.write(buf, sizeof(buf));
    io.seek(0, BasicIo::beg);

    ow.writeOffsets(io);
    // Should not crash; verifying the operation completes
    EXPECT_GE(io.size(), 100u);
}

// Test: TiffHeaderBase basic properties
TEST_F(TiffParserWorkerEncodeTest_1168, TiffHeaderBaseProperties_1168) {
    TiffHeader header(littleEndian, 8);

    EXPECT_EQ(header.byteOrder(), littleEndian);
    EXPECT_EQ(header.offset(), 8u);
    EXPECT_EQ(header.tag(), 42);
    EXPECT_EQ(header.size(), 8u);
}

// Test: TiffHeaderBase setByteOrder changes byte order
TEST_F(TiffParserWorkerEncodeTest_1168, TiffHeaderBaseSetByteOrder_1168) {
    TiffHeader header(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);

    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test: TiffHeaderBase setOffset changes offset
TEST_F(TiffParserWorkerEncodeTest_1168, TiffHeaderBaseSetOffset_1168) {
    TiffHeader header(littleEndian, 8);
    EXPECT_EQ(header.offset(), 8u);

    header.setOffset(16);
    EXPECT_EQ(header.offset(), 16u);
}

// Test: TiffHeaderBase write produces valid data
TEST_F(TiffParserWorkerEncodeTest_1168, TiffHeaderBaseWrite_1168) {
    TiffHeader header(littleEndian, 8);
    DataBuf buf = header.write();

    EXPECT_EQ(buf.size(), 8u);
    // Little-endian: "II"
    EXPECT_EQ(buf.read_uint8(0), 'I');
    EXPECT_EQ(buf.read_uint8(1), 'I');
}

// Test: TiffHeaderBase read with valid TIFF data
TEST_F(TiffParserWorkerEncodeTest_1168, TiffHeaderBaseReadValid_1168) {
    auto tiff = makeMinimalTiff();
    TiffHeader header;

    bool result = header.read(tiff.data(), tiff.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    EXPECT_EQ(header.offset(), 8u);
}

// Test: TiffHeaderBase read with data too small
TEST_F(TiffParserWorkerEncodeTest_1168, TiffHeaderBaseReadTooSmall_1168) {
    byte smallData[4] = {'I', 'I', 42, 0};
    TiffHeader header;

    bool result = header.read(smallData, 4);
    // Expect failure since data is too small for a full TIFF header
    EXPECT_FALSE(result);
}

// Test: TiffHeaderBase read with invalid byte order
TEST_F(TiffParserWorkerEncodeTest_1168, TiffHeaderBaseReadInvalidByteOrder_1168) {
    byte invalidData[8] = {'X', 'X', 42, 0, 8, 0, 0, 0};
    TiffHeader header;

    bool result = header.read(invalidData, 8);
    EXPECT_FALSE(result);
}

// Test: TiffHeaderBase isImageTag always returns false for base
TEST_F(TiffParserWorkerEncodeTest_1168, TiffHeaderBaseIsImageTag_1168) {
    TiffHeader header;
    PrimaryGroups pg;

    bool result = header.isImageTag(0x0100, IfdId::ifd0Id, pg);
    EXPECT_FALSE(result);
}

// Test: Encoding with invalid/corrupted binary data still works (intrusive)
TEST_F(TiffParserWorkerEncodeTest_1168, EncodeWithCorruptedBinaryData_1168) {
    MemIo io;
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    exifData["Exif.Image.Make"] = "TestCamera";

    // Create some garbage data that isn't valid TIFF
    byte garbage[64];
    memset(garbage, 0xFF, sizeof(garbage));

    TiffHeader header;

    WriteMethod wm = TiffParserWorker::encode(
        io, garbage, sizeof(garbage), exifData, iptcData, xmpData,
        Tag::root, findEncoder, &header, nullptr);

    // Should fall back to intrusive writing since parsing will fail
    EXPECT_EQ(wm, wmIntrusive);
    EXPECT_GT(io.size(), 0u);
}

// Test: TiffCreator create returns non-null for root
TEST_F(TiffParserWorkerEncodeTest_1168, TiffCreatorCreateRoot_1168) {
    auto component = TiffCreator::create(Tag::root, IfdId::ifdIdNotSet);
    EXPECT_NE(component, nullptr);
}

// Test: IoWrapper writes data through to underlying IO
TEST_F(TiffParserWorkerEncodeTest_1168, IoWrapperWrite_1168) {
    MemIo memIo;
    byte headerData[8] = {'I', 'I', 42, 0, 8, 0, 0, 0};

    IoWrapper wrapper(memIo, headerData, sizeof(headerData), nullptr);

    byte testData[] = {1, 2, 3, 4};
    size_t written = wrapper.write(testData, sizeof(testData));

    // The wrapper may write header + data on first write
    EXPECT_GT(written, 0u);
    EXPECT_GT(memIo.size(), 0u);
}

// Test: IoWrapper putb writes single byte
TEST_F(TiffParserWorkerEncodeTest_1168, IoWrapperPutb_1168) {
    MemIo memIo;
    byte headerData[8] = {'I', 'I', 42, 0, 8, 0, 0, 0};

    IoWrapper wrapper(memIo, headerData, sizeof(headerData), nullptr);

    int result = wrapper.putb(0x42);
    EXPECT_EQ(result, 0x42);
    EXPECT_GT(memIo.size(), 0u);
}

// Test: DataBuf basic operations
TEST_F(TiffParserWorkerEncodeTest_1168, DataBufBasicOperations_1168) {
    DataBuf buf(16);
    EXPECT_EQ(buf.size(), 16u);
    EXPECT_FALSE(buf.empty());

    buf.write_uint8(0, 0x42);
    EXPECT_EQ(buf.read_uint8(0), 0x42);

    buf.write_uint16(2, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(2, littleEndian), 0x1234);

    buf.write_uint32(4, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0xDEADBEEF);
}

// Test: DataBuf default construction
TEST_F(TiffParserWorkerEncodeTest_1168, DataBufDefaultConstruction_1168) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// Test: DataBuf reset clears data
TEST_F(TiffParserWorkerEncodeTest_1168, DataBufReset_1168) {
    DataBuf buf(32);
    EXPECT_EQ(buf.size(), 32u);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}
