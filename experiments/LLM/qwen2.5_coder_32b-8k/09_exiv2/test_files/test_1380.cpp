#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/exiv2.hpp>

#include "tags_int.cpp"



namespace {



using namespace Exiv2;

using namespace Exiv2::Internal;



class PrintUcs2Test_1380 : public ::testing::Test {

protected:

    Value value_;

};



TEST_F(PrintUcs2Test_1380, NormalOperation_UCS2LEtoUTF8_1380) {

    std::ostringstream os;

    DataBuf buffer(4);

    buffer.write_uint16(0x4100, 0); // 'A' in UCS-2LE

    buffer.write_uint16(0x4200, 2); // 'B' in UCS-2LE



    value_.setValue(buffer.data(), buffer.size());

    printUcs2(os, value_, nullptr);



    EXPECT_EQ("AB", os.str());

}



TEST_F(PrintUcs2Test_1380, BoundaryCondition_EmptyValue_1380) {

    std::ostringstream os;

    value_.setValue(nullptr, 0);

    printUcs2(os, value_, nullptr);



    EXPECT_TRUE(os.str().empty());

}



TEST_F(PrintUcs2Test_1380, BoundaryCondition_SingleByteValue_1380) {

    std::ostringstream os;

    DataBuf buffer(1);

    buffer.write_uint8(0x41, 0); // Invalid UCS-2LE



    value_.setValue(buffer.data(), buffer.size());

    printUcs2(os, value_, nullptr);



    EXPECT_EQ(value_, os.str());

}



TEST_F(PrintUcs2Test_1380, BoundaryCondition_PaddedZeros_1380) {

    std::ostringstream os;

    DataBuf buffer(6);

    buffer.write_uint16(0x4100, 0); // 'A' in UCS-2LE

    buffer.write_uint16(0x4200, 2); // 'B' in UCS-2LE

    buffer.write_uint16(0x0000, 4); // Padding zeros



    value_.setValue(buffer.data(), buffer.size());

    printUcs2(os, value_, nullptr);



    EXPECT_EQ("AB", os.str());

}



TEST_F(PrintUcs2Test_1380, ExceptionalCase_InvalidUCS2LE_1380) {

    std::ostringstream os;

    DataBuf buffer(4);

    buffer.write_uint16(0xD800, 0); // Invalid surrogate pair in UCS-2LE

    buffer.write_uint16(0xDC00, 2);



    value_.setValue(buffer.data(), buffer.size());

    printUcs2(os, value_, nullptr);



    EXPECT_EQ(value_, os.str());

}



} // namespace
