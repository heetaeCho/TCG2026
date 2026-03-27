#include <gtest/gtest.h>

#include "exiv2/exiv2.hpp"



using namespace Exiv2;



TEST(ExifDataTest, AddAndRetrieveTag) {

    ExifData exifData;

    ExifKey key("Exif.Image.Artist");

    Value::AutoPtr value = Value::createString(TypeAscii);

    value->read("John Doe");



    exifData.add(key, value.get());



    const Exifdatum& datum = *exifData.findKey(key);

    EXPECT_EQ(datum.toString(), "John Doe");

}



TEST(IptcDataTest, AddAndRetrieveTag) {

    IptcData iptcData;

    IptcKey key("Iptc.Application2.Caption");

    Value::AutoPtr value = Value::createString(TypeAscii);

    value->read("Sample Caption");



    iptcData.add(key, value.get());



    const Iptcdatum& datum = *iptcData.findKey(key);

    EXPECT_EQ(datum.toString(), "Sample Caption");

}



TEST(XmpDataTest, AddAndRetrieveTag) {

    XmpData xmpData;

    XmpKey key("Xmp.dc.creator");

    Value::AutoPtr value = Value::createString(TypeString);

    value->read("Jane Smith");



    xmpData.add(key, value.get());



    const Xmpdatum& datum = *xmpData.findKey(key);

    EXPECT_EQ(datum.toString(), "Jane Smith");

}



TEST(IfdIdTest, CheckEnumValues) {

    EXPECT_EQ(static_cast<int>(IfdId::ifd0Id), 1);

    EXPECT_EQ(static_cast<int>(IfdId::exifId), 5);

    EXPECT_EQ(static_cast<int>(IfdId::gpsId), 6);

    EXPECT_EQ(static_cast<int>(IfdId::iopId), 7);

    EXPECT_EQ(static_cast<int>(IfdId::subImage1Id), 9);

    EXPECT_EQ(static_cast<int>(IfdId::canonId), 21);

    EXPECT_EQ(static_cast<int>(IfdId::olympusId), 97);

}



TEST(TiffComponentTest, EncodeAndDecode) {

    // Mock implementation for TiffComponent, TiffEntryBase, and related classes

    // This is a simplified test to demonstrate structure



    class MockTiffEncoder : public Internal::TiffEncoder {

    public:

        void encode(const Internal::TiffEntryBase* entry) override {

            encoded = true;

        }

        bool encoded = false;

    };



    class MockExifdatum : public Exifdatum {

    public:

        MockExifdatum(ExifKey key, Value::AutoPtr value)

            : Exifdatum(key, value.get()) {}

    };



    Internal::TiffEntryBase entry(0x1234, IfdId::exifId, TiffType::tiffShort);

    MockTiffEncoder encoder;

    MockExifdatum datum("Exif.ExifIfd.SomeTag", Value::createString(TypeAscii));



    entry.encode(encoder, &datum);



    EXPECT_TRUE(encoder.encoded);

}



TEST(TiffVisitorTest, VisitEntry) {

    class MockTiffEntry : public Internal::TiffEntryBase {

    public:

        MockTiffEntry(uint16_t tag, IfdId group, TiffType tiffType)

            : TiffEntryBase(tag, group, tiffType) {}

    };



    class MockVisitor : public Internal::TiffVisitor {

    public:

        void visitEntry(Internal::TiffEntry* entry) override {

            visited = true;

        }

        bool visited = false;

    };



    MockTiffEntry entry(0x1234, IfdId::exifId, TiffType::tiffShort);

    MockVisitor visitor;



    visitor.visitEntry(&entry);



    EXPECT_TRUE(visitor.visited);

}



TEST(TiffFinderTest, FindObject) {

    class MockTiffEntry : public Internal::TiffEntryBase {

    public:

        MockTiffEntry(uint16_t tag, IfdId group, TiffType tiffType)

            : TiffEntryBase(tag, group, tiffType) {}

    };



    MockTiffEntry entry(0x1234, IfdId::exifId, TiffType::tiffShort);

    Internal::TiffFinder finder(0x1234, IfdId::exifId);



    finder.findObject(&entry);



    EXPECT_EQ(finder.result(), &entry);

}



TEST(TiffDecoderTest, DecodeXmp) {

    class MockXmpData : public XmpData {

    public:

        void add(const XmpKey& key, const Value* value) override {

            added = true;

        }

        bool added = false;

    };



    class MockTiffEntryBase : public Internal::TiffEntryBase {

    public:

        MockTiffEntryBase(uint16_t tag, IfdId group, TiffType tiffType)

            : TiffEntryBase(tag, group, tiffType) {}



        void setData(byte* pData, size_t size, std::shared_ptr<DataBuf> storage) override {

            this->pData_ = pData;

            this->count_ = size;

        }



    private:

        byte* pData_ = nullptr;

    };



    MockXmpData xmpData;

    MockTiffEntryBase entry(0x927C, IfdId::ifd1Id, TiffType::tiffUndefined);

    Internal::TiffDecoder decoder({}, xmpData, {}, nullptr, {});



    byte data[] = "<?xpacket begin='﻿' id='W5M0MpCehiHzreSzNTczkc9d'?>\n<x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='Image::ExifTool 12.34'>\n<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>\n<rdf:Description rdf:about='' xmlns:xmp='http://ns.adobe.com/xap/1.0/'/>\n</rdf:RDF>\n<?xpacket end='r'?>";

    entry.setData(data, sizeof(data), std::make_shared<DataBuf>());



    decoder.decodeXmp(&entry);



    EXPECT_TRUE(xmpData.added);

}
