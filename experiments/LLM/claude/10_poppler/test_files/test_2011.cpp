#include <gtest/gtest.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "annot_stamp_sold.h"
#include "GlobalParams.h"

class SoldStampExtGStateDictTest_2011 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory to get a valid PDFDoc
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
            "startxref\n196\n%%EOF\n";

        auto stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        doc = std::make_unique<PDFDoc>(std::unique_ptr<BaseStream>(stream));
        ASSERT_TRUE(doc->isOk());
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(SoldStampExtGStateDictTest_2011, ReturnsNonNullDict_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, HasTwoEntries_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, HasA0Key_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, HasA1Key_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A0IsDict_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A1IsDict_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A0DictHasCAKey_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A0DictHascaKey_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A0DictCAValue_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isReal() || caObj.isNum());
    EXPECT_NEAR(caObj.getReal(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A0DictcaValue_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isReal() || caObj.isNum());
    EXPECT_NEAR(caObj.getReal(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A0DictHasTwoEntries_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A1DictHasCAKey_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A1DictHascaKey_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A1DictCAValue_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isInt() || caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A1DictcaValue_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isInt() || caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A1DictHasTwoEntries_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, DoesNotHaveNonExistentKey_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("nonexistent"));
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A0CAAndcaAreSameValue_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caUpperObj = a0Dict->lookup("CA");
    Object caLowerObj = a0Dict->lookup("ca");
    EXPECT_NEAR(caUpperObj.getNum(), caLowerObj.getNum(), 0.0001);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, A1CAAndcaAreSameValue_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caUpperObj = a1Dict->lookup("CA");
    Object caLowerObj = a1Dict->lookup("ca");
    EXPECT_NEAR(caUpperObj.getNum(), caLowerObj.getNum(), 0.0001);
    delete extGStateDict;
}

TEST_F(SoldStampExtGStateDictTest_2011, MultipleCallsReturnDistinctDicts_2011) {
    Dict *dict1 = getSoldStampExtGStateDict(doc.get());
    Dict *dict2 = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    EXPECT_NE(dict1, dict2);
    delete dict1;
    delete dict2;
}

TEST_F(SoldStampExtGStateDictTest_2011, KeysAreCorrectNames_2011) {
    Dict *extGStateDict = getSoldStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    ASSERT_EQ(extGStateDict->getLength(), 2);
    
    // Verify key names
    std::string key0 = extGStateDict->getKey(0);
    std::string key1 = extGStateDict->getKey(1);
    
    // Keys should be "a0" and "a1" (order may vary)
    bool hasA0 = (key0 == "a0" || key1 == "a0");
    bool hasA1 = (key0 == "a1" || key1 == "a1");
    EXPECT_TRUE(hasA0);
    EXPECT_TRUE(hasA1);
    delete extGStateDict;
}
