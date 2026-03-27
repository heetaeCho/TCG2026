#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/goo/TiffWriter.h"

#include <cstdio>



using namespace testing;



class TiffWriterTest_33 : public ::testing::Test {

protected:

    void SetUp() override {

        tempFile = std::tmpfile();

        ASSERT_NE(tempFile, nullptr);

    }



    void TearDown() override {

        if (tempFile) {

            fclose(tempFile);

        }

    }



    FILE* tempFile;

};



TEST_F(TiffWriterTest_33, SupportCMYK_ReturnsTrue_33) {

    TiffWriter writer(ImgWriter::Format::TIFF);

    EXPECT_TRUE(writer.supportCMYK());

}



TEST_F(TiffWriterTest_33, Init_ValidParameters_ReturnsTrue_33) {

    TiffWriter writer(ImgWriter::Format::TIFF);

    EXPECT_TRUE(writer.init(tempFile, 100, 100, 300.0, 300.0));

}



TEST_F(TiffWriterTest_33, Init_ZeroWidth_ReturnsFalse_33) {

    TiffWriter writer(ImgWriter::Format::TIFF);

    EXPECT_FALSE(writer.init(tempFile, 0, 100, 300.0, 300.0));

}



TEST_F(TiffWriterTest_33, Init_ZeroHeight_ReturnsFalse_33) {

    TiffWriter writer(ImgWriter::Format::TIFF);

    EXPECT_FALSE(writer.init(tempFile, 100, 0, 300.0, 300.0));

}



TEST_F(TiffWriterTest_33, WritePointers_ValidParameters_ReturnsTrue_33) {

    TiffWriter writer(ImgWriter::Format::TIFF);

    ASSERT_TRUE(writer.init(tempFile, 100, 100, 300.0, 300.0));

    unsigned char* rowPointers[100];

    for (int i = 0; i < 100; ++i) {

        rowPointers[i] = new unsigned char[100]; // Assuming single channel for simplicity

    }

    EXPECT_TRUE(writer.writePointers(rowPointers, 100));

    for (int i = 0; i < 100; ++i) {

        delete[] rowPointers[i];

    }

}



TEST_F(TiffWriterTest_33, WriteRow_ValidParameters_ReturnsTrue_33) {

    TiffWriter writer(ImgWriter::Format::TIFF);

    ASSERT_TRUE(writer.init(tempFile, 100, 100, 300.0, 300.0));

    unsigned char* rowData = new unsigned char[100]; // Assuming single channel for simplicity

    EXPECT_TRUE(writer.writeRow(&rowData));

    delete[] rowData;

}



TEST_F(TiffWriterTest_33, Close_ValidState_ReturnsTrue_33) {

    TiffWriter writer(ImgWriter::Format::TIFF);

    ASSERT_TRUE(writer.init(tempFile, 100, 100, 300.0, 300.0));

    EXPECT_TRUE(writer.close());

}



TEST_F(TiffWriterTest_33, SetCompressionString_ValidString_NoCrash_33) {

    TiffWriter writer(ImgWriter::Format::TIFF);

    ASSERT_NO_THROW(writer.setCompressionString("LZW"));

}
