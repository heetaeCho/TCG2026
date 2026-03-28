#include <gtest/gtest.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "GlobalParams.h"
#include "annot_stamp_not_for_public_release.h"

class NotForPublicReleaseStampTest_2010 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory or from file
        // We need a valid PDFDoc to get an XRef
        doc = createMinimalPDFDoc();
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal PDF document in memory
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        auto baseStr = std::unique_ptr<BaseStream>(stream);
        return std::make_unique<PDFDoc>(std::move(baseStr), std::optional<GooString>(), std::optional<GooString>());
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that the function returns a non-null Dict pointer
TEST_F(NotForPublicReleaseStampTest_2010, ReturnsNonNullDict_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

// Test that the returned dict has exactly 2 entries (a0 and a1)
TEST_F(NotForPublicReleaseStampTest_2010, DictHasTwoEntries_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

// Test that the dict contains key "a0"
TEST_F(NotForPublicReleaseStampTest_2010, DictContainsKeyA0_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

// Test that the dict contains key "a1"
TEST_F(NotForPublicReleaseStampTest_2010, DictContainsKeyA1_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

// Test that "a0" value is a Dict
TEST_F(NotForPublicReleaseStampTest_2010, A0ValueIsDict_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

// Test that "a1" value is a Dict
TEST_F(NotForPublicReleaseStampTest_2010, A1ValueIsDict_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

// Test that "a0" sub-dict has CA key with value ~0.588235
TEST_F(NotForPublicReleaseStampTest_2010, A0DictHasCA_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    Object caObj = a0Dict->lookup("CA");
    EXPECT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 0.0001);
    delete extGStateDict;
}

// Test that "a0" sub-dict has ca key with value ~0.588235
TEST_F(NotForPublicReleaseStampTest_2010, A0DictHasLowercaseCa_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    Object caObj = a0Dict->lookup("ca");
    EXPECT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 0.0001);
    delete extGStateDict;
}

// Test that "a1" sub-dict has CA key with value 1
TEST_F(NotForPublicReleaseStampTest_2010, A1DictHasCA_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    Object caObj = a1Dict->lookup("CA");
    EXPECT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.0001);
    delete extGStateDict;
}

// Test that "a1" sub-dict has ca key with value 1
TEST_F(NotForPublicReleaseStampTest_2010, A1DictHasLowercaseCa_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    Object caObj = a1Dict->lookup("ca");
    EXPECT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.0001);
    delete extGStateDict;
}

// Test that "a0" sub-dict has exactly 2 entries
TEST_F(NotForPublicReleaseStampTest_2010, A0DictHasTwoEntries_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    EXPECT_EQ(a0Obj.getDict()->getLength(), 2);
    delete extGStateDict;
}

// Test that "a1" sub-dict has exactly 2 entries
TEST_F(NotForPublicReleaseStampTest_2010, A1DictHasTwoEntries_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    EXPECT_EQ(a1Obj.getDict()->getLength(), 2);
    delete extGStateDict;
}

// Test that the dict does not contain unexpected keys
TEST_F(NotForPublicReleaseStampTest_2010, DictDoesNotContainUnexpectedKeys_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("b0"));
    EXPECT_FALSE(extGStateDict->hasKey(""));
    delete extGStateDict;
}

// Test that calling the function multiple times produces independent dicts
TEST_F(NotForPublicReleaseStampTest_2010, MultipleCalls_ProduceIndependentDicts_2010) {
    ASSERT_TRUE(doc->isOk());
    Dict *dict1 = getNotForPublicReleaseStampExtGStateDict(doc.get());
    Dict *dict2 = getNotForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    EXPECT_NE(dict1, dict2);
    EXPECT_EQ(dict1->getLength(), dict2->getLength());
    delete dict1;
    delete dict2;
}
