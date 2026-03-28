#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "annot_stamp_top_secret.h"
#include "GlobalParams.h"

class TopSecretStampTest_2012 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [] /Count 0 >>\n"
            "endobj\n"
            "xref\n"
            "0 3\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "trailer\n"
            "<< /Size 3 /Root 1 0 R >>\n"
            "startxref\n"
            "109\n"
            "%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        auto baseStr = std::unique_ptr<BaseStream>(stream);
        doc = std::make_unique<PDFDoc>(std::move(baseStr), std::optional<GooString>(), std::optional<GooString>());
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(TopSecretStampTest_2012, ReturnsNonNullDict_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, ExtGStateDictHasTwoEntries_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, ExtGStateDictHasA0Key_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, ExtGStateDictHasA1Key_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A0EntryIsDict_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A1EntryIsDict_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A0DictHasTwoEntries_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A1DictHasTwoEntries_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A0DictCAValue_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();

    Object caUpperObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caUpperObj.isNum());
    EXPECT_NEAR(caUpperObj.getNum(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A0DictLowercaseCaValue_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();

    Object caLowerObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caLowerObj.isNum());
    EXPECT_NEAR(caLowerObj.getNum(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A1DictCAValue_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();

    Object caUpperObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caUpperObj.isNum());
    EXPECT_NEAR(caUpperObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A1DictLowercaseCaValue_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();

    Object caLowerObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caLowerObj.isNum());
    EXPECT_NEAR(caLowerObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A0DictHasCAKey_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A1DictHasCAKey_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, ExtGStateDictDoesNotHaveUnexpectedKeys_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("A0"));
    EXPECT_FALSE(extGStateDict->hasKey("A1"));
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, A0AndA1HaveDifferentOpacityValues_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);

    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Object a0CA = a0Obj.getDict()->lookup("CA");

    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Object a1CA = a1Obj.getDict()->lookup("CA");

    ASSERT_TRUE(a0CA.isNum());
    ASSERT_TRUE(a1CA.isNum());
    EXPECT_NE(a0CA.getNum(), a1CA.getNum());
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, KeyOrderInExtGStateDict_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    ASSERT_EQ(extGStateDict->getLength(), 2);

    // Verify the keys are "a0" and "a1" (order may vary depending on implementation)
    std::string key0 = extGStateDict->getKey(0);
    std::string key1 = extGStateDict->getKey(1);

    bool hasA0 = (key0 == "a0" || key1 == "a0");
    bool hasA1 = (key0 == "a1" || key1 == "a1");
    EXPECT_TRUE(hasA0);
    EXPECT_TRUE(hasA1);
    delete extGStateDict;
}

TEST_F(TopSecretStampTest_2012, MultipleCallsReturnIndependentDicts_2012) {
    ASSERT_TRUE(doc->isOk());
    Dict *dict1 = getTopSecretStampExtGStateDict(doc.get());
    Dict *dict2 = getTopSecretStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    EXPECT_NE(dict1, dict2);
    delete dict1;
    delete dict2;
}
