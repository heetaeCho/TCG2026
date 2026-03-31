#include <gtest/gtest.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "annot_stamp_expired.h"
#include "GlobalParams.h"

class ExpiredStampExtGStateDictTest_2008 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory to get a working PDFDoc
        static const char pdfData[] =
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

        auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        doc = std::make_unique<PDFDoc>(std::unique_ptr<BaseStream>(stream), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(ExpiredStampExtGStateDictTest_2008, ReturnsNonNullDict_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, HasTwoEntries_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, HasKeyA0_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, HasKeyA1_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A0IsDict_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A1IsDict_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A0DictHasTwoEntries_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A0DictHasCA_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A0DictHasCa_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A0CAValue_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A0CaValue_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A1DictHasTwoEntries_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A1DictHasCA_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A1DictHasCa_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A1CAValueIsOne_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A1CaValueIsOne_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, DoesNotHaveNonExistentKey_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("nonexistent"));
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, KeyNamesCorrect_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    ASSERT_EQ(extGStateDict->getLength(), 2);
    // Verify the key names
    std::string key0 = extGStateDict->getKey(0);
    std::string key1 = extGStateDict->getKey(1);
    // Keys should be "a0" and "a1" (order may vary)
    bool hasA0 = (key0 == "a0" || key1 == "a0");
    bool hasA1 = (key0 == "a1" || key1 == "a1");
    EXPECT_TRUE(hasA0);
    EXPECT_TRUE(hasA1);
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, A0AndA1HaveDifferentCAValues_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Object a0CA = a0Obj.getDict()->lookup("CA");
    
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Object a1CA = a1Obj.getDict()->lookup("CA");
    
    ASSERT_TRUE(a0CA.isNum());
    ASSERT_TRUE(a1CA.isNum());
    
    // a0 CA should be ~0.588235, a1 CA should be 1.0
    EXPECT_LT(a0CA.getNum(), a1CA.getNum());
    delete extGStateDict;
}

TEST_F(ExpiredStampExtGStateDictTest_2008, MultipleCallsReturnIndependentDicts_2008) {
    ASSERT_TRUE(doc->isOk());
    Dict *dict1 = getExpiredStampExtGStateDict(doc.get());
    Dict *dict2 = getExpiredStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    // They should be different pointers (independent allocations)
    EXPECT_NE(dict1, dict2);
    // But both should have the same structure
    EXPECT_EQ(dict1->getLength(), dict2->getLength());
    delete dict1;
    delete dict2;
}
