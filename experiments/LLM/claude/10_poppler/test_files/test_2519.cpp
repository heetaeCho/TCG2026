#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-structure-element.h>
#include <glib.h>
#include <cstdio>
#include <cstring>

class PopplerStructureElementTest_2519 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress GLib critical warnings for invalid argument tests
    }

    void TearDown() override {
    }

    // Helper to create a minimal tagged PDF in memory and load it
    PopplerDocument* loadTaggedPDF(const char* path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) g_error_free(error);
        return doc;
    }
};

// Test that passing NULL returns the default value (POPPLER_STRUCTURE_ELEMENT_CONTENT)
// The g_return_val_if_fail should trigger and return the default
TEST_F(PopplerStructureElementTest_2519, NullElementReturnsContent_2519) {
    // Suppress GLib warnings for this test
    GLogLevelFlags old_flags = g_log_set_always_fatal(GLogLevelFlags(0));
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");

    PopplerStructureElementKind kind = poppler_structure_element_get_kind(nullptr);
    EXPECT_EQ(kind, POPPLER_STRUCTURE_ELEMENT_CONTENT);

    g_test_assert_expected_messages();
    g_log_set_always_fatal(old_flags);
}

// Test that the enum values are properly defined and distinct
TEST_F(PopplerStructureElementTest_2519, EnumValuesAreDefined_2519) {
    // Just verify that the enum constants exist and are distinct
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_CONTENT, POPPLER_STRUCTURE_ELEMENT_OBJECT_REFERENCE);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_DOCUMENT, POPPLER_STRUCTURE_ELEMENT_PART);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_ARTICLE, POPPLER_STRUCTURE_ELEMENT_SECTION);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_DIV, POPPLER_STRUCTURE_ELEMENT_SPAN);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_QUOTE, POPPLER_STRUCTURE_ELEMENT_NOTE);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_HEADING_1, POPPLER_STRUCTURE_ELEMENT_HEADING_2);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_TABLE, POPPLER_STRUCTURE_ELEMENT_TABLE_ROW);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_TABLE_HEADING, POPPLER_STRUCTURE_ELEMENT_TABLE_DATA);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_LIST, POPPLER_STRUCTURE_ELEMENT_LIST_ITEM);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_RUBY, POPPLER_STRUCTURE_ELEMENT_RUBY_BASE_TEXT);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_WARICHU, POPPLER_STRUCTURE_ELEMENT_WARICHU_TEXT);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_FIGURE, POPPLER_STRUCTURE_ELEMENT_FORMULA);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_FORM, POPPLER_STRUCTURE_ELEMENT_FIGURE);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_PARAGRAPH, POPPLER_STRUCTURE_ELEMENT_HEADING);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_TOC, POPPLER_STRUCTURE_ELEMENT_TOC_ITEM);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_BLOCKQUOTE, POPPLER_STRUCTURE_ELEMENT_CAPTION);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_NONSTRUCT, POPPLER_STRUCTURE_ELEMENT_PRIVATE);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_INDEX, POPPLER_STRUCTURE_ELEMENT_BIBENTRY);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_CODE, POPPLER_STRUCTURE_ELEMENT_LINK);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_ANNOT, POPPLER_STRUCTURE_ELEMENT_REFERENCE);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_TABLE_HEADER, POPPLER_STRUCTURE_ELEMENT_TABLE_FOOTER);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_TABLE_BODY, POPPLER_STRUCTURE_ELEMENT_TABLE_HEADER);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_HEADING_3, POPPLER_STRUCTURE_ELEMENT_HEADING_4);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_HEADING_5, POPPLER_STRUCTURE_ELEMENT_HEADING_6);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_LIST_LABEL, POPPLER_STRUCTURE_ELEMENT_LIST_BODY);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_RUBY_ANNOT_TEXT, POPPLER_STRUCTURE_ELEMENT_RUBY_PUNCTUATION);
    EXPECT_NE(POPPLER_STRUCTURE_ELEMENT_WARICHU_PUNCTUATION, POPPLER_STRUCTURE_ELEMENT_WARICHU_TEXT);
}

// Test with a non-GObject pointer (invalid type check)
TEST_F(PopplerStructureElementTest_2519, InvalidGObjectReturnsContent_2519) {
    GLogLevelFlags old_flags = g_log_set_always_fatal(GLogLevelFlags(0));
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");

    // Pass a completely wrong type - this should fail the IS_STRUCTURE_ELEMENT check
    PopplerStructureElementKind kind = poppler_structure_element_get_kind(
        reinterpret_cast<PopplerStructureElement*>(0x1));
    EXPECT_EQ(kind, POPPLER_STRUCTURE_ELEMENT_CONTENT);

    g_test_assert_expected_messages();
    g_log_set_always_fatal(old_flags);
}

// Test that all heading enum values are sequential/distinct
TEST_F(PopplerStructureElementTest_2519, HeadingEnumValuesDistinct_2519) {
    PopplerStructureElementKind headings[] = {
        POPPLER_STRUCTURE_ELEMENT_HEADING,
        POPPLER_STRUCTURE_ELEMENT_HEADING_1,
        POPPLER_STRUCTURE_ELEMENT_HEADING_2,
        POPPLER_STRUCTURE_ELEMENT_HEADING_3,
        POPPLER_STRUCTURE_ELEMENT_HEADING_4,
        POPPLER_STRUCTURE_ELEMENT_HEADING_5,
        POPPLER_STRUCTURE_ELEMENT_HEADING_6,
    };

    for (size_t i = 0; i < sizeof(headings)/sizeof(headings[0]); i++) {
        for (size_t j = i + 1; j < sizeof(headings)/sizeof(headings[0]); j++) {
            EXPECT_NE(headings[i], headings[j])
                << "Heading enums at index " << i << " and " << j << " should differ";
        }
    }
}

// Test that all table-related enum values are distinct
TEST_F(PopplerStructureElementTest_2519, TableEnumValuesDistinct_2519) {
    PopplerStructureElementKind table_kinds[] = {
        POPPLER_STRUCTURE_ELEMENT_TABLE,
        POPPLER_STRUCTURE_ELEMENT_TABLE_ROW,
        POPPLER_STRUCTURE_ELEMENT_TABLE_HEADING,
        POPPLER_STRUCTURE_ELEMENT_TABLE_DATA,
        POPPLER_STRUCTURE_ELEMENT_TABLE_HEADER,
        POPPLER_STRUCTURE_ELEMENT_TABLE_FOOTER,
        POPPLER_STRUCTURE_ELEMENT_TABLE_BODY,
    };

    for (size_t i = 0; i < sizeof(table_kinds)/sizeof(table_kinds[0]); i++) {
        for (size_t j = i + 1; j < sizeof(table_kinds)/sizeof(table_kinds[0]); j++) {
            EXPECT_NE(table_kinds[i], table_kinds[j])
                << "Table enums at index " << i << " and " << j << " should differ";
        }
    }
}

// Test all ruby-related enum values are distinct
TEST_F(PopplerStructureElementTest_2519, RubyEnumValuesDistinct_2519) {
    PopplerStructureElementKind ruby_kinds[] = {
        POPPLER_STRUCTURE_ELEMENT_RUBY,
        POPPLER_STRUCTURE_ELEMENT_RUBY_BASE_TEXT,
        POPPLER_STRUCTURE_ELEMENT_RUBY_ANNOT_TEXT,
        POPPLER_STRUCTURE_ELEMENT_RUBY_PUNCTUATION,
    };

    for (size_t i = 0; i < sizeof(ruby_kinds)/sizeof(ruby_kinds[0]); i++) {
        for (size_t j = i + 1; j < sizeof(ruby_kinds)/sizeof(ruby_kinds[0]); j++) {
            EXPECT_NE(ruby_kinds[i], ruby_kinds[j])
                << "Ruby enums at index " << i << " and " << j << " should differ";
        }
    }
}

// Test all warichu-related enum values are distinct
TEST_F(PopplerStructureElementTest_2519, WarichuEnumValuesDistinct_2519) {
    PopplerStructureElementKind warichu_kinds[] = {
        POPPLER_STRUCTURE_ELEMENT_WARICHU,
        POPPLER_STRUCTURE_ELEMENT_WARICHU_TEXT,
        POPPLER_STRUCTURE_ELEMENT_WARICHU_PUNCTUATION,
    };

    for (size_t i = 0; i < sizeof(warichu_kinds)/sizeof(warichu_kinds[0]); i++) {
        for (size_t j = i + 1; j < sizeof(warichu_kinds)/sizeof(warichu_kinds[0]); j++) {
            EXPECT_NE(warichu_kinds[i], warichu_kinds[j])
                << "Warichu enums at index " << i << " and " << j << " should differ";
        }
    }
}

// Test list-related enum values are distinct
TEST_F(PopplerStructureElementTest_2519, ListEnumValuesDistinct_2519) {
    PopplerStructureElementKind list_kinds[] = {
        POPPLER_STRUCTURE_ELEMENT_LIST,
        POPPLER_STRUCTURE_ELEMENT_LIST_ITEM,
        POPPLER_STRUCTURE_ELEMENT_LIST_LABEL,
        POPPLER_STRUCTURE_ELEMENT_LIST_BODY,
    };

    for (size_t i = 0; i < sizeof(list_kinds)/sizeof(list_kinds[0]); i++) {
        for (size_t j = i + 1; j < sizeof(list_kinds)/sizeof(list_kinds[0]); j++) {
            EXPECT_NE(list_kinds[i], list_kinds[j])
                << "List enums at index " << i << " and " << j << " should differ";
        }
    }
}

// Verify the complete set of known enum values covers all expected structure types
TEST_F(PopplerStructureElementTest_2519, AllEnumValuesExist_2519) {
    // This test verifies that all expected enum values compile and are usable
    PopplerStructureElementKind all_kinds[] = {
        POPPLER_STRUCTURE_ELEMENT_CONTENT,
        POPPLER_STRUCTURE_ELEMENT_OBJECT_REFERENCE,
        POPPLER_STRUCTURE_ELEMENT_DOCUMENT,
        POPPLER_STRUCTURE_ELEMENT_PART,
        POPPLER_STRUCTURE_ELEMENT_ARTICLE,
        POPPLER_STRUCTURE_ELEMENT_SECTION,
        POPPLER_STRUCTURE_ELEMENT_DIV,
        POPPLER_STRUCTURE_ELEMENT_SPAN,
        POPPLER_STRUCTURE_ELEMENT_QUOTE,
        POPPLER_STRUCTURE_ELEMENT_NOTE,
        POPPLER_STRUCTURE_ELEMENT_REFERENCE,
        POPPLER_STRUCTURE_ELEMENT_BIBENTRY,
        POPPLER_STRUCTURE_ELEMENT_CODE,
        POPPLER_STRUCTURE_ELEMENT_LINK,
        POPPLER_STRUCTURE_ELEMENT_ANNOT,
        POPPLER_STRUCTURE_ELEMENT_BLOCKQUOTE,
        POPPLER_STRUCTURE_ELEMENT_CAPTION,
        POPPLER_STRUCTURE_ELEMENT_NONSTRUCT,
        POPPLER_STRUCTURE_ELEMENT_TOC,
        POPPLER_STRUCTURE_ELEMENT_TOC_ITEM,
        POPPLER_STRUCTURE_ELEMENT_INDEX,
        POPPLER_STRUCTURE_ELEMENT_PRIVATE,
        POPPLER_STRUCTURE_ELEMENT_PARAGRAPH,
        POPPLER_STRUCTURE_ELEMENT_HEADING,
        POPPLER_STRUCTURE_ELEMENT_HEADING_1,
        POPPLER_STRUCTURE_ELEMENT_HEADING_2,
        POPPLER_STRUCTURE_ELEMENT_HEADING_3,
        POPPLER_STRUCTURE_ELEMENT_HEADING_4,
        POPPLER_STRUCTURE_ELEMENT_HEADING_5,
        POPPLER_STRUCTURE_ELEMENT_HEADING_6,
        POPPLER_STRUCTURE_ELEMENT_LIST,
        POPPLER_STRUCTURE_ELEMENT_LIST_ITEM,
        POPPLER_STRUCTURE_ELEMENT_LIST_LABEL,
        POPPLER_STRUCTURE_ELEMENT_LIST_BODY,
        POPPLER_STRUCTURE_ELEMENT_TABLE,
        POPPLER_STRUCTURE_ELEMENT_TABLE_ROW,
        POPPLER_STRUCTURE_ELEMENT_TABLE_HEADING,
        POPPLER_STRUCTURE_ELEMENT_TABLE_DATA,
        POPPLER_STRUCTURE_ELEMENT_TABLE_HEADER,
        POPPLER_STRUCTURE_ELEMENT_TABLE_FOOTER,
        POPPLER_STRUCTURE_ELEMENT_TABLE_BODY,
        POPPLER_STRUCTURE_ELEMENT_RUBY,
        POPPLER_STRUCTURE_ELEMENT_RUBY_BASE_TEXT,
        POPPLER_STRUCTURE_ELEMENT_RUBY_ANNOT_TEXT,
        POPPLER_STRUCTURE_ELEMENT_RUBY_PUNCTUATION,
        POPPLER_STRUCTURE_ELEMENT_WARICHU,
        POPPLER_STRUCTURE_ELEMENT_WARICHU_TEXT,
        POPPLER_STRUCTURE_ELEMENT_WARICHU_PUNCTUATION,
        POPPLER_STRUCTURE_ELEMENT_FIGURE,
        POPPLER_STRUCTURE_ELEMENT_FORMULA,
        POPPLER_STRUCTURE_ELEMENT_FORM,
    };

    // All 51 enum values should be present
    EXPECT_EQ(sizeof(all_kinds) / sizeof(all_kinds[0]), 51u);

    // Verify all values are unique
    std::set<int> unique_vals;
    for (auto k : all_kinds) {
        unique_vals.insert(static_cast<int>(k));
    }
    EXPECT_EQ(unique_vals.size(), 51u);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
