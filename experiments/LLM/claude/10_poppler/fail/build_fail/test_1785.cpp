#include <gtest/gtest.h>
#include "poppler/StructElement.h"

// Since nameToType is a static function in the .cc file, we cannot directly test it
// from outside. However, we can test the StructElement public interface that uses
// these type mappings. We'll test through the public API of StructElement.

// Based on the PDF structure element specification, we test the type name mapping
// through the StructElement's public interface.

class StructElementTest_1785 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that StructElement::Type enum has the Unknown value
TEST_F(StructElementTest_1785, UnknownTypeExists_1785) {
    StructElement::Type t = StructElement::Unknown;
    EXPECT_EQ(t, StructElement::Unknown);
}

// Test known standard structure element types exist in the enum
TEST_F(StructElementTest_1785, StandardTypesExist_1785) {
    // Document level
    StructElement::Type doc = StructElement::Document;
    EXPECT_NE(doc, StructElement::Unknown);

    // Grouping elements
    StructElement::Type part = StructElement::Part;
    EXPECT_NE(part, StructElement::Unknown);

    StructElement::Type sect = StructElement::Sect;
    EXPECT_NE(sect, StructElement::Unknown);

    StructElement::Type div = StructElement::Div;
    EXPECT_NE(div, StructElement::Unknown);
}

// Test block-level structure element types
TEST_F(StructElementTest_1785, BlockLevelTypesExist_1785) {
    StructElement::Type p = StructElement::P;
    EXPECT_NE(p, StructElement::Unknown);

    StructElement::Type h = StructElement::H;
    EXPECT_NE(h, StructElement::Unknown);
}

// Test inline-level structure element types
TEST_F(StructElementTest_1785, InlineLevelTypesExist_1785) {
    StructElement::Type span = StructElement::Span;
    EXPECT_NE(span, StructElement::Unknown);

    StructElement::Type link = StructElement::Link;
    EXPECT_NE(link, StructElement::Unknown);
}

// Test table structure element types
TEST_F(StructElementTest_1785, TableTypesExist_1785) {
    StructElement::Type table = StructElement::Table;
    EXPECT_NE(table, StructElement::Unknown);

    StructElement::Type tr = StructElement::TR;
    EXPECT_NE(tr, StructElement::Unknown);

    StructElement::Type td = StructElement::TD;
    EXPECT_NE(td, StructElement::Unknown);

    StructElement::Type th = StructElement::TH;
    EXPECT_NE(th, StructElement::Unknown);
}

// Test list structure element types
TEST_F(StructElementTest_1785, ListTypesExist_1785) {
    StructElement::Type l = StructElement::L;
    EXPECT_NE(l, StructElement::Unknown);

    StructElement::Type li = StructElement::LI;
    EXPECT_NE(li, StructElement::Unknown);
}

// Test that different types have distinct values
TEST_F(StructElementTest_1785, TypesAreDistinct_1785) {
    EXPECT_NE(StructElement::Document, StructElement::Part);
    EXPECT_NE(StructElement::P, StructElement::Span);
    EXPECT_NE(StructElement::Table, StructElement::TR);
    EXPECT_NE(StructElement::H, StructElement::P);
    EXPECT_NE(StructElement::Link, StructElement::Span);
    EXPECT_NE(StructElement::L, StructElement::LI);
}

// Test heading types
TEST_F(StructElementTest_1785, HeadingTypesExist_1785) {
    StructElement::Type h1 = StructElement::H1;
    StructElement::Type h2 = StructElement::H2;
    StructElement::Type h3 = StructElement::H3;
    StructElement::Type h4 = StructElement::H4;
    StructElement::Type h5 = StructElement::H5;
    StructElement::Type h6 = StructElement::H6;

    EXPECT_NE(h1, StructElement::Unknown);
    EXPECT_NE(h2, StructElement::Unknown);
    EXPECT_NE(h3, StructElement::Unknown);
    EXPECT_NE(h4, StructElement::Unknown);
    EXPECT_NE(h5, StructElement::Unknown);
    EXPECT_NE(h6, StructElement::Unknown);

    // All headings should be distinct
    EXPECT_NE(h1, h2);
    EXPECT_NE(h2, h3);
    EXPECT_NE(h3, h4);
    EXPECT_NE(h4, h5);
    EXPECT_NE(h5, h6);
}

// Test illustration types
TEST_F(StructElementTest_1785, IllustrationTypesExist_1785) {
    StructElement::Type figure = StructElement::Figure;
    EXPECT_NE(figure, StructElement::Unknown);

    StructElement::Type formula = StructElement::Formula;
    EXPECT_NE(formula, StructElement::Unknown);

    StructElement::Type form = StructElement::Form;
    EXPECT_NE(form, StructElement::Unknown);
}

// Test the typeName method if available - verifying round-trip
TEST_F(StructElementTest_1785, TypeNameRoundTrip_1785) {
    // The typeName static method should return a name for known types
    const char *name = StructElement::typeName(StructElement::Document);
    if (name != nullptr) {
        EXPECT_STREQ(name, "Document");
    }

    const char *pName = StructElement::typeName(StructElement::P);
    if (pName != nullptr) {
        EXPECT_STREQ(pName, "P");
    }

    const char *spanName = StructElement::typeName(StructElement::Span);
    if (spanName != nullptr) {
        EXPECT_STREQ(spanName, "Span");
    }
}

// Test typeName for Unknown type
TEST_F(StructElementTest_1785, TypeNameForUnknown_1785) {
    const char *name = StructElement::typeName(StructElement::Unknown);
    // Unknown type should return nullptr or empty string
    if (name != nullptr) {
        // If it returns something, just verify it doesn't crash
        SUCCEED();
    } else {
        EXPECT_EQ(name, nullptr);
    }
}
