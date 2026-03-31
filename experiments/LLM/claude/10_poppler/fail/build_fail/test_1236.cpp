#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <vector>

#include "poppler/SignatureInfo.h"
#include "poppler/CertificateInfo.h"
#include "poppler/HashAlgorithm.h"
#include "poppler/CryptoSignBackend.h"
#include "poppler/GooString.h"

// ==================== SignatureInfo Tests ====================

class SignatureInfoTest_1236 : public ::testing::Test {
protected:
    void SetUp() override {
        sigInfo = std::make_unique<SignatureInfo>();
    }
    void TearDown() override {
        sigInfo.reset();
    }
    std::unique_ptr<SignatureInfo> sigInfo;
};

TEST_F(SignatureInfoTest_1236, DefaultSignatureValStatus_1236) {
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_NOT_VERIFIED);
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignatureValStatus_Valid_1236) {
    sigInfo->setSignatureValStatus(SIGNATURE_VALID);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_VALID);
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignatureValStatus_Invalid_1236) {
    sigInfo->setSignatureValStatus(SIGNATURE_INVALID);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_INVALID);
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignatureValStatus_DigestMismatch_1236) {
    sigInfo->setSignatureValStatus(SIGNATURE_DIGEST_MISMATCH);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_DIGEST_MISMATCH);
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignatureValStatus_DecodingError_1236) {
    sigInfo->setSignatureValStatus(SIGNATURE_DECODING_ERROR);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_DECODING_ERROR);
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignatureValStatus_GenericError_1236) {
    sigInfo->setSignatureValStatus(SIGNATURE_GENERIC_ERROR);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_GENERIC_ERROR);
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignatureValStatus_NotFound_1236) {
    sigInfo->setSignatureValStatus(SIGNATURE_NOT_FOUND);
    EXPECT_EQ(sigInfo->getSignatureValStatus(), SIGNATURE_NOT_FOUND);
}

TEST_F(SignatureInfoTest_1236, DefaultSignerName_1236) {
    EXPECT_TRUE(sigInfo->getSignerName().empty());
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignerName_1236) {
    sigInfo->setSignerName("Test Signer");
    EXPECT_EQ(sigInfo->getSignerName(), "Test Signer");
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignerNameEmpty_1236) {
    sigInfo->setSignerName("");
    EXPECT_TRUE(sigInfo->getSignerName().empty());
}

TEST_F(SignatureInfoTest_1236, SetAndGetSignerNameLong_1236) {
    std::string longName(1024, 'A');
    sigInfo->setSignerName(longName);
    EXPECT_EQ(sigInfo->getSignerName(), longName);
}

TEST_F(SignatureInfoTest_1236, DefaultSubjectDN_1236) {
    EXPECT_TRUE(sigInfo->getSubjectDN().empty());
}

TEST_F(SignatureInfoTest_1236, SetAndGetSubjectDN_1236) {
    sigInfo->setSubjectDN("CN=Test,O=Org");
    EXPECT_EQ(sigInfo->getSubjectDN(), "CN=Test,O=Org");
}

TEST_F(SignatureInfoTest_1236, DefaultHashAlgorithm_1236) {
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Unknown);
}

TEST_F(SignatureInfoTest_1236, SetAndGetHashAlgorithm_SHA256_1236) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha256);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha256);
}

TEST_F(SignatureInfoTest_1236, SetAndGetHashAlgorithm_SHA512_1236) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha512);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha512);
}

TEST_F(SignatureInfoTest_1236, SetAndGetHashAlgorithm_SHA1_1236) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha1);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha1);
}

TEST_F(SignatureInfoTest_1236, SetAndGetHashAlgorithm_Md5_1236) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Md5);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Md5);
}

TEST_F(SignatureInfoTest_1236, SetAndGetHashAlgorithm_Md2_1236) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Md2);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Md2);
}

TEST_F(SignatureInfoTest_1236, SetAndGetHashAlgorithm_Sha384_1236) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha384);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha384);
}

TEST_F(SignatureInfoTest_1236, SetAndGetHashAlgorithm_Sha224_1236) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha224);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha224);
}

TEST_F(SignatureInfoTest_1236, DefaultSigningTime_1236) {
    EXPECT_EQ(sigInfo->getSigningTime(), 0);
}

TEST_F(SignatureInfoTest_1236, SetAndGetSigningTime_1236) {
    time_t testTime = 1700000000;
    sigInfo->setSigningTime(testTime);
    EXPECT_EQ(sigInfo->getSigningTime(), testTime);
}

TEST_F(SignatureInfoTest_1236, SetAndGetSigningTimeZero_1236) {
    sigInfo->setSigningTime(0);
    EXPECT_EQ(sigInfo->getSigningTime(), 0);
}

TEST_F(SignatureInfoTest_1236, DefaultCertificateInfoIsNull_1236) {
    EXPECT_EQ(sigInfo->getCertificateInfo(), nullptr);
}

TEST_F(SignatureInfoTest_1236, SetAndGetCertificateInfo_1236) {
    auto certInfo = std::make_unique<X509CertificateInfo>();
    certInfo->setVersion(3);
    X509CertificateInfo* rawPtr = certInfo.get();
    sigInfo->setCertificateInfo(std::move(certInfo));
    EXPECT_NE(sigInfo->getCertificateInfo(), nullptr);
    EXPECT_EQ(sigInfo->getCertificateInfo()->getVersion(), 3);
}

TEST_F(SignatureInfoTest_1236, DefaultSubfilterSupport_1236) {
    EXPECT_FALSE(sigInfo->isSubfilterSupported());
}

TEST_F(SignatureInfoTest_1236, SetSubfilterSupportTrue_1236) {
    sigInfo->setSubFilterSupport(true);
    EXPECT_TRUE(sigInfo->isSubfilterSupported());
}

TEST_F(SignatureInfoTest_1236, SetSubfilterSupportFalse_1236) {
    sigInfo->setSubFilterSupport(true);
    sigInfo->setSubFilterSupport(false);
    EXPECT_FALSE(sigInfo->isSubfilterSupported());
}

TEST_F(SignatureInfoTest_1236, SetLocation_1236) {
    auto loc = std::make_unique<GooString>("Test Location");
    sigInfo->setLocation(std::move(loc));
    const GooString& location = sigInfo->getLocation();
    EXPECT_EQ(location.toStr(), "Test Location");
}

TEST_F(SignatureInfoTest_1236, SetReason_1236) {
    auto reason = std::make_unique<GooString>("Test Reason");
    sigInfo->setReason(std::move(reason));
    const GooString& r = sigInfo->getReason();
    EXPECT_EQ(r.toStr(), "Test Reason");
}

TEST_F(SignatureInfoTest_1236, OverwriteSignerName_1236) {
    sigInfo->setSignerName("First");
    sigInfo->setSignerName("Second");
    EXPECT_EQ(sigInfo->getSignerName(), "Second");
}

TEST_F(SignatureInfoTest_1236, OverwriteHashAlgorithm_1236) {
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha1);
    sigInfo->setHashAlgorithm(HashAlgorithm::Sha512);
    EXPECT_EQ(sigInfo->getHashAlgorithm(), HashAlgorithm::Sha512);
}

// ==================== X509CertificateInfo Tests ====================

class X509CertificateInfoTest_1236 : public ::testing::Test {
protected:
    void SetUp() override {
        certInfo = std::make_unique<X509CertificateInfo>();
    }
    void TearDown() override {
        certInfo.reset();
    }
    std::unique_ptr<X509CertificateInfo> certInfo;
};

TEST_F(X509CertificateInfoTest_1236, DefaultVersion_1236) {
    EXPECT_EQ(certInfo->getVersion(), -1);
}

TEST_F(X509CertificateInfoTest_1236, SetAndGetVersion_1236) {
    certInfo->setVersion(3);
    EXPECT_EQ(certInfo->getVersion(), 3);
}

TEST_F(X509CertificateInfoTest_1236, SetAndGetVersionZero_1236) {
    certInfo->setVersion(0);
    EXPECT_EQ(certInfo->getVersion(), 0);
}

TEST_F(X509CertificateInfoTest_1236, SetAndGetVersionNegative_1236) {
    certInfo->setVersion(-1);
    EXPECT_EQ(certInfo->getVersion(), -1);
}

TEST_F(X509CertificateInfoTest_1236, DefaultIsSelfSigned_1236) {
    EXPECT_FALSE(certInfo->getIsSelfSigned());
}

TEST_F(X509CertificateInfoTest_1236, SetIsSelfSignedTrue_1236) {
    certInfo->setIsSelfSigned(true);
    EXPECT_TRUE(certInfo->getIsSelfSigned());
}

TEST_F(X509CertificateInfoTest_1236, SetIsSelfSignedFalse_1236) {
    certInfo->setIsSelfSigned(true);
    certInfo->setIsSelfSigned(false);
    EXPECT_FALSE(certInfo->getIsSelfSigned());
}

TEST_F(X509CertificateInfoTest_1236, DefaultIsQualified_1236) {
    EXPECT_FALSE(certInfo->isQualified());
}

TEST_F(X509CertificateInfoTest_1236, SetQualifiedTrue_1236) {
    certInfo->setQualified(true);
    EXPECT_TRUE(certInfo->isQualified());
}

TEST_F(X509CertificateInfoTest_1236, SetQualifiedFalse_1236) {
    certInfo->setQualified(true);
    certInfo->setQualified(false);
    EXPECT_FALSE(certInfo->isQualified());
}

TEST_F(X509CertificateInfoTest_1236, SetAndGetSerialNumber_1236) {
    GooString serial("1234567890");
    certInfo->setSerialNumber(serial);
    EXPECT_EQ(certInfo->getSerialNumber().toStr(), "1234567890");
}

TEST_F(X509CertificateInfoTest_1236, SetAndGetNickName_1236) {
    GooString nick("TestNick");
    certInfo->setNickName(nick);
    EXPECT_EQ(certInfo->getNickName().toStr(), "TestNick");
}

TEST_F(X509CertificateInfoTest_1236, SetAndGetCertificateDER_1236) {
    GooString der("DERdata");
    certInfo->setCertificateDER(der);
    EXPECT_EQ(certInfo->getCertificateDER().toStr(), "DERdata");
}

TEST_F(X509CertificateInfoTest_1236, DefaultKeyUsageExtensions_1236) {
    EXPECT_EQ(certInfo->getKeyUsageExtensions(), 0u);
}

TEST_F(X509CertificateInfoTest_1236, SetAndGetKeyUsageExtensions_1236) {
    certInfo->setKeyUsageExtensions(0xFF);
    EXPECT_EQ(certInfo->getKeyUsageExtensions(), 0xFFu);
}

TEST_F(X509CertificateInfoTest_1236, OverwriteVersion_1236) {
    certInfo->setVersion(1);
    certInfo->setVersion(2);
    certInfo->setVersion(3);
    EXPECT_EQ(certInfo->getVersion(), 3);
}

// ==================== GooString Tests ====================

class GooStringTest_1236 : public ::testing::Test {
};

TEST_F(GooStringTest_1236, DefaultConstructor_1236) {
    GooString str;
    EXPECT_EQ(str.toStr(), "");
}

TEST_F(GooStringTest_1236, ConstructFromCString_1236) {
    GooString str("hello");
    EXPECT_EQ(str.toStr(), "hello");
}

TEST_F(GooStringTest_1236, ConstructFromStdString_1236) {
    std::string s = "world";
    GooString str(s);
    EXPECT_EQ(str.toStr(), "world");
}

TEST_F(GooStringTest_1236, ConstructFromStringView_1236) {
    std::string_view sv = "test";
    GooString str(sv);
    EXPECT_EQ(str.toStr(), "test");
}

TEST_F(GooStringTest_1236, ConstructFromCStringWithLength_1236) {
    GooString str("hello world", 5);
    EXPECT_EQ(str.toStr(), "hello");
}

TEST_F(GooStringTest_1236, ConstructFromNullCString_1236) {
    GooString str(static_cast<const char*>(nullptr));
    EXPECT_EQ(str.toStr(), "");
}

TEST_F(GooStringTest_1236, MoveConstructor_1236) {
    GooString str1("movable");
    GooString str2(std::move(str1));
    EXPECT_EQ(str2.toStr(), "movable");
}

TEST_F(GooStringTest_1236, CopyMethod_1236) {
    GooString str("copy me");
    auto copy = str.copy();
    EXPECT_EQ(copy->toStr(), "copy me");
}

TEST_F(GooStringTest_1236, GetCharAt_1236) {
    GooString str("abc");
    EXPECT_EQ(str.getChar(0), 'a');
    EXPECT_EQ(str.getChar(1), 'b');
    EXPECT_EQ(str.getChar(2), 'c');
}

TEST_F(GooStringTest_1236, SetCharAt_1236) {
    GooString str("abc");
    str.setChar(1, 'X');
    EXPECT_EQ(str.getChar(1), 'X');
    EXPECT_EQ(str.toStr(), "aXc");
}

TEST_F(GooStringTest_1236, LowerCase_1236) {
    std::string s = "HELLO";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST_F(GooStringTest_1236, LowerCaseAlreadyLower_1236) {
    std::string s = "hello";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST_F(GooStringTest_1236, LowerCaseMixed_1236) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST_F(GooStringTest_1236, LowerCaseEmpty_1236) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

TEST_F(GooStringTest_1236, ToLowerCaseStringView_1236) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

TEST_F(GooStringTest_1236, MoveAssignment_1236) {
    GooString str1("first");
    GooString str2("second");
    str1 = std::move(str2);
    EXPECT_EQ(str1.toStr(), "second");
}

TEST_F(GooStringTest_1236, ConstructFromMoveStdString_1236) {
    std::string s = "moved string";
    GooString str(std::move(s));
    EXPECT_EQ(str.toStr(), "moved string");
}

TEST_F(GooStringTest_1236, ConstructFromSubstringWithIndex_1236) {
    std::string s = "hello world";
    GooString str(s, 6, 5);
    EXPECT_EQ(str.toStr(), "world");
}

// ==================== Object Tests ====================

class ObjectTest_1236 : public ::testing::Test {
};

TEST_F(ObjectTest_1236, DefaultConstructorIsNone_1236) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
}

TEST_F(ObjectTest_1236, BoolObject_1236) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_1236, BoolObjectFalse_1236) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_1236, IntObject_1236) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_1236, IntObjectNegative_1236) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_1236, IntObjectZero_1236) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_1236, RealObject_1236) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_1236, RealObjectZero_1236) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_1236, RealObjectNegative_1236) {
    Object obj(-2.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.5);
}

TEST_F(ObjectTest_1236, Int64Object_1236) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_1236, StringObject_1236) {
    Object obj(std::string("test string"));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(std::string(obj.getString()->toStr()), "test string");
}

TEST_F(ObjectTest_1236, NullObject_1236) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_1236, ErrorObject_1236) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
}

TEST_F(ObjectTest_1236, EofObject_1236) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
}

TEST_F(ObjectTest_1236, MoveConstructor_1236) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_1236, MoveAssignment_1236) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_1236, SetToNull_1236) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_1236, CopyObject_1236) {
    Object obj(42);
    Object objCopy = obj.copy();
    EXPECT_TRUE(objCopy.isInt());
    EXPECT_EQ(objCopy.getInt(), 42);
}

TEST_F(ObjectTest_1236, IsNumForInt_1236) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_1236, IsNumForReal_1236) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_1236, GetNumFromInt_1236) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_1236, GetNumFromReal_1236) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

TEST_F(ObjectTest_1236, GetNumWithDefaultValue_1236) {
    Object obj;
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_1236, GetBoolWithDefaultValue_1236) {
    Object obj;
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_1236, TypeNameForNone_1236) {
    Object obj;
    EXPECT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_1236, IntOrInt64ForInt_1236) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

TEST_F(ObjectTest_1236, IntOrInt64ForInt64_1236) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_1236, NotBoolForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectTest_1236, NotIntForBool_1236) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectTest_1236, NotStringForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isString());
}

TEST_F(ObjectTest_1236, NotArrayForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isArray());
}

TEST_F(ObjectTest_1236, NotDictForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isDict());
}

TEST_F(ObjectTest_1236, NotStreamForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectTest_1236, NotRefForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectTest_1236, NotCmdForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd());
}

TEST_F(ObjectTest_1236, NotErrorForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectTest_1236, NotEOFForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectTest_1236, NotNoneForInt_1236) {
    Object obj(42);
    EXPECT_FALSE(obj.isNone());
}

// ==================== Ref Tests ====================

class RefTest_1236 : public ::testing::Test {
};

TEST_F(RefTest_1236, InvalidRef_1236) {
    Ref ref = Ref::INVALID();
    EXPECT_EQ(ref.num, -1);
    EXPECT_EQ(ref.gen, -1);
}

TEST_F(RefTest_1236, RefConstruction_1236) {
    Ref ref;
    ref.num = 10;
    ref.gen = 0;
    EXPECT_EQ(ref.num, 10);
    EXPECT_EQ(ref.gen, 0);
}

// ==================== AnnotColor Tests ====================

class AnnotColorTest_1236 : public ::testing::Test {
};

TEST_F(AnnotColorTest_1236, DefaultConstructor_1236) {
    AnnotColor color;
    // Default color should be valid
    auto values = color.getValues();
    // Just verify it doesn't crash
    SUCCEED();
}

TEST_F(AnnotColorTest_1236, GrayConstructor_1236) {
    AnnotColor color(0.5);
    auto values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.5);
}

TEST_F(AnnotColorTest_1236, RGBConstructor_1236) {
    AnnotColor color(1.0, 0.0, 0.5);
    auto values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 1.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.5);
}

TEST_F(AnnotColorTest_1236, CMYKConstructor_1236) {
    AnnotColor color(0.1, 0.2, 0.3, 0.4);
    auto values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.1);
    EXPECT_DOUBLE_EQ(values[1], 0.2);
    EXPECT_DOUBLE_EQ(values[2], 0.3);
    EXPECT_DOUBLE_EQ(values[3], 0.4);
}

TEST_F(AnnotColorTest_1236, GrayBlack_1236) {
    AnnotColor color(0.0);
    auto values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 0.0);
}

TEST_F(AnnotColorTest_1236, GrayWhite_1236) {
    AnnotColor color(1.0);
    auto values = color.getValues();
    EXPECT_DOUBLE_EQ(values[0], 1.0);
}

// ==================== CryptoSign Factory Tests ====================

class CryptoSignFactoryTest_1236 : public ::testing::Test {
};

TEST_F(CryptoSignFactoryTest_1236, GetAvailableBackends_1236) {
    auto available = CryptoSign::Factory::getAvailable();
    // Just verify it returns without crashing; content depends on build config
    SUCCEED();
}

TEST_F(CryptoSignFactoryTest_1236, GetActive_1236) {
    auto active = CryptoSign::Factory::getActive();
    // May or may not have an active backend
    SUCCEED();
}

TEST_F(CryptoSignFactoryTest_1236, TypeFromStringNSS_1236) {
    auto type = CryptoSign::Factory::typeFromString("NSS");
    // Result depends on build, but should not crash
    SUCCEED();
}

TEST_F(CryptoSignFactoryTest_1236, TypeFromStringInvalid_1236) {
    auto type = CryptoSign::Factory::typeFromString("NONEXISTENT_BACKEND");
    EXPECT_FALSE(type.has_value());
}

TEST_F(CryptoSignFactoryTest_1236, TypeFromStringEmpty_1236) {
    auto type = CryptoSign::Factory::typeFromString("");
    EXPECT_FALSE(type.has_value());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
