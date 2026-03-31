#include <gtest/gtest.h>
#include <memory>
#include "PDFDoc.h"
#include "Dict.h"
#include "Object.h"
#include "GlobalParams.h"
#include "annot_stamp_as_is.h"

class AsIsStampExtGStateDictTest_2002 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
        // Create a minimal valid PDF in memory to get a working PDFDoc
        // We need a PDFDoc to get an XRef for Dict creation
        static const char pdfData[] = "%PDF-1.4\n"
                                       "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
                                       "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
                                       "xref\n0 3\n"
                                       "0000000000 65535 f \n"
                                       "0000000009 00000 n \n"
                                       "0000000058 00000 n \n"
                                       "trailer\n<< /Size 3 /Root 1 0 R >>\n"
                                       "startxref\n109\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        doc = std::make_unique<PDFDoc>(std::unique_ptr<BaseStream>(stream));
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(AsIsStampExtGStateDictTest_2002, ReturnsNonNullDict_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    ASSERT_NE(extGStateDict, nullptr);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, HasTwoEntries_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    EXPECT_EQ(extGStateDict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, HasKeyA0_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, HasKeyA1_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, DoesNotHaveUnexpectedKeys_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    EXPECT_FALSE(extGStateDict->hasKey("a2"));
    EXPECT_FALSE(extGStateDict->hasKey("b0"));
    EXPECT_FALSE(extGStateDict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A0IsDict_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a0Obj = extGStateDict->lookup("a0");
    EXPECT_TRUE(a0Obj.isDict());
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A1IsDict_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a1Obj = extGStateDict->lookup("a1");
    EXPECT_TRUE(a1Obj.isDict());
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A0DictHasTwoEntries_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_EQ(a0Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A1DictHasTwoEntries_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_EQ(a1Dict->getLength(), 2);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A0DictHasCAKey_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A0DictHasCaKey_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A0CAValueIs0588235_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A0CaValueIs0588235_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object caObj = a0Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 0.588235, 1e-5);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A1CAValueIs1_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("CA");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 1e-5);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A1CaValueIs1_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object caObj = a1Dict->lookup("ca");
    ASSERT_TRUE(caObj.isNum());
    EXPECT_NEAR(caObj.getNum(), 1.0, 1e-5);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A1DictHasCAKey_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    EXPECT_TRUE(a1Dict->hasKey("ca"));
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, KeyOrderA0First_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    ASSERT_GE(extGStateDict->getLength(), 2);
    // Verify that keys "a0" and "a1" exist (order may vary due to sorting)
    std::string key0 = extGStateDict->getKey(0);
    std::string key1 = extGStateDict->getKey(1);
    bool hasA0 = (key0 == "a0" || key1 == "a0");
    bool hasA1 = (key0 == "a1" || key1 == "a1");
    EXPECT_TRUE(hasA0);
    EXPECT_TRUE(hasA1);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A0CAAndCaAreSameValue_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a0Obj = extGStateDict->lookup("a0");
    ASSERT_TRUE(a0Obj.isDict());
    Dict *a0Dict = a0Obj.getDict();
    Object bigCA = a0Dict->lookup("CA");
    Object smallCa = a0Dict->lookup("ca");
    ASSERT_TRUE(bigCA.isNum());
    ASSERT_TRUE(smallCa.isNum());
    EXPECT_NEAR(bigCA.getNum(), smallCa.getNum(), 1e-10);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A1CAAndCaAreSameValue_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    Object a1Obj = extGStateDict->lookup("a1");
    ASSERT_TRUE(a1Obj.isDict());
    Dict *a1Dict = a1Obj.getDict();
    Object bigCA = a1Dict->lookup("CA");
    Object smallCa = a1Dict->lookup("ca");
    ASSERT_TRUE(bigCA.isNum());
    ASSERT_TRUE(smallCa.isNum());
    EXPECT_NEAR(bigCA.getNum(), smallCa.getNum(), 1e-10);
    delete extGStateDict;
}

TEST_F(AsIsStampExtGStateDictTest_2002, A0ValuesAreLessThanA1Values_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *extGStateDict = getAsIsStampExtGStateDict(doc.get());
    
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

TEST_F(AsIsStampExtGStateDictTest_2002, MultipleCallsReturnIndependentDicts_2002)
{
    ASSERT_TRUE(doc->isOk());
    Dict *dict1 = getAsIsStampExtGStateDict(doc.get());
    Dict *dict2 = getAsIsStampExtGStateDict(doc.get());
    
    EXPECT_NE(dict1, dict2);
    EXPECT_EQ(dict1->getLength(), dict2->getLength());
    
    delete dict1;
    delete dict2;
}
