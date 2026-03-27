#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Annot.cc"

#include "poppler/Object.h"

#include "poppler/Dict.h"

#include "poppler/XRef.h"



using namespace testing;



class XRefMock : public XRef {

public:

    MOCK_METHOD(Object, getCatalog, (), (const));

    MOCK_METHOD(void, addIndirectObject, (const Object &), ());

};



TEST(CreateAnnotDrawFontTest_2022, NormalOperation_Helvetica_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);

    

    auto font = createAnnotDrawFont(&xref, &fontParentDict);

    

    EXPECT_NE(font.get(), nullptr);

}



TEST(CreateAnnotDrawFontTest_2022, NormalOperation_ZapfDingbats_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);



    auto font = createAnnotDrawFont(&xref, &fontParentDict, "AnnotDrawFont", "ZapfDingbats");



    EXPECT_NE(font.get(), nullptr);

}



TEST(CreateAnnotDrawFontTest_2022, NormalOperation_Symbol_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);



    auto font = createAnnotDrawFont(&xref, &fontParentDict, "AnnotDrawFont", "Symbol");



    EXPECT_NE(font.get(), nullptr);

}



TEST(CreateAnnotDrawFontTest_2022, BoundaryCondition_EmptyResourceName_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);



    auto font = createAnnotDrawFont(&xref, &fontParentDict, "");



    EXPECT_NE(font.get(), nullptr);

}



TEST(CreateAnnotDrawFontTest_2022, BoundaryCondition_EmptyFontName_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);



    auto font = createAnnotDrawFont(&xref, &fontParentDict, "AnnotDrawFont", "");



    EXPECT_NE(font.get(), nullptr);

}



TEST(CreateAnnotDrawFontTest_2022, ExternalInteraction_FontDictAdditions_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);



    createAnnotDrawFont(&xref, &fontParentDict);



    EXPECT_EQ(fontParentDict.dictLookupNF("Font").getDict()->dictGetLength(), 1);

}



TEST(CreateAnnotDrawFontTest_2022, ExternalInteraction_FontDictEntries_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);



    createAnnotDrawFont(&xref, &fontParentDict);



    auto fontDict = fontParentDict.dictLookupNF("Font").getDict()->dictGetValNF(0).getDict();

    

    EXPECT_STREQ(fontDict->dictLookupNF("BaseFont").getName(), "Helvetica");

    EXPECT_STREQ(fontDict->dictLookupNF("Subtype").getName(), "Type1");

    EXPECT_STREQ(fontDict->dictLookupNF("Encoding").getName(), "WinAnsiEncoding");

}



TEST(CreateAnnotDrawFontTest_2022, ExternalInteraction_FontDictEntries_ZapfDingbats_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);



    createAnnotDrawFont(&xref, &fontParentDict, "AnnotDrawFont", "ZapfDingbats");



    auto fontDict = fontParentDict.dictLookupNF("Font").getDict()->dictGetValNF(0).getDict();

    

    EXPECT_STREQ(fontDict->dictLookupNF("BaseFont").getName(), "ZapfDingbats");

    EXPECT_STREQ(fontDict->dictLookupNF("Subtype").getName(), "Type1");

    EXPECT_FALSE(fontDict->hasKey("Encoding"));

}



TEST(CreateAnnotDrawFontTest_2022, ExternalInteraction_FontDictEntries_Symbol_2022) {

    XRefMock xref;

    Dict fontParentDict(&xref);



    createAnnotDrawFont(&xref, &fontParentDict, "AnnotDrawFont", "Symbol");



    auto fontDict = fontParentDict.dictLookupNF("Font").getDict()->dictGetValNF(0).getDict();

    

    EXPECT_STREQ(fontDict->dictLookupNF("BaseFont").getName(), "Symbol");

    EXPECT_STREQ(fontDict->dictLookupNF("Subtype").getName(), "Type1");

    EXPECT_FALSE(fontDict->hasKey("Encoding"));

}
