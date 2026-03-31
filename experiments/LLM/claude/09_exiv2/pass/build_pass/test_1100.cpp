#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

using namespace Exiv2;

class ImageFactoryCheckModeTest_1100 : public ::testing::Test {
protected:
};

// ==================== JPEG Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, JpegExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::jpeg, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, JpegIptcSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::jpeg, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, JpegXmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::jpeg, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, JpegCommentSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::jpeg, mdComment));
}

// ==================== EXV Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, ExvExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::exv, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, ExvIptcSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::exv, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, ExvXmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::exv, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, ExvCommentSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::exv, mdComment));
}

// ==================== CR2 Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, Cr2ExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::cr2, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, Cr2IptcSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::cr2, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, Cr2XmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::cr2, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, Cr2CommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::cr2, mdComment));
}

// ==================== CRW Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, CrwExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::crw, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, CrwIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::crw, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, CrwXmpSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::crw, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, CrwCommentSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::crw, mdComment));
}

// ==================== MRW Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, MrwExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::mrw, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, MrwIptcSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::mrw, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, MrwXmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::mrw, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, MrwCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::mrw, mdComment));
}

// ==================== TIFF Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, TiffExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::tiff, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, TiffIptcSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::tiff, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, TiffXmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::tiff, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, TiffCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::tiff, mdComment));
}

// ==================== WebP Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, WebPExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::webp, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, WebPIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::webp, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, WebPXmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::webp, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, WebPCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::webp, mdComment));
}

// ==================== PNG Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, PngExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::png, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, PngIptcSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::png, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, PngXmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::png, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, PngCommentSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::png, mdComment));
}

// ==================== GIF Tests (all amNone) ====================

TEST_F(ImageFactoryCheckModeTest_1100, GifExifSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::gif, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, GifIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::gif, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, GifXmpSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::gif, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, GifCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::gif, mdComment));
}

// ==================== PSD Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, PsdExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::psd, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, PsdIptcSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::psd, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, PsdXmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::psd, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, PsdCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::psd, mdComment));
}

// ==================== TGA Tests (all amNone) ====================

TEST_F(ImageFactoryCheckModeTest_1100, TgaExifSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::tga, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, TgaIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::tga, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, TgaXmpSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::tga, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, TgaCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::tga, mdComment));
}

// ==================== BMP Tests (all amNone) ====================

TEST_F(ImageFactoryCheckModeTest_1100, BmpExifSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::bmp, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, BmpIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::bmp, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, BmpXmpSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::bmp, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, BmpCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::bmp, mdComment));
}

// ==================== JP2 Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, Jp2ExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::jp2, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, Jp2IptcSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::jp2, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, Jp2XmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::jp2, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, Jp2CommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::jp2, mdComment));
}

// ==================== EPS Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, EpsExifSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::eps, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, EpsIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::eps, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, EpsXmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::eps, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, EpsCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::eps, mdComment));
}

// ==================== XMP Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, XmpExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::xmp, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, XmpIptcSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::xmp, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, XmpXmpSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::xmp, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, XmpCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::xmp, mdComment));
}

// ==================== ARW Tests (read-only) ====================

TEST_F(ImageFactoryCheckModeTest_1100, ArwExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::arw, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, ArwIptcSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::arw, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, ArwXmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::arw, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, ArwCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::arw, mdComment));
}

// ==================== RW2 Tests (read-only) ====================

TEST_F(ImageFactoryCheckModeTest_1100, Rw2ExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::rw2, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, Rw2IptcSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::rw2, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, Rw2XmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::rw2, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, Rw2CommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::rw2, mdComment));
}

// ==================== RAF Tests (read-only) ====================

TEST_F(ImageFactoryCheckModeTest_1100, RafExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::raf, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, RafIptcSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::raf, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, RafXmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::raf, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, RafCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::raf, mdComment));
}

// ==================== PGF Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, PgfExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::pgf, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, PgfCommentSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::pgf, mdComment));
}

// ==================== QTime Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, QTimeExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::qtime, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, QTimeIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::qtime, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, QTimeXmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::qtime, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, QTimeCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::qtime, mdComment));
}

// ==================== BMFF Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, BmffExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::bmff, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, BmffIptcSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::bmff, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, BmffXmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::bmff, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, BmffCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::bmff, mdComment));
}

// ==================== mdNone returns amNone ====================

TEST_F(ImageFactoryCheckModeTest_1100, JpegMdNoneReturnsAmNone_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::jpeg, mdNone));
}

TEST_F(ImageFactoryCheckModeTest_1100, TiffMdNoneReturnsAmNone_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::tiff, mdNone));
}

// ==================== mdIccProfile returns amNone (not handled) ====================

TEST_F(ImageFactoryCheckModeTest_1100, JpegMdIccProfileReturnsAmNone_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::jpeg, mdIccProfile));
}

// ==================== Unsupported/Invalid ImageType throws ====================

TEST_F(ImageFactoryCheckModeTest_1100, UnsupportedImageTypeThrows_1100) {
  // ImageType::none is not in the registry, should throw
  EXPECT_THROW(ImageFactory::checkMode(ImageType::none, mdExif), Exiv2::Error);
}

TEST_F(ImageFactoryCheckModeTest_1100, UnsupportedImageTypeThrowsCorrectError_1100) {
  try {
    ImageFactory::checkMode(ImageType::none, mdExif);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(ErrorCode::kerUnsupportedImageType, e.code());
  } catch (...) {
    FAIL() << "Expected Exiv2::Error but got a different exception";
  }
}

// ==================== DNG Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, DngExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::dng, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, DngCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::dng, mdComment));
}

// ==================== NEF Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, NefExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::nef, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, NefCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::nef, mdComment));
}

// ==================== PEF Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, PefExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::pef, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, PefCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::pef, mdComment));
}

// ==================== SR2 Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, Sr2ExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::sr2, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, Sr2CommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::sr2, mdComment));
}

// ==================== SRW Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, SrwExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::srw, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, SrwCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::srw, mdComment));
}

// ==================== ORF Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, OrfExifSupport_1100) {
  EXPECT_EQ(amReadWrite, ImageFactory::checkMode(ImageType::orf, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, OrfCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::orf, mdComment));
}

// ==================== ASF Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, AsfExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::asf, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, AsfIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::asf, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, AsfXmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::asf, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, AsfCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::asf, mdComment));
}

// ==================== RIFF Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, RiffExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::riff, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, RiffIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::riff, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, RiffXmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::riff, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, RiffCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::riff, mdComment));
}

// ==================== MKV Tests ====================

TEST_F(ImageFactoryCheckModeTest_1100, MkvExifSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::mkv, mdExif));
}

TEST_F(ImageFactoryCheckModeTest_1100, MkvIptcSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::mkv, mdIptc));
}

TEST_F(ImageFactoryCheckModeTest_1100, MkvXmpSupport_1100) {
  EXPECT_EQ(amRead, ImageFactory::checkMode(ImageType::mkv, mdXmp));
}

TEST_F(ImageFactoryCheckModeTest_1100, MkvCommentSupport_1100) {
  EXPECT_EQ(amNone, ImageFactory::checkMode(ImageType::mkv, mdComment));
}
