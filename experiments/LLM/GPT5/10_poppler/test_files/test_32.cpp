// SPDX-License-Identifier: GPL-2.0-or-later
// File: ft_utils_test_32.cc
//
// Unit tests for: ft_new_face_from_file
// Source under test: ./TestProjects/poppler/goo/ft_utils.cc
//
// NOTE:
// - These tests treat the implementation as a black box.
// - External collaborators (FreeType entry points and openFile) are replaced with
//   test doubles via link-time symbol overriding in this test TU.

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>

#if __has_include(<ft2build.h>)
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_ERRORS_H
#else
// Fallback minimal FreeType type declarations (only if headers are unavailable).
// This is only to allow the test to compile; in a real build, FreeType headers should exist.
using FT_Error = int;
using FT_Long = long;
struct FT_LibraryRec_;
using FT_Library = FT_LibraryRec_*;
struct FT_FaceRec_;
using FT_Face = FT_FaceRec_*;
struct FT_StreamRec_;
using FT_Stream = FT_StreamRec_*;
struct FT_Open_Args_;
using FT_Open_Args = FT_Open_Args_;
#ifndef FT_OPEN_STREAM
#define FT_OPEN_STREAM 0x2
#endif
#ifndef FT_Err_Invalid_Argument
#define FT_Err_Invalid_Argument 0x06
#endif
#ifndef FT_Err_Cannot_Open_Resource
#define FT_Err_Cannot_Open_Resource 0x01
#endif
#ifndef FT_Err_Cannot_Open_Stream
#define FT_Err_Cannot_Open_Stream 0x02
#endif
#endif

// Prefer including a header if it exists; otherwise forward-declare.
#if __has_include("goo/ft_utils.h")
#include "goo/ft_utils.h"
#elif __has_include("./TestProjects/poppler/goo/ft_utils.h")
#include "./TestProjects/poppler/goo/ft_utils.h"
#else
FT_Error ft_new_face_from_file(FT_Library library, const char* filename_utf8, FT_Long face_index, FT_Face* aface);
#endif

namespace {

// --------- Test doubles / call recording for external collaborators ----------

struct FtNewFaceCall {
  bool called = false;
  FT_Library library = nullptr;
  const char* filename = nullptr;
  FT_Long face_index = 0;
  FT_Face* aface = nullptr;
  FT_Error ret = 0;
  int call_count = 0;
};

struct FtOpenFaceCall {
  bool called = false;
  FT_Library library = nullptr;
  const FT_Open_Args* args = nullptr;
  FT_Long face_index = 0;
  FT_Face* aface = nullptr;
  FT_Error ret = 0;
  int call_count = 0;

  // Minimal observable bits (safe to check: they are part of the public FT_Open_Args).
  unsigned long flags = 0;
  void* stream_ptr = nullptr;
};

struct OpenFileCall {
  bool called = false;
  std::string filename;
  std::string mode;
  int call_count = 0;
  FILE* ret_file = nullptr;
};

FtNewFaceCall g_newFace;
FtOpenFaceCall g_openFace;
OpenFileCall g_openFile;

void ResetDoubles() {
  g_newFace = FtNewFaceCall{};
  g_openFace = FtOpenFaceCall{};
  g_openFile = OpenFileCall{};
}

std::string MakeTempFileWithBytes(const std::string& bytes) {
  // Simple, portable-ish temp filename creation.
  // (We don't rely on OS-specific mkstemp to keep this file self-contained.)
  // Collisions are very unlikely in typical CI because PID/time differ, but still possible;
  // if that happens, the test will fail and should be adjusted for that environment.
  const std::string base = "ft_utils_test_32_tmp_";
  const auto stamp = std::to_string(reinterpret_cast<uintptr_t>(&g_newFace));
  const std::string path = base + stamp + ".bin";

  std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
  ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  ofs.close();
  return path;
}

}  // namespace

// --------- Symbol overrides (link-time seams) ----------
// These replace the real functions during unit test linking.

// FreeType API: non-Windows path calls FT_New_Face.
extern "C" FT_Error FT_New_Face(FT_Library library, const char* filepathname, FT_Long face_index, FT_Face* aface) {
  g_newFace.called = true;
  g_newFace.call_count++;
  g_newFace.library = library;
  g_newFace.filename = filepathname;
  g_newFace.face_index = face_index;
  g_newFace.aface = aface;
  return g_newFace.ret;
}

#ifdef _WIN32
// poppler's Windows path calls openFile and FT_Open_Face.

// openFile is a poppler utility; override it.
extern "C" FILE* openFile(const char* fileName, const char* mode) {
  g_openFile.called = true;
  g_openFile.call_count++;
  g_openFile.filename = fileName ? fileName : "";
  g_openFile.mode = mode ? mode : "";
  return g_openFile.ret_file;
}

// FreeType API: Windows path calls FT_Open_Face with FT_OPEN_STREAM.
extern "C" FT_Error FT_Open_Face(FT_Library library, const FT_Open_Args* args, FT_Long face_index, FT_Face* aface) {
  g_openFace.called = true;
  g_openFace.call_count++;
  g_openFace.library = library;
  g_openFace.args = args;
  g_openFace.face_index = face_index;
  g_openFace.aface = aface;
  if (args) {
    g_openFace.flags = args->flags;
    // FT_Open_Args::stream exists when FT_OPEN_STREAM is set.
    // Store as void* for simple observability.
    g_openFace.stream_ptr = reinterpret_cast<void*>(args->stream);
  }
  return g_openFace.ret;
}
#endif  // _WIN32

// ------------------------------ Tests --------------------------------

class FtNewFaceFromFileTest_32 : public ::testing::Test {
 protected:
  void SetUp() override { ResetDoubles(); }
  void TearDown() override { ResetDoubles(); }
};

#ifndef _WIN32

TEST_F(FtNewFaceFromFileTest_32, ForwardsParametersToFT_New_Face_32) {
  g_newFace.ret = static_cast<FT_Error>(123);  // arbitrary sentinel

  FT_Library lib = reinterpret_cast<FT_Library>(0x1111);
  FT_Face outFace = nullptr;
  FT_Face* outFacePtr = &outFace;

  const char* filename = "some_font.ttf";
  FT_Long faceIndex = 7;

  FT_Error rc = ft_new_face_from_file(lib, filename, faceIndex, outFacePtr);

  EXPECT_EQ(rc, static_cast<FT_Error>(123));
  EXPECT_TRUE(g_newFace.called);
  EXPECT_EQ(g_newFace.call_count, 1);
  EXPECT_EQ(g_newFace.library, lib);
  EXPECT_EQ(g_newFace.filename, filename);
  EXPECT_EQ(g_newFace.face_index, faceIndex);
  EXPECT_EQ(g_newFace.aface, outFacePtr);
}

TEST_F(FtNewFaceFromFileTest_32, PropagatesErrorFromFT_New_Face_32) {
  g_newFace.ret = static_cast<FT_Error>(-7);  // arbitrary error sentinel

  FT_Library lib = reinterpret_cast<FT_Library>(0x2222);
  FT_Face outFace = nullptr;

  FT_Error rc = ft_new_face_from_file(lib, "bad_font.ttf", 0, &outFace);

  EXPECT_EQ(rc, static_cast<FT_Error>(-7));
  EXPECT_TRUE(g_newFace.called);
  EXPECT_EQ(g_newFace.call_count, 1);
}

TEST_F(FtNewFaceFromFileTest_32, AllowsNullFilenameAndForwardsIt_32) {
  // The wrapper behavior is observable only via forwarding + return value.
  g_newFace.ret = static_cast<FT_Error>(42);

  FT_Library lib = reinterpret_cast<FT_Library>(0x3333);
  FT_Face outFace = nullptr;

  FT_Error rc = ft_new_face_from_file(lib, nullptr, 0, &outFace);

  EXPECT_EQ(rc, static_cast<FT_Error>(42));
  EXPECT_TRUE(g_newFace.called);
  EXPECT_EQ(g_newFace.call_count, 1);
  EXPECT_EQ(g_newFace.filename, nullptr);
}

TEST_F(FtNewFaceFromFileTest_32, ForwardsBoundaryFaceIndexValues_32) {
  g_newFace.ret = static_cast<FT_Error>(0);

  FT_Library lib = reinterpret_cast<FT_Library>(0x4444);
  FT_Face outFace = nullptr;

  // Boundary-ish: negative and large positive (still within FT_Long).
  const FT_Long indices[] = {0, -1, 1, static_cast<FT_Long>(2147483647L)};

  for (FT_Long idx : indices) {
    ResetDoubles();
    g_newFace.ret = static_cast<FT_Error>(0);

    FT_Error rc = ft_new_face_from_file(lib, "font.ttf", idx, &outFace);

    EXPECT_EQ(rc, static_cast<FT_Error>(0));
    EXPECT_TRUE(g_newFace.called);
    EXPECT_EQ(g_newFace.face_index, idx);
  }
}

#else  // _WIN32

TEST_F(FtNewFaceFromFileTest_32, NullFilenameReturnsInvalidArgumentAndDoesNotCallOpenFile_32) {
  g_openFile.ret_file = nullptr;
  g_openFace.ret = static_cast<FT_Error>(0);

  FT_Library lib = reinterpret_cast<FT_Library>(0x5555);
  FT_Face outFace = nullptr;

  FT_Error rc = ft_new_face_from_file(lib, nullptr, 0, &outFace);

  EXPECT_EQ(rc, FT_Err_Invalid_Argument);
  EXPECT_FALSE(g_openFile.called);
  EXPECT_FALSE(g_openFace.called);
}

TEST_F(FtNewFaceFromFileTest_32, OpenFileFailureReturnsCannotOpenResource_32) {
  g_openFile.ret_file = nullptr;  // simulate failure
  g_openFace.ret = static_cast<FT_Error>(0);

  FT_Library lib = reinterpret_cast<FT_Library>(0x6666);
  FT_Face outFace = nullptr;

  FT_Error rc = ft_new_face_from_file(lib, "missing.ttf", 0, &outFace);

  EXPECT_EQ(rc, FT_Err_Cannot_Open_Resource);
  EXPECT_TRUE(g_openFile.called);
  EXPECT_EQ(g_openFile.call_count, 1);
  EXPECT_FALSE(g_openFace.called);
}

TEST_F(FtNewFaceFromFileTest_32, SuccessfulOpenCallsFT_Open_FaceWithStreamFlag_32) {
  // Prepare a small file so fseek/ftell produce a positive size.
  const std::string path = MakeTempFileWithBytes(std::string("\x01\x02\x03", 3));

  // Let our openFile return a real FILE*.
  g_openFile.ret_file = std::fopen(path.c_str(), "rb");
  ASSERT_NE(g_openFile.ret_file, nullptr);

  g_openFace.ret = static_cast<FT_Error>(77);  // sentinel

  FT_Library lib = reinterpret_cast<FT_Library>(0x7777);
  FT_Face outFace = nullptr;

  FT_Error rc = ft_new_face_from_file(lib, path.c_str(), /*face_index=*/5, &outFace);

  EXPECT_EQ(rc, static_cast<FT_Error>(77));
  EXPECT_TRUE(g_openFile.called);
  EXPECT_TRUE(g_openFace.called);
  EXPECT_EQ(g_openFace.call_count, 1);
  EXPECT_EQ(g_openFace.library, lib);
  EXPECT_EQ(g_openFace.face_index, 5);
  EXPECT_EQ(g_openFace.aface, &outFace);

  // Observable expectation: FT_OPEN_STREAM should be used on Windows path.
  EXPECT_NE((g_openFace.flags & FT_OPEN_STREAM), 0UL);
  EXPECT_NE(g_openFace.stream_ptr, nullptr);

  // Cleanup: The wrapper hands ownership to FreeType in real usage; our stub doesn't close.
  // Close the FILE* we opened to avoid leaking descriptors in the test process.
  std::fclose(g_openFile.ret_file);
  std::remove(path.c_str());
}

#endif  // _WIN32