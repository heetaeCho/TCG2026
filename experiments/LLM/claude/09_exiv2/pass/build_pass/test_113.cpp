#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/metadatum.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <memory>
#include <string>

namespace Exiv2 {

// Forward declaration of the free function we're testing
bool cmpMetadataByKey(const Metadatum& lhs, const Metadatum& rhs);

// Concrete mock class derived from Metadatum for testing purposes
class MockMetadatum : public Metadatum {
public:
    MockMetadatum() = default;
    ~MockMetadatum() override = default;

    MOCK_METHOD(void, setValue, (const Value* pValue), (override));
    MOCK_METHOD(int, setValue, (const std::string& buf), (override));
    MOCK_METHOD(size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));
    MOCK_METHOD(std::ostream&, write, (std::ostream& os, const ExifData* pMetadata), (const, override));
    MOCK_METHOD(std::string, key, (), (const, override));
    MOCK_METHOD(const char*, familyName, (), (const, override));
    MOCK_METHOD(std::string, groupName, (), (const, override));
    MOCK_METHOD(std::string, tagName, (), (const, override));
    MOCK_METHOD(std::string, tagLabel, (), (const, override));
    MOCK_METHOD(std::string, tagDesc, (), (const, override));
    MOCK_METHOD(uint16_t, tag, (), (const, override));
    MOCK_METHOD(TypeId, typeId, (), (const, override));
    MOCK_METHOD(const char*, typeName, (), (const, override));
    MOCK_METHOD(size_t, typeSize, (), (const, override));
    MOCK_METHOD(size_t, count, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(std::string, toString, (), (const, override));
    MOCK_METHOD(std::string, toString, (size_t n), (const, override));
    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));
    MOCK_METHOD(float, toFloat, (size_t n), (const, override));
    MOCK_METHOD(Rational, toRational, (size_t n), (const, override));
    MOCK_METHOD(std::unique_ptr<Value>, getValue, (), (const, override));
    MOCK_METHOD(const Value&, value, (), (const, override));
};

} // namespace Exiv2

using namespace Exiv2;
using ::testing::Return;

class CmpMetadataByKeyTest_113 : public ::testing::Test {
protected:
    MockMetadatum lhs;
    MockMetadatum rhs;
};

// Test that lhs < rhs returns true when lhs key is lexicographically less
TEST_F(CmpMetadataByKeyTest_113, LhsKeyLessThanRhsKey_ReturnsTrue_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Image.Alpha"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("Exif.Image.Beta"));

    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

// Test that lhs > rhs returns false when lhs key is lexicographically greater
TEST_F(CmpMetadataByKeyTest_113, LhsKeyGreaterThanRhsKey_ReturnsFalse_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Image.Beta"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("Exif.Image.Alpha"));

    EXPECT_FALSE(cmpMetadataByKey(lhs, rhs));
}

// Test that equal keys returns false (strict less-than comparison)
TEST_F(CmpMetadataByKeyTest_113, EqualKeys_ReturnsFalse_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Image.Same"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("Exif.Image.Same"));

    EXPECT_FALSE(cmpMetadataByKey(lhs, rhs));
}

// Test with empty keys - both empty should return false
TEST_F(CmpMetadataByKeyTest_113, BothEmptyKeys_ReturnsFalse_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return(""));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return(""));

    EXPECT_FALSE(cmpMetadataByKey(lhs, rhs));
}

// Test with empty lhs key and non-empty rhs key
TEST_F(CmpMetadataByKeyTest_113, EmptyLhsKey_NonEmptyRhsKey_ReturnsTrue_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return(""));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("Exif.Image.Something"));

    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

// Test with non-empty lhs key and empty rhs key
TEST_F(CmpMetadataByKeyTest_113, NonEmptyLhsKey_EmptyRhsKey_ReturnsFalse_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Image.Something"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return(""));

    EXPECT_FALSE(cmpMetadataByKey(lhs, rhs));
}

// Test with keys that differ only in case
TEST_F(CmpMetadataByKeyTest_113, CaseSensitiveComparison_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Image.ABC"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("Exif.Image.abc"));

    // 'A' (65) < 'a' (97) in ASCII, so this should be true
    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

// Test with keys where one is a prefix of the other
TEST_F(CmpMetadataByKeyTest_113, PrefixKey_LhsShorter_ReturnsTrue_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Image"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("Exif.Image.More"));

    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

// Test with keys where one is a prefix of the other (reversed)
TEST_F(CmpMetadataByKeyTest_113, PrefixKey_LhsLonger_ReturnsFalse_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Image.More"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("Exif.Image"));

    EXPECT_FALSE(cmpMetadataByKey(lhs, rhs));
}

// Test with different family names to ensure full key comparison
TEST_F(CmpMetadataByKeyTest_113, DifferentFamilyNames_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Image.Width"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("Iptc.Image.Width"));

    // 'E' < 'I' in ASCII
    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

// Test with single character keys
TEST_F(CmpMetadataByKeyTest_113, SingleCharKeys_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("a"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("b"));

    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
}

// Test reflexivity: cmpMetadataByKey(x, x) should be false
TEST_F(CmpMetadataByKeyTest_113, Reflexivity_ReturnsFalse_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("Exif.Photo.DateTimeOriginal"));

    EXPECT_FALSE(cmpMetadataByKey(lhs, lhs));
}

// Test that the function provides a strict weak ordering (asymmetry)
TEST_F(CmpMetadataByKeyTest_113, Asymmetry_113) {
    EXPECT_CALL(lhs, key()).WillRepeatedly(Return("AAA"));
    EXPECT_CALL(rhs, key()).WillRepeatedly(Return("BBB"));

    // If lhs < rhs is true, then rhs < lhs must be false
    EXPECT_TRUE(cmpMetadataByKey(lhs, rhs));
    EXPECT_FALSE(cmpMetadataByKey(rhs, lhs));
}

// Test toUint32 method of Metadatum
class MetadatumToUint32Test_113 : public ::testing::Test {
protected:
    MockMetadatum metadatum;
};

TEST_F(MetadatumToUint32Test_113, ToUint32DelegatesToToInt64_113) {
    // toUint32 should convert the result from toInt64
    EXPECT_CALL(metadatum, toInt64(0)).WillOnce(Return(42));
    
    uint32_t result = metadatum.toUint32(0);
    EXPECT_EQ(result, 42u);
}

TEST_F(MetadatumToUint32Test_113, ToUint32WithZero_113) {
    EXPECT_CALL(metadatum, toInt64(0)).WillOnce(Return(0));
    
    uint32_t result = metadatum.toUint32(0);
    EXPECT_EQ(result, 0u);
}

TEST_F(MetadatumToUint32Test_113, ToUint32WithLargeValue_113) {
    EXPECT_CALL(metadatum, toInt64(0)).WillOnce(Return(static_cast<int64_t>(4294967295)));
    
    uint32_t result = metadatum.toUint32(0);
    EXPECT_EQ(result, 4294967295u);
}

TEST_F(MetadatumToUint32Test_113, ToUint32WithDifferentIndex_113) {
    EXPECT_CALL(metadatum, toInt64(5)).WillOnce(Return(100));
    
    uint32_t result = metadatum.toUint32(5);
    EXPECT_EQ(result, 100u);
}
