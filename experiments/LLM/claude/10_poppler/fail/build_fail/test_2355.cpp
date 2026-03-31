#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// Forward declarations based on the interface
extern "C" {

typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

typedef struct {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

typedef struct {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

typedef struct _PopplerSigningData {
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    PopplerRectangle signature_rect;
    int left_font_size;
    PopplerColor border_color;
    int border_width;
    PopplerColor background_color;
    char *field_partial_name;
    char *reason;
    char *location;
    char *image_path;
    char *password;
    char *document_owner_password;
    char *document_user_password;
    PopplerCertificateInfo *certificate_info;
} PopplerSigningData;

void poppler_signing_data_free(PopplerSigningData *signing_data);
void poppler_certificate_info_free(PopplerCertificateInfo *info);

}

class PopplerSigningDataFreeTest_2355 : public ::testing::Test {
protected:
    PopplerSigningData *CreateSigningData() {
        PopplerSigningData *data = g_new0(PopplerSigningData, 1);
        return data;
    }

    PopplerSigningData *CreateFullSigningData() {
        PopplerSigningData *data = g_new0(PopplerSigningData, 1);
        data->destination_filename = g_strdup("test_dest.pdf");
        data->signature_text = g_strdup("Test Signature");
        data->signature_text_left = g_strdup("Left Text");
        data->field_partial_name = g_strdup("field1");
        data->reason = g_strdup("Testing");
        data->location = g_strdup("Test Location");
        data->image_path = g_strdup("/path/to/image.png");
        data->password = g_strdup("secret_password");
        data->document_owner_password = g_strdup("owner_pass");
        data->document_user_password = g_strdup("user_pass");
        data->certificate_info = nullptr; // Not allocating since we don't know the structure
        data->signature_rect = {0.0, 0.0, 100.0, 50.0};
        data->left_font_size = 12;
        data->border_width = 1;
        return data;
    }
};

// Test that passing NULL does not crash
TEST_F(PopplerSigningDataFreeTest_2355, FreeNull_DoesNotCrash_2355) {
    poppler_signing_data_free(nullptr);
    // If we reach here without crashing, the test passes
    SUCCEED();
}

// Test freeing a signing data with all fields set to NULL (zero-initialized)
TEST_F(PopplerSigningDataFreeTest_2355, FreeZeroInitialized_DoesNotCrash_2355) {
    PopplerSigningData *data = CreateSigningData();
    poppler_signing_data_free(data);
    // If we reach here without crashing, the test passes
    SUCCEED();
}

// Test freeing a fully populated signing data
TEST_F(PopplerSigningDataFreeTest_2355, FreeFullyPopulated_DoesNotCrash_2355) {
    PopplerSigningData *data = CreateFullSigningData();
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with only destination_filename set
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithOnlyDestFilename_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->destination_filename = g_strdup("output.pdf");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with only password set
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithOnlyPassword_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->password = g_strdup("my_password");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with only document_owner_password set
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithOnlyOwnerPassword_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->document_owner_password = g_strdup("owner123");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with only document_user_password set
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithOnlyUserPassword_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->document_user_password = g_strdup("user456");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with all string fields set but no passwords
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithStringsNoPasswords_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->destination_filename = g_strdup("dest.pdf");
    data->signature_text = g_strdup("Sig Text");
    data->signature_text_left = g_strdup("Sig Left");
    data->field_partial_name = g_strdup("partial");
    data->reason = g_strdup("reason");
    data->location = g_strdup("location");
    data->image_path = g_strdup("/image.png");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with only passwords set (no other strings)
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithOnlyAllPasswords_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->password = g_strdup("pass1");
    data->document_owner_password = g_strdup("pass2");
    data->document_user_password = g_strdup("pass3");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with empty string fields
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithEmptyStrings_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->destination_filename = g_strdup("");
    data->signature_text = g_strdup("");
    data->signature_text_left = g_strdup("");
    data->field_partial_name = g_strdup("");
    data->reason = g_strdup("");
    data->location = g_strdup("");
    data->image_path = g_strdup("");
    data->password = g_strdup("");
    data->document_owner_password = g_strdup("");
    data->document_user_password = g_strdup("");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with very long strings
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithLongStrings_2355) {
    PopplerSigningData *data = CreateSigningData();
    // Create a long string (4096 characters)
    std::string long_str(4096, 'A');
    data->destination_filename = g_strdup(long_str.c_str());
    data->password = g_strdup(long_str.c_str());
    data->document_owner_password = g_strdup(long_str.c_str());
    data->document_user_password = g_strdup(long_str.c_str());
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test freeing signing data with special characters in strings
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithSpecialCharacters_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->destination_filename = g_strdup("/path/to/file with spaces.pdf");
    data->signature_text = g_strdup("Ünîcödé Tëxt");
    data->password = g_strdup("p@$$w0rd!#%&");
    data->reason = g_strdup("Reason with\nnewlines\tand\ttabs");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test that signing data with only signature_text set frees correctly
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithOnlySignatureText_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->signature_text = g_strdup("My Signature");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test that signing data with only reason and location set frees correctly
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithReasonAndLocation_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->reason = g_strdup("Approval");
    data->location = g_strdup("New York, NY");
    poppler_signing_data_free(data);
    SUCCEED();
}

// Test that signing data with only image_path set frees correctly
TEST_F(PopplerSigningDataFreeTest_2355, FreeWithOnlyImagePath_2355) {
    PopplerSigningData *data = CreateSigningData();
    data->image_path = g_strdup("/usr/share/images/signature.png");
    poppler_signing_data_free(data);
    SUCCEED();
}
