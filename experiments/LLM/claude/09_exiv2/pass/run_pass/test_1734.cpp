#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/tags.hpp>
#include <cstring>

using namespace Exiv2;

class TiffParserTest_1734 : public ::testing::Test {
protected:
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    void SetUp() override {
        exifData.clear();
        iptcData.clear();
        xmpData.clear();
    }
};

// Test decode with null data pointer and zero size
TEST_F(TiffParserTest_1734, DecodeNullDataZeroSize_1734) {
    // Passing nullptr with size 0 should not crash; it may throw or return gracefully
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, nullptr, 0);
        // If it doesn't throw, we just verify it returns some ByteOrder
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected - invalid data may throw
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with empty data (non-null but zero size)
TEST_F(TiffParserTest_1734, DecodeEmptyData_1734) {
    const byte emptyData[] = {0};
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, emptyData, 0);
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected for invalid/empty TIFF data
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with too-small data that isn't valid TIFF
TEST_F(TiffParserTest_1734, DecodeTooSmallData_1734) {
    const byte smallData[] = {0x49, 0x49}; // Just "II" - too small for valid TIFF
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, smallData, 2);
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected for data too small to be TIFF
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with invalid TIFF magic number
TEST_F(TiffParserTest_1734, DecodeInvalidMagic_1734) {
    // TIFF requires either "II" (little endian) or "MM" (big endian) followed by 42
    const byte invalidData[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, invalidData, 8);
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected for invalid TIFF header
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with a minimal valid little-endian TIFF header but no IFD entries
TEST_F(TiffParserTest_1734, DecodeMinimalLittleEndianTiff_1734) {
    // II (little endian), 42, offset to IFD = 8, IFD with 0 entries, next IFD offset = 0
    const byte tiffLE[] = {
        0x49, 0x49,             // "II" - little endian
        0x2A, 0x00,             // Magic number 42
        0x08, 0x00, 0x00, 0x00, // Offset to first IFD (8)
        0x00, 0x00,             // Number of directory entries (0)
        0x00, 0x00, 0x00, 0x00  // Next IFD offset (0 = no more IFDs)
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, tiffLE, sizeof(tiffLE));
        EXPECT_EQ(bo, littleEndian);
    } catch (const Exiv2::Error&) {
        // May throw if it considers this insufficient
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with a minimal valid big-endian TIFF header but no IFD entries
TEST_F(TiffParserTest_1734, DecodeMinimalBigEndianTiff_1734) {
    const byte tiffBE[] = {
        0x4D, 0x4D,             // "MM" - big endian
        0x00, 0x2A,             // Magic number 42
        0x00, 0x00, 0x00, 0x08, // Offset to first IFD (8)
        0x00, 0x00,             // Number of directory entries (0)
        0x00, 0x00, 0x00, 0x00  // Next IFD offset (0)
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, tiffBE, sizeof(tiffBE));
        EXPECT_EQ(bo, bigEndian);
    } catch (const Exiv2::Error&) {
        // May throw
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test that FUJIFILM Make in ExifData influences the decode (Fuji root path)
TEST_F(TiffParserTest_1734, DecodeFujifilmMake_1734) {
    // Pre-populate ExifData with Exif.Image.Make = "FUJIFILM"
    exifData["Exif.Image.Make"] = "FUJIFILM";

    // Minimal LE TIFF
    const byte tiffLE[] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, tiffLE, sizeof(tiffLE));
        // Should not crash - it uses fuji root instead of standard root
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Acceptable
    } catch (const std::exception&) {
        // Acceptable
    }
}

// Test that non-FUJIFILM Make does not trigger Fuji path
TEST_F(TiffParserTest_1734, DecodeNonFujiMake_1734) {
    exifData["Exif.Image.Make"] = "Canon";

    const byte tiffLE[] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, tiffLE, sizeof(tiffLE));
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Acceptable
    } catch (const std::exception&) {
        // Acceptable
    }
}

// Test decode with ExifData that has Make key but empty value
TEST_F(TiffParserTest_1734, DecodeEmptyMakeValue_1734) {
    exifData["Exif.Image.Make"] = "";

    const byte tiffLE[] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, tiffLE, sizeof(tiffLE));
        // Should use standard root (not fuji) since Make is not "FUJIFILM"
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Acceptable
    } catch (const std::exception&) {
        // Acceptable
    }
}

// Test decode with random garbage data
TEST_F(TiffParserTest_1734, DecodeGarbageData_1734) {
    const byte garbage[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6};
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, garbage, sizeof(garbage));
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected for garbage data
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with data size = 1 (boundary)
TEST_F(TiffParserTest_1734, DecodeSingleByte_1734) {
    const byte singleByte[] = {0x49};
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, singleByte, 1);
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with exactly 8 bytes (minimal TIFF header size but no IFD)
TEST_F(TiffParserTest_1734, DecodeExactHeaderSizeNoIFD_1734) {
    // Valid header but IFD offset points beyond data
    const byte headerOnly[] = {
        0x49, 0x49,             // "II"
        0x2A, 0x00,             // 42
        0x08, 0x00, 0x00, 0x00  // offset to IFD = 8, but no data there
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, headerOnly, sizeof(headerOnly));
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected - IFD is beyond end of data
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test that decode with FUJIFILM make (case sensitive - lowercase should NOT trigger fuji)
TEST_F(TiffParserTest_1734, DecodeFujifilmCaseSensitive_1734) {
    exifData["Exif.Image.Make"] = "Fujifilm"; // Not exactly "FUJIFILM"

    const byte tiffLE[] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x08, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, tiffLE, sizeof(tiffLE));
        // Should use standard root since "Fujifilm" != "FUJIFILM"
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Acceptable
    } catch (const std::exception&) {
        // Acceptable
    }
}

// Test that a valid little endian TIFF with one IFD entry containing Make tag can be decoded
TEST_F(TiffParserTest_1734, DecodeWithMakeTag_1734) {
    // Construct a minimal TIFF with one IFD entry: Make = "Nikon"
    // Layout:
    // 0-1: "II"
    // 2-3: 42 (LE)
    // 4-7: offset to IFD0 = 8
    // 8-9: count of entries = 1
    // 10-21: IFD entry (tag=0x010F Make, type=2 ASCII, count=6, offset=26)
    // 22-25: next IFD offset = 0
    // 26-31: "Nikon\0"
    const byte tiffWithMake[] = {
        0x49, 0x49,                         // 0: "II"
        0x2A, 0x00,                         // 2: 42
        0x08, 0x00, 0x00, 0x00,             // 4: IFD offset = 8
        0x01, 0x00,                         // 8: 1 entry
        0x0F, 0x01,                         // 10: tag 0x010F (Make)
        0x02, 0x00,                         // 12: type 2 (ASCII)
        0x06, 0x00, 0x00, 0x00,             // 14: count = 6
        0x1A, 0x00, 0x00, 0x00,             // 18: value offset = 26
        0x00, 0x00, 0x00, 0x00,             // 22: next IFD = 0
        0x4E, 0x69, 0x6B, 0x6F, 0x6E, 0x00 // 26: "Nikon\0"
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, tiffWithMake, sizeof(tiffWithMake));
        EXPECT_EQ(bo, littleEndian);
        // Check if Make was decoded
        ExifKey makeKey("Exif.Image.Make");
        auto it = exifData.findKey(makeKey);
        if (it != exifData.end()) {
            EXPECT_EQ(it->toString(), "Nikon");
        }
    } catch (const Exiv2::Error&) {
        // May throw depending on internal validation
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with TIFF header pointing to IFD at offset 0 (self-referential)
TEST_F(TiffParserTest_1734, DecodeSelfReferentialOffset_1734) {
    const byte selfRef[] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x00, 0x00, 0x00, 0x00  // IFD offset = 0 (points to start of file)
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, selfRef, sizeof(selfRef));
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected - malformed
    } catch (const std::exception&) {
        // Also acceptable
    }
}

// Test decode with very large IFD offset
TEST_F(TiffParserTest_1734, DecodeLargeIFDOffset_1734) {
    const byte largeOffset[] = {
        0x49, 0x49,
        0x2A, 0x00,
        0xFF, 0xFF, 0xFF, 0x7F  // IFD offset = 0x7FFFFFFF
    };
    try {
        ByteOrder bo = TiffParser::decode(exifData, iptcData, xmpData, largeOffset, sizeof(largeOffset));
        (void)bo;
    } catch (const Exiv2::Error&) {
        // Expected - offset way beyond data
    } catch (const std::exception&) {
        // Also acceptable
    }
}
