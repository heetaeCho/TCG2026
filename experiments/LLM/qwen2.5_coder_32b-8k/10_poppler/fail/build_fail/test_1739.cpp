#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/CairoOutputDev.h"



using ::testing::_;

using ::testing::Return;



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



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class MockGfxColor : public GfxColor {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



class CairoImageOutputDevTest_1739 : public ::testing::Test {

protected:

    CairoImageOutputDev output_dev;

    std::unique_ptr<MockGfxState> mock_state = std::make_unique<MockGfxState>();

    std::unique_ptr<MockObject> mock_ref = std::make_unique<MockObject>();

    std::unique_ptr<MockStream> mock_str = std::make_unique<MockStream>();

    std::unique_ptr<MockGfxImageColorMap> mock_color_map = std::make_unique<MockGfxImageColorMap>();

    std::unique_ptr<MockFunction> mock_transfer_func = std::make_unique<MockFunction>();

    std::unique_ptr<MockCatalog> mock_catalog = std::make_unique<MockCatalog>();

    std::unique_ptr<MockGfxTilingPattern> mock_t_pat = std::make_unique<MockGfxTilingPattern>();

    std::unique_ptr<MockGfxAxialShading> mock_shading_axial = std::make_unique<MockGfxAxialShading>();

    std::unique_ptr<MockGfxRadialShading> mock_shading_radial = std::make_unique<MockGfxRadialShading>();

    std::unique_ptr<MockGfxColorSpace> mock_blending_color_space = std::make_unique<MockGfxColorSpace>();

    std::unique_ptr<MockGfxColor> mock_backdrop_color = std::make_unique<MockGfxColor>();



    std::array<double, 6> base_matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    int width = 10;

    int height = 10;

};



TEST_F(CairoImageOutputDevTest_1739, UseDrawChar_ReturnsFalse_1739) {

    EXPECT_FALSE(output_dev.useDrawChar());

}



TEST_F(CairoImageOutputDevTest_1739, DrawImageMask_NormalOperation_1739) {

    output_dev.drawImageMask(mock_state.get(), mock_ref.get(), mock_str.get(), width, height, false, false, false);

    // No observable behavior to verify in this case

}



TEST_F(CairoImageOutputDevTest_1739, DrawImage_NormalOperation_1739) {

    output_dev.drawImage(mock_state.get(), mock_ref.get(), mock_str.get(), width, height, mock_color_map.get(), false, nullptr, false);

    // No observable behavior to verify in this case

}



TEST_F(CairoImageOutputDevTest_1739, DrawSoftMaskedImage_NormalOperation_1739) {

    output_dev.drawSoftMaskedImage(mock_state.get(), mock_ref.get(), mock_str.get(), width, height, mock_color_map.get(), false,

                                   mock_str.get(), width, height, mock_color_map.get(), false);

    // No observable behavior to verify in this case

}



TEST_F(CairoImageOutputDevTest_1739, DrawMaskedImage_NormalOperation_1739) {

    output_dev.drawMaskedImage(mock_state.get(), mock_ref.get(), mock_str.get(), width, height, mock_color_map.get(), false,

                               mock_str.get(), width, height, false, false);

    // No observable behavior to verify in this case

}



TEST_F(CairoImageOutputDevTest_1739, SetSoftMaskFromImageMask_NormalOperation_1739) {

    output_dev.setSoftMaskFromImageMask(mock_state.get(), mock_ref.get(), mock_str.get(), width, height, false, false, base_matrix);

    // No observable behavior to verify in this case

}



TEST_F(CairoImageOutputDevTest_1739, GetNumImages_DefaultValue_1739) {

    EXPECT_EQ(output_dev.getNumImages(), 0);

}



TEST_F(CairoImageOutputDevTest_1739, SetImageDrawDecideCbk_NormalOperation_1739) {

    bool (*cbk)(int img_id, void *data) = [](int img_id, void *data) { return true; };

    output_dev.setImageDrawDecideCbk(cbk, nullptr);

    // No observable behavior to verify in this case

}



TEST_F(CairoImageOutputDevTest_1739, UpdateAll_NormalOperation_1739) {

    output_dev.updateAll(mock_state.get());

    // No observable behavior to verify in this case

}
