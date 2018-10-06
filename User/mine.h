#ifndef _MINE_H_
#define _MINE_H_

//速度式
void SABCD(long int MotoASpeed,long int MotoBSpeed,long int MotoCSpeed,long int MotoDSpeed);
uint16_t filter(uint16_t in);
void Go(long int speed,long int time);
void Stop(void);
void Back(long int speed,long int time);
void TurnLeft(long int speed,long int time);
void TurnRight(long int speed,long int time);
void LGo(long int speed,long int time);
void RGo(long int speed,long int time);
void Left(long int speed,long int time);
void Right(long int speed,long int time);

void delayy(int time);
void walk(long int Runtime,long int Alltime);
void walk2(long int Runtime,long int Alltime);
void walk3(long int Runtime,long int Alltime);
void walk4(long int Runtime,long int Alltime);

//位置式
void GoPosition(long long int x,long long int y,long int time);


void strightL(void);
void strightR(void);


#endif
