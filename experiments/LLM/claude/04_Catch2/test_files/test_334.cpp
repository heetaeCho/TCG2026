#include <gtest/gtest.h>
#include <cstdint>
#include <climits>
#include <type_traits>

// Include the header under test
#include "catch2/internal/catch_random_integer_helpers.hpp"

// A mock/fake generator that satisfies the constraints:
// - min() == 0
// - max() == static_cast<result_type>(-1)
// - operator() returns a controllable value

template <typename ResultType>
class FakeGenerator {
public:
    using result_type = ResultType;

    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return static_cast<result_type>(-1); }

    explicit FakeGenerator(result_type value) : value_(value) {}

    result_type operator()() { 
        call_count_++;
        return value_; 
    }

    void setValue(result_type v) { value_ = v; }
    int callCount() const { return call_count_; }

private:
    result_type value_;
    int call_count_ = 0;
};

// Test fixture
class FillBitsFromTest_334 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: When generator result_type equals target type, the value should pass through directly
TEST_F(FillBitsFromTest_334, SameSize_ReturnsGeneratorValue_334) {
    FakeGenerator<uint64_t> gen(0x123456789ABCDEF0ULL);
    auto result = Catch::Detail::fillBitsFrom<uint64_t>(gen);
    // generated_bits == return_bits, so shift by 0
    EXPECT_EQ(result, 0x123456789ABCDEF0ULL);
}

// Test: When generator result_type is larger than target type, high bits are extracted
TEST_F(FillBitsFromTest_334, LargerGenerator_ExtractsHighBits_334) {
    // Generator is 64-bit, target is 32-bit
    // Should right-shift by (64 - 32) = 32, extracting the top 32 bits
    FakeGenerator<uint64_t> gen(0xDEADBEEF00000000ULL);
    auto result = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result, static_cast<uint32_t>(0xDEADBEEFU));
}

// Test: When generator outputs zero, result should be zero regardless of type sizes
TEST_F(FillBitsFromTest_334, ZeroValue_ReturnsZero_334) {
    FakeGenerator<uint64_t> gen(0);
    auto result = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result, 0U);
}

// Test: When generator outputs max value, result should be max of target type
TEST_F(FillBitsFromTest_334, MaxValue_ReturnsMaxTarget_334) {
    FakeGenerator<uint64_t> gen(std::numeric_limits<uint64_t>::max());
    auto result = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result, std::numeric_limits<uint32_t>::max());
}

// Test: Same size with zero
TEST_F(FillBitsFromTest_334, SameSize_Zero_334) {
    FakeGenerator<uint32_t> gen(0);
    auto result = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result, 0U);
}

// Test: Same size with max
TEST_F(FillBitsFromTest_334, SameSize_Max_334) {
    FakeGenerator<uint32_t> gen(std::numeric_limits<uint32_t>::max());
    auto result = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result, std::numeric_limits<uint32_t>::max());
}

// Test: 64-bit generator to 16-bit target
TEST_F(FillBitsFromTest_334, U64ToU16_ExtractsTop16Bits_334) {
    // Shift by (64-16) = 48
    // 0xABCD000000000000 >> 48 = 0xABCD
    FakeGenerator<uint64_t> gen(0xABCD000000000000ULL);
    auto result = Catch::Detail::fillBitsFrom<uint16_t>(gen);
    EXPECT_EQ(result, static_cast<uint16_t>(0xABCD));
}

// Test: 64-bit generator to 8-bit target
TEST_F(FillBitsFromTest_334, U64ToU8_ExtractsTop8Bits_334) {
    // Shift by (64-8) = 56
    // 0xFF00000000000000 >> 56 = 0xFF
    FakeGenerator<uint64_t> gen(0xFF00000000000000ULL);
    auto result = Catch::Detail::fillBitsFrom<uint8_t>(gen);
    EXPECT_EQ(result, static_cast<uint8_t>(0xFF));
}

// Test: 32-bit generator to 16-bit target
TEST_F(FillBitsFromTest_334, U32ToU16_ExtractsTop16Bits_334) {
    // Shift by (32-16) = 16
    // 0xBEEF0000 >> 16 = 0xBEEF
    FakeGenerator<uint32_t> gen(0xBEEF0000U);
    auto result = Catch::Detail::fillBitsFrom<uint16_t>(gen);
    EXPECT_EQ(result, static_cast<uint16_t>(0xBEEF));
}

// Test: 32-bit generator to 8-bit target
TEST_F(FillBitsFromTest_334, U32ToU8_ExtractsTop8Bits_334) {
    // Shift by (32-8) = 24
    // 0x42000000 >> 24 = 0x42
    FakeGenerator<uint32_t> gen(0x42000000U);
    auto result = Catch::Detail::fillBitsFrom<uint8_t>(gen);
    EXPECT_EQ(result, static_cast<uint8_t>(0x42));
}

// Test: Low bits of generator value are discarded when target is smaller
TEST_F(FillBitsFromTest_334, LowBitsDiscarded_334) {
    // Only low bits set in the 64-bit value; target is 32-bit
    // 0x00000000FFFFFFFF >> 32 = 0x00000000
    FakeGenerator<uint64_t> gen(0x00000000FFFFFFFFULL);
    auto result = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result, 0U);
}

// Test: Verify generator is called exactly once
TEST_F(FillBitsFromTest_334, GeneratorCalledOnce_334) {
    FakeGenerator<uint64_t> gen(42);
    Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(gen.callCount(), 1);
}

// Test: Verify generator is called exactly once for same-size case
TEST_F(FillBitsFromTest_334, GeneratorCalledOnce_SameSize_334) {
    FakeGenerator<uint64_t> gen(42);
    Catch::Detail::fillBitsFrom<uint64_t>(gen);
    EXPECT_EQ(gen.callCount(), 1);
}

// Test: 16-bit generator to 16-bit target (same size, smaller types)
TEST_F(FillBitsFromTest_334, U16ToU16_SameSize_334) {
    FakeGenerator<uint16_t> gen(0x1234);
    auto result = Catch::Detail::fillBitsFrom<uint16_t>(gen);
    EXPECT_EQ(result, static_cast<uint16_t>(0x1234));
}

// Test: 16-bit generator to 8-bit target
TEST_F(FillBitsFromTest_334, U16ToU8_ExtractsTop8Bits_334) {
    // Shift by (16-8) = 8
    // 0xAB00 >> 8 = 0xAB
    FakeGenerator<uint16_t> gen(0xAB00);
    auto result = Catch::Detail::fillBitsFrom<uint8_t>(gen);
    EXPECT_EQ(result, static_cast<uint8_t>(0xAB));
}

// Test: Specific bit pattern to verify correct shifting
TEST_F(FillBitsFromTest_334, SpecificBitPattern_334) {
    // 64-bit to 32-bit
    // 0x8000000000000000 >> 32 = 0x80000000
    FakeGenerator<uint64_t> gen(0x8000000000000000ULL);
    auto result = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result, 0x80000000U);
}

// Test: Value of 1 in generator for 64->32 conversion
TEST_F(FillBitsFromTest_334, ValueOneShiftedToZero_334) {
    // 1ULL >> 32 = 0
    FakeGenerator<uint64_t> gen(1ULL);
    auto result = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result, 0U);
}

// Test: Multiple calls use updated generator state
TEST_F(FillBitsFromTest_334, MultipleCalls_334) {
    FakeGenerator<uint64_t> gen(0xAAAAAAAA00000000ULL);
    auto result1 = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result1, 0xAAAAAAAAU);

    gen.setValue(0xBBBBBBBB00000000ULL);
    auto result2 = Catch::Detail::fillBitsFrom<uint32_t>(gen);
    EXPECT_EQ(result2, 0xBBBBBBBBU);
    EXPECT_EQ(gen.callCount(), 2);
}
