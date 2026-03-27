#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/CairoFontEngine.cc"



using namespace testing;



class type3_font_info_t_Test : public ::testing::Test {

protected:

    std::shared_ptr<GfxFont> font;

    PDFDoc *doc;

    CairoFontEngine *fontEngine;

    CairoOutputDev *outputDev;

    Gfx *gfx;

    type3_font_info_t *info;



    void SetUp() override {

        font = std::make_shared<GfxFont>();

        doc = new PDFDoc();

        fontEngine = new CairoFontEngine();

        outputDev = new CairoOutputDev();

        gfx = new Gfx();



        info = new type3_font_info_t(font, doc, fontEngine, outputDev, gfx);

    }



    void TearDown() override {

        delete info;

        delete gfx;

        delete outputDev;

        delete fontEngine;

        delete doc;

    }

};



TEST_F(type3_font_info_t_Test_1751, FreeType3FontInfo_DeletesOutputDev_1751) {

    EXPECT_CALL(*outputDev, ~CairoOutputDev()).Times(1);

    _free_type3_font_info(info);

}



TEST_F(type3_font_info_t_Test_1751, FreeType3FontInfo_DeletesGfx_1751) {

    EXPECT_CALL(*gfx, ~Gfx()).Times(1);

    _free_type3_font_info(info);

}



TEST_F(type3_font_info_t_Test_1751, FreeType3FontInfo_DeletesType3FontInfo_1751) {

    EXPECT_NE(info, nullptr);

    _free_type3_font_info(info);

    info = nullptr;

}

```


