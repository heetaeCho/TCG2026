#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "goo/GooString.h"



using ::testing::Eq;

using ::testing::IsNull;

using ::testing::NotNull;



class PDFDocTest_989 : public ::testing::Test {

protected:

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        // Assuming a default constructor or mock setup is possible

        // Since we cannot instantiate directly due to private constructors, this is a placeholder.

        // In practice, you would need a way to create a valid PDFDoc instance for testing.

        // For the sake of this exercise, let's assume we can create one.

        pdfDoc = std::make_unique<PDFDoc>(nullptr, std::nullopt, std::nullopt, [](){});

    }

};



TEST_F(PDFDocTest_989, GetDocInfoCreatDate_ReturnsNullPtrWhenNotSet_989) {

    auto result = pdfDoc->getDocInfoCreatDate();

    EXPECT_THAT(result.get(), IsNull());

}



TEST_F(PDFDocTest_989, GetDocInfoCreatDate_ReturnsValidGooStringWhenSet_989) {

    std::unique_ptr<GooString> creationDate = std::make_unique<GooString>("D:20231005142300Z");

    pdfDoc->setDocInfoCreatDate(std::move(creationDate));



    auto result = pdfDoc->getDocInfoCreatDate();

    EXPECT_THAT(result.get(), NotNull());

    EXPECT_STREQ(result->getCString(), "D:20231005142300Z");

}



TEST_F(PDFDocTest_989, GetDocInfoCreatDate_MultipleCallsConsistent_989) {

    std::unique_ptr<GooString> creationDate = std::make_unique<GooString>("D:20231005142300Z");

    pdfDoc->setDocInfoCreatDate(std::move(creationDate));



    auto firstCallResult = pdfDoc->getDocInfoCreatDate();

    auto secondCallResult = pdfDoc->getDocInfoCreatDate();



    EXPECT_THAT(firstCallResult.get(), NotNull());

    EXPECT_STREQ(firstCallResult->getCString(), "D:20231005142300Z");

    EXPECT_EQ(firstCallResult.get(), secondCallResult.get()); // Check if they return the same pointer

}



TEST_F(PDFDocTest_989, GetDocInfoCreatDate_ReturnsDifferentInstancesOnEachCall_989) {

    std::unique_ptr<GooString> creationDate = std::make_unique<GooString>("D:20231005142300Z");

    pdfDoc->setDocInfoCreatDate(std::move(creationDate));



    auto firstCallResult = pdfDoc->getDocInfoCreatDate();

    auto secondCallResult = pdfDoc->getDocInfoCreatDate();



    EXPECT_THAT(firstCallResult.get(), NotNull());

    EXPECT_STREQ(firstCallResult->getCString(), "D:20231005142300Z");

    EXPECT_NE(firstCallResult.get(), secondCallResult.get()); // Check if they return different pointers

}
