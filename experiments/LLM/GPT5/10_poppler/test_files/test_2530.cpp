// poppler_structure_element_get_abbreviation_test_2530.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include "poppler.h"
#include "poppler-structure-element.h"

// Access to _PopplerStructureElement::elem for controlled setup (elem == nullptr case).
#include "poppler-private.h"

namespace {

class PopplerStructureElementGetAbbreviationTest_2530 : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Ensure type system is ready (harmless if already initialized).
#if !GLIB_CHECK_VERSION(2, 36, 0)
        g_type_init();
#endif
    }
};

TEST_F(PopplerStructureElementGetAbbreviationTest_2530, NullInstance_ReturnsNullAndLogsCritical_2530)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");

    gchar *abbr = poppler_structure_element_get_abbreviation(nullptr);

    g_test_assert_expected_messages();
    EXPECT_EQ(abbr, nullptr);
}

TEST_F(PopplerStructureElementGetAbbreviationTest_2530, WrongGType_ReturnsNullAndLogsCritical_2530)
{
    GObject *not_a_structure_element = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(not_a_structure_element, nullptr);

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");

    // Intentionally pass the wrong type (cast) to trigger the g_return_val_if_fail.
    gchar *abbr =
        poppler_structure_element_get_abbreviation(reinterpret_cast<PopplerStructureElement *>(not_a_structure_element));

    g_test_assert_expected_messages();
    EXPECT_EQ(abbr, nullptr);

    g_object_unref(not_a_structure_element);
}

TEST_F(PopplerStructureElementGetAbbreviationTest_2530, ValidInstanceWithNullElem_ReturnsNullAndLogsCritical_2530)
{
    PopplerStructureElement *se =
        reinterpret_cast<PopplerStructureElement *>(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    ASSERT_NE(se, nullptr);

    // Force elem == nullptr (even if constructor might set it).
    se->elem = nullptr;

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*poppler_structure_element->elem != nullptr*");

    gchar *abbr = poppler_structure_element_get_abbreviation(se);

    g_test_assert_expected_messages();
    EXPECT_EQ(abbr, nullptr);

    g_object_unref(se);
}

} // namespace