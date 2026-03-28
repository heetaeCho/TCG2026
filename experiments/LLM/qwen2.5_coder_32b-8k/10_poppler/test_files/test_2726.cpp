#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>

#include <memory>

#include <poppler/PDFDoc.h>

#include <poppler/TextOutputDev.h>



using namespace testing;



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(int, getNumPages, (), (const override));

    MOCK_METHOD(double, getPageMediaWidth, (int), (const override));

    MOCK_METHOD(double, getPageMediaHeight, (int), (const override));

    MOCK_METHOD(double, getPageCropWidth, (int), (const override));

    MOCK_METHOD(double, getPageCropHeight, (int), (const override));

    MOCK_METHOD(void, displayPage, (OutputDev *, int, double, double, int, bool, bool, bool), (override));

};



class MockTextOutputDev : public TextOutputDev {

public:

    using TextOutputDev::TextOutputDev;

    MOCK_CONST_METHOD0(getFlows, const TextFlow*());

};



class PrintDocBBoxTest_2726 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = std::make_unique<MockPDFDoc>();

        textOut = std::make_unique<MockTextOutputDev>(nullptr, true, 0.0, false, false);

        output.reset(fopen("output.txt", "w+"));

        if (!output) {

            throw std::runtime_error("Failed to open file for writing");

        }

    }



    void TearDown() override {

        fclose(output.get());

        remove("output.txt");

    }



    FILE* getOutputFile() { return output.get(); }

    MockPDFDoc* getMockDoc() { return doc.get(); }

    MockTextOutputDev* getMockTextOut() { return textOut.get(); }



private:

    std::unique_ptr<FILE, decltype(&fclose)> output{nullptr, fclose};

    std::unique_ptr<MockPDFDoc> doc;

    std::unique_ptr<MockTextOutputDev> textOut;

};



TEST_F(PrintDocBBoxTest_2726, SinglePageDocument_PrintsOnePage_2726) {

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(1));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(1)).WillOnce(Return(595.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(1)).WillOnce(Return(842.0));

    EXPECT_CALL(*getMockTextOut(), getFlows()).WillRepeatedly(Return(nullptr));



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 1, 1);



    rewind(getOutputFile());

    char buffer[256];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, MultiplePagesDocument_PrintsMultiplePages_2726) {

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(3));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(1)).WillOnce(Return(595.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(1)).WillOnce(Return(842.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(2)).WillOnce(Return(612.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(2)).WillOnce(Return(792.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(3)).WillOnce(Return(595.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(3)).WillOnce(Return(842.0));

    EXPECT_CALL(*getMockTextOut(), getFlows()).WillRepeatedly(Return(nullptr));



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 1, 3);



    rewind(getOutputFile());

    char buffer[512];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n <page width=\"595\" height=\"842\">\n</page>\n <page width=\"612\" height=\"792\">\n</page>\n <page width=\"595\" height=\"842\">\n</page>\n</doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, BoundaryCondition_FirstPageGreaterThanLastPage_DoesNotPrintAnyPages_2726) {

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(3));

    EXPECT_CALL(*getMockTextOut(), getFlows()).Times(0);



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 3, 1);



    rewind(getOutputFile());

    char buffer[256];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n</doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, BoundaryCondition_FirstPageEqualToLastPage_PrintsOnePage_2726) {

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(3));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(2)).WillOnce(Return(595.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(2)).WillOnce(Return(842.0));

    EXPECT_CALL(*getMockTextOut(), getFlows()).WillRepeatedly(Return(nullptr));



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 2, 2);



    rewind(getOutputFile());

    char buffer[256];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n <page width=\"595\" height=\"842\">\n</page>\n</doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, ExceptionalCase_NoPagesInDocument_DoesNotPrintAnyPages_2726) {

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(0));

    EXPECT_CALL(*getMockTextOut(), getFlows()).Times(0);



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 1, 1);



    rewind(getOutputFile());

    char buffer[256];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n</doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, ExceptionalCase_PageNumberOutOfRange_DoesNotPrintPage_2726) {

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(1));

    EXPECT_CALL(*getMockTextOut(), getFlows()).Times(0);



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 2, 2);



    rewind(getOutputFile());

    char buffer[256];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n</doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, BoundaryCondition_FirstPageIsZero_DoesNotPrintAnyPages_2726) {

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(3));

    EXPECT_CALL(*getMockTextOut(), getFlows()).Times(0);



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 0, 1);



    rewind(getOutputFile());

    char buffer[256];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n</doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, BoundaryCondition_LastPageIsGreaterThanTotalPages_PrintsUpToLastPage_2726) {

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(3));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(1)).WillOnce(Return(595.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(1)).WillOnce(Return(842.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(2)).WillOnce(Return(612.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(2)).WillOnce(Return(792.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(3)).WillOnce(Return(595.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(3)).WillOnce(Return(842.0));

    EXPECT_CALL(*getMockTextOut(), getFlows()).WillRepeatedly(Return(nullptr));



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 1, 5);



    rewind(getOutputFile());

    char buffer[512];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n <page width=\"595\" height=\"842\">\n</page>\n <page width=\"612\" height=\"792\">\n</page>\n <page width=\"595\" height=\"842\">\n</page>\n</doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, NormalCase_UseCropBox_PrintsCropBoxDimensions_2726) {

    ::useCropBox = true;

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(1));

    EXPECT_CALL(*getMockDoc(), getPageCropWidth(1)).WillOnce(Return(590.0));

    EXPECT_CALL(*getMockDoc(), getPageCropHeight(1)).WillOnce(Return(837.0));

    EXPECT_CALL(*getMockTextOut(), getFlows()).WillRepeatedly(Return(nullptr));



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 1, 1);



    rewind(getOutputFile());

    char buffer[256];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n <page width=\"590\" height=\"837\">\n</page>\n</doc>\n", buffer);

}



TEST_F(PrintDocBBoxTest_2726, NormalCase_UseMediaBox_PrintsMediaBoxDimensions_2726) {

    ::useCropBox = false;

    EXPECT_CALL(*getMockDoc(), getNumPages()).WillOnce(Return(1));

    EXPECT_CALL(*getMockDoc(), getPageMediaWidth(1)).WillOnce(Return(595.0));

    EXPECT_CALL(*getMockDoc(), getPageMediaHeight(1)).WillOnce(Return(842.0));

    EXPECT_CALL(*getMockTextOut(), getFlows()).WillRepeatedly(Return(nullptr));



    printDocBBox(getOutputFile(), getMockDoc(), getMockTextOut(), 1, 1);



    rewind(getOutputFile());

    char buffer[256];

    fgets(buffer, sizeof(buffer), getOutputFile());



    EXPECT_STREQ("<doc>\n <page width=\"595\" height=\"842\">\n</page>\n</doc>\n", buffer);

}
