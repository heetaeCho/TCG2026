#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/metadatum.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <memory>
#include <cstdint>

namespace {

// Concrete mock implementation of the abstract Metadatum class for testing
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

class CmpMetadataByTagTest_112 : public ::testing::Test {
protected:
    MockMetadatum lhs;
    MockMetadatum rhs;
};

// Test: lhs.tag() < rhs.tag() should return true
TEST_F(CmpMetadataByTagTest_112, LhsTagLessThanRhsTag_ReturnsTrue_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(2));

    EXPECT_TRUE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: lhs.tag() > rhs.tag() should return false
TEST_F(CmpMetadataByTagTest_112, LhsTagGreaterThanRhsTag_ReturnsFalse_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(5));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(3));

    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: lhs.tag() == rhs.tag() should return false (strict less-than)
TEST_F(CmpMetadataByTagTest_112, EqualTags_ReturnsFalse_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(10));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(10));

    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: Both tags are zero
TEST_F(CmpMetadataByTagTest_112, BothZeroTags_ReturnsFalse_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(0));

    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: lhs tag is zero, rhs is non-zero
TEST_F(CmpMetadataByTagTest_112, LhsZeroRhsNonZero_ReturnsTrue_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(1));

    EXPECT_TRUE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: lhs tag is non-zero, rhs is zero
TEST_F(CmpMetadataByTagTest_112, LhsNonZeroRhsZero_ReturnsFalse_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(0));

    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: Boundary with max uint16_t
TEST_F(CmpMetadataByTagTest_112, LhsMaxTagRhsMaxTag_ReturnsFalse_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(0xFFFF));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(0xFFFF));

    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: lhs is max-1, rhs is max
TEST_F(CmpMetadataByTagTest_112, LhsMaxMinusOneRhsMax_ReturnsTrue_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(0xFFFE));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(0xFFFF));

    EXPECT_TRUE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: lhs is max, rhs is max-1
TEST_F(CmpMetadataByTagTest_112, LhsMaxRhsMaxMinusOne_ReturnsFalse_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(0xFFFF));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(0xFFFE));

    EXPECT_FALSE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: Consecutive tags
TEST_F(CmpMetadataByTagTest_112, ConsecutiveTags_112) {
    EXPECT_CALL(lhs, tag()).WillRepeatedly(::testing::Return(100));
    EXPECT_CALL(rhs, tag()).WillRepeatedly(::testing::Return(101));

    EXPECT_TRUE(Exiv2::cmpMetadataByTag(lhs, rhs));
}

// Test: Symmetry - if lhs < rhs is true, then rhs < lhs should be false
TEST_F(CmpMetadataByTagTest_112, Antisymmetry_112) {
    MockMetadatum a, b;
    EXPECT_CALL(a, tag()).WillRepeatedly(::testing::Return(3));
    EXPECT_CALL(b, tag()).WillRepeatedly(::testing::Return(7));

    EXPECT_TRUE(Exiv2::cmpMetadataByTag(a, b));
    EXPECT_FALSE(Exiv2::cmpMetadataByTag(b, a));
}

// Test: Irreflexivity - cmp(a, a) should be false
TEST_F(CmpMetadataByTagTest_112, Irreflexivity_112) {
    MockMetadatum a;
    EXPECT_CALL(a, tag()).WillRepeatedly(::testing::Return(42));

    EXPECT_FALSE(Exiv2::cmpMetadataByTag(a, a));
}

// Test for toUint32 - since it's a non-virtual method that likely delegates to toInt64
class MetadatumToUint32Test_112 : public ::testing::Test {
protected:
    MockMetadatum datum;
};

TEST_F(MetadatumToUint32Test_112, ToUint32ReturnsExpectedValue_112) {
    EXPECT_CALL(datum, toInt64(0)).WillOnce(::testing::Return(42));
    uint32_t result = datum.toUint32(0);
    EXPECT_EQ(result, 42u);
}

TEST_F(MetadatumToUint32Test_112, ToUint32WithNonZeroIndex_112) {
    EXPECT_CALL(datum, toInt64(3)).WillOnce(::testing::Return(100));
    uint32_t result = datum.toUint32(3);
    EXPECT_EQ(result, 100u);
}

TEST_F(MetadatumToUint32Test_112, ToUint32WithZeroValue_112) {
    EXPECT_CALL(datum, toInt64(0)).WillOnce(::testing::Return(0));
    uint32_t result = datum.toUint32(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(MetadatumToUint32Test_112, ToUint32WithMaxUint32Value_112) {
    EXPECT_CALL(datum, toInt64(0)).WillOnce(::testing::Return(static_cast<int64_t>(0xFFFFFFFF)));
    uint32_t result = datum.toUint32(0);
    EXPECT_EQ(result, 0xFFFFFFFFu);
}

} // namespace
