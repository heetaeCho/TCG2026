#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// Include the header for the function under test
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size);

class RE2FuzzerTest_386 : public ::testing::Test {
protected:
    // Helper to create a data buffer with specific content
    std::vector<uint8_t> MakeData(const std::string& content) {
        return std::vector<uint8_t>(content.begin(), content.end());
    }
};

// Test that empty input returns 0 immediately
TEST_F(RE2FuzzerTest_386, EmptyInputReturnsZero_386) {
    const uint8_t* data = nullptr;
    int result = LLVMFuzzerTestOneInput(data, 0);
    EXPECT_EQ(result, 0);
}

// Test that size == 0 returns 0
TEST_F(RE2FuzzerTest_386, ZeroSizeReturnsZero_386) {
    uint8_t data[] = {0x01};
    int result = LLVMFuzzerTestOneInput(data, 0);
    EXPECT_EQ(result, 0);
}

// Test that input exceeding 4096 bytes returns 0
TEST_F(RE2FuzzerTest_386, OversizedInputReturnsZero_386) {
    std::vector<uint8_t> data(4097, 'a');
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test that input exactly at 4096 bytes is accepted (does not return early)
TEST_F(RE2FuzzerTest_386, ExactMaxSizeInputAccepted_386) {
    std::vector<uint8_t> data(4096, 0x00);
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with a single byte of input (minimum valid size)
TEST_F(RE2FuzzerTest_386, SingleByteInput_386) {
    uint8_t data[] = {0x00};
    int result = LLVMFuzzerTestOneInput(data, 1);
    EXPECT_EQ(result, 0);
}

// Test with minimal data that covers all boolean options consumption
// FuzzedDataProvider consumes 11 bools (1 bit each) + anchor selection + pattern + text
// At minimum we need enough bytes to not exhaust data provider badly
TEST_F(RE2FuzzerTest_386, MinimalValidInput_386) {
    // 11 bools consume ~2 bytes, anchor needs 1 byte, then pattern/text are empty
    std::vector<uint8_t> data = {0xFF, 0xFF, 0x00, 0x00};
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with a simple regex pattern and text
TEST_F(RE2FuzzerTest_386, SimplePatternAndText_386) {
    // Construct data: 11 bools (all false) + anchor byte + pattern + text
    // bools consume from end of buffer; let's just provide enough data
    std::string input = "hello.*world";
    std::vector<uint8_t> data(input.begin(), input.end());
    // Pad to ensure enough for bool consumption
    data.insert(data.end(), 20, 0x00);
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with all 0xFF bytes to exercise all-true boolean paths
TEST_F(RE2FuzzerTest_386, AllOnesInput_386) {
    std::vector<uint8_t> data(100, 0xFF);
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with all 0x00 bytes to exercise all-false boolean paths
TEST_F(RE2FuzzerTest_386, AllZerosInput_386) {
    std::vector<uint8_t> data(100, 0x00);
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with an invalid regex pattern (unclosed group)
TEST_F(RE2FuzzerTest_386, InvalidRegexPattern_386) {
    // Put enough control bytes for bools/anchor, then an invalid pattern
    std::string payload = "((((";
    std::vector<uint8_t> data;
    // Add some control bytes
    for (int i = 0; i < 20; i++) data.push_back(0x00);
    data.insert(data.end(), payload.begin(), payload.end());
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with binary data containing null bytes
TEST_F(RE2FuzzerTest_386, BinaryDataWithNullBytes_386) {
    std::vector<uint8_t> data = {0x00, 0x01, 0x00, 0x02, 0x00, 0x03,
                                  0x00, 0x04, 0x00, 0x05, 0x00, 0x06,
                                  0x00, 0x07, 0x00, 0x08, 0x00, 0x09,
                                  0x00, 0x0A, 0x00, 0x0B, 0x00, 0x0C};
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test boundary: size == 1
TEST_F(RE2FuzzerTest_386, SizeOne_386) {
    uint8_t data[] = {0x42};
    int result = LLVMFuzzerTestOneInput(data, 1);
    EXPECT_EQ(result, 0);
}

// Test boundary: size == 4095 (just under max)
TEST_F(RE2FuzzerTest_386, SizeJustUnderMax_386) {
    std::vector<uint8_t> data(4095, 'x');
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with alternating byte pattern
TEST_F(RE2FuzzerTest_386, AlternatingBytePattern_386) {
    std::vector<uint8_t> data(200, 0);
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = (i % 2 == 0) ? 0xAA : 0x55;
    }
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with data that resembles a complex regex
TEST_F(RE2FuzzerTest_386, ComplexRegexData_386) {
    std::string complex = "^(?:a{1,3}|b+|[c-z]*)\\d{2,4}$";
    std::vector<uint8_t> data;
    // Add control bytes for options
    for (int i = 0; i < 15; i++) data.push_back(static_cast<uint8_t>(i));
    data.insert(data.end(), complex.begin(), complex.end());
    // Add some text data
    std::string text = "abc123def";
    data.insert(data.end(), text.begin(), text.end());
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with UTF-8 multibyte characters
TEST_F(RE2FuzzerTest_386, UTF8MultibyteInput_386) {
    // Control bytes + UTF-8 pattern
    std::vector<uint8_t> data = {0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00};
    // Add UTF-8 encoded characters (e.g., é = 0xC3 0xA9)
    data.push_back(0xC3);
    data.push_back(0xA9);
    data.push_back(0x2B); // +
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test that function always returns 0 for valid inputs
TEST_F(RE2FuzzerTest_386, AlwaysReturnsZero_386) {
    // Various sizes
    for (size_t sz = 1; sz <= 100; sz++) {
        std::vector<uint8_t> data(sz, static_cast<uint8_t>(sz & 0xFF));
        int result = LLVMFuzzerTestOneInput(data.data(), data.size());
        EXPECT_EQ(result, 0) << "Failed for size=" << sz;
    }
}

// Test with data that would set Latin1 encoding (first bool true)
TEST_F(RE2FuzzerTest_386, Latin1EncodingPath_386) {
    // The first bool consumed is for encoding; make it true
    // FuzzedDataProvider consumes bools from the end of the data
    std::vector<uint8_t> data(50, 0xFF); // All true bools
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with data that would set UTF8 encoding (first bool false)
TEST_F(RE2FuzzerTest_386, UTF8EncodingPath_386) {
    std::vector<uint8_t> data(50, 0x00); // All false bools
    int result = LLVMFuzzerTestOneInput(data.data(), data.size());
    EXPECT_EQ(result, 0);
}

// Test with two bytes (very minimal but valid)
TEST_F(RE2FuzzerTest_386, TwoBytesInput_386) {
    uint8_t data[] = {0xAB, 0xCD};
    int result = LLVMFuzzerTestOneInput(data, 2);
    EXPECT_EQ(result, 0);
}
