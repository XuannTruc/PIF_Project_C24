/*
 * Lunar.c
 *
 *  Created on: Jan 2, 2024
 *      Author: Nguyen_Vu_Huy
 */
#include "Lunar.h"
#include "ILI9225.h"

int jdFromDate(int dd, int mm, int yy) {     //Ham chuyen tu ngay, thang, nam nhap vao sang Julius day (tuc la so ngay tu ngay 1/1/4713 TCN theo lich Julius den ngay nhap vao)
    int a, y, m, jd;
    a = (14 - mm) / 12;
    y = yy + 4800 - a;
    m = mm + 12 * a - 3;
    jd = dd + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    if (jd < 2299161) {
        jd = dd + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083;
    }
    return jd;
    }
int getNewMoonDay(int k, double timeZone) {     //Ham se tinh toan diem Soc cua thang am lich chua ngay nhap vao, tu do tinh duoc ngay am lich cua thoi gian da nhap
    double T, T2, T3, dr, Jd1, M, Mpr, F, C1, deltat, JdNew;
    T = k / 1236.85;
    T2 = T * T;
    T3 = T2 * T;
    dr = PI / 180;
    Jd1 = 2415020.75933 + 29.53058868 * k + 0.0001178 * T2 - 0.000000155 * T3;
    Jd1 = Jd1 + 0.00033 * sin((166.56 + 132.87 * T - 0.009173 * T2) * dr);
    M = 359.2242 + 29.10535608 * k - 0.0000333 * T2 - 0.00000347 * T3;
    Mpr = 306.0253 + 385.81691806 * k + 0.0107306 * T2 + 0.00001236 * T3;
    F = 21.2964 + 390.67050646 * k - 0.0016528 * T2 - 0.00000239 * T3;
    C1 = (0.1734 - 0.000393 * T) * sin(M * dr) + 0.0021 * sin(2 * dr * M);
    C1 = C1 - 0.4068 * sin(Mpr * dr) + 0.0161 * sin(dr * 2 * Mpr);
    C1 = C1 - 0.0004 * sin(dr * 3 * Mpr);
    C1 = C1 + 0.0104 * sin(dr * 2 * F) - 0.0051 * sin(dr * (M + Mpr));
    C1 = C1 - 0.0074 * sin(dr * (M - Mpr)) + 0.0004 * sin(dr * (2 * F + M));
    C1 = C1 - 0.0004 * sin(dr * (2 * F - M)) - 0.0006 * sin(dr * (2 * F + Mpr));
    C1 = C1 + 0.0010 * sin(dr * (2 * F - Mpr)) + 0.0005 * sin(dr * (2 * Mpr + M));
    if (T < -11) {
        deltat = 0.001 + 0.000839 * T + 0.0002261 * T2 - 0.00000845 * T3 - 0.000000081 * T * T3;
    } else {
        deltat = -0.000278 + 0.000265 * T + 0.000262 * T2;
    }
    JdNew = Jd1 + C1 - deltat;
    return (int)(JdNew + 0.5 + timeZone / 24);
}

int getSunLongitude(double jdn, double timeZone) {    //Ham tinh xem thang da nhap vao co Trung khi nao
    double T, T2, dr, M, L0, DL, L;
    T = (jdn - 2451545.5 - timeZone / 24) / 36525;
    T2 = T * T;
    dr = PI / 180;
    M = 357.52910 + 35999.05030 * T - 0.0001559 * T2 - 0.00000048 * T * T2;
    L0 = 280.46645 + 36000.76983 * T + 0.0003032 * T2;
    DL = (1.914600 - 0.004817 * T - 0.000014 * T2) * sin(dr * M);
    DL = DL + (0.019993 - 0.000101 * T) * sin(dr * 2 * M) + 0.000290 * sin(dr * 3 * M);
    L = L0 + DL;
    L = L * dr;
    L = L - PI * 2 * (int)(L / (PI * 2));
    return (int)(L / PI * 6);
}
double getLunarMonth11(int yy, double timeZone) {   //Ham tinh xem nam am lich cua thoi gian da nhap co phai nam nhuan hay khong
    int k, off, nm, sunLong;
    off = jdFromDate(31, 12, yy) - 2415021;
    k = (int)(off / 29.530588853);
    nm = (int)getNewMoonDay(k, timeZone);
    sunLong = getSunLongitude(nm, timeZone);
    if (sunLong >= 9) {
        nm = (int)getNewMoonDay(k - 1, timeZone);
    }
    return nm;
}
int getLeapMonthOffset(double a11, double timeZone) {   //Ham tinh xem neu nam do la nam nhuan thi thang nhuan se la thang nao
    int k, last, arc, i;
    k = (int)((a11 - 2415021.076998695) / 29.530588853 + 0.5);
    last = 0;
    i = 1;
    arc = getSunLongitude(getNewMoonDay(k + i, timeZone), timeZone);
    do {
        last = arc;
        i++;
        arc = getSunLongitude(getNewMoonDay(k + i, timeZone), timeZone);
    } while (arc != last && i < 14);
    return i - 1;
}
void convertSolar2Lunar(int dd, int mm, int yy, double timeZone) {    //Ham chuyen tu ngay duong lich sang ngay am lich bang cach su dung cac ham da goi o tren
    int k, dayNumber, monthStart, a11, b11, lunarDay, lunarMonth, lunarYear, lunarLeap;
    dayNumber = jdFromDate(dd, mm, yy);
    k = (int)((dayNumber - 2415021.076998695) / 29.530588853);
    monthStart = (int)getNewMoonDay(k + 1, timeZone);
    if (monthStart > dayNumber) {
        monthStart = (int)getNewMoonDay(k, timeZone);
    }
    a11 = (int)getLunarMonth11(yy, timeZone);
    b11 = a11;
    if (a11 >= monthStart) {
        lunarYear = yy;
        a11 = (int)getLunarMonth11(yy - 1, timeZone);
    } else {
        lunarYear = yy + 1;
        b11 = (int)getLunarMonth11(yy + 1, timeZone);
    }
    lunarDay = dayNumber - monthStart - 2; // nếu sai ngày âm xem tại đây, ban đầu bằng +1
    int diff = (int)((monthStart - a11) / 29);
    lunarLeap = 0;
    lunarMonth = diff + 11;
    if (b11 - a11 > 365) {
        int leapMonthDiff = getLeapMonthOffset(a11, timeZone);
        if (diff >= leapMonthDiff) {
            lunarMonth = diff + 10;
            if (diff == leapMonthDiff) {
                lunarLeap = 1;
            }
        }
    }
    if (lunarMonth > 12) {
        lunarMonth = lunarMonth - 12;
    }
    if (lunarMonth >= 11 && diff < 4) {
        lunarYear -= 1;
    }
    int thu_tu_can = lunarYear%10;
    int thu_tu_chi = lunarYear%12;
    sprintf(str4,"Lunar %.2d/%.2d/%s %s",lunarDay, lunarMonth ,can[thu_tu_can],chi[thu_tu_chi]);
    draw_string(20, 140, COLOR_BLACK, 1, str4);
}

