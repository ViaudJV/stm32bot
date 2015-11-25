/*
 * PID.h
 *
 *  Created on: 9 août 2015
 *      Author: jul
 */

#ifndef PID_H_
#define PID_H_

class PID {
private:
	float m_Kp;
	float m_Ki;
	float m_Kd;
	float m_max_integral;  //!< saturation de l'integrale
	float m_max_out;       //!< saturation de la sortie
	float m_integral;      //!< valeur courante de l'integrale
	float m_lastError;     //!< derniere valeur pour calculer la derivee


public:
	PID();
	PID(float kp,float ki,float kd,float Max, float max_integral );
	~PID();
	void SetKp(float kp){m_Kp = kp;}
	void SetKi(float ki){m_Ki = ki;}
	void SetKd(float kd){m_Kd = kd;}

	void SetMax(float Max){m_max_out = Max;}
	void SetMAxIntegral(float max_integral){m_max_integral = max_integral;}

	float GetKd(){return m_Kd;}
	float GetKi(){return m_Ki;}
	float GetKp(){return m_Kp;}
	float GetMax(){return m_max_out ;}
	float GetMAxIntegral(){ return m_max_integral;}

	float compute(float error, float dt);
};

#endif /* PID_H_ */
