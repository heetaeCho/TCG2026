#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/CairoOutputDev.h"



class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockObject : public Object {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockStream : public Stream {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockGfxImageColorMap : public GfxImageColorMap {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockFunction : public Function {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockGfxColor : public GfxColor {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockCatalog : public Catalog {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockGfxTilingPattern : public GfxTilingPattern {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockGfxAxialShading : public GfxAxialShading {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockGfxRadialShading : public GfxRadialShading {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class CairoImageOutputDevTest_1743 : public ::testing::Test {

protected:

    CairoImageOutputDev output_dev;

    NiceMock<MockGfxState> mock_state;

    NiceMock<MockObject> mock_ref;

    NiceMock<MockStream> mock_str;

    NiceMock<MockGfxImageColorMap> mock_color_map;

    NiceMock<Function> mock_transfer_func;

    NiceMock<GfxColor> mock_backdrop_color;

    NiceMock<Catalog> mock_cat;

    NiceMock<GfxTilingPattern> mock_t_pat;

    NiceMock<GfxAxialShading> mock_shading_axial;

    NiceMock<GfxRadialShading> mock_shading_radial;



    static bool imgDrawCbk(int img_id, void *data) {

        return true;

    }

};



TEST_F(CairoImageOutputDevTest_1743, InterpretType3Chars_ReturnsFalse_1743) {

    EXPECT_FALSE(output_dev.interpretType3Chars());

}



TEST_F(CairoImageOutputDevTest_1743, DrawImageMask_DoesNotCrashOnValidInput_1743) {

    output_dev.drawImageMask(&mock_state, &mock_ref, &mock_str, 100, 100, false, false, false);

}



TEST_F(CairoImageOutputDevTest_1743, DrawImage_DoesNotCrashOnValidInput_1743) {

    output_dev.drawImage(&mock_state, &mock_ref, &mock_str, 100, 100, &mock_color_map, false, nullptr, false);

}



TEST_F(CairoImageOutputDevTest_1743, DrawSoftMaskedImage_DoesNotCrashOnValidInput_1743) {

    output_dev.drawSoftMaskedImage(&mock_state, &mock_ref, &mock_str, 100, 100, &mock_color_map, false,

                                   &mock_str, 100, 100, &mock_color_map, false);

}



TEST_F(CairoImageOutputDevTest_1743, DrawMaskedImage_DoesNotCrashOnValidInput_1743) {

    output_dev.drawMaskedImage(&mock_state, &mock_ref, &mock_str, 100, 100, &mock_color_map, false,

                                &mock_str, 100, 100, false, false);

}



TEST_F(CairoImageOutputDevTest_1743, SetSoftMaskFromImageMask_DoesNotCrashOnValidInput_1743) {

    std::array<double, 6> base_matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    output_dev.setSoftMaskFromImageMask(&mock_state, &mock_ref, &mock_str, 100, 100, false, false, base_matrix);

}



TEST_F(CairoImageOutputDevTest_1743, UpsideDown_ReturnsFalseByDefault_1743) {

    EXPECT_FALSE(output_dev.upsideDown());

}



TEST_F(CairoImageOutputDevTest_1743, UseDrawChar_ReturnsTrueByDefault_1743) {

    EXPECT_TRUE(output_dev.useDrawChar());

}



TEST_F(CairoImageOutputDevTest_1743, UseTilingPatternFill_ReturnsFalseByDefault_1743) {

    EXPECT_FALSE(output_dev.useTilingPatternFill());

}



TEST_F(CairoImageOutputDevTest_1743, UseShadedFills_ReturnsFalseForAllTypes_1743) {

    for (int type = 0; type <= 2; ++type) { // Assuming types are 0, 1, 2

        EXPECT_FALSE(output_dev.useShadedFills(type));

    }

}



TEST_F(CairoImageOutputDevTest_1743, UseFillColorStop_ReturnsFalseByDefault_1743) {

    EXPECT_FALSE(output_dev.useFillColorStop());

}



TEST_F(CairoImageOutputDevTest_1743, NeedNonText_ReturnsTrueByDefault_1743) {

    EXPECT_TRUE(output_dev.needNonText());

}



TEST_F(CairoImageOutputDevTest_1743, SetImageDrawDecideCbk_SetsCallback_1743) {

    output_dev.setImageDrawDecideCbk(imgDrawCbk, nullptr);

    // Cannot directly verify internal state, but this should not crash

}



TEST_F(CairoImageOutputDevTest_1743, GetNumImages_ReturnsZeroInitially_1743) {

    EXPECT_EQ(output_dev.getNumImages(), 0);

}
