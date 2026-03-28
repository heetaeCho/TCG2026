#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstdio>
#include <filesystem>

namespace fs = std::filesystem;

// Helper to create a temporary file with content
static std::string createTempFile(const std::string& prefix, const std::string& content = "") {
    std::string path = prefix + "_test_" + std::to_string(std::rand()) + ".tmp";
    if (!content.empty()) {
        std::ofstream ofs(path, std::ios::binary);
        ofs.write(content.data(), content.size());
        ofs.close();
    } else {
        // Create empty file
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    return path;
}

static void removeTempFile(const std::string& path) {
    std::error_code ec;
    fs::remove(path, ec);
}

class FileIoTransferTest_554 : public ::testing::Test {
protected:
    std::vector<std::string> tempFiles_;

    void TearDown() override {
        for (auto& f : tempFiles_) {
            removeTempFile(f);
        }
    }

    std::string makeTempFile(const std::string& prefix, const std::string& content = "") {
        auto path = createTempFile(prefix, content);
        tempFiles_.push_back(path);
        return path;
    }
};

// Test: Transfer from one FileIo to another (FileIo-to-FileIo path)
TEST_F(FileIoTransferTest_554, TransferFileIoToFileIo_554) {
    std::string srcContent = "Hello, World!";
    std::string srcPath = makeTempFile("src", srcContent);
    std::string dstPath = makeTempFile("dst", "old content");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    ASSERT_NO_THROW(dst.transfer(src));

    // After transfer, dst should contain src's content
    ASSERT_EQ(dst.open(), 0);
    Exiv2::DataBuf buf = dst.read(100);
    dst.close();

    std::string result(reinterpret_cast<const char*>(buf.c_data()), buf.size());
    EXPECT_EQ(result, srcContent);
}

// Test: Transfer from FileIo to FileIo when destination was open
TEST_F(FileIoTransferTest_554, TransferReopensIfWasOpen_554) {
    std::string srcContent = "Transfer test data";
    std::string srcPath = makeTempFile("src_open", srcContent);
    std::string dstPath = makeTempFile("dst_open", "initial");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    // Open destination before transfer
    ASSERT_EQ(dst.open(), 0);
    EXPECT_TRUE(dst.isopen());

    ASSERT_NO_THROW(dst.transfer(src));

    // After transfer with wasOpen=true, dst should still be open
    EXPECT_TRUE(dst.isopen());
    dst.close();
}

// Test: Transfer from FileIo to FileIo when destination was closed
TEST_F(FileIoTransferTest_554, TransferClosedDestinationRemainsClosed_554) {
    std::string srcContent = "Closed dest test";
    std::string srcPath = makeTempFile("src_closed", srcContent);
    std::string dstPath = makeTempFile("dst_closed", "data");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    // Don't open destination
    EXPECT_FALSE(dst.isopen());

    ASSERT_NO_THROW(dst.transfer(src));

    // After transfer with wasOpen=false, dst should be closed
    EXPECT_FALSE(dst.isopen());
}

// Test: Transfer empty file
TEST_F(FileIoTransferTest_554, TransferEmptyFile_554) {
    std::string srcPath = makeTempFile("src_empty", "");
    std::string dstPath = makeTempFile("dst_empty", "some content");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    ASSERT_NO_THROW(dst.transfer(src));

    ASSERT_EQ(dst.open(), 0);
    EXPECT_EQ(dst.size(), 0u);
    dst.close();
}

// Test: Transfer large data
TEST_F(FileIoTransferTest_554, TransferLargeData_554) {
    std::string largeContent(100000, 'X');
    std::string srcPath = makeTempFile("src_large", largeContent);
    std::string dstPath = makeTempFile("dst_large", "small");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    ASSERT_NO_THROW(dst.transfer(src));

    ASSERT_EQ(dst.open(), 0);
    EXPECT_EQ(dst.size(), 100000u);
    dst.close();
}

// Test: Transfer from MemIo (non-FileIo BasicIo) to FileIo
TEST_F(FileIoTransferTest_554, TransferFromMemIoToFileIo_554) {
    std::string dstPath = makeTempFile("dst_memio", "old");

    Exiv2::FileIo dst(dstPath);

    // Use MemIo as source (non-FileIo path in transfer)
    const std::string srcData = "MemIo source data";
    Exiv2::MemIo memSrc(reinterpret_cast<const Exiv2::byte*>(srcData.data()), srcData.size());

    ASSERT_NO_THROW(dst.transfer(memSrc));

    ASSERT_EQ(dst.open(), 0);
    Exiv2::DataBuf buf = dst.read(100);
    dst.close();

    std::string result(reinterpret_cast<const char*>(buf.c_data()), buf.size());
    EXPECT_EQ(result, srcData);
}

// Test: Transfer from empty MemIo to FileIo
TEST_F(FileIoTransferTest_554, TransferFromEmptyMemIo_554) {
    std::string dstPath = makeTempFile("dst_empty_memio", "existing data");

    Exiv2::FileIo dst(dstPath);
    Exiv2::MemIo memSrc;

    ASSERT_NO_THROW(dst.transfer(memSrc));

    ASSERT_EQ(dst.open(), 0);
    EXPECT_EQ(dst.size(), 0u);
    dst.close();
}

// Test: Transfer to non-existent destination path (FileIo-to-FileIo)
TEST_F(FileIoTransferTest_554, TransferToNewFile_554) {
    std::string srcContent = "New file data";
    std::string srcPath = makeTempFile("src_new", srcContent);
    std::string dstPath = "nonexistent_dst_554_" + std::to_string(std::rand()) + ".tmp";
    tempFiles_.push_back(dstPath);

    // Create the dst path (needs to exist for "a+b" open to work in transfer)
    {
        std::ofstream ofs(dstPath, std::ios::binary);
        ofs.close();
    }

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    ASSERT_NO_THROW(dst.transfer(src));

    ASSERT_EQ(dst.open(), 0);
    Exiv2::DataBuf buf = dst.read(100);
    dst.close();

    std::string result(reinterpret_cast<const char*>(buf.c_data()), buf.size());
    EXPECT_EQ(result, srcContent);
}

// Test: Source FileIo is closed after transfer
TEST_F(FileIoTransferTest_554, SourceFileIoClosedAfterTransfer_554) {
    std::string srcPath = makeTempFile("src_close_check", "data");
    std::string dstPath = makeTempFile("dst_close_check", "old");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    ASSERT_NO_THROW(dst.transfer(src));

    // Source should be effectively closed/moved
    EXPECT_FALSE(src.isopen());
}

// Test: Transfer with MemIo when destination was open with specific mode
TEST_F(FileIoTransferTest_554, TransferFromMemIoWhenDstWasOpen_554) {
    std::string dstPath = makeTempFile("dst_open_memio", "initial");

    Exiv2::FileIo dst(dstPath);
    ASSERT_EQ(dst.open(), 0);

    const std::string srcData = "replacement data";
    Exiv2::MemIo memSrc(reinterpret_cast<const Exiv2::byte*>(srcData.data()), srcData.size());

    ASSERT_NO_THROW(dst.transfer(memSrc));

    // Should be reopened since it was open
    EXPECT_TRUE(dst.isopen());
    dst.close();

    // Verify content
    ASSERT_EQ(dst.open(), 0);
    Exiv2::DataBuf buf = dst.read(100);
    dst.close();
    std::string result(reinterpret_cast<const char*>(buf.c_data()), buf.size());
    EXPECT_EQ(result, srcData);
}

// Test: Transfer preserves path of destination
TEST_F(FileIoTransferTest_554, TransferPreservesDestinationPath_554) {
    std::string srcPath = makeTempFile("src_path", "data");
    std::string dstPath = makeTempFile("dst_path", "old");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    std::string originalPath = dst.path();

    ASSERT_NO_THROW(dst.transfer(src));

    EXPECT_EQ(dst.path(), originalPath);
}

// Test: Transfer binary data integrity
TEST_F(FileIoTransferTest_554, TransferBinaryDataIntegrity_554) {
    std::string srcContent;
    for (int i = 0; i < 256; ++i) {
        srcContent.push_back(static_cast<char>(i));
    }
    std::string srcPath = makeTempFile("src_binary", srcContent);
    std::string dstPath = makeTempFile("dst_binary", "old");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    ASSERT_NO_THROW(dst.transfer(src));

    ASSERT_EQ(dst.open(), 0);
    Exiv2::DataBuf buf = dst.read(300);
    dst.close();

    ASSERT_EQ(buf.size(), 256u);
    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(buf.c_data()[i], static_cast<Exiv2::byte>(i)) << "Mismatch at byte " << i;
    }
}

// Test: Transfer to invalid path should throw
TEST_F(FileIoTransferTest_554, TransferToInvalidPathThrows_554) {
    std::string srcPath = makeTempFile("src_invalid", "data");

    // Use an invalid path for destination
    std::string invalidDstPath = "/nonexistent_dir_554/impossible_path/file.tmp";

    Exiv2::FileIo dst(invalidDstPath);
    Exiv2::FileIo src(srcPath);

    EXPECT_THROW(dst.transfer(src), Exiv2::Error);
}

// Test: Transfer from MemIo with binary data
TEST_F(FileIoTransferTest_554, TransferFromMemIoBinaryData_554) {
    std::string dstPath = makeTempFile("dst_memio_bin", "");

    std::vector<Exiv2::byte> binData(256);
    for (int i = 0; i < 256; ++i) {
        binData[i] = static_cast<Exiv2::byte>(i);
    }

    Exiv2::FileIo dst(dstPath);
    Exiv2::MemIo memSrc(binData.data(), binData.size());

    ASSERT_NO_THROW(dst.transfer(memSrc));

    ASSERT_EQ(dst.open(), 0);
    Exiv2::DataBuf buf = dst.read(300);
    dst.close();

    ASSERT_EQ(buf.size(), 256u);
    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(buf.c_data()[i], static_cast<Exiv2::byte>(i));
    }
}

// Test: Size after transfer reflects source size
TEST_F(FileIoTransferTest_554, SizeAfterTransferMatchesSource_554) {
    std::string srcContent = "Exact size check content!";
    std::string srcPath = makeTempFile("src_size", srcContent);
    std::string dstPath = makeTempFile("dst_size", "shorter");

    Exiv2::FileIo dst(dstPath);
    Exiv2::FileIo src(srcPath);

    ASSERT_NO_THROW(dst.transfer(src));

    ASSERT_EQ(dst.open(), 0);
    EXPECT_EQ(dst.size(), srcContent.size());
    dst.close();
}
