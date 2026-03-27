#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using namespace testing;



class PopplerFontInfoTest : public Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

        font_info = poppler_font_info_new(document);

    }



    void TearDown() override {

        g_object_unref(font_info);

        g_object_unref(document);

    }



    PopplerDocument* document;

    PopplerFontInfo* font_info;

};



TEST_F(PopplerFontInfoTest_2235, NullDocumentReturnsNull_2235) {

    EXPECT_EQ(poppler_font_info_new(nullptr), nullptr);

}



TEST_F(PopplerFontInfoTest_2235, NormalOperationCreatesValidObject_2235) {

    EXPECT_NE(font_info, nullptr);

}



TEST_F(PopplerFontInfoTest_2235, DocumentRefIsIncremented_2235) {

    int initial_ref_count = G_OBJECT(document)->ref_count;

    PopplerFontInfo* new_font_info = poppler_font_info_new(document);

    EXPECT_EQ(G_OBJECT(document)->ref_count, initial_ref_count + 1);

    g_object_unref(new_font_info);

}



TEST_F(PopplerFontInfoTest_2235, ScannerIsInitialized_2235) {

    EXPECT_NE(font_info->scanner, nullptr);

}
