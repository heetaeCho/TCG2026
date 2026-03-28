#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>

#include "TestProjects/exiv2/src/canonmn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class CanonMakerNoteTest_965 : public ::testing::Test {

protected:

    CanonMakerNote canonMakerNote;

    std::ostringstream os;

    ExifData exifData;

};



TEST_F(CanonMakerNoteTest_965, PrintFiFocusDistance_NormalOperation_965) {

    Value value(signedShort);

    value.makeArray(1);

    static_cast<int16_t*>(value.data())[0] = 200;



    canonMakerNote.printFiFocusDistance(os, value, &exifData);



    EXPECT_EQ("2.00 m", os.str());

}



TEST_F(CanonMakerNoteTest_965, PrintFiFocusDistance_InfiniteValue_965) {

    Value value(signedShort);

    value.makeArray(1);

    static_cast<int16_t*>(value.data())[0] = -1;



    canonMakerNote.printFiFocusDistance(os, value, &exifData);



    EXPECT_EQ("Infinite", os.str());

}



TEST_F(CanonMakerNoteTest_965, PrintFiFocusDistance_ZeroValue_965) {

    Value value(signedShort);

    value.makeArray(1);

    static_cast<int16_t*>(value.data())[0] = 0;



    canonMakerNote.printFiFocusDistance(os, value, &exifData);



    EXPECT_EQ("0.00 m", os.str());

}



TEST_F(CanonMakerNoteTest_965, PrintFiFocusDistance_WrongType_965) {

    Value value(unsignedLong);

    value.makeArray(1);

    static_cast<uint32_t*>(value.data())[0] = 200;



    canonMakerNote.printFiFocusDistance(os, value, &exifData);



    EXPECT_EQ("200", os.str());

}



TEST_F(CanonMakerNoteTest_965, PrintFiFocusDistance_EmptyValue_965) {

    Value value(signedShort);

    value.makeArray(0);



    canonMakerNote.printFiFocusDistance(os, value, &exifData);



    EXPECT_EQ("", os.str());

}
