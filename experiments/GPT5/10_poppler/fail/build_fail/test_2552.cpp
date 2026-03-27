// poppler-structure-element-get-writing-mode-test-2552.cc
#include <gtest/gtest.h>

#include <glib-object.h>

#include <poppler.h>

// For EnumNameValue<PopplerStructureWritingMode>::values[...] used by the implementation
#include "poppler-private.h"

namespace {

class PopplerStructureElementGetWritingModeTest_2552 : public ::testing::Test {
protected:
    static PopplerStructureWritingMode DefaultValue() {
        return EnumNameValue<PopplerStructureWritingMode>::values[0].value;
    }

    static bool IsOneOfKnownValues(PopplerStructureWritingMode v) {
        // EnumNameValue arrays in Poppler GLib code are typically terminated with { nullptr, ... }.
        const auto *vals = EnumNameValue<PopplerStructureWritingMode>::values;
        for (int i = 0; vals[i].name != nullptr; ++i) {
            if (vals[i].value == v) {
                return true;
            }
        }
        // If termination is not present for some reason, at least accept the default value.
        // (Still keeps the check conservative.)
        return v == DefaultValue();
    }
};

TEST_F(PopplerStructureElementGetWritingModeTest_2552, NullptrReturnsDefault_2552)
{
    PopplerStructureWritingMode mode = poppler_structure_element_get_writing_mode(nullptr);
    EXPECT_EQ(mode, DefaultValue());
}

TEST_F(PopplerStructureElementGetWritingModeTest_2552, WrongGObjectTypeReturnsDefault_2552)
{
    GObject *not_an_element = g_object_new(G_TYPE_OBJECT, nullptr);
    ASSERT_NE(not_an_element, nullptr);

    auto *as_element = reinterpret_cast<PopplerStructureElement *>(not_an_element);
    PopplerStructureWritingMode mode = poppler_structure_element_get_writing_mode(as_element);

    EXPECT_EQ(mode, DefaultValue());

    g_object_unref(not_an_element);
}

TEST_F(PopplerStructureElementGetWritingModeTest_2552, ConstructedElementReturnsKnownEnumValue_2552)
{
    // Normal operation (as much as the public type system allows): create a real instance.
    auto *obj = g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr);
    ASSERT_NE(obj, nullptr);

    auto *element = POPPLER_STRUCTURE_ELEMENT(obj);
    ASSERT_TRUE(POPPLER_IS_STRUCTURE_ELEMENT(element));

    PopplerStructureWritingMode mode = poppler_structure_element_get_writing_mode(element);

    EXPECT_TRUE(IsOneOfKnownValues(mode));

    g_object_unref(obj);
}

TEST_F(PopplerStructureElementGetWritingModeTest_2552, RepeatedCallsAreStableForSameObject_2552)
{
    auto *obj = g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr);
    ASSERT_NE(obj, nullptr);

    auto *element = POPPLER_STRUCTURE_ELEMENT(obj);
    ASSERT_TRUE(POPPLER_IS_STRUCTURE_ELEMENT(element));

    PopplerStructureWritingMode mode1 = poppler_structure_element_get_writing_mode(element);
    PopplerStructureWritingMode mode2 = poppler_structure_element_get_writing_mode(element);

    EXPECT_EQ(mode1, mode2);
    EXPECT_TRUE(IsOneOfKnownValues(mode1));

    g_object_unref(obj);
}

} // namespace