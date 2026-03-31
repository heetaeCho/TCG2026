#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cmath>

#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "GlobalParams.h"
#include "annot_stamp_for_comment.h"

class ForCommentStampTest_2006 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory for PDFDoc
        doc = createMinimalPDFDoc();
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Minimal PDF content
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
        auto str = std::unique_ptr<BaseStream>(stream);
        return std::make_unique<PDFDoc>(std::move(str), std::optional<GooString>(), std::optional<GooString>());
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that the function returns a non-null dictionary
TEST_F(ForCommentStampTest_2006, ReturnsNonNullDict_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

// Test that the returned dictionary has exactly 2 entries ("a0" and "a1")
TEST_F(ForCommentStampTest_2006, DictHasTwoEntries_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

// Test that the dictionary contains key "a0"
TEST_F(ForCommentStampTest_2006, DictHasKeyA0_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

// Test that the dictionary contains key "a1"
TEST_F(ForCommentStampTest_2006, DictHasKeyA1_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

// Test that "a0" value is a dictionary
TEST_F(ForCommentStampTest_2006, A0ValueIsDict_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

// Test that "a1" value is a dictionary
TEST_F(ForCommentStampTest_2006, A1ValueIsDict_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

// Test that a0 dictionary has "CA" key with value approximately 0.588235
TEST_F(ForCommentStampTest_2006, A0DictHasCA_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGStateDict;
}

// Test that a0 dictionary has "ca" key with value approximately 0.588235
TEST_F(ForCommentStampTest_2006, A0DictHas_ca_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGStateDict;
}

// Test that a0 dictionary has exactly 2 entries
TEST_F(ForCommentStampTest_2006, A0DictHasTwoEntries_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGStateDict;
}

// Test that a1 dictionary has "CA" key with value 1
TEST_F(ForCommentStampTest_2006, A1DictHasCA_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 1e-5);
    delete extGStateDict;
}

// Test that a1 dictionary has "ca" key with value 1
TEST_F(ForCommentStampTest_2006, A1DictHas_ca_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 1e-5);
    delete extGStateDict;
}

// Test that a1 dictionary has exactly 2 entries
TEST_F(ForCommentStampTest_2006, A1DictHasTwoEntries_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGStateDict;
}

// Test that the dictionary does not have any unexpected keys
TEST_F(ForCommentStampTest_2006, DictDoesNotHaveUnexpectedKeys_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("b0"));
    EXPECT_FALSE(extGStateDict->hasKey(""));
    delete extGStateDict;
}

// Test that calling the function multiple times produces independent dictionaries
TEST_F(ForCommentStampTest_2006, MultipleCallsProduceIndependentDicts_2006) {
    Dict *dict1 = getForCommentStampExtGStateDict(doc.get());
    Dict *dict2 = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    EXPECT_NE(dict1, dict2);
    EXPECT_EQ(dict1->getLength(), dict2->getLength());
    delete dict1;
    delete dict2;
}

// Test that the XRef of the returned dictionary matches the document's XRef
TEST_F(ForCommentStampTest_2006, DictXRefMatchesDoc_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getXRef(), doc->getXRef());
    delete extGStateDict;
}

// Test that the a0 sub-dictionary's XRef matches the document's XRef
TEST_F(ForCommentStampTest_2006, A0SubDictXRefMatchesDoc_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    EXPECT_EQ(a0Obj.getDict()->getXRef(), doc->getXRef());
    delete extGStateDict;
}

// Test key names of the outer dictionary
TEST_F(ForCommentStampTest_2006, OuterDictKeyNames_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    ASSERT_EQ(extGStateDict->getLength(), 2);
    // Keys should be "a0" and "a1" (order may vary but typically insertion order)
    std::string key0 = extGStateDict->getKey(0);
    std::string key1 = extGStateDict->getKey(1);
    bool hasA0 = (key0 == "a0" || key1 == "a0");
    bool hasA1 = (key0 == "a1" || key1 == "a1");
    EXPECT_TRUE(hasA0);
    EXPECT_TRUE(hasA1);
    delete extGStateDict;
}

// Test that CA and ca in a0 have the same value
TEST_F(ForCommentStampTest_2006, A0CAAndcaAreSame_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caUpperObj = a0Dict->lookup("CA");
    Object caLowerObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caUpperObj.isNum());
    ASSERT_TRUE(caLowerObj.isNum());
    EXPECT_DOUBLE_EQ(caUpperObj.getNum(), caLowerObj.getNum());
    delete extGStateDict;
}

// Test that CA and ca in a1 have the same value
TEST_F(ForCommentStampTest_2006, A1CAAndcaAreSame_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caUpperObj = a1Dict->lookup("CA");
    Object caLowerObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caUpperObj.isNum());
    ASSERT_TRUE(caLowerObj.isNum());
    EXPECT_DOUBLE_EQ(caUpperObj.getNum(), caLowerObj.getNum());
    delete extGStateDict;
}

// Test that a0 CA value is less than a1 CA value (0.588235 < 1.0)
TEST_F(ForCommentStampTest_2006, A0OpacityLessThanA1_2006) {
    Dict *extGStateDict = getForCommentStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a0Obj.isDict());
    ASSERT_TRUE(a1Obj.isDict());
    Object a0CA = a0Obj.getDict()->lookup("CA");
    Object a1CA = a1Obj.getDict()->lookup("CA");
    ASSERT_TRUE(a0CA.isNum());
    ASSERT_TRUE(a1CA.isNum());
    EXPECT_LT(a0CA.getNum(), a1CA.getNum());
    delete extGStateDict;
}
