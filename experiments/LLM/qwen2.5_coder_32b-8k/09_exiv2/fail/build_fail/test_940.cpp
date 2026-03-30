#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"



namespace Exiv2 {

namespace Internal {



class MockExifData : public ExifData {

public:

    MOCK_CONST_METHOD0(begin, const_iterator());

    MOCK_CONST_METHOD0(end, const_iterator());

    // Add other necessary mocks if needed

};



class CanonMakerNoteTest_940 : public ::testing::Test {

protected:

    std::ostringstream os;

    MockExifData mockMetadata;

    Value mockValue;

};



TEST_F(CanonMakerNoteTest_940, PrintFiFileNumber_NormalOperation_940) {

    EXPECT_CALL(mockMetadata, begin()).Times(1);

    EXPECT_CALL(mockMetadata, end()).Times(1);



    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintFocalLength_NormalOperation_940) {

    EXPECT_CALL(mockMetadata, begin()).Times(1);

    EXPECT_CALL(mockMetadata, end()).Times(1);



    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, Print0x0008_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, Print0x000a_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, Print0x000c_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintCs0x0002_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintCsLensType_NormalOperation_940) {

    EXPECT_CALL(mockMetadata, begin()).Times(1);

    EXPECT_CALL(mockMetadata, end()).Times(1);



    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintCsLens_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintLe0x0000_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0001_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0002_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0003_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0009_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x000c_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x000d_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x000e_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0013_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0015_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0016_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0017_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintSi0x0018_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_940, PrintFiFocusDistance_NormalOperation_940) {

    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



}  // namespace Internal

}  // namespace Exiv2
