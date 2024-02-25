/*
 * Lunar.h
 *
 *  Created on: Jan 2, 2024
 *      Author: ACER
 */

#ifndef INC_LUNAR_H_
#define INC_LUNAR_H_

#include <math.h>
#include <stdio.h>
#define PI 3.14159265358979323846
char str4[50];
char can[10][10]={"Canh","Tan","Nham","Quy","Giap","At","Binh","Dinh","Mau","Ky"};
char chi[12][10]={"Than","Dau","Tuat","Hoi","Ty'","Suu","Dan","Mao","Thin","Ty.","Ngo","Mui"};

int jdFromDate(int dd, int mm, int yy);
int getNewMoonDay(int k, double timeZone);
int getSunLongitude(double jdn, double timeZone);
double getLunarMonth11(int yy, double timeZone);
int getLeapMonthOffset(double a11, double timeZone);
void convertSolar2Lunar(int dd, int mm, int yy, double timeZone);


#endif /* INC_LUNAR_H_ */
