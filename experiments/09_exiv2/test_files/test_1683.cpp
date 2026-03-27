#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



// Mocking TiffEntry for testing purposes

class MockTiffEntry : public TiffEntry {

public:

    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), override);

    MOCK_METHOD(void, doEncode, (TiffEncoder& encoder, const Exifdatum* datum), override);

    MOCK_METHOD(const TiffEntry*, doClone, (), const, override);

};



// Mocking Exifdatum for testing purposes

class MockExifdatum : public Exifdatum {

public:

    using Exifdatum::Exifdatum;

    MOCK_METHOD(void, setValue, (const Value* pValue), (override));

    MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

    MOCK_METHOD(std::string, key, (), (const, override));

    MOCK_METHOD(const char*, familyName, (), (const, override));

    MOCK_METHOD(std::string, groupName, (), (const, override));

    MOCK_METHOD(std::string, tagName, (), (const, override));

    MOCK_METHOD(std::string, tagLabel, (), (const, override));

    MOCK_METHOD(std::string, tagDesc, (), (const, override));

    MOCK_METHOD(uint16_t, tag, (), (const, override));

    MOCK_METHOD(IfdId, ifdId, (), (const, override));

    MOCK_METHOD(const char*, ifdName, (), (const, override));

    MOCK_METHOD(int, idx, (), (const, override));

    MOCK_METHOD(size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(TypeId, typeId, (), (const, override));

    MOCK_METHOD(const char*, typeName, (), (const, override));

    MOCK_METHOD(size_t, typeSize, (), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(std::string, toString, (), (const, override));

    MOCK_METHOD(std::string, toString, (size_t n), (const, override));

    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));

    MOCK_METHOD(float, toFloat, (size_t n), (const, override));

    MOCK_METHOD(Rational, toRational, (size_t n), (const, override));

    MOCK_METHOD(Value::UniquePtr, getValue, (), (const, override));

    MOCK_METHOD(const Value&, value, (), (const, override));

    MOCK_METHOD(size_t, sizeDataArea, (), (const, override));

    MOCK_METHOD(DataBuf, dataArea, (), (const, override));

};



class TiffEncoderTest_1683 : public ::testing::Test {

protected:

    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    MockTiffEntry mockTiffEntry_;

    MockExifdatum mockExifdatum_;

    ByteOrder byteOrder_ = littleEndian;

    PrimaryGroups primaryGroups_{};

    TiffHeaderBase header_{byteOrder_};



    TiffEncoder encoder_{exifData_, iptcData_, xmpData_, nullptr, false, primaryGroups_, &header_, nullptr};

};



TEST_F(TiffEncoderTest_1683, EncodeTiffEntry_NormalOperation_1683) {

    EXPECT_CALL(mockTiffEntry_, doEncode(::testing::Ref(encoder_), ::testing::Ref(mockExifdatum_)))

        .Times(1);



    encoder_.encodeTiffEntry(&mockTiffEntry_, &mockExifdatum_);

}



TEST_F(TiffEncoderTest_1683, EncodeTiffEntry_NullTiffEntry_1683) {

    EXPECT_THROW(encoder_.encodeTiffEntry(nullptr, &mockExifdatum_), std::invalid_argument);

}



TEST_F(TiffEncoderTest_1683, EncodeTiffEntry_NullExifdatum_1683) {

    EXPECT_THROW(encoder_.encodeTiffEntry(&mockTiffEntry_, nullptr), std::invalid_argument);

}
