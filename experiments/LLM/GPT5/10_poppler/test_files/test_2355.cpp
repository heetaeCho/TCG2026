// File: poppler_signing_data_free_test_2355.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <poppler.h>

// These tests treat poppler_signing_data_free() as a black box.
// Observable behavior we can safely assert without peeking into internals:
//   - It must be NULL-safe
//   - It must not crash for typical/populated inputs
//   - It must not crash for boundary inputs (empty strings, very long strings, mixed NULL/non-NULL)
//
// NOTE: We do not attempt to read fields after calling poppler_signing_data_free(),
// because that would be use-after-free and violates black-box constraints.

namespace {

class PopplerSigningDataFreeTest_2355 : public ::testing::Test {
protected:
    static PopplerSigningData *NewZeroedSigningData() {
        // PopplerSigningData is expected to be a concrete struct type (as per provided snippet).
        // Allocate zeroed memory so all pointers start NULL.
        return static_cast<PopplerSigningData *>(g_malloc0(sizeof(PopplerSigningData)));
    }

    static void PopulateCommonFields(PopplerSigningData *sd) {
        ASSERT_NE(sd, nullptr);

        sd->destination_filename = g_strdup("out.pdf");
        sd->signature_text = g_strdup("Signed by Unit Test");
        sd->signature_text_left = g_strdup("Left text");

        sd->field_partial_name = g_strdup("SigField1");
        sd->reason = g_strdup("Unit testing");
        sd->location = g_strdup("CI");
        sd->image_path = g_strdup("/tmp/image.png");

        // Set some scalar/struct fields too (shouldn't matter, but covers typical usage).
        sd->left_font_size = 10;
        sd->border_width = 1;

        sd->signature_rect.x1 = 1;
        sd->signature_rect.y1 = 2;
        sd->signature_rect.x2 = 3;
        sd->signature_rect.y2 = 4;

        sd->border_color.red = 0;
        sd->border_color.green = 0;
        sd->border_color.blue = 0;

        sd->background_color.red = 65535;
        sd->background_color.green = 65535;
        sd->background_color.blue = 65535;
    }

    static char *MakeStringOfLength(size_t len, char fill_char) {
        // Create a NUL-terminated C string of exactly 'len' characters.
        char *buf = static_cast<char *>(g_malloc(len + 1));
        memset(buf, static_cast<unsigned char>(fill_char), len);
        buf[len] = '\0';
        return buf;
    }
};

TEST_F(PopplerSigningDataFreeTest_2355, NullPointerDoesNothing_2355) {
    // Should be NULL-safe.
    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_free(nullptr));
}

TEST_F(PopplerSigningDataFreeTest_2355, AllNullMembersDoesNotCrash_2355) {
    PopplerSigningData *sd = NewZeroedSigningData();
    ASSERT_NE(sd, nullptr);

    // All members are NULL due to g_malloc0.
    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_free(sd));
}

TEST_F(PopplerSigningDataFreeTest_2355, TypicalPopulatedFieldsDoesNotCrash_2355) {
    PopplerSigningData *sd = NewZeroedSigningData();
    ASSERT_NE(sd, nullptr);

    PopulateCommonFields(sd);

    // Include password fields as typical values.
    sd->password = g_strdup("p@ssw0rd");
    sd->document_owner_password = g_strdup("owner-secret");
    sd->document_user_password = g_strdup("user-secret");

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_free(sd));
}

TEST_F(PopplerSigningDataFreeTest_2355, EmptyPasswordsDoesNotCrash_2355) {
    PopplerSigningData *sd = NewZeroedSigningData();
    ASSERT_NE(sd, nullptr);

    PopulateCommonFields(sd);

    // Boundary: empty strings (strlen == 0)
    sd->password = g_strdup("");
    sd->document_owner_password = g_strdup("");
    sd->document_user_password = g_strdup("");

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_free(sd));
}

TEST_F(PopplerSigningDataFreeTest_2355, VeryLongPasswordsDoesNotCrash_2355) {
    PopplerSigningData *sd = NewZeroedSigningData();
    ASSERT_NE(sd, nullptr);

    PopulateCommonFields(sd);

    // Boundary: large buffers (exercise strlen/memset/explicit_bzero paths safely)
    // Use moderate size to keep tests fast but meaningful.
    sd->password = MakeStringOfLength(4096, 'A');
    sd->document_owner_password = MakeStringOfLength(4096, 'B');
    sd->document_user_password = MakeStringOfLength(4096, 'C');

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_free(sd));
}

TEST_F(PopplerSigningDataFreeTest_2355, MixedNullAndNonNullMembersDoesNotCrash_2355) {
    PopplerSigningData *sd = NewZeroedSigningData();
    ASSERT_NE(sd, nullptr);

    // Populate only some fields, leave others NULL.
    sd->destination_filename = g_strdup("out.pdf");
    sd->signature_text = g_strdup("Sig");
    // signature_text_left left NULL
    sd->field_partial_name = g_strdup("Field");
    // reason/location/image_path left NULL

    // Only one password set; others NULL.
    sd->password = g_strdup("secret");

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_free(sd));
}

} // namespace