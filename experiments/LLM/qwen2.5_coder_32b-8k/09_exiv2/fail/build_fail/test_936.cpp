#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class CanonMakerNoteTest_936 : public ::testing::Test {

protected:

    // Mock Value and ExifData classes if necessary

    class MockValue {};

    class MockExifData {};



    MockValue mockValue_;

    MockExifData mockMetadata_;



    std::ostringstream oss_;

};



TEST_F(CanonMakerNoteTest_936, TagListMeReturnsCorrectTagInfo_936) {

    const auto& tagList = CanonMakerNote::tagListMe();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(CanonMakerNoteTest_936, PrintFiFileNumberNormalOperation_936) {

    std::ostream& result = CanonMakerNote::printFiFileNumber(oss_, mockValue_, &mockMetadata_);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintFocalLengthNormalOperation_936) {

    std::ostream& result = CanonMakerNote::printFocalLength(oss_, mockValue_, &mockMetadata_);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, Print0x0008NormalOperation_936) {

    std::ostream& result = CanonMakerNote::print0x0008(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, Print0x000ANormalOperation_936) {

    std::ostream& result = CanonMakerNote::print0x000a(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, Print0x000CNormalOperation_936) {

    std::ostream& result = CanonMakerNote::print0x000c(oss_, mockValue_, &mockMetadata_);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintCs0x0002NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printCs0x0002(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintCsLensTypeNormalOperation_936) {

    std::ostream& result = CanonMakerNote::printCsLensType(oss_, mockValue_, &mockMetadata_);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintCsLensNormalOperation_936) {

    std::ostream& result = CanonMakerNote::printCsLens(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintLe0x0000NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printLe0x0000(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0001NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0001(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0002NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0002(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0003NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0003(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0009NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0009(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x000CNormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x000c(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x000DNormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x000d(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x000ENormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x000e(oss_, mockValue_, &mockMetadata_);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0013NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0013(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0015NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0015(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0016NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0016(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0017NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0017(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintSi0x0018NormalOperation_936) {

    std::ostream& result = CanonMakerNote::printSi0x0018(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}



TEST_F(CanonMakerNoteTest_936, PrintFiFocusDistanceNormalOperation_936) {

    std::ostream& result = CanonMakerNote::printFiFocusDistance(oss_, mockValue_, nullptr);

    EXPECT_EQ(&result, &oss_);

    // Assuming some output is generated

    EXPECT_FALSE(oss_.str().empty());

}
