#include <gtest/gtest.h>

#include "poppler-annot.h"

#include "Annot.h"



class PopplerAnnotFreeTextTest_2096 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or mock dependencies here

        poppler_annot = static_cast<PopplerAnnotFreeText*>(g_malloc0(sizeof(PopplerAnnotFreeText)));

        GType type = g_type_register_static(G_TYPE_OBJECT, "PopplerAnnotFreeText",

            &(GTypeInfo){

                sizeof(PopplerAnnotFreeTextClass),

                nullptr,

                nullptr,

                nullptr,

                nullptr,

                nullptr,

                sizeof(PopplerAnnotFreeText),

                0,

                nullptr

            },

            GTypeFlags(0));

        g_type_set_qdata(type, g_quark_from_static_string("poppler-annot-type"), GINT_TO_POINTER(POPPLER_ANNOT_FREE_TEXT));

        poppler_annot->parent.instance.g_class = reinterpret_cast<GTypeInstanceClass*>(g_type_class_ref(type));



        // Mocking AnnotFreeText

        annot_free_text = new AnnotFreeText(nullptr, nullptr);

        g_object_set_data(G_OBJECT(poppler_annot), "annot", annot_free_text);

    }



    void TearDown() override {

        // Clean up any resources here

        delete annot_free_text;

        g_type_class_unref(poppler_annot->parent.instance.g_class);

        g_free(poppler_annot);

    }



    PopplerAnnotFreeText *poppler_annot;

    AnnotFreeText *annot_free_text;

};



TEST_F(PopplerAnnotFreeTextTest_2096, GetQuaddingLeftJustified_2096) {

    annot_free_text->setQuadding(VariableTextQuadding::leftJustified);

    EXPECT_EQ(poppler_annot_free_text_get_quadding(poppler_annot), POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED);

}



TEST_F(PopplerAnnotFreeTextTest_2096, GetQuaddingCentered_2096) {

    annot_free_text->setQuadding(VariableTextQuadding::centered);

    EXPECT_EQ(poppler_annot_free_text_get_quadding(poppler_annot), POPPLER_ANNOT_FREE_TEXT_QUADDING_CENTERED);

}



TEST_F(PopplerAnnotFreeTextTest_2096, GetQuaddingRightJustified_2096) {

    annot_free_text->setQuadding(VariableTextQuadding::rightJustified);

    EXPECT_EQ(poppler_annot_free_text_get_quadding(poppler_annot), POPPLER_ANNOT_FREE_TEXT_QUADDING_RIGHT_JUSTIFIED);

}



TEST_F(PopplerAnnotFreeTextTest_2096, GetQuaddingUnsupportedValue_2096) {

    annot_free_text->setQuadding(static_cast<VariableTextQuadding>(3)); // Assuming 3 is not a valid value

    EXPECT_EQ(poppler_annot_free_text_get_quadding(poppler_annot), POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED);

}



TEST_F(PopplerAnnotFreeTextTest_2096, NullPointer_2096) {

    EXPECT_EQ(poppler_annot_free_text_get_quadding(nullptr), POPPLER_ANNOT_FREE_TEXT_QUADDING_LEFT_JUSTIFIED);

}
