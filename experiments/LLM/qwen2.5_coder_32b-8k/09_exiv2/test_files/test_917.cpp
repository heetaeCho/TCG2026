#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



// Mocking ExifData and Value for testing purposes

class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(void, write, (Exiv2::Byte* pArray) const, (const override));

    MOCK_METHOD(size_t, size, () const, (override));

};



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_METHOD(Exiv2::Value::AutoPtr, findKey, (const Exiv2::ExifKey& key), ());

};



TEST(CanonMakerNoteTest_917, TagListMvReturnsConstant_917) {

    auto tagList = CanonMakerNote::tagListMv();

    EXPECT_TRUE(tagList != nullptr);

}



TEST(CanonMakerNoteTest_917, PrintFiFileNumberNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintFocalLengthNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, Print0x0008NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::print0x0008(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, Print0x000aNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::print0x000a(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, Print0x000cNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintCs0x0002NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintCsLensTypeNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintCsLensNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printCsLens(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintLe0x0000NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0001NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0002NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0003NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0009NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x000cNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x000dNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x000eNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0013NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0015NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0016NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0017NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintSi0x0018NormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}



TEST(CanonMakerNoteTest_917, PrintFiFocusDistanceNormalOperation_917) {

    MockExifData mockMetadata;

    MockValue mockValue;



    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, mockValue, &mockMetadata);



    EXPECT_FALSE(os.str().empty());

}
