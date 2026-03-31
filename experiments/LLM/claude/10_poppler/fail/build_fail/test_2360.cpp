#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

// Forward declarations based on the interface
typedef struct _PopplerSigningData PopplerSigningData;

// We need the public API functions
PopplerSigningData *poppler_signing_data_new(void);
void poppler_signing_data_free(PopplerSigningData *signing_data);
void poppler_signing_data_set_page(PopplerSigningData *signing_data, int page);
int poppler_signing_data_get_page(PopplerSigningData *signing_data);

// Include the actual header
#include "poppler-form-field.h"
}

class PopplerSigningDataSetPageTest_2360 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;

    void SetUp() override
    {
        signing_data = poppler_signing_data_new();
        ASSERT_NE(signing_data, nullptr);
    }

    void TearDown() override
    {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }
};

// Test setting a valid positive page number
TEST_F(PopplerSigningDataSetPageTest_2360, SetPositivePage_2360)
{
    poppler_signing_data_set_page(signing_data, 5);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 5);
}

// Test setting page to zero (boundary: minimum valid value)
TEST_F(PopplerSigningDataSetPageTest_2360, SetPageZero_2360)
{
    poppler_signing_data_set_page(signing_data, 0);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 0);
}

// Test setting a negative page number (should be ignored)
TEST_F(PopplerSigningDataSetPageTest_2360, SetNegativePageIgnored_2360)
{
    // First set a valid page
    poppler_signing_data_set_page(signing_data, 3);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 3);

    // Now try to set a negative page - should be ignored
    poppler_signing_data_set_page(signing_data, -1);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 3);
}

// Test setting a large negative page number (should be ignored)
TEST_F(PopplerSigningDataSetPageTest_2360, SetLargeNegativePageIgnored_2360)
{
    poppler_signing_data_set_page(signing_data, 10);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 10);

    poppler_signing_data_set_page(signing_data, -100);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 10);
}

// Test setting page with nullptr signing_data (should not crash, uses g_return_if_fail)
TEST_F(PopplerSigningDataSetPageTest_2360, SetPageWithNullSigningData_2360)
{
    // This should not crash due to g_return_if_fail
    poppler_signing_data_set_page(nullptr, 5);
    // If we reach here, the null check worked
    SUCCEED();
}

// Test setting page to a large positive value
TEST_F(PopplerSigningDataSetPageTest_2360, SetLargePositivePage_2360)
{
    poppler_signing_data_set_page(signing_data, 999999);
    int page = poppler_signing_data_get_page(signing_data);
    EXPECT_EQ(page, 999999);
}

// Test overwriting the page value with a new valid value
TEST_F(PopplerSigningDataSetPageTest_2360, OverwritePageValue_2360)
{
    poppler_signing_data_set_page(signing_data, 1);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 1);

    poppler_signing_data_set_page(signing_data, 42);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 42);
}

// Test that setting page to 1 works (common first page)
TEST_F(PopplerSigningDataSetPageTest_2360, SetPageOne_2360)
{
    poppler_signing_data_set_page(signing_data, 1);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 1);
}

// Test boundary: -1 should be rejected, 0 should be accepted
TEST_F(PopplerSigningDataSetPageTest_2360, BoundaryBetweenNegativeAndZero_2360)
{
    // Set initial value
    poppler_signing_data_set_page(signing_data, 7);

    // -1 should be rejected
    poppler_signing_data_set_page(signing_data, -1);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 7);

    // 0 should be accepted
    poppler_signing_data_set_page(signing_data, 0);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 0);
}

// Test setting INT_MAX as page
TEST_F(PopplerSigningDataSetPageTest_2360, SetPageIntMax_2360)
{
    poppler_signing_data_set_page(signing_data, INT_MAX);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), INT_MAX);
}

// Test setting INT_MIN as page (should be ignored since it's negative)
TEST_F(PopplerSigningDataSetPageTest_2360, SetPageIntMinIgnored_2360)
{
    poppler_signing_data_set_page(signing_data, 2);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 2);

    poppler_signing_data_set_page(signing_data, INT_MIN);
    EXPECT_EQ(poppler_signing_data_get_page(signing_data), 2);
}
