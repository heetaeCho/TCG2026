#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;



class CopyIptcToXmpTest_1860 : public ::testing::Test {

protected:

    IptcData iptcData;

    XmpData xmpData;

};



TEST_F(CopyIptcToXmpTest_1860, NormalOperationWithCharset_1860) {

    // Arrange

    const char* charset = "UTF-8";

    iptcData.add(IptcKey("Iptc.Envelope.CodedCharacterSet", 0x01, 0x90), new Value);

    

    // Act

    copyIptcToXmp(iptcData, xmpData, charset);



    // Assert

    EXPECT_EQ(xmpData.count(), iptcData.size());

}



TEST_F(CopyIptcToXmpTest_1860, NormalOperationWithoutCharset_1860) {

    // Arrange

    iptcData.add(IptcKey("Iptc.Envelope.CodedCharacterSet", 0x01, 0x90), new Value);

    

    // Act

    copyIptcToXmp(iptcData, xmpData, nullptr);



    // Assert

    EXPECT_EQ(xmpData.count(), iptcData.size());

}



TEST_F(CopyIptcToXmpTest_1860, BoundaryConditionEmptyIptcData_1860) {

    // Arrange (empty IptcData)



    // Act

    copyIptcToXmp(iptcData, xmpData, nullptr);



    // Assert

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(CopyIptcToXmpTest_1860, BoundaryConditionLargeIptcData_1860) {

    // Arrange (large IptcData)

    for (size_t i = 0; i < 100; ++i) {

        iptcData.add(IptcKey("Iptc.Application2.Byline", 0x02, 0x50), new Value);

    }



    // Act

    copyIptcToXmp(iptcData, xmpData, nullptr);



    // Assert

    EXPECT_EQ(xmpData.count(), iptcData.size());

}



TEST_F(CopyIptcToXmpTest_1860, ExceptionalCaseInvalidCharset_1860) {

    // Arrange (invalid charset)

    const char* invalidCharset = "INVALID-CHARSET";

    iptcData.add(IptcKey("Iptc.Envelope.CodedCharacterSet", 0x01, 0x90), new Value);



    // Act & Assert

    copyIptcToXmp(iptcData, xmpData, invalidCharset);

    EXPECT_EQ(xmpData.count(), iptcData.size()); // Assuming it falls back to a default charset like ISO-8859-1

}



TEST_F(CopyIptcToXmpTest_1860, VerificationOfExternalInteractions_1860) {

    // Arrange (Mocking external collaborators if needed)

    // No mocks are required here as the function does not involve any callbacks or dependencies



    // Act

    copyIptcToXmp(iptcData, xmpData, nullptr);



    // Assert

    EXPECT_EQ(xmpData.count(), iptcData.size());

}
