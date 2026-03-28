#include <gtest/gtest.h>
#include <string>

// Minimal stub to match the provided partial code
namespace Exiv2 {

class ExvImage {
public:
    std::string mimeType() const {
        return "image/x-exv";
    }
};

}  // namespace Exiv2

// Test fixture
class ExvImageTest_1225 : public ::testing::Test {
protected:
    Exiv2::ExvImage image;
};

// Test that mimeType returns the correct MIME type string
TEST_F(ExvImageTest_1225, MimeTypeReturnsCorrectValue_1225) {
    EXPECT_EQ(image.mimeType(), "image/x-exv");
}

// Test that mimeType does not return an empty string
TEST_F(ExvImageTest_1225, MimeTypeIsNotEmpty_1225) {
    EXPECT_FALSE(image.mimeType().empty());
}

// Test that mimeType is consistent across multiple calls
TEST_F(ExvImageTest_1225, MimeTypeIsConsistent_1225) {
    std::string first = image.mimeType();
    std::string second = image.mimeType();
    EXPECT_EQ(first, second);
}

// Test that mimeType does not return a generic image MIME type
TEST_F(ExvImageTest_1225, MimeTypeIsNotGenericJpeg_1225) {
    EXPECT_NE(image.mimeType(), "image/jpeg");
}

// Test that mimeType does not return a generic image MIME type
TEST_F(ExvImageTest_1225, MimeTypeIsNotGenericPng_1225) {
    EXPECT_NE(image.mimeType(), "image/png");
}

// Test that mimeType starts with "image/"
TEST_F(ExvImageTest_1225, MimeTypeStartsWithImageSlash_1225) {
    std::string mime = image.mimeType();
    EXPECT_EQ(mime.substr(0, 6), "image/");
}

// Test that mimeType contains "x-exv" subtype
TEST_F(ExvImageTest_1225, MimeTypeContainsExvSubtype_1225) {
    std::string mime = image.mimeType();
    EXPECT_NE(mime.find("x-exv"), std::string::npos);
}

// Test that mimeType has correct length
TEST_F(ExvImageTest_1225, MimeTypeHasCorrectLength_1225) {
    std::string expected = "image/x-exv";
    EXPECT_EQ(image.mimeType().length(), expected.length());
}

// Test with a different ExvImage instance to ensure all instances behave the same
TEST_F(ExvImageTest_1225, DifferentInstancesSameMimeType_1225) {
    Exiv2::ExvImage anotherImage;
    EXPECT_EQ(image.mimeType(), anotherImage.mimeType());
}

// Test that the returned string is a valid copy (modifying it doesn't affect future calls)
TEST_F(ExvImageTest_1225, MimeTypeReturnsByValue_1225) {
    std::string mime = image.mimeType();
    mime = "modified";
    EXPECT_EQ(image.mimeType(), "image/x-exv");
}
