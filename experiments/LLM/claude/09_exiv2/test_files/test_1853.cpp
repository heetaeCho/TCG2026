#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Test fixture for Converter tests using ExifData and XmpData
class ConverterTest_1853 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_ = Exiv2::ExifData();
        xmpData_ = Exiv2::XmpData();
        iptcData_ = Exiv2::IptcData();
    }

    Exiv2::ExifData exifData_;
    Exiv2::XmpData xmpData_;
    Exiv2::IptcData iptcData_;
};

// Test: writeExifDigest writes NativeDigest keys to XmpData
TEST_F(ConverterTest_1853, WriteExifDigest_SetsNativeDigestKeys_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.writeExifDigest();

    // Check that the NativeDigest keys exist in XmpData
    auto tiffDigest = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.NativeDigest"));
    auto exifDigest = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.NativeDigest"));

    EXPECT_NE(tiffDigest, xmpData_.end()) << "Xmp.tiff.NativeDigest should be set";
    EXPECT_NE(exifDigest, xmpData_.end()) << "Xmp.exif.NativeDigest should be set";

    // The digest strings should not be empty
    if (tiffDigest != xmpData_.end()) {
        EXPECT_FALSE(tiffDigest->toString().empty());
    }
    if (exifDigest != xmpData_.end()) {
        EXPECT_FALSE(exifDigest->toString().empty());
    }
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: writeExifDigest with empty ExifData still produces digests
TEST_F(ConverterTest_1853, WriteExifDigest_EmptyExifData_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.writeExifDigest();

    auto tiffDigest = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.NativeDigest"));
    auto exifDigest = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.NativeDigest"));

    EXPECT_NE(tiffDigest, xmpData_.end());
    EXPECT_NE(exifDigest, xmpData_.end());
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: writeExifDigest with populated ExifData
TEST_F(ConverterTest_1853, WriteExifDigest_WithExifData_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    // Add some EXIF data
    exifData_["Exif.Image.Make"] = "TestCamera";
    exifData_["Exif.Image.Model"] = "TestModel";
    exifData_["Exif.Photo.ExposureTime"] = "1/100";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.writeExifDigest();

    auto tiffDigest = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.NativeDigest"));
    auto exifDigest = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.NativeDigest"));

    EXPECT_NE(tiffDigest, xmpData_.end());
    EXPECT_NE(exifDigest, xmpData_.end());
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: writeExifDigest produces different digests for different ExifData
TEST_F(ConverterTest_1853, WriteExifDigest_DifferentDataDifferentDigests_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    // First: empty exif data
    Exiv2::Converter converter1(exifData_, xmpData_);
    converter1.writeExifDigest();

    auto tiffDigest1 = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.NativeDigest"));
    auto exifDigest1 = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.NativeDigest"));
    std::string tiffStr1, exifStr1;
    if (tiffDigest1 != xmpData_.end()) tiffStr1 = tiffDigest1->toString();
    if (exifDigest1 != xmpData_.end()) exifStr1 = exifDigest1->toString();

    // Second: with some exif data
    Exiv2::ExifData exifData2;
    Exiv2::XmpData xmpData2;
    exifData2["Exif.Image.Make"] = "DifferentCamera";
    exifData2["Exif.Image.Model"] = "DifferentModel";

    Exiv2::Converter converter2(exifData2, xmpData2);
    converter2.writeExifDigest();

    auto tiffDigest2 = xmpData2.findKey(Exiv2::XmpKey("Xmp.tiff.NativeDigest"));
    auto exifDigest2 = xmpData2.findKey(Exiv2::XmpKey("Xmp.exif.NativeDigest"));
    std::string tiffStr2, exifStr2;
    if (tiffDigest2 != xmpData2.end()) tiffStr2 = tiffDigest2->toString();
    if (exifDigest2 != xmpData2.end()) exifStr2 = exifDigest2->toString();

    // The digests should differ when the underlying data differs
    // (at least one of them should differ)
    bool atLeastOneDiffers = (tiffStr1 != tiffStr2) || (exifStr1 != exifStr2);
    EXPECT_TRUE(atLeastOneDiffers) << "Digests should differ for different EXIF data";
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: writeExifDigest called twice overwrites previous digest
TEST_F(ConverterTest_1853, WriteExifDigest_CalledTwiceOverwrites_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.writeExifDigest();

    auto tiffDigest1 = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.NativeDigest"));
    std::string tiffStr1;
    if (tiffDigest1 != xmpData_.end()) tiffStr1 = tiffDigest1->toString();

    // Call again with the same data
    converter.writeExifDigest();

    auto tiffDigest2 = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.NativeDigest"));
    std::string tiffStr2;
    if (tiffDigest2 != xmpData_.end()) tiffStr2 = tiffDigest2->toString();

    // Should produce the same digest for the same data
    EXPECT_EQ(tiffStr1, tiffStr2);
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: Converter construction with ExifData and XmpData
TEST_F(ConverterTest_1853, ConstructorExifXmp_1853) {
    EXPECT_NO_THROW({
        Exiv2::Converter converter(exifData_, xmpData_);
    });
}

// Test: Converter construction with IptcData and XmpData
TEST_F(ConverterTest_1853, ConstructorIptcXmp_1853) {
    EXPECT_NO_THROW({
        Exiv2::Converter converter(iptcData_, xmpData_, nullptr);
    });
}

// Test: setErase and erase
TEST_F(ConverterTest_1853, SetEraseAndErase_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);

    // Default should be false
    EXPECT_FALSE(converter.erase());

    converter.setErase(true);
    EXPECT_TRUE(converter.erase());

    converter.setErase(false);
    EXPECT_FALSE(converter.erase());
}

// Test: setErase default parameter
TEST_F(ConverterTest_1853, SetEraseDefaultParam_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);

    converter.setErase(); // default is true
    EXPECT_TRUE(converter.erase());
}

// Test: cnvToXmp with empty data
TEST_F(ConverterTest_1853, CnvToXmpEmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvToXmp());
}

// Test: cnvFromXmp with empty data
TEST_F(ConverterTest_1853, CnvFromXmpEmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvFromXmp());
}

// Test: cnvToXmp converts Exif to XMP
TEST_F(ConverterTest_1853, CnvToXmpConvertsData_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    exifData_["Exif.Image.Make"] = "TestMake";
    exifData_["Exif.Image.Model"] = "TestModel";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvToXmp();

    // After conversion, XMP data should contain corresponding entries
    auto make = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    auto model = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Model"));

    EXPECT_NE(make, xmpData_.end());
    EXPECT_NE(model, xmpData_.end());

    if (make != xmpData_.end()) {
        EXPECT_EQ(make->toString(), "TestMake");
    }
    if (model != xmpData_.end()) {
        EXPECT_EQ(model->toString(), "TestModel");
    }
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: cnvFromXmp converts XMP to Exif
TEST_F(ConverterTest_1853, CnvFromXmpConvertsData_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    xmpData_["Xmp.tiff.Make"] = "XmpMake";
    xmpData_["Xmp.tiff.Model"] = "XmpModel";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvFromXmp();

    auto make = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    auto model = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));

    EXPECT_NE(make, exifData_.end());
    EXPECT_NE(model, exifData_.end());
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: cnvNone does nothing
TEST_F(ConverterTest_1853, CnvNone_DoesNothing_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvNone("Exif.Image.Make", "Xmp.tiff.Make"));
    EXPECT_TRUE(xmpData_.empty());
}

// Test: syncExifWithXmp with empty data
TEST_F(ConverterTest_1853, SyncExifWithXmp_EmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.syncExifWithXmp());
}

// Test: syncExifWithXmp with populated data
TEST_F(ConverterTest_1853, SyncExifWithXmp_PopulatedData_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    xmpData_["Xmp.tiff.Make"] = "SyncMake";

    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.syncExifWithXmp());
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: setOverwrite controls overwrite behavior
TEST_F(ConverterTest_1853, SetOverwrite_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    exifData_["Exif.Image.Make"] = "OriginalMake";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvToXmp();

    // Now change exif and convert again with overwrite = false
    exifData_["Exif.Image.Make"] = "NewMake";
    converter.setOverwrite(false);
    converter.cnvToXmp();

    auto make = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    if (make != xmpData_.end()) {
        // With overwrite=false, the original value should remain
        EXPECT_EQ(make->toString(), "OriginalMake");
    }
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: setOverwrite true allows overwriting
TEST_F(ConverterTest_1853, SetOverwriteTrue_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    exifData_["Exif.Image.Make"] = "OriginalMake";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvToXmp();

    // Now change exif and convert again with overwrite = true (default)
    exifData_["Exif.Image.Make"] = "NewMake";
    converter.setOverwrite(true);
    converter.cnvToXmp();

    auto make = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
    if (make != xmpData_.end()) {
        EXPECT_EQ(make->toString(), "NewMake");
    }
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: IPTC to XMP conversion with empty data
TEST_F(ConverterTest_1853, IptcCnvToXmp_EmptyData_1853) {
    Exiv2::Converter converter(iptcData_, xmpData_, nullptr);
    EXPECT_NO_THROW(converter.cnvToXmp());
}

// Test: IPTC from XMP conversion with empty data
TEST_F(ConverterTest_1853, IptcCnvFromXmp_EmptyData_1853) {
    Exiv2::Converter converter(iptcData_, xmpData_, nullptr);
    EXPECT_NO_THROW(converter.cnvFromXmp());
}

// Test: cnvExifValue with nonexistent key does not crash
TEST_F(ConverterTest_1853, CnvExifValue_NonexistentKey_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make"));
    // Since there's no Exif.Image.Make in exifData_, xmpData_ should remain empty
    EXPECT_TRUE(xmpData_.empty());
}

// Test: cnvXmpValue with nonexistent key does not crash
TEST_F(ConverterTest_1853, CnvXmpValue_NonexistentKey_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvXmpValue("Xmp.tiff.Make", "Exif.Image.Make"));
    EXPECT_TRUE(exifData_.empty());
}

// Test: writeExifDigest with pre-existing digest entries in XmpData
TEST_F(ConverterTest_1853, WriteExifDigest_OverwritesExisting_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    // Pre-populate with some dummy digest values
    xmpData_["Xmp.tiff.NativeDigest"] = "dummy_tiff_digest";
    xmpData_["Xmp.exif.NativeDigest"] = "dummy_exif_digest";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.writeExifDigest();

    auto tiffDigest = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.NativeDigest"));
    auto exifDigest = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.NativeDigest"));

    ASSERT_NE(tiffDigest, xmpData_.end());
    ASSERT_NE(exifDigest, xmpData_.end());

    // The values should have been overwritten (not the dummy values)
    EXPECT_NE(tiffDigest->toString(), "dummy_tiff_digest");
    EXPECT_NE(exifDigest->toString(), "dummy_exif_digest");
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: cnvExifDate with empty data
TEST_F(ConverterTest_1853, CnvExifDate_EmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvExifDate("Exif.Photo.DateTimeOriginal", "Xmp.photoshop.DateCreated"));
}

// Test: cnvExifVersion with empty data
TEST_F(ConverterTest_1853, CnvExifVersion_EmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvExifVersion("Exif.Photo.ExifVersion", "Xmp.exif.ExifVersion"));
}

// Test: cnvExifFlash with empty data
TEST_F(ConverterTest_1853, CnvExifFlash_EmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvExifFlash("Exif.Photo.Flash", "Xmp.exif.Flash"));
}

// Test: cnvExifGPSCoord with empty data
TEST_F(ConverterTest_1853, CnvExifGPSCoord_EmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude"));
}

// Test: cnvExifGPSVersion with empty data
TEST_F(ConverterTest_1853, CnvExifGPSVersion_EmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.exif.GPSVersionID"));
}

// Test: cnvExifComment with empty data
TEST_F(ConverterTest_1853, CnvExifComment_EmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvExifComment("Exif.Photo.UserComment", "Xmp.exif.UserComment"));
}

// Test: cnvExifArray with empty data
TEST_F(ConverterTest_1853, CnvExifArray_EmptyData_1853) {
    Exiv2::Converter converter(exifData_, xmpData_);
    EXPECT_NO_THROW(converter.cnvExifArray("Exif.Image.BitsPerSample", "Xmp.tiff.BitsPerSample"));
}

// Test: Round-trip conversion ExifData -> XmpData -> ExifData
TEST_F(ConverterTest_1853, RoundTripConversion_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    exifData_["Exif.Image.Make"] = "RoundTripMake";

    Exiv2::Converter toXmp(exifData_, xmpData_);
    toXmp.cnvToXmp();

    // Clear exif and convert back
    Exiv2::ExifData exifData2;
    Exiv2::Converter fromXmp(exifData2, xmpData_);
    fromXmp.cnvFromXmp();

    auto make = exifData2.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(make, exifData2.end());
    if (make != exifData2.end()) {
        EXPECT_EQ(make->toString(), "RoundTripMake");
    }
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}

// Test: setErase causes source data to be erased during conversion
TEST_F(ConverterTest_1853, SetErase_RemovesSourceData_1853) {
#ifdef EXV_HAVE_XMP_TOOLKIT
    exifData_["Exif.Image.Make"] = "EraseMake";

    Exiv2::Converter converter(exifData_, xmpData_);
    converter.setErase(true);
    converter.cnvToXmp();

    // After conversion with erase, the exif entry should be removed
    auto make = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_EQ(make, exifData_.end()) << "Source EXIF data should be erased after cnvToXmp with setErase(true)";
#else
    GTEST_SKIP() << "XMP toolkit not available";
#endif
}
