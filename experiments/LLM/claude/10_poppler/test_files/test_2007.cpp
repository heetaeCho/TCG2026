#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "annot_stamp_experimental.h"
#include "GlobalParams.h"

class ExperimentalStampExtGStateDictTest_2007 : public ::testing::Test {
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
            "startxref\n196\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        doc = std::make_unique<PDFDoc>(std::unique_ptr<BaseStream>(stream));
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(ExperimentalStampExtGStateDictTest_2007, ReturnsNonNullDict_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, HasTwoEntries_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, HasKeyA0_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, HasKeyA1_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A0IsDict_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A1IsDict_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A0DictHasTwoEntries_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    EXPECT_EQ(a0Obj.getDict()->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A1DictHasTwoEntries_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    EXPECT_EQ(a1Obj.getDict()->getLength(), 2);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A0HasCAKey_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    EXPECT_TRUE(a0Obj.getDict()->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A0HasLowercaseCaKey_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    EXPECT_TRUE(a0Obj.getDict()->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A0CAValueIsApprox0588235_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Object caObj = a0Obj.getDict()->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A0LowercaseCaValueIsApprox0588235_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Object caObj = a0Obj.getDict()->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A1HasCAKey_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    EXPECT_TRUE(a1Obj.getDict()->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A1HasLowercaseCaKey_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    EXPECT_TRUE(a1Obj.getDict()->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A1CAValueIs1_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Object caObj = a1Obj.getDict()->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 1e-5);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, A1LowercaseCaValueIs1_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Object caObj = a1Obj.getDict()->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 1e-5);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, DoesNotHaveUnexpectedKeys_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("A0"));
    EXPECT_FALSE(extGStateDict->hasKey("A1"));
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, KeyNamesAreCorrect_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    ASSERT_EQ(extGStateDict->getLength(), 2);

    // Check the key names at indices 0 and 1
    std::string key0 = extGStateDict->getKey(0);
    std::string key1 = extGStateDict->getKey(1);

    // Both "a0" and "a1" should be present (order may vary)
    bool hasA0 = (key0 == "a0" || key1 == "a0");
    bool hasA1 = (key0 == "a1" || key1 == "a1");
    EXPECT_TRUE(hasA0);
    EXPECT_TRUE(hasA1);
    delete extGStateDict;
}

TEST_F(ExperimentalStampExtGStateDictTest_2007, MultipleCallsReturnIndependentDicts_2007) {
    ASSERT_TRUE(doc->isOk());
    Dict *dict1 = getExperimentalStampExtGStateDict(doc.get());
    Dict *dict2 = getExperimentalStampExtGStateDict(doc.get());
    ASSERT_NE(dict1, nullptr);
    ASSERT_NE(dict2, nullptr);
    EXPECT_NE(dict1, dict2);
    EXPECT_EQ(dict1->getLength(), dict2->getLength());
    delete dict1;
    delete dict2;
}
