#include <stdio.h>
#include <stdlib.h>

int sub_10003400(int a1, int a2, signed int a3)
{
	if (abs(a1) > 40)
		return 1;

	if (abs(a2) > 40)
		return 2;

	if (a3 > 80)
		return 3;

	if (a3 < -50)
		return 4;

	if (((a3 / 2) + abs(a1)) > 40)
		return 5;

	if (((a3 / 2) + abs(a2)) > 40)
		return 6;

	return 0;
}

void CameraCalibrate(signed int x1_yellow, signed int y1_magenta, signed int x2_cyan, signed int y2_green, int *cal_x, int *cal_y, signed int *cal_z)
{
	double v8; // st7@2
	double v9; // st6@2
	double v11; // st7@5
	double v13; // st7@9
	double v16; // st7@15

	if ((y2_green + y1_magenta) <= (x2_cyan + x1_yellow)) {
		v8 = 40.0 - (double)x1_yellow;
		v9 = (double)x2_cyan;
	} else {
		v8 = 40.0 - (double)y1_magenta;
		v9 = (double)y2_green;
	}

	v11 = 80.0 - (v8 + 40.0 - v9) * 3.0 * 1.098901098901099;
	v11 = (v11 < 0.0) ? v11 - 0.5 : v11 + 0.5;
	*cal_z = (signed int)v11;

	if (sub_10003400(0, 0, *cal_z)) {
		do {
			*cal_z = *cal_z - ((((*cal_z <= 0) - 1) & 2) - 1);
		} while ( sub_10003400(0, 0, *cal_z) );
	}


	v13 = ((double)*cal_z * 0.001 + 1.0) * 0.9259259259259258 * (double)(x2_cyan - x1_yellow) * 3.0 * 0.5;
	v13 = (v13 < 0.0) ? v13 - 0.5 : v13 + 0.5;
	*cal_x = (int)v13;

	if ( sub_10003400(*cal_x, 0, *cal_z) ) {
		do {
			*cal_x = *cal_x - ((((*cal_x <= 0) - 1) & 2) - 1);
		} while ( sub_10003400(*cal_x, 0, *cal_z) );
	}


	v16 = ((double)*cal_z * 0.001 + 1.0) * 0.9259259259259258 * (double)(y2_green - y1_magenta) * 3.0 * 0.5;
	v16 = (v16 < 0.0) ? v16 - 0.5 : v16 + 0.5;
	*cal_y = (int)v16;

	if (sub_10003400(*cal_x, *cal_y, *cal_z)) {
		do {
			*cal_y = *cal_y - ((((*cal_y <= 0) - 1) & 2) - 1);
		} while (sub_10003400(*cal_x, *cal_y, *cal_z));
	}
}

int main(void)
{
	//CameraCalibrate(signed int a1, signed int a2, signed int a3, signed int a4, int *a5, int *a6, signed int *a7)

	char vals[][4] = {
		// a   b   c   d
		{ 28, 28, 28, 28 },
		{  0, 28, 28, 28 },
		{  0, 16, 28, 28 },
		{  0, 28, 16, 28 },
		{  0, 28, 28, 16 },
		{ 28,  0, 28, 28 },
		{ 16,  0, 28, 28 },
		{ 28,  0, 16, 28 },
		{ 28,  0, 28, 16 },
		{ 28, 28,  0, 28 },
		{ 16, 28,  0, 28 },
		{ 28, 16,  0, 28 },
		{ 28, 28,  0, 16 },
		{ 28, 28, 28,  0 },
		{ 16, 28, 28,  0 },
		{ 28, 16, 28,  0 },
		{ 28, 28, 16,  0 },
	};

	int i;

	for (i=40; i>=0; i--) {
		int x, y, z;
		CameraCalibrate(i,i,i,i, &x, &y, &z);
		printf("%2d %2d %2d %2d => %4d %4d %4d\n", i, i, i, i, x, y, z);
	}

	/***
	 *
	 *   B
	 * A   C
	 *   D
	 *
	 * A = Yellow
	 * B = Magenta
	 * C = Cyan
	 * D = Green
	 *
	 * X,Y,Z = X/Y translation and zoom
	 */

	for (i=0; i<(sizeof(vals)/sizeof(vals[0])); i++) {
		int a, b, c, d;
		int x, y, z;
		a = vals[i][0]; b = vals[i][1]; c = vals[i][2]; d = vals[i][3];
		CameraCalibrate(a, b, c, d, &x, &y, &z);
		printf("%2d %2d %2d %2d => %4d %4d %4d\n", a, b, c, d, x, y, z);
	}

	return 0;
}
