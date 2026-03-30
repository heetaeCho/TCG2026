#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "./TestProjects/poppler/glib/poppler-page.h"

}



class PopplerLinkMappingTest_2483 : public ::testing::Test {

protected:

    void SetUp() override {

        mapping = poppler_link_mapping_new();

    }



    void TearDown() override {

        g_slice_free(PopplerLinkMapping, mapping);

    }



    PopplerLinkMapping* mapping;

};



TEST_F(PopplerLinkMappingTest_2483, CreateInstance_2483) {

    EXPECT_NE(mapping, nullptr);

}



TEST_F(PopplerLinkMappingTest_2483, MemoryAllocation_2483) {

    // Assuming the allocation should not fail

    EXPECT_NE(poppler_link_mapping_new(), nullptr);

}
