#include <gtest/gtest.h>

#include "XMPMeta.hpp"



TEST_F(SerializeAsRDFTest_2115, NormalOperation_NoOptions_2115) {

    XMPMeta xmpObj;

    XMP_VarString headStr, tailStr;

    SerializeAsRDF(xmpObj, headStr, tailStr, 0, "\n", "  ", 0);

    EXPECT_TRUE(headStr.find(kPacketHeader) != std::string::npos);

    EXPECT_TRUE(tailStr.find(kPacketTrailer) != std::string::npos);

}



TEST_F(SerializeAsRDFTest_2115, NormalOperation_ComactFormat_2115) {

    XMPMeta xmpObj;

    XMP_VarString headStr, tailStr;

    SerializeAsRDF(xmpObj, headStr, tailStr, kXMP_UseCompactFormat, "\n", "  ", 0);

    EXPECT_TRUE(headStr.find(kPacketHeader) != std::string::npos);

    EXPECT_TRUE(tailStr.find(kPacketTrailer) != std::string::npos);

}



TEST_F(SerializeAsRDFTest_2115, BoundaryCondition_EmptyXMPObject_2115) {

    XMPMeta xmpObj;

    XMP_VarString headStr, tailStr;

    SerializeAsRDF(xmpObj, headStr, tailStr, 0, "\n", "  ", 0);

    EXPECT_TRUE(headStr.find(kRDF_SchemaStart) != std::string::npos);

    EXPECT_TRUE(tailStr.find(kPacketTrailer) != std::string::npos);

}



TEST_F(SerializeAsRDFTest_2115, BoundaryCondition_BaseIndentZero_2115) {

    XMPMeta xmpObj;

    XMP_VarString headStr, tailStr;

    SerializeAsRDF(xmpObj, headStr, tailStr, 0, "\n", "  ", 0);

    EXPECT_TRUE(headStr.find(kPacketHeader) != std::string::npos);

}



TEST_F(SerializeAsRDFTest_2115, BoundaryCondition_BaseIndentNonZero_2115) {

    XMPMeta xmpObj;

    XMP_VarString headStr, tailStr;

    SerializeAsRDF(xmpObj, headStr, tailStr, 0, "\n", "  ", 2);

    EXPECT_TRUE(headStr.find("    <?xpacket begin") != std::string::npos);

}



TEST_F(SerializeAsRDFTest_2115, ExceptionalCase_OmitPacketWrapper_2115) {

    XMPMeta xmpObj;

    XMP_VarString headStr, tailStr;

    SerializeAsRDF(xmpObj, headStr, tailStr, kXMP_OmitPacketWrapper, "\n", "  ", 0);

    EXPECT_TRUE(headStr.find(kPacketHeader) == std::string::npos);

    EXPECT_TRUE(tailStr.find(kPacketTrailer) == std::string::npos);

}



TEST_F(SerializeAsRDFTest_2115, ExceptionalCase_OmitXMPMetaElement_2115) {

    XMPMeta xmpObj;

    XMP_VarString headStr, tailStr;

    SerializeAsRDF(xmpObj, headStr, tailStr, kXMP_OmitXMPMetaElement, "\n", "  ", 0);

    EXPECT_TRUE(headStr.find(kRDF_XMPMetaStart) == std::string::npos);

    EXPECT_TRUE(tailStr.find(kRDF_XMPMetaEnd) == std::string::npos);

}



TEST_F(SerializeAsRDFTest_2115, ExceptionalCase_ReadOnlyPacket_2115) {

    XMPMeta xmpObj;

    XMP_VarString headStr, tailStr;

    SerializeAsRDF(xmpObj, headStr, tailStr, kXMP_ReadOnlyPacket, "\n", "  ", 0);

    EXPECT_TRUE(tailStr.find("end=\"r\"?>") != std::string::npos);

}
