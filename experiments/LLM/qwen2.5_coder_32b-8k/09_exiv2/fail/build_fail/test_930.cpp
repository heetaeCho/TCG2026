#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class CanonMakerNoteTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value dummyValue;

    ExifData exifData;

};



TEST_F(CanonMakerNoteTest, PrintFiFileNumber_NormalOperation_930) {

    CanonMakerNote::printFiFileNumber(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintFocalLength_NormalOperation_930) {

    CanonMakerNote::printFocalLength(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, Print0x0008_NormalOperation_930) {

    CanonMakerNote::print0x0008(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, Print0x000A_NormalOperation_930) {

    CanonMakerNote::print0x000a(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, Print0x000C_NormalOperation_930) {

    CanonMakerNote::print0x000c(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintCs0x0002_NormalOperation_930) {

    CanonMakerNote::printCs0x0002(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintCsLensType_NormalOperation_930) {

    CanonMakerNote::printCsLensType(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintCsLens_NormalOperation_930) {

    CanonMakerNote::printCsLens(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintLe0x0000_NormalOperation_930) {

    CanonMakerNote::printLe0x0000(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0001_NormalOperation_930) {

    CanonMakerNote::printSi0x0001(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0002_NormalOperation_930) {

    CanonMakerNote::printSi0x0002(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0003_NormalOperation_930) {

    CanonMakerNote::printSi0x0003(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0009_NormalOperation_930) {

    CanonMakerNote::printSi0x0009(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x000C_NormalOperation_930) {

    CanonMakerNote::printSi0x000c(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x000D_NormalOperation_930) {

    CanonMakerNote::printSi0x000d(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x000E_NormalOperation_930) {

    CanonMakerNote::printSi0x000e(oss, dummyValue, &exifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0013_NormalOperation_930) {

    CanonMakerNote::printSi0x0013(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0015_NormalOperation_930) {

    CanonMakerNote::printSi0x0015(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0016_NormalOperation_930) {

    CanonMakerNote::printSi0x0016(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0017_NormalOperation_930) {

    CanonMakerNote::printSi0x0017(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0018_NormalOperation_930) {

    CanonMakerNote::printSi0x0018(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintFiFocusDistance_NormalOperation_930) {

    CanonMakerNote::printFiFocusDistance(oss, dummyValue, nullptr);

    EXPECT_FALSE(oss.str().empty());

}
