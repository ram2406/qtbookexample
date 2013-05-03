#include <stdio.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <cmath>
#include <string>

#define SUCCESS  0
#define ERROR_01 1
#define ERROR_02 2
#define ERROR_03 3
#define ERROR_04 4
#define ERROR_05 5
#define ERROR_06 6
#define ERROR_07 7
#define ERROR_08 8

struct CADR
{ int  N;
  int  G;
	long X;
	long Y;
	long Z;
	long I;
	long J;
	long K;
	int  F;
	int  S;
	int  T;
	int  M;
	int  L;
};

void fun_output(std::string formatText , ...);

int G_1;
int G_2;
int F;
int finish;

void InterpolCadr(CADR cadr, FILE * fout);
void InterpolLine(CADR cadr, FILE * fout);
void InterpolCircle(CADR cadr, FILE * fout);
void InterpolPause(CADR cadr, FILE * fout);
void InterpolTechn(CADR cadr, FILE * fout);

void interpol(std::wstring finName, std::wstring foutName)
{ FILE * fin;
  FILE * fout;
  CADR   cadr;
  int    nAddr;

  int    c;

  char str[80];
  char *pStr;

	finish = 0;


    fin  = _wfopen(finName.c_str(), L"r");
	if(!fin)
	{ 
        throw L"Не удалоссь открыть входящий файл";
	}

    fout = _wfopen(foutName.c_str(), L"w+b");
	if(!fout)
	{ 
        throw L"Не удалоссь сохранить исходящий файл";
	}
    {
	c = fgetc(fin);
	while(c != EOF && c != '%') c = fgetc(fin);
	/*
	while(fgets(str, 80, fin) && !strstr(str, "%"));
	if(!strstr(str, "%"))
	{ fun_output("\nERROR_05: ­Ґ ­ ©¤Ґ­ бЁ¬ў®« %%!");
		exit(ERROR_05);
	}
	*/
	if(c != '%')
	{ 
        throw L"Не удалось найти специальный символ '%' в начале файла";
	}
    while( c != 'N'  && c != EOF) c = fgetc(fin);

    if(c == EOF) throw L"Программа пуста";
    }
    fseek(fin, -1 , SEEK_CUR);
    //clrscr();

	G_1 = 0;
	G_2 = 0;
	F   = 0;

    while(!finish && fgets(str, 80, fin))
    {
        fun_output("Строка :\n");
        fun_output(str);
        fun_output("\n");
        nAddr = 0;
		fun_output("\n");

		cadr.N = 0;
		if(pStr = strchr(str, 'N'))
		{ cadr.N = atoi(pStr + 1);
			nAddr++;

			fun_output("N%03d",   cadr.N);
		}

		cadr.G = 0;
		if(pStr = strchr(str, 'G'))
		{ cadr.G = atoi(pStr + 1);
			nAddr++;

			fun_output("G%02d",   cadr.G);

			if(cadr.G == 1 || cadr.G == 2 || cadr.G == 3 || cadr.G == 4) G_1 = cadr.G;
			else if(cadr.G == 17 ||	cadr.G == 18 ||	cadr.G == 19) G_2 = cadr.G;
					 else
					 { 
                        throw L"Не известная команда";
					 }
		}

		cadr.X = 0;
		if(pStr = strchr(str, 'X'))
		{ cadr.X = atol(pStr + 1);
			nAddr++;

			fun_output("X%+07ld", cadr.X);
		}

		cadr.Y = 0;
		if(pStr = strchr(str, 'Y'))
		{ cadr.Y = atol(pStr + 1);
			nAddr++;

			fun_output("Y%+07ld", cadr.Y);
		}

		cadr.Z = 0;
		if(pStr = strchr(str, 'Z'))
		{ cadr.Z = atol(pStr + 1);
			nAddr++;

			fun_output("Z%+07ld", cadr.Z);
		}

		cadr.I = 0;
		if(pStr = strchr(str, 'I'))
		{ cadr.I = atol(pStr + 1);
			if(cadr.I < 0) cadr.I = -cadr.I;
			nAddr++;

			fun_output("I%+07ld", cadr.I);
		}

		cadr.J = 0;
		if(pStr = strchr(str, 'J'))
		{ cadr.J = atol(pStr + 1);
			if(cadr.J < 0) cadr.J = -cadr.J;
			nAddr++;

			fun_output("J%+07ld", cadr.J);
		}

		cadr.K = 0;
		if(pStr = strchr(str, 'K'))
		{ cadr.K = atol(pStr + 1);
			if(cadr.K < 0) cadr.K = -cadr.K;
			nAddr++;

			fun_output("K%+07ld", cadr.K);
		}

		cadr.F = 0;
		if(pStr = strchr(str, 'F'))
		{ cadr.F = atoi(pStr + 1);
			nAddr++;

			fun_output("F%04d",   cadr.F);

			F = cadr.F;
		}

		cadr.S = 0;
		if(pStr = strchr(str, 'S'))
		{ cadr.S = atoi(pStr + 1);
			nAddr++;

			fun_output("S%02d",   cadr.S);
		}

		cadr.T = 0;
		if(pStr = strchr(str, 'T'))
		{ cadr.T = atoi(pStr + 1);
			nAddr++;

			fun_output("T%02d",   cadr.T);
		}

		cadr.M = -1;
		if(pStr = strchr(str, 'M'))
		{ cadr.M = atoi(pStr + 1);
			nAddr++;

			fun_output("M%02d",   cadr.M);
		}

		cadr.L = 0;
		if(pStr = strchr(str, 'L'))
		{ cadr.L = atoi(pStr + 1);
			nAddr++;

			fun_output("L%03d",   cadr.L);
		}

		if(nAddr == 0) break;

		InterpolCadr(cadr, fout);
	}

    fun_output("\nSUCCESS: Успешно­ !");
	getch();

    fclose(fin);
    fclose(fout);

    //exit(SUCCESS);
}

void InterpolCadr(CADR cadr, FILE * fout)
{ if(G_1 == 1 && (cadr.X != 0 || cadr.Y != 0 || cadr.Z != 0) && F != 0)
    { fun_output("\nЛинейная интерполяция!");
		InterpolLine(cadr, fout);
	}
	else if((G_1 == 2 || G_1 == 3 ) && (cadr.X != 0 || cadr.Y != 0 || cadr.Z != 0) && F != 0)
			 { 
				fun_output("\nКруговая интерполяция");
				InterpolCircle(cadr, fout);
			 }
			 else if(G_1 == 4)
						{ 
							fun_output("\nЗадержка!");
							InterpolPause(cadr, fout);
						}
			else if(cadr.M != -1)
					 { 
                        fun_output("\nТехническая интерполяция!");
						InterpolTechn(cadr, fout);
					 }
					 else if(G_2 == 17 || G_2 == 18 || G_2 == 19)
								{
									fun_output("\nИзменение плоскости круговой интерполяции");
								}
								else
								{ 
									throw "\nНе правильно заданы кадры программы";
									
								}
}

void InterpolLine(CADR cadr, FILE * fout)
{ double        f;
	int           V;
	int           m;
	double        fx;
	double        fy;
	double        fz;
	double        X;
	double        Y;
	double        Z;
	double        cosx;
	double        cosy;
	double        cosz;
	unsigned char dX;
	unsigned char dY;
	unsigned char dZ;
	unsigned int  outByte;
	double        nx;
	double        ny;
	double        nz;
	double        ix;
	double        iy;
	double        iz;
	long          x;
	long          y;
	long          z;

	//ђ бзҐв з бв®вл ўл¤ зЁ
	V = F;
	if(V >= 4000) V -= 4000;
	m = V / 100 - 3;
	V = V % 100;
	f = 0.01 * V * pow(10.0, m) * 2000 / 1200;

	//ђ бзҐв з бв®в Ї® Є®®а¤Ё­ в ¬
	X = cadr.X;
	Y = cadr.Y;
	Z = cadr.Z;

	cosx = X / sqrt(X * X + Y * Y + Z * Z);
	cosy = Y / sqrt(X * X + Y * Y + Z * Z);
	cosz = Z / sqrt(X * X + Y * Y + Z * Z);

	fx = f * cosx;
	fy = f * cosy;
	fz = f * cosz;

	if(cadr.X >= 0) dX = 1;
	else
	{ dX = 2;
		fx = -fx;
	}

	if(cadr.Y >= 0) dY = 4;
	else
	{ dY = 8;
		fy = -fy;
	}

	if(cadr.Z >= 0) dZ = 16;
	else
	{ dZ = 32;
		fz = -fz;
	}

	if(fx != 0) nx = 2000.0 / fx;
	else nx = -1;

	if(fy != 0) ny = 2000.0 / fy;
	else ny = -1;

	if(fz != 0) nz = 2000.0 / fz;
	else nz = -1;

	fun_output("\nf = %.1lf fx = %.1lf fy = %.1lf fz = %.1lf", f, fx, fy, fz);
	fun_output("\nnx = %.1lf ny = %.1lf nz = %.1lf", nx, ny, nz);

	//‡ ЇЁбм ў д ©« ЇаЁ§­ Є  ­ з «  Є ¤а 
	outByte = 15;
	fputc(outByte, fout);

	//€­вҐаЇ®«пжЁп
	x = 0;
	y = 0;
	z = 0;

	ix = 0;
	iy = 0;
	iz = 0;

	while(1)
	{ outByte = 0;

		ix += 1;
		iy += 1;
		iz += 1;

		if(ix >= nx)
		{ if(x < labs(cadr.X))
			{ outByte |= dX;
				x++;
			}
			ix -= nx;
		}

		if(iy >= ny)
		{ if(y < labs(cadr.Y))
			{ outByte |= dY;
				y++;
			}
			iy -= ny;
		}

		if(iz >= nz)
		{ if(z < labs(cadr.Z))
			{ outByte |= dZ;
				z++;
			}
			iz -= nz;
		}

		fputc(outByte, fout);

		if((x == labs(cadr.X)) && (y == labs(cadr.Y)) && (z == labs(cadr.Z))) break;
	}
}

void InterpolCircle(CADR cadr, FILE * fout)
{ double       x;
	double       y;
	double       z;
	long         X;
	long         Y;
	long         Z;
	double       R;
	double       dX;
	double       dY;
	double       dZ;
	double       dx;
	double       dy;
	double       dz;
	double       f;
	int          V;
	int          m;
	double       n;
	double       i;
	unsigned int outByte;

	fun_output("\n");

	//ђ бзҐв з бв®вл ўл¤ зЁ
	V = F;
	if(V >= 4000) V -= 4000;
	m = V / 100 - 3;
	V = V % 100;
	f = 0.01 * V * pow(10.0, m) * 2000 / 1200;
	n = 2000.0 / f;

	//‡ ЇЁбм ў д ©« ЇаЁ§­ Є  ­ з «  Є ¤а 
	outByte = 15;
	fputc(outByte, fout);

	//€­вҐаЇ®«пжЁп
	if(G_2 == 17)
    { if(cadr.I != 0 && cadr.J != 0) R = sqrt(double(cadr.I * cadr.I + cadr.J * cadr.J));
		else if(cadr.I != 0 && cadr.J == 0) R = cadr.I;
				 else if(cadr.I == 0 && cadr.J != 0) R = cadr.J;
							else
                            {
                                throw L"Не правильно заданы геометрическая инйормация для круговой интерполяции!";
								
							}

		if(cadr.X > 0 && cadr.Y < 0)
		{ x = cadr.I;
			y = cadr.J;
		}
		else if(cadr.X < 0 && cadr.Y < 0)
				 { x =  cadr.I;
					 y = -cadr.J;
				 }
				 else if(cadr.X < 0 && cadr.Y > 0)
							{ x = -cadr.I;
								y = -cadr.J;
							}
							else
							{ x = -cadr.I;
								y = cadr.J;
							}

		X  = 0;
		Y  = 0;
		dx = 0;
		dy = 0;
		i  = 0;
		while(1)
		{ outByte = 0;

			i += 1;
			if(i >= n)
			{ dX =  y / R;
				dY = -x / R;
				x += dX;
				y += dY;

				if(X < labs(cadr.X))
				{ dx += fabs(dX);
					if(dx >= 1)
					{ X++;
						dx -= 1;
						if(cadr.X >= 0) outByte |= 1;
						else outByte |= 2;
					}
				}

				if(Y < labs(cadr.Y))
				{ dy += fabs(dY);
					if(dy >= 1)
					{ Y++;
						dy -= 1;
						if(cadr.Y >= 0) outByte |= 4;
						else outByte |= 8;
					}
				}
				i -= n;
			}

			fputc(outByte, fout);

			if((X == labs(cadr.X)) && (Y == labs(cadr.Y))) return;
		}
	}

	if(G_2 == 18)
    { if(cadr.I != 0 && cadr.K != 0) R = sqrt(double ( cadr.I * cadr.I + cadr.K * cadr.K));
		else if(cadr.I != 0 && cadr.K == 0) R = cadr.I;
				 else if(cadr.I == 0 && cadr.K != 0) R = cadr.K;
							else
							{ 
								throw "Не правильно заданы параметры для круговой интерполяции";
								
							}

		if(cadr.X > 0 && cadr.Z < 0)
		{ x = cadr.I;
			z = cadr.K;
		}
		else if(cadr.X < 0 && cadr.Z < 0)
				 { x =  cadr.I;
					 z = -cadr.K;
				 }
				 else if(cadr.X < 0 && cadr.Z > 0)
							{ x = -cadr.I;
								z = -cadr.K;
							}
							else
							{ x = -cadr.I;
								z = cadr.K;
							}

		X  = 0;
		Z  = 0;
		dx = 0;
		dz = 0;
		i  = 0;
		while(1)
		{ outByte = 0;

			i += 1;
			if(i >= n)
			{ dX =  z / R;
				dZ = -x / R;
				x += dX;
				z += dZ;

				if(X < labs(cadr.X))
				{ dx += fabs(dX);
					if(dx >= 1)
					{ X++;
						dx -= 1;
						if(cadr.X >= 0) outByte |= 1;
						else outByte |= 2;
					}
				}

				if(Z < labs(cadr.Z))
				{ dz += fabs(dZ);
					if(dz >= 1)
					{ Z++;
						dz -= 1;
						if(cadr.Z >= 0) outByte |= 16;
						else outByte |= 32;
					}
				}
				i -= n;
			}

			fputc(outByte, fout);

			if((X == labs(cadr.X)) && (Z == labs(cadr.Z))) return;
		}
	}

	if(G_2 == 19)
    { if(cadr.J != 0 && cadr.K != 0) R = sqrt(double( cadr.J * cadr.J + cadr.K * cadr.K));
		else if(cadr.J != 0 && cadr.K == 0) R = cadr.J;
				 else if(cadr.J == 0 && cadr.K != 0) R = cadr.K;
							else
                            {
                                fun_output("\nERROR_08: неправиль­о задана­  геометрическая и­формация для круговой и­терполяции!");
                                //exit(ERROR_08);
                                throw L"Неправиль­о задана­  геометрическая и­формация для круговой и­терполяции!";
							}

		if(cadr.Y > 0 && cadr.Z < 0)
		{ y = cadr.J;
			z = cadr.K;
		}
		else if(cadr.Y < 0 && cadr.Z < 0)
				 { y =  cadr.J;
					 z = -cadr.K;
				 }
				 else if(cadr.Y < 0 && cadr.Z > 0)
							{ y = -cadr.J;
								z = -cadr.K;
							}
							else
							{ y = -cadr.J;
								z = cadr.K;
							}

		Y  = 0;
		Z  = 0;
		dy = 0;
		dz = 0;
		i  = 0;
		while(1)
		{ outByte = 0;

			i += 1;
			if(i >= n)
			{ dY =  z / R;
				dZ = -y / R;
				y += dY;
				z += dZ;

				if(Y < labs(cadr.Y))
				{ dy += fabs(dY);
					if(dy >= 1)
					{ Y++;
						dy -= 1;
						if(cadr.Y >= 0) outByte |= 1;
						else outByte |= 2;
					}
				}

				if(Z < labs(cadr.Z))
				{ dz += fabs(dZ);
					if(dz >= 1)
					{ Z++;
						dz -= 1;
						if(cadr.Z >= 0) outByte |= 16;
						else outByte |= 32;
					}
				}
				i -= n;
			}

			fputc(outByte, fout);

			if((Y == labs(cadr.Y)) && (Z == labs(cadr.Z))) return;
		}
	}
}

void InterpolPause(CADR cadr, FILE * fout)
{ double        f;
	int           V;
	int           m;
	double        fx;
	double        fy;
	double        fz;
	double        X;
	double        Y;
	double        Z;
	double        cosx;
	double        cosy;
	double        cosz;
	unsigned int  outByte;
	double        nx;
	double        ny;
	double        nz;
	double        ix;
	double        iy;
	double        iz;
	long          x;
	long          y;
	long          z;

	//ђ бзҐв з бв®вл ўл¤ зЁ
	V = F;
	if(V >= 4000) V -= 4000;
	m = V / 100 - 3;
	V = V % 100;
	f = 0.01 * V * pow(10.0, m) * 2000 / 1200;

	//ђ бзҐв з бв®в Ї® Є®®а¤Ё­ в ¬
	X = cadr.X;
	Y = cadr.Y;
	Z = cadr.Z;

	cosx = X / sqrt(X * X + Y * Y + Z * Z);
	cosy = Y / sqrt(X * X + Y * Y + Z * Z);
	cosz = Z / sqrt(X * X + Y * Y + Z * Z);

	fx = f * cosx;
	fy = f * cosy;
	fz = f * cosz;

	if(cadr.X < 0) fx = -fx;

	if(cadr.Y < 0) fy = -fy;

	if(cadr.Z < 0) fz = -fz;

	if(fx != 0) nx = 2000.0 / fx;
	else nx = -1;

	if(fy != 0)	ny = 2000.0 / fy;
	else ny = -1;

	if(fz != 0) nz = 2000.0 / fz;
	else nz = -1;

	fun_output("\nf = %.1lf fx = %.1lf fy = %.1lf fz = %.1lf", f, fx, fy, fz);
	fun_output("\nnx = %.1lf ny = %.1lf nz = %.1lf", nx, ny, nz);

	//‡ ЇЁбм ў д ©« ЇаЁ§­ Є  ­ з «  Є ¤а 
	outByte = 15;
	fputc(outByte, fout);

	//€­вҐаЇ®«пжЁп
	x = 0;
	y = 0;
	z = 0;

	ix = 0;
	iy = 0;
	iz = 0;

	while(1)
	{ outByte = 0;

		ix += 1;
		iy += 1;
		iz += 1;

		if(ix >= nx)
		{ if(x < labs(cadr.X)) x++;
			ix -= nx;
		}

		if(iy >= ny)
		{ if(y < labs(cadr.Y)) y++;
			iy -= ny;
		}

		if(iz >= nz)
		{ if(z < labs(cadr.Z)) z++;
			iz -= nz;
		}

		fputc(outByte, fout);

		if((x == labs(cadr.X)) && (y == labs(cadr.Y)) && (z == labs(cadr.Z))) break;
	}
}

void InterpolTechn(CADR cadr, FILE * fout)
{ unsigned int  outByte;

	if(cadr.M == 2)
    {
        fun_output("\nНайден­ кадр с коман­дой остан­ова!");
		outByte = 15;
		fputc(outByte, fout);
		finish = 1;
	}
}
