#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD0(begin, iterator());

    MOCK_CONST_METHOD0(end, iterator());

    MOCK_CONST_METHOD1(findKey, const_iterator(const Exiv2::ExifKey&));

};



class CanonMakerNoteTest_935 : public ::testing::Test {

protected:

    MockExifData mockMetadata;

    Value mockValue;

};



TEST_F(CanonMakerNoteTest_935, TagListAm_ReturnsExpectedValue_935) {

    const auto* tagList = CanonMakerNote::tagListAm();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(CanonMakerNoteTest_935, PrintFiFileNumber_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintFocalLength_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, Print0x0008_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::print0x0008(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, Print0x000A_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::print0x000a(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, Print0x000C_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintCs0x0002_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printCs0x0002(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintCsLensType_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintCsLens_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printCsLens(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintLe0x0000_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printLe0x0000(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0001_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0001(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0002_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0002(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0003_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0003(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0009_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0009(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x000C_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x000c(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x000D_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x000d(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x000E_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0013_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0013(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0015_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0015(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0016_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0016(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0017_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0017(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintSi0x0018_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printSi0x0018(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_935, PrintFiFocusDistance_NormalOperation_935) {

    std::ostringstream os;

    auto result = CanonMakerNote::printFiFocusDistance(os, mockValue, &mockMetadata);

    EXPECT_EQ(&os, &result);

    EXPECT_FALSE(os.str().empty());

}
