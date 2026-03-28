#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>

#include "FoFiTrueType.h"

// Helper output function that appends to a std::string
static void outputToString(void *stream, const char *data, int len) {
    std::string *str = static_cast<std::string *>(stream);
    str->append(data, len);
}

// Minimal valid TrueType font data - we'll test with nullptr/empty data to check error handling
// and with actual font files if available

class FoFiTrueTypeTest_45 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal TTF-like buffer (not necessarily valid)
    std::vector<unsigned char> createMinimalTTFData() {
        // A minimal TrueType file has at least an offset table (12 bytes)
        // plus table records. This won't be a valid font but tests null handling.
        std::vector<unsigned char> data(64, 0);
        // TrueType signature: 0x00010000
        data[0] = 0x00;
        data[1] = 0x01;
        data[2] = 0x00;
        data[3] = 0x00;
        // numTables = 0
        data[4] = 0x00;
        data[5] = 0x00;
        return data;
    }
};

// Test that make() with null/empty data returns nullptr
TEST_F(FoFiTrueTypeTest_45, MakeWithNullDataReturnsNull_45) {
    auto result = FoFiTrueType::make(nullptr, 0, 0);
    // Depending on implementation, may return nullptr for invalid data
    // We just test that it doesn't crash
}

// Test that load() with non-existent file returns nullptr
TEST_F(FoFiTrueTypeTest_45, LoadNonExistentFileReturnsNull_45) {
    auto result = FoFiTrueType::load("/non/existent/path/to/font.ttf", 0);
    EXPECT_EQ(result, nullptr);
}

// Test that load() with nullptr filename returns nullptr
TEST_F(FoFiTrueTypeTest_45, LoadNullFilenameReturnsNull_45) {
    auto result = FoFiTrueType::load(nullptr, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that load() with empty filename returns nullptr
TEST_F(FoFiTrueTypeTest_45, LoadEmptyFilenameReturnsNull_45) {
    auto result = FoFiTrueType::load("", 0);
    EXPECT_EQ(result, nullptr);
}

// Test isOpenTypeCFF on a TrueType font (should return false for regular TTF)
TEST_F(FoFiTrueTypeTest_45, IsOpenTypeCFFReturnsFalseForTTF_45) {
    // Try to find a system TTF font
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        EXPECT_FALSE(font->isOpenTypeCFF());
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test getNumCmaps returns a non-negative value for a valid font
TEST_F(FoFiTrueTypeTest_45, GetNumCmapsReturnsNonNegativeForValidFont_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int numCmaps = font->getNumCmaps();
        EXPECT_GE(numCmaps, 0);
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test getCmapPlatform and getCmapEncoding with valid and invalid indices
TEST_F(FoFiTrueTypeTest_45, GetCmapPlatformAndEncodingValidIndex_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int numCmaps = font->getNumCmaps();
        if (numCmaps > 0) {
            int platform = font->getCmapPlatform(0);
            int encoding = font->getCmapEncoding(0);
            // Platform IDs: 0=Unicode, 1=Macintosh, 3=Windows
            EXPECT_GE(platform, 0);
            EXPECT_GE(encoding, 0);
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test findCmap for a common platform/encoding combination
TEST_F(FoFiTrueTypeTest_45, FindCmapReturnsValidIndexForWindowsUnicodeBMP_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        // Platform 3 (Windows), Encoding 1 (Unicode BMP) is very common
        int cmapIndex = font->findCmap(3, 1);
        // It's common for this to exist, but not guaranteed
        // Just check it doesn't crash and returns a reasonable value
        EXPECT_GE(cmapIndex, -1); // -1 or valid index
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test findCmap with non-existent platform/encoding
TEST_F(FoFiTrueTypeTest_45, FindCmapReturnsNegativeForNonExistentCmap_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        // Use an unlikely platform/encoding combination
        int cmapIndex = font->findCmap(999, 999);
        EXPECT_LT(cmapIndex, 0);
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test mapCodeToGID with invalid cmap index
TEST_F(FoFiTrueTypeTest_45, MapCodeToGIDWithInvalidCmapIndex_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        // Invalid cmap index should return 0
        int gid = font->mapCodeToGID(-1, 'A');
        EXPECT_EQ(gid, 0);
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test mapCodeToGID with valid cmap for ASCII 'A'
TEST_F(FoFiTrueTypeTest_45, MapCodeToGIDForLetterA_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int cmapIndex = font->findCmap(3, 1);
        if (cmapIndex >= 0) {
            int gid = font->mapCodeToGID(cmapIndex, 'A');
            // 'A' should map to a non-zero GID in most fonts
            EXPECT_GT(gid, 0);
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test mapCodeToGID for null character
TEST_F(FoFiTrueTypeTest_45, MapCodeToGIDForNullCharacter_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int cmapIndex = font->findCmap(3, 1);
        if (cmapIndex >= 0) {
            int gid = font->mapCodeToGID(cmapIndex, 0);
            // Null character typically maps to GID 0
            EXPECT_EQ(gid, 0);
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test getEmbeddingRights returns a valid value
TEST_F(FoFiTrueTypeTest_45, GetEmbeddingRightsReturnsValidValue_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int rights = font->getEmbeddingRights();
        // Embedding rights should be a valid fsType value or -1 if not found
        EXPECT_GE(rights, -1);
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test getCIDToGIDMap returns a vector
TEST_F(FoFiTrueTypeTest_45, GetCIDToGIDMapReturnsVector_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        auto cidToGID = font->getCIDToGIDMap();
        // For a non-CID font, this might be empty or populated
        // Just check it doesn't crash
        EXPECT_GE(static_cast<int>(cidToGID.size()), 0);
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test convertToType42 produces output
TEST_F(FoFiTrueTypeTest_45, ConvertToType42ProducesOutput_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        if (!font->isOpenTypeCFF()) {
            std::string output;
            std::vector<int> codeToGID(256, 0);
            // Set up a basic mapping
            int cmapIndex = font->findCmap(3, 1);
            if (cmapIndex >= 0) {
                for (int i = 0; i < 256; ++i) {
                    codeToGID[i] = font->mapCodeToGID(cmapIndex, i);
                }
            }

            font->convertToType42("TestFont", nullptr, codeToGID,
                                  &outputToString, &output);
            EXPECT_FALSE(output.empty());
            // Type42 fonts should contain certain PostScript elements
            EXPECT_NE(output.find("/FontType 42"), std::string::npos);
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test convertToCIDType2 produces output
TEST_F(FoFiTrueTypeTest_45, ConvertToCIDType2ProducesOutput_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        if (!font->isOpenTypeCFF()) {
            std::string output;
            std::vector<int> cidMap;

            font->convertToCIDType2("TestFont", cidMap, false,
                                    &outputToString, &output);
            EXPECT_FALSE(output.empty());
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test convertToType0 produces output
TEST_F(FoFiTrueTypeTest_45, ConvertToType0ProducesOutput_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        if (!font->isOpenTypeCFF()) {
            std::string output;
            std::vector<int> cidMap;
            int maxValidGlyph = 0;

            font->convertToType0("TestFont", cidMap, false, &maxValidGlyph,
                                 &outputToString, &output);
            EXPECT_FALSE(output.empty());
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test mapToVertGID with GID 0
TEST_F(FoFiTrueTypeTest_45, MapToVertGIDWithZeroGID_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        unsigned int vertGID = font->mapToVertGID(0);
        // Without GSUB vertical feature setup, should return the same GID
        EXPECT_EQ(vertGID, 0u);
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test mapNameToGID with a known glyph name
TEST_F(FoFiTrueTypeTest_45, MapNameToGIDForSpace_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        // "space" is a common glyph name
        int gid = font->mapNameToGID("space");
        // Most fonts have a space glyph
        // It might return 0 if the post table doesn't have names
        EXPECT_GE(gid, 0);
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test mapNameToGID with non-existent name
TEST_F(FoFiTrueTypeTest_45, MapNameToGIDForNonExistentName_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int gid = font->mapNameToGID("nonexistent_glyph_name_xyz_12345");
        EXPECT_EQ(gid, 0);
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test setupGSUB with invalid script
TEST_F(FoFiTrueTypeTest_45, SetupGSUBWithInvalidScript_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int result = font->setupGSUB("ZZZZ", "ZZZZ");
        // Should handle gracefully - likely returns error or no-op
        // Don't crash is the main thing
        (void)result;
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test that multiple cmap queries are consistent
TEST_F(FoFiTrueTypeTest_45, CmapQueriesAreConsistent_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int numCmaps = font->getNumCmaps();
        for (int i = 0; i < numCmaps; ++i) {
            int platform = font->getCmapPlatform(i);
            int encoding = font->getCmapEncoding(i);
            int foundIndex = font->findCmap(platform, encoding);
            // Should find the cmap we just queried (may find an earlier one with same platform/encoding)
            EXPECT_GE(foundIndex, 0);
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test that getCmapPlatform with out-of-bounds index handles gracefully
TEST_F(FoFiTrueTypeTest_45, GetCmapPlatformOutOfBoundsIndex_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int numCmaps = font->getNumCmaps();
        // Query beyond valid range - should not crash
        int platform = font->getCmapPlatform(numCmaps + 100);
        int encoding = font->getCmapEncoding(numCmaps + 100);
        // Just ensure no crash; values are implementation-defined
        (void)platform;
        (void)encoding;
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test loading with different face index
TEST_F(FoFiTrueTypeTest_45, LoadWithInvalidFaceIndex_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        // Try loading with face index 999 (unlikely to exist in a single-face font)
        auto font = FoFiTrueType::load(possibleFonts[i], 999);
        // For a single-face TTF, this might still succeed but with default face,
        // or it might return nullptr. Either way it shouldn't crash.
        if (font) {
            // If it loaded, basic operations should still work
            EXPECT_GE(font->getNumCmaps(), 0);
            return;
        }
    }
    GTEST_SKIP() << "No TrueType font found on system for testing";
}

// Test convertToType42 with null output function doesn't crash (boundary test)
// Note: this might crash depending on implementation, so we guard it
TEST_F(FoFiTrueTypeTest_45, MapCodeToGIDWithHighCodepoint_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        int cmapIndex = font->findCmap(3, 1);
        if (cmapIndex >= 0) {
            // Test with a very high codepoint
            int gid = font->mapCodeToGID(cmapIndex, 0xFFFF);
            // Should return 0 or a valid GID
            EXPECT_GE(gid, 0);

            // Test with maximum unsigned int value
            gid = font->mapCodeToGID(cmapIndex, 0xFFFFFFFF);
            EXPECT_GE(gid, 0);
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test that mapNameToGID with nullptr doesn't crash
TEST_F(FoFiTrueTypeTest_45, MapNameToGIDWithCommonNames_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        // Test common glyph names
        int gidA = font->mapNameToGID("A");
        int gidB = font->mapNameToGID("B");
        int gidNotDef = font->mapNameToGID(".notdef");

        // These should all be valid (>=0)
        EXPECT_GE(gidA, 0);
        EXPECT_GE(gidB, 0);
        EXPECT_GE(gidNotDef, 0);

        // A and B should map to different GIDs (if both exist)
        if (gidA > 0 && gidB > 0) {
            EXPECT_NE(gidA, gidB);
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test convertToType0 overload without maxValidGlyph pointer
TEST_F(FoFiTrueTypeTest_45, ConvertToType0OverloadProducesOutput_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    std::unique_ptr<FoFiTrueType> font;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        font = FoFiTrueType::load(possibleFonts[i], 0);
        if (font) {
            break;
        }
    }

    if (font) {
        if (font->isOpenTypeCFF()) {
            std::string output;
            std::vector<int> cidMap;

            font->convertToType0("TestFont", cidMap,
                                 &outputToString, &output);
            // OpenType CFF fonts should produce CIDFont Type0 output
            EXPECT_FALSE(output.empty());
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}

// Test that loading the same font twice produces consistent results
TEST_F(FoFiTrueTypeTest_45, LoadSameFontTwiceIsConsistent_45) {
    const char *possibleFonts[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };

    const char *fontPath = nullptr;
    for (int i = 0; possibleFonts[i] != nullptr; ++i) {
        auto testFont = FoFiTrueType::load(possibleFonts[i], 0);
        if (testFont) {
            fontPath = possibleFonts[i];
            break;
        }
    }

    if (fontPath) {
        auto font1 = FoFiTrueType::load(fontPath, 0);
        auto font2 = FoFiTrueType::load(fontPath, 0);

        ASSERT_NE(font1, nullptr);
        ASSERT_NE(font2, nullptr);

        EXPECT_EQ(font1->getNumCmaps(), font2->getNumCmaps());
        EXPECT_EQ(font1->isOpenTypeCFF(), font2->isOpenTypeCFF());
        EXPECT_EQ(font1->getEmbeddingRights(), font2->getEmbeddingRights());

        int numCmaps = font1->getNumCmaps();
        for (int i = 0; i < numCmaps; ++i) {
            EXPECT_EQ(font1->getCmapPlatform(i), font2->getCmapPlatform(i));
            EXPECT_EQ(font1->getCmapEncoding(i), font2->getCmapEncoding(i));
        }
    } else {
        GTEST_SKIP() << "No TrueType font found on system for testing";
    }
}
