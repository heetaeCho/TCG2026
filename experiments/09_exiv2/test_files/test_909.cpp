#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"



namespace Exiv2 {

    class Value {};

    struct ExifData {};

}



using namespace ::testing;

using namespace Exiv2::Internal;



class CanonMakerNoteTest_909 : public Test {

protected:

    Exiv2::Value value;

    const Exiv2::ExifData* metadata = nullptr;

};



TEST_F(CanonMakerNoteTest_909, TagListCsReturnsConstexprArray_909) {

    auto tagListCs = CanonMakerNote::tagListCs();

    EXPECT_TRUE(tagListCs != nullptr);

}



TEST_F(CanonMakerNoteTest_909, PrintFiFileNumber_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printFiFileNumber(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintFocalLength_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printFocalLength(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, Print0x0008_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::print0x0008(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, Print0x000A_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::print0x000a(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, Print0x000C_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::print0x000c(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintCs0x0002_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printCs0x0002(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintCsLensType_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printCsLensType(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintCsLens_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printCsLens(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintLe0x0000_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printLe0x0000(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0001_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0001(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0002_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0002(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0003_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0003(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0009_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0009(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x000C_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x000c(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x000D_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x000d(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x000E_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x000e(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0013_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0013(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0015_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0015(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0016_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0016(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0017_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0017(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintSi0x0018_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0018(os, value, metadata);

    EXPECT_EQ(&os, &result);

}



TEST_F(CanonMakerNoteTest_909, PrintFiFocusDistance_ReturnsOstream_909) {

    std::ostringstream os;

    auto result = CanonMakerNote::printFiFocusDistance(os, value, metadata);

    EXPECT_EQ(&os, &result);

}
