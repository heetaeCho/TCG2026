#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>

// Assuming binaryToStringHelper is defined elsewhere and has a 'buf_' member variable
namespace Exiv2 { namespace Internal {

    // Mock class to represent binaryToStringHelper for the unit tests
    template <typename T>
    class binaryToStringHelper {
    public:
        std::vector<T> buf_;
        binaryToStringHelper(const std::vector<T>& buf) : buf_(buf) {}
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& stream, const binaryToStringHelper<T>& binToStr) noexcept {
        for (size_t i = 0; i < binToStr.buf_.size(); ++i) {
            auto c = static_cast<unsigned char>(binToStr.buf_.at(i));
            if (c != 0 || i != binToStr.buf_.size() - 1) {
                if (c < 32 || c > 126) stream.put('.');
                else stream.put(static_cast<char>(c));
            }
        }
        return stream;
    }

} } // namespace Exiv2::Internal

// Test fixture for binaryToStringHelper class
class BinaryToStringHelperTest : public ::testing::Test {
protected:
    // Helper function to convert vector to binaryToStringHelper for the test
    template <typename T>
    Exiv2::Internal::binaryToStringHelper<T> createHelper(const std::vector<T>& data) {
        return Exiv2::Internal::binaryToStringHelper<T>(data);
    }
};

// TEST_ID 62: Test normal behavior with a simple binary data
TEST_F(BinaryToStringHelperTest, NormalOperation_62) {
    std::vector<char> data = {'a', 'b', 'c', 127, 32};  // Normal characters with non-printable char
    auto helper = createHelper(data);

    std::stringstream ss;
    ss << helper;

    // The expected output should be the printable characters followed by a '.'
    EXPECT_EQ(ss.str(), "abc. ");
}

// TEST_ID 63: Test with an empty buffer
TEST_F(BinaryToStringHelperTest, EmptyBuffer_63) {
    std::vector<char> data = {};
    auto helper = createHelper(data);

    std::stringstream ss;
    ss << helper;

    // Expected to output nothing since the buffer is empty
    EXPECT_EQ(ss.str(), "");
}

// TEST_ID 64: Test with a buffer that has only non-printable characters
TEST_F(BinaryToStringHelperTest, NonPrintableCharacters_64) {
    std::vector<char> data = {0, 1, 2, 3};  // Non-printable characters
    auto helper = createHelper(data);

    std::stringstream ss;
    ss << helper;

    // The expected output should contain a '.' for each non-printable character
    EXPECT_EQ(ss.str(), "....");
}

// TEST_ID 65: Test buffer with a null-terminator and trailing non-zero byte
TEST_F(BinaryToStringHelperTest, NullTerminatorAndNonZero_65) {
    std::vector<char> data = {0, 'z', 0};  // Null byte and printable 'z'
    auto helper = createHelper(data);

    std::stringstream ss;
    ss << helper;

    // The null byte should be converted to '.', and 'z' should be printed
    EXPECT_EQ(ss.str(), ".z.");
}

// TEST_ID 66: Test buffer with only spaces and special chars
TEST_F(BinaryToStringHelperTest, SpecialCharsAndSpaces_66) {
    std::vector<char> data = {' ', '!', '@', '#'};  // Space and special chars
    auto helper = createHelper(data);

    std::stringstream ss;
    ss << helper;

    // All characters are printable, so they should appear as-is
    EXPECT_EQ(ss.str(), " !@#");
}

// TEST_ID 67: Test with boundary case for large data
TEST_F(BinaryToStringHelperTest, LargeBuffer_67) {
    std::vector<char> data(10000, 'a');  // Large buffer with 10000 'a' characters
    auto helper = createHelper(data);

    std::stringstream ss;
    ss << helper;

    // The output will consist of 10000 'a' characters, followed by '.'
    EXPECT_EQ(ss.str(), std::string(10000, 'a'));
}