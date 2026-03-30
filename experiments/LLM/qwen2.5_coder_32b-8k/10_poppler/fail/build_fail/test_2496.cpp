#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



// Mocking PopplerAnnot for testing purposes

class MockPopplerAnnot {

public:

    MOCK_METHOD(void, ref, (), (const));

};



TEST(PopplerAnnotMappingCopyTest_2496, CopyReturnsNewInstance_2496) {

    PopplerAnnotMapping original_mapping;

    original_mapping.annot = reinterpret_cast<PopplerAnnot*>(new MockPopplerAnnot());



    PopplerAnnotMapping* new_mapping = poppler_annot_mapping_copy(&original_mapping);



    EXPECT_NE(new_mapping, &original_mapping);

    EXPECT_EQ(new_mapping->annot, original_mapping.annot);



    g_slice_free(PopplerAnnotMapping, new_mapping);

    delete reinterpret_cast<MockPopplerAnnot*>(original_mapping.annot);

}



TEST(PopplerAnnotMappingCopyTest_2496, CopyIncrementsRefcount_2496) {

    PopplerAnnotMapping original_mapping;

    auto* mock_annot = new MockPopplerAnnot();

    original_mapping.annot = reinterpret_cast<PopplerAnnot*>(mock_annot);



    EXPECT_CALL(*mock_annot, ref()).Times(1);



    poppler_annot_mapping_copy(&original_mapping);



    delete mock_annot;

}



TEST(PopplerAnnotMappingCopyTest_2496, CopyHandlesNullAnnot_2496) {

    PopplerAnnotMapping original_mapping;

    original_mapping.annot = nullptr;



    PopplerAnnotMapping* new_mapping = poppler_annot_mapping_copy(&original_mapping);



    EXPECT_EQ(new_mapping->annot, nullptr);



    g_slice_free(PopplerAnnotMapping, new_mapping);

}
