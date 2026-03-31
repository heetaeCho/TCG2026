#include <gtest/gtest.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "annot_stamp_draft.h"
#include "GlobalParams.h"

class DraftStampExtGStateDictTest_2014 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory for PDFDoc
        doc = createMinimalPDFDoc();
    }

    void TearDown() override {
        // Clean up
    }

    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Minimal PDF content
        static const char *pdfContent =
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

        auto *stream = new MemStream(const_cast<char *>(pdfContent), 0, strlen(pdfContent), Object(objNull));
        auto baseStr = std::unique_ptr<BaseStream>(stream);
        return std::make_unique<PDFDoc>(std::move(baseStr), std::optional<GooString>(), std::optional<GooString>());
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that getDraftStampExtGStateDict returns a non-null Dict
TEST_F(DraftStampExtGStateDictTest_2014, ReturnsNonNullDict_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    delete result;
}

// Test that the returned Dict has exactly 2 entries (a0 and a1)
TEST_F(DraftStampExtGStateDictTest_2014, HasTwoEntries_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getLength(), 2);
    delete result;
}

// Test that the returned Dict has key "a0"
TEST_F(DraftStampExtGStateDictTest_2014, HasKeyA0_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a0"));
    delete result;
}

// Test that the returned Dict has key "a1"
TEST_F(DraftStampExtGStateDictTest_2014, HasKeyA1_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->hasKey("a1"));
    delete result;
}

// Test that "a0" value is a Dict
TEST_F(DraftStampExtGStateDictTest_2014, A0ValueIsDict_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete result;
}

// Test that "a1" value is a Dict
TEST_F(DraftStampExtGStateDictTest_2014, A1ValueIsDict_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete result;
}

// Test that "a0" dict has "CA" key with value approximately 0.588235
TEST_F(DraftStampExtGStateDictTest_2014, A0DictHasCAKey_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    Object caObj = a0Dict->lookup("CA");
    EXPECT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 0.001);
    delete result;
}

// Test that "a0" dict has "ca" key with value approximately 0.588235
TEST_F(DraftStampExtGStateDictTest_2014, A0DictHasLowercaseCaKey_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    Object caObj = a0Dict->lookup("ca");
    EXPECT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 0.001);
    delete result;
}

// Test that "a1" dict has "CA" key with value 1
TEST_F(DraftStampExtGStateDictTest_2014, A1DictHasCAKeyWithValue1_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    Object caObj = a1Dict->lookup("CA");
    EXPECT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete result;
}

// Test that "a1" dict has "ca" key with value 1
TEST_F(DraftStampExtGStateDictTest_2014, A1DictHasLowercaseCaKeyWithValue1_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    Object caObj = a1Dict->lookup("ca");
    EXPECT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 0.001);
    delete result;
}

// Test that "a0" dict has exactly 2 entries
TEST_F(DraftStampExtGStateDictTest_2014, A0DictHasTwoEntries_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a0Obj = result->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete result;
}

// Test that "a1" dict has exactly 2 entries
TEST_F(DraftStampExtGStateDictTest_2014, A1DictHasTwoEntries_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    Object a1Obj = result->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete result;
}

// Test that the returned dict does not have unexpected keys
TEST_F(DraftStampExtGStateDictTest_2014, DoesNotHaveUnexpectedKeys_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->hasKey("a2"));
    EXPECT_FALSE(result->hasKey("b0"));
    EXPECT_FALSE(result->hasKey(""));
    delete result;
}

// Test that calling the function multiple times produces consistent results
TEST_F(DraftStampExtGStateDictTest_2014, MultipleCallsProduceConsistentResults_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result1 = getDraftStampExtGStateDict(doc.get());
    Dict *result2 = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);

    EXPECT_EQ(result1->getLength(), result2->getLength());
    EXPECT_TRUE(result1->hasKey("a0"));
    EXPECT_TRUE(result2->hasKey("a0"));
    EXPECT_TRUE(result1->hasKey("a1"));
    EXPECT_TRUE(result2->hasKey("a1"));

    // Verify a0 CA values are the same
    Object a0Obj1 = result1->lookup("a0");
    Object a0Obj2 = result2->lookup("a0");
    Object ca1 = a0Obj1.getDict()->lookup("CA");
    Object ca2 = a0Obj2.getDict()->lookup("CA");
    EXPECT_NEAR(ca1.getNum(), ca2.getNum(), 0.0001);

    delete result1;
    delete result2;
}

// Test that the XRef used by the dict comes from the doc
TEST_F(DraftStampExtGStateDictTest_2014, DictUsesDocXRef_2014) {
    ASSERT_TRUE(doc->isOk());
    Dict *result = getDraftStampExtGStateDict(doc.get());
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getXRef(), doc->getXRef());
    delete result;
}
