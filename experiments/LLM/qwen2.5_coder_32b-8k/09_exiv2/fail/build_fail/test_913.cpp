#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



// Mock classes and objects if needed



TEST(CanonMakerNoteTagListPi_913, ReturnsExpectedValue_913) {

    const auto& tagList = CanonMakerNote::tagListPi();

    EXPECT_TRUE(tagList != nullptr); // Assuming the returned list is not null

}



class ValueMock : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(typeId, Exiv2::TypeId());

    MOCK_CONST_METHOD0(size, size_t());

    MOCK_CONST_METHOD1(toString, std::string(int) const);

};



class ExifDataMock : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD1(findKey, Exiv2::ExifData::const_iterator(const Exiv2::ExifKey&));

};



TEST(CanonMakerNotePrintFiFileNumber_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printFiFileNumber(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintFocalLength_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printFocalLength(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrint0x0008_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::print0x0008(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrint0x000a_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::print0x000a(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrint0x000c_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::print0x000c(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintCs0x0002_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printCs0x0002(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintCsLensType_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printCsLensType(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintCsLens_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printCsLens(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintLe0x0000_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printLe0x0000(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0001_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0001(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0002_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0002(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0003_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0003(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0009_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0009(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x000c_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x000c(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x000d_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x000d(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x000e_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x000e(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0013_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0013(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0015_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0015(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0016_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0016(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0017_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0017(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintSi0x0018_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printSi0x0018(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}



TEST(CanonMakerNotePrintFiFocusDistance_913, OutputsCorrectly_913) {

    std::ostringstream os;

    ValueMock valueMock;

    ExifDataMock exifDataMock;



    EXPECT_CALL(valueMock, toString(_)).WillOnce(::testing::Return("TestValue"));



    CanonMakerNote::printFiFocusDistance(os, valueMock, &exifDataMock);



    EXPECT_EQ(os.str(), "TestValue");

}
