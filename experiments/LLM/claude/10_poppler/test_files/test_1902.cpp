#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <filesystem>

// Include necessary headers
#include "GlobalParams.h"
#include "fofi/FoFiIdentifier.h"
#include "fofi/FoFiTrueType.h"
#include "poppler/Error.h"

// Since supportedFontForEmbedding is a static function in GlobalParams.cc,
// we need to either have it exposed or test it through the public interface.
// Based on the partial code, we'll assume it's accessible for testing.
// If it's truly static (file-local), we'd need to include the .cc file or
// have it exposed via a header. For this test, we assume it's declared somewhere accessible.

// Forward declaration if needed
extern bool supportedFontForEmbedding(Unicode uChar, const char *filepath, int faceIndex);

// Helper to create a temporary file with given content and extension
class TempFile {
public:
    TempFile(const std::string &extension, const std::vector<uint8_t> &content = {}) {
        filepath_ = std::filesystem::temp_directory_path() / ("test_font_XXXXXX" + extension);
        // Create a unique name
        static int counter = 0;
        filepath_ = std::filesystem::temp_directory_path() / ("test_font_" + std::to_string(counter++) + extension);
        std::ofstream ofs(filepath_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(reinterpret_cast<const char *>(content.data()), content.size());
        }
        ofs.close();
    }

    ~TempFile() {
        std::filesystem::remove(filepath_);
    }

    const char *path() const { return filepath_.c_str(); }

private:
    std::filesystem::path filepath_;
};

// Test fixture
class SupportedFontForEmbeddingTest_1902 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Unsupported file extension (.pfb) should return false
TEST_F(SupportedFontForEmbeddingTest_1902, UnsupportedExtensionPFB_1902) {
    TempFile tmp(".pfb");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Unsupported file extension (.pfa) should return false
TEST_F(SupportedFontForEmbeddingTest_1902, UnsupportedExtensionPFA_1902) {
    TempFile tmp(".pfa");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Unsupported file extension (.woff) should return false
TEST_F(SupportedFontForEmbeddingTest_1902, UnsupportedExtensionWOFF_1902) {
    TempFile tmp(".woff");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Unsupported file extension (no extension) should return false
TEST_F(SupportedFontForEmbeddingTest_1902, NoExtension_1902) {
    TempFile tmp("");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: .txt extension should return false
TEST_F(SupportedFontForEmbeddingTest_1902, UnsupportedExtensionTXT_1902) {
    TempFile tmp(".txt");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: .ttf extension but empty/invalid file content should return false
// (FoFiIdentifier won't identify it as a valid TrueType font)
TEST_F(SupportedFontForEmbeddingTest_1902, TTFExtensionInvalidContent_1902) {
    TempFile tmp(".ttf", {0x00, 0x00, 0x00, 0x00});
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: .ttc extension but empty/invalid file content should return false
TEST_F(SupportedFontForEmbeddingTest_1902, TTCExtensionInvalidContent_1902) {
    TempFile tmp(".ttc", {0x00, 0x00, 0x00, 0x00});
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: .otf extension but empty/invalid file content should return false
TEST_F(SupportedFontForEmbeddingTest_1902, OTFExtensionInvalidContent_1902) {
    TempFile tmp(".otf", {0x00, 0x00, 0x00, 0x00});
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: .ttf extension but file doesn't exist should return false
TEST_F(SupportedFontForEmbeddingTest_1902, TTFNonexistentFile_1902) {
    EXPECT_FALSE(supportedFontForEmbedding('A', "/nonexistent/path/font.ttf", 0));
}

// Test: .otf extension but file doesn't exist should return false
TEST_F(SupportedFontForEmbeddingTest_1902, OTFNonexistentFile_1902) {
    EXPECT_FALSE(supportedFontForEmbedding('A', "/nonexistent/path/font.otf", 0));
}

// Test: .ttc extension but file doesn't exist should return false
TEST_F(SupportedFontForEmbeddingTest_1902, TTCNonexistentFile_1902) {
    EXPECT_FALSE(supportedFontForEmbedding('A', "/nonexistent/path/font.ttc", 0));
}

// Test: .ttf with random garbage that looks like TTF header but isn't valid
TEST_F(SupportedFontForEmbeddingTest_1902, TTFGarbageContent_1902) {
    // TrueType starts with 0x00010000 or 'true'
    std::vector<uint8_t> fakeHeader = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TempFile tmp(".ttf", fakeHeader);
    // Even if identified, loading may fail
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Empty file with .ttf extension
TEST_F(SupportedFontForEmbeddingTest_1902, TTFEmptyFile_1902) {
    TempFile tmp(".ttf");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Empty file with .otf extension
TEST_F(SupportedFontForEmbeddingTest_1902, OTFEmptyFile_1902) {
    TempFile tmp(".otf");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Empty file with .ttc extension
TEST_F(SupportedFontForEmbeddingTest_1902, TTCEmptyFile_1902) {
    TempFile tmp(".ttc");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Extension is case-sensitive - .TTF should return false
TEST_F(SupportedFontForEmbeddingTest_1902, UppercaseTTFExtension_1902) {
    TempFile tmp(".TTF");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Extension is case-sensitive - .OTF should return false
TEST_F(SupportedFontForEmbeddingTest_1902, UppercaseOTFExtension_1902) {
    TempFile tmp(".OTF");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 0));
}

// Test: Unicode character 0 with invalid font
TEST_F(SupportedFontForEmbeddingTest_1902, ZeroUnicodeCharInvalidFont_1902) {
    TempFile tmp(".ttf");
    EXPECT_FALSE(supportedFontForEmbedding(0, tmp.path(), 0));
}

// Test: Negative face index with invalid font
TEST_F(SupportedFontForEmbeddingTest_1902, NegativeFaceIndexInvalidFont_1902) {
    TempFile tmp(".ttf");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), -1));
}

// Test: Large face index with invalid font
TEST_F(SupportedFontForEmbeddingTest_1902, LargeFaceIndexInvalidFont_1902) {
    TempFile tmp(".ttf");
    EXPECT_FALSE(supportedFontForEmbedding('A', tmp.path(), 9999));
}

// Test with a real system font if available (platform-dependent)
// This tests the happy path with a real TrueType font
class SupportedFontForEmbeddingRealFontTest_1902 : public ::testing::Test {
protected:
    std::string findSystemFont() {
        // Try common system font paths
        std::vector<std::string> candidates = {
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/TTF/DejaVuSans.ttf",
            "/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
            "/System/Library/Fonts/Helvetica.ttc",
            "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
            "C:\\Windows\\Fonts\\arial.ttf"
        };
        for (const auto &path : candidates) {
            if (std::filesystem::exists(path)) {
                return path;
            }
        }
        return "";
    }
};

TEST_F(SupportedFontForEmbeddingRealFontTest_1902, RealFontWithASCIIChar_1902) {
    std::string fontPath = findSystemFont();
    if (fontPath.empty()) {
        GTEST_SKIP() << "No system TrueType font found for testing";
    }
    // ASCII 'A' should be supported in most fonts
    bool result = supportedFontForEmbedding('A', fontPath.c_str(), 0);
    EXPECT_TRUE(result);
}

TEST_F(SupportedFontForEmbeddingRealFontTest_1902, RealFontWithSpaceChar_1902) {
    std::string fontPath = findSystemFont();
    if (fontPath.empty()) {
        GTEST_SKIP() << "No system TrueType font found for testing";
    }
    // Space character should be in most fonts
    bool result = supportedFontForEmbedding(' ', fontPath.c_str(), 0);
    EXPECT_TRUE(result);
}

TEST_F(SupportedFontForEmbeddingRealFontTest_1902, RealFontWithRareCJKChar_1902) {
    std::string fontPath = findSystemFont();
    if (fontPath.empty()) {
        GTEST_SKIP() << "No system TrueType font found for testing";
    }
    // A rare CJK unified ideograph that might not be in DejaVu
    // U+9FFF is at the end of the CJK range
    // This might return false for DejaVu fonts since they don't have CJK
    bool result = supportedFontForEmbedding(0x9FFF, fontPath.c_str(), 0);
    // We don't assert specific value - just verify it doesn't crash
    (void)result;
}

TEST_F(SupportedFontForEmbeddingRealFontTest_1902, RealFontWithNullChar_1902) {
    std::string fontPath = findSystemFont();
    if (fontPath.empty()) {
        GTEST_SKIP() << "No system TrueType font found for testing";
    }
    // Unicode null - glyph 0 maps to .notdef, so glyph > 0 check should fail
    bool result = supportedFontForEmbedding(0, fontPath.c_str(), 0);
    EXPECT_FALSE(result);
}

TEST_F(SupportedFontForEmbeddingRealFontTest_1902, RealFontWithInvalidFaceIndex_1902) {
    std::string fontPath = findSystemFont();
    if (fontPath.empty()) {
        GTEST_SKIP() << "No system TrueType font found for testing";
    }
    // Very large face index should fail to load
    bool result = supportedFontForEmbedding('A', fontPath.c_str(), 99999);
    EXPECT_FALSE(result);
}

TEST_F(SupportedFontForEmbeddingRealFontTest_1902, RealFontWithDigitChar_1902) {
    std::string fontPath = findSystemFont();
    if (fontPath.empty()) {
        GTEST_SKIP() << "No system TrueType font found for testing";
    }
    bool result = supportedFontForEmbedding('0', fontPath.c_str(), 0);
    EXPECT_TRUE(result);
}

TEST_F(SupportedFontForEmbeddingRealFontTest_1902, RealFontWithLatinChar_1902) {
    std::string fontPath = findSystemFont();
    if (fontPath.empty()) {
        GTEST_SKIP() << "No system TrueType font found for testing";
    }
    // Latin small letter a with acute (U+00E1)
    bool result = supportedFontForEmbedding(0x00E1, fontPath.c_str(), 0);
    EXPECT_TRUE(result);
}

// Test boundary: filepath ending exactly with supported extensions
TEST_F(SupportedFontForEmbeddingTest_1902, ExtensionBoundaryTTF_1902) {
    // A path that contains .ttf but not at the end
    EXPECT_FALSE(supportedFontForEmbedding('A', "/tmp/font.ttf.bak", 0));
}

TEST_F(SupportedFontForEmbeddingTest_1902, ExtensionBoundaryOTF_1902) {
    EXPECT_FALSE(supportedFontForEmbedding('A', "/tmp/font.otf.bak", 0));
}

TEST_F(SupportedFontForEmbeddingTest_1902, ExtensionBoundaryTTC_1902) {
    EXPECT_FALSE(supportedFontForEmbedding('A', "/tmp/font.ttc.bak", 0));
}
