#pragma once

struct ColourStruct {
	ColourStruct() {};
	ColourStruct(unsigned int R, unsigned int G, unsigned int B, unsigned int A) {
		r = R; g = G; b = B; a = A;
	}
	// Each of the struct's 4 elements is limited to 8 bits
	unsigned int r : 8, g : 8, b : 8, a : 8;

	// Define the == operator for comparing pixels
	bool operator==(const ColourStruct& second) const {
		return r == second.r && g == second.g && b == second.b && a == second.a;
	}

	// Define the != operator as the opposite of ==
	bool operator!=(const ColourStruct& second) const {
		return !(operator==(second));
	}
};