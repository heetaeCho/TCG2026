#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CairoOutputDev.h"

#include "GfxState.h"

#include "XRef.h"



using ::testing::_;

using ::testing::Return;



class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, setDefaultCTM, (const std::array<double, 6> & ctm), (override));

};



class CairoOutputDevTest_1727 : public ::testing::Test {

protected:

    CairoOutputDev output_dev;

    MockGfxState mock_state;

    XRef xref;

};



TEST_F(CairoOutputDevTest_1727, InterpretType3CharsReturnsFalse_1727) {

    EXPECT_FALSE(output_dev.interpretType3Chars());

}



TEST_F(CairoOutputDevTest_1727, StartPageDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.startPage(1, &mock_state, &xref));

}



TEST_F(CairoOutputDevTest_1727, EndPageDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.endPage());

}



TEST_F(CairoOutputDevTest_1727, SaveStateDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.saveState(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, RestoreStateDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.restoreState(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateAllDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateAll(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, SetDefaultCTMDoesNotThrowException_1727) {

    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_NO_THROW(output_dev.setDefaultCTM(ctm));

}



TEST_F(CairoOutputDevTest_1727, UpdateCTMDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateCTM(&mock_state, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0));

}



TEST_F(CairoOutputDevTest_1727, UpdateLineDashDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateLineDash(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateFlatnessDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateFlatness(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateLineJoinDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateLineJoin(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateLineCapDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateLineCap(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateMiterLimitDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateMiterLimit(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateLineWidthDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateLineWidth(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateFillColorDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateFillColor(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateStrokeColorDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateStrokeColor(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateFillOpacityDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateFillOpacity(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateStrokeOpacityDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateStrokeOpacity(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateFillColorStopDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateFillColorStop(&mock_state, 0.5));

}



TEST_F(CairoOutputDevTest_1727, UpdateBlendModeDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateBlendMode(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, UpdateFontDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.updateFont(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, StrokeDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.stroke(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, FillDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.fill(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, EoFillDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.eoFill(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, ClipToStrokePathDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.clipToStrokePath(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, ClipDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.clip(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, EoClipDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.eoClip(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, BeginStringDoesNotThrowException_1727) {

    GooString str("test");

    EXPECT_NO_THROW(output_dev.beginString(&mock_state, &str));

}



TEST_F(CairoOutputDevTest_1727, EndStringDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.endString(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, BeginActualTextDoesNotThrowException_1727) {

    GooString str("test");

    EXPECT_NO_THROW(output_dev.beginActualText(&mock_state, &str));

}



TEST_F(CairoOutputDevTest_1727, EndActualTextDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.endActualText(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, BeginMarkedContentDoesNotThrowException_1727) {

    Dict dict;

    EXPECT_NO_THROW(output_dev.beginMarkedContent("name", &dict));

}



TEST_F(CairoOutputDevTest_1727, EndMarkedContentDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.endMarkedContent(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, BeginTransparencyGroupDoesNotThrowException_1727) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    GfxColorSpace color_space;

    EXPECT_NO_THROW(output_dev.beginTransparencyGroup(&mock_state, bbox, &color_space, false, false, false));

}



TEST_F(CairoOutputDevTest_1727, EndTransparencyGroupDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.endTransparencyGroup(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, PaintTransparencyGroupDoesNotThrowException_1727) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    EXPECT_NO_THROW(output_dev.paintTransparencyGroup(&mock_state, bbox));

}



TEST_F(CairoOutputDevTest_1727, SetSoftMaskDoesNotThrowException_1727) {

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    GfxColor color;

    EXPECT_NO_THROW(output_dev.setSoftMask(&mock_state, bbox, false, nullptr, &color));

}



TEST_F(CairoOutputDevTest_1727, ClearSoftMaskDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.clearSoftMask(&mock_state));

}



TEST_F(CairoOutputDevTest_1727, SetPrintingDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.setPrinting(true));

}



TEST_F(CairoOutputDevTest_1727, SetLogicalStructureDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.setLogicalStructure(true));

}



TEST_F(CairoOutputDevTest_1727, SetType3RenderTypeDoesNotThrowException_1727) {

    EXPECT_NO_THROW(output_dev.setType3RenderType(Type3RenderType::None));

}
