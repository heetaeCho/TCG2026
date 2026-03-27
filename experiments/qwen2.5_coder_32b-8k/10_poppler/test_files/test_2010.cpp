#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking the necessary classes for testing

class MockXRef : public XRef {

public:

    MOCK_METHOD(XRef*, getXRef, (), (override));

};



class MockPDFDoc : public PDFDoc {

public:

    explicit MockPDFDoc(std::unique_ptr<GooString>&& fileNameA,

                        const std::optional<GooString>& ownerPassword = std::nullopt,

                        const std::optional<GooString>& userPassword = std::nullopt,

                        const std::function<void(void)>& xrefReconstructedCallback = nullptr)

        : PDFDoc(std::move(fileNameA), ownerPassword, userPassword, xrefReconstructedCallback) {}



    MOCK_METHOD(XRef*, getXRef, (), (const override));

};



using namespace ::testing;



TEST(getNotForPublicReleaseStampExtGStateDictTest_2010, CreatesValidDictStructure_2010) {

    auto fileName = std::make_unique<GooString>("dummy.pdf");

    MockPDFDoc mockPdfDoc(std::move(fileName));



    Dict* result = getNotForPublicReleaseStampExtGStateDict(&mockPdfDoc);



    EXPECT_TRUE(result->hasKey("a0"));

    EXPECT_TRUE(result->hasKey("a1"));



    auto a0DictObj = result->lookupNF("a0");

    EXPECT_EQ(a0DictObj.getType(), dictType);

    Dict* a0Dict = a0DictObj.getDict();

    EXPECT_TRUE(a0Dict->hasKey("CA"));

    EXPECT_TRUE(a0Dict->hasKey("ca"));



    auto caValueA0 = a0Dict->lookupNF("CA");

    EXPECT_EQ(caValueA0.getType(), realType);

    EXPECT_DOUBLE_EQ(caValueA0.getNum(), 0.588235);



    auto caValueA1 = a0Dict->lookupNF("ca");

    EXPECT_EQ(caValueA1.getType(), realType);

    EXPECT_DOUBLE_EQ(caValueA1.getNum(), 0.588235);



    auto a1DictObj = result->lookupNF("a1");

    EXPECT_EQ(a1DictObj.getType(), dictType);

    Dict* a1Dict = a1DictObj.getDict();

    EXPECT_TRUE(a1Dict->hasKey("CA"));

    EXPECT_TRUE(a1Dict->hasKey("ca"));



    auto caValueA2 = a1Dict->lookupNF("CA");

    EXPECT_EQ(caValueA2.getType(), realType);

    EXPECT_DOUBLE_EQ(caValueA2.getNum(), 1.0);



    auto caValueA3 = a1Dict->lookupNF("ca");

    EXPECT_EQ(caValueA3.getType(), realType);

    EXPECT_DOUBLE_EQ(caValueA3.getNum(), 1.0);



    delete result;

}



TEST(getNotForPublicReleaseStampExtGStateDictTest_2010, CorrectXRefUsage_2010) {

    auto fileName = std::make_unique<GooString>("dummy.pdf");

    MockPDFDoc mockPdfDoc(std::move(fileName));



    EXPECT_CALL(mockPdfDoc, getXRef()).Times(3);



    Dict* result = getNotForPublicReleaseStampExtGStateDict(&mockPdfDoc);

    delete result;

}
