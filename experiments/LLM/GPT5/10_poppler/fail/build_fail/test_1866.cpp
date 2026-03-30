#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XRef.h"
#include "GooFile.h"
#include "ImageEmbeddingUtils.h"

// Mocks for external dependencies
class MockGooFile : public GooFile {
public:
    MockGooFile(int fdA) : GooFile(fdA) {}
    MOCK_METHOD(int, read, (char* buf, int n, Goffset offset), (const, override));
    MOCK_METHOD(Goffset, size, (), (const, override));
};

class MockXRef : public XRef {
public:
    MOCK_METHOD(Ref, addStreamObject, (Dict* dict, int buffer, StreamCompression compression), (override));
};

// Test fixture for the ImageEmbeddingUtils::embed function
class ImageEmbeddingUtilsTest : public ::testing::Test {
protected:
    // Mock objects
    MockXRef xref;
    MockGooFile imageFile;

    // Function to help test the embed function
    Ref embedImage(const GooFile& imageFile) {
        // Create a GooFile object mock and set expectations
        std::unique_ptr<GooFile> mockFile = std::make_unique<MockGooFile>(imageFile);
        
        // Call the actual function to be tested
        return ImageEmbeddingUtils::embed(&xref, *mockFile);
    }
};

// Test case for normal operation
TEST_F(ImageEmbeddingUtilsTest, embed_SuccessfulEmbed_1866) {
    // Setup mock behavior
    EXPECT_CALL(imageFile, size())
        .WillOnce(testing::Return(100));  // Pretend the file size is 100 bytes
    EXPECT_CALL(imageFile, read(testing::_, testing::_, testing::_))
        .WillOnce(testing::Return(100));  // Simulate successful read

    // Simulate PNG magic number in the file
    std::vector<char> fileContent(100, 0);  // Just some mock data
    EXPECT_CALL(xref, addStreamObject(testing::_, testing::_, testing::_))
        .WillOnce(testing::Return(Ref{1, 1}));  // Simulate a successful addition of the stream

    // Execute test
    Ref result = embedImage(imageFile);
    
    // Validate result
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.num, 1);
    EXPECT_EQ(result.gen, 1);
}

// Test case for file size being negative (error case)
TEST_F(ImageEmbeddingUtilsTest, embed_NegativeFileSize_1867) {
    // Setup mock behavior
    EXPECT_CALL(imageFile, size())
        .WillOnce(testing::Return(-1));  // Simulate negative file size
    
    // Execute test
    Ref result = embedImage(imageFile);
    
    // Validate result
    EXPECT_FALSE(result.isValid());
}

// Test case for file size exceeding max allowed (error case)
TEST_F(ImageEmbeddingUtilsTest, embed_FileSizeTooBig_1868) {
    // Setup mock behavior
    EXPECT_CALL(imageFile, size())
        .WillOnce(testing::Return(std::numeric_limits<Goffset>::max()));  // Simulate too big file size
    
    // Execute test
    Ref result = embedImage(imageFile);
    
    // Validate result
    EXPECT_FALSE(result.isValid());
}

// Test case for unsuccessful file read (error case)
TEST_F(ImageEmbeddingUtilsTest, embed_UnsuccessfulRead_1869) {
    // Setup mock behavior
    EXPECT_CALL(imageFile, size())
        .WillOnce(testing::Return(100));  // Simulate valid file size
    EXPECT_CALL(imageFile, read(testing::_, testing::_, testing::_))
        .WillOnce(testing::Return(50));  // Simulate failed read

    // Execute test
    Ref result = embedImage(imageFile);
    
    // Validate result
    EXPECT_FALSE(result.isValid());
}

// Test case for unsupported image format (error case)
TEST_F(ImageEmbeddingUtilsTest, embed_UnsupportedFormat_1870) {
    // Setup mock behavior
    EXPECT_CALL(imageFile, size())
        .WillOnce(testing::Return(100));  // Simulate valid file size
    EXPECT_CALL(imageFile, read(testing::_, testing::_, testing::_))
        .WillOnce(testing::Return(100));  // Simulate successful read

    // Simulate unsupported format (e.g., not PNG, JPEG, or JPEG2000)
    std::vector<char> fileContent(100, 0);  // Just some mock data
    EXPECT_CALL(xref, addStreamObject(testing::_, testing::_, testing::_))
        .Times(0);  // We shouldn't reach this point due to the unsupported format

    // Execute test
    Ref result = embedImage(imageFile);
    
    // Validate result
    EXPECT_FALSE(result.isValid());
}