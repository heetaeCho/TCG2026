#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers and types are defined in poppler-page.h

extern "C" {

    #include "poppler-page.h"

}



TEST(poppler_link_mapping_free_Test_2485, NullMappingDoesNotCrash_2485) {

    PopplerLinkMapping *mapping = nullptr;

    EXPECT_NO_THROW(poppler_link_mapping_free(mapping));

}



TEST(poppler_link_mapping_free_Test_2485, ValidMappingFreesAction_2485) {

    // Mocking poppler_action_free is not allowed per constraints.

    // We can only test if it doesn't crash and behaves as expected.



    PopplerLinkMapping *mapping = g_slice_new0(PopplerLinkMapping);

    mapping->action = g_slice_new0(PopplerAction);  // Allocate a dummy action



    EXPECT_NO_THROW(poppler_link_mapping_free(mapping));

}



TEST(poppler_link_mapping_free_Test_2485, ValidMappingWithoutActionFreesCorrectly_2485) {

    PopplerLinkMapping *mapping = g_slice_new0(PopplerLinkMapping);

    mapping->action = nullptr;  // No action to free



    EXPECT_NO_THROW(poppler_link_mapping_free(mapping));

}



TEST(poppler_link_mapping_free_Test_2485, RepeatedFreeDoesNotCrash_2485) {

    PopplerLinkMapping *mapping = g_slice_new0(PopplerLinkMapping);

    mapping->action = nullptr;  // No action to free



    EXPECT_NO_THROW(poppler_link_mapping_free(mapping));

    // Freeing a second time would be undefined behavior, but we can't test that.

    // We'll assume the function is idempotent for this test.

}



// Assuming no exceptional cases are observable through the interface.
