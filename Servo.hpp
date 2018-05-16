#pragma once
#include "UDP.hpp"

/*
Klasa obs³uguj¹ca serwomechanizm.
Okreœlamy pin, na którym znajduje siê serwomechanizm oraz jego granice (¿eby nie zniszczyæ serwa przekraczaj¹c zakres) - wszystko w ms.
Nastêpnie okreœlamy krok, o jaki ma siê ruszaæ serwomechanizm.

Ruch nastêpuje przez ruch serwa w prawo lub lewo w zale¿noœci od podania mu szerokoœci impulsu.
*/

class CServo
{
public:
	CServo(int pin, int pulsewidth, int upperlimit, int lowerlimit, int stepsize, CUDP* conn);
	~CServo();

private:
	int iPin;                                                               //--- Pin do którego podpiêty jest serwomechanizm
	int iPulseWidth;                                                        //--- Szerokoœæ wype³nienia impulsu (zazwyczaj 1000-2000)
	int iUpperLimit;                                                        //--- Górny limit serwomechanizmu (zazwyczaj 2000)
	int iLowerLimit;                                                        //--- Dolna granica serwomechanizmu (zazywczaj 1000)
	int iStepSize;                                                          //--- Szerokoœæ kroku      
	CUDP* connection;
public:
	int UpdatePulseWidth();													//--- Aktualizacja wype³nienia serwa
	int SetPulseWidth(int pulseWidth);                                      //--- Ustawienie wype³nienia serwa
	inline int GetCurrentPulseWidth() const { return iPulseWidth; }         //--- Getter aktualnego wype³nienia serwomechanizmu
	inline int GetStepSize() const { return iStepSize; }                    //--- Getter aktualnego kroku serwa
	inline int GetLowerLimit() const { return iLowerLimit; }  				//--- Getter limitu serwa
	inline int GetUpperLimit() const { return iUpperLimit; }  				//--- Getter limitu serwa
	inline int GetPin() const { return iPin; }  				//--- Getter pinu
};