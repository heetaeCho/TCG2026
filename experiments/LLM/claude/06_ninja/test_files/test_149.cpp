#include "gtest/gtest.h"
#include <string>
#include <vector>

// Include necessary headers
#include "string_piece.h"

// We need to include or forward declare the MountPoint struct
// Since it's defined in util.cc, we need to include the appropriate header
#include "util.h"

// If util.h doesn't expose MountPoint, we may need to include util.cc directly
// or replicate the struct definition. Based on the prompt, we test the interface as given.

class MountPointTranslateTest_149 : public ::testing::Test {
protected:
    MountPoint mp;
    
    void SetUp() override {
        // Default setup - we'll customize per test
    }
    
    void SetMountPointFields(const std::string& rootStr, const std::string& mountPointStr) {
        // Store strings so they remain valid
        rootStorage = rootStr;
        mountPointStorage = mountPointStr;
        mp.root = StringPiece(rootStorage.data(), rootStorage.size());
        mp.mountPoint = StringPiece(mountPointStorage.data(), mountPointStorage.size());
    }
    
    std::string rootStorage;
    std::string mountPointStorage;
};

// Test: Path that matches root prefix gets translated correctly
TEST_F(MountPointTranslateTest_149, BasicTranslation_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/root/subdir/file.txt";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/mnt//subdir/file.txt");
}

// Test: Path that does not match root prefix returns empty string
TEST_F(MountPointTranslateTest_149, NonMatchingPathReturnsEmpty_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/other/subdir/file.txt";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Path that after stripping root becomes ".." returns empty (directory traversal)
TEST_F(MountPointTranslateTest_149, DirectoryTraversalDoubleDotReturnsEmpty_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/root..";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Path that after stripping root starts with "../" returns empty
TEST_F(MountPointTranslateTest_149, DirectoryTraversalDoubleDotSlashReturnsEmpty_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/root../etc/passwd";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Path exactly matches root (remainder is empty)
TEST_F(MountPointTranslateTest_149, PathExactlyMatchesRoot_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/root";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/mnt/");
}

// Test: Empty root prefix matches any path
TEST_F(MountPointTranslateTest_149, EmptyRootMatchesAnyPath_149) {
    SetMountPointFields("", "/mnt");
    std::string path = "some/path";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/mnt/some/path");
}

// Test: Empty root with ".." path returns empty
TEST_F(MountPointTranslateTest_149, EmptyRootWithDoubleDotReturnsEmpty_149) {
    SetMountPointFields("", "/mnt");
    std::string path = "..";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Empty root with "../something" path returns empty
TEST_F(MountPointTranslateTest_149, EmptyRootWithDoubleDotSlashReturnsEmpty_149) {
    SetMountPointFields("", "/mnt");
    std::string path = "../something";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Path with root as "/" (single slash root)
TEST_F(MountPointTranslateTest_149, SingleSlashRoot_149) {
    SetMountPointFields("/", "/mnt");
    std::string path = "/home/user";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/mnt/home/user");
}

// Test: Single slash root with ".." after stripping
TEST_F(MountPointTranslateTest_149, SingleSlashRootWithDoubleDot_149) {
    SetMountPointFields("/", "/mnt");
    std::string path = "/..";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Single slash root with "../" after stripping
TEST_F(MountPointTranslateTest_149, SingleSlashRootWithDoubleDotSlash_149) {
    SetMountPointFields("/", "/mnt");
    std::string path = "/../etc";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Path that is a prefix of root but shorter returns empty
TEST_F(MountPointTranslateTest_149, PathShorterThanRootReturnsEmpty_149) {
    SetMountPointFields("/root/long", "/mnt");
    std::string path = "/root";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Remainder is a single dot (not "..")
TEST_F(MountPointTranslateTest_149, RemainderIsSingleDot_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/root.";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/mnt/.");
}

// Test: Remainder starts with "..." (not a traversal)
TEST_F(MountPointTranslateTest_149, RemainderIsTripleDot_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/root...";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/mnt/...");
}

// Test: Empty path with empty root
TEST_F(MountPointTranslateTest_149, EmptyPathEmptyRoot_149) {
    SetMountPointFields("", "/mnt");
    std::string path = "";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/mnt/");
}

// Test: Path modifies input (erase behavior)
TEST_F(MountPointTranslateTest_149, PathIsModifiedAfterTranslate_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/rootsubdir/file";
    std::string result = mp.translate(path);
    // After erasing the root prefix "/root", path should become "subdir/file"
    EXPECT_EQ(path, "subdir/file");
    EXPECT_EQ(result, "/mnt/subdir/file");
}

// Test: Non-matching path is NOT modified
TEST_F(MountPointTranslateTest_149, NonMatchingPathNotModified_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/other/path";
    std::string originalPath = path;
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
    EXPECT_EQ(path, originalPath);
}

// Test: Mount point is empty string
TEST_F(MountPointTranslateTest_149, EmptyMountPoint_149) {
    SetMountPointFields("/root", "");
    std::string path = "/rootfile.txt";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/file.txt");
}

// Test: Long path with deep nesting
TEST_F(MountPointTranslateTest_149, LongNestedPath_149) {
    SetMountPointFields("/a", "/b");
    std::string path = "/a/c/d/e/f/g";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/b//c/d/e/f/g");
}

// Test: Remainder exactly "../" (length 3, starts with "../")
TEST_F(MountPointTranslateTest_149, RemainderExactlyDoubleDotSlash_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/root../";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "");
}

// Test: Remainder is "..x" (starts with ".." but not "../" and length > 2)
TEST_F(MountPointTranslateTest_149, RemainderStartsWithDoubleDotButNotSlash_149) {
    SetMountPointFields("/root", "/mnt");
    std::string path = "/root..x";
    std::string result = mp.translate(path);
    EXPECT_EQ(result, "/mnt/..x");
}
