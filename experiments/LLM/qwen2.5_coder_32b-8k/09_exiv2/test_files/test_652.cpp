#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using testing::Return;



// Mocking TypeInfo and IptcDataSets for external interactions

class MockTypeInfo : public TypeInfo {

public:

    MOCK_STATIC_METHOD1(typeName, const char*(TypeId));

};



class MockIptcDataSets : public IptcDataSets {

public:

    MOCK_STATIC_METHOD2(dataSetType, TypeId(uint16_t, uint16_t));

    MOCK_STATIC_METHOD2(recordName, std::string(uint16_t, uint16_t));

    MOCK_STATIC_METHOD2(dataSetDesc, const char*(uint16_t, uint16_t));

};



TEST_F(DataSetTest_652, NormalOperation_652) {

    MockTypeInfo mockTypeInfo;

    MockIptcDataSets mockIptcDataSets;



    DataSet dataSet = {0x8397, "ObjectName", true, false, 0, 255, TypeId::asciiString, nullptr};



    EXPECT_CALL(mockIptcDataSets, dataSetType(0x8397, 0))

            .WillOnce(Return(TypeId::asciiString));

    EXPECT_CALL(mockIptcDataSets, recordName(0, 0))

            .WillOnce(Return("Envelope Record"));

    EXPECT_CALL(mockTypeInfo, typeName(TypeId::asciiString))

            .WillOnce(Return("Ascii String"));

    EXPECT_CALL(mockIptcDataSets, dataSetDesc(0x8397, 0))

            .WillOnce(Return("\"The ObjectName tag is used to describe the subject of the image.\""));



    std::ostringstream os;

    os << dataSet;



    EXPECT_EQ(os.str(), "ObjectName, 0x8397, 0x8397, Envelope Record, true, false, 0, 255, Iptc.Envelope.ObjectName, Ascii String, \"\"The ObjectName tag is used to describe the subject of the image.\"\"");

}



TEST_F(DataSetTest_652, BoundaryCondition_EmptyDescription_652) {

    MockTypeInfo mockTypeInfo;

    MockIptcDataSets mockIptcDataSets;



    DataSet dataSet = {0x8397, "ObjectName", true, false, 0, 255, TypeId::asciiString, nullptr};



    EXPECT_CALL(mockIptcDataSets, dataSetType(0x8397, 0))

            .WillOnce(Return(TypeId::asciiString));

    EXPECT_CALL(mockIptcDataSets, recordName(0, 0))

            .WillOnce(Return("Envelope Record"));

    EXPECT_CALL(mockTypeInfo, typeName(TypeId::asciiString))

            .WillOnce(Return("Ascii String"));

    EXPECT_CALL(mockIptcDataSets, dataSetDesc(0x8397, 0))

            .WillOnce(Return(""));



    std::ostringstream os;

    os << dataSet;



    EXPECT_EQ(os.str(), "ObjectName, 0x8397, 0x8397, Envelope Record, true, false, 0, 255, Iptc.Envelope.ObjectName, Ascii String, \"\"");

}



TEST_F(DataSetTest_652, ExceptionalCase_EmptyRecordName_652) {

    MockTypeInfo mockTypeInfo;

    MockIptcDataSets mockIptcDataSets;



    DataSet dataSet = {0x8397, "ObjectName", true, false, 0, 255, TypeId::asciiString, nullptr};



    EXPECT_CALL(mockIptcDataSets, dataSetType(0x8397, 0))

            .WillOnce(Return(TypeId::asciiString));

    EXPECT_CALL(mockIptcDataSets, recordName(0, 0))

            .WillOnce(Return(""));

    EXPECT_CALL(mockTypeInfo, typeName(TypeId::asciiString))

            .WillOnce(Return("Ascii String"));

    EXPECT_CALL(mockIptcDataSets, dataSetDesc(0x8397, 0))

            .WillOnce(Return("\"The ObjectName tag is used to describe the subject of the image.\""));



    std::ostringstream os;

    os << dataSet;



    EXPECT_EQ(os.str(), "ObjectName, 0x8397, 0x8397, , true, false, 0, 255, Iptc.Envelope.ObjectName, Ascii String, \"\"The ObjectName tag is used to describe the subject of the image.\"\"");

}



TEST_F(DataSetTest_652, VerificationOfExternalInteractions_652) {

    MockTypeInfo mockTypeInfo;

    MockIptcDataSets mockIptcDataSets;



    DataSet dataSet = {0x8397, "ObjectName", true, false, 0, 255, TypeId::asciiString, nullptr};



    EXPECT_CALL(mockIptcDataSets, dataSetType(0x8397, 0))

            .WillOnce(Return(TypeId::asciiString));

    EXPECT_CALL(mockIptcDataSets, recordName(0, 0))

            .WillOnce(Return("Envelope Record"));

    EXPECT_CALL(mockTypeInfo, typeName(TypeId::asciiString))

            .WillOnce(Return("Ascii String"));

    EXPECT_CALL(mockIptcDataSets, dataSetDesc(0x8397, 0))

            .WillOnce(Return("\"The ObjectName tag is used to describe the subject of the image.\""));



    std::ostringstream os;

    os << dataSet;



    // No assertions on os.str() here as we are verifying interactions

}
