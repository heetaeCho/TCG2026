#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"



namespace Exiv2 {

    class Value {};

    class ExifData {};

}



using namespace Exiv2::Internal;

using namespace testing;



class CanonMakerNoteTest_911 : public Test {

protected:

    std::ostringstream os;

    Exiv2::Value value;

    const Exiv2::ExifData* metadata = nullptr;

};



TEST_F(CanonMakerNoteTest_911, TagListPa_ReturnsConstantExpression_911) {

    auto tagList = CanonMakerNote::tagListPa();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(CanonMakerNoteTest_911, PrintFiFileNumber_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintFocalLength_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, Print0x0008_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::print0x0008(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, Print0x000A_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::print0x000a(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, Print0x000C_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::print0x000c(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintCs0x0002_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintCsLensType_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintCsLens_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printCsLens(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintLe0x0000_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0001_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0002_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0003_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0009_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x000C_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x000D_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x000E_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0013_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0015_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0016_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0017_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintSi0x0018_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_911, PrintFiFocusDistance_NormalOperation_911) {

    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}
