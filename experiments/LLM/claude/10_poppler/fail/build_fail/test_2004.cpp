#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "annot_stamp_departmental.h"
#include "GlobalParams.h"

class DepartmentalStampExtGStateTest_2004 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory to get a valid PDFDoc
        // We'll use a simple PDF structure
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Count 1/Kids[3 0 R]>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        auto stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        auto baseStream = std::unique_ptr<BaseStream>(stream);
        doc = std::make_unique<PDFDoc>(std::move(baseStream), std::optional<GooString>(), std::optional<GooString>());
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(DepartmentalStampExtGStateTest_2004, ReturnsNonNullDict_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, DictHasTwoEntries_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, HasA0Key_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, HasA1Key_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A0IsDict_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A1IsDict_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A0DictHasTwoEntries_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A1DictHasTwoEntries_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A0DictHasCAKey_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A0DictHascaKey_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A0CAValueIsReal_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    EXPECT_TRUE(caObj.isReal() || caObj.isNum());
    EXPECT_NEAR(caObj.getReal(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A0caValueIsReal_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    EXPECT_TRUE(caObj.isReal() || caObj.isNum());
    EXPECT_NEAR(caObj.getReal(), 0.588235, 0.001);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A1CAValueIsOne_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    EXPECT_TRUE(caObj.isInt() || caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A1caValueIsOne_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    EXPECT_TRUE(caObj.isInt() || caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A1DictHasCAKey_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A1DictHascaKey_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, DoesNotHaveNonexistentKey_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("nonexistent"));
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A0CAAndcaAreSameValue_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caUpperObj = a0Dict->lookup("CA");
    Object caLowerObj = a0Dict->lookup("ca");
    EXPECT_NEAR(caUpperObj.getNum(), caLowerObj.getNum(), 0.0001);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, A1CAAndcaAreSameValue_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caUpperObj = a1Dict->lookup("CA");
    Object caLowerObj = a1Dict->lookup("ca");
    EXPECT_NEAR(caUpperObj.getNum(), caLowerObj.getNum(), 0.0001);
    delete extGStateDict;
}

TEST_F(DepartmentalStampExtGStateTest_2004, KeyNamesAreCorrect_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    ASSERT_EQ(extGStateDict->getLength(), 2);
    
    // Verify keys are "a0" and "a1"
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

TEST_F(DepartmentalStampExtGStateTest_2004, MultipleCallsReturnDistinctDicts_2004) {
    ASSERT_TRUE(doc->isOk());
    Dict *dict1 = getDepartmentalStampExtGStateDict(doc.get());
    Dict *dict2 = getDepartmentalStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    EXPECT_NE(dict1, dict2);
    delete dict1;
    delete dict2;
}
