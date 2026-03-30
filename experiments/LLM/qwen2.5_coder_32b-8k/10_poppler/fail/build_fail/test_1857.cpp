#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace ImageEmbeddingUtils {

    static bool checkMagicNum(const char *fileContent, const uint8_t *magicNum, const uint8_t size);

}



class ImageEmbeddingUtilsTest : public ::testing::Test {

protected:

    const uint8_t magicNum[3] = {0x89, 0x50, 0x4E}; // Example PNG magic number

    const char validPngFileContent[6] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A};

    const char invalidFileContent[6] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10}; // Example JPEG magic number

};



TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_ValidInput_ReturnsTrue_1857) {

    EXPECT_TRUE(ImageEmbeddingUtils::checkMagicNum(validPngFileContent, magicNum, sizeof(magicNum)));

}



TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_InvalidInput_ReturnsFalse_1857) {

    EXPECT_FALSE(ImageEmbeddingUtils::checkMagicNum(invalidFileContent, magicNum, sizeof(magicNum)));

}



TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_PartialMatch_ReturnsFalse_1857) {

    const char partialMatchFileContent[6] = {0x89, 0x50, 0xFF, 0x47, 0x0D, 0x0A};

    EXPECT_FALSE(ImageEmbeddingUtils::checkMagicNum(partialMatchFileContent, magicNum, sizeof(magicNum)));

}



TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_SmallSize_ReturnsTrue_1857) {

    const uint8_t smallMagicNum[2] = {0x89, 0x50};

    EXPECT_TRUE(ImageEmbeddingUtils::checkMagicNum(validPngFileContent, smallMagicNum, sizeof(smallMagicNum)));

}



TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_ZeroSize_ReturnsTrue_1857) {

    const uint8_t zeroSizeMagicNum[0] = {};

    EXPECT_TRUE(ImageEmbeddingUtils::checkMagicNum(validPngFileContent, zeroSizeMagicNum, sizeof(zeroSizeMagicNum)));

}



TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_NullPointer_ReturnsFalse_1857) {

    EXPECT_FALSE(ImageEmbeddingUtils::checkMagicNum(nullptr, magicNum, sizeof(magicNum)));

    EXPECT_FALSE(ImageEmbeddingUtils::checkMagicNum(validPngFileContent, nullptr, sizeof(magicNum)));

}



TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_SizeLargerThanInput_ReturnsFalse_1857) {

    const uint8_t largeMagicNum[6] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A};

    EXPECT_FALSE(ImageEmbeddingUtils::checkMagicNum(validPngFileContent, largeMagicNum, sizeof(largeMagicNum)));

}
