#include <gtest/gtest.h>
#include <cairo.h>
#include <cstring>
#include <string>

// Include necessary headers
#include "poppler/Object.h"
#include "goo/GooString.h"
#include "goo/gmem.h"

// Since setMimeIdFromRef is a static function in CairoOutputDev.cc, we need to
// either include it or replicate its declaration for testing. Since it's static,
// we include the source or use a test helper. We'll define it here by including
// the relevant portion.

// Forward declare the function - since it's static in the .cc file, we need
// to make it accessible. One approach is to include the .cc file directly
// for testing purposes.
#include "poppler/CairoOutputDev.cc"

class SetMimeIdFromRefTest_1929 : public ::testing::Test {
protected:
    cairo_surface_t *surface;

    void SetUp() override {
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    }

    void TearDown() override {
        if (surface) {
            cairo_surface_destroy(surface);
        }
    }

    std::string getMimeData(cairo_surface_t *surf, const char *mime_type) {
        const unsigned char *data = nullptr;
        unsigned long length = 0;
        cairo_surface_get_mime_data(surf, mime_type, &data, &length);
        if (data && length > 0) {
            return std::string(reinterpret_cast<const char *>(data), length);
        }
        return "";
    }
};

// Test normal operation with a prefix and valid ref
TEST_F(SetMimeIdFromRefTest_1929, NormalOperationWithPrefix_1929) {
    Ref ref;
    ref.num = 42;
    ref.gen = 7;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;
    const char *prefix = "prefix_";

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, prefix, ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    ASSERT_GT(length, 0u);

    std::string result(reinterpret_cast<const char *>(data), length);
    EXPECT_EQ(result, "prefix_7-42");
}

// Test normal operation without a prefix (nullptr)
TEST_F(SetMimeIdFromRefTest_1929, NormalOperationWithoutPrefix_1929) {
    Ref ref;
    ref.num = 10;
    ref.gen = 3;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, nullptr, ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    ASSERT_GT(length, 0u);

    std::string result(reinterpret_cast<const char *>(data), length);
    EXPECT_EQ(result, "3-10");
}

// Test with zero gen and num values
TEST_F(SetMimeIdFromRefTest_1929, ZeroRefValues_1929) {
    Ref ref;
    ref.num = 0;
    ref.gen = 0;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, nullptr, ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    std::string result(reinterpret_cast<const char *>(data), length);
    EXPECT_EQ(result, "0-0");
}

// Test with large ref values
TEST_F(SetMimeIdFromRefTest_1929, LargeRefValues_1929) {
    Ref ref;
    ref.num = 999999;
    ref.gen = 888888;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;
    const char *prefix = "img_";

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, prefix, ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    std::string result(reinterpret_cast<const char *>(data), length);
    EXPECT_EQ(result, "img_888888-999999");
}

// Test with empty string prefix
TEST_F(SetMimeIdFromRefTest_1929, EmptyStringPrefix_1929) {
    Ref ref;
    ref.num = 5;
    ref.gen = 2;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;
    const char *prefix = "";

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, prefix, ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    std::string result(reinterpret_cast<const char *>(data), length);
    EXPECT_EQ(result, "2-5");
}

// Test with a different MIME type
TEST_F(SetMimeIdFromRefTest_1929, DifferentMimeType_1929) {
    Ref ref;
    ref.num = 1;
    ref.gen = 0;
    const char *mime_type = CAIRO_MIME_TYPE_JPEG;

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, "test_", ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    std::string result(reinterpret_cast<const char *>(data), length);
    EXPECT_EQ(result, "test_0-1");
}

// Test that the mime data length matches expected string length
TEST_F(SetMimeIdFromRefTest_1929, MimeDataLengthIsCorrect_1929) {
    Ref ref;
    ref.num = 123;
    ref.gen = 456;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;
    const char *prefix = "p";

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, prefix, ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    // Expected: "p456-123" -> length 8
    std::string expected = "p456-123";
    EXPECT_EQ(length, expected.size());
}

// Test with negative ref values (if applicable)
TEST_F(SetMimeIdFromRefTest_1929, NegativeRefValues_1929) {
    Ref ref;
    ref.num = -1;
    ref.gen = -2;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, nullptr, ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    ASSERT_GT(length, 0u);
    // The format should contain the negative numbers
    std::string result(reinterpret_cast<const char *>(data), length);
    EXPECT_NE(result.find("-"), std::string::npos);
}

// Test calling setMimeIdFromRef twice on same surface with same mime type
// Second call should succeed and overwrite
TEST_F(SetMimeIdFromRefTest_1929, OverwriteMimeData_1929) {
    Ref ref1;
    ref1.num = 1;
    ref1.gen = 0;
    Ref ref2;
    ref2.num = 2;
    ref2.gen = 0;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;

    cairo_status_t status1 = setMimeIdFromRef(surface, mime_type, nullptr, ref1);
    EXPECT_EQ(status1, CAIRO_STATUS_SUCCESS);

    cairo_status_t status2 = setMimeIdFromRef(surface, mime_type, nullptr, ref2);
    EXPECT_EQ(status2, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    std::string result(reinterpret_cast<const char *>(data), length);
    EXPECT_EQ(result, "0-2");
}

// Test with a long prefix
TEST_F(SetMimeIdFromRefTest_1929, LongPrefix_1929) {
    Ref ref;
    ref.num = 1;
    ref.gen = 0;
    const char *mime_type = CAIRO_MIME_TYPE_UNIQUE_ID;
    std::string longPrefix(1000, 'x');

    cairo_status_t status = setMimeIdFromRef(surface, mime_type, longPrefix.c_str(), ref);

    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    const unsigned char *data = nullptr;
    unsigned long length = 0;
    cairo_surface_get_mime_data(surface, mime_type, &data, &length);

    ASSERT_NE(data, nullptr);
    std::string result(reinterpret_cast<const char *>(data), length);
    std::string expected = longPrefix + "0-1";
    EXPECT_EQ(result, expected);
}
