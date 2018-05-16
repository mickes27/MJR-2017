#pragma once
#include "UDP.hpp"


/*
Klasa obs³uguj¹ca silnik krokowy.
Okreœlamy pin, na którym znajduje siê silnik oraz jego kierunek. W celu kontroli prêdkoœci okreœlamy tak¿e liczbê kroków na obrót
Ruch nastêpuje poprzez podanie sygna³u PWM o odpowiedniej czêstotliwoœci
*/

class CStepEngine
{
public:
	CStepEngine(int pul, int dir, int microsteps, int speed, CUDP* conn);
	~CStepEngine();

private:
	int iPul;                                                               //--- Pin do którego podpiêty jest silnik
	int iDir;                                                               //--- Kierunek obrotu silnika
	int iSpeed;															//--- Predkosc w obrotach na sekunde
	int iMicroSteps;                                                        //--- Liczba kroków na obrót
	CUDP* connection;
public:
	void MoveEngine(int speed);
	int UpdatePulseWidth(int freq, int width);                              //--- Aktualizacja PWM silnika
	int CalculateFreq(int speed); 										//--- Oblicza wymagan¹ czêstotliwoœæ PWM, aby osi¹gn¹æ zadan¹ prêdkoœæ w obr/sec (UWAGA: czêstotliwoœci s¹ skwantowane!)
	void UpdateDir(int state);                                         		//--- Puszcza sygnal na DIR
	void SetPul(int pul);                                                   //--- Setter pinu
	void SetDir(int dir);                                                   //--- Setter kierunku
	void SetSpeed(int speed);												//--- Setter predkosci
	void SetMicroSteps(int microsteps);                                     //--- Setter liczby kroków na obrót
	inline int GetPul() const { return iPul; }                              //--- Getter pinu
	inline int GetDirection() const { return iDir; }                        //--- Getter kierunku
	inline int GetSpeed() const { return iSpeed; }						//--- Getter predkosci
	inline int GetMicroSteps() const { return iMicroSteps; }                //--- Getter liczby kroków na obrót
};