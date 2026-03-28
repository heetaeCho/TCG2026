#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace {

// Test fixture for TypeInfo tests
class TypeInfoTest_1113 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== typeId() tests ====================

TEST_F(TypeInfoTest_1113, TypeIdFromByte_1113) {
    EXPECT_EQ(Exiv2::unsignedByte, Exiv2::TypeInfo::typeId("Byte"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromAscii_1113) {
    EXPECT_EQ(Exiv2::asciiString, Exiv2::TypeInfo::typeId("Ascii"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromShort_1113) {
    EXPECT_EQ(Exiv2::unsignedShort, Exiv2::TypeInfo::typeId("Short"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromLong_1113) {
    EXPECT_EQ(Exiv2::unsignedLong, Exiv2::TypeInfo::typeId("Long"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromRational_1113) {
    EXPECT_EQ(Exiv2::unsignedRational, Exiv2::TypeInfo::typeId("Rational"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromSByte_1113) {
    EXPECT_EQ(Exiv2::signedByte, Exiv2::TypeInfo::typeId("SByte"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromUndefined_1113) {
    EXPECT_EQ(Exiv2::undefined, Exiv2::TypeInfo::typeId("Undefined"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromSShort_1113) {
    EXPECT_EQ(Exiv2::signedShort, Exiv2::TypeInfo::typeId("SShort"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromSLong_1113) {
    EXPECT_EQ(Exiv2::signedLong, Exiv2::TypeInfo::typeId("SLong"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromSRational_1113) {
    EXPECT_EQ(Exiv2::signedRational, Exiv2::TypeInfo::typeId("SRational"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromFloat_1113) {
    EXPECT_EQ(Exiv2::tiffFloat, Exiv2::TypeInfo::typeId("Float"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromDouble_1113) {
    EXPECT_EQ(Exiv2::tiffDouble, Exiv2::TypeInfo::typeId("Double"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromIfd_1113) {
    EXPECT_EQ(Exiv2::tiffIfd, Exiv2::TypeInfo::typeId("Ifd"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromString_1113) {
    EXPECT_EQ(Exiv2::string, Exiv2::TypeInfo::typeId("String"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromDate_1113) {
    EXPECT_EQ(Exiv2::date, Exiv2::TypeInfo::typeId("Date"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromTime_1113) {
    EXPECT_EQ(Exiv2::time, Exiv2::TypeInfo::typeId("Time"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromComment_1113) {
    EXPECT_EQ(Exiv2::comment, Exiv2::TypeInfo::typeId("Comment"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromDirectory_1113) {
    EXPECT_EQ(Exiv2::directory, Exiv2::TypeInfo::typeId("Directory"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromXmpText_1113) {
    EXPECT_EQ(Exiv2::xmpText, Exiv2::TypeInfo::typeId("XmpText"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromXmpAlt_1113) {
    EXPECT_EQ(Exiv2::xmpAlt, Exiv2::TypeInfo::typeId("XmpAlt"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromXmpBag_1113) {
    EXPECT_EQ(Exiv2::xmpBag, Exiv2::TypeInfo::typeId("XmpBag"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromXmpSeq_1113) {
    EXPECT_EQ(Exiv2::xmpSeq, Exiv2::TypeInfo::typeId("XmpSeq"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromLangAlt_1113) {
    EXPECT_EQ(Exiv2::langAlt, Exiv2::TypeInfo::typeId("LangAlt"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromInvalid_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("Invalid"));
}

// Error/boundary cases for typeId()
TEST_F(TypeInfoTest_1113, TypeIdFromEmptyString_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId(""));
}

TEST_F(TypeInfoTest_1113, TypeIdFromUnknownString_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("NonExistent"));
}

TEST_F(TypeInfoTest_1113, TypeIdCaseSensitiveLowercase_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("byte"));
}

TEST_F(TypeInfoTest_1113, TypeIdCaseSensitiveUppercase_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("BYTE"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromWhitespace_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId(" Byte"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromTrailingWhitespace_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("Byte "));
}

// ==================== typeName() tests ====================

TEST_F(TypeInfoTest_1113, TypeNameFromUnsignedByte_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedByte);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Byte", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromAsciiString_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::asciiString);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Ascii", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromUnsignedShort_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedShort);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Short", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromUnsignedLong_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedLong);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Long", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromUnsignedRational_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedRational);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Rational", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromSignedByte_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedByte);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SByte", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromUndefined_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::undefined);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Undefined", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromSignedShort_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedShort);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SShort", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromSignedLong_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedLong);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SLong", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromSignedRational_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedRational);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SRational", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromTiffFloat_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffFloat);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Float", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromTiffDouble_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffDouble);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Double", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromTiffIfd_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffIfd);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Ifd", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromStringType_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::string);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("String", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromDate_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::date);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Date", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromTime_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::time);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Time", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromComment_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::comment);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Comment", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromDirectory_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::directory);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Directory", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromXmpText_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpText);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpText", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromXmpAlt_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpAlt);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpAlt", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromXmpBag_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpBag);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpBag", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromXmpSeq_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpSeq);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpSeq", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromLangAlt_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::langAlt);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("LangAlt", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromInvalidTypeId_1113) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::invalidTypeId);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Invalid", name);
}

TEST_F(TypeInfoTest_1113, TypeNameFromLastTypeId_1113) {
    // lastTypeId is not in the table, so it should return nullptr or some default
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::lastTypeId);
    // We just check the call doesn't crash; the result may be nullptr
    // for an unrecognized type
    (void)name;
}

// ==================== typeSize() tests ====================

TEST_F(TypeInfoTest_1113, TypeSizeUnsignedByte_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedByte));
}

TEST_F(TypeInfoTest_1113, TypeSizeAsciiString_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::asciiString));
}

TEST_F(TypeInfoTest_1113, TypeSizeUnsignedShort_1113) {
    EXPECT_EQ(2u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedShort));
}

TEST_F(TypeInfoTest_1113, TypeSizeUnsignedLong_1113) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedLong));
}

TEST_F(TypeInfoTest_1113, TypeSizeUnsignedRational_1113) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedRational));
}

TEST_F(TypeInfoTest_1113, TypeSizeSignedByte_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::signedByte));
}

TEST_F(TypeInfoTest_1113, TypeSizeUndefined_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::undefined));
}

TEST_F(TypeInfoTest_1113, TypeSizeSignedShort_1113) {
    EXPECT_EQ(2u, Exiv2::TypeInfo::typeSize(Exiv2::signedShort));
}

TEST_F(TypeInfoTest_1113, TypeSizeSignedLong_1113) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::signedLong));
}

TEST_F(TypeInfoTest_1113, TypeSizeSignedRational_1113) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::signedRational));
}

TEST_F(TypeInfoTest_1113, TypeSizeTiffFloat_1113) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::tiffFloat));
}

TEST_F(TypeInfoTest_1113, TypeSizeTiffDouble_1113) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::tiffDouble));
}

TEST_F(TypeInfoTest_1113, TypeSizeTiffIfd_1113) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::tiffIfd));
}

TEST_F(TypeInfoTest_1113, TypeSizeString_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::string));
}

TEST_F(TypeInfoTest_1113, TypeSizeDate_1113) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::date));
}

TEST_F(TypeInfoTest_1113, TypeSizeTime_1113) {
    EXPECT_EQ(11u, Exiv2::TypeInfo::typeSize(Exiv2::time));
}

TEST_F(TypeInfoTest_1113, TypeSizeComment_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::comment));
}

TEST_F(TypeInfoTest_1113, TypeSizeDirectory_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::directory));
}

TEST_F(TypeInfoTest_1113, TypeSizeXmpText_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpText));
}

TEST_F(TypeInfoTest_1113, TypeSizeXmpAlt_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpAlt));
}

TEST_F(TypeInfoTest_1113, TypeSizeXmpBag_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpBag));
}

TEST_F(TypeInfoTest_1113, TypeSizeXmpSeq_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpSeq));
}

TEST_F(TypeInfoTest_1113, TypeSizeLangAlt_1113) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::langAlt));
}

TEST_F(TypeInfoTest_1113, TypeSizeInvalidTypeId_1113) {
    EXPECT_EQ(0u, Exiv2::TypeInfo::typeSize(Exiv2::invalidTypeId));
}

// ==================== Round-trip tests ====================

TEST_F(TypeInfoTest_1113, RoundTripTypeNameToTypeId_1113) {
    // For each known type, converting name->id->name should be consistent
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedByte);
    ASSERT_NE(nullptr, name);
    Exiv2::TypeId id = Exiv2::TypeInfo::typeId(name);
    EXPECT_EQ(Exiv2::unsignedByte, id);
}

TEST_F(TypeInfoTest_1113, RoundTripAllTypes_1113) {
    Exiv2::TypeId types[] = {
        Exiv2::unsignedByte, Exiv2::asciiString, Exiv2::unsignedShort,
        Exiv2::unsignedLong, Exiv2::unsignedRational, Exiv2::signedByte,
        Exiv2::undefined, Exiv2::signedShort, Exiv2::signedLong,
        Exiv2::signedRational, Exiv2::tiffFloat, Exiv2::tiffDouble,
        Exiv2::tiffIfd, Exiv2::string, Exiv2::date, Exiv2::time,
        Exiv2::comment, Exiv2::directory, Exiv2::xmpText, Exiv2::xmpAlt,
        Exiv2::xmpBag, Exiv2::xmpSeq, Exiv2::langAlt
    };

    for (auto typeId : types) {
        const char* name = Exiv2::TypeInfo::typeName(typeId);
        ASSERT_NE(nullptr, name) << "typeName returned nullptr for typeId=" << typeId;
        Exiv2::TypeId roundTripped = Exiv2::TypeInfo::typeId(name);
        EXPECT_EQ(typeId, roundTripped) << "Round-trip failed for type name: " << name;
    }
}

// ==================== Additional edge cases ====================

TEST_F(TypeInfoTest_1113, TypeIdFromNumericString_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("123"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromSpecialCharacters_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("@#$%"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromPartialName_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("Byt"));
}

TEST_F(TypeInfoTest_1113, TypeIdFromNameWithExtraChars_1113) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("ByteExtra"));
}

}  // namespace
