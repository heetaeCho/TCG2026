#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



// Mock class for PopplerAnnot to verify g_object_unref calls

class MockPopplerAnnot {

public:

    MOCK_METHOD0(g_object_unref, void());

};



extern "C" {

    // Mock implementation of g_object_unref to use with Google Mock

    void g_object_unref(gpointer object) {

        static_cast<MockPopplerAnnot*>(object)->g_object_unref();

    }

}



// Test fixture for poppler_annot_mapping_free function

class PopplerAnnotMappingFreeTest : public ::testing::Test {

protected:

    PopplerAnnotMapping* mapping;

    MockPopplerAnnot mockAnnot;



    void SetUp() override {

        mapping = static_cast<PopplerAnnotMapping*>(g_slice_new0(PopplerAnnotMapping));

        mapping->annot = reinterpret_cast<PopplerAnnot*>(&mockAnnot);

    }



    void TearDown() override {

        poppler_annot_mapping_free(mapping);

    }

};



// Test for normal operation when annot is not null

TEST_F(PopplerAnnotMappingFreeTest_NormalOperation_2497, AnnotNotNull_2497) {

    EXPECT_CALL(mockAnnot, g_object_unref());

    poppler_annot_mapping_free(mapping);

}



// Test for boundary condition when mapping is null

TEST_F(PopplerAnnotMappingFreeTest_BoundaryCondition_2497, MappingNull_2497) {

    PopplerAnnotMapping* nullMapping = nullptr;

    EXPECT_NO_THROW(poppler_annot_mapping_free(nullMapping));

}



// Test for normal operation when annot is null

TEST_F(PopplerAnnotMappingFreeTest_NormalOperation_2497, AnnotNull_2497) {

    mapping->annot = nullptr;

    EXPECT_NO_THROW(poppler_annot_mapping_free(mapping));

}
