#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include <string>

#include "exiv2/basicio.hpp"

namespace fs = std::filesystem;

// Helper to create a temporary file with content
static std::string createTempFile(const std::string& suffix, const std::string& content = "hello world") {
    std::string path = fs::temp_directory_path().string() + "/exiv2_test_" + 
                       std::to_string(std::rand()) + suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(content.data(), content.size());
    ofs.close();
    return path;
}

// ==================== FileIo Tests ====================

class FileIoTest_596 : public ::testing::Test {
protected:
    std::string tempPath_;
    
    void SetUp() override {
        tempPath_ = createTempFile(".dat", "test content 1234");
    }
    
    void TearDown() override {
        if (fs::exists(tempPath_)) {
            fs::remove(tempPath_);
        }
    }
};

TEST_F(FileIoTest_596, ConstructorSetsPath_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.path(), tempPath_);
}

TEST_F(FileIoTest_596, OpenAndClose_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    EXPECT_TRUE(fio.isopen());
    EXPECT_EQ(fio.close(), 0);
    EXPECT_FALSE(fio.isopen());
}

TEST_F(FileIoTest_596, OpenWithMode_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open("rb"), 0);
    EXPECT_TRUE(fio.isopen());
    fio.close();
}

TEST_F(FileIoTest_596, OpenNonExistentFile_596) {
    Exiv2::FileIo fio("/nonexistent/path/to/file.dat");
    EXPECT_NE(fio.open(), 0);
    EXPECT_FALSE(fio.isopen());
}

TEST_F(FileIoTest_596, SizeReturnsCorrectValue_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    EXPECT_EQ(fio.size(), static_cast<size_t>(18)); // "test content 1234" is 18 bytes
    fio.close();
}

TEST_F(FileIoTest_596, ReadContent_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    Exiv2::byte buf[32] = {};
    size_t bytesRead = fio.read(buf, 18);
    EXPECT_EQ(bytesRead, 18u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 18), "test content 1234");
    fio.close();
}

TEST_F(FileIoTest_596, ReadDataBuf_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    Exiv2::DataBuf db = fio.read(18);
    EXPECT_EQ(db.size(), 18u);
    fio.close();
}

TEST_F(FileIoTest_596, SeekAndTell_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    EXPECT_EQ(fio.tell(), 0u);
    fio.seek(5, Exiv2::BasicIo::beg);
    EXPECT_EQ(fio.tell(), 5u);
    fio.seek(3, Exiv2::BasicIo::cur);
    EXPECT_EQ(fio.tell(), 8u);
    fio.seek(0, Exiv2::BasicIo::end);
    EXPECT_EQ(fio.tell(), 18u);
    fio.close();
}

TEST_F(FileIoTest_596, GetbReadsOneByte_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    int byte = fio.getb();
    EXPECT_EQ(byte, 't'); // first char of "test content 1234"
    EXPECT_EQ(fio.tell(), 1u);
    fio.close();
}

TEST_F(FileIoTest_596, PutbWritesOneByte_596) {
    {
        Exiv2::FileIo fio(tempPath_);
        EXPECT_EQ(fio.open("r+b"), 0);
        fio.seek(0, Exiv2::BasicIo::beg);
        EXPECT_EQ(fio.putb('X'), 0);
        fio.close();
    }
    {
        Exiv2::FileIo fio(tempPath_);
        EXPECT_EQ(fio.open(), 0);
        int byte = fio.getb();
        EXPECT_EQ(byte, 'X');
        fio.close();
    }
}

TEST_F(FileIoTest_596, WriteDataToFile_596) {
    std::string newPath = tempPath_ + ".write_test";
    {
        Exiv2::FileIo fio(newPath);
        EXPECT_EQ(fio.open("w+b"), 0);
        const std::string data = "written data";
        size_t written = fio.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
        EXPECT_EQ(written, data.size());
        fio.close();
    }
    // Verify
    {
        Exiv2::FileIo fio(newPath);
        EXPECT_EQ(fio.open(), 0);
        EXPECT_EQ(fio.size(), 12u);
        fio.close();
    }
    fs::remove(newPath);
}

TEST_F(FileIoTest_596, WriteFromBasicIo_596) {
    std::string srcPath = createTempFile(".src", "source data");
    std::string dstPath = tempPath_ + ".dst";
    {
        Exiv2::FileIo src(srcPath);
        Exiv2::FileIo dst(dstPath);
        EXPECT_EQ(src.open(), 0);
        EXPECT_EQ(dst.open("w+b"), 0);
        size_t written = dst.write(src);
        EXPECT_EQ(written, 11u); // "source data" is 11 bytes
        src.close();
        dst.close();
    }
    {
        Exiv2::FileIo dst(dstPath);
        EXPECT_EQ(dst.open(), 0);
        EXPECT_EQ(dst.size(), 11u);
        dst.close();
    }
    fs::remove(srcPath);
    fs::remove(dstPath);
}

TEST_F(FileIoTest_596, EofBehavior_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    EXPECT_FALSE(fio.eof());
    
    // Read past end
    fio.seek(0, Exiv2::BasicIo::end);
    Exiv2::byte buf[1];
    fio.read(buf, 1);
    EXPECT_TRUE(fio.eof());
    fio.close();
}

TEST_F(FileIoTest_596, ErrorOnClosedFile_596) {
    Exiv2::FileIo fio(tempPath_);
    // Don't open - operations on closed file
    EXPECT_FALSE(fio.isopen());
}

TEST_F(FileIoTest_596, SetPathChangesPath_596) {
    Exiv2::FileIo fio(tempPath_);
    std::string newPath = "/some/other/path.dat";
    fio.setPath(newPath);
    EXPECT_EQ(fio.path(), newPath);
}

TEST_F(FileIoTest_596, MmapAndMunmap_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    Exiv2::byte* data = fio.mmap(false);
    EXPECT_NE(data, nullptr);
    // First byte should be 't'
    EXPECT_EQ(data[0], 't');
    
    EXPECT_EQ(fio.munmap(), 0);
    fio.close();
}

TEST_F(FileIoTest_596, TransferFromAnotherFileIo_596) {
    std::string srcPath = createTempFile(".src2", "transferred data");
    {
        Exiv2::FileIo dst(tempPath_);
        Exiv2::FileIo src(srcPath);
        dst.transfer(src);
    }
    // After transfer, tempPath_ should have the transferred content
    {
        Exiv2::FileIo fio(tempPath_);
        EXPECT_EQ(fio.open(), 0);
        EXPECT_EQ(fio.size(), 16u); // "transferred data" is 16 bytes
        Exiv2::byte buf[32] = {};
        fio.read(buf, 16);
        EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 16), "transferred data");
        fio.close();
    }
    // srcPath may or may not exist after transfer depending on implementation
    if (fs::exists(srcPath)) {
        fs::remove(srcPath);
    }
}

TEST_F(FileIoTest_596, ReadMoreThanAvailable_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    Exiv2::byte buf[1024] = {};
    size_t bytesRead = fio.read(buf, 1024);
    EXPECT_EQ(bytesRead, 18u); // file only has 18 bytes
    fio.close();
}

TEST_F(FileIoTest_596, SeekBeyondEnd_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    // Seek beyond end - behavior may vary, but should not crash
    int result = fio.seek(1000, Exiv2::BasicIo::beg);
    // Just verify it doesn't crash; result may be 0 or error
    (void)result;
    fio.close();
}

TEST_F(FileIoTest_596, CloseAlreadyClosedFile_596) {
    Exiv2::FileIo fio(tempPath_);
    // Closing a file that was never opened
    int result = fio.close();
    // Should handle gracefully
    (void)result;
}

TEST_F(FileIoTest_596, ReadZeroBytes_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    Exiv2::byte buf[1];
    size_t bytesRead = fio.read(buf, 0);
    EXPECT_EQ(bytesRead, 0u);
    fio.close();
}

TEST_F(FileIoTest_596, WriteZeroBytes_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open("r+b"), 0);
    
    const Exiv2::byte data[] = {0};
    size_t written = fio.write(data, 0);
    EXPECT_EQ(written, 0u);
    fio.close();
}

TEST_F(FileIoTest_596, SizeWithoutOpen_596) {
    Exiv2::FileIo fio(tempPath_);
    // size() should work even without open (reads from filesystem)
    size_t sz = fio.size();
    EXPECT_EQ(sz, 18u);
}

// ==================== BasicIo readOrThrow and seekOrThrow Tests ====================

class BasicIoThrowTest_596 : public ::testing::Test {
protected:
    std::string tempPath_;
    
    void SetUp() override {
        tempPath_ = createTempFile(".throw_test", "abcdefgh");
    }
    
    void TearDown() override {
        if (fs::exists(tempPath_)) {
            fs::remove(tempPath_);
        }
    }
};

TEST_F(BasicIoThrowTest_596, ReadOrThrowSucceeds_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    Exiv2::byte buf[8];
    EXPECT_NO_THROW(fio.readOrThrow(buf, 8, Exiv2::ErrorCode::kerFailedToReadImageData));
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 8), "abcdefgh");
    fio.close();
}

TEST_F(BasicIoThrowTest_596, ReadOrThrowThrowsOnShortRead_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    Exiv2::byte buf[100];
    // Trying to read more bytes than available should throw
    EXPECT_THROW(fio.readOrThrow(buf, 100, Exiv2::ErrorCode::kerFailedToReadImageData), Exiv2::Error);
    fio.close();
}

TEST_F(BasicIoThrowTest_596, SeekOrThrowSucceeds_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    
    EXPECT_NO_THROW(fio.seekOrThrow(4, Exiv2::BasicIo::beg, Exiv2::ErrorCode::kerFailedToReadImageData));
    EXPECT_EQ(fio.tell(), 4u);
    fio.close();
}

// ==================== Empty File Tests ====================

class FileIoEmptyTest_596 : public ::testing::Test {
protected:
    std::string tempPath_;
    
    void SetUp() override {
        tempPath_ = createTempFile(".empty", "");
    }
    
    void TearDown() override {
        if (fs::exists(tempPath_)) {
            fs::remove(tempPath_);
        }
    }
};

TEST_F(FileIoEmptyTest_596, EmptyFileSize_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    EXPECT_EQ(fio.size(), 0u);
    fio.close();
}

TEST_F(FileIoEmptyTest_596, GetbOnEmptyFileReturnsEof_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    int result = fio.getb();
    EXPECT_EQ(result, EOF);
    fio.close();
}

TEST_F(FileIoEmptyTest_596, ReadFromEmptyFile_596) {
    Exiv2::FileIo fio(tempPath_);
    EXPECT_EQ(fio.open(), 0);
    Exiv2::byte buf[10];
    size_t bytesRead = fio.read(buf, 10);
    EXPECT_EQ(bytesRead, 0u);
    fio.close();
}
