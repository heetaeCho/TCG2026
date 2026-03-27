#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

namespace ImageEmbeddingUtils {

// Declare the function in the same namespace for testing
static bool checkMagicNum(const char *fileContent, const uint8_t *magicNum, const uint8_t size) {
    return (memcmp(fileContent, magicNum, size) == 0);
}

}  // namespace ImageEmbeddingUtils

// Test case class
class ImageEmbeddingUtilsTest_1857 : public testing::Test {
protected:
    // Setup and teardown code can be added here
    void SetUp() override {
        // Setup code
    }

    void TearDown() override {
        // Cleanup code
    }
};

// Test normal operation: matching file content and magic number
TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_Matching_1857) {
    const char fileContent[] = {0x01, 0x02, 0x03, 0x04};
    const uint8_t magicNum[] = {0x01, 0x02, 0x03, 0x04};
    uint8_t size = 4;

    EXPECT_TRUE(ImageEmbeddingUtils::checkMagicNum(fileContent, magicNum, size));
}

// Test boundary condition: empty file content and magic number
TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_EmptyContent_1857) {
    const char fileContent[] = {};
    const uint8_t magicNum[] = {};
    uint8_t size = 0;

    EXPECT_TRUE(ImageEmbeddingUtils::checkMagicNum(fileContent, magicNum, size));
}

// Test boundary condition: file content smaller than magic number
TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_SmallContent_1857) {
    const char fileContent[] = {0x01, 0x02};
    const uint8_t magicNum[] = {0x01, 0x02, 0x03};
    uint8_t size = 3;

    EXPECT_FALSE(ImageEmbeddingUtils::checkMagicNum(fileContent, magicNum, size));
}

// Test exceptional case: different file content and magic number
TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_NonMatching_1857) {
    const char fileContent[] = {0x01, 0x02, 0x03, 0x04};
    const uint8_t magicNum[] = {0x05, 0x06, 0x07, 0x08};
    uint8_t size = 4;

    EXPECT_FALSE(ImageEmbeddingUtils::checkMagicNum(fileContent, magicNum, size));
}

// Test exceptional case: file content larger than magic number
TEST_F(ImageEmbeddingUtilsTest_1857, CheckMagicNum_LargerContent_1857) {
    const char fileContent[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    const uint8_t magicNum[] = {0x01, 0x02, 0x03, 0x04};
    uint8_t size = 4;

    EXPECT_FALSE(ImageEmbeddingUtils::checkMagicNum(fileContent, magicNum, size));
}