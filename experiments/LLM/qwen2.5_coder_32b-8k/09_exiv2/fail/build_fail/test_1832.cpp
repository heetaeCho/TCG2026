#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

    class Converter { 

        private:

            bool erase_ = {false};

            bool overwrite_ = {true};

            ExifData * exifData_;

            IptcData * iptcData_;

            XmpData * xmpData_;

            const char * iptcCharset_;



        public:  

            Converter (ExifData & exifData, XmpData & xmpData);

            Converter (IptcData & iptcData, XmpData & xmpData, const char * iptcCharset);



            void cnvToXmp ();

            void cnvFromXmp ();

            void cnvNone (const char * unnamed, const char * unnamed);

            void cnvExifValue (const char * from, const char * to);

            void cnvExifComment (const char * from, const char * to);

            void cnvExifArray (const char * from, const char * to);

            void cnvExifDate (const char * from, const char * to);

            void cnvExifVersion (const char * from, const char * to);

            void cnvExifGPSVersion (const char * from, const char * to);

            void cnvExifFlash (const char * from, const char * to);

            void cnvExifGPSCoord (const char * from, const char * to);

            void cnvXmpValue (const char * from, const char * to);

            void cnvXmpComment (const char * from, const char * to);

            void cnvXmpArray (const char * from, const char * to);

            void cnvXmpDate (const char * from, const char * to);

            void cnvXmpVersion (const char * from, const char * to);

            void cnvXmpGPSVersion (const char * from, const char * to);

            void cnvXmpFlash (const char * from, const char * to);

            void cnvXmpGPSCoord (const char * from, const char * to);

            void cnvIptcValue (const char * from, const char * to);

            void cnvXmpValueToIptc (const char * from, const char * to);

            void writeExifDigest ();

            void syncExifWithXmp ();



            void setErase(bool onoff = true);

            bool erase() const;

    };

}



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



class MockIptcData : public Exiv2::IptcData {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



class MockXmpData : public Exiv2::XmpData {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



using namespace testing;



TEST(ConverterTest_1832, DefaultEraseValueIsFalse_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);

    

    EXPECT_FALSE(converter.erase());

}



TEST(ConverterTest_1832, SetEraseTrueAndGetTrue_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);

    

    converter.setErase(true);

    EXPECT_TRUE(converter.erase());

}



TEST(ConverterTest_1832, SetEraseFalseAndGetFalse_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);

    

    converter.setErase(false);

    EXPECT_FALSE(converter.erase());

}



TEST(ConverterTest_1832, IptcConstructorInitializesCorrectly_1832) {

    MockIptcData iptcData;

    MockXmpData xmpData;

    Exiv2::Converter converter(iptcData, xmpData, "charset");

    

    EXPECT_EQ(converter.erase(), false);

}



TEST(ConverterTest_1832, ExifConstructorInitializesCorrectly_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);

    

    EXPECT_EQ(converter.erase(), false);

}



TEST(ConverterTest_1832, CnvNoneDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvNone("from", "to"));

}



TEST(ConverterTest_1832, CnvExifValueDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvExifValue("from", "to"));

}



TEST(ConverterTest_1832, CnvExifCommentDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvExifComment("from", "to"));

}



TEST(ConverterTest_1832, CnvExifArrayDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvExifArray("from", "to"));

}



TEST(ConverterTest_1832, CnvExifDateDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvExifDate("from", "to"));

}



TEST(ConverterTest_1832, CnvExifVersionDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvExifVersion("from", "to"));

}



TEST(ConverterTest_1832, CnvExifGPSVersionDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvExifGPSVersion("from", "to"));

}



TEST(ConverterTest_1832, CnvExifFlashDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvExifFlash("from", "to"));

}



TEST(ConverterTest_1832, CnvExifGPSCoordDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvExifGPSCoord("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpValueDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpValue("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpCommentDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpComment("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpArrayDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpArray("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpDateDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpDate("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpVersionDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpVersion("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpGPSVersionDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpGPSVersion("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpFlashDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpFlash("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpGPSCoordDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpGPSCoord("from", "to"));

}



TEST(ConverterTest_1832, CnvIptcValueDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvIptcValue("from", "to"));

}



TEST(ConverterTest_1832, CnvXmpValueToIptcDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.cnvXmpValueToIptc("from", "to"));

}



TEST(ConverterTest_1832, WriteExifDigestDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.writeExifDigest());

}



TEST(ConverterTest_1832, SyncExifWithXmpDoesNotThrow_1832) {

    MockExifData exifData;

    MockXmpData xmpData;

    Exiv2::Converter converter(exifData, xmpData);



    EXPECT_NO_THROW(converter.syncExifWithXmp());

}
