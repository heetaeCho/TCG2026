#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/exiv2.hpp>
#include <exiv2/basicio.hpp>

namespace {

// Helper to create a TGA file with TRUEVISION-XFILE footer
std::vector<Exiv2::byte> createTgaWithFooter(size_t totalSize = 100) {
    std::vector<Exiv2::byte> data(totalSize, 0);
    // The footer is the last 26 bytes
    // bytes [size-26 .. size-26+7] = extension/developer offsets (don't care)
    // bytes [size-18 .. size-18+15] = "TRUEVISION-XFILE"
    // bytes [size-2] = '.'
    // bytes [size-1] = '\0'
    if (totalSize >= 26) {
        const char* sig = "TRUEVISION-XFILE";
        std::memcpy(data.data() + totalSize - 26 + 8, sig, 16);
        data[totalSize - 2] = '.';
        data[totalSize - 1] = '\0';
    }
    return data;
}

// Helper to create a TGA file without the TRUEVISION-XFILE footer
std::vector<Exiv2::byte> createTgaWithoutFooter(size_t totalSize = 100) {
    std::vector<Exiv2::byte> data(totalSize, 0);
    // Fill footer area with garbage
    if (totalSize >= 26) {
        const char* sig = "NOT_A_TGA_FOOTER";
        std::memcpy(data.data() + totalSize - 26 + 8, sig, 16);
    }
    return data;
}

class IsTgaTypeTest_1234 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: File with .tga extension should be recognized as TGA regardless of content
TEST_F(IsTgaTypeTest_1234, TgaExtensionLowerCase_1234) {
    // Create a temporary file with .tga extension
    std::string path = "/tmp/test_tga_lower.tga";
    std::vector<Exiv2::byte> data(100, 0); // No valid footer
    
    // Write data to file
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_TRUE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: File with .TGA extension should be recognized as TGA regardless of content
TEST_F(IsTgaTypeTest_1234, TgaExtensionUpperCase_1234) {
    std::string path = "/tmp/test_tga_upper.TGA";
    std::vector<Exiv2::byte> data(100, 0);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_TRUE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: File without .tga extension but with valid TRUEVISION-XFILE footer
TEST_F(IsTgaTypeTest_1234, NonTgaExtensionWithValidFooter_1234) {
    std::string path = "/tmp/test_tga_valid_footer.bin";
    auto data = createTgaWithFooter(100);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    // We need to position the cursor somewhere >= 26
    // After open, tell() returns 0 which is < 26, so we need to seek first
    io.seek(0, Exiv2::BasicIo::end);
    size_t fileSize = io.tell();
    // Seek to a position >= 26
    io.seek(50, Exiv2::BasicIo::beg);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_TRUE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: File without .tga extension and without valid footer
TEST_F(IsTgaTypeTest_1234, NonTgaExtensionWithInvalidFooter_1234) {
    std::string path = "/tmp/test_tga_invalid_footer.bin";
    auto data = createTgaWithoutFooter(100);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    // Seek to position >= 26
    io.seek(50, Exiv2::BasicIo::beg);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_FALSE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: File position less than 26 and no .tga extension should return false
TEST_F(IsTgaTypeTest_1234, CurPosLessThan26NoTgaExtension_1234) {
    std::string path = "/tmp/test_tga_small_pos.bin";
    auto data = createTgaWithFooter(100);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    // tell() should be 0 after open, which is < 26
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_FALSE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: Current position is restored after the call
TEST_F(IsTgaTypeTest_1234, PositionRestoredAfterCall_1234) {
    std::string path = "/tmp/test_tga_pos_restore.bin";
    auto data = createTgaWithFooter(100);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    io.seek(50, Exiv2::BasicIo::beg);
    size_t posBefore = io.tell();
    
    Exiv2::isTgaType(io, false);
    
    size_t posAfter = io.tell();
    EXPECT_EQ(posBefore, posAfter);
    
    io.close();
    std::remove(path.c_str());
}

// Test: Exactly 26 bytes file with valid footer, curPos at 26
TEST_F(IsTgaTypeTest_1234, ExactlyMinimumSizeWithValidFooter_1234) {
    std::string path = "/tmp/test_tga_exact26.bin";
    auto data = createTgaWithFooter(26);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    // Seek to end to get curPos = 26
    io.seek(0, Exiv2::BasicIo::end);
    ASSERT_EQ(io.tell(), 26u);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_TRUE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: curPos exactly at 26 boundary
TEST_F(IsTgaTypeTest_1234, CurPosExactly26_1234) {
    std::string path = "/tmp/test_tga_pos26.bin";
    auto data = createTgaWithFooter(100);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    io.seek(26, Exiv2::BasicIo::beg);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_TRUE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: curPos at 25 (just below threshold) without .tga extension
TEST_F(IsTgaTypeTest_1234, CurPosAt25ReturnsFalse_1234) {
    std::string path = "/tmp/test_tga_pos25.bin";
    auto data = createTgaWithFooter(100);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    io.seek(25, Exiv2::BasicIo::beg);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_FALSE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: MemIo with .tga path (MemIo has empty path by default, so use FileIo)
// Test with mixed case extension like .Tga should NOT match
TEST_F(IsTgaTypeTest_1234, MixedCaseExtensionNotMatched_1234) {
    std::string path = "/tmp/test_tga_mixed.Tga";
    auto data = createTgaWithoutFooter(100);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    io.seek(50, Exiv2::BasicIo::beg);
    
    // .Tga is neither .tga nor .TGA, so it depends on footer
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_FALSE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: Large file with valid footer
TEST_F(IsTgaTypeTest_1234, LargeFileWithValidFooter_1234) {
    std::string path = "/tmp/test_tga_large.bin";
    auto data = createTgaWithFooter(10000);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    io.seek(5000, Exiv2::BasicIo::beg);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_TRUE(result);
    
    io.close();
    std::remove(path.c_str());
}

// Test: advance parameter is ignored (pass true)
TEST_F(IsTgaTypeTest_1234, AdvanceParameterIgnored_1234) {
    std::string path = "/tmp/test_tga_advance.tga";
    std::vector<Exiv2::byte> data(100, 0);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    
    bool resultFalse = Exiv2::isTgaType(io, false);
    bool resultTrue = Exiv2::isTgaType(io, true);
    
    // Both should return true since path ends with .tga
    EXPECT_TRUE(resultFalse);
    EXPECT_TRUE(resultTrue);
    
    io.close();
    std::remove(path.c_str());
}

// Test: File with partial TRUEVISION-XFILE string should not match
TEST_F(IsTgaTypeTest_1234, PartialFooterSignatureNoMatch_1234) {
    std::string path = "/tmp/test_tga_partial.bin";
    std::vector<Exiv2::byte> data(100, 0);
    // Put partial signature
    const char* partial = "TRUEVISION-XFIL\0"; // One char short
    std::memcpy(data.data() + 100 - 26 + 8, partial, 16);
    
    {
        FILE* f = fopen(path.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
    
    Exiv2::FileIo io(path);
    ASSERT_EQ(io.open(), 0);
    io.seek(50, Exiv2::BasicIo::beg);
    
    bool result = Exiv2::isTgaType(io, false);
    EXPECT_FALSE(result);
    
    io.close();
    std::remove(path.c_str());
}

} // namespace
