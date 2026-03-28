#include <gtest/gtest.h>

#include "GfxFont.h"



class GfxFontTest_1142 : public ::testing::Test {

protected:

    std::unique_ptr<GfxFont> createGfxFont() {

        // Mock parameters to create a GfxFont object

        const char* tagA = "MockTag";

        Ref idA(1, 0);

        std::optional<std::string> nameA = "MockName";

        GfxFontType typeA = gfxFontTypeNone;

        Ref embFontIDA(2, 0);



        return GfxFont::makeFont(nullptr, tagA, idA, nullptr, embFontIDA);

    }

};



TEST_F(GfxFontTest_1142, GetStretch_NormalOperation_1142) {

    auto font = createGfxFont();

    Stretch stretch = font->getStretch();



    // Assuming a default value for stretch if not set otherwise

    EXPECT_EQ(stretch, Stretch::Normal);

}



TEST_F(GfxFontTest_1142, GetWeight_NormalOperation_1142) {

    auto font = createGfxFont();

    Weight weight = font->getWeight();



    // Assuming a default value for weight if not set otherwise

    EXPECT_EQ(weight, Weight::Normal);

}



TEST_F(GfxFontTest_1142, IsSubset_NormalOperation_1142) {

    auto font = createGfxFont();

    bool isSubset = font->isSubset();



    // Assuming subset status is false by default if not set otherwise

    EXPECT_FALSE(isSubset);

}



TEST_F(GfxFontTest_1142, GetNameWithoutSubsetTag_NormalOperation_1142) {

    auto font = createGfxFont();

    std::string name = font->getNameWithoutSubsetTag();



    // Assuming the name is returned as is if no subset tag is present

    EXPECT_EQ(name, "MockName");

}



TEST_F(GfxFontTest_1142, GetToUnicode_NormalOperation_1142) {

    auto font = createGfxFont();

    const CharCodeToUnicode* toUnicode = font->getToUnicode();



    // Assuming no Unicode mapping by default

    EXPECT_EQ(toUnicode, nullptr);

}



TEST_F(GfxFontTest_1142, LocateFont_NormalOperation_1142) {

    auto font = createGfxFont();

    XRef* xref = nullptr;

    PSOutputDev* ps = nullptr;

    GooString substituteFontName("SubstituteFont");



    std::optional<GfxFontLoc> loc = font->locateFont(xref, ps, &substituteFontName);



    // Assuming no font location found by default

    EXPECT_FALSE(loc.has_value());

}



TEST_F(GfxFontTest_1142, ReadEmbFontFile_NormalOperation_1142) {

    auto font = createGfxFont();

    XRef* xref = nullptr;



    std::optional<std::vector<unsigned char>> embFontData = font->readEmbFontFile(xref);



    // Assuming no embedded font data by default

    EXPECT_FALSE(embFontData.has_value());

}



TEST_F(GfxFontTest_1142, GetTag_NormalOperation_1142) {

    auto font = createGfxFont();

    std::string tag = font->getTag();



    // Assuming the tag is returned as set during creation

    EXPECT_EQ(tag, "MockTag");

}



TEST_F(GfxFontTest_1142, GetID_NormalOperation_1142) {

    auto font = createGfxFont();

    const Ref* id = font->getID();



    // Assuming the ID is returned as set during creation

    EXPECT_TRUE(id != nullptr);

    EXPECT_EQ(*id, Ref(1, 0));

}



TEST_F(GfxFontTest_1142, Matches_NormalOperation_1142) {

    auto font = createGfxFont();

    bool matches = font->matches("MockTag");



    // Assuming the tag matches as set during creation

    EXPECT_TRUE(matches);

}



TEST_F(GfxFontTest_1142, GetFamily_NormalOperation_1142) {

    auto font = createGfxFont();

    const GooString* family = font->getFamily();



    // Assuming no family name by default

    EXPECT_EQ(family, nullptr);

}



TEST_F(GfxFontTest_1142, GetType_NormalOperation_1142) {

    auto font = createGfxFont();

    GfxFontType type = font->getType();



    // Assuming the type is returned as set during creation

    EXPECT_EQ(type, gfxFontTypeNone);

}



TEST_F(GfxFontTest_1142, IsCIDFont_NormalOperation_1142) {

    auto font = createGfxFont();

    bool isCIDFont = font->isCIDFont();



    // Assuming not a CID font by default

    EXPECT_FALSE(isCIDFont);

}



TEST_F(GfxFontTest_1142, GetEmbeddedFontID_NormalOperation_1142) {

    auto font = createGfxFont();

    Ref embID(0, 0);

    bool hasID = font->getEmbeddedFontID(&embID);



    // Assuming no embedded font ID by default

    EXPECT_FALSE(hasID);

}



TEST_F(GfxFontTest_1142, InvalidateEmbeddedFont_NormalOperation_1142) {

    auto font = createGfxFont();

    bool invalidated = font->invalidateEmbeddedFont();



    // Assuming the operation succeeds but does not change state in this test

    EXPECT_TRUE(invalidated);

}



TEST_F(GfxFontTest_1142, GetEmbeddedFontName_NormalOperation_1142) {

    auto font = createGfxFont();

    const GooString* embFontName = font->getEmbeddedFontName();



    // Assuming no embedded font name by default

    EXPECT_EQ(embFontName, nullptr);

}



TEST_F(GfxFontTest_1142, GetFlags_NormalOperation_1142) {

    auto font = createGfxFont();

    int flags = font->getFlags();



    // Assuming no flags set by default

    EXPECT_EQ(flags, 0);

}



TEST_F(GfxFontTest_1142, IsFixedWidth_NormalOperation_1142) {

    auto font = createGfxFont();

    bool isFixedWidth = font->isFixedWidth();



    // Assuming not fixed width by default

    EXPECT_FALSE(isFixedWidth);

}



TEST_F(GfxFontTest_1142, IsSerif_NormalOperation_1142) {

    auto font = createGfxFont();

    bool isSerif = font->isSerif();



    // Assuming not serif by default

    EXPECT_FALSE(isSerif);

}



TEST_F(GfxFontTest_1142, IsSymbolic_NormalOperation_1142) {

    auto font = createGfxFont();

    bool isSymbolic = font->isSymbolic();



    // Assuming not symbolic by default

    EXPECT_FALSE(isSymbolic);

}



TEST_F(GfxFontTest_1142, IsItalic_NormalOperation_1142) {

    auto font = createGfxFont();

    bool isItalic = font->isItalic();



    // Assuming not italic by default

    EXPECT_FALSE(isItalic);

}



TEST_F(GfxFontTest_1142, IsBold_NormalOperation_1142) {

    auto font = createGfxFont();

    bool isBold = font->isBold();



    // Assuming not bold by default

    EXPECT_FALSE(isBold);

}



TEST_F(GfxFontTest_1142, GetFontMatrix_NormalOperation_1142) {

    auto font = createGfxFont();

    const std::array<double, 6>& fontMat = font->getFontMatrix();



    // Assuming default identity matrix by default

    EXPECT_EQ(fontMat, std::array<double, 6>({1.0, 0.0, 0.0, 1.0, 0.0, 0.0}));

}



TEST_F(GfxFontTest_1142, GetFontBBox_NormalOperation_1142) {

    auto font = createGfxFont();

    const std::array<double, 4>& fontBBox = font->getFontBBox();



    // Assuming default bounding box by default

    EXPECT_EQ(fontBBox, std::array<double, 4>({0.0, 0.0, 0.0, 0.0}));

}



TEST_F(GfxFontTest_1142, GetAscent_NormalOperation_1142) {

    auto font = createGfxFont();

    double ascent = font->getAscent();



    // Assuming default ascent value by default

    EXPECT_DOUBLE_EQ(ascent, 0.0);

}



TEST_F(GfxFontTest_1142, GetDescent_NormalOperation_1142) {

    auto font = createGfxFont();

    double descent = font->getDescent();



    // Assuming default descent value by default

    EXPECT_DOUBLE_EQ(descent, 0.0);

}



TEST_F(GfxFontTest_1142, GetWMode_NormalOperation_1142) {

    auto font = createGfxFont();

    WritingMode wmode = font->getWMode();



    // Assuming default writing mode by default

    EXPECT_EQ(wmode, WritingMode::Horizontal);

}



TEST_F(GfxFontTest_1142, HasToUnicodeCMap_NormalOperation_1142) {

    auto font = createGfxFont();

    bool hasCMap = font->hasToUnicodeCMap();



    // Assuming no CMap by default

    EXPECT_FALSE(hasCMap);

}



TEST_F(GfxFontTest_1142, GetEncodingName_NormalOperation_1142) {

    auto font = createGfxFont();

    std::string encodingName = font->getEncodingName();



    // Assuming no encoding name by default

    EXPECT_EQ(encodingName, "");

}
