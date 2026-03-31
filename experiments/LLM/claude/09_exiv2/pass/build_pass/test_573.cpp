#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <vector>
#include <fstream>
#include <cstdio>

// Since BlockMap is a private/internal class within basicio.cpp, we test through
// the public BasicIo interface classes that use it (RemoteIo, HttpIo, etc.)
// We focus on the public BasicIo-derived classes that are available.

namespace {

// Helper to create a temporary file with known content
class TempFile {
public:
    TempFile(const std::string& name, const std::string& content) : name_(name) {
        std::ofstream ofs(name_, std::ios::binary);
        ofs.write(content.data(), content.size());
        ofs.close();
    }
    ~TempFile() {
        std::remove(name_.c_str());
    }
    const std::string& path() const { return name_; }
private:
    std::string name_;
};

} // anonymous namespace

// Tests for FileIo
class FileIoTest_573 : public ::testing::Test {
protected:
    void SetUp() override {
        testContent_ = "Hello, World! This is test content for FileIo.";
        tempFile_ = std::make_unique<TempFile>("test_fileio_573.tmp", testContent_);
    }
    void TearDown() override {
        tempFile_.reset();
    }
    std::string testContent_;
    std::unique_ptr<TempFile> tempFile_;
};

TEST_F(FileIoTest_573, OpenAndReadContent_573) {
    Exiv2::FileIo fileIo(tempFile_->path());
    ASSERT_EQ(0, fileIo.open());
    
    Exiv2::DataBuf buf = fileIo.read(testContent_.size());
    ASSERT_EQ(testContent_.size(), buf.size());
    EXPECT_EQ(0, std::memcmp(buf.data(), testContent_.data(), testContent_.size()));
    
    ASSERT_EQ(0, fileIo.close());
}

TEST_F(FileIoTest_573, SizeReturnsCorrectValue_573) {
    Exiv2::FileIo fileIo(tempFile_->path());
    ASSERT_EQ(0, fileIo.open());
    EXPECT_EQ(testContent_.size(), fileIo.size());
    fileIo.close();
}

TEST_F(FileIoTest_573, IsOpenReturnsTrueAfterOpen_573) {
    Exiv2::FileIo fileIo(tempFile_->path());
    EXPECT_FALSE(fileIo.isopen());
    ASSERT_EQ(0, fileIo.open());
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
    EXPECT_FALSE(fileIo.isopen());
}

TEST_F(FileIoTest_573, SeekAndTell_573) {
    Exiv2::FileIo fileIo(tempFile_->path());
    ASSERT_EQ(0, fileIo.open());
    
    // Seek from beginning
    EXPECT_EQ(0, fileIo.seek(5, Exiv2::BasicIo::beg));
    EXPECT_EQ(5, fileIo.tell());
    
    // Seek from current
    EXPECT_EQ(0, fileIo.seek(3, Exiv2::BasicIo::cur));
    EXPECT_EQ(8, fileIo.tell());
    
    // Seek from end
    EXPECT_EQ(0, fileIo.seek(0, Exiv2::BasicIo::end));
    EXPECT_EQ(static_cast<long>(testContent_.size()), fileIo.tell());
    
    fileIo.close();
}

TEST_F(FileIoTest_573, EofAfterReadingAll_573) {
    Exiv2::FileIo fileIo(tempFile_->path());
    ASSERT_EQ(0, fileIo.open());
    
    EXPECT_FALSE(fileIo.eof());
    fileIo.read(testContent_.size());
    // Read one more byte to trigger EOF
    Exiv2::byte oneByte;
    fileIo.read(&oneByte, 1);
    EXPECT_TRUE(fileIo.eof());
    
    fileIo.close();
}

TEST_F(FileIoTest_573, PathReturnsCorrectPath_573) {
    Exiv2::FileIo fileIo(tempFile_->path());
    EXPECT_EQ(tempFile_->path(), fileIo.path());
}

TEST_F(FileIoTest_573, OpenNonExistentFileFails_573) {
    Exiv2::FileIo fileIo("non_existent_file_573.tmp");
    EXPECT_NE(0, fileIo.open());
}

TEST_F(FileIoTest_573, WriteAndReadBack_573) {
    std::string writePath = "test_write_573.tmp";
    {
        Exiv2::FileIo fileIo(writePath);
        ASSERT_EQ(0, fileIo.open("wb"));
        
        std::string data = "Test write data";
        EXPECT_EQ(data.size(), fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size()));
        fileIo.close();
    }
    {
        Exiv2::FileIo fileIo(writePath);
        ASSERT_EQ(0, fileIo.open());
        Exiv2::DataBuf buf = fileIo.read(15);
        EXPECT_EQ(15u, buf.size());
        EXPECT_EQ(0, std::memcmp(buf.data(), "Test write data", 15));
        fileIo.close();
    }
    std::remove(writePath.c_str());
}

TEST_F(FileIoTest_573, ReadZeroBytes_573) {
    Exiv2::FileIo fileIo(tempFile_->path());
    ASSERT_EQ(0, fileIo.open());
    
    Exiv2::DataBuf buf = fileIo.read(0);
    EXPECT_EQ(0u, buf.size());
    EXPECT_EQ(0, fileIo.tell());
    
    fileIo.close();
}

TEST_F(FileIoTest_573, SeekBeyondEnd_573) {
    Exiv2::FileIo fileIo(tempFile_->path());
    ASSERT_EQ(0, fileIo.open());
    
    // Seeking beyond end is typically allowed but reading should return 0 bytes
    fileIo.seek(static_cast<long>(testContent_.size() + 100), Exiv2::BasicIo::beg);
    Exiv2::byte oneByte;
    long bytesRead = fileIo.read(&oneByte, 1);
    EXPECT_EQ(0, bytesRead);
    
    fileIo.close();
}

// Tests for MemIo
class MemIoTest_573 : public ::testing::Test {
protected:
    void SetUp() override {
        testData_ = "Memory IO test content 573";
    }
    std::string testData_;
};

TEST_F(MemIoTest_573, DefaultConstructorCreatesEmpty_573) {
    Exiv2::MemIo memIo;
    EXPECT_EQ(0u, memIo.size());
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_573, ConstructWithData_573) {
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(testData_.data()), testData_.size());
    EXPECT_EQ(testData_.size(), memIo.size());
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_573, ReadFromMemIo_573) {
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(testData_.data()), testData_.size());
    
    Exiv2::DataBuf buf = memIo.read(testData_.size());
    ASSERT_EQ(testData_.size(), buf.size());
    EXPECT_EQ(0, std::memcmp(buf.data(), testData_.data(), testData_.size()));
}

TEST_F(MemIoTest_573, WriteToMemIo_573) {
    Exiv2::MemIo memIo;
    
    std::string data = "Written data";
    size_t written = memIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(data.size(), written);
    EXPECT_EQ(data.size(), memIo.size());
    
    // Seek back and read
    memIo.seek(0, Exiv2::BasicIo::beg);
    Exiv2::DataBuf buf = memIo.read(data.size());
    EXPECT_EQ(0, std::memcmp(buf.data(), data.data(), data.size()));
}

TEST_F(MemIoTest_573, SeekAndTellMemIo_573) {
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(testData_.data()), testData_.size());
    
    EXPECT_EQ(0, memIo.tell());
    
    memIo.seek(10, Exiv2::BasicIo::beg);
    EXPECT_EQ(10, memIo.tell());
    
    memIo.seek(5, Exiv2::BasicIo::cur);
    EXPECT_EQ(15, memIo.tell());
    
    memIo.seek(0, Exiv2::BasicIo::end);
    EXPECT_EQ(static_cast<long>(testData_.size()), memIo.tell());
}

TEST_F(MemIoTest_573, EofMemIo_573) {
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(testData_.data()), testData_.size());
    
    EXPECT_FALSE(memIo.eof());
    
    memIo.read(testData_.size());
    Exiv2::byte oneByte;
    memIo.read(&oneByte, 1);
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_573, MmapReturnsNonNull_573) {
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(testData_.data()), testData_.size());
    
    const Exiv2::byte* mapped = memIo.mmap();
    ASSERT_NE(nullptr, mapped);
    EXPECT_EQ(0, std::memcmp(mapped, testData_.data(), testData_.size()));
    EXPECT_EQ(0, memIo.munmap());
}

TEST_F(MemIoTest_573, TransferToAnotherMemIo_573) {
    Exiv2::MemIo src(reinterpret_cast<const Exiv2::byte*>(testData_.data()), testData_.size());
    Exiv2::MemIo dst;
    
    dst.transfer(src);
    
    EXPECT_EQ(testData_.size(), dst.size());
    dst.seek(0, Exiv2::BasicIo::beg);
    Exiv2::DataBuf buf = dst.read(testData_.size());
    EXPECT_EQ(0, std::memcmp(buf.data(), testData_.data(), testData_.size()));
}

TEST_F(MemIoTest_573, ReadMoreThanAvailable_573) {
    std::string small = "Hi";
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(small.data()), small.size());
    
    Exiv2::DataBuf buf = memIo.read(100);
    EXPECT_EQ(small.size(), buf.size());
}

TEST_F(MemIoTest_573, MultipleWrites_573) {
    Exiv2::MemIo memIo;
    
    std::string part1 = "Hello";
    std::string part2 = " World";
    
    memIo.write(reinterpret_cast<const Exiv2::byte*>(part1.data()), part1.size());
    memIo.write(reinterpret_cast<const Exiv2::byte*>(part2.data()), part2.size());
    
    EXPECT_EQ(part1.size() + part2.size(), memIo.size());
    
    memIo.seek(0, Exiv2::BasicIo::beg);
    Exiv2::DataBuf buf = memIo.read(11);
    EXPECT_EQ(0, std::memcmp(buf.data(), "Hello World", 11));
}

TEST_F(MemIoTest_573, EmptyMemIoSize_573) {
    Exiv2::MemIo memIo;
    EXPECT_EQ(0u, memIo.size());
    EXPECT_EQ(0, memIo.tell());
}

TEST_F(MemIoTest_573, OpenCloseMemIo_573) {
    Exiv2::MemIo memIo;
    // MemIo is always open
    EXPECT_TRUE(memIo.isopen());
    EXPECT_EQ(0, memIo.close());
    // After close, it should still work for MemIo
}

TEST_F(MemIoTest_573, SeekNegativeFromCurrent_573) {
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(testData_.data()), testData_.size());
    
    memIo.seek(10, Exiv2::BasicIo::beg);
    EXPECT_EQ(10, memIo.tell());
    
    memIo.seek(-5, Exiv2::BasicIo::cur);
    EXPECT_EQ(5, memIo.tell());
}

TEST_F(MemIoTest_573, SeekNegativeFromEnd_573) {
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(testData_.data()), testData_.size());
    
    memIo.seek(-5, Exiv2::BasicIo::end);
    EXPECT_EQ(static_cast<long>(testData_.size()) - 5, memIo.tell());
}

// Test for FileIo with MemIo transfer
class FileIoMemIoTransferTest_573 : public ::testing::Test {};

TEST_F(FileIoMemIoTransferTest_573, TransferFromMemIoToFileIo_573) {
    std::string data = "Transfer test data 573";
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    
    std::string filePath = "transfer_test_573.tmp";
    Exiv2::FileIo fileIo(filePath);
    
    fileIo.transfer(memIo);
    
    ASSERT_EQ(0, fileIo.open());
    Exiv2::DataBuf buf = fileIo.read(data.size());
    EXPECT_EQ(data.size(), buf.size());
    EXPECT_EQ(0, std::memcmp(buf.data(), data.data(), data.size()));
    fileIo.close();
    
    std::remove(filePath.c_str());
}

// Test putb and getb
class MemIoPutGetByteTest_573 : public ::testing::Test {};

TEST_F(MemIoPutGetByteTest_573, PutAndGetByte_573) {
    Exiv2::MemIo memIo;
    
    EXPECT_EQ(0, memIo.putb(0x42));
    EXPECT_EQ(1u, memIo.size());
    
    memIo.seek(0, Exiv2::BasicIo::beg);
    EXPECT_EQ(0x42, memIo.getb());
}

TEST_F(MemIoPutGetByteTest_573, GetbAtEofReturnsEof_573) {
    Exiv2::MemIo memIo;
    memIo.putb(0x01);
    
    memIo.seek(0, Exiv2::BasicIo::beg);
    EXPECT_EQ(0x01, memIo.getb());
    EXPECT_EQ(EOF, memIo.getb());
}

TEST_F(MemIoPutGetByteTest_573, MultiplePutb_573) {
    Exiv2::MemIo memIo;
    
    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(0, memIo.putb(static_cast<Exiv2::byte>(i)));
    }
    EXPECT_EQ(256u, memIo.size());
    
    memIo.seek(0, Exiv2::BasicIo::beg);
    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(i, memIo.getb());
    }
}

// Test error()
class IoErrorTest_573 : public ::testing::Test {};

TEST_F(IoErrorTest_573, MemIoNoError_573) {
    Exiv2::MemIo memIo;
    EXPECT_EQ(0, memIo.error());
}

TEST_F(IoErrorTest_573, FileIoErrorWhenNotOpen_573) {
    Exiv2::FileIo fileIo("nonexistent_573.tmp");
    // Error state before opening is 0
    EXPECT_EQ(0, fileIo.error());
}

// Test writing from one Io to another via write(BasicIo&)
class IoToIoWriteTest_573 : public ::testing::Test {};

TEST_F(IoToIoWriteTest_573, WriteMemIoToMemIo_573) {
    std::string data = "Source data for copy 573";
    Exiv2::MemIo src(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    Exiv2::MemIo dst;
    
    dst.write(src);
    
    EXPECT_EQ(data.size(), dst.size());
    dst.seek(0, Exiv2::BasicIo::beg);
    Exiv2::DataBuf buf = dst.read(data.size());
    EXPECT_EQ(0, std::memcmp(buf.data(), data.data(), data.size()));
}

// Test large data handling
class LargeDataTest_573 : public ::testing::Test {};

TEST_F(LargeDataTest_573, MemIoLargeWrite_573) {
    const size_t largeSize = 1024 * 1024; // 1MB
    std::vector<Exiv2::byte> largeData(largeSize, 0xAB);
    
    Exiv2::MemIo memIo;
    size_t written = memIo.write(largeData.data(), largeData.size());
    EXPECT_EQ(largeSize, written);
    EXPECT_EQ(largeSize, memIo.size());
    
    memIo.seek(0, Exiv2::BasicIo::beg);
    Exiv2::DataBuf buf = memIo.read(largeSize);
    EXPECT_EQ(largeSize, buf.size());
    EXPECT_EQ(0xAB, buf.data()[0]);
    EXPECT_EQ(0xAB, buf.data()[largeSize - 1]);
}

// Boundary test: single byte
class BoundaryTest_573 : public ::testing::Test {};

TEST_F(BoundaryTest_573, SingleByteMemIo_573) {
    Exiv2::byte singleByte = 0xFF;
    Exiv2::MemIo memIo(&singleByte, 1);
    
    EXPECT_EQ(1u, memIo.size());
    
    Exiv2::DataBuf buf = memIo.read(1);
    EXPECT_EQ(1u, buf.size());
    EXPECT_EQ(0xFF, buf.data()[0]);
}

TEST_F(BoundaryTest_573, SeekToBeginning_573) {
    std::string data = "Test";
    Exiv2::MemIo memIo(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    
    memIo.read(4);
    EXPECT_EQ(4, memIo.tell());
    
    memIo.seek(0, Exiv2::BasicIo::beg);
    EXPECT_EQ(0, memIo.tell());
}
