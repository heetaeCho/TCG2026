#include <gtest/gtest.h>
#include "poppler/ImageEmbeddingUtils.cc"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/XRef.h"

using namespace ImageEmbeddingUtils;

class ImageEmbedderTest_1858 : public ::testing::Test {
protected:
    XRef *xref;

    void SetUp() override {
        xref = new XRef();
    }

    void TearDown() override {
        delete xref;
    }
};

// Test that createImageDict returns a non-null Dict pointer
TEST_F(ImageEmbedderTest_1858, CreateImageDictReturnsNonNull_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 200, 8);
    ASSERT_NE(dict, nullptr);
    delete dict;
}

// Test that the Type key is set to "XObject"
TEST_F(ImageEmbedderTest_1858, CreateImageDictSetsType_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 200, 8);
    ASSERT_NE(dict, nullptr);
    EXPECT_TRUE(dict->hasKey("Type"));
    Object typeObj = dict->lookup("Type");
    EXPECT_EQ(typeObj.getType(), objName);
    EXPECT_STREQ(typeObj.getName(), "XObject");
    delete dict;
}

// Test that the Subtype key is set to "Image"
TEST_F(ImageEmbedderTest_1858, CreateImageDictSetsSubtype_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 200, 8);
    ASSERT_NE(dict, nullptr);
    EXPECT_TRUE(dict->hasKey("Subtype"));
    Object subtypeObj = dict->lookup("Subtype");
    EXPECT_EQ(subtypeObj.getType(), objName);
    EXPECT_STREQ(subtypeObj.getName(), "Image");
    delete dict;
}

// Test that ColorSpace is correctly set to DeviceRGB
TEST_F(ImageEmbedderTest_1858, CreateImageDictSetsColorSpaceDeviceRGB_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 200, 8);
    ASSERT_NE(dict, nullptr);
    EXPECT_TRUE(dict->hasKey("ColorSpace"));
    Object csObj = dict->lookup("ColorSpace");
    EXPECT_EQ(csObj.getType(), objName);
    EXPECT_STREQ(csObj.getName(), "DeviceRGB");
    delete dict;
}

// Test that ColorSpace is correctly set to DeviceGray
TEST_F(ImageEmbedderTest_1858, CreateImageDictSetsColorSpaceDeviceGray_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceGray", 50, 50, 1);
    ASSERT_NE(dict, nullptr);
    Object csObj = dict->lookup("ColorSpace");
    EXPECT_EQ(csObj.getType(), objName);
    EXPECT_STREQ(csObj.getName(), "DeviceGray");
    delete dict;
}

// Test that ColorSpace is correctly set to DeviceCMYK
TEST_F(ImageEmbedderTest_1858, CreateImageDictSetsColorSpaceDeviceCMYK_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceCMYK", 300, 400, 8);
    ASSERT_NE(dict, nullptr);
    Object csObj = dict->lookup("ColorSpace");
    EXPECT_EQ(csObj.getType(), objName);
    EXPECT_STREQ(csObj.getName(), "DeviceCMYK");
    delete dict;
}

// Test that Width is correctly set
TEST_F(ImageEmbedderTest_1858, CreateImageDictSetsWidth_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 640, 480, 8);
    ASSERT_NE(dict, nullptr);
    EXPECT_TRUE(dict->hasKey("Width"));
    Object widthObj = dict->lookup("Width");
    EXPECT_EQ(widthObj.getType(), objInt);
    EXPECT_EQ(widthObj.getInt(), 640);
    delete dict;
}

// Test that Height is correctly set
TEST_F(ImageEmbedderTest_1858, CreateImageDictSetsHeight_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 640, 480, 8);
    ASSERT_NE(dict, nullptr);
    EXPECT_TRUE(dict->hasKey("Height"));
    Object heightObj = dict->lookup("Height");
    EXPECT_EQ(heightObj.getType(), objInt);
    EXPECT_EQ(heightObj.getInt(), 480);
    delete dict;
}

// Test that BitsPerComponent is correctly set
TEST_F(ImageEmbedderTest_1858, CreateImageDictSetsBitsPerComponent_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 200, 8);
    ASSERT_NE(dict, nullptr);
    EXPECT_TRUE(dict->hasKey("BitsPerComponent"));
    Object bpcObj = dict->lookup("BitsPerComponent");
    EXPECT_EQ(bpcObj.getType(), objInt);
    EXPECT_EQ(bpcObj.getInt(), 8);
    delete dict;
}

// Test with BitsPerComponent = 1 (monochrome)
TEST_F(ImageEmbedderTest_1858, CreateImageDictBitsPerComponent1_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceGray", 100, 100, 1);
    ASSERT_NE(dict, nullptr);
    Object bpcObj = dict->lookup("BitsPerComponent");
    EXPECT_EQ(bpcObj.getInt(), 1);
    delete dict;
}

// Test with BitsPerComponent = 16
TEST_F(ImageEmbedderTest_1858, CreateImageDictBitsPerComponent16_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 100, 16);
    ASSERT_NE(dict, nullptr);
    Object bpcObj = dict->lookup("BitsPerComponent");
    EXPECT_EQ(bpcObj.getInt(), 16);
    delete dict;
}

// Test with width = 1 (boundary)
TEST_F(ImageEmbedderTest_1858, CreateImageDictWidthOne_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 1, 1, 8);
    ASSERT_NE(dict, nullptr);
    Object widthObj = dict->lookup("Width");
    EXPECT_EQ(widthObj.getInt(), 1);
    Object heightObj = dict->lookup("Height");
    EXPECT_EQ(heightObj.getInt(), 1);
    delete dict;
}

// Test with large dimensions
TEST_F(ImageEmbedderTest_1858, CreateImageDictLargeDimensions_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 10000, 10000, 8);
    ASSERT_NE(dict, nullptr);
    Object widthObj = dict->lookup("Width");
    EXPECT_EQ(widthObj.getInt(), 10000);
    Object heightObj = dict->lookup("Height");
    EXPECT_EQ(heightObj.getInt(), 10000);
    delete dict;
}

// Test that the dictionary has exactly 6 entries
TEST_F(ImageEmbedderTest_1858, CreateImageDictHasSixEntries_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 200, 8);
    ASSERT_NE(dict, nullptr);
    EXPECT_EQ(dict->getLength(), 6);
    delete dict;
}

// Test with zero width (boundary/edge case)
TEST_F(ImageEmbedderTest_1858, CreateImageDictZeroWidth_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 0, 100, 8);
    ASSERT_NE(dict, nullptr);
    Object widthObj = dict->lookup("Width");
    EXPECT_EQ(widthObj.getInt(), 0);
    delete dict;
}

// Test with zero height (boundary/edge case)
TEST_F(ImageEmbedderTest_1858, CreateImageDictZeroHeight_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 0, 8);
    ASSERT_NE(dict, nullptr);
    Object heightObj = dict->lookup("Height");
    EXPECT_EQ(heightObj.getInt(), 0);
    delete dict;
}

// Test with negative width (edge case)
TEST_F(ImageEmbedderTest_1858, CreateImageDictNegativeWidth_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", -1, 100, 8);
    ASSERT_NE(dict, nullptr);
    Object widthObj = dict->lookup("Width");
    EXPECT_EQ(widthObj.getInt(), -1);
    delete dict;
}

// Test that the XRef pointer is associated with the dict
TEST_F(ImageEmbedderTest_1858, CreateImageDictUsesXRef_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceRGB", 100, 200, 8);
    ASSERT_NE(dict, nullptr);
    EXPECT_EQ(dict->getXRef(), xref);
    delete dict;
}

// Test with BitsPerComponent = 4
TEST_F(ImageEmbedderTest_1858, CreateImageDictBitsPerComponent4_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceGray", 256, 256, 4);
    ASSERT_NE(dict, nullptr);
    Object bpcObj = dict->lookup("BitsPerComponent");
    EXPECT_EQ(bpcObj.getInt(), 4);
    delete dict;
}

// Test with BitsPerComponent = 2
TEST_F(ImageEmbedderTest_1858, CreateImageDictBitsPerComponent2_1858) {
    Dict *dict = ImageEmbedder::createImageDict(xref, "DeviceGray", 128, 128, 2);
    ASSERT_NE(dict, nullptr);
    Object bpcObj = dict->lookup("BitsPerComponent");
    EXPECT_EQ(bpcObj.getInt(), 2);
    delete dict;
}
