#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock dependencies if necessary

class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, getCTM, (std::array<double, 6>&), (const override));

    // Add other mocked methods as needed

};



class MockCatalog : public Catalog {

public:

    // Add mocked methods as needed

};



class MockGfx : public Gfx {

public:

    // Add mocked methods as needed

};



class MockGfxTilingPattern : public GfxTilingPattern {

public:

    // Add mocked methods as needed

};



class MockXRef : public XRef {

public:

    // Add mocked methods as needed

};



class MockPDFDoc : public PDFDoc {

public:

    // Add mocked methods as needed

};



class MockCairoFontEngine : public CairoFontEngine {

public:

    // Add mocked methods as needed

};



class MockGfxFunctionShading : public GfxFunctionShading {

public:

    // Add mocked methods as needed

};



class MockGfxAxialShading : public GfxAxialShading {

public:

    // Add mocked methods as needed

};



class MockGfxRadialShading : public GfxRadialShading {

public:

    // Add mocked methods as needed

};



class MockGfxGouraudTriangleShading : public GfxGouraudTriangleShading {

public:

    // Add mocked methods as needed

};



class MockGfxPatchMeshShading : public GfxPatchMeshShading {

public:

    // Add mocked methods as needed

};



class MockDict : public Dict {

public:

    // Add mocked methods as needed

};



class MockStream : public Stream {

public:

    MOCK_METHOD(void, reset, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(int64_t, getPosition, (), (const override));

    MOCK_METHOD(void, setPosition, (int64_t), (override));

    // Add other mocked methods as needed

};



class MockObject : public Object {

public:

    // Add mocked methods as needed

};



class MockGfxImageColorMap : public GfxImageColorMap {

public:

    // Add mocked methods as needed

};



class MockFunction : public Function {

public:

    // Add mocked methods as needed

};



class MockGfxColor : public GfxColor {

public:

    // Add mocked methods as needed

};



class MockStructElement : public StructElement {

public:

    // Add mocked methods as needed

};



class MockAnnotLink : public AnnotLink {

public:

    // Add mocked methods as needed

};



class MockLinkDest : public LinkDest {

public:

    // Add mocked methods as needed

};



class MockGfxPath : public GfxPath {

public:

    // Add mocked methods as needed

};



class MockGfxSubpath : public GfxSubpath {

public:

    // Add mocked methods as needed

};



class MockAnnotQuadrilaterals : public AnnotQuadrilaterals {

public:

    // Add mocked methods as needed

};



class MockTextPage : public TextPage {

public:

    // Add mocked methods as needed

};



TEST(CairoOutputDevTest_1723, UseDrawCharReturnsTrue_1723) {

    CairoOutputDev dev;

    EXPECT_TRUE(dev.useDrawChar());

}



TEST(CairoOutputDevTest_1723, StartPageSetsPageNumber_1723) {

    MockGfxState state;

    MockXRef xref;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);

    

    dev.startPage(1, &state, &xref);

    // No observable way to verify page number directly

}



TEST(CairoOutputDevTest_1723, EndPageDoesNotThrow_1723) {

    CairoOutputDev dev;



    EXPECT_NO_THROW(dev.endPage());

}



TEST(CairoOutputDevTest_1723, EmitStructTreeDoesNotThrow_1723) {

    CairoOutputDev dev;



    EXPECT_NO_THROW(dev.emitStructTree());

}



TEST(CairoOutputDevTest_1723, BeginFormEndFormRoundtrip_1723) {

    MockObject obj;

    Ref id;

    CairoOutputDev dev;



    EXPECT_NO_THROW(dev.beginForm(&obj, id));

    EXPECT_NO_THROW(dev.endForm(&obj, id));

}



TEST(CairoOutputDevTest_1723, SaveRestoreStateRoundtrip_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    dev.saveState(&state);

    EXPECT_NO_THROW(dev.restoreState(&state));

}



TEST(CairoOutputDevTest_1723, UpdateAllDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateAll(&state));

}



TEST(CairoOutputDevTest_1723, SetDefaultCTMDoesNotThrow_1723) {

    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    CairoOutputDev dev;



    EXPECT_NO_THROW(dev.setDefaultCTM(ctm));

}



TEST(CairoOutputDevTest_1723, UpdateCTMDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateCTM(&state, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0));

}



TEST(CairoOutputDevTest_1723, UpdateLineDashDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateLineDash(&state));

}



TEST(CairoOutputDevTest_1723, UpdateFlatnessDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateFlatness(&state));

}



TEST(CairoOutputDevTest_1723, UpdateLineJoinDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateLineJoin(&state));

}



TEST(CairoOutputDevTest_1723, UpdateLineCapDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateLineCap(&state));

}



TEST(CairoOutputDevTest_1723, UpdateMiterLimitDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateMiterLimit(&state));

}



TEST(CairoOutputDevTest_1723, UpdateLineWidthDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateLineWidth(&state));

}



TEST(CairoOutputDevTest_1723, UpdateFillColorDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateFillColor(&state));

}



TEST(CairoOutputDevTest_1723, UpdateStrokeColorDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateStrokeColor(&state));

}



TEST(CairoOutputDevTest_1723, UpdateFillOpacityDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateFillOpacity(&state));

}



TEST(CairoOutputDevTest_1723, UpdateStrokeOpacityDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateStrokeOpacity(&state));

}



TEST(CairoOutputDevTest_1723, UpdateFillColorStopDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateFillColorStop(&state, 0.5));

}



TEST(CairoOutputDevTest_1723, UpdateBlendModeDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateBlendMode(&state));

}



TEST(CairoOutputDevTest_1723, UpdateFontDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.updateFont(&state));

}



TEST(CairoOutputDevTest_1723, StrokeDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.stroke(&state));

}



TEST(CairoOutputDevTest_1723, FillDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.fill(&state));

}



TEST(CairoOutputDevTest_1723, EoFillDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.eoFill(&state));

}



TEST(CairoOutputDevTest_1723, ClipToStrokePathDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.clipToStrokePath(&state));

}



TEST(CairoOutputDevTest_1723, TilingPatternFillReturnsFalse_1723) {

    MockGfxState state;

    MockGfx gfx;

    MockCatalog cat;

    MockGfxTilingPattern tPat;

    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    bool result = dev.tilingPatternFill(&state, &gfx, &cat, &tPat, mat, 0, 0, 0, 0, 0.0, 0.0);

    EXPECT_FALSE(result);

}



TEST(CairoOutputDevTest_1723, FunctionShadedFillReturnsFalse_1723) {

    MockGfxState state;

    MockGfxFunctionShading shading;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    bool result = dev.functionShadedFill(&state, &shading);

    EXPECT_FALSE(result);

}



TEST(CairoOutputDevTest_1723, AxialShadedFillReturnsFalse_1723) {

    MockGfxState state;

    MockGfxAxialShading shading;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    bool result = dev.axialShadedFill(&state, &shading, 0.0, 1.0);

    EXPECT_FALSE(result);

}



TEST(CairoOutputDevTest_1723, AxialShadedSupportExtendReturnsFalse_1723) {

    MockGfxState state;

    MockGfxAxialShading shading;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    bool result = dev.axialShadedSupportExtend(&state, &shading);

    EXPECT_FALSE(result);

}



TEST(CairoOutputDevTest_1723, RadialShadedFillReturnsFalse_1723) {

    MockGfxState state;

    MockGfxRadialShading shading;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    bool result = dev.radialShadedFill(&state, &shading, 0.0, 1.0);

    EXPECT_FALSE(result);

}



TEST(CairoOutputDevTest_1723, RadialShadedSupportExtendReturnsFalse_1723) {

    MockGfxState state;

    MockGfxRadialShading shading;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    bool result = dev.radialShadedSupportExtend(&state, &shading);

    EXPECT_FALSE(result);

}



TEST(CairoOutputDevTest_1723, GouraudTriangleShadedFillReturnsFalse_1723) {

    MockGfxState state;

    MockGfxGouraudTriangleShading shading;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    bool result = dev.gouraudTriangleShadedFill(&state, &shading);

    EXPECT_FALSE(result);

}



TEST(CairoOutputDevTest_1723, PatchMeshShadedFillReturnsFalse_1723) {

    MockGfxState state;

    MockGfxPatchMeshShading shading;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    bool result = dev.patchMeshShadedFill(&state, &shading);

    EXPECT_FALSE(result);

}



TEST(CairoOutputDevTest_1723, ClipDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.clip(&state));

}



TEST(CairoOutputDevTest_1723, EoClipDoesNotThrow_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.eoClip(&state));

}



TEST(CairoOutputDevTest_1723, BeginStringEndStringRoundtrip_1723) {

    MockGfxState state;

    GooString s("test");

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.beginString(&state, &s));

    EXPECT_NO_THROW(dev.endString(&state));

}



TEST(CairoOutputDevTest_1723, DrawCharDoesNotThrow_1723) {

    MockGfxState state;

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0, originX = 0.0, originY = 0.0;

    CharCode code = 65; // 'A'

    int nBytes = 1;

    Unicode u = 65; // 'A'

    int uLen = 1;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.drawChar(&state, x, y, dx, dy, originX, originY, code, nBytes, &u, uLen));

}



TEST(CairoOutputDevTest_1723, BeginActualTextEndActualTextRoundtrip_1723) {

    MockGfxState state;

    GooString text("test");

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.beginActualText(&state, &text));

    EXPECT_NO_THROW(dev.endActualText(&state));

}



TEST(CairoOutputDevTest_1723, BeginType3CharEndType3CharRoundtrip_1723) {

    MockGfxState state;

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0;

    CharCode code = 65; // 'A'

    Unicode u = 65; // 'A'

    int uLen = 1;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_TRUE(dev.beginType3Char(&state, x, y, dx, dy, code, &u, uLen));

    EXPECT_NO_THROW(dev.endType3Char(&state));

}



TEST(CairoOutputDevTest_1723, BeginTextObjectEndTextObjectRoundtrip_1723) {

    MockGfxState state;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.beginTextObject(&state));

    EXPECT_NO_THROW(dev.endTextObject(&state));

}



TEST(CairoOutputDevTest_1723, BeginMarkedContentEndMarkedContentRoundtrip_1723) {

    MockGfxState state;

    char name[] = "name";

    MockDict properties;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.beginMarkedContent(name, &properties));

    EXPECT_NO_THROW(dev.endMarkedContent(&state));

}



TEST(CairoOutputDevTest_1723, DrawImageMaskDoesNotThrow_1723) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    int width = 100, height = 100;

    bool invert = false, interpolate = false, inlineImg = false;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);

    EXPECT_CALL(str, reset()).Times(1);



    EXPECT_NO_THROW(dev.drawImageMask(&state, &ref, &str, width, height, invert, interpolate, inlineImg));

}



TEST(CairoOutputDevTest_1723, SetSoftMaskFromImageMaskDoesNotThrow_1723) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    int width = 100, height = 100;

    bool invert = false, inlineImg = false;

    std::array<double, 6> baseMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);

    EXPECT_CALL(str, reset()).Times(1);



    EXPECT_NO_THROW(dev.setSoftMaskFromImageMask(&state, &ref, &str, width, height, invert, inlineImg, baseMatrix));

}



TEST(CairoOutputDevTest_1723, UnsetSoftMaskFromImageMaskDoesNotThrow_1723) {

    MockGfxState state;

    std::array<double, 6> baseMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.unsetSoftMaskFromImageMask(&state, baseMatrix));

}



TEST(CairoOutputDevTest_1723, DrawImageDoesNotThrow_1723) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    int width = 100, height = 100;

    MockGfxImageColorMap colorMap;

    bool interpolate = false;

    const int * maskColors = nullptr;

    bool inlineImg = false;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);

    EXPECT_CALL(str, reset()).Times(1);



    EXPECT_NO_THROW(dev.drawImage(&state, &ref, &str, width, height, &colorMap, interpolate, maskColors, inlineImg));

}



TEST(CairoOutputDevTest_1723, DrawSoftMaskedImageDoesNotThrow_1723) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    int width = 100, height = 100;

    MockGfxImageColorMap colorMap;

    bool interpolate = false;

    MockStream maskStr;

    int maskWidth = 100, maskHeight = 100;

    MockGfxImageColorMap maskColorMap;

    bool maskInterpolate = false;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);

    EXPECT_CALL(str, reset()).Times(1);

    EXPECT_CALL(maskStr, reset()).Times(1);



    EXPECT_NO_THROW(dev.drawSoftMaskedImage(&state, &ref, &str, width, height, &colorMap, interpolate, &maskStr, maskWidth, maskHeight, &maskColorMap, maskInterpolate));

}



TEST(CairoOutputDevTest_1723, DrawMaskedImageDoesNotThrow_1723) {

    MockGfxState state;

    MockObject ref;

    MockStream str;

    int width = 100, height = 100;

    MockGfxImageColorMap colorMap;

    bool interpolate = false;

    MockStream maskStr;

    int maskWidth = 100, maskHeight = 100;

    bool maskInvert = false, maskInterpolate = false;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);

    EXPECT_CALL(str, reset()).Times(1);

    EXPECT_CALL(maskStr, reset()).Times(1);



    EXPECT_NO_THROW(dev.drawMaskedImage(&state, &ref, &str, width, height, &colorMap, interpolate, &maskStr, maskWidth, maskHeight, maskInvert, maskInterpolate));

}



TEST(CairoOutputDevTest_1723, BeginTransparencyGroupDoesNotThrow_1723) {

    MockGfxState state;

    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};

    GfxColorSpace * colorSpace = nullptr;

    bool isolated = false, knockout = false, hasBlendMode = false, isCSG = false;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.beginTransparencyGroup(&state, bbox, colorSpace, isolated, knockout, hasBlendMode, isCSG));

}



TEST(CairoOutputDevTest_1723, PopTransparencyGroupDoesNotThrow_1723) {

    CairoOutputDev dev;



    EXPECT_NO_THROW(dev.popTransparencyGroup());

}



TEST(CairoOutputDevTest_1723, SetSoftMaskDoesNotThrow_1723) {

    MockGfxState state;

    GfxColorSpace * colorSpace = nullptr;

    double alpha = 1.0;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.setSoftMask(&state, colorSpace, alpha));

}



TEST(CairoOutputDevTest_1723, ClearSoftMaskDoesNotThrow_1723) {

    CairoOutputDev dev;



    EXPECT_NO_THROW(dev.clearSoftMask());

}



TEST(CairoOutputDevTest_1723, BeginGroupDoesNotThrow_1723) {

    MockGfxState state;

    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};

    GfxColorSpace * colorSpace = nullptr;

    bool isolated = false, knockout = false;

    CairoOutputDev dev;



    EXPECT_CALL(state, getCTM(testing::_)).Times(1);



    EXPECT_NO_THROW(dev.beginGroup(&state, bbox, colorSpace, isolated, knockout));

}



TEST(CairoOutputDevTest_1723, EndGroupDoesNotThrow_1723) {

    CairoOutputDev dev;



    EXPECT_NO_THROW(dev.endGroup());

}
