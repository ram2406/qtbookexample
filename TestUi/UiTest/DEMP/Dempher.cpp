
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "dempher.h"

unsigned short DempherClass::NCADR = 2000;

DempherClass::DempherClass() {
    cadr.reserve(NCADR);
}

void DempherClass::GetConfig(void)
{ FILE * fconfig;
  char   str[20];
  char * pStr;
  int    nParam;

  fconfig = fopen("c:\\interpol\\config.cfg", "rt");
  if(!fconfig)
  { printf(getTextResCode(ERROR_05).c_str());
    exit(ERROR_05);
  }

  config.dF1 = 0;
  config.dF2 = 0;

  nParam = 0;
  while(nParam < 2 && fgets(str, 80, fconfig))
  { if( (pStr = std::strstr(str, "dF1=") ) )
    { config.dF1 = std::atof(pStr + std::strlen("dF1="));
      printf("dF1=%06.1lf\n", config.dF1);
      nParam++;
    }

    if( ( pStr = strstr(str, "dF2=") ) )
    { config.dF2 = std::atof(pStr + std::strlen("dF2="));
      printf("dF2=%06.1lf\n", config.dF2);
      nParam++;
    }
  }

  fclose(fconfig);

  if(nParam != 2)
  { printf(getTextResCode(ERROR_06).c_str());
    exit(ERROR_06);
  }
}

result_code DempherClass::GetCadr(FILE * fin)
{
    int  inByte;
    long nF;
    long NF;
    long X;
    long Y;
    long Z;
    long L;

    nCadr = 0;

    nF = 0;
    NF = 0;
    X  = 0;
    Y  = 0;
    Z  = 0;
    L  = 0;

    inByte = fgetc(fin);

    while(inByte != EOF)
    {
        if(inByte == 15)
        {

            double F = (NF != 0)
                       ? (1200.0 * nF / NF)
                       : (0.0);

            CADR newCadr = { X, Y, Z , L, F};
            cadr.push_back(newCadr);

            nF = 0;
            NF = 0;
            X  = 0;
            Y  = 0;
            Z  = 0;
            L  = 0;
        }
        else
        {
            NF++;
            if(inByte)
            {
              nF++;
              L++;
            }
            if(inByte & 1)  X++;
            if(inByte & 2)  X--;
            if(inByte & 4)  Y++;
            if(inByte & 8)  Y--;
            if(inByte & 16) Z++;
            if(inByte & 32) Z--;
        }
        inByte = fgetc(fin);
    }
    CADR lastCadr = {0 , 0 , 0 , 0 , 0.0};
    cadr.push_back(lastCadr);
    nCadr = cadr.size();

    return SUCCESS;
}

void DempherClass::PutCadr(int step)
{ int iCadr;
  printf("PRG\n");
  for(iCadr = 0; iCadr < nCadr; iCadr++)
  { printf("N%04d X%+07ld Y%+07ld Z%+07ld F%06.1lf L%06ld\n",
	    iCadr,
	    cadr[iCadr].X,
	    cadr[iCadr].Y,
	    cadr[iCadr].Z,
	    cadr[iCadr].F,
	    cadr[iCadr].L
	  );
     if(step) getchar();
  }
}

result_code DempherClass::Dempher(FILE * fin, FILE * fout)
{ int    iCadr;
  long   L1;
  long   L2;
  long   L;
  long   l;
  long   i;
  double dF;
  double F;
  double lF;
  int    inByte;
  int    sign;

  fseek(fin, 0L, SEEK_SET);

  iCadr = 0;
  inByte = fgetc(fin);
  if(inByte != 15)
  {
      printf(getTextResCode(ERROR_08).c_str(), iCadr + 1);
      return ERROR_08;
  }
  fputc(inByte, fout);

  for(iCadr = 1; iCadr < nCadr - 1; iCadr++)
  {
      if(cadr[iCadr].L == 0)
      {
          inByte = fgetc(fin);
          while(inByte != 15)
          {
            fputc(inByte, fout);
            inByte = fgetc(fin);
          }
          fputc(inByte, fout);
          continue;
      }


      if(cadr[iCadr - 1].X * cadr[iCadr].X < 0 ||
         cadr[iCadr - 1].Y * cadr[iCadr].Y < 0 ||
         cadr[iCadr - 1].Z * cadr[iCadr].Z < 0
        ) sign = -1;
      else sign = 1;

      if(sign > 0)
          dF = cadr[iCadr].F - cadr[iCadr - 1].F;
      else
          dF = cadr[iCadr].F;

      if(dF > config.dF1)
          L1 = dF / config.dF2 + 1;
      else
          L1 = 0;

      if(cadr[iCadr + 1].X * cadr[iCadr].X < 0 ||
         cadr[iCadr + 1].Y * cadr[iCadr].Y < 0 ||
         cadr[iCadr + 1].Z * cadr[iCadr].Z < 0
        ) sign = -1;
      else sign = 1;

      if(sign > 0)
          dF = cadr[iCadr].F - cadr[iCadr + 1].F;
      else
          dF = cadr[iCadr].F;

      if(dF > config.dF1)
          L2 = dF / config.dF2 + 1;
      else
          L2 = 0;

      if(L1 + L2 > cadr[iCadr].L)
      {
        printf(getTextResCode(ERROR_09).c_str(), iCadr);
        return ERROR_09;
      }

      inByte = fgetc(fin);
      L = 0;

      if(L1 > 0)
      {
          l = 0;
          F = cadr[iCadr].F - L1 * config.dF2;

          while(L < L1)
          {
              if(inByte == 0) l++;
              else
                {
                  F = F + config.dF2;

                  if(F > cadr[iCadr].F)
                      F = cadr[iCadr].F;

                  lF = 1200.0 / F;

                  if(lF > l)
                      l = lF;

                  for(i = 0; i < l; i++)
                      fputc(0, fout);

                  fputc(inByte, fout);

                  l = 0;

                  L++;
                }

              inByte = fgetc(fin);
          } // while(L < L1)
    }

    while(L < cadr[iCadr].L - L2)
    {
        if(inByte != 0) L++;
        fputc(inByte, fout);
        inByte = fgetc(fin);
    }

    if(L2 > 0)
    { l = 0;
      F = cadr[iCadr].F;

      while(L < cadr[iCadr].L)
      {
          if(inByte == 0) l++;
          else
            {
              F = F - config.dF2;
              if(F < config.dF2) F = config.dF2;

              lF = 1200.0 / F;
              if(lF > l) l = lF;
              for(i = 0; i < l; i++) fputc(0, fout);
              fputc(inByte, fout);
              l = 0;
              L++;
            }
            inByte = fgetc(fin);
      }     //while(L < cadr[iCadr].L)
    }   //if(L2 > 0)

    if(inByte != 15)
    {
        printf(getTextResCode(ERROR_08).c_str(), iCadr + 1);
        return ERROR_08;
    }   //if(inByte != 15)

    fputc(inByte, fout);
  }     //for(iCadr = 1; iCadr < nCadr - 1; iCadr++)

  return SUCCESS;
}

result_code DempherClass::exec(std::string filenameIn, std::string filenameOut, bool step , CONFIG &conf)
{
    FILE * fin;
    FILE * fout;


    fin  = fopen(filenameIn.c_str(), "rb");
    if(!fin)
    {
        printf(getTextResCode(ERROR_03).c_str());
        return ERROR_03;
    }

    fout = fopen(filenameOut.c_str(), "w+b");
    if(!fout)
    {
        printf(getTextResCode(ERROR_04).c_str());
        return ERROR_04;
    }

    config = conf;

    GetCadr(fin);
    PutCadr(step);
    Dempher(fin, fout);

    fclose(fin);
    fclose(fout);

    //fcloseall();

    printf("SUCCESS!");
    return SUCCESS;

}
