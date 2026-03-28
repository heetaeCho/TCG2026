#include <gtest/gtest.h>
#include <glib-object.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler-document.h"
}
#include "poppler-private.h"

class PopplerPSFileSetDuplexTest_2259 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need to create a PopplerPSFile manually for testing
        // Since PopplerPSFile is a GObject, we use the type system
        // However, we may need to create it in a way that doesn't require
        // a full document. We'll allocate and initialize manually.
    }

    void TearDown() override {
    }
};

// Helper to create a minimal PopplerPSFile struct for testing
// We allocate it as a raw struct since we need to control the 'out' field
static _PopplerPSFile *create_test_ps_file(PSOutputDev *out_dev = nullptr) {
    // Use g_object_new or manual allocation depending on GObject registration
    // Since PopplerPSFile is a GObject type, we try to use the type system
    // But for unit testing purposes, we create a minimal struct
    _PopplerPSFile *ps_file = g_new0(_PopplerPSFile, 1);
    ps_file->out = out_dev;
    ps_file->duplex = 0;
    ps_file->document = nullptr;
    ps_file->filename = nullptr;
    ps_file->first_page = 0;
    ps_file->last_page = 0;
    ps_file->paper_width = 0.0;
    ps_file->paper_height = 0.0;
    return ps_file;
}

static void free_test_ps_file(_PopplerPSFile *ps_file) {
    if (ps_file) {
        g_free(ps_file->filename);
        g_free(ps_file);
    }
}

// Test: Setting duplex to TRUE when out is nullptr should succeed
TEST_F(PopplerPSFileSetDuplexTest_2259, SetDuplexTrue_WhenOutIsNull_2259) {
    _PopplerPSFile *ps_file = create_test_ps_file(nullptr);
    
    poppler_ps_file_set_duplex(reinterpret_cast<PopplerPSFile*>(ps_file), TRUE);
    
    EXPECT_EQ(ps_file->duplex, TRUE);
    
    free_test_ps_file(ps_file);
}

// Test: Setting duplex to FALSE when out is nullptr should succeed
TEST_F(PopplerPSFileSetDuplexTest_2259, SetDuplexFalse_WhenOutIsNull_2259) {
    _PopplerPSFile *ps_file = create_test_ps_file(nullptr);
    ps_file->duplex = TRUE; // Start with TRUE
    
    poppler_ps_file_set_duplex(reinterpret_cast<PopplerPSFile*>(ps_file), FALSE);
    
    EXPECT_EQ(ps_file->duplex, FALSE);
    
    free_test_ps_file(ps_file);
}

// Test: Setting duplex when out is NOT nullptr should not change the value (guard fails)
TEST_F(PopplerPSFileSetDuplexTest_2259, SetDuplex_WhenOutIsNotNull_ShouldNotChange_2259) {
    // Use a non-null pointer as a fake PSOutputDev
    PSOutputDev *fake_out = reinterpret_cast<PSOutputDev*>(0xDEADBEEF);
    _PopplerPSFile *ps_file = create_test_ps_file(fake_out);
    ps_file->duplex = FALSE;
    
    // The g_return_if_fail should cause early return without modifying duplex
    poppler_ps_file_set_duplex(reinterpret_cast<PopplerPSFile*>(ps_file), TRUE);
    
    EXPECT_EQ(ps_file->duplex, FALSE);
    
    free_test_ps_file(ps_file);
}

// Test: Setting duplex multiple times should reflect the last value
TEST_F(PopplerPSFileSetDuplexTest_2259, SetDuplexMultipleTimes_2259) {
    _PopplerPSFile *ps_file = create_test_ps_file(nullptr);
    
    poppler_ps_file_set_duplex(reinterpret_cast<PopplerPSFile*>(ps_file), TRUE);
    EXPECT_EQ(ps_file->duplex, TRUE);
    
    poppler_ps_file_set_duplex(reinterpret_cast<PopplerPSFile*>(ps_file), FALSE);
    EXPECT_EQ(ps_file->duplex, FALSE);
    
    poppler_ps_file_set_duplex(reinterpret_cast<PopplerPSFile*>(ps_file), TRUE);
    EXPECT_EQ(ps_file->duplex, TRUE);
    
    free_test_ps_file(ps_file);
}

// Test: Setting duplex with integer value other than 0 or 1 (gboolean is int)
TEST_F(PopplerPSFileSetDuplexTest_2259, SetDuplexWithNonBooleanValue_2259) {
    _PopplerPSFile *ps_file = create_test_ps_file(nullptr);
    
    poppler_ps_file_set_duplex(reinterpret_cast<PopplerPSFile*>(ps_file), 42);
    
    // The value should be stored as-is since duplex is an int
    EXPECT_EQ(ps_file->duplex, 42);
    
    free_test_ps_file(ps_file);
}

// Test: Initial duplex value is 0 (FALSE) and setting to FALSE is idempotent
TEST_F(PopplerPSFileSetDuplexTest_2259, SetDuplexFalse_Idempotent_2259) {
    _PopplerPSFile *ps_file = create_test_ps_file(nullptr);
    EXPECT_EQ(ps_file->duplex, 0);
    
    poppler_ps_file_set_duplex(reinterpret_cast<PopplerPSFile*>(ps_file), FALSE);
    EXPECT_EQ(ps_file->duplex, FALSE);
    
    free_test_ps_file(ps_file);
}
