#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/canonmn_int.cpp" // Assuming this file contains the class definition



namespace Exiv2 {

namespace Internal {



class CanonMakerNoteTest_952 : public ::testing::Test {

protected:

    CanonMakerNote canonChangeNote;

    std::ostringstream oss;

};



TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_NormalOperation_952) {

    Value value(TypeId::unsignedByte);

    value.makeArray(5);

    for (size_t i = 0; i < 5; ++i) {

        value.toInt64(i) = static_cast<int64_t>(i); // Set values to 0, 1, 2, 3, 4

    }



    canonChangeNote.printLe0x0000(oss, value, nullptr);



    EXPECT_EQ("0001020304", oss.str());

}



TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_BoundaryCondition_EmptyValue_952) {

    Value value(TypeId::unsignedByte);

    canonChangeNote.printLe0x0000(oss, value, nullptr);



    EXPECT_EQ("()", oss.str());

}



TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_BoundaryCondition_SmallSize_952) {

    Value value(TypeId::unsignedByte);

    value.makeArray(1);

    value.toInt64(0) = 255;



    canonChangeNote.printLe0x0000(oss, value, nullptr);



    EXPECT_EQ("()", oss.str());

}



TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_BoundaryCondition_LargeSize_952) {

    Value value(TypeId::unsignedByte);

    value.makeArray(6);

    for (size_t i = 0; i < 6; ++i) {

        value.toInt64(i) = static_cast<int64_t>(i); // Set values to 0, 1, 2, 3, 4, 5

    }



    canonChangeNote.printLe0x0000(oss, value, nullptr);



    EXPECT_EQ("()", oss.str());

}



TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_ExceptionalCase_WrongTypeId_952) {

    Value value(TypeId::undefined);

    value.makeArray(5);



    canonChangeNote.printLe0x0000(oss, value, nullptr);



    EXPECT_EQ("()", oss.str());

}



TEST_F(CanonMakerNoteTest_952, PrintLe0x0000_ExceptionalCase_WrongSize_952) {

    Value value(TypeId::unsignedByte);

    value.makeArray(4);



    canonChangeNote.printLe0x0000(oss, value, nullptr);



    EXPECT_EQ("()", oss.str());

}



} // namespace Internal

} // namespace Exiv2
