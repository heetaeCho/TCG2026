#include <gtest/gtest.h>
#include <climits>
#include <cstdlib>
#include <cstring>

// Replicate the structures needed to test doLookChar
// Based on openjpeg-style structures that poppler uses

#ifndef EOF
#define EOF (-1)
#endif

#ifndef unlikely
#define unlikely(x) (x)
#endif

struct opj_image_comp_t {
    int *data;
    // Other fields omitted for testing
};

struct opj_image_t {
    opj_image_comp_t *comps;
    // Other fields omitted for testing
};

struct JPXStreamPrivate {
    int counter = 0;
    int ccounter = 0;
    int npixels = 0;
    int ncomps = 0;
    bool inited = false;
    opj_image_t *image = nullptr;
};

// Reproducing the function under test exactly as provided
static inline int doLookChar(JPXStreamPrivate *priv) {
    if (unlikely(priv->counter >= priv->npixels)) {
        return EOF;
    }
    return ((unsigned char *)priv->image->comps[priv->ccounter].data)[priv->counter];
}

class DoLookCharTest_1996 : public ::testing::Test {
protected:
    JPXStreamPrivate priv;
    opj_image_t image;
    opj_image_comp_t comps[4]; // up to 4 components
    int pixelData[256];

    void SetUp() override {
        memset(&priv, 0, sizeof(priv));
        memset(&image, 0, sizeof(image));
        memset(comps, 0, sizeof(comps));
        memset(pixelData, 0, sizeof(pixelData));

        image.comps = comps;
        priv.image = &image;
    }
};

TEST_F(DoLookCharTest_1996, ReturnsEOFWhenCounterEqualsNpixels_1996) {
    priv.counter = 10;
    priv.npixels = 10;
    EXPECT_EQ(EOF, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, ReturnsEOFWhenCounterExceedsNpixels_1996) {
    priv.counter = 15;
    priv.npixels = 10;
    EXPECT_EQ(EOF, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, ReturnsEOFWhenNpixelsIsZero_1996) {
    priv.counter = 0;
    priv.npixels = 0;
    EXPECT_EQ(EOF, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, ReturnsCorrectByteAtCounterZero_1996) {
    pixelData[0] = 42;
    comps[0].data = pixelData;
    priv.counter = 0;
    priv.ccounter = 0;
    priv.npixels = 10;
    EXPECT_EQ(42, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, ReturnsCorrectByteAtNonZeroCounter_1996) {
    // Note: data is int*, but accessed as unsigned char*
    // So we need to set bytes carefully
    unsigned char *bytePtr = (unsigned char *)pixelData;
    bytePtr[5] = 200;
    comps[0].data = pixelData;
    priv.counter = 5;
    priv.ccounter = 0;
    priv.npixels = 100;
    EXPECT_EQ(200, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, ReturnsUnsignedCharValue_1996) {
    // Test that values > 127 are returned as positive (unsigned char)
    unsigned char *bytePtr = (unsigned char *)pixelData;
    bytePtr[0] = 255;
    comps[0].data = pixelData;
    priv.counter = 0;
    priv.ccounter = 0;
    priv.npixels = 10;
    EXPECT_EQ(255, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, UsesCorrectComponent_1996) {
    int pixelData2[256];
    memset(pixelData2, 0, sizeof(pixelData2));
    unsigned char *bytePtr = (unsigned char *)pixelData2;
    bytePtr[3] = 123;
    comps[0].data = pixelData;
    comps[1].data = pixelData2;
    priv.counter = 3;
    priv.ccounter = 1;
    priv.npixels = 100;
    EXPECT_EQ(123, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, ReturnsZeroByte_1996) {
    comps[0].data = pixelData;
    priv.counter = 0;
    priv.ccounter = 0;
    priv.npixels = 10;
    EXPECT_EQ(0, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, CounterJustBeforeNpixels_1996) {
    unsigned char *bytePtr = (unsigned char *)pixelData;
    bytePtr[9] = 77;
    comps[0].data = pixelData;
    priv.counter = 9;
    priv.ccounter = 0;
    priv.npixels = 10;
    EXPECT_EQ(77, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, ReturnsEOFWhenNpixelsNegative_1996) {
    priv.counter = 0;
    priv.npixels = -1;
    EXPECT_EQ(EOF, doLookChar(&priv));
}

TEST_F(DoLookCharTest_1996, DoesNotModifyCounter_1996) {
    unsigned char *bytePtr = (unsigned char *)pixelData;
    bytePtr[3] = 50;
    comps[0].data = pixelData;
    priv.counter = 3;
    priv.ccounter = 0;
    priv.npixels = 10;

    int result1 = doLookChar(&priv);
    int result2 = doLookChar(&priv);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(3, priv.counter);
}

TEST_F(DoLookCharTest_1996, MultipleComponentsAccessCorrectOne_1996) {
    int pixelData0[64], pixelData1[64], pixelData2[64];
    memset(pixelData0, 0, sizeof(pixelData0));
    memset(pixelData1, 0, sizeof(pixelData1));
    memset(pixelData2, 0, sizeof(pixelData2));

    ((unsigned char *)pixelData0)[0] = 10;
    ((unsigned char *)pixelData1)[0] = 20;
    ((unsigned char *)pixelData2)[0] = 30;

    comps[0].data = pixelData0;
    comps[1].data = pixelData1;
    comps[2].data = pixelData2;

    priv.counter = 0;
    priv.npixels = 100;

    priv.ccounter = 0;
    EXPECT_EQ(10, doLookChar(&priv));

    priv.ccounter = 1;
    EXPECT_EQ(20, doLookChar(&priv));

    priv.ccounter = 2;
    EXPECT_EQ(30, doLookChar(&priv));
}
