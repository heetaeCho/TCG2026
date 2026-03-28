#include <gtest/gtest.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "GlobalParams.h"
#include "annot_stamp_for_public_release.h"

class ForPublicReleaseStampTest_2013 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory to get a working PDFDoc
        // We need a PDFDoc to get an XRef for Dict creation
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n190\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        auto baseStr = std::unique_ptr<BaseStream>(stream);
        doc = std::make_unique<PDFDoc>(std::move(baseStr), std::optional<GooString>(), std::optional<GooString>());
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(ForPublicReleaseStampTest_2013, ReturnsNonNullDict_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, ExtGStateDictHasTwoEntries_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, ExtGStateDictHasKeyA0_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, ExtGStateDictHasKeyA1_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A0EntryIsDict_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A1EntryIsDict_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A0DictHasTwoEntries_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A1DictHasTwoEntries_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A0DictHasCA_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A0DictHasLowercaseCa_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A0DictCAValue_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isReal() || caObj.isNum());
    EXPECT_NEAR(caObj.getReal(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A0DictLowercaseCaValue_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isReal() || caObj.isNum());
    EXPECT_NEAR(caObj.getReal(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A1DictHasCA_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A1DictHasLowercaseCa_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A1DictCAValue_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isInt() || caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A1DictLowercaseCaValue_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isInt() || caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, DoesNotHaveUnexpectedKeys_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    // Should only have "a0" and "a1"
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("a3"));
    EXPECT_FALSE(extGStateDict->hasKey("b0"));
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A0AndA1AreDistinctDicts_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a0Obj.isDict());
    ASSERT_TRUE(a1Obj.isDict());
    // The two sub-dicts should be different objects
    EXPECT_NE(a0Obj.getDict(), a1Obj.getDict());
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A0CAAndCaHaveSameValue_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caUpperObj = a0Dict->lookup("CA");
    Object caLowerObj = a0Dict->lookup("ca");
    EXPECT_NEAR(caUpperObj.getNum(), caLowerObj.getNum(), 0.0001);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, A1CAAndCaHaveSameValue_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caUpperObj = a1Dict->lookup("CA");
    Object caLowerObj = a1Dict->lookup("ca");
    EXPECT_NEAR(caUpperObj.getNum(), caLowerObj.getNum(), 0.0001);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, KeyNamesAreCorrect_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    // Verify key names at indices
    bool foundA0 = false, foundA1 = false;
    for (int i = 0; i < extGStateDict->getLength(); i++) {
        std::string key = extGStateDict->getKey(i);
        if (key == "a0") foundA0 = true;
        if (key == "a1") foundA1 = true;
    }
    EXPECT_TRUE(foundA0);
    EXPECT_TRUE(foundA1);
    delete extGStateDict;
}

TEST_F(ForPublicReleaseStampTest_2013, MultipleCallsReturnIndependentDicts_2013) {
    ASSERT_TRUE(doc->isOk());
    Dict *dict1 = getForPublicReleaseStampExtGStateDict(doc.get());
    Dict *dict2 = getForPublicReleaseStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    // Each call should return a different Dict pointer
    EXPECT_NE(dict1, dict2);
    // Both should have the same structure
    EXPECT_EQ(dict1->getLength(), dict2->getLength());
    delete dict1;
    delete dict2;
}
