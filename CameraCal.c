#include <stdio.h>
#include <stdlib.h>

int sub_10003400(int a1, int a2, signed int a3)
{
	signed int v3; // ecx@1
	signed int v5; // esi@3

	v3 = abs(a1);
	if (v3 > 40)
		return 1;

	v5 = abs(a2);
	if (v5 > 40)
		return 2;

	if (a3 > 80)
		return 3;

	if (a3 < -50)
		return 4;

	if (((a3 / 2) + v3) > 40)
		return 5;

	if (((a3 / 2) + v5) > 40)
		return 6;

	return 0;
}

void CameraCalibrate(signed int x1_yellow, signed int y1_magenta, signed int x2_cyan, signed int y2_green, int *cal_x, int *cal_y, signed int *cal_z)
{
	double v8; // st7@2
	double v9; // st6@2
	double v10; // st7@4
	double v11; // st7@5
	signed int v12; // eax@8
	double v13; // st7@9
	double v14; // st7@10
	int v15; // eax@13
	double v16; // st7@15
	double v17; // st7@16
	int v19; // eax@19

	if ( y2_green + y1_magenta <= x2_cyan + x1_yellow )
	{
		v8 = 40.0 - (double)x1_yellow;
		v9 = (double)x2_cyan;
	}
	else
	{
		v8 = 40.0 - (double)y1_magenta;
		v9 = (double)y2_green;
	}

	v10 = 80.0 - (v8 + 40.0 - v9) * 3.0 * 1.098901098901099;

	if ( v10 < 0.0 )
		v11 = v10 - 0.5;
	else
		v11 = v10 + 0.5;

	*cal_z = (signed int)v11;

	if (sub_10003400(0, 0, (signed int)v11))
	{
		do
		{
			v12 = *cal_z - ((((*cal_z <= 0) - 1) & 2) - 1);
			*cal_z = v12;
		}
		while ( sub_10003400(0, 0, v12) );
	}
	v13 = ((double)*cal_z * 0.001 + 1.0) * 0.9259259259259258 * (double)(x2_cyan - x1_yellow) * 3.0 * 0.5;
	if ( v13 < 0.0 )
		v14 = v13 - 0.5;
	else
		v14 = v13 + 0.5;
	*cal_x = (int)v14;
	if ( sub_10003400((int)v14, 0, *cal_z) )
	{
		do
		{
			v15 = *cal_x - ((((*cal_x <= 0) - 1) & 2) - 1);
			*cal_x = v15;
		}
		while ( sub_10003400(v15, 0, *cal_z) );
	}
	v16 = ((double)*cal_z * 0.001 + 1.0) * 0.9259259259259258 * (double)(y2_green - y1_magenta) * 3.0 * 0.5;
	if ( v16 < 0.0 )
		v17 = v16 - 0.5;
	else
		v17 = v16 + 0.5;
	*cal_y = (int)v17;

	if (sub_10003400(*cal_x, (int)v17, *cal_z)) {
		do {
			v19 = *cal_y - ((((*cal_y <= 0) - 1) & 2) - 1);
			*cal_y = v19;
		} while (sub_10003400(*cal_x, v19, *cal_z));
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
