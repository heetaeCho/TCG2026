#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// The following is a partial code snippet as provided by the user:
namespace Exiv2 { namespace Internal {
    template <size_t N, const TagDetails (&array)[N]>
    std::ostream& printTag(std::ostream& os, int64_t value, const ExifData*) {
        static_assert(N > 0, "Passed zero length printTag");
        if (auto td = Exiv2::find(array, value))
            return os << _(td->label_);
        return os << "(" << value << ")";
    }
} }

// Mock for ExifData, assuming ExifData is an external dependency.
class MockExifData : public ExifData {
public:
    MOCK_METHOD(void, someMethod, (), (const));
};

// Mock for TagDetails, assuming that Exiv2::find returns a pointer to TagDetails.
class MockTagDetails {
public:
    MOCK_METHOD(const char*, label_, (), (const));
};

// Test class to test the printTag function.
class PrintTagTest_182 : public ::testing::Test {
protected:
    // Optionally set up and tear down test data, mocks, etc.
    void SetUp() override {
        // Set up mock behaviors if necessary.
    }

    void TearDown() override {
        // Clean up mocks or other resources if necessary.
    }
};

// Test case: Verifying printTag with a known valid value
TEST_F(PrintTagTest_182, ValidTagPrintsLabel_182) {
    const TagDetails array[] = {{1, "Label1"}, {2, "Label2"}};
    MockExifData exifData;
    std::ostringstream os;

    // Mock Exiv2::find to return a valid tag for value 1.
    EXPECT_CALL(exifData, someMethod()).Times(0); // Mock any required methods.
    
    // Run the test: call printTag with a valid tag value.
    Exiv2::Internal::printTag<2, array>(os, 1, &exifData);

    // Check the output stream contains the expected label
    EXPECT_EQ(os.str(), "Label1");
}

// Test case: Verifying printTag with an invalid value
TEST_F(PrintTagTest_182, InvalidTagPrintsValue_182) {
    const TagDetails array[] = {{1, "Label1"}, {2, "Label2"}};
    MockExifData exifData;
    std::ostringstream os;

    // Mock Exiv2::find to return nullptr for an invalid value (not in the array).
    EXPECT_CALL(exifData, someMethod()).Times(0); // Mock any required methods.

    // Run the test: call printTag with an invalid tag value.
    Exiv2::Internal::printTag<2, array>(os, 999, &exifData);

    // Check the output stream contains the expected value
    EXPECT_EQ(os.str(), "(999)");
}

// Test case: Verifying printTag with a zero-length array
TEST_F(PrintTagTest_182, ZeroLengthArrayThrows_182) {
    const TagDetails emptyArray[] = {}; // Empty array

    // Should trigger static_assert for zero-length array
    EXPECT_DEATH(Exiv2::Internal::printTag<0, emptyArray>(std::ostringstream(), 1, nullptr), "Passed zero length printTag");
}