#pragma once
#include "UDP.hpp"

/*
Klasa obs�uguj�ca serwomechanizm.
Okre�lamy pin, na kt�rym znajduje si� serwomechanizm oraz jego granice (�eby nie zniszczy� serwa przekraczaj�c zakres) - wszystko w ms.
Nast�pnie okre�lamy krok, o jaki ma si� rusza� serwomechanizm.

Ruch nast�puje przez ruch serwa w prawo lub lewo w zale�no�ci od podania mu szeroko�ci impulsu.
*/

class CServo
{
public:
	CServo(int pin, int pulsewidth, int upperlimit, int lowerlimit, int stepsize, CUDP* conn);
	~CServo();

private:
	int iPin;                                                               //--- Pin do kt�rego podpi�ty jest serwomechanizm
	int iPulseWidth;                                                        //--- Szeroko�� wype�nienia impulsu (zazwyczaj 1000-2000)
	int iUpperLimit;                                                        //--- G�rny limit serwomechanizmu (zazwyczaj 2000)
	int iLowerLimit;                                                        //--- Dolna granica serwomechanizmu (zazywczaj 1000)
	int iStepSize;                                                          //--- Szeroko�� kroku      
	CUDP* connection;
public:
	int UpdatePulseWidth();													//--- Aktualizacja wype�nienia serwa
	int SetPulseWidth(int pulseWidth);                                      //--- Ustawienie wype�nienia serwa
	inline int GetCurrentPulseWidth() const { return iPulseWidth; }         //--- Getter aktualnego wype�nienia serwomechanizmu
	inline int GetStepSize() const { return iStepSize; }                    //--- Getter aktualnego kroku serwa
	inline int GetLowerLimit() const { return iLowerLimit; }  				//--- Getter limitu serwa
	inline int GetUpperLimit() const { return iUpperLimit; }  				//--- Getter limitu serwa
	inline int GetPin() const { return iPin; }  				//--- Getter pinu
};