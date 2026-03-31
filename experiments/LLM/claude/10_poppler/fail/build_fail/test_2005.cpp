#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "annot_stamp_final.h"
#include "GlobalParams.h"

class FinalStampExtGStateDictTest_2005 : public ::testing::Test {
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
            "startxref\n190\n%%EOF\n";

        auto stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        auto baseStr = std::unique_ptr<BaseStream>(stream);
        doc = std::make_unique<PDFDoc>(std::move(baseStr), std::optional<GooString>(), std::optional<GooString>());
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(FinalStampExtGStateDictTest_2005, ReturnsNonNullDict_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, DictHasTwoEntries_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 2);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, HasA0Key_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a0"));
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, HasA1Key_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a1"));
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A0IsDict_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A1IsDict_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A0DictHasTwoEntries_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A1DictHasTwoEntries_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A0DictHasCAKey_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A0DictHascaKey_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A0CAValueIsCorrect_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isReal() || caObj.isNum());
    EXPECT_NEAR(caObj.getReal(), 0.588235, 0.001);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A0caValueIsCorrect_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isReal() || caObj.isNum());
    EXPECT_NEAR(caObj.getReal(), 0.588235, 0.001);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A1CAValueIsOne_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isInt() || caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A1caValueIsOne_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isInt() || caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A1DictHasCAKey_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A1DictHascaKey_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, DoesNotHaveNonExistentKey_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->hasKey("a2"));
    EXPECT_FALSE(result->hasKey("nonexistent"));
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, KeyNamesAreCorrect_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->getLength(), 2);
    // Check the keys by name
    std::string key0 = result->getKey(0);
    std::string key1 = result->getKey(1);
    // The two keys should be "a0" and "a1" (order may vary)
    bool hasA0 = (key0 == "a0" || key1 == "a0");
    bool hasA1 = (key0 == "a1" || key1 == "a1");
    EXPECT_TRUE(hasA0);
    EXPECT_TRUE(hasA1);
    delete result;
}

TEST_F(FinalStampExtGStateDictTest_2005, A0AndA1HaveDifferentOpacityValues_2005) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getFinalStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);

    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Object a0CA = a0Obj.getDict()->lookup("CA");

    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Object a1CA = a1Obj.getDict()->lookup("CA");

    // a0 CA should be ~0.588235, a1 CA should be 1
    double a0Val = a0CA.getNum();
    double a1Val = a1CA.getNum();
    EXPECT_NE(a0Val, a1Val);
    EXPECT_LT(a0Val, a1Val);

    delete result;
}
