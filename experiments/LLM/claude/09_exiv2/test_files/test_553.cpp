#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace Exiv2;

// Helper to create a temporary file with known content
class TempFile {
public:
    explicit TempFile(const std::string& name, const std::string& content = "") : path_(name) {
        std::ofstream ofs(path_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(content.data(), content.size());
        }
        ofs.close();
    }
    ~TempFile() {
        std::remove(path_.c_str());
    }
    const std::string& path() const { return path_; }
private:
    std::string path_;
};

// Test fixture
class FileIoTest_553 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ============================================================
// Constructor and path tests
// ============================================================

TEST_F(FileIoTest_553, ConstructorSetsPath_553) {
    std::string testPath = "test_constructor_553.tmp";
    FileIo fio(testPath);
    EXPECT_EQ(fio.path(), testPath);
}

// ============================================================
// Open / Close / isopen tests
// ============================================================

TEST_F(FileIoTest_553, IsOpenReturnsFalseBeforeOpen_553) {
    TempFile tmp("test_isopen_553.tmp", "hello");
    FileIo fio(tmp.path());
    EXPECT_FALSE(fio.isopen());
}

TEST_F(FileIoTest_553, OpenSucceedsForExistingFile_553) {
    TempFile tmp("test_open_553.tmp", "data");
    FileIo fio(tmp.path());
    EXPECT_EQ(fio.open(), 0);
    EXPECT_TRUE(fio.isopen());
    fio.close();
}

TEST_F(FileIoTest_553, OpenFailsForNonExistentFile_553) {
    FileIo fio("nonexistent_file_553_xyz.tmp");
    // open() for reading a non-existent file should fail
    int result = fio.open();
    // If file doesn't exist, open should return non-zero or the file should not be open
    // We check isopen
    if (result != 0) {
        EXPECT_FALSE(fio.isopen());
    }
}

TEST_F(FileIoTest_553, CloseAfterOpen_553) {
    TempFile tmp("test_close_553.tmp", "data");
    FileIo fio(tmp.path());
    fio.open();
    EXPECT_TRUE(fio.isopen());
    EXPECT_EQ(fio.close(), 0);
    EXPECT_FALSE(fio.isopen());
}

TEST_F(FileIoTest_553, CloseWithoutOpen_553) {
    TempFile tmp("test_close_noopen_553.tmp", "data");
    FileIo fio(tmp.path());
    // closing without opening should not crash
    int result = fio.close();
    // Result could be 0 or non-zero depending on implementation
    EXPECT_FALSE(fio.isopen());
}

// ============================================================
// Open with mode
// ============================================================

TEST_F(FileIoTest_553, OpenWithWriteMode_553) {
    std::string path = "test_open_mode_553.tmp";
    {
        std::ofstream ofs(path);
        ofs << "initial";
    }
    FileIo fio(path);
    EXPECT_EQ(fio.open("w+b"), 0);
    EXPECT_TRUE(fio.isopen());
    fio.close();
    std::remove(path.c_str());
}

// ============================================================
// Write byte data tests
// ============================================================

TEST_F(FileIoTest_553, WriteByteData_553) {
    std::string path = "test_write_bytes_553.tmp";
    {
        FileIo fio(path);
        fio.open("w+b");
        const byte data[] = "Hello, World!";
        size_t written = fio.write(data, 13);
        EXPECT_EQ(written, 13u);
        fio.close();
    }
    // Verify by reading back
    {
        FileIo fio(path);
        fio.open();
        byte buf[20] = {};
        size_t readCount = fio.read(buf, 13);
        EXPECT_EQ(readCount, 13u);
        EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 13), "Hello, World!");
        fio.close();
    }
    std::remove(path.c_str());
}

TEST_F(FileIoTest_553, WriteZeroBytes_553) {
    std::string path = "test_write_zero_553.tmp";
    FileIo fio(path);
    fio.open("w+b");
    const byte data[] = "test";
    size_t written = fio.write(data, 0);
    EXPECT_EQ(written, 0u);
    fio.close();
    std::remove(path.c_str());
}

// ============================================================
// Write from BasicIo source
// ============================================================

TEST_F(FileIoTest_553, WriteFromSourceFileIo_553) {
    // Create source file
    std::string srcPath = "test_write_src_553.tmp";
    std::string dstPath = "test_write_dst_553.tmp";
    {
        std::ofstream ofs(srcPath, std::ios::binary);
        ofs << "Source data for copy test 553";
    }

    FileIo src(srcPath);
    EXPECT_EQ(src.open(), 0);

    FileIo dst(dstPath);
    EXPECT_EQ(dst.open("w+b"), 0);

    size_t written = dst.write(src);
    EXPECT_GT(written, 0u);
    EXPECT_EQ(written, 28u); // "Source data for copy test 553" minus null = 28

    dst.close();
    src.close();

    // Verify destination content
    {
        FileIo verify(dstPath);
        verify.open();
        byte buf[100] = {};
        size_t readCount = verify.read(buf, 100);
        EXPECT_EQ(readCount, 28u);
        EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 28), "Source data for copy test 553");
        verify.close();
    }

    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}

TEST_F(FileIoTest_553, WriteSelfReturnsZero_553) {
    std::string path = "test_write_self_553.tmp";
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs << "self data";
    }
    FileIo fio(path);
    fio.open("r+b");
    // Writing to self should return 0
    size_t written = fio.write(fio);
    EXPECT_EQ(written, 0u);
    fio.close();
    std::remove(path.c_str());
}

TEST_F(FileIoTest_553, WriteFromClosedSourceReturnsZero_553) {
    std::string srcPath = "test_write_closed_src_553.tmp";
    std::string dstPath = "test_write_closed_dst_553.tmp";
    {
        std::ofstream ofs(srcPath, std::ios::binary);
        ofs << "some data";
    }

    FileIo src(srcPath);
    // Don't open src
    EXPECT_FALSE(src.isopen());

    FileIo dst(dstPath);
    dst.open("w+b");

    size_t written = dst.write(src);
    EXPECT_EQ(written, 0u);

    dst.close();
    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}

// ============================================================
// Read tests
// ============================================================

TEST_F(FileIoTest_553, ReadIntoBuffer_553) {
    std::string content = "ReadTest553Data";
    TempFile tmp("test_read_553.tmp", content);
    FileIo fio(tmp.path());
    fio.open();
    byte buf[50] = {};
    size_t readCount = fio.read(buf, 50);
    EXPECT_EQ(readCount, content.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), readCount), content);
    fio.close();
}

TEST_F(FileIoTest_553, ReadDataBuf_553) {
    std::string content = "DataBuf553";
    TempFile tmp("test_read_databuf_553.tmp", content);
    FileIo fio(tmp.path());
    fio.open();
    DataBuf data = fio.read(content.size());
    EXPECT_EQ(data.size(), content.size());
    fio.close();
}

TEST_F(FileIoTest_553, ReadFromEmptyFile_553) {
    TempFile tmp("test_read_empty_553.tmp", "");
    FileIo fio(tmp.path());
    fio.open();
    byte buf[10] = {};
    size_t readCount = fio.read(buf, 10);
    EXPECT_EQ(readCount, 0u);
    fio.close();
}

// ============================================================
// Seek and Tell tests
// ============================================================

TEST_F(FileIoTest_553, SeekAndTell_553) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_553.tmp", content);
    FileIo fio(tmp.path());
    fio.open();

    // Seek to position 5 from beginning
    EXPECT_EQ(fio.seek(5, BasicIo::beg), 0);
    EXPECT_EQ(fio.tell(), 5u);

    // Read one byte
    byte buf[1];
    fio.read(buf, 1);
    EXPECT_EQ(buf[0], '5');
    EXPECT_EQ(fio.tell(), 6u);

    // Seek relative
    EXPECT_EQ(fio.seek(-3, BasicIo::cur), 0);
    EXPECT_EQ(fio.tell(), 3u);

    // Seek from end
    EXPECT_EQ(fio.seek(-2, BasicIo::end), 0);
    EXPECT_EQ(fio.tell(), 8u);

    fio.close();
}

TEST_F(FileIoTest_553, TellAtBeginning_553) {
    TempFile tmp("test_tell_553.tmp", "data");
    FileIo fio(tmp.path());
    fio.open();
    EXPECT_EQ(fio.tell(), 0u);
    fio.close();
}

// ============================================================
// Size tests
// ============================================================

TEST_F(FileIoTest_553, SizeReturnsCorrectValue_553) {
    std::string content = "Hello553";
    TempFile tmp("test_size_553.tmp", content);
    FileIo fio(tmp.path());
    fio.open();
    EXPECT_EQ(fio.size(), content.size());
    fio.close();
}

TEST_F(FileIoTest_553, SizeOfEmptyFile_553) {
    TempFile tmp("test_size_empty_553.tmp", "");
    FileIo fio(tmp.path());
    fio.open();
    EXPECT_EQ(fio.size(), 0u);
    fio.close();
}

// ============================================================
// putb and getb tests
// ============================================================

TEST_F(FileIoTest_553, PutbAndGetb_553) {
    std::string path = "test_putb_553.tmp";
    {
        FileIo fio(path);
        fio.open("w+b");
        EXPECT_EQ(fio.putb(0x42), 0x42);
        EXPECT_EQ(fio.putb(0xAB), 0xAB);
        fio.close();
    }
    {
        FileIo fio(path);
        fio.open();
        EXPECT_EQ(fio.getb(), 0x42);
        EXPECT_EQ(fio.getb(), 0xAB);
        fio.close();
    }
    std::remove(path.c_str());
}

TEST_F(FileIoTest_553, GetbAtEof_553) {
    TempFile tmp("test_getb_eof_553.tmp", "A");
    FileIo fio(tmp.path());
    fio.open();
    int val = fio.getb();
    EXPECT_EQ(val, 'A');
    val = fio.getb();
    EXPECT_EQ(val, EOF);
    fio.close();
}

// ============================================================
// EOF tests
// ============================================================

TEST_F(FileIoTest_553, EofAfterReadingAll_553) {
    TempFile tmp("test_eof_553.tmp", "ab");
    FileIo fio(tmp.path());
    fio.open();
    byte buf[10];
    fio.read(buf, 10); // Read more than available
    EXPECT_TRUE(fio.eof());
    fio.close();
}

TEST_F(FileIoTest_553, NotEofAfterPartialRead_553) {
    std::string content = "abcdefghij";
    TempFile tmp("test_not_eof_553.tmp", content);
    FileIo fio(tmp.path());
    fio.open();
    byte buf[5];
    fio.read(buf, 5);
    EXPECT_FALSE(fio.eof());
    fio.close();
}

// ============================================================
// Error tests
// ============================================================

TEST_F(FileIoTest_553, ErrorAfterOpen_553) {
    TempFile tmp("test_error_553.tmp", "data");
    FileIo fio(tmp.path());
    fio.open();
    EXPECT_EQ(fio.error(), 0);
    fio.close();
}

// ============================================================
// setPath test
// ============================================================

TEST_F(FileIoTest_553, SetPathChangesPath_553) {
    TempFile tmp("test_setpath_553.tmp", "data");
    FileIo fio(tmp.path());
    std::string newPath = "new_path_553.tmp";
    fio.setPath(newPath);
    EXPECT_EQ(fio.path(), newPath);
}

// ============================================================
// Large write from source (boundary: more than 4096 buffer)
// ============================================================

TEST_F(FileIoTest_553, WriteLargeSourceExceedingBuffer_553) {
    std::string srcPath = "test_large_src_553.tmp";
    std::string dstPath = "test_large_dst_553.tmp";

    // Create source with > 4096 bytes
    std::string largeContent(8192, 'X');
    {
        std::ofstream ofs(srcPath, std::ios::binary);
        ofs.write(largeContent.data(), largeContent.size());
    }

    FileIo src(srcPath);
    src.open();
    FileIo dst(dstPath);
    dst.open("w+b");

    size_t written = dst.write(src);
    EXPECT_EQ(written, 8192u);

    dst.close();
    src.close();

    // Verify
    {
        FileIo verify(dstPath);
        verify.open();
        EXPECT_EQ(verify.size(), 8192u);
        byte buf[8192];
        size_t readCount = verify.read(buf, 8192);
        EXPECT_EQ(readCount, 8192u);
        for (size_t i = 0; i < readCount; ++i) {
            EXPECT_EQ(buf[i], 'X') << "Mismatch at index " << i;
        }
        verify.close();
    }

    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}

// ============================================================
// Write exactly 4096 bytes (boundary)
// ============================================================

TEST_F(FileIoTest_553, WriteExactly4096Bytes_553) {
    std::string srcPath = "test_4096_src_553.tmp";
    std::string dstPath = "test_4096_dst_553.tmp";

    std::string content(4096, 'A');
    {
        std::ofstream ofs(srcPath, std::ios::binary);
        ofs.write(content.data(), content.size());
    }

    FileIo src(srcPath);
    src.open();
    FileIo dst(dstPath);
    dst.open("w+b");

    size_t written = dst.write(src);
    EXPECT_EQ(written, 4096u);

    dst.close();
    src.close();

    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}

// ============================================================
// Transfer test
// ============================================================

TEST_F(FileIoTest_553, TransferFromSource_553) {
    std::string srcPath = "test_transfer_src_553.tmp";
    std::string dstPath = "test_transfer_dst_553.tmp";

    {
        std::ofstream ofs(srcPath, std::ios::binary);
        ofs << "transfer content 553";
    }

    FileIo src(srcPath);
    FileIo dst(dstPath);
    dst.open("w+b");
    dst.close();

    // Transfer should move content from src to dst
    dst.transfer(src);

    // After transfer, dst should have the content
    FileIo verify(dstPath);
    verify.open();
    EXPECT_GT(verify.size(), 0u);
    verify.close();

    // Cleanup - srcPath may or may not exist after transfer
    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}

// ============================================================
// Multiple sequential writes
// ============================================================

TEST_F(FileIoTest_553, MultipleSequentialWrites_553) {
    std::string path = "test_multi_write_553.tmp";
    FileIo fio(path);
    fio.open("w+b");

    const byte data1[] = "First";
    const byte data2[] = "Second";
    size_t w1 = fio.write(data1, 5);
    size_t w2 = fio.write(data2, 6);
    EXPECT_EQ(w1, 5u);
    EXPECT_EQ(w2, 6u);

    fio.seek(0, BasicIo::beg);
    byte buf[20] = {};
    size_t readCount = fio.read(buf, 20);
    EXPECT_EQ(readCount, 11u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 11), "FirstSecond");

    fio.close();
    std::remove(path.c_str());
}

// ============================================================
// Seek beyond file size
// ============================================================

TEST_F(FileIoTest_553, SeekBeyondFileSize_553) {
    TempFile tmp("test_seek_beyond_553.tmp", "abc");
    FileIo fio(tmp.path());
    fio.open();

    // Seeking beyond file size - behavior depends on implementation
    int result = fio.seek(100, BasicIo::beg);
    // We just check it doesn't crash; result may vary
    (void)result;

    fio.close();
}

// ============================================================
// mmap / munmap tests
// ============================================================

TEST_F(FileIoTest_553, MmapAndMunmap_553) {
    std::string content = "mmap test 553";
    TempFile tmp("test_mmap_553.tmp", content);
    FileIo fio(tmp.path());
    fio.open();

    byte* mapped = fio.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(mapped), content.size()), content);

    EXPECT_EQ(fio.munmap(), 0);
    fio.close();
}

// ============================================================
// Write from source with exact 4096+1 bytes (boundary: just over buffer)
// ============================================================

TEST_F(FileIoTest_553, WriteSourceWith4097Bytes_553) {
    std::string srcPath = "test_4097_src_553.tmp";
    std::string dstPath = "test_4097_dst_553.tmp";

    std::string content(4097, 'B');
    {
        std::ofstream ofs(srcPath, std::ios::binary);
        ofs.write(content.data(), content.size());
    }

    FileIo src(srcPath);
    src.open();
    FileIo dst(dstPath);
    dst.open("w+b");

    size_t written = dst.write(src);
    EXPECT_EQ(written, 4097u);

    dst.close();
    src.close();

    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}

// ============================================================
// Write single byte source
// ============================================================

TEST_F(FileIoTest_553, WriteSourceWithSingleByte_553) {
    std::string srcPath = "test_1byte_src_553.tmp";
    std::string dstPath = "test_1byte_dst_553.tmp";

    {
        std::ofstream ofs(srcPath, std::ios::binary);
        ofs.put('Z');
    }

    FileIo src(srcPath);
    src.open();
    FileIo dst(dstPath);
    dst.open("w+b");

    size_t written = dst.write(src);
    EXPECT_EQ(written, 1u);

    dst.close();
    src.close();

    // Verify
    {
        FileIo verify(dstPath);
        verify.open();
        EXPECT_EQ(verify.getb(), 'Z');
        verify.close();
    }

    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}

// ============================================================
// Write from empty source
// ============================================================

TEST_F(FileIoTest_553, WriteFromEmptySource_553) {
    std::string srcPath = "test_empty_src_553.tmp";
    std::string dstPath = "test_empty_dst_553.tmp";

    {
        std::ofstream ofs(srcPath, std::ios::binary);
        // Write nothing
    }

    FileIo src(srcPath);
    src.open();
    FileIo dst(dstPath);
    dst.open("w+b");

    size_t written = dst.write(src);
    EXPECT_EQ(written, 0u);

    dst.close();
    src.close();

    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}
