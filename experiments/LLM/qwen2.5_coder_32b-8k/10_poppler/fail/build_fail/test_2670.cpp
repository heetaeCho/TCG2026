#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <memory>

#include "poppler/poppler/Link.h"

#include "poppler/utils/pdfinfo.cc"  // Assuming printLinkDest is exposed for testing



class MockLinkDest : public LinkDest {

public:

    MOCK_CONST_METHOD0(getKind, LinkDestKind());

    MOCK_CONST_METHOD0(getChangeLeft, bool());

    MOCK_CONST_METHOD0(getChangeTop, bool());

    MOCK_CONST_METHOD0(getChangeZoom, bool());

    MOCK_CONST_METHOD0(getLeft, double());

    MOCK_CONST_METHOD0(getTop, double());

    MOCK_CONST_METHOD0(getZoom, double());

    MOCK_CONST_METHOD0(getBottom, double());

    MOCK_CONST_METHOD0(getRight, double());

};



class PrintLinkDestTest_2670 : public ::testing::Test {

protected:

    std::unique_ptr<MockLinkDest> mock_link_dest;

    

    void SetUp() override {

        mock_link_dest = std::make_unique<MockLinkDest>();

    }

};



TEST_F(PrintLinkDestTest_2670, DestXYZ_AllValuesSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destXYZ));

    EXPECT_CALL(*mock_link_dest, getChangeLeft()).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_link_dest, getChangeTop()).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_link_dest, getChangeZoom()).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_link_dest, getLeft()).WillOnce(::testing::Return(10.5));

    EXPECT_CALL(*mock_link_dest, getTop()).WillOnce(::testing::Return(20.3));

    EXPECT_CALL(*mock_link_dest, getZoom()).WillOnce(::testing::Return(1.5));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ XYZ 10.5 20.3 1.50 ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestXYZ_NoValuesSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destXYZ));

    EXPECT_CALL(*mock_link_dest, getChangeLeft()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_link_dest, getChangeTop()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_link_dest, getChangeZoom()).WillOnce(::testing::Return(false));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ XYZ null null null ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFit_Default_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFit));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ Fit ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitH_TopSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitH));

    EXPECT_CALL(*mock_link_dest, getChangeTop()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_link_dest, getTop()).WillOnce(::testing::Return(30.2));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitH 30.2 ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitH_TopNotSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitH));

    EXPECT_CALL(*mock_link_dest, getChangeTop()).WillOnce(::testing::Return(false));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitH null ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitV_LeftSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitV));

    EXPECT_CALL(*mock_link_dest, getChangeLeft()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_link_dest, getLeft()).WillOnce(::testing::Return(40.1));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitV 40.1 ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitV_LeftNotSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitV));

    EXPECT_CALL(*mock_link_dest, getChangeLeft()).WillOnce(::testing::Return(false));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitV null ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitR_AllValuesSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitR));

    EXPECT_CALL(*mock_link_dest, getLeft()).WillOnce(::testing::Return(50.0));

    EXPECT_CALL(*mock_link_dest, getBottom()).WillOnce(::testing::Return(60.0));

    EXPECT_CALL(*mock_link_dest, getRight()).WillOnce(::testing::Return(70.0));

    EXPECT_CALL(*mock_link_dest, getTop()).WillOnce(::testing::Return(80.0));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitR 50 60 70 80 ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitB_Default_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitB));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitB ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitBH_TopSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitBH));

    EXPECT_CALL(*mock_link_dest, getChangeTop()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_link_dest, getTop()).WillOnce(::testing::Return(90.5));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitBH 90.5 ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitBH_TopNotSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitBH));

    EXPECT_CALL(*mock_link_dest, getChangeTop()).WillOnce(::testing::Return(false));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitBH null ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitBV_LeftSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitBV));

    EXPECT_CALL(*mock_link_dest, getChangeLeft()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_link_dest, getLeft()).WillOnce(::testing::Return(100.2));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitBV 100.2 ]\n");

}



TEST_F(PrintLinkDestTest_2670, DestFitBV_LeftNotSet_2670) {

    EXPECT_CALL(*mock_link_dest, getKind()).WillOnce(::testing::Return(destFitBV));

    EXPECT_CALL(*mock_link_dest, getChangeLeft()).WillOnce(::testing::Return(false));



    testing::internal::CaptureStdout();

    printLinkDest(mock_link_dest);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[ FitBV null ]\n");

}
