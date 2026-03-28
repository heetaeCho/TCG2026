#include <gtest/gtest.h>
#include <cstring>

// We need to include the necessary headers to access StructElement types and the function.
// Since getTypeMapEntry is a static inline function in StructElement.cc, we need to
// include/recreate the minimal interface to test it. However, since we're testing a 
// static function from a .cc file, we need to include that file or replicate the 
// accessible interface.

// Include the header that defines StructElement
#include "StructElement.h"

// Since getTypeMapEntry is static in the .cc file, we need to include the .cc file
// to access it for testing purposes.
#include "StructElement.cc"

class GetTypeMapEntryTest_1783 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that looking up "Document" returns a valid entry with correct type
TEST_F(GetTypeMapEntryTest_1783, FindDocument_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Document");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Document);
    EXPECT_STREQ(entry->name, "Document");
}

// Test that looking up "Part" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindPart_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Part");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Part);
}

// Test that looking up "Art" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindArt_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Art");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Art);
}

// Test that looking up "Sect" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindSect_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Sect");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Sect);
}

// Test that looking up "Div" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindDiv_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Div");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Div);
}

// Test that looking up "BlockQuote" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindBlockQuote_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("BlockQuote");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::BlockQuote);
}

// Test that looking up "Caption" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindCaption_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Caption");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Caption);
}

// Test that looking up "NonStruct" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindNonStruct_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("NonStruct");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::NonStruct);
}

// Test that looking up "Index" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindIndex_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Index");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Index);
}

// Test that looking up "Private" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindPrivate_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Private");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Private);
}

// Test that looking up "Span" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindSpan_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Span");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Span);
}

// Test that looking up "Quote" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindQuote_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Quote");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Quote);
}

// Test that looking up "Note" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindNote_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Note");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Note);
}

// Test that looking up "Reference" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindReference_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Reference");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Reference);
}

// Test that looking up "BibEntry" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindBibEntry_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("BibEntry");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::BibEntry);
}

// Test that looking up "Code" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindCode_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Code");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Code);
}

// Test that looking up "Link" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindLink_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Link");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Link);
}

// Test that looking up "Annot" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindAnnot_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Annot");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Annot);
}

// Test that looking up "Ruby" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindRuby_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Ruby");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Ruby);
}

// Test that looking up "RB" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindRB_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("RB");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::RB);
}

// Test that looking up "RT" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindRT_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("RT");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::RT);
}

// Test that looking up "RP" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindRP_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("RP");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::RP);
}

// Test that looking up "Warichu" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindWarichu_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Warichu");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Warichu);
}

// Test that looking up "WT" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindWT_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("WT");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::WT);
}

// Test that looking up "WP" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindWP_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("WP");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::WP);
}

// Test that looking up "P" returns a valid entry
TEST_F(GetTypeMapEntryTest_1783, FindP_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("P");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::P);
}

// Test heading entries H, H1-H6
TEST_F(GetTypeMapEntryTest_1783, FindH_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("H");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::H);
}

TEST_F(GetTypeMapEntryTest_1783, FindH1_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("H1");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::H1);
}

TEST_F(GetTypeMapEntryTest_1783, FindH2_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("H2");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::H2);
}

TEST_F(GetTypeMapEntryTest_1783, FindH3_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("H3");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::H3);
}

TEST_F(GetTypeMapEntryTest_1783, FindH4_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("H4");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::H4);
}

TEST_F(GetTypeMapEntryTest_1783, FindH5_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("H5");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::H5);
}

TEST_F(GetTypeMapEntryTest_1783, FindH6_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("H6");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::H6);
}

// Test list-related entries
TEST_F(GetTypeMapEntryTest_1783, FindL_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("L");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::L);
}

TEST_F(GetTypeMapEntryTest_1783, FindLI_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("LI");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::LI);
}

TEST_F(GetTypeMapEntryTest_1783, FindLbl_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Lbl");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Lbl);
}

TEST_F(GetTypeMapEntryTest_1783, FindLBody_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("LBody");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::LBody);
}

// Test table-related entries
TEST_F(GetTypeMapEntryTest_1783, FindTable_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Table");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Table);
}

TEST_F(GetTypeMapEntryTest_1783, FindTR_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("TR");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::TR);
}

TEST_F(GetTypeMapEntryTest_1783, FindTH_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("TH");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::TH);
}

TEST_F(GetTypeMapEntryTest_1783, FindTD_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("TD");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::TD);
}

TEST_F(GetTypeMapEntryTest_1783, FindTHead_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("THead");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::THead);
}

TEST_F(GetTypeMapEntryTest_1783, FindTFoot_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("TFoot");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::TFoot);
}

TEST_F(GetTypeMapEntryTest_1783, FindTBody_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("TBody");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::TBody);
}

// Test illustration-related entries
TEST_F(GetTypeMapEntryTest_1783, FindFigure_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Figure");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Figure);
}

TEST_F(GetTypeMapEntryTest_1783, FindFormula_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Formula");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Formula);
}

TEST_F(GetTypeMapEntryTest_1783, FindForm_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Form");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Form);
}

// Test TOC-related entries
TEST_F(GetTypeMapEntryTest_1783, FindTOC_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("TOC");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::TOC);
}

TEST_F(GetTypeMapEntryTest_1783, FindTOCI_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("TOCI");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::TOCI);
}

// ========================
// Boundary / Error cases
// ========================

// Test that an unknown name returns nullptr
TEST_F(GetTypeMapEntryTest_1783, UnknownNameReturnsNull_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("UnknownType");
    EXPECT_EQ(entry, nullptr);
}

// Test empty string returns nullptr
TEST_F(GetTypeMapEntryTest_1783, EmptyStringReturnsNull_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("");
    EXPECT_EQ(entry, nullptr);
}

// Test case sensitivity - lowercase should not match
TEST_F(GetTypeMapEntryTest_1783, CaseSensitiveLowercase_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("document");
    EXPECT_EQ(entry, nullptr);
}

// Test case sensitivity - uppercase should not match for mixed case entries
TEST_F(GetTypeMapEntryTest_1783, CaseSensitiveUppercase_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("DOCUMENT");
    EXPECT_EQ(entry, nullptr);
}

// Test case sensitivity for short names
TEST_F(GetTypeMapEntryTest_1783, CaseSensitiveShortName_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("p");
    EXPECT_EQ(entry, nullptr);
}

// Test partial name match should not work
TEST_F(GetTypeMapEntryTest_1783, PartialNameNoMatch_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Doc");
    EXPECT_EQ(entry, nullptr);
}

// Test name with trailing space should not match
TEST_F(GetTypeMapEntryTest_1783, TrailingSpaceNoMatch_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Document ");
    EXPECT_EQ(entry, nullptr);
}

// Test name with leading space should not match
TEST_F(GetTypeMapEntryTest_1783, LeadingSpaceNoMatch_1783) {
    const TypeMapEntry *entry = getTypeMapEntry(" Document");
    EXPECT_EQ(entry, nullptr);
}

// Test a name that is a prefix of a valid name
TEST_F(GetTypeMapEntryTest_1783, PrefixOfValidNameNoMatch_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Block");
    EXPECT_EQ(entry, nullptr);
}

// Test a name that extends a valid name
TEST_F(GetTypeMapEntryTest_1783, ExtendedValidNameNoMatch_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Documents");
    EXPECT_EQ(entry, nullptr);
}

// Test single character that is not a valid name
TEST_F(GetTypeMapEntryTest_1783, SingleInvalidChar_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("X");
    EXPECT_EQ(entry, nullptr);
}

// Test that the last entry in the map (TOCI) is found correctly
TEST_F(GetTypeMapEntryTest_1783, LastEntryFound_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("TOCI");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::TOCI);
    EXPECT_STREQ(entry->name, "TOCI");
}

// Test that the first entry in the map (Document) is found correctly
TEST_F(GetTypeMapEntryTest_1783, FirstEntryFound_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("Document");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->type, StructElement::Document);
    EXPECT_STREQ(entry->name, "Document");
}

// Test that name field of the returned entry matches the input
TEST_F(GetTypeMapEntryTest_1783, ReturnedEntryNameMatches_1783) {
    const char *names[] = {"Document", "Part", "Span", "Table", "Figure", "P", "H1", "L"};
    for (const char *name : names) {
        const TypeMapEntry *entry = getTypeMapEntry(name);
        ASSERT_NE(entry, nullptr) << "Failed for name: " << name;
        EXPECT_STREQ(entry->name, name) << "Name mismatch for: " << name;
    }
}

// Test numeric-like string that isn't a valid type
TEST_F(GetTypeMapEntryTest_1783, NumericStringReturnsNull_1783) {
    const TypeMapEntry *entry = getTypeMapEntry("123");
    EXPECT_EQ(entry, nullptr);
}

// Test null-like edge case with just a null terminator equivalent
TEST_F(GetTypeMapEntryTest_1783, SingleNullCharStringReturnsNull_1783) {
    const char nullStr[] = "";
    const TypeMapEntry *entry = getTypeMapEntry(nullStr);
    EXPECT_EQ(entry, nullptr);
}
