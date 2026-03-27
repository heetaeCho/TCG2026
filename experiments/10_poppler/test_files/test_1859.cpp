#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include "TestProjects/poppler/poppler/ImageEmbeddingUtils.cc"



using namespace ImageEmbeddingUtils;

using ::testing::_;

using ::testing::InSequence;



class PngEmbedderLibpngInputStreamTest : public ::testing::Test {

protected:

    std::vector<char> testFileContent = {'H', 'e', 'l', 'l', 'o'};

    LibpngInputStream *stream;



    void SetUp() override {

        stream = new LibpngInputStream(std::move(testFileContent));

    }



    void TearDown() override {

        delete stream;

    }

};



TEST_F(PngEmbedderLibpngInputStreamTest_1859, ReadCallbackReadsFullSize_1859) {

    png_structp png = nullptr; // Placeholder for actual usage

    std::vector<png_byte> outBuffer(5);

    png_size_t size = 5;



    LibpngInputStream::readCallback(png, outBuffer.data(), size);



    EXPECT_EQ(outBuffer, testFileContent);

}



TEST_F(PngEmbedderLibpngInputStreamTest_1859, ReadCallbackReadsPartialSize_1859) {

    png_structp png = nullptr; // Placeholder for actual usage

    std::vector<png_byte> outBuffer(3);

    png_size_t size = 3;



    LibpngInputStream::readCallback(png, outBuffer.data(), size);



    EXPECT_EQ(outBuffer, std::vector<char>(testFileContent.begin(), testFileContent.begin() + 3));

}



TEST_F(PngEmbedderLibpngInputStreamTest_1859, ReadCallbackReadsBeyondEnd_1859) {

    png_structp png = nullptr; // Placeholder for actual usage

    std::vector<png_byte> outBuffer(10);

    png_size_t size = 10;



    LibpngInputStream::readCallback(png, outBuffer.data(), size);



    EXPECT_EQ(outBuffer, testFileContent);

}



TEST_F(PngEmbedderLibpngInputStreamTest_1859, ReadCallbackNoStream_1859) {

    png_structp png = nullptr; // Placeholder for actual usage

    std::vector<png_byte> outBuffer(5);

    png_size_t size = 5;



    stream->m_iterator = nullptr;

    LibpngInputStream::readCallback(png, outBuffer.data(), size);



    EXPECT_EQ(outBuffer, std::vector<char>(5, '\0'));

}
