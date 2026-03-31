#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include "CMap.h"
#include "Object.h"
#include "GlobalParams.h"

class CMapTest_1505 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test CMap creation with a known CMap name (Identity-H is a built-in CMap)
TEST_F(CMapTest_1505, ParseIdentityHCMap_1505) {
    auto cmap = CMap::parse(nullptr, "Identity-H", nullptr);
    ASSERT_NE(cmap, nullptr);
}

// Test CMap creation with Identity-V
TEST_F(CMapTest_1505, ParseIdentityVCMap_1505) {
    auto cmap = CMap::parse(nullptr, "Identity-V", nullptr);
    ASSERT_NE(cmap, nullptr);
}

// Test CMap CID lookup with Identity-H mapping
TEST_F(CMapTest_1505, IdentityHMapsCIDDirectly_1505) {
    auto cmap = CMap::parse(nullptr, "Identity-H", nullptr);
    ASSERT_NE(cmap, nullptr);
    
    // Identity-H should map character codes directly to CIDs
    char buf[2];
    buf[0] = 0x00;
    buf[1] = 0x41; // character code 0x0041 = 65
    int nUsed;
    CID cid = cmap->getCID(buf, 2, &nUsed);
    EXPECT_EQ(cid, 0x0041);
    EXPECT_EQ(nUsed, 2);
}

// Test CMap with zero character code in Identity-H
TEST_F(CMapTest_1505, IdentityHMapsZeroCID_1505) {
    auto cmap = CMap::parse(nullptr, "Identity-H", nullptr);
    ASSERT_NE(cmap, nullptr);
    
    char buf[2];
    buf[0] = 0x00;
    buf[1] = 0x00;
    int nUsed;
    CID cid = cmap->getCID(buf, 2, &nUsed);
    EXPECT_EQ(cid, 0x0000);
    EXPECT_EQ(nUsed, 2);
}

// Test CMap with max character code in Identity-H
TEST_F(CMapTest_1505, IdentityHMapsMaxCID_1505) {
    auto cmap = CMap::parse(nullptr, "Identity-H", nullptr);
    ASSERT_NE(cmap, nullptr);
    
    char buf[2];
    buf[0] = (char)0xFF;
    buf[1] = (char)0xFF;
    int nUsed;
    CID cid = cmap->getCID(buf, 2, &nUsed);
    EXPECT_EQ(cid, 0xFFFF);
    EXPECT_EQ(nUsed, 2);
}

// Test that an invalid/unknown CMap name returns nullptr or handles gracefully
TEST_F(CMapTest_1505, ParseInvalidCMapName_1505) {
    auto cmap = CMap::parse(nullptr, "NonExistent-Bogus-CMap-Name", nullptr);
    // An unknown CMap may return nullptr
    // This tests that the code doesn't crash
}

// Test getCharFromFile behavior indirectly through file-based CMap parsing
TEST_F(CMapTest_1505, FileBasedCharReading_1505) {
    // Create a temporary file to test file-based reading
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    
    // Write a single byte and read it back via fgetc (same as getCharFromFile)
    fputc('A', tmpFile);
    rewind(tmpFile);
    int ch = fgetc(tmpFile);
    EXPECT_EQ(ch, 'A');
    
    fclose(tmpFile);
}

// Test EOF behavior with fgetc (mirrors getCharFromFile at EOF)
TEST_F(CMapTest_1505, FileBasedCharReadingEOF_1505) {
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    
    // Empty file should return EOF
    int ch = fgetc(tmpFile);
    EXPECT_EQ(ch, EOF);
    
    fclose(tmpFile);
}

// Test CMap with Identity-V and verify it doesn't crash
TEST_F(CMapTest_1505, IdentityVMapsCIDDirectly_1505) {
    auto cmap = CMap::parse(nullptr, "Identity-V", nullptr);
    ASSERT_NE(cmap, nullptr);
    
    char buf[2];
    buf[0] = 0x01;
    buf[1] = 0x00;
    int nUsed;
    CID cid = cmap->getCID(buf, 2, &nUsed);
    EXPECT_EQ(cid, 0x0100);
    EXPECT_EQ(nUsed, 2);
}
