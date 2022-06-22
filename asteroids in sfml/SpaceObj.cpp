#include "SpaceObj.h"

float SpaceObj::angletorii(float angle) {
	return angle * 3.14159265359 / 180;
}

float SpaceObj::sixtyFPSMove(float pixels) {
	return pixels / 0.17;
}
