#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "crwimage_int.hpp"

#include "types.hpp"



namespace Exiv2 {

    namespace Internal {



class CiffComponentTest : public ::testing::Test {

protected:

    CiffComponent component;

};



TEST_F(CiffComponentTest_1782, DoPrint_NormalOperation_1782) {

    std::ostringstream os;

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate

    component.print(os, byteOrder, "prefix");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CiffComponentTest_1782, DoPrint_ValueSizeLessThan100_1782) {

    std::ostringstream os;

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate

    component.setValue(DataBuf(new byte[1], 1)); // small value size

    component.print(os, byteOrder, "prefix");

    EXPECT_TRUE(os.str().find("prefix*value*") != std::string::npos);

}



TEST_F(CiffComponentTest_1782, DoPrint_ValueSizeGreaterThan100_1782) {

    std::ostringstream os;

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate

    component.setValue(DataBuf(new byte[150], 150)); // large value size

    component.print(os, byteOrder, "prefix");

    EXPECT_FALSE(os.str().find("prefix*value*") != std::string::npos);

}



TEST_F(CiffComponentTest_1782, DoPrint_TypeIdDirectory_1782) {

    std::ostringstream os;

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate

    component.setValue(DataBuf(new byte[1], 1));

    component.setType(directory);

    component.print(os, byteOrder, "prefix");

    EXPECT_FALSE(os.str().find("prefix*value*") != std::string::npos);

}



TEST_F(CiffComponentTest_1782, DoPrint_TypeIdNotDirectory_1782) {

    std::ostringstream os;

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate

    component.setValue(DataBuf(new byte[1], 1));

    component.setType(unsignedByte);

    component.print(os, byteOrder, "prefix");

    EXPECT_TRUE(os.str().find("prefix*value*") != std::string::npos);

}



} // namespace Internal

} // namespace Exiv2
