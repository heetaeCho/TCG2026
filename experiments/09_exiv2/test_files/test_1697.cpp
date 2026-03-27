#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 { namespace Internal {



class MockTiffDataEntry : public TiffDataEntry {

public:

    MOCK_METHOD(void, setStrips, (const Value * pSize, const byte * pData, size_t sizeData, size_t baseOffset), (override));

    MOCK_METHOD(void, doAccept, (TiffVisitor & visitor), (override));

    MOCK_METHOD(void, doEncode, (TiffEncoder & encoder, const Exifdatum* datum), (override));

    MOCK_METHOD(size_t, doWrite, (IoWrapper & ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t & imageIdx), (override));

    MOCK_METHOD(const TiffDataEntry *, doClone, (), (const, override));

    MOCK_METHOD(const size_t, doWriteData, (IoWrapper & ioWrapper, ByteOrder byteOrder, size_t offset, size_t dataIdx, size_t & imageIdx), (const, override));

    MOCK_METHOD(const size_t, doSizeData, (), (const, override));

};



class TiffReaderTest_1697 : public ::testing::Test {

protected:

    MockTiffDataEntry mockDataEntry;

    byte testData[1024];

    TiffReader reader{testData, sizeof(testData), nullptr, TiffRwState()};

};



TEST_F(TiffReaderTest_1697, VisitDataEntryCallsReadDataEntryBase_1697) {

    EXPECT_CALL(mockDataEntry, doAccept(::testing::_)).WillOnce([this](TiffVisitor& visitor){

        visitor.readDataEntryBase(&mockDataEntry);

    });



    reader.visitDataEntry(&mockDataEntry);

}



TEST_F(TiffReaderTest_1697, VisitDataEntryWithNullObjectDoesNotCrash_1697) {

    EXPECT_NO_THROW(reader.visitDataEntry(nullptr));

}



}} // namespace Exiv2::Internal
