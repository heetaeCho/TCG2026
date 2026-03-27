#include <gtest/gtest.h>

#include "poppler-page.h"



class PopplerImageMappingTest_2487 : public ::testing::Test {

protected:

    PopplerImageMapping* original_mapping = nullptr;

    PopplerImageMapping* copied_mapping = nullptr;



    void SetUp() override {

        original_mapping = static_cast<PopplerImageMapping*>(g_slice_alloc(sizeof(PopplerImageMapping)));

        original_mapping->image_id = 42; // Arbitrary value for testing

    }



    void TearDown() override {

        g_slice_free(PopplerImageMapping, original_mapping);

        if (copied_mapping) {

            g_slice_free(PopplerImageMapping, copied_mapping);

        }

    }

};



TEST_F(PopplerImageMappingTest_2487, CopyCreatesNewInstance_2487) {

    copied_mapping = poppler_image_mapping_copy(original_mapping);

    EXPECT_NE(original_mapping, copied_mapping);

}



TEST_F(PopplerImageMappingTest_2487, CopiedValuesAreEqual_2487) {

    copied_mapping = poppler_image_mapping_copy(original_mapping);

    EXPECT_EQ(original_mapping->image_id, copied_mapping->image_id);

}



TEST_F(PopplerImageMappingTest_2487, CopyHandlesNullPointer_2487) {

    copied_mapping = poppler_image_mapping_copy(nullptr);

    EXPECT_EQ(copied_mapping, nullptr);

}
