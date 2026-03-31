#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>

#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

namespace {

// Helper to create a temporary file path
std::string getTempFilePath(const std::string& suffix = "") {
    static int counter = 0;
    std::string path = "test_writeFile_620_" + std::to_string(counter++) + suffix + ".tmp";
    return path;
}

// Helper to remove a file
void removeFile(const std::string& path) {
    std::remove(path.c_str());
}

// Helper to read file contents
std::vector<uint8_t> readFileContents(const std::string& path) {
    std::ifstream ifs(path, std::ios::binary);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(ifs)),
                                 std::istreambuf_iterator<char>());
}

}  // namespace

// Test fixture for writeFile tests
class WriteFileTest_620 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (const auto& f : filesToCleanup_) {
      removeFile(f);
    }
  }

  void addCleanup(const std::string& path) {
    filesToCleanup_.push_back(path);
  }

  std::vector<std::string> filesToCleanup_;
};

// Test: Writing a non-empty buffer to a file succeeds and returns correct size
TEST_F(WriteFileTest_620, WriteNonEmptyBuffer_ReturnsCorrectSize_620) {
    std::string path = getTempFilePath("_nonempty");
    addCleanup(path);

    const uint8_t data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};  // "Hello"
    Exiv2::DataBuf buf(data, sizeof(data));

    size_t written = Exiv2::writeFile(buf, path);
    EXPECT_EQ(written, sizeof(data));
}

// Test: Written data matches the buffer content
TEST_F(WriteFileTest_620, WrittenDataMatchesBuffer_620) {
    std::string path = getTempFilePath("_match");
    addCleanup(path);

    const uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0xFF};
    Exiv2::DataBuf buf(data, sizeof(data));

    Exiv2::writeFile(buf, path);

    auto contents = readFileContents(path);
    ASSERT_EQ(contents.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(contents.data(), data, sizeof(data)), 0);
}

// Test: Writing an empty buffer creates an empty file
TEST_F(WriteFileTest_620, WriteEmptyBuffer_ReturnsZero_620) {
    std::string path = getTempFilePath("_empty");
    addCleanup(path);

    Exiv2::DataBuf buf;

    size_t written = Exiv2::writeFile(buf, path);
    EXPECT_EQ(written, 0u);

    auto contents = readFileContents(path);
    EXPECT_TRUE(contents.empty());
}

// Test: Writing to an invalid/non-existent directory throws an error
TEST_F(WriteFileTest_620, WriteToInvalidPath_ThrowsError_620) {
    std::string invalidPath = "/nonexistent_dir_xyz_620/test_file.tmp";

    const uint8_t data[] = {0x01, 0x02};
    Exiv2::DataBuf buf(data, sizeof(data));

    EXPECT_THROW(Exiv2::writeFile(buf, invalidPath), Exiv2::Error);
}

// Test: Writing a large buffer succeeds
TEST_F(WriteFileTest_620, WriteLargeBuffer_Succeeds_620) {
    std::string path = getTempFilePath("_large");
    addCleanup(path);

    const size_t largeSize = 100000;
    Exiv2::DataBuf buf(largeSize);
    // Fill with a pattern
    for (size_t i = 0; i < largeSize; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i % 256));
    }

    size_t written = Exiv2::writeFile(buf, path);
    EXPECT_EQ(written, largeSize);

    auto contents = readFileContents(path);
    ASSERT_EQ(contents.size(), largeSize);
    for (size_t i = 0; i < largeSize; ++i) {
        EXPECT_EQ(contents[i], static_cast<uint8_t>(i % 256)) << "Mismatch at offset " << i;
    }
}

// Test: Writing overwrites existing file content
TEST_F(WriteFileTest_620, WriteOverwritesExistingFile_620) {
    std::string path = getTempFilePath("_overwrite");
    addCleanup(path);

    // Write first content
    const uint8_t data1[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    Exiv2::DataBuf buf1(data1, sizeof(data1));
    Exiv2::writeFile(buf1, path);

    // Write second (shorter) content
    const uint8_t data2[] = {0x11, 0x22};
    Exiv2::DataBuf buf2(data2, sizeof(data2));
    size_t written = Exiv2::writeFile(buf2, path);

    EXPECT_EQ(written, sizeof(data2));

    auto contents = readFileContents(path);
    ASSERT_EQ(contents.size(), sizeof(data2));
    EXPECT_EQ(std::memcmp(contents.data(), data2, sizeof(data2)), 0);
}

// Test: Writing a single byte buffer
TEST_F(WriteFileTest_620, WriteSingleByte_620) {
    std::string path = getTempFilePath("_singlebyte");
    addCleanup(path);

    const uint8_t data[] = {0x42};
    Exiv2::DataBuf buf(data, sizeof(data));

    size_t written = Exiv2::writeFile(buf, path);
    EXPECT_EQ(written, 1u);

    auto contents = readFileContents(path);
    ASSERT_EQ(contents.size(), 1u);
    EXPECT_EQ(contents[0], 0x42);
}

// Test fixture for FileIo tests
class FileIoTest_620 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (const auto& f : filesToCleanup_) {
      removeFile(f);
    }
  }

  void addCleanup(const std::string& path) {
    filesToCleanup_.push_back(path);
  }

  std::string createTempFile(const std::string& suffix, const std::vector<uint8_t>& content = {}) {
    std::string path = getTempFilePath(suffix);
    addCleanup(path);
    if (!content.empty()) {
      std::ofstream ofs(path, std::ios::binary);
      ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
    }
    return path;
  }

  std::vector<std::string> filesToCleanup_;
};

// Test: FileIo path returns the correct path
TEST_F(FileIoTest_620, PathReturnsCorrectPath_620) {
    std::string path = "/some/test/path.jpg";
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(fileIo.path(), path);
}

// Test: FileIo open with valid mode on existing file succeeds
TEST_F(FileIoTest_620, OpenExistingFileSucceeds_620) {
    std::string path = createTempFile("_open", {0x01, 0x02});
    Exiv2::FileIo fileIo(path);
    int result = fileIo.open("rb");
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test: FileIo isopen returns false before open
TEST_F(FileIoTest_620, IsOpenReturnsFalseBeforeOpen_620) {
    std::string path = createTempFile("_isopen", {0x01});
    Exiv2::FileIo fileIo(path);
    EXPECT_FALSE(fileIo.isopen());
}

// Test: FileIo close after open
TEST_F(FileIoTest_620, CloseAfterOpen_620) {
    std::string path = createTempFile("_close", {0x01});
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
    EXPECT_FALSE(fileIo.isopen());
}

// Test: FileIo size returns correct size
TEST_F(FileIoTest_620, SizeReturnsCorrectValue_620) {
    std::vector<uint8_t> content = {0x01, 0x02, 0x03, 0x04, 0x05};
    std::string path = createTempFile("_size", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");
    EXPECT_EQ(fileIo.size(), content.size());
    fileIo.close();
}

// Test: FileIo read returns correct data
TEST_F(FileIoTest_620, ReadReturnsCorrectData_620) {
    std::vector<uint8_t> content = {0xDE, 0xAD, 0xBE, 0xEF};
    std::string path = createTempFile("_read", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");

    Exiv2::DataBuf buf = fileIo.read(4);
    ASSERT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.read_uint8(0), 0xDE);
    EXPECT_EQ(buf.read_uint8(1), 0xAD);
    EXPECT_EQ(buf.read_uint8(2), 0xBE);
    EXPECT_EQ(buf.read_uint8(3), 0xEF);

    fileIo.close();
}

// Test: FileIo write and read back
TEST_F(FileIoTest_620, WriteAndReadBack_620) {
    std::string path = createTempFile("_writeread");
    Exiv2::FileIo fileIo(path);

    ASSERT_EQ(fileIo.open("wb"), 0);
    const uint8_t data[] = {0x10, 0x20, 0x30};
    size_t written = fileIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    fileIo.close();

    ASSERT_EQ(fileIo.open("rb"), 0);
    Exiv2::DataBuf buf = fileIo.read(3);
    ASSERT_EQ(buf.size(), 3u);
    EXPECT_EQ(buf.read_uint8(0), 0x10);
    EXPECT_EQ(buf.read_uint8(1), 0x20);
    EXPECT_EQ(buf.read_uint8(2), 0x30);
    fileIo.close();
}

// Test: FileIo tell returns correct position
TEST_F(FileIoTest_620, TellReturnsCorrectPosition_620) {
    std::vector<uint8_t> content = {0x01, 0x02, 0x03, 0x04, 0x05};
    std::string path = createTempFile("_tell", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");

    EXPECT_EQ(fileIo.tell(), 0u);

    fileIo.read(3);
    EXPECT_EQ(fileIo.tell(), 3u);

    fileIo.close();
}

// Test: FileIo seek to different positions
TEST_F(FileIoTest_620, SeekToPositions_620) {
    std::vector<uint8_t> content = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E};
    std::string path = createTempFile("_seek", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");

    // Seek from beginning
    EXPECT_EQ(fileIo.seek(2, Exiv2::BasicIo::beg), 0);
    EXPECT_EQ(fileIo.tell(), 2u);

    // Read byte at position 2
    int b = fileIo.getb();
    EXPECT_EQ(b, 0x0C);

    // Seek from current position
    EXPECT_EQ(fileIo.seek(1, Exiv2::BasicIo::cur), 0);
    b = fileIo.getb();
    EXPECT_EQ(b, 0x0E);

    // Seek from end
    EXPECT_EQ(fileIo.seek(-1, Exiv2::BasicIo::end), 0);
    b = fileIo.getb();
    EXPECT_EQ(b, 0x0E);

    fileIo.close();
}

// Test: FileIo getb returns EOF at end
TEST_F(FileIoTest_620, GetbReturnsEOFAtEnd_620) {
    std::vector<uint8_t> content = {0x42};
    std::string path = createTempFile("_getbeof", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");

    int b = fileIo.getb();
    EXPECT_EQ(b, 0x42);

    b = fileIo.getb();
    EXPECT_EQ(b, EOF);

    fileIo.close();
}

// Test: FileIo eof returns true at end of file
TEST_F(FileIoTest_620, EofReturnsTrueAtEnd_620) {
    std::vector<uint8_t> content = {0x01};
    std::string path = createTempFile("_eof", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");

    EXPECT_FALSE(fileIo.eof());
    fileIo.read(1);
    // After reading all content, try to read more to trigger EOF
    fileIo.getb();
    EXPECT_TRUE(fileIo.eof());

    fileIo.close();
}

// Test: FileIo putb writes a single byte
TEST_F(FileIoTest_620, PutbWritesSingleByte_620) {
    std::string path = createTempFile("_putb");
    Exiv2::FileIo fileIo(path);
    fileIo.open("wb");

    int result = fileIo.putb(0xAB);
    EXPECT_EQ(result, 0xAB);

    fileIo.close();

    // Read back to verify
    fileIo.open("rb");
    int b = fileIo.getb();
    EXPECT_EQ(b, 0xAB);
    fileIo.close();
}

// Test: FileIo open non-existent file for reading fails
TEST_F(FileIoTest_620, OpenNonExistentForReadFails_620) {
    std::string path = "/nonexistent_path_620/no_such_file.tmp";
    Exiv2::FileIo fileIo(path);
    int result = fileIo.open("rb");
    EXPECT_NE(result, 0);
    EXPECT_FALSE(fileIo.isopen());
}

// Test: FileIo setPath changes path
TEST_F(FileIoTest_620, SetPathChangesPath_620) {
    std::string path1 = "original_path_620.tmp";
    std::string path2 = "new_path_620.tmp";
    Exiv2::FileIo fileIo(path1);
    EXPECT_EQ(fileIo.path(), path1);

    fileIo.setPath(path2);
    EXPECT_EQ(fileIo.path(), path2);
}

// Test: FileIo read with buffer
TEST_F(FileIoTest_620, ReadWithBuffer_620) {
    std::vector<uint8_t> content = {0x11, 0x22, 0x33, 0x44};
    std::string path = createTempFile("_readbuf", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");

    uint8_t buf[4] = {};
    size_t readCount = fileIo.read(buf, 4);
    EXPECT_EQ(readCount, 4u);
    EXPECT_EQ(buf[0], 0x11);
    EXPECT_EQ(buf[1], 0x22);
    EXPECT_EQ(buf[2], 0x33);
    EXPECT_EQ(buf[3], 0x44);

    fileIo.close();
}

// Test: FileIo read more than available returns actual size
TEST_F(FileIoTest_620, ReadMoreThanAvailable_620) {
    std::vector<uint8_t> content = {0xAA, 0xBB};
    std::string path = createTempFile("_readmore", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");

    uint8_t buf[10] = {};
    size_t readCount = fileIo.read(buf, 10);
    EXPECT_EQ(readCount, 2u);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);

    fileIo.close();
}

// Test: FileIo error returns 0 when no error
TEST_F(FileIoTest_620, ErrorReturnsZeroWhenNoError_620) {
    std::vector<uint8_t> content = {0x01};
    std::string path = createTempFile("_error", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open("rb");
    EXPECT_EQ(fileIo.error(), 0);
    fileIo.close();
}
