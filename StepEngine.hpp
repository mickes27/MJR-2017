#pragma once
#include "UDP.hpp"


/*
Klasa obs�uguj�ca silnik krokowy.
Okre�lamy pin, na kt�rym znajduje si� silnik oraz jego kierunek. W celu kontroli pr�dko�ci okre�lamy tak�e liczb� krok�w na obr�t
Ruch nast�puje poprzez podanie sygna�u PWM o odpowiedniej cz�stotliwo�ci
*/

class CStepEngine
{
public:
	CStepEngine(int pul, int dir, int microsteps, int speed, CUDP* conn);
	~CStepEngine();

private:
	int iPul;                                                               //--- Pin do kt�rego podpi�ty jest silnik
	int iDir;                                                               //--- Kierunek obrotu silnika
	int iSpeed;															//--- Predkosc w obrotach na sekunde
	int iMicroSteps;                                                        //--- Liczba krok�w na obr�t
	CUDP* connection;
public:
	void MoveEngine(int speed);
	int UpdatePulseWidth(int freq, int width);                              //--- Aktualizacja PWM silnika
	int CalculateFreq(int speed); 										//--- Oblicza wymagan� cz�stotliwo�� PWM, aby osi�gn�� zadan� pr�dko�� w obr/sec (UWAGA: cz�stotliwo�ci s� skwantowane!)
	void UpdateDir(int state);                                         		//--- Puszcza sygnal na DIR
	void SetPul(int pul);                                                   //--- Setter pinu
	void SetDir(int dir);                                                   //--- Setter kierunku
	void SetSpeed(int speed);												//--- Setter predkosci
	void SetMicroSteps(int microsteps);                                     //--- Setter liczby krok�w na obr�t
	inline int GetPul() const { return iPul; }                              //--- Getter pinu
	inline int GetDirection() const { return iDir; }                        //--- Getter kierunku
	inline int GetSpeed() const { return iSpeed; }						//--- Getter predkosci
	inline int GetMicroSteps() const { return iMicroSteps; }                //--- Getter liczby krok�w na obr�t
};