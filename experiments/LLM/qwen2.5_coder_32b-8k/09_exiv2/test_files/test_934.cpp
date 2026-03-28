#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "canonmn_int.hpp"



using namespace Exiv2::Internal;



class CanonMakerNoteTest_934 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(CanonMakerNoteTest_934, TagListLeReturnsConstant_934) {

    const auto& tagList = CanonMakerNote::tagListLe();

    EXPECT_EQ(tagList, CanonMakerNote::tagInfoLe_);

}



TEST_F(CanonMakerNoteTest_934, PrintFiFileNumberDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printFiFileNumber(oss, mockValue, &mockMetadata));

}



TEST_F(CanonMakerNoteTest_934, PrintFocalLengthDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printFocalLength(oss, mockValue, &mockMetadata));

}



TEST_F(CanonMakerNoteTest_934, Print0x0008DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::print0x0008(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, Print0x000ADoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::print0x000a(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, Print0x000CDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::print0x000c(oss, mockValue, &mockMetadata));

}



TEST_F(CanonMakerNoteTest_934, PrintCs0x0002DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printCs0x0002(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintCsLensTypeDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printCsLensType(oss, mockValue, &mockMetadata));

}



TEST_F(CanonMakerNoteTest_934, PrintCsLensDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printCsLens(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintLe0x0000DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printLe0x0000(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0001DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0001(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0002DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0002(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0003DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0003(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0009DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0009(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x000CDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x000c(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x000DDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x000d(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x000EDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x000e(oss, mockValue, &mockMetadata));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0013DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0013(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0015DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0015(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0016DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0016(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0017DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0017(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintSi0x0018DoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printSi0x0018(oss, mockValue, nullptr));

}



TEST_F(CanonMakerNoteTest_934, PrintFiFocusDistanceDoesNotThrow_934) {

    std::ostringstream oss;

    EXPECT_NO_THROW(CanonMakerNote::printFiFocusDistance(oss, mockValue, nullptr));

}
