#include <gtest/gtest.h>
#include <glib.h>

// Include the poppler glib header
extern "C" {
#include "poppler-form-field.h"
}

class PopplerSigningDataTest_2361 : public ::testing::Test {
protected:
    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }

    PopplerSigningData *signing_data = nullptr;
};

// Test that getting page from a newly created signing data returns default value
TEST_F(PopplerSigningDataTest_2361, GetPageDefaultValue_2361) {
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 0);
}

// Test that setting and getting page works correctly
TEST_F(PopplerSigningDataTest_2361, SetAndGetPage_2361) {
    poppler_signing_data_set_page(signing_data, 5);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 5);
}

// Test setting page to zero
TEST_F(PopplerSigningDataTest_2361, SetPageToZero_2361) {
    poppler_signing_data_set_page(signing_data, 3);
    poppler_signing_data_set_page(signing_data, 0);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 0);
}

// Test setting page to a large value
TEST_F(PopplerSigningDataTest_2361, SetPageToLargeValue_2361) {
    poppler_signing_data_set_page(signing_data, 99999);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 99999);
}

// Test setting page to a negative value
TEST_F(PopplerSigningDataTest_2361, SetPageToNegativeValue_2361) {
    poppler_signing_data_set_page(signing_data, -1);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, -1);
}

// Test that passing nullptr returns 0 (the g_return_val_if_fail guard)
TEST_F(PopplerSigningDataTest_2361, GetPageWithNullReturnsZero_2361) {
    int page = poppler_signing_data_get_page(nullptr);
    EXPECT_EQ(page, 0);
}

// Test setting page multiple times - last value wins
TEST_F(PopplerSigningDataTest_2361, SetPageMultipleTimes_2361) {
    poppler_signing_data_set_page(signing_data, 1);
    poppler_signing_data_set_page(signing_data, 2);
    poppler_signing_data_set_page(signing_data, 3);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 3);
}

// Test with copied signing data
TEST_F(PopplerSigningDataTest_2361, CopyPreservesPage_2361) {
    poppler_signing_data_set_page(signing_data, 42);
    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);
    int page = poppler_signing_data_get_page(copy);
    EXPECT_EQ(page, 42);
    poppler_signing_data_free(copy);
}

// Test setting page to INT_MAX
TEST_F(PopplerSigningDataTest_2361, SetPageToIntMax_2361) {
    poppler_signing_data_set_page(signing_data, INT_MAX);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, INT_MAX);
}

// Test setting page to INT_MIN
TEST_F(PopplerSigningDataTest_2361, SetPageToIntMin_2361) {
    poppler_signing_data_set_page(signing_data, INT_MIN);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, INT_MIN);
}

// Test that other fields don't affect page
TEST_F(PopplerSigningDataTest_2361, OtherFieldsDontAffectPage_2361) {
    poppler_signing_data_set_page(signing_data, 7);
    poppler_signing_data_set_destination_filename(signing_data, "test.pdf");
    poppler_signing_data_set_signature_text(signing_data, "John Doe");
    poppler_signing_data_set_reason(signing_data, "Approval");
    poppler_signing_data_set_location(signing_data, "Office");
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 7);
}

// Test page value with first page (typical use case)
TEST_F(PopplerSigningDataTest_2361, SetPageToFirstPage_2361) {
    poppler_signing_data_set_page(signing_data, 1);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 1);
}
