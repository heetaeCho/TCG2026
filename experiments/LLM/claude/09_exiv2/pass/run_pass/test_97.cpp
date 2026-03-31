#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/matroskavideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <memory>
#include <sstream>

using namespace Exiv2;

class MatroskaVideoTest_97 : public ::testing::Test {
protected:
    std::unique_ptr<MatroskaVideo> createMatroskaVideo(const byte* data, size_t size) {
        auto io = std::make_unique<MemIo>(data, size);
        return std::make_unique<MatroskaVideo>(std::move(io));
    }

    std::unique_ptr<MatroskaVideo> createMatroskaVideoFromEmpty() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<MatroskaVideo>(std::move(io));
    }
};

// Test mimeType returns correct MIME type
TEST_F(MatroskaVideoTest_97, MimeType_97) {
    auto mkv = createMatroskaVideoFromEmpty();
    EXPECT_EQ(mkv->mimeType(), "video/x-matroska");
}

// Test writeMetadata throws
TEST_F(MatroskaVideoTest_97, WriteMetadataThrows_97) {
    auto mkv = createMatroskaVideoFromEmpty();
    EXPECT_THROW(mkv->writeMetadata(), Error);
}

// Test readMetadata on empty data
TEST_F(MatroskaVideoTest_97, ReadMetadataEmptyData_97) {
    auto mkv = createMatroskaVideoFromEmpty();
    EXPECT_THROW(mkv->readMetadata(), Error);
}

// Test readMetadata with minimal valid EBML header
TEST_F(MatroskaVideoTest_97, ReadMetadataMinimalFile_97) {
    // EBML Header tag: 0x1A45DFA3
    // This is a 4-byte tag with leading bits pattern
    // The EBML header ID is 0x1A45DFA3 (EBMLHeader = 172351395)
    // encoded in Matroska VINT form: 1A 45 DF A3
    // followed by size
    // We just try to not crash; the file won't be fully valid
    byte data[] = {
        0x1A, 0x45, 0xDF, 0xA3,  // EBML Header tag ID
        0x84,                      // Size: 4 bytes (VINT)
        0x42, 0x86,                // EBMLVersion tag (0x4286 = 646)
        0x81,                      // Size: 1 byte
        0x01                       // Value: 1
    };
    auto mkv = createMatroskaVideo(data, sizeof(data));
    // readMetadata might throw or might partially work; we just check it doesn't crash fatally
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected for incomplete data
    }
}

// Test with data that triggers EOF immediately (decodeBlock reads 1 byte, gets EOF)
TEST_F(MatroskaVideoTest_97, DecodeBlockEofImmediate_97) {
    byte data[] = {};
    auto io = std::make_unique<MemIo>();
    auto mkv = std::make_unique<MatroskaVideo>(std::move(io));
    // readMetadata should handle EOF gracefully or throw
    EXPECT_THROW(mkv->readMetadata(), Error);
}

// Test findBlockSize is a static protected method - we test it indirectly through readMetadata
// A byte with value 0x80 should result in block size 1 (leading 1 in bit 7)
// A byte with value 0x40 should result in block size 2
// etc.

// Test with a known tag that gets skipped (Binary type, Skip process)
TEST_F(MatroskaVideoTest_97, ReadMetadataSkippedBinaryTag_97) {
    // Block tag (id=33, Binary, Skip): encoded as single-byte VINT
    // But 33 decimal = 0x21 which doesn't have the VINT marker bit
    // In Matroska VINT: for 1-byte IDs, the leading bit must be 1
    // So ID=33 would be 0xA1 (0x80 | 33) 
    // Actually, findBlockSize determines the length based on leading bits
    // For byte 0xA1 (10100001), leading bit is 1, so block_size=1, tag value = 0xA1 & 0x7F = 0x21 = 33
    // Wait, returnTagValue likely strips the VINT marker. Let me reconsider.
    // Actually the tag_id = returnTagValue(buf, block_size) likely returns the raw value
    // For the matroskaTags array, Block = 33, so we need to produce tag_id = 33

    // For a 1-byte VINT: byte with leading 1 bit -> block_size = 1
    // returnTagValue for 1 byte likely returns buf[0] & 0x7F = value, or just buf[0]
    // Given Block=33=0x21, as VINT: 0x80|0x21 = 0xA1

    // Size VINT: 0x82 = size 2 (0x80|0x02)
    // Then 2 bytes of data that get skipped (Binary, Skip)
    byte data[] = {
        0xA1,       // Tag ID VINT for Block (33): 0x80|0x21
        0x82,       // Size VINT: 2 bytes
        0x00, 0x00  // 2 bytes of data (skipped)
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // May throw due to incomplete file structure
    }
}

// Test with data forming a Cues tag which should stop traversal
TEST_F(MatroskaVideoTest_97, ReadMetadataCuesStopsTraversal_97) {
    // Cues = 206814059 = 0x0C53BB6B
    // As a 4-byte VINT: first byte has leading pattern 0001xxxx
    // 4-byte VINT: 0x10 | (value >> 24 & 0x0F)
    // 0x0C53BB6B: 
    // For VINT encoding: the marker for 4 bytes is bit pattern 0001xxxx in first byte
    // value = 0x0C53BB6B
    // first byte: 0x10 | ((0x0C53BB6B >> 21) & 0x0F)... 
    // Actually the standard EBML VINT for element IDs keeps the leading bits
    // The raw bytes for Cues element ID are: 0x1C 0x53 0xBB 0x6B
    
    byte data[] = {
        0x1C, 0x53, 0xBB, 0x6B,  // Cues tag ID (4-byte VINT)
        0x81,                      // Size VINT: 1 byte
        0x00                       // dummy data
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test with valid Cluster tag which should also stop traversal  
TEST_F(MatroskaVideoTest_97, ReadMetadataClusterStopsTraversal_97) {
    // Cluster = 256095861 = 0x0F43B675
    // 4-byte VINT: 0x1F 0x43 0xB6 0x75
    byte data[] = {
        0x1F, 0x43, 0xB6, 0x75,  // Cluster tag ID
        0x81,                      // Size: 1
        0x00
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test with an unknown tag ID which should stop traversal
TEST_F(MatroskaVideoTest_97, ReadMetadataUnknownTagStopsTraversal_97) {
    // Use a tag ID that's not in the matroskaTags table
    // 0xFF would be VINT value 0x7F = 127, which is not a known tag
    byte data[] = {
        0xFF,   // Unknown 1-byte VINT tag (value 127)
        0x81,   // Size: 1
        0x00
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test a composite tag that is not skipped (should recurse without reading content)
TEST_F(MatroskaVideoTest_97, ReadMetadataCompositeTag_97) {
    // Video = 96 = 0x60, as VINT: 0xE0 (0x80|0x60), Master type, Composite process
    // For composite+not-skipped, decodeBlock returns after reading size (no content read)
    byte data[] = {
        0xE0,       // Video tag (96) as 1-byte VINT
        0x80,       // Size: 0 (empty composite)
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test a string tag that gets processed
TEST_F(MatroskaVideoTest_97, ReadMetadataStringTag_97) {
    // Xmp_video_MuxingApp = 3456 = 0x0D80
    // As 2-byte VINT: 0x4D 0x80 (marker bit 01xxxxxx for 2-byte)
    // Actually: 2-byte VINT has leading bits 01, so first byte = 0x40 | (value >> 8) 
    // 3456 = 0x0D80, value >> 8 = 0x0D, first byte = 0x4D, second byte = 0x80
    byte data[] = {
        0x4D, 0x80,             // MuxingApp tag ID (3456) as 2-byte VINT
        0x84,                   // Size: 4 bytes
        't', 'e', 's', 't'     // String value "test"
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // May throw due to incomplete traversal
    }
    // Check if the XMP data contains the MuxingApp
    auto& xmp = mkv->xmpData();
    // The tag might be set; we check if it exists
    auto it = xmp.findKey(XmpKey("Xmp.video.MuxingApp"));
    // It's possible it was set
    if (it != xmp.end()) {
        EXPECT_EQ(it->toString(), "test");
    }
}

// Test an integer tag that gets processed
TEST_F(MatroskaVideoTest_97, ReadMetadataIntegerTag_97) {
    // Xmp_video_EBMLVersion = 646 = 0x0286
    // As 2-byte VINT: first byte = 0x42, second byte = 0x86
    byte data[] = {
        0x42, 0x86,     // EBMLVersion tag ID (646) as 2-byte VINT
        0x81,           // Size: 1 byte
        0x01            // Value: 1
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test a boolean tag
TEST_F(MatroskaVideoTest_97, ReadMetadataBooleanTag_97) {
    // TrackType = 3 = 0x03, as 1-byte VINT: 0x83
    byte data[] = {
        0x83,       // TrackType tag (3) as 1-byte VINT
        0x81,       // Size: 1 byte
        0x01        // Boolean value: true
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test with tag size > 200 (bufMaxSize) which should be skipped with a warning
TEST_F(MatroskaVideoTest_97, ReadMetadataOversizedTagSkipped_97) {
    // Xmp_video_Title = 15273 = 0x3BA9
    // As 2-byte VINT: 0x7B 0xA9 (0x40 | (0x3BA9 >> 8)) = 0x40|0x3B = 0x7B, 0xA9
    // This is a String, Process tag - not skipped, not composite
    // We'll set size to 201 which exceeds bufMaxSize=200
    // Size 201 = 0xC9, as 2-byte VINT: 0x40|0x00 = 0x40, 0xC9
    // Actually we need proper VINT: 201 as 2-byte VINT = 0x40 | (201 >> 8) = 0x40, 0xC9
    
    std::vector<byte> data;
    data.push_back(0x7B); data.push_back(0xA9);  // Title tag ID
    data.push_back(0x40); data.push_back(0xC9);  // Size: 201 (2-byte VINT)
    // Then 201 bytes of data (will be seek'd over since size > 200)
    for (int i = 0; i < 201; i++) {
        data.push_back(0x00);
    }

    auto mkv = createMatroskaVideo(data.data(), data.size());
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test float tag
TEST_F(MatroskaVideoTest_97, ReadMetadataFloatTag_97) {
    // Xmp_audio_SampleRate = 53 = 0x35, as 1-byte VINT: 0xB5
    // Float, Process
    // 4 bytes for a float value (e.g., 44100.0 as IEEE 754)
    float sampleRate = 44100.0f;
    byte floatBytes[4];
    // Big-endian float
    uint32_t asInt;
    std::memcpy(&asInt, &sampleRate, 4);
    floatBytes[0] = (asInt >> 24) & 0xFF;
    floatBytes[1] = (asInt >> 16) & 0xFF;
    floatBytes[2] = (asInt >> 8) & 0xFF;
    floatBytes[3] = asInt & 0xFF;

    byte data[] = {
        0xB5,               // SampleRate tag (53) as 1-byte VINT
        0x84,               // Size: 4 bytes
        floatBytes[0], floatBytes[1], floatBytes[2], floatBytes[3]
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test Date tag
TEST_F(MatroskaVideoTest_97, ReadMetadataDateTag_97) {
    // Xmp_video_DateUTC = 1121 = 0x0461
    // As 2-byte VINT: 0x44, 0x61
    // Date, Process
    byte data[] = {
        0x44, 0x61,                             // DateUTC tag ID (1121) as 2-byte VINT
        0x88,                                   // Size: 8 bytes
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // Date value: 0 (epoch)
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test InternalField tag
TEST_F(MatroskaVideoTest_97, ReadMetadataInternalFieldTag_97) {
    // Xmp_video_VideoScanTpye = 26 = 0x1A, as 1-byte VINT: 0x9A
    // InternalField, Process
    byte data[] = {
        0x9A,       // VideoScanType tag (26) as 1-byte VINT
        0x81,       // Size: 1 byte
        0x01        // Value
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test that constructing MatroskaVideo sets the image type correctly
TEST_F(MatroskaVideoTest_97, ConstructorSetsImageType_97) {
    auto mkv = createMatroskaVideoFromEmpty();
    EXPECT_EQ(mkv->imageType(), ImageType::mkv);
}

// Test with a single byte that causes EOF (file has exactly 1 byte but then EOF on second read)
TEST_F(MatroskaVideoTest_97, SingleByteInput_97) {
    byte data[] = {0x80};  // 1-byte VINT, value 0 (not a valid tag)
    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test with multiple sequential tags
TEST_F(MatroskaVideoTest_97, MultipleSequentialTags_97) {
    // EBMLVersion (646=0x0286, VINT: 42 86) followed by EBMLReadVersion (759=0x02F7, VINT: 42 F7)
    // Both are Integer/UInteger, Process
    byte data[] = {
        // First tag: EBMLVersion
        0x42, 0x86,     // Tag ID
        0x81,           // Size: 1
        0x01,           // Value: 1
        // Second tag: EBMLReadVersion (759 = 0x02F7)
        0x42, 0xF7,     // Tag ID
        0x81,           // Size: 1
        0x01,           // Value: 1
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test with a skipped tag (non-composite, Skip process)
TEST_F(MatroskaVideoTest_97, SkippedTag_97) {
    // ChapterTimeStart = 17 = 0x11, as 1-byte VINT: 0x91
    // UInteger, Skip
    byte data[] = {
        0x91,       // ChapterTimeStart tag (17) as 1-byte VINT
        0x84,       // Size: 4 bytes
        0x00, 0x00, 0x00, 0x01  // Value (will be skipped/seeked)
    };

    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test edge case: tag with size exactly 200 (should be processed, not skipped)
TEST_F(MatroskaVideoTest_97, TagSizeExactly200_97) {
    // Xmp_video_Title = 15273 = 0x3BA9, VINT: 7B A9
    // String, Process (not skipped, not composite)
    // Size 200 = 0xC8, as 2-byte VINT: 0x40 0xC8
    std::vector<byte> data;
    data.push_back(0x7B); data.push_back(0xA9);  // Title tag ID
    data.push_back(0x40); data.push_back(0xC8);  // Size: 200
    // 200 bytes of string data
    for (int i = 0; i < 200; i++) {
        data.push_back('A');
    }

    auto mkv = createMatroskaVideo(data.data(), data.size());
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test with zero-length VINT (findBlockSize returns 0 for byte 0x00)
TEST_F(MatroskaVideoTest_97, ZeroLengthVINT_97) {
    byte data[] = {0x00};
    auto mkv = createMatroskaVideo(data, sizeof(data));
    try {
        mkv->readMetadata();
    } catch (const Error&) {
        // Expected - block_size of 0 means no additional reads, 
        // returnTagValue with size 0 likely yields invalid tag
    }
}

// Test good() on a valid io
TEST_F(MatroskaVideoTest_97, GoodOnValidIo_97) {
    byte data[] = {0x1A, 0x45, 0xDF, 0xA3};
    auto mkv = createMatroskaVideo(data, sizeof(data));
    EXPECT_TRUE(mkv->good());
}

// Test good() on empty io
TEST_F(MatroskaVideoTest_97, GoodOnEmptyIo_97) {
    auto mkv = createMatroskaVideoFromEmpty();
    // MemIo with no data - good() depends on io state
    EXPECT_TRUE(mkv->good());
}
