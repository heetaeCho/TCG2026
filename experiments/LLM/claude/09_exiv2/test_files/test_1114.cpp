#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace {

// Test fixture for TypeInfo tests
class TypeInfoTest_1114 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== typeSize tests ====================

TEST_F(TypeInfoTest_1114, TypeSizeInvalidTypeIdReturnsZero_1114) {
    EXPECT_EQ(0u, Exiv2::TypeInfo::typeSize(Exiv2::invalidTypeId));
}

TEST_F(TypeInfoTest_1114, TypeSizeUnsignedByteReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedByte));
}

TEST_F(TypeInfoTest_1114, TypeSizeAsciiStringReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::asciiString));
}

TEST_F(TypeInfoTest_1114, TypeSizeUnsignedShortReturnsTwo_1114) {
    EXPECT_EQ(2u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedShort));
}

TEST_F(TypeInfoTest_1114, TypeSizeUnsignedLongReturnsFour_1114) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedLong));
}

TEST_F(TypeInfoTest_1114, TypeSizeUnsignedRationalReturnsEight_1114) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedRational));
}

TEST_F(TypeInfoTest_1114, TypeSizeSignedByteReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::signedByte));
}

TEST_F(TypeInfoTest_1114, TypeSizeUndefinedReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::undefined));
}

TEST_F(TypeInfoTest_1114, TypeSizeSignedShortReturnsTwo_1114) {
    EXPECT_EQ(2u, Exiv2::TypeInfo::typeSize(Exiv2::signedShort));
}

TEST_F(TypeInfoTest_1114, TypeSizeSignedLongReturnsFour_1114) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::signedLong));
}

TEST_F(TypeInfoTest_1114, TypeSizeSignedRationalReturnsEight_1114) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::signedRational));
}

TEST_F(TypeInfoTest_1114, TypeSizeTiffFloatReturnsFour_1114) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::tiffFloat));
}

TEST_F(TypeInfoTest_1114, TypeSizeTiffDoubleReturnsEight_1114) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::tiffDouble));
}

TEST_F(TypeInfoTest_1114, TypeSizeTiffIfdReturnsFour_1114) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::tiffIfd));
}

TEST_F(TypeInfoTest_1114, TypeSizeStringReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::string));
}

TEST_F(TypeInfoTest_1114, TypeSizeDateReturnsEight_1114) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::date));
}

TEST_F(TypeInfoTest_1114, TypeSizeTimeReturnsEleven_1114) {
    EXPECT_EQ(11u, Exiv2::TypeInfo::typeSize(Exiv2::time));
}

TEST_F(TypeInfoTest_1114, TypeSizeCommentReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::comment));
}

TEST_F(TypeInfoTest_1114, TypeSizeDirectoryReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::directory));
}

TEST_F(TypeInfoTest_1114, TypeSizeXmpTextReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpText));
}

TEST_F(TypeInfoTest_1114, TypeSizeXmpAltReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpAlt));
}

TEST_F(TypeInfoTest_1114, TypeSizeXmpBagReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpBag));
}

TEST_F(TypeInfoTest_1114, TypeSizeXmpSeqReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpSeq));
}

TEST_F(TypeInfoTest_1114, TypeSizeLangAltReturnsOne_1114) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::langAlt));
}

TEST_F(TypeInfoTest_1114, TypeSizeUnknownTypeIdReturnsZero_1114) {
    // Using a cast to create an unknown TypeId value
    EXPECT_EQ(0u, Exiv2::TypeInfo::typeSize(static_cast<Exiv2::TypeId>(9999)));
}

TEST_F(TypeInfoTest_1114, TypeSizeNegativeTypeIdReturnsZero_1114) {
    EXPECT_EQ(0u, Exiv2::TypeInfo::typeSize(static_cast<Exiv2::TypeId>(-1)));
}

// ==================== typeName tests ====================

TEST_F(TypeInfoTest_1114, TypeNameInvalidTypeId_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::invalidTypeId);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Invalid", name);
}

TEST_F(TypeInfoTest_1114, TypeNameUnsignedByte_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedByte);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Byte", name);
}

TEST_F(TypeInfoTest_1114, TypeNameAsciiString_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::asciiString);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Ascii", name);
}

TEST_F(TypeInfoTest_1114, TypeNameUnsignedShort_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedShort);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Short", name);
}

TEST_F(TypeInfoTest_1114, TypeNameUnsignedLong_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedLong);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Long", name);
}

TEST_F(TypeInfoTest_1114, TypeNameUnsignedRational_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedRational);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Rational", name);
}

TEST_F(TypeInfoTest_1114, TypeNameSignedByte_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedByte);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SByte", name);
}

TEST_F(TypeInfoTest_1114, TypeNameUndefined_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::undefined);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Undefined", name);
}

TEST_F(TypeInfoTest_1114, TypeNameSignedShort_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedShort);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SShort", name);
}

TEST_F(TypeInfoTest_1114, TypeNameSignedLong_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedLong);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SLong", name);
}

TEST_F(TypeInfoTest_1114, TypeNameSignedRational_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedRational);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SRational", name);
}

TEST_F(TypeInfoTest_1114, TypeNameTiffFloat_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffFloat);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Float", name);
}

TEST_F(TypeInfoTest_1114, TypeNameTiffDouble_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffDouble);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Double", name);
}

TEST_F(TypeInfoTest_1114, TypeNameTiffIfd_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffIfd);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Ifd", name);
}

TEST_F(TypeInfoTest_1114, TypeNameString_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::string);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("String", name);
}

TEST_F(TypeInfoTest_1114, TypeNameDate_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::date);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Date", name);
}

TEST_F(TypeInfoTest_1114, TypeNameTime_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::time);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Time", name);
}

TEST_F(TypeInfoTest_1114, TypeNameComment_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::comment);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Comment", name);
}

TEST_F(TypeInfoTest_1114, TypeNameDirectory_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::directory);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Directory", name);
}

TEST_F(TypeInfoTest_1114, TypeNameXmpText_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpText);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpText", name);
}

TEST_F(TypeInfoTest_1114, TypeNameXmpAlt_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpAlt);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpAlt", name);
}

TEST_F(TypeInfoTest_1114, TypeNameXmpBag_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpBag);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpBag", name);
}

TEST_F(TypeInfoTest_1114, TypeNameXmpSeq_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpSeq);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpSeq", name);
}

TEST_F(TypeInfoTest_1114, TypeNameLangAlt_1114) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::langAlt);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("LangAlt", name);
}

TEST_F(TypeInfoTest_1114, TypeNameUnknownTypeIdReturnsNull_1114) {
    const char* name = Exiv2::TypeInfo::typeName(static_cast<Exiv2::TypeId>(9999));
    // Unknown type IDs should return nullptr or empty
    // Based on the find pattern, if not found it should return nullptr
    EXPECT_EQ(nullptr, name);
}

// ==================== typeId tests ====================

TEST_F(TypeInfoTest_1114, TypeIdFromNameByte_1114) {
    EXPECT_EQ(Exiv2::unsignedByte, Exiv2::TypeInfo::typeId("Byte"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameAscii_1114) {
    EXPECT_EQ(Exiv2::asciiString, Exiv2::TypeInfo::typeId("Ascii"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameShort_1114) {
    EXPECT_EQ(Exiv2::unsignedShort, Exiv2::TypeInfo::typeId("Short"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameLong_1114) {
    EXPECT_EQ(Exiv2::unsignedLong, Exiv2::TypeInfo::typeId("Long"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameRational_1114) {
    EXPECT_EQ(Exiv2::unsignedRational, Exiv2::TypeInfo::typeId("Rational"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameSByte_1114) {
    EXPECT_EQ(Exiv2::signedByte, Exiv2::TypeInfo::typeId("SByte"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameUndefined_1114) {
    EXPECT_EQ(Exiv2::undefined, Exiv2::TypeInfo::typeId("Undefined"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameSShort_1114) {
    EXPECT_EQ(Exiv2::signedShort, Exiv2::TypeInfo::typeId("SShort"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameSLong_1114) {
    EXPECT_EQ(Exiv2::signedLong, Exiv2::TypeInfo::typeId("SLong"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameSRational_1114) {
    EXPECT_EQ(Exiv2::signedRational, Exiv2::TypeInfo::typeId("SRational"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameFloat_1114) {
    EXPECT_EQ(Exiv2::tiffFloat, Exiv2::TypeInfo::typeId("Float"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameDouble_1114) {
    EXPECT_EQ(Exiv2::tiffDouble, Exiv2::TypeInfo::typeId("Double"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameIfd_1114) {
    EXPECT_EQ(Exiv2::tiffIfd, Exiv2::TypeInfo::typeId("Ifd"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameString_1114) {
    EXPECT_EQ(Exiv2::string, Exiv2::TypeInfo::typeId("String"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameDate_1114) {
    EXPECT_EQ(Exiv2::date, Exiv2::TypeInfo::typeId("Date"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameTime_1114) {
    EXPECT_EQ(Exiv2::time, Exiv2::TypeInfo::typeId("Time"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameComment_1114) {
    EXPECT_EQ(Exiv2::comment, Exiv2::TypeInfo::typeId("Comment"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameDirectory_1114) {
    EXPECT_EQ(Exiv2::directory, Exiv2::TypeInfo::typeId("Directory"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameXmpText_1114) {
    EXPECT_EQ(Exiv2::xmpText, Exiv2::TypeInfo::typeId("XmpText"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameXmpAlt_1114) {
    EXPECT_EQ(Exiv2::xmpAlt, Exiv2::TypeInfo::typeId("XmpAlt"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameXmpBag_1114) {
    EXPECT_EQ(Exiv2::xmpBag, Exiv2::TypeInfo::typeId("XmpBag"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameXmpSeq_1114) {
    EXPECT_EQ(Exiv2::xmpSeq, Exiv2::TypeInfo::typeId("XmpSeq"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameLangAlt_1114) {
    EXPECT_EQ(Exiv2::langAlt, Exiv2::TypeInfo::typeId("LangAlt"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromNameInvalid_1114) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("Invalid"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromUnknownNameReturnsInvalidTypeId_1114) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("NonExistentType"));
}

TEST_F(TypeInfoTest_1114, TypeIdFromEmptyStringReturnsInvalidTypeId_1114) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId(""));
}

TEST_F(TypeInfoTest_1114, TypeIdCaseSensitiveLowercase_1114) {
    // "byte" should not match "Byte" if comparison is case-sensitive
    Exiv2::TypeId result = Exiv2::TypeInfo::typeId("byte");
    EXPECT_EQ(Exiv2::invalidTypeId, result);
}

TEST_F(TypeInfoTest_1114, TypeIdCaseSensitiveUppercase_1114) {
    // "BYTE" should not match "Byte" if comparison is case-sensitive
    Exiv2::TypeId result = Exiv2::TypeInfo::typeId("BYTE");
    EXPECT_EQ(Exiv2::invalidTypeId, result);
}

// ==================== Roundtrip tests ====================

TEST_F(TypeInfoTest_1114, RoundtripTypeNameToTypeId_1114) {
    // For each known type, typeName -> typeId should roundtrip
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedByte);
    ASSERT_NE(nullptr, name);
    EXPECT_EQ(Exiv2::unsignedByte, Exiv2::TypeInfo::typeId(name));
}

TEST_F(TypeInfoTest_1114, RoundtripAllTypes_1114) {
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
        ASSERT_NE(nullptr, name) << "typeName returned null for typeId=" << typeId;
        EXPECT_EQ(typeId, Exiv2::TypeInfo::typeId(name))
            << "Roundtrip failed for typeId=" << typeId << " name=" << name;
    }
}

}  // namespace
