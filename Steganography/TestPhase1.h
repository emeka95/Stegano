#pragma once
#include "ColourStruct.h"
#include "SurfaceHandler.h"
#include <iostream>
#include <SDL_image.h>
#include <gtest\gtest.h>
#include <string>



// Since many tests will require input files, there needs to be a test directory
// A relative path cannot be used as it is impossible to know where main will be called from.
// An absolute path would damage portability, so instead, the path will be given when the tests are run
std::string testDir = "C:/Users/Windows 8/Documents/Visual Studio 2015/Projects/Steganography/images/";

// A simple test to ensure that gtest is working correctly. No other tests need to be run if this fails
TEST(Phase1_0, zeroIsZero) {
	ASSERT_EQ(0, 0);
}

/*
Phase 1_1 tests that the SurfaceHandler class is able to get the correct colour information from a specific pixel
The images were prepared beforehand, and their expecte values checked using Gimp2
*/

// Check pixel (0, 0) of the test image; its rgba values should be : (255, 0, 0, 255)
TEST(Phase1_1, png_0_0) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.png");
	ColourStruct pixel = ColourStruct(255, 0, 0, 255);
	EXPECT_EQ(pixel, sh.getPixel(0, 0));
}

// Check pixel (0, 2) of the test image; its rgba values should be : (0, 255, 0, 255)
TEST(Phase1_1, png_0_2) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.png");
	ColourStruct pixel = ColourStruct(255, 0, 0, 255);
	EXPECT_EQ(pixel, sh.getPixel(0, 1));
}

// Check pixel (2, 0) of the test image; its rgba values should be : (0, 0, 255, 255)
TEST(Phase1_1, png_2_0) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.png");
	ColourStruct pixel = ColourStruct(255, 0, 0, 255);
	EXPECT_EQ(pixel, sh.getPixel(0, 0));
}

// Check pixel (2, 2) of the test image; its rgba values should be : (255, 255, 255, 128)
TEST(Phase1_1, png_2_2) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.png");
	ColourStruct pixel = ColourStruct(255, 255, 255, 128);
	EXPECT_EQ(pixel, sh.getPixel(2, 2));
}

// Check pixel (1, 1) of the test image; its rgba values should be : (0, 0, 0, 218)
TEST(Phase1_1, png_1_1) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.png");
	ColourStruct pixel = ColourStruct(0, 0, 0, 218);
	EXPECT_EQ(pixel, sh.getPixel(1, 1));
}

// Check pixel (0, 0) of the test image; its rgba values should be : (255, 0, 0, 255)
TEST(Phase1_1, bmp_0_0) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.bmp");
	ColourStruct pixel = ColourStruct(255, 0, 0, 255);
	EXPECT_EQ(pixel, sh.getPixel(0, 0));
}

// Check pixel (0, 2) of the test image; its rgba values should be : (0, 255, 0, 255)
TEST(Phase1_1, bmp_0_2) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.bmp");
	ColourStruct pixel = ColourStruct(255, 0, 0, 255);
	EXPECT_EQ(pixel, sh.getPixel(0, 1));
}

// Check pixel (2, 0) of the test image; its rgba values should be : (0, 0, 255, 255)
TEST(Phase1_1, bmp_2_0) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.bmp");
	ColourStruct pixel = ColourStruct(255, 0, 0, 255);
	EXPECT_EQ(pixel, sh.getPixel(0, 0));
}

// Check pixel (2, 2) of the test image; its rgba values should be : (255, 255, 255, 128)
TEST(Phase1_1, bmp_2_2) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.bmp");
	ColourStruct pixel = ColourStruct(255, 255, 255, 128);
	EXPECT_EQ(pixel, sh.getPixel(2, 2));
}

// Check pixel (1, 1) of the test image; its rgba values should be : (0, 0, 0, 218)
TEST(Phase1_1, bmp_1_1) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_1.bmp");
	ColourStruct pixel = ColourStruct(0, 0, 0, 218);
	EXPECT_EQ(pixel, sh.getPixel(1, 1));
}


/*
Testing phase 1_2 checks the application's ability to edit a single pixel and then save the image.
This phase has to be verified externally (using Gimp2 in this case) so the only meaningful test case
can be written is to ensure that there are no exceptions.
*/
TEST(Phases1_2, save_png0_0) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.png");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 255, 255, 255, 255 }, 0, 0));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.png"));
}

TEST(Phases1_2, save_png1_2) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.png");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 1, 2, 3, 4 }, 1, 2));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.png"));
}

TEST(Phases1_2, save_png0_3) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.png");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 128, 128, 128, 128 }, 0, 3));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.png"));
}

TEST(Phases1_2, save_png4_1) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.png");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 0, 255, 0, 0 }, 4, 1));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.png"));
}

TEST(Phases1_2, save_png5_5) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.png");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 0, 0, 0, 0 }, 5, 5));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.png"));
}

TEST(Phases1_2, save_bmp0_0) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.bmp");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 255, 255, 255, 255 }, 0, 0));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.bmp"));
}

TEST(Phases1_2, save_bmp1_2) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.bmp");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 1, 2, 3, 4 }, 1, 2));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.bmp"));
}

TEST(Phases1_2, save_bmp0_3) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.bmp");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 128, 128, 128, 128 }, 0, 3));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.bmp"));
}

TEST(Phases1_2, save_bmp4_1) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.bmp");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 0, 255, 0, 0 }, 4, 1));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.bmp"));
}

TEST(Phases1_2, save_bmp5_5) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_2.bmp");
	EXPECT_NO_THROW(sh.setPixel(ColourStruct{ 0, 0, 0, 0 }, 5, 5));
	EXPECT_NO_THROW(sh.saveSurface(testDir + "Test Image 1_2.bmp"));
}

/*
Testing phase 1_3 checks the application's ability to edit a single pixel, save it and then re-extract the same information.
*/
TEST(Phase1_3, save_and_reload_png) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_3.png");
	ColourStruct pixel = ColourStruct(14, 14, 14, 14);
	sh.setPixel(pixel, 1, 1);
	sh.saveSurface(testDir + "Test Image 1_3.png");
	SurfaceHandler sh2 = SurfaceHandler();
	sh2.loadSurface(testDir + "Test Image 1_3.png");
	EXPECT_EQ(pixel, sh2.getPixel(1, 1));
}

TEST(Phase1_3, save_and_reload_bmp) {
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(testDir + "Test Image 1_3.bmp");
	ColourStruct pixel = ColourStruct(14, 14, 14, 14);
	sh.setPixel(pixel, 1, 1);
	sh.saveSurface(testDir + "Test Image 1_3.bmp");
	SurfaceHandler sh2 = SurfaceHandler();
	sh2.loadSurface(testDir + "Test Image 1_3.bmp");
	EXPECT_EQ(pixel, sh2.getPixel(1, 1));
}