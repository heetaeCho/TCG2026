#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/canonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD0(typeName, std::string() const);

    MOCK_METHOD1(write, size_t(byte* pBlob) const);

    MOCK_METHOD0(copy, std::unique_ptr<Exiv2::Value>() const);

};



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_METHOD0(begin, iterator());

    MOCK_METHOD0(end, iterator());

    MOCK_CONST_METHOD1(findKey, const_iterator(const Exiv2::ExifKey& key) const);

};



TEST(CanonMakerNoteTest_929, TagListCi_ReturnsConstantValue_929) {

    auto result = CanonMakerNote::tagListCi();

    EXPECT_NE(result, nullptr);

}



TEST(CanonMakerNoteTest_929, PrintFiFileNumber_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintFocalLength_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, Print0x0008_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::print0x0008(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, Print0x000A_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::print0x000a(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, Print0x000C_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintCs0x0002_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printCs0x0002(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintCsLensType_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintCsLens_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printCsLens(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintLe0x0000_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printLe0x0000(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0001_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0001(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0002_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0002(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0003_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0003(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0009_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0009(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x000C_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x000c(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x000D_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x000d(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x000E_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0013_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0013(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0015_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0015(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0016_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0016(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0017_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0017(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintSi0x0018_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printSi0x0018(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_929, PrintFiFocusDistance_NormalOperation_929) {

    MockExifData mockMetadata;

    MockValue mockValue;

    std::ostringstream os;



    CanonMakerNote::printFiFocusDistance(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}
