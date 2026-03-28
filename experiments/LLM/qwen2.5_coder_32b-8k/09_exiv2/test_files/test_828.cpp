#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpValueTest_828 : public ::testing::Test {

protected:

    XmpValue xmpValue;

};



TEST_F(XmpValueTest_828, DefaultConstructorInitializesXmpArrayTypeToNone_828) {

    EXPECT_EQ(xmpValue.xmpArrayType(), xaNone);

}



TEST_F(XmpValueTest_828, SetXmpArrayTypeUpdatesXmpArrayType_828) {

    xmpValue.setXmpArrayType(xaOrdered);

    EXPECT_EQ(xmpValue.xmpArrayType(), xaOrdered);



    xmpValue.setXmpArrayType(xaAlternative);

    EXPECT_EQ(xmpValue.xmpArrayType(), xaAlternative);



    xmpValue.setXmpArrayType(xaBag);

    EXPECT_EQ(xmpValue.xmpArrayType(), xaBag);



    xmpValue.setXmpArrayType(xaNone);

    EXPECT_EQ(xmpValue.xmpArrayType(), xaNone);

}



TEST_F(XmpValueTest_828, XmpArrayTypeMethodDoesNotModifyState_828) {

    XmpArrayType initialType = xmpValue.xmpArrayType();

    xmpValue.xmpArrayType();

    EXPECT_EQ(xmpValue.xmpArrayType(), initialType);

}



// Assuming that the size and copy methods have observable behavior through their return values

TEST_F(XmpValueTest_828, SizeReturnsNonNegativeValue_828) {

    EXPECT_GE(xmpValue.size(), 0u);

}



TEST_F(XmpValueTest_828, CopyMethodWithValidBufferDoesNotThrow_828) {

    byte buffer[100];

    EXPECT_NO_THROW(xmpValue.copy(buffer, ByteOrder::bigEndian));

}



// Assuming that the read methods have observable behavior through their return values

TEST_F(XmpValueTest_828, ReadWithByteArrayDoesNotThrow_828) {

    const byte buffer[] = {0x01, 0x02, 0x03};

    EXPECT_NO_THROW(xmpValue.read(buffer, sizeof(buffer), ByteOrder::bigEndian));

}



TEST_F(XmpValueTest_828, ReadWithStringDoesNotThrow_828) {

    std::string buffer = "test";

    EXPECT_NO_THROW(xmpValue.read(buffer));

}
