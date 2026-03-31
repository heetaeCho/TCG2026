#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNotePrintFocusMode3Test_1611 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: When value count is not 1, output should be "(<value>)"
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, WrongCount_OutputsParenthesizedValue_1611) {
    // Create a value with count != 1 (two unsigned short values)
    UShortValue val;
    val.read("1 2");
    ASSERT_EQ(val.count(), 2u);

    ExifData exifData;
    SonyMakerNote::printFocusMode3(os, val, &exifData);

    std::string result = os.str();
    // Should start with "(" and end with ")"
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When value typeId is not unsignedShort, output should be "(<value>)"
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, WrongTypeId_OutputsParenthesizedValue_1611) {
    // Create a signed short value (not unsignedShort)
    Value::UniquePtr val = Value::create(signedShort);
    val->read("1");
    ASSERT_EQ(val->count(), 1u);
    ASSERT_NE(val->typeId(), unsignedShort);

    ExifData exifData;
    SonyMakerNote::printFocusMode3(os, *val, &exifData);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When metadata is null, output should be "(<value>)"
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, NullMetadata_OutputsParenthesizedValue_1611) {
    UShortValue val;
    val.read("1");
    ASSERT_EQ(val.count(), 1u);

    SonyMakerNote::printFocusMode3(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When metadata is valid but doesn't contain the required meta version, should output "n/a"
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, NoMetaVersion_OutputsNA_1611) {
    UShortValue val;
    val.read("0");
    ASSERT_EQ(val.count(), 1u);
    ASSERT_EQ(val.typeId(), unsignedShort);

    ExifData exifData;
    // Don't add any metadata version info
    SonyMakerNote::printFocusMode3(os, val, &exifData);

    std::string result = os.str();
    // Should output "n/a" (possibly localized)
    EXPECT_FALSE(result.empty());
    // It should NOT be a parenthesized value
    EXPECT_NE(result.front(), '(');
}

// Test: Verify that the function returns a reference to the same ostream
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, ReturnsSameOstream_1611) {
    UShortValue val;
    val.read("0");

    ExifData exifData;
    std::ostream& returned = SonyMakerNote::printFocusMode3(os, val, &exifData);

    EXPECT_EQ(&returned, &os);
}

// Test: Return same ostream when metadata is null
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, ReturnsSameOstreamNullMetadata_1611) {
    UShortValue val;
    val.read("0");

    std::ostream& returned = SonyMakerNote::printFocusMode3(os, val, nullptr);

    EXPECT_EQ(&returned, &os);
}

// Test: When count is 0, output should be parenthesized
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, ZeroCount_OutputsParenthesizedValue_1611) {
    // An empty UShortValue has count 0
    UShortValue val;
    ASSERT_EQ(val.count(), 0u);

    ExifData exifData;
    SonyMakerNote::printFocusMode3(os, val, &exifData);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Wrong type (unsignedLong instead of unsignedShort) should produce parenthesized output
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, UnsignedLongType_OutputsParenthesizedValue_1611) {
    Value::UniquePtr val = Value::create(unsignedLong);
    val->read("2");
    ASSERT_EQ(val->count(), 1u);
    ASSERT_EQ(val->typeId(), unsignedLong);

    ExifData exifData;
    SonyMakerNote::printFocusMode3(os, *val, &exifData);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Valid unsignedShort with count 1 and empty metadata outputs n/a
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, ValidValueEmptyMetadata_OutputsNA_1611) {
    UShortValue val;
    val.read("3");
    ASSERT_EQ(val.count(), 1u);
    ASSERT_EQ(val.typeId(), unsignedShort);

    ExifData exifData;
    SonyMakerNote::printFocusMode3(os, val, &exifData);

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.front(), '(');
}

// Test: Multiple values of wrong count but correct type
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, MultipleValuesWrongCount_1611) {
    UShortValue val;
    val.read("1 2 3");
    ASSERT_EQ(val.count(), 3u);

    ExifData exifData;
    SonyMakerNote::printFocusMode3(os, val, &exifData);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Valid value with specific focus mode value 5 and no matching meta version
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, FocusModeValue5NoMetaVersion_1611) {
    UShortValue val;
    val.read("5");
    ASSERT_EQ(val.count(), 1u);

    ExifData exifData;
    SonyMakerNote::printFocusMode3(os, val, &exifData);

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.front(), '(');
}

// Test: Undefined type should produce parenthesized output
TEST_F(SonyMakerNotePrintFocusMode3Test_1611, UndefinedType_OutputsParenthesizedValue_1611) {
    Value::UniquePtr val = Value::create(undefined);
    val->read("0");
    ASSERT_EQ(val->typeId(), undefined);

    ExifData exifData;
    SonyMakerNote::printFocusMode3(os, *val, &exifData);

    std::string result = os.str();
    // Either parenthesized or some error output, but should not crash
    EXPECT_FALSE(result.empty());
}
