#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



// Mocking PopplerAction for verification purposes

class MockPopplerAction {

public:

    MOCK_METHOD(PopplerAction*, poppler_action_copy, (), (const));

};



// Test fixture for PopplerLinkMapping tests

class PopplerLinkMappingTest_2484 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the original mapping for testing

        original_mapping = new PopplerLinkMapping();

        original_mapping->action = reinterpret_cast<PopplerAction*>(new MockPopplerAction());

    }



    void TearDown() override {

        // Clean up the allocated memory

        delete reinterpret_cast<MockPopplerAction*>(original_mapping->action);

        g_slice_free(PopplerLinkMapping, original_mapping);

    }



    PopplerLinkMapping* original_mapping;

};



// Test case to verify normal operation of poppler_link_mapping_copy

TEST_F(PopplerLinkMappingTest_2484, CopyCreatesNewInstance_2484) {

    PopplerLinkMapping* copied_mapping = poppler_link_mapping_copy(original_mapping);

    EXPECT_NE(copied_mapping, original_mapping); // Ensure the copy is a new instance

    g_slice_free(PopplerLinkMapping, copied_mapping);

}



// Test case to verify that the action field is properly copied

TEST_F(PopplerLinkMappingTest_2484, ActionFieldCopiedCorrectly_2484) {

    PopplerLinkMapping* copied_mapping = poppler_link_mapping_copy(original_mapping);

    EXPECT_NE(copied_mapping->action, original_mapping->action); // Ensure the action is a new instance

    g_slice_free(PopplerLinkMapping, copied_mapping);

}



// Test case to verify behavior when action is null

TEST_F(PopplerLinkMappingTest_2484, NullActionHandledProperly_2484) {

    original_mapping->action = nullptr;

    PopplerLinkMapping* copied_mapping = poppler_link_mapping_copy(original_mapping);

    EXPECT_EQ(copied_mapping->action, nullptr); // Ensure the action remains null

    g_slice_free(PopplerLinkMapping, copied_mapping);

}



// Test case to verify memory allocation and deallocation

TEST_F(PopplerLinkMappingTest_2484, MemoryManagement_2484) {

    for (int i = 0; i < 10; ++i) { // Perform multiple allocations/deallocations

        PopplerLinkMapping* copied_mapping = poppler_link_mapping_copy(original_mapping);

        g_slice_free(PopplerLinkMapping, copied_mapping);

    }

}



// Test case to verify external interactions (Mock usage)

TEST_F(PopplerLinkMappingTest_2484, ExternalInteractionVerification_2484) {

    auto* mock_action = reinterpret_cast<MockPopplerAction*>(original_mapping->action);

    EXPECT_CALL(*mock_action, poppler_action_copy())

        .WillOnce(::testing::Return(reinterpret_cast<PopplerAction*>(new MockPopplerAction())));



    PopplerLinkMapping* copied_mapping = poppler_link_mapping_copy(original_mapping);

    g_slice_free(PopplerLinkMapping, copied_mapping);

}
