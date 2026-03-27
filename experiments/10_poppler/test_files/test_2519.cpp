#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-structure-element.h"

#include "TestProjects/poppler/poppler/StructElement.h"



using ::testing::MockFunction;



class MockStructElement : public StructElement {

public:

    MOCK_CONST_METHOD0(getType, StructElement::Type());

};



class PopplerStructureElementTest_2519 : public ::testing::Test {

protected:

    void SetUp() override {

        mockStructElement = new testing::NiceMock<MockStructElement>();

        poppler_structure_element = static_cast<PopplerStructureElement*>(g_slice_new0(PopplerStructureElement));

        poppler_structure_element->elem = mockStructElement;

    }



    void TearDown() override {

        g_slice_free(PopplerStructureElement, poppler_structure_element);

        delete mockStructElement;

    }



    PopplerStructureElement* poppler_structure_element;

    MockStructElement* mockStructElement;

};



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsContentForMCID_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::MCID));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_CONTENT);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsObjectReferenceForOBJR_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::OBJR));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_OBJECT_REFERENCE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsDocumentForDocument_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Document));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_DOCUMENT);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsPartForPart_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Part));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_PART);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsArticleForArt_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Art));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_ARTICLE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsSectionForSect_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Sect));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_SECTION);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsDivForDiv_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Div));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_DIV);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsSpanForSpan_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Span));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_SPAN);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsQuoteForQuote_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Quote));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_QUOTE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsNoteForNote_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Note));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_NOTE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsReferenceForReference_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Reference));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_REFERENCE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsBibEntryForBibEntry_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::BibEntry));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_BIBENTRY);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsCodeForCode_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Code));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_CODE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsLinkForLink_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Link));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_LINK);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsAnnotForAnnot_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Annot));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_ANNOT);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsBlockQuoteForBlockQuote_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::BlockQuote));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_BLOCKQUOTE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsCaptionForCaption_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Caption));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_CAPTION);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsNonStructForNonStruct_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::NonStruct));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_NONSTRUCT);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTOCForTOC_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::TOC));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TOC);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTOCIForTOCI_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::TOCI));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TOC_ITEM);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsIndexForIndex_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Index));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_INDEX);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsPrivateForPrivate_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Private));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_PRIVATE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsParagraphForP_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::P));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_PARAGRAPH);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsHeadingForH_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::H));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_HEADING);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsHeading1ForH1_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::H1));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_HEADING_1);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsHeading2ForH2_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::H2));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_HEADING_2);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsHeading3ForH3_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::H3));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_HEADING_3);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsHeading4ForH4_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::H4));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_HEADING_4);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsHeading5ForH5_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::H5));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_HEADING_5);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsHeading6ForH6_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::H6));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_HEADING_6);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsListForL_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::L));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_LIST);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsListItemForLI_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::LI));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_LIST_ITEM);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsListLabelForLbl_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Lbl));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_LIST_LABEL);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsListBodyForLBody_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::LBody));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_LIST_BODY);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTableForTable_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Table));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TABLE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTableRowForTR_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::TR));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TABLE_ROW);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTableHeadingForTH_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::TH));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TABLE_HEADING);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTableDataForTD_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::TD));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TABLE_DATA);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTableHeaderForTHead_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::THead));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TABLE_HEADER);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTableFooterForTFoot_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::TFoot));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TABLE_FOOTER);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsTableBodyForTBody_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::TBody));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_TABLE_BODY);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsRubyForRuby_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Ruby));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_RUBY);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsRubyBaseTextForRB_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::RB));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_RUBY_BASE_TEXT);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsRubyAnnotTextForRT_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::RT));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_RUBY_ANNOT_TEXT);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsRubyPunctuationForRP_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::RP));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_RUBY_PUNCTUATION);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsWarichuForWarichu_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Warichu));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_WARICHU);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsWarichuTextForWT_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::WT));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_WARICHU_TEXT);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsWarichuPunctuationForWP_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::WP));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_WARICHU_PUNCTUATION);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsFigureForFigure_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Figure));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_FIGURE);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsFormulaForFormula_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Formula));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_FORMULA);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsFormForForm_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Form));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_FORM);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsContentForInvalidType_2519) {

    EXPECT_CALL(*mockStructElement, getType()).WillOnce(testing::Return(StructElement::Unknown));

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_CONTENT);

}



TEST_F(PopplerStructureElementTest_2519, GetKindReturnsContentForNullPointer_2519) {

    poppler_structure_element->elem = nullptr;

    EXPECT_EQ(poppler_structure_element_get_kind(poppler_structure_element), POPPLER_STRUCTURE_ELEMENT_CONTENT);

}
