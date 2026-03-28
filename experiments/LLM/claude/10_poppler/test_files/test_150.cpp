#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdio>
#include <cstring>
#include <fstream>

#include "Stream.h"
#include "goo/GooFile.h"
#include "Object.h"

class FileStreamTest_150 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        testData = "Hello, World! This is a test file for FileStream unit tests.";
        ofs.write(testData.c_str(), testData.size());
        ofs.close();
    }

    void TearDown() override {
        std::remove(tmpFilePath.c_str());
    }

    std::unique_ptr<FileStream> createFileStream(Goffset start = 0, bool limited = true, Goffset length = -1) {
        if (length < 0) {
            length = static_cast<Goffset>(testData.size()) - start;
        }
        GooFile *gooFile = GooFile::open(tmpFilePath);
        EXPECT_NE(gooFile, nullptr);
        if (!gooFile) return nullptr;
        Object dict;
        auto fs = std::make_unique<FileStream>(gooFile, start, limited, length, std::move(dict));
        gooFiles.push_back(gooFile);
        return fs;
    }

    std::string tmpFilePath;
    std::string testData;
    std::vector<GooFile*> gooFiles;
};

TEST_F(FileStreamTest_150, LookCharReturnsFirstByte_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    int ch = fs->lookChar();
    EXPECT_EQ(ch, static_cast<unsigned char>('H'));
}

TEST_F(FileStreamTest_150, LookCharDoesNotAdvancePosition_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    int ch1 = fs->lookChar();
    int ch2 = fs->lookChar();
    EXPECT_EQ(ch1, ch2);
}

TEST_F(FileStreamTest_150, GetCharAdvancesPosition_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    int ch1 = fs->getChar();
    int ch2 = fs->getChar();
    EXPECT_EQ(ch1, static_cast<unsigned char>('H'));
    EXPECT_EQ(ch2, static_cast<unsigned char>('e'));
}

TEST_F(FileStreamTest_150, GetCharReturnsEOFAtEnd_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    // Read all bytes
    for (size_t i = 0; i < testData.size(); i++) {
        int ch = fs->getChar();
        EXPECT_NE(ch, EOF);
    }
    // Next should be EOF
    int ch = fs->getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(FileStreamTest_150, LookCharReturnsEOFAtEnd_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    // Read all bytes
    for (size_t i = 0; i < testData.size(); i++) {
        fs->getChar();
    }
    int ch = fs->lookChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(FileStreamTest_150, RewindResetsPosition_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    fs->getChar(); // read 'H'
    fs->getChar(); // read 'e'
    fs->rewind();
    int ch = fs->getChar();
    EXPECT_EQ(ch, static_cast<unsigned char>('H'));
}

TEST_F(FileStreamTest_150, GetPosReturnsCorrectPosition_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    EXPECT_EQ(fs->getPos(), 0);
    fs->getChar();
    EXPECT_EQ(fs->getPos(), 1);
    fs->getChar();
    EXPECT_EQ(fs->getPos(), 2);
}

TEST_F(FileStreamTest_150, GetStartReturnsStartOffset_150) {
    auto fs = createFileStream(5, true, 10);
    ASSERT_NE(fs, nullptr);
    EXPECT_EQ(fs->getStart(), 5);
}

TEST_F(FileStreamTest_150, StreamWithOffset_150) {
    auto fs = createFileStream(7, true, 5);
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    // testData[7] should be 'W' ("Hello, World!...")
    int ch = fs->lookChar();
    EXPECT_EQ(ch, static_cast<unsigned char>(testData[7]));
}

TEST_F(FileStreamTest_150, GetKindReturnsFileStreamKind_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    EXPECT_EQ(fs->getKind(), strFile);
}

TEST_F(FileStreamTest_150, CopyReturnsValidStream_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    auto copyStream = fs->copy();
    ASSERT_NE(copyStream, nullptr);
}

TEST_F(FileStreamTest_150, MakeSubStreamReturnsValidStream_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    Object dict;
    auto subStream = fs->makeSubStream(5, true, 10, std::move(dict));
    ASSERT_NE(subStream, nullptr);
}

TEST_F(FileStreamTest_150, SetPosFromStart_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    fs->setPos(3, 0);
    int ch = fs->lookChar();
    EXPECT_EQ(ch, static_cast<unsigned char>(testData[3]));
}

TEST_F(FileStreamTest_150, MoveStartShiftsStartPosition_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    Goffset originalStart = fs->getStart();
    fs->moveStart(5);
    EXPECT_EQ(fs->getStart(), originalStart + 5);
}

TEST_F(FileStreamTest_150, ReadEntireContent_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    std::string result;
    int ch;
    while ((ch = fs->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, testData);
}

TEST_F(FileStreamTest_150, LimitedStreamRespectsLength_150) {
    Goffset limitedLen = 5;
    auto fs = createFileStream(0, true, limitedLen);
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    std::string result;
    int ch;
    while ((ch = fs->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, testData.substr(0, limitedLen));
}

TEST_F(FileStreamTest_150, GetUnfilteredChar_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    int ch = fs->getUnfilteredChar();
    EXPECT_EQ(ch, static_cast<unsigned char>('H'));
}

TEST_F(FileStreamTest_150, UnfilteredRewind_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    fs->getChar();
    fs->getChar();
    bool result = fs->unfilteredRewind();
    EXPECT_TRUE(result);
}

TEST_F(FileStreamTest_150, NeedsEncryptionOnSaveDefaultFalse_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    EXPECT_FALSE(fs->getNeedsEncryptionOnSave());
}

TEST_F(FileStreamTest_150, SetNeedsEncryptionOnSave_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(fs->getNeedsEncryptionOnSave());
    fs->setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(fs->getNeedsEncryptionOnSave());
}

TEST_F(FileStreamTest_150, ZeroLengthStream_150) {
    auto fs = createFileStream(0, true, 0);
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    int ch = fs->lookChar();
    EXPECT_EQ(ch, EOF);
    ch = fs->getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(FileStreamTest_150, SingleByteStream_150) {
    auto fs = createFileStream(0, true, 1);
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    int ch = fs->lookChar();
    EXPECT_EQ(ch, static_cast<unsigned char>('H'));
    ch = fs->getChar();
    EXPECT_EQ(ch, static_cast<unsigned char>('H'));
    ch = fs->lookChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(FileStreamTest_150, CloseAndRewind_150) {
    auto fs = createFileStream(0, true, testData.size());
    ASSERT_NE(fs, nullptr);
    fs->rewind();
    fs->getChar();
    fs->close();
    // After close, rewind should still work
    bool rewound = fs->rewind();
    EXPECT_TRUE(rewound);
}

TEST_F(FileStreamTest_150, LookCharReturnsByteAs0to255_150) {
    // Create a file with a byte value > 127 to test unsigned behavior
    std::string binFilePath = std::tmpnam(nullptr);
    {
        std::ofstream ofs(binFilePath, std::ios::binary);
        unsigned char data[] = { 0x00, 0x7F, 0x80, 0xFF };
        ofs.write(reinterpret_cast<char*>(data), sizeof(data));
    }

    GooFile *gooFile = GooFile::open(binFilePath);
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile, 0, true, 4, std::move(dict));
    fs.rewind();

    EXPECT_EQ(fs.lookChar(), 0x00);
    EXPECT_EQ(fs.getChar(), 0x00);

    EXPECT_EQ(fs.lookChar(), 0x7F);
    EXPECT_EQ(fs.getChar(), 0x7F);

    EXPECT_EQ(fs.lookChar(), 0x80);
    EXPECT_EQ(fs.getChar(), 0x80);

    EXPECT_EQ(fs.lookChar(), 0xFF);
    EXPECT_EQ(fs.getChar(), 0xFF);

    EXPECT_EQ(fs.lookChar(), EOF);

    std::remove(binFilePath.c_str());
    delete gooFile;
}
