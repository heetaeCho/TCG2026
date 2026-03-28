#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/ImageEmbeddingUtils.cc"
#include "./TestProjects/poppler/poppler/XRef.h"
#include "./TestProjects/poppler/poppler/Dict.h"

using namespace testing;

// Mock for XRef class
class MockXRef : public XRef {
public:
    MOCK_METHOD(Ref, addStreamObject, (Dict* dict, std::vector<char> buffer, StreamCompression compression), (override));
};

// Test fixture class
class JpegEmbedderTest_1865 : public Test {
protected:
    std::vector<char> fileContent = {'\xFF', '\xD8', '\xFF'};  // Sample JPEG data
    int width = 1024;
    int height = 768;
    MockXRef mockXRef;

    JpegEmbedderTest_1865() : embedder(width, height, std::move(fileContent)) {}

    JpegEmbedder embedder;
};

// Test for normal operation
TEST_F(JpegEmbedderTest_1865, EmbedImage_NormalOperation_1865) {
    Dict *mockDict = new Dict(&mockXRef);
    Ref expectedRef{1, 0}; // Expected return value
    std::vector<char> mockBuffer = {'\xFF', '\xD8'};  // Mocked JPEG stream

    // Set up the mock expectations
    EXPECT_CALL(mockXRef, addStreamObject(mockDict, mockBuffer, StreamCompression::None))
        .WillOnce(Return(expectedRef));

    // Call the function under test
    Ref result = embedder.embedImage(&mockXRef);

    // Verify the result
    EXPECT_EQ(result.num, expectedRef.num);
    EXPECT_EQ(result.gen, expectedRef.gen);
}

// Test for boundary condition with empty file content
TEST_F(JpegEmbedderTest_1865, EmbedImage_EmptyFileContent_1865) {
    JpegEmbedder emptyEmbedder(1024, 768, {});  // Empty content
    Ref result = emptyEmbedder.embedImage(&mockXRef);

    // Expect an invalid reference as the content is empty
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test for boundary condition with extremely large image dimensions
TEST_F(JpegEmbedderTest_1865, EmbedImage_LargeDimensions_1865) {
    JpegEmbedder largeEmbedder(10000, 10000, std::move(fileContent));
    Ref expectedRef{1, 0};

    Dict *mockDict = new Dict(&mockXRef);
    std::vector<char> mockBuffer = {'\xFF', '\xD8'};

    // Set up the mock expectations
    EXPECT_CALL(mockXRef, addStreamObject(mockDict, mockBuffer, StreamCompression::None))
        .WillOnce(Return(expectedRef));

    // Call the function under test
    Ref result = largeEmbedder.embedImage(&mockXRef);

    // Verify the result
    EXPECT_EQ(result.num, expectedRef.num);
    EXPECT_EQ(result.gen, expectedRef.gen);
}

// Test for exceptional case where addStreamObject fails
TEST_F(JpegEmbedderTest_1865, EmbedImage_FailureInAddStreamObject_1865) {
    Dict *mockDict = new Dict(&mockXRef);
    std::vector<char> mockBuffer = {'\xFF', '\xD8'};

    // Set up the mock expectations to simulate failure
    EXPECT_CALL(mockXRef, addStreamObject(mockDict, mockBuffer, StreamCompression::None))
        .WillOnce(Return(Ref::INVALID()));

    // Call the function under test
    Ref result = embedder.embedImage(&mockXRef);

    // Verify that the result is invalid
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}