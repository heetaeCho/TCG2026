#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/canonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class CanonMakerNoteTest_924 : public ::testing::Test {

protected:

    // Mock Value and ExifData classes

    class MockValue : public Exiv2::Value {

    public:

        MOCK_METHOD(void, write, (std::ostream& os) const, (const override));

    };



    class MockExifData : public Exiv2::ExifData {

    public:

        MOCK_METHOD(const Exiv2::Exifdatum&, operator[], (const Exiv2::ExifKey& key), (const override));

        MOCK_CONST_METHOD1(findKey, iterator((const Exiv2::ExifKey&)));

        MOCK_CONST_METHOD0(end, const_iterator());

    };



    MockValue mockValue;

    MockExifData mockMetadata;

};



TEST_F(CanonMakerNoteTest_924, PrintFiFileNumber_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintFocalLength_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, Print0x0008_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, Print0x000a_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, Print0x000c_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintCs0x0002_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintCsLensType_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintCsLens_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintLe0x0000_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0001_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0002_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0003_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0009_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x000c_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x000d_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x000e_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0013_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0015_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0016_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0017_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintSi0x0018_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, PrintFiFocusDistance_NormalOperation_924) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, write(_)).Times(1);

    CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_924, TagListAs_NormalOperation_924) {

    const auto& tagList = CanonMakerNote::tagListAs_();

    EXPECT_TRUE(tagList.size() > 0); // Assuming there should be at least one entry

}
