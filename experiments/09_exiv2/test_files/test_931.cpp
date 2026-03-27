#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_METHOD(void, clear, (), (override));

    MOCK_CONST_METHOD0(begin, iterator(), (override));

    MOCK_CONST_METHOD0(end, iterator(), (override));

};



TEST_F(CanonMakerNoteTest_931, tagListVigCor_ReturnsExpectedTagInfo_931) {

    const auto& tagInfo = CanonMakerNote::tagListVigCor();

    EXPECT_EQ(tagInfo.name_, "Vignetting Correction");

}



TEST_F(CanonMakerNoteTest_931, printFiFileNumber_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value; // Assuming Value is default constructible and usable in this context



    CanonMakerNote::printFiFileNumber(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printFocalLength_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printFocalLength(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, print0x0008_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::print0x0008(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, print0x000a_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::print0x000a(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, print0x000c_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::print0x000c(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printCs0x0002_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printCs0x0002(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printCsLensType_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printCsLensType(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printCsLens_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printCsLens(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printLe0x0000_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printLe0x0000(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0001_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0001(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0002_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0002(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0003_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0003(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0009_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0009(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x000c_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x000c(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x000d_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x000d(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x000e_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x000e(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0013_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0013(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0015_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0015(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0016_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0016(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0017_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0017(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printSi0x0018_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printSi0x0018(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_931, printFiFocusDistance_NormalOperation_931) {

    std::ostringstream os;

    MockExifData mockMetadata;

    Exiv2::Value value;



    CanonMakerNote::printFiFocusDistance(os, value, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}
