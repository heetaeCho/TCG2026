#include <gtest/gtest.h>
#include "poppler/StructElement.h"

// Since getTypeMapEntry is a static function internal to the .cc file,
// we test its behavior through the public interface of StructElement.
// StructElement provides public methods like getTypeName(), isBlock(),
// isInline(), isGrouping(), etc. that rely on getTypeMapEntry internally.

class StructElementTypeTest_1782 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that known type names are correctly returned via getTypeName
TEST_F(StructElementTypeTest_1782, GetTypeNameDocument_1782) {
    const char *name = StructElement::typeName(StructElement::Document);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Document");
}

TEST_F(StructElementTypeTest_1782, GetTypeNamePart_1782) {
    const char *name = StructElement::typeName(StructElement::Part);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Part");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameArt_1782) {
    const char *name = StructElement::typeName(StructElement::Art);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Art");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameSect_1782) {
    const char *name = StructElement::typeName(StructElement::Sect);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Sect");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameDiv_1782) {
    const char *name = StructElement::typeName(StructElement::Div);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Div");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameSpan_1782) {
    const char *name = StructElement::typeName(StructElement::Span);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Span");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameP_1782) {
    const char *name = StructElement::typeName(StructElement::P);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "P");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameH1_1782) {
    const char *name = StructElement::typeName(StructElement::H1);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "H1");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameH6_1782) {
    const char *name = StructElement::typeName(StructElement::H6);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "H6");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTable_1782) {
    const char *name = StructElement::typeName(StructElement::Table);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Table");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTR_1782) {
    const char *name = StructElement::typeName(StructElement::TR);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "TR");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTH_1782) {
    const char *name = StructElement::typeName(StructElement::TH);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "TH");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTD_1782) {
    const char *name = StructElement::typeName(StructElement::TD);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "TD");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameFigure_1782) {
    const char *name = StructElement::typeName(StructElement::Figure);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Figure");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameFormula_1782) {
    const char *name = StructElement::typeName(StructElement::Formula);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Formula");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameForm_1782) {
    const char *name = StructElement::typeName(StructElement::Form);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Form");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTOC_1782) {
    const char *name = StructElement::typeName(StructElement::TOC);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "TOC");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTOCI_1782) {
    const char *name = StructElement::typeName(StructElement::TOCI);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "TOCI");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameBlockQuote_1782) {
    const char *name = StructElement::typeName(StructElement::BlockQuote);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "BlockQuote");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameCaption_1782) {
    const char *name = StructElement::typeName(StructElement::Caption);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Caption");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameLink_1782) {
    const char *name = StructElement::typeName(StructElement::Link);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Link");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameAnnot_1782) {
    const char *name = StructElement::typeName(StructElement::Annot);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Annot");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameRuby_1782) {
    const char *name = StructElement::typeName(StructElement::Ruby);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Ruby");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameWarichu_1782) {
    const char *name = StructElement::typeName(StructElement::Warichu);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Warichu");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameL_1782) {
    const char *name = StructElement::typeName(StructElement::L);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "L");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameLI_1782) {
    const char *name = StructElement::typeName(StructElement::LI);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "LI");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameLbl_1782) {
    const char *name = StructElement::typeName(StructElement::Lbl);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Lbl");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameLBody_1782) {
    const char *name = StructElement::typeName(StructElement::LBody);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "LBody");
}

// Boundary: test an unknown/invalid type returns nullptr
TEST_F(StructElementTypeTest_1782, GetTypeNameUnknownTypeReturnsNull_1782) {
    const char *name = StructElement::typeName(StructElement::Unknown);
    EXPECT_EQ(name, nullptr);
}

// Test all heading types
TEST_F(StructElementTypeTest_1782, GetTypeNameH_1782) {
    const char *name = StructElement::typeName(StructElement::H);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "H");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameH2_1782) {
    const char *name = StructElement::typeName(StructElement::H2);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "H2");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameH3_1782) {
    const char *name = StructElement::typeName(StructElement::H3);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "H3");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameH4_1782) {
    const char *name = StructElement::typeName(StructElement::H4);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "H4");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameH5_1782) {
    const char *name = StructElement::typeName(StructElement::H5);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "H5");
}

// Test remaining types
TEST_F(StructElementTypeTest_1782, GetTypeNameNonStruct_1782) {
    const char *name = StructElement::typeName(StructElement::NonStruct);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "NonStruct");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameIndex_1782) {
    const char *name = StructElement::typeName(StructElement::Index);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Index");
}

TEST_F(StructElementTypeTest_1782, GetTypeNamePrivate_1782) {
    const char *name = StructElement::typeName(StructElement::Private);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Private");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameQuote_1782) {
    const char *name = StructElement::typeName(StructElement::Quote);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Quote");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameNote_1782) {
    const char *name = StructElement::typeName(StructElement::Note);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Note");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameReference_1782) {
    const char *name = StructElement::typeName(StructElement::Reference);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Reference");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameBibEntry_1782) {
    const char *name = StructElement::typeName(StructElement::BibEntry);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "BibEntry");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameCode_1782) {
    const char *name = StructElement::typeName(StructElement::Code);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Code");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameRB_1782) {
    const char *name = StructElement::typeName(StructElement::RB);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "RB");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameRT_1782) {
    const char *name = StructElement::typeName(StructElement::RT);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "RT");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameRP_1782) {
    const char *name = StructElement::typeName(StructElement::RP);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "RP");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameWT_1782) {
    const char *name = StructElement::typeName(StructElement::WT);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "WT");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameWP_1782) {
    const char *name = StructElement::typeName(StructElement::WP);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "WP");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTHead_1782) {
    const char *name = StructElement::typeName(StructElement::THead);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "THead");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTFoot_1782) {
    const char *name = StructElement::typeName(StructElement::TFoot);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "TFoot");
}

TEST_F(StructElementTypeTest_1782, GetTypeNameTBody_1782) {
    const char *name = StructElement::typeName(StructElement::TBody);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "TBody");
}
