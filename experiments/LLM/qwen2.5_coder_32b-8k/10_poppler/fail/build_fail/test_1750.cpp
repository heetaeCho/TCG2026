#include <gtest/gtest.h>

#include "CairoOutputDev.h"

#include <gmock/gmock.h>



class MockGfxState : public GfxState {

public:

    MOCK_METHOD0(getNumImages, int());

};



class MockObject : public Object {

public:

    MOCK_CONST_METHOD0(isStream, bool());

};



class MockStream : public Stream {

public:

    MOCK_METHOD0(getChar, int());

};



class MockGfxImageColorMap : public GfxImageColorMap {

public:

    MOCK_METHOD2(getColor, void(GfxRGB &, int));

};



class CairoImageOutputDevTest_1750 : public ::testing::Test {

protected:

    CairoImageOutputDev output_dev;

};



TEST_F(CairoImageOutputDevTest_1750, GetNumImages_ReturnsZeroInitially_1750) {

    EXPECT_EQ(output_dev.getNumImages(), 0);

}



TEST_F(CairoImageOutputDevTest_1750, GetImage_OutOfBounds_ReturnsNullptr_1750) {

    EXPECT_EQ(output_dev.getImage(0), nullptr);

}



TEST_F(CairoImageOutputDevTest_1750, DrawImage_ValidParameters_IncreasesNumImages_1750) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    MockGfxImageColorMap colorMap;



    EXPECT_CALL(ref, isStream()).WillOnce(::testing::Return(true));

    

    output_dev.drawImage(&state, &ref, &str, 100, 200, &colorMap, false, nullptr, false);

    EXPECT_EQ(output_dev.getNumImages(), 1);

}



TEST_F(CairoImageOutputDevTest_1750, DrawMaskedImage_ValidParameters_IncreasesNumImages_1750) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    MockStream maskStr;

    MockGfxImageColorMap colorMap;

    MockGfxImageColorMap maskColorMap;



    EXPECT_CALL(ref, isStream()).WillOnce(::testing::Return(true));

    

    output_dev.drawMaskedImage(&state, &ref, &str, 100, 200, &colorMap, false, &maskStr, 50, 100, true, false);

    EXPECT_EQ(output_dev.getNumImages(), 1);

}



TEST_F(CairoImageOutputDevTest_1750, DrawSoftMaskedImage_ValidParameters_IncreasesNumImages_1750) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    MockStream maskStr;

    MockGfxImageColorMap colorMap;

    MockGfxImageColorMap maskColorMap;



    EXPECT_CALL(ref, isStream()).WillOnce(::testing::Return(true));

    

    output_dev.drawSoftMaskedImage(&state, &ref, &str, 100, 200, &colorMap, false, &maskStr, 50, 100, &maskColorMap, false);

    EXPECT_EQ(output_dev.getNumImages(), 1);

}



TEST_F(CairoImageOutputDevTest_1750, DrawImageMask_ValidParameters_IncreasesNumImages_1750) {

    MockGfxState state;

    MockObject ref;

    MockStream str;



    EXPECT_CALL(ref, isStream()).WillOnce(::testing::Return(true));

    

    output_dev.drawImageMask(&state, &ref, &str, 100, 200, false, false, false);

    EXPECT_EQ(output_dev.getNumImages(), 1);

}



TEST_F(CairoImageOutputDevTest_1750, GetImage_ValidIndex_ReturnsNonNullptr_1750) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    MockGfxImageColorMap colorMap;



    EXPECT_CALL(ref, isStream()).WillOnce(::testing::Return(true));

    

    output_dev.drawImage(&state, &ref, &str, 100, 200, &colorMap, false, nullptr, false);

    EXPECT_NE(output_dev.getImage(0), nullptr);

}



TEST_F(CairoImageOutputDevTest_1750, GetImage_OutOfBounds_ReturnsNullptr_AfterDraw_1750) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    MockGfxImageColorMap colorMap;



    EXPECT_CALL(ref, isStream()).WillOnce(::testing::Return(true));

    

    output_dev.drawImage(&state, &ref, &str, 100, 200, &colorMap, false, nullptr, false);

    EXPECT_EQ(output_dev.getImage(1), nullptr);

}
