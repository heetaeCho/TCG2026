#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <string>
#include <memory>

#include "exiv2/metadatum.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

namespace {

// Concrete mock implementation of the abstract Metadatum class
class MockMetadatum : public Exiv2::Metadatum {
public:
    MockMetadatum() = default;
    ~MockMetadatum() override = default;

    MOCK_METHOD(void, setValue, (const Exiv2::Value* pValue), (override));
    MOCK_METHOD(int, setValue, (const std::string& buf), (override));
    MOCK_METHOD(size_t, copy, (Exiv2::byte* buf, Exiv2::ByteOrder byteOrder), (const, override));
    MOCK_METHOD(std::ostream&, write, (std::ostream& os, const Exiv2::ExifData* pMetadata), (const, override));
    MOCK_METHOD(std::string, key, (), (const, override));
    MOCK_METHOD(const char*, familyName, (), (const, override));
    MOCK_METHOD(std::string, groupName, (), (const, override));
    MOCK_METHOD(std::string, tagName, (), (const, override));
    MOCK_METHOD(std::string, tagLabel, (), (const, override));
    MOCK_METHOD(std::string, tagDesc, (), (const, override));
    MOCK_METHOD(uint16_t, tag, (), (const, override));
    MOCK_METHOD(Exiv2::TypeId, typeId, (), (const, override));
    MOCK_METHOD(const char*, typeName, (), (const, override));
    MOCK_METHOD(size_t, typeSize, (), (const, override));
    MOCK_METHOD(size_t, count, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(std::string, toString, (), (const, override));
    MOCK_METHOD(std::string, toString, (size_t n), (const, override));
    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));
    MOCK_METHOD(float, toFloat, (size_t n), (const, override));
    MOCK_METHOD(Exiv2::Rational, toRational, (size_t n), (const, override));
    MOCK_METHOD(std::unique_ptr<Exiv2::Value>, getValue, (), (const, override));
    MOCK_METHOD(const Exiv2::Value&, value, (), (const, override));
};

class MetadatumTest_111 : public ::testing::Test {
protected:
    MockMetadatum metadatum_;
};

// Test that toUint32 returns the correct cast of toInt64 for a normal positive value
TEST_F(MetadatumTest_111, ToUint32_NormalPositiveValue_111) {
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(42));
    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, 42u);
}

// Test that toUint32 returns 0 when toInt64 returns 0
TEST_F(MetadatumTest_111, ToUint32_ZeroValue_111) {
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(0));
    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, 0u);
}

// Test that toUint32 correctly truncates a large int64_t value to uint32_t
TEST_F(MetadatumTest_111, ToUint32_LargeInt64ValueTruncated_111) {
    // Value larger than UINT32_MAX should be truncated
    int64_t largeValue = static_cast<int64_t>(UINT32_MAX) + 1;
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(largeValue));
    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, 0u);
}

// Test that toUint32 handles UINT32_MAX correctly
TEST_F(MetadatumTest_111, ToUint32_MaxUint32Value_111) {
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(static_cast<int64_t>(UINT32_MAX)));
    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, UINT32_MAX);
}

// Test that toUint32 handles negative int64_t values (wraps around via static_cast)
TEST_F(MetadatumTest_111, ToUint32_NegativeValue_111) {
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(-1));
    uint32_t result = metadatum_.toUint32(0);
    // static_cast<uint32_t>(-1) should give UINT32_MAX
    EXPECT_EQ(result, UINT32_MAX);
}

// Test that toUint32 handles a different index parameter
TEST_F(MetadatumTest_111, ToUint32_DifferentIndex_111) {
    EXPECT_CALL(metadatum_, toInt64(5)).WillOnce(::testing::Return(100));
    uint32_t result = metadatum_.toUint32(5);
    EXPECT_EQ(result, 100u);
}

// Test that toUint32 passes the correct index to toInt64
TEST_F(MetadatumTest_111, ToUint32_IndexPassedCorrectly_111) {
    EXPECT_CALL(metadatum_, toInt64(999)).WillOnce(::testing::Return(12345));
    uint32_t result = metadatum_.toUint32(999);
    EXPECT_EQ(result, 12345u);
}

// Test with a value that fits exactly in uint32 but is larger in int64
TEST_F(MetadatumTest_111, ToUint32_ValueExactlyUint32Max_111) {
    int64_t value = 4294967295LL; // UINT32_MAX
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(value));
    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, 4294967295u);
}

// Test with a very large positive int64 value
TEST_F(MetadatumTest_111, ToUint32_VeryLargeInt64_111) {
    int64_t value = INT64_MAX;
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(value));
    uint32_t result = metadatum_.toUint32(0);
    // static_cast<uint32_t>(INT64_MAX) = UINT32_MAX (lower 32 bits of INT64_MAX are all 1s)
    EXPECT_EQ(result, static_cast<uint32_t>(INT64_MAX));
}

// Test with INT64_MIN (negative boundary)
TEST_F(MetadatumTest_111, ToUint32_Int64Min_111) {
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(INT64_MIN));
    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, static_cast<uint32_t>(INT64_MIN));
}

// Test with index 0 and value 1
TEST_F(MetadatumTest_111, ToUint32_ValueOne_111) {
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(1));
    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, 1u);
}

// Test that toUint32 delegates to toInt64 exactly once
TEST_F(MetadatumTest_111, ToUint32_CallsToInt64ExactlyOnce_111) {
    EXPECT_CALL(metadatum_, toInt64(0)).Times(1).WillOnce(::testing::Return(50));
    metadatum_.toUint32(0);
}

// Test with negative value that truncates to a specific uint32 value
TEST_F(MetadatumTest_111, ToUint32_NegativeSmallValue_111) {
    EXPECT_CALL(metadatum_, toInt64(0)).WillOnce(::testing::Return(-100));
    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, static_cast<uint32_t>(-100));
}

}  // namespace
