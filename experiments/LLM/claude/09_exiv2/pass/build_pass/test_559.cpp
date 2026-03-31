#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>

namespace {

// Helper to create a temporary file with given content
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

}  // namespace

class FileIoTest_559 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that path() returns the path passed to the constructor
TEST_F(FileIoTest_559, ConstructorSetsPath_559) {
    std::string testPath = "test_constructor_path_559.tmp";
    Exiv2::FileIo fio(testPath);
    EXPECT_EQ(fio.path(), testPath);
}

// Test setPath changes the path
TEST_F(FileIoTest_559, SetPathChangesPath_559) {
    Exiv2::FileIo fio("initial_path_559.tmp");
    EXPECT_EQ(fio.path(), "initial_path_559.tmp");
    fio.setPath("new_path_559.tmp");
    EXPECT_EQ(fio.path(), "new_path_559.tmp");
}

// Test open on a non-existent file returns non-zero (error)
TEST_F(FileIoTest_559, OpenNonExistentFileReturnsError_559) {
    Exiv2::FileIo fio("non_existent_file_559.tmp");
    int result = fio.open();
    EXPECT_NE(result, 0);
}

// Test open on an existing file returns 0 (success)
TEST_F(FileIoTest_559, OpenExistingFileSucceeds_559) {
    TempFile tmp("test_open_existing_559.tmp", "hello");
    Exiv2::FileIo fio(tmp.path());
    int result = fio.open();
    EXPECT_EQ(result, 0);
    fio.close();
}

// Test isopen returns false before open
TEST_F(FileIoTest_559, IsOpenReturnsFalseBeforeOpen_559) {
    Exiv2::FileIo fio("test_isopen_559.tmp");
    EXPECT_FALSE(fio.isopen());
}

// Test isopen returns true after successful open
TEST_F(FileIoTest_559, IsOpenReturnsTrueAfterOpen_559) {
    TempFile tmp("test_isopen_after_559.tmp", "data");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    EXPECT_TRUE(fio.isopen());
    fio.close();
}

// Test isopen returns false after close
TEST_F(FileIoTest_559, IsOpenReturnsFalseAfterClose_559) {
    TempFile tmp("test_isopen_close_559.tmp", "data");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    fio.close();
    EXPECT_FALSE(fio.isopen());
}

// Test close on an unopened file
TEST_F(FileIoTest_559, CloseUnOpenedFile_559) {
    Exiv2::FileIo fio("test_close_unopened_559.tmp");
    int result = fio.close();
    EXPECT_EQ(result, 0);
}

// Test size returns correct size of file
TEST_F(FileIoTest_559, SizeReturnsFileSize_559) {
    std::string content = "Hello, World!";
    TempFile tmp("test_size_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    EXPECT_EQ(fio.size(), content.size());
}

// Test size of empty file
TEST_F(FileIoTest_559, SizeOfEmptyFile_559) {
    TempFile tmp("test_size_empty_559.tmp", "");
    Exiv2::FileIo fio(tmp.path());
    EXPECT_EQ(fio.size(), 0u);
}

// Test open with write mode
TEST_F(FileIoTest_559, OpenWithWriteMode_559) {
    TempFile tmp("test_write_mode_559.tmp", "");
    Exiv2::FileIo fio(tmp.path());
    int result = fio.open("w+b");
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(fio.isopen());
    fio.close();
}

// Test write data to file
TEST_F(FileIoTest_559, WriteDataToFile_559) {
    TempFile tmp("test_write_data_559.tmp", "");
    Exiv2::FileIo fio(tmp.path());
    fio.open("w+b");
    const std::string data = "Test data 559";
    size_t written = fio.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(written, data.size());
    fio.close();
}

// Test read data from file
TEST_F(FileIoTest_559, ReadDataFromFile_559) {
    std::string content = "ReadTest559";
    TempFile tmp("test_read_data_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    Exiv2::byte buf[64] = {};
    size_t bytesRead = fio.read(buf, content.size());
    EXPECT_EQ(bytesRead, content.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), content);
    fio.close();
}

// Test read with DataBuf
TEST_F(FileIoTest_559, ReadDataBufFromFile_559) {
    std::string content = "DataBufTest559";
    TempFile tmp("test_read_databuf_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    Exiv2::DataBuf dbuf = fio.read(content.size());
    EXPECT_EQ(dbuf.size(), content.size());
    EXPECT_EQ(std::memcmp(dbuf.data(), content.data(), content.size()), 0);
    fio.close();
}

// Test tell after open is at position 0
TEST_F(FileIoTest_559, TellAtBeginningAfterOpen_559) {
    TempFile tmp("test_tell_559.tmp", "some content");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    EXPECT_EQ(fio.tell(), 0u);
    fio.close();
}

// Test tell after reading
TEST_F(FileIoTest_559, TellAfterRead_559) {
    std::string content = "0123456789";
    TempFile tmp("test_tell_after_read_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    Exiv2::byte buf[5];
    fio.read(buf, 5);
    EXPECT_EQ(fio.tell(), 5u);
    fio.close();
}

// Test seek from beginning
TEST_F(FileIoTest_559, SeekFromBeginning_559) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_beg_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    int result = fio.seek(5, Exiv2::BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(fio.tell(), 5u);
    fio.close();
}

// Test seek from current position
TEST_F(FileIoTest_559, SeekFromCurrent_559) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_cur_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    fio.seek(3, Exiv2::BasicIo::beg);
    fio.seek(2, Exiv2::BasicIo::cur);
    EXPECT_EQ(fio.tell(), 5u);
    fio.close();
}

// Test seek from end
TEST_F(FileIoTest_559, SeekFromEnd_559) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_end_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    fio.seek(0, Exiv2::BasicIo::end);
    EXPECT_EQ(fio.tell(), content.size());
    fio.close();
}

// Test getb reads one byte at a time
TEST_F(FileIoTest_559, GetbReadsSingleByte_559) {
    std::string content = "AB";
    TempFile tmp("test_getb_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    int b1 = fio.getb();
    EXPECT_EQ(b1, 'A');
    int b2 = fio.getb();
    EXPECT_EQ(b2, 'B');
    fio.close();
}

// Test getb at EOF returns EOF
TEST_F(FileIoTest_559, GetbAtEofReturnsEof_559) {
    TempFile tmp("test_getb_eof_559.tmp", "X");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    fio.getb();  // read 'X'
    int result = fio.getb();  // should be EOF
    EXPECT_EQ(result, EOF);
    fio.close();
}

// Test putb writes a single byte
TEST_F(FileIoTest_559, PutbWritesByte_559) {
    TempFile tmp("test_putb_559.tmp", "");
    Exiv2::FileIo fio(tmp.path());
    fio.open("w+b");
    int result = fio.putb(0x42);
    EXPECT_EQ(result, 0x42);
    fio.seek(0, Exiv2::BasicIo::beg);
    int b = fio.getb();
    EXPECT_EQ(b, 0x42);
    fio.close();
}

// Test eof returns false when not at end
TEST_F(FileIoTest_559, EofReturnsFalseBeforeEnd_559) {
    TempFile tmp("test_eof_false_559.tmp", "data");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    EXPECT_FALSE(fio.eof());
    fio.close();
}

// Test eof returns true after reading past end
TEST_F(FileIoTest_559, EofReturnsTrueAtEnd_559) {
    TempFile tmp("test_eof_true_559.tmp", "X");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    fio.getb();   // read 'X'
    fio.getb();   // attempt to read past end
    EXPECT_TRUE(fio.eof());
    fio.close();
}

// Test error returns 0 for normal operation
TEST_F(FileIoTest_559, ErrorReturnsZeroNormally_559) {
    TempFile tmp("test_error_559.tmp", "data");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    EXPECT_EQ(fio.error(), 0);
    fio.close();
}

// Test read more bytes than available
TEST_F(FileIoTest_559, ReadMoreThanAvailable_559) {
    std::string content = "short";
    TempFile tmp("test_read_more_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    Exiv2::byte buf[100] = {};
    size_t bytesRead = fio.read(buf, 100);
    EXPECT_EQ(bytesRead, content.size());
    fio.close();
}

// Test reading zero bytes
TEST_F(FileIoTest_559, ReadZeroBytes_559) {
    TempFile tmp("test_read_zero_559.tmp", "content");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    Exiv2::byte buf[1] = {};
    size_t bytesRead = fio.read(buf, 0);
    EXPECT_EQ(bytesRead, 0u);
    EXPECT_EQ(fio.tell(), 0u);
    fio.close();
}

// Test writing zero bytes
TEST_F(FileIoTest_559, WriteZeroBytes_559) {
    TempFile tmp("test_write_zero_559.tmp", "");
    Exiv2::FileIo fio(tmp.path());
    fio.open("w+b");
    const Exiv2::byte data[] = {0x00};
    size_t written = fio.write(data, 0);
    EXPECT_EQ(written, 0u);
    fio.close();
}

// Test write from another BasicIo (FileIo)
TEST_F(FileIoTest_559, WriteFromAnotherFileIo_559) {
    std::string content = "source content 559";
    TempFile tmpSrc("test_write_src_559.tmp", content);
    TempFile tmpDst("test_write_dst_559.tmp", "");

    Exiv2::FileIo src(tmpSrc.path());
    Exiv2::FileIo dst(tmpDst.path());

    src.open();
    dst.open("w+b");

    size_t written = dst.write(src);
    EXPECT_EQ(written, content.size());

    dst.seek(0, Exiv2::BasicIo::beg);
    Exiv2::byte buf[64] = {};
    size_t bytesRead = dst.read(buf, 64);
    EXPECT_EQ(bytesRead, content.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), content);

    src.close();
    dst.close();
}

// Test transfer from another FileIo
TEST_F(FileIoTest_559, TransferFromAnotherFileIo_559) {
    std::string content = "transfer data 559";
    TempFile tmpSrc("test_transfer_src_559.tmp", content);
    TempFile tmpDst("test_transfer_dst_559.tmp", "");

    Exiv2::FileIo src(tmpSrc.path());
    Exiv2::FileIo dst(tmpDst.path());

    src.open();
    dst.transfer(src);

    dst.open();
    Exiv2::byte buf[64] = {};
    size_t bytesRead = dst.read(buf, 64);
    EXPECT_EQ(bytesRead, content.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), content);
    dst.close();
}

// Test mmap and munmap
TEST_F(FileIoTest_559, MmapAndMunmap_559) {
    std::string content = "mmap test 559";
    TempFile tmp("test_mmap_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    fio.open();

    Exiv2::byte* mapped = fio.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);

    int result = fio.munmap();
    EXPECT_EQ(result, 0);
    fio.close();
}

// Test multiple open and close cycles
TEST_F(FileIoTest_559, MultipleOpenCloseCycles_559) {
    TempFile tmp("test_multi_oc_559.tmp", "cycle data");
    Exiv2::FileIo fio(tmp.path());

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(fio.open(), 0);
        EXPECT_TRUE(fio.isopen());
        EXPECT_EQ(fio.close(), 0);
        EXPECT_FALSE(fio.isopen());
    }
}

// Test seek to negative offset from beginning (should fail or handle gracefully)
TEST_F(FileIoTest_559, SeekNegativeFromBeginning_559) {
    TempFile tmp("test_seek_neg_559.tmp", "data");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    int result = fio.seek(-1, Exiv2::BasicIo::beg);
    // Seeking to negative from beginning is typically an error
    EXPECT_NE(result, 0);
    fio.close();
}

// Test populateFakeData does not crash
TEST_F(FileIoTest_559, PopulateFakeDataDoesNotCrash_559) {
    Exiv2::FileIo fio("fake_data_559.tmp");
    EXPECT_NO_THROW(fio.populateFakeData());
}

// Test that size works without explicitly opening the file
TEST_F(FileIoTest_559, SizeWithoutOpen_559) {
    std::string content = "size without open";
    TempFile tmp("test_size_no_open_559.tmp", content);
    Exiv2::FileIo fio(tmp.path());
    // size() should be able to stat the file even without open
    EXPECT_EQ(fio.size(), content.size());
}

// Test write then read back
TEST_F(FileIoTest_559, WriteAndReadBack_559) {
    TempFile tmp("test_write_read_559.tmp", "");
    Exiv2::FileIo fio(tmp.path());
    fio.open("w+b");

    std::string data = "write and read back 559";
    fio.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());

    fio.seek(0, Exiv2::BasicIo::beg);
    Exiv2::byte buf[64] = {};
    size_t bytesRead = fio.read(buf, 64);
    EXPECT_EQ(bytesRead, data.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), data);

    fio.close();
}

// Test DataBuf read of zero bytes
TEST_F(FileIoTest_559, ReadDataBufZeroBytes_559) {
    TempFile tmp("test_databuf_zero_559.tmp", "content");
    Exiv2::FileIo fio(tmp.path());
    fio.open();
    Exiv2::DataBuf dbuf = fio.read(0);
    EXPECT_EQ(dbuf.size(), 0u);
    fio.close();
}
