#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/ImageEmbeddingUtils.cc"
#include "./TestProjects/poppler/poppler/Dict.h"
#include "./TestProjects/poppler/poppler/XRef.h"
#include "./TestProjects/poppler/poppler/Object.h"

// Mock class for XRef since it's used in createImageDict
class MockXRef : public XRef {
public:
    MOCK_METHOD(bool, isEncrypted, (), (const, override));
    MOCK_METHOD(bool, okToPrint, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToPrintHighRes, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToChange, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToCopy, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToAddNotes, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToFillForm, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToAccessibility, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(bool, okToAssemble, (bool ignoreOwnerPW), (const, override));
    MOCK_METHOD(Object, getCatalog, (), (override));
};

// Test fixture for the ImageEmbedder class
class ImageEmbedderTest_1858 : public ::testing::Test {
protected:
    MockXRef* mockXRef;

    void SetUp() override {
        mockXRef = new MockXRef();
    }

    void TearDown() override {
        delete mockXRef;
    }
};

// Test case for createImageDict (normal operation)
TEST_F(ImageEmbedderTest_1858, CreateImageDict_NormalOperation_1858) {
    // Set up mock XRef
    XRef* xref = mockXRef;
    const char* colorSpace = "RGB";
    const int width = 200;
    const int height = 300;
    const int bitsPerComponent = 8;

    // Call the static function createImageDict
    Dict* imageDict = ImageEmbedder::createImageDict(xref, colorSpace, width, height, bitsPerComponent);

    // Verify the values in the Dict object
    ASSERT_NE(imageDict, nullptr);
    EXPECT_EQ(imageDict->lookup("Type", 0).getName(), "XObject");
    EXPECT_EQ(imageDict->lookup("Subtype", 0).getName(), "Image");
    EXPECT_EQ(imageDict->lookup("ColorSpace", 0).getName(), colorSpace);
    EXPECT_EQ(imageDict->lookup("Width", 0).getInt(), width);
    EXPECT_EQ(imageDict->lookup("Height", 0).getInt(), height);
    EXPECT_EQ(imageDict->lookup("BitsPerComponent", 0).getInt(), bitsPerComponent);

    delete imageDict;
}

// Test case for createImageDict (boundary case with minimum values)
TEST_F(ImageEmbedderTest_1858, CreateImageDict_BoundaryCase_MinValues_1858) {
    // Set up mock XRef
    XRef* xref = mockXRef;
    const char* colorSpace = "RGB";
    const int width = 0;  // Minimum value for width
    const int height = 0; // Minimum value for height
    const int bitsPerComponent = 1; // Minimum value for bitsPerComponent

    // Call the static function createImageDict
    Dict* imageDict = ImageEmbedder::createImageDict(xref, colorSpace, width, height, bitsPerComponent);

    // Verify the values in the Dict object
    ASSERT_NE(imageDict, nullptr);
    EXPECT_EQ(imageDict->lookup("Type", 0).getName(), "XObject");
    EXPECT_EQ(imageDict->lookup("Subtype", 0).getName(), "Image");
    EXPECT_EQ(imageDict->lookup("ColorSpace", 0).getName(), colorSpace);
    EXPECT_EQ(imageDict->lookup("Width", 0).getInt(), width);
    EXPECT_EQ(imageDict->lookup("Height", 0).getInt(), height);
    EXPECT_EQ(imageDict->lookup("BitsPerComponent", 0).getInt(), bitsPerComponent);

    delete imageDict;
}

// Test case for createImageDict (boundary case with very large values)
TEST_F(ImageEmbedderTest_1858, CreateImageDict_BoundaryCase_MaxValues_1858) {
    // Set up mock XRef
    XRef* xref = mockXRef;
    const char* colorSpace = "RGB";
    const int width = INT_MAX;  // Maximum value for width
    const int height = INT_MAX; // Maximum value for height
    const int bitsPerComponent = 32; // Maximum value for bitsPerComponent

    // Call the static function createImageDict
    Dict* imageDict = ImageEmbedder::createImageDict(xref, colorSpace, width, height, bitsPerComponent);

    // Verify the values in the Dict object
    ASSERT_NE(imageDict, nullptr);
    EXPECT_EQ(imageDict->lookup("Type", 0).getName(), "XObject");
    EXPECT_EQ(imageDict->lookup("Subtype", 0).getName(), "Image");
    EXPECT_EQ(imageDict->lookup("ColorSpace", 0).getName(), colorSpace);
    EXPECT_EQ(imageDict->lookup("Width", 0).getInt(), width);
    EXPECT_EQ(imageDict->lookup("Height", 0).getInt(), height);
    EXPECT_EQ(imageDict->lookup("BitsPerComponent", 0).getInt(), bitsPerComponent);

    delete imageDict;
}

// Test case for embedImage (assuming the function uses createImageDict internally)
TEST_F(ImageEmbedderTest_1858, EmbedImage_NormalOperation_1858) {
    // Set up mock XRef
    XRef* xref = mockXRef;
    ImageEmbedder embedder(100, 150);

    // Mock the behavior of the Dict creation
    EXPECT_CALL(*mockXRef, isEncrypted()).WillOnce(testing::Return(false));

    // Test the embedImage function (assuming it interacts with XRef)
    Ref ref = embedder.embedImage(xref);

    // Validate that the embedImage returned a valid Ref (simplified assumption here)
    EXPECT_TRUE(ref.isValid());
}