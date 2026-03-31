#include <gtest/gtest.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "GlobalParams.h"
#include "annot_stamp_not_approved.h"

class NotApprovedStampTest_2009 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory to get a PDFDoc with a valid XRef
        doc = createMinimalPDFDoc();
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Minimal PDF content
        static const char pdfData[] =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
            "xref\n0 3\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "trailer\n<< /Size 3 /Root 1 0 R >>\n"
            "startxref\n109\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        auto baseStr = std::unique_ptr<BaseStream>(stream);
        return std::make_unique<PDFDoc>(std::move(baseStr), std::optional<GooString>(), std::optional<GooString>());
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that the function returns a non-null dictionary
TEST_F(NotApprovedStampTest_2009, ReturnsNonNullDict_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    delete extGState;
}

// Test that the returned dictionary has exactly 2 entries (a0 and a1)
TEST_F(NotApprovedStampTest_2009, DictHasTwoEntries_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    EXPECT_EQ(extGState->getLength(), 2);
    delete extGState;
}

// Test that the dictionary contains key "a0"
TEST_F(NotApprovedStampTest_2009, DictHasKeyA0_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    EXPECT_TRUE(extGState->hasKey("a0"));
    delete extGState;
}

// Test that the dictionary contains key "a1"
TEST_F(NotApprovedStampTest_2009, DictHasKeyA1_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    EXPECT_TRUE(extGState->hasKey("a1"));
    delete extGState;
}

// Test that "a0" value is a dictionary
TEST_F(NotApprovedStampTest_2009, A0ValueIsDict_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGState;
}

// Test that "a1" value is a dictionary
TEST_F(NotApprovedStampTest_2009, A1ValueIsDict_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGState;
}

// Test that "a0" sub-dictionary has CA key with value ~0.588235
TEST_F(NotApprovedStampTest_2009, A0HasCA_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGState;
}

// Test that "a0" sub-dictionary has ca key with value ~0.588235
TEST_F(NotApprovedStampTest_2009, A0HasLowerCA_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGState;
}

// Test that "a0" sub-dictionary has exactly 2 entries
TEST_F(NotApprovedStampTest_2009, A0DictHasTwoEntries_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a0Obj = extGState->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    EXPECT_EQ(a0Obj.getDict()->getLength(), 2);
    delete extGState;
}

// Test that "a1" sub-dictionary has CA key with value 1
TEST_F(NotApprovedStampTest_2009, A1HasCA_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_DOUBLE_EQ(caObj.getNum(), 1.0);
    delete extGState;
}

// Test that "a1" sub-dictionary has ca key with value 1
TEST_F(NotApprovedStampTest_2009, A1HasLowerCA_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_DOUBLE_EQ(caObj.getNum(), 1.0);
    delete extGState;
}

// Test that "a1" sub-dictionary has exactly 2 entries
TEST_F(NotApprovedStampTest_2009, A1DictHasTwoEntries_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    Object a1Obj = extGState->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    EXPECT_EQ(a1Obj.getDict()->getLength(), 2);
    delete extGState;
}

// Test that non-existent keys are not present in the returned dictionary
TEST_F(NotApprovedStampTest_2009, DictDoesNotHaveNonExistentKey_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState, nullptr);
    EXPECT_FALSE(extGState->hasKey("a2"));
    EXPECT_FALSE(extGState->hasKey("b0"));
    EXPECT_FALSE(extGState->hasKey(""));
    delete extGState;
}

// Test calling the function multiple times produces independent results
TEST_F(NotApprovedStampTest_2009, MultipleCallsReturnIndependentDicts_2009) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGState1 = getNotApprovedStampExtGStateDict(doc.get());
    Dict *extGState2 = getNotApprovedStampExtGStateDict(doc.get());
    ASSERT_NE(extGState1, nullptr);
    ASSERT_NE(extGState2, nullptr);
    // They should be different allocations
    EXPECT_NE(extGState1, extGState2);
    // But same structure
    EXPECT_EQ(extGState1->getLength(), extGState2->getLength());
    delete extGState1;
    delete extGState2;
}
