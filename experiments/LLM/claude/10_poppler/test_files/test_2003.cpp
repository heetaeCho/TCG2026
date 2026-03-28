#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cmath>

#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "GlobalParams.h"
#include "annot_stamp_confidential.h"

class ConfidentialStampExtGStateTest_2003 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Create a minimal valid PDF in memory to get a valid PDFDoc
        doc = createMinimalPDFDoc();
        ASSERT_NE(doc, nullptr);
        ASSERT_TRUE(doc->isOk());
    }

    void TearDown() override {
        // Clean up
    }

    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal PDF document in memory
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
        return std::make_unique<PDFDoc>(std::unique_ptr<BaseStream>(stream), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that the function returns a non-null Dict pointer
TEST_F(ConfidentialStampExtGStateTest_2003, ReturnsNonNullDict_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

// Test that the returned dict has exactly 2 entries (a0 and a1)
TEST_F(ConfidentialStampExtGStateTest_2003, DictHasTwoEntries_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

// Test that the dict contains key "a0"
TEST_F(ConfidentialStampExtGStateTest_2003, DictContainsA0Key_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

// Test that the dict contains key "a1"
TEST_F(ConfidentialStampExtGStateTest_2003, DictContainsA1Key_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

// Test that "a0" value is a dictionary
TEST_F(ConfidentialStampExtGStateTest_2003, A0ValueIsDict_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

// Test that "a1" value is a dictionary
TEST_F(ConfidentialStampExtGStateTest_2003, A1ValueIsDict_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

// Test that "a0" dict has "CA" key with value ~0.588235
TEST_F(ConfidentialStampExtGStateTest_2003, A0HasCAValue_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGStateDict;
}

// Test that "a0" dict has "ca" key with value ~0.588235
TEST_F(ConfidentialStampExtGStateTest_2003, A0HasSmallCaValue_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGStateDict;
}

// Test that "a1" dict has "CA" key with value 1
TEST_F(ConfidentialStampExtGStateTest_2003, A1HasCAValue_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_DOUBLE_EQ(caObj.getNum(), 1.0);
    delete extGStateDict;
}

// Test that "a1" dict has "ca" key with value 1
TEST_F(ConfidentialStampExtGStateTest_2003, A1HasSmallCaValue_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_DOUBLE_EQ(caObj.getNum(), 1.0);
    delete extGStateDict;
}

// Test that "a0" dict has exactly 2 entries
TEST_F(ConfidentialStampExtGStateTest_2003, A0DictHasTwoEntries_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGStateDict;
}

// Test that "a1" dict has exactly 2 entries
TEST_F(ConfidentialStampExtGStateTest_2003, A1DictHasTwoEntries_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGStateDict;
}

// Test that "a0" dict does not have unexpected keys
TEST_F(ConfidentialStampExtGStateTest_2003, A0DictDoesNotHaveUnexpectedKeys_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_FALSE(a0Dict->hasKey("Type"));
    EXPECT_FALSE(a0Dict->hasKey("BM"));
    delete extGStateDict;
}

// Test that the outer dict does not contain unexpected keys
TEST_F(ConfidentialStampExtGStateTest_2003, DictDoesNotContainUnexpectedKeys_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("Type"));
    delete extGStateDict;
}

// Test that calling the function multiple times produces independent results
TEST_F(ConfidentialStampExtGStateTest_2003, MultipleCallsProduceIndependentDicts_2003) {
    Dict *dict1 = getConfidentialStampExtGStateDict(doc.get());
    Dict *dict2 = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    // They should be different objects
    EXPECT_NE(dict1, dict2);
    // But both should have the same structure
    EXPECT_EQ(dict1->getLength(), dict2->getLength());
    delete dict1;
    delete dict2;
}

// Test the key names of the outer dictionary
TEST_F(ConfidentialStampExtGStateTest_2003, OuterDictKeyNames_2003) {
    Dict *extGStateDict = getConfidentialStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    ASSERT_EQ(extGStateDict->getLength(), 2);
    // Check keys by index - order should be a0, a1 as added
    std::string key0 = extGStateDict->getKey(0);
    std::string key1 = extGStateDict->getKey(1);
    // Both keys should be present (order may vary)
    bool hasA0 = (key0 == "a0" || key1 == "a0");
    bool hasA1 = (key0 == "a1" || key1 == "a1");
    EXPECT_TRUE(hasA0);
    EXPECT_TRUE(hasA1);
    delete extGStateDict;
}
