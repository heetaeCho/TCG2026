#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/ImageEmbeddingUtils.cc"

#include "TestProjects/poppler/poppler/Dict.h"

#include "TestProjects/poppler/poppler/XRef.h"



using namespace ImageEmbeddingUtils;



// Mock XRef class for testing purposes

class MockXRef : public XRef {

public:

    MOCK_METHOD0(getRootNum, int());

    MOCK_METHOD0(getRootGen, int());

};



TEST_F(ImageEmbedderTest_1858, CreateImageDict_ValidParameters_ReturnsValidDict_1858) {

    MockXRef mockXRef;

    const char* colorSpace = "DeviceRGB";

    int width = 640;

    int height = 480;

    int bitsPerComponent = 8;



    Dict* imageDict = ImageEmbedder::createImageDict(&mockXRef, colorSpace, width, height, bitsPerComponent);



    ASSERT_NE(imageDict, nullptr);

    EXPECT_EQ(imageDict->lookupNF("Type").isName("XObject"), true);

    EXPECT_EQ(imageDict->lookupNF("Subtype").isName("Image"), true);

    EXPECT_EQ(imageDict->lookupNF("ColorSpace").isName(colorSpace), true);

    EXPECT_EQ(imageDict->lookupNF("Width").getInt(), width);

    EXPECT_EQ(imageDict->lookupNF("Height").getInt(), height);

    EXPECT_EQ(imageDict->lookupNF("BitsPerComponent").getInt(), bitsPerComponent);



    delete imageDict;

}



TEST_F(ImageEmbedderTest_1858, CreateImageDict_ZeroDimensions_ReturnsValidDict_1858) {

    MockXRef mockXRef;

    const char* colorSpace = "DeviceRGB";

    int width = 0;

    int height = 0;

    int bitsPerComponent = 8;



    Dict* imageDict = ImageEmbedder::createImageDict(&mockXRef, colorSpace, width, height, bitsPerComponent);



    ASSERT_NE(imageDict, nullptr);

    EXPECT_EQ(imageDict->lookupNF("Width").getInt(), width);

    EXPECT_EQ(imageDict->lookupNF("Height").getInt(), height);



    delete imageDict;

}



TEST_F(ImageEmbedderTest_1858, CreateImageDict_NegativeDimensions_ReturnsValidDictWithZero_1858) {

    MockXRef mockXRef;

    const char* colorSpace = "DeviceRGB";

    int width = -640;

    int height = -480;

    int bitsPerComponent = 8;



    Dict* imageDict = ImageEmbedder::createImageDict(&mockXRef, colorSpace, width, height, bitsPerComponent);



    ASSERT_NE(imageDict, nullptr);

    EXPECT_EQ(imageDict->lookupNF("Width").getInt(), 0);

    EXPECT_EQ(imageDict->lookupNF("Height").getInt(), 0);



    delete imageDict;

}



TEST_F(ImageEmbedderTest_1858, CreateImageDict_ZeroBitsPerComponent_ReturnsValidDict_1858) {

    MockXRef mockXRef;

    const char* colorSpace = "DeviceRGB";

    int width = 640;

    int height = 480;

    int bitsPerComponent = 0;



    Dict* imageDict = ImageEmbedder::createImageDict(&mockXRef, colorSpace, width, height, bitsPerComponent);



    ASSERT_NE(imageDict, nullptr);

    EXPECT_EQ(imageDict->lookupNF("BitsPerComponent").getInt(), bitsPerComponent);



    delete imageDict;

}



TEST_F(ImageEmbedderTest_1858, CreateImageDict_NullColorSpace_ReturnsValidDictWithDefaultColorSpace_1858) {

    MockXRef mockXRef;

    const char* colorSpace = nullptr;

    int width = 640;

    int height = 480;

    int bitsPerComponent = 8;



    Dict* imageDict = ImageEmbedder::createImageDict(&mockXRef, colorSpace, width, height, bitsPerComponent);



    ASSERT_NE(imageDict, nullptr);

    EXPECT_EQ(imageDict->lookupNF("ColorSpace").isName(""), true); // Assuming default is empty string if null



    delete imageDict;

}
