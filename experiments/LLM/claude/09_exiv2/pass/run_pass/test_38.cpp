#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <cstdint>

#include <exiv2/metadatum.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;

// Mock class for Metadatum since it's abstract
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

class MetadatumTest_38 : public ::testing::Test {
protected:
    MockMetadatum metadatum_;
};

// Test that operator<< calls write() on the Metadatum
TEST_F(MetadatumTest_38, OperatorInsertionCallsWrite_38) {
    std::ostringstream oss;

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "TestOutput";
            return os;
        }));

    oss << metadatum_;
    EXPECT_EQ(oss.str(), "TestOutput");
}

// Test that operator<< returns the same ostream reference
TEST_F(MetadatumTest_38, OperatorInsertionReturnsOstream_38) {
    std::ostringstream oss;

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            return os;
        }));

    std::ostream& result = (oss << metadatum_);
    EXPECT_EQ(&result, &oss);
}

// Test that operator<< with empty write produces empty string
TEST_F(MetadatumTest_38, OperatorInsertionEmptyOutput_38) {
    std::ostringstream oss;

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            return os;
        }));

    oss << metadatum_;
    EXPECT_EQ(oss.str(), "");
}

// Test that operator<< with multiline content works
TEST_F(MetadatumTest_38, OperatorInsertionMultilineOutput_38) {
    std::ostringstream oss;

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "Line1\nLine2\nLine3";
            return os;
        }));

    oss << metadatum_;
    EXPECT_EQ(oss.str(), "Line1\nLine2\nLine3");
}

// Test that operator<< can be chained
TEST_F(MetadatumTest_38, OperatorInsertionChaining_38) {
    std::ostringstream oss;

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "MetadatumValue";
            return os;
        }));

    oss << "Before:" << metadatum_;
    EXPECT_EQ(oss.str(), "Before:MetadatumValue");
}

// Test that operator<< handles special characters in output
TEST_F(MetadatumTest_38, OperatorInsertionSpecialCharacters_38) {
    std::ostringstream oss;

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "Special: \t\r\n\0";
            return os;
        }));

    oss << metadatum_;
    EXPECT_FALSE(oss.str().empty());
}

// Test toUint32 delegates to toInt64
TEST_F(MetadatumTest_38, ToUint32ReturnsValueFromToInt64_38) {
    EXPECT_CALL(metadatum_, toInt64(0))
        .WillOnce(Return(static_cast<int64_t>(42)));

    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, 42u);
}

// Test toUint32 with different index values
TEST_F(MetadatumTest_38, ToUint32WithDifferentIndex_38) {
    EXPECT_CALL(metadatum_, toInt64(5))
        .WillOnce(Return(static_cast<int64_t>(12345)));

    uint32_t result = metadatum_.toUint32(5);
    EXPECT_EQ(result, 12345u);
}

// Test toUint32 with zero value
TEST_F(MetadatumTest_38, ToUint32ZeroValue_38) {
    EXPECT_CALL(metadatum_, toInt64(0))
        .WillOnce(Return(static_cast<int64_t>(0)));

    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, 0u);
}

// Test toUint32 with max uint32 value
TEST_F(MetadatumTest_38, ToUint32MaxValue_38) {
    EXPECT_CALL(metadatum_, toInt64(0))
        .WillOnce(Return(static_cast<int64_t>(UINT32_MAX)));

    uint32_t result = metadatum_.toUint32(0);
    EXPECT_EQ(result, UINT32_MAX);
}

// Test print method
TEST_F(MetadatumTest_38, PrintWithNullMetadata_38) {
    EXPECT_CALL(metadatum_, write(_, nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "printed_value";
            return os;
        }));

    std::string result = metadatum_.print(nullptr);
    EXPECT_EQ(result, "printed_value");
}

// Test print with ExifData
TEST_F(MetadatumTest_38, PrintWithExifData_38) {
    ExifData exifData;

    EXPECT_CALL(metadatum_, write(_, &exifData))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "exif_printed";
            return os;
        }));

    std::string result = metadatum_.print(&exifData);
    EXPECT_EQ(result, "exif_printed");
}

// Test print returns empty string when write produces nothing
TEST_F(MetadatumTest_38, PrintEmptyResult_38) {
    EXPECT_CALL(metadatum_, write(_, nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            return os;
        }));

    std::string result = metadatum_.print(nullptr);
    EXPECT_EQ(result, "");
}

// Test multiple operator<< calls on same metadatum
TEST_F(MetadatumTest_38, MultipleInsertions_38) {
    std::ostringstream oss1;
    std::ostringstream oss2;

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss1), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "first";
            return os;
        }));

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss2), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "second";
            return os;
        }));

    oss1 << metadatum_;
    oss2 << metadatum_;

    EXPECT_EQ(oss1.str(), "first");
    EXPECT_EQ(oss2.str(), "second");
}

// Test operator<< with unicode-like content
TEST_F(MetadatumTest_38, OperatorInsertionUnicodeContent_38) {
    std::ostringstream oss;

    EXPECT_CALL(metadatum_, write(::testing::Ref(oss), nullptr))
        .WillOnce(::testing::Invoke([](std::ostream& os, const ExifData*) -> std::ostream& {
            os << "日本語テスト";
            return os;
        }));

    oss << metadatum_;
    EXPECT_EQ(oss.str(), "日本語テスト");
}

// Test toUint32 with index at boundary
TEST_F(MetadatumTest_38, ToUint32LargeIndex_38) {
    size_t largeIndex = 1000;
    EXPECT_CALL(metadatum_, toInt64(largeIndex))
        .WillOnce(Return(static_cast<int64_t>(999)));

    uint32_t result = metadatum_.toUint32(largeIndex);
    EXPECT_EQ(result, 999u);
}
