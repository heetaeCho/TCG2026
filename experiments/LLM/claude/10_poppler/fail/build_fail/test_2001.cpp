#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "annot_stamp_approved.h"
#include "GlobalParams.h"

class ApprovedStampExtGStateTest_2001 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory to get a working PDFDoc
        static const char pdfData[] =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
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

        auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        doc = std::make_unique<PDFDoc>(std::unique_ptr<BaseStream>(stream));
        ASSERT_TRUE(doc->isOk());
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(ApprovedStampExtGStateTest_2001, ReturnsNonNullDict_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, HasTwoEntries_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    EXPECT_EQ(extGState->getLength(), 2);
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, HasKeyA0_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    EXPECT_TRUE(extGState->hasKey("a0"));
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, HasKeyA1_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    EXPECT_TRUE(extGState->hasKey("a1"));
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A0IsDict_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A1IsDict_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A0DictHasCA_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A0DictHasLowercaseCa_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A0CAValueIs0Point588235_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A0LowercaseCaValueIs0Point588235_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A1DictHasCA_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A1DictHasLowercaseCa_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A1CAValueIs1_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 1e-5);
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A1LowercaseCaValueIs1_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 1e-5);
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A0DictHasTwoEntries_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A1DictHasTwoEntries_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, DoesNotHaveUnexpectedKeys_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    EXPECT_FALSE(extGState->hasKey("a2"));
    EXPECT_FALSE(extGState->hasKey("b0"));
    EXPECT_FALSE(extGState->hasKey(""));
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, KeyNamesAreCorrect_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    ASSERT_EQ(extGState->getLength(), 2);
    // Check key names (order may vary, so check both)
    std::string key0 = extGState->getKey(0);
    std::string key1 = extGState->getKey(1);
    EXPECT_TRUE((key0 == "a0" && key1 == "a1") || (key0 == "a1" && key1 == "a0"));
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, A0AndA1HaveDifferentCAValues_2001) {
    Dict *extGState = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);

    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Object a0CA = a0Obj.getDict()->lookup("CA");

    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Object a1CA = a1Obj.getDict()->lookup("CA");

    ASSERT_TRUE(a0CA.isNum());
    ASSERT_TRUE(a1CA.isNum());
    EXPECT_NE(a0CA.getNum(), a1CA.getNum());
    delete extGState;
}

TEST_F(ApprovedStampExtGStateTest_2001, MultipleCallsReturnIndependentDicts_2001) {
    Dict *extGState1 = getApprovedStampExtGStateDict(doc.get());
    Dict *extGState2 = getApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState1, nullptr);
    ASSERT_NE(extGState2, nullptr);
    EXPECT_NE(extGState1, extGState2);
    delete extGState1;
    delete extGState2;
}
