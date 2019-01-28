/*
  File:         Normal_Distribution.cpp
  Version:      0.0.1
  Date:         23-Jan-2019
  Revision:     23-Jan-2019
  Author:       Jerome Drouin (jerome.p.drouin@gmail.com)

  Editions:	Please go to Normal_Distribution.h for Edition Notes.

  Normal_Distribution.cpp - Library for 'duino
  https://github.com/newEndeavour/Normal_Distribution

  Normal_Distribution implements a Normal Gaussian distribution. 

  Copyright (c) 2018-2019 Jerome Drouin  All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "Arduino.h"
#include "Normal_Distribution.h"


// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Normal_Distribution::Normal_Distribution(float _Mu, float _Sigma)
{

	// Object parameter's error handling
	error = 1;

	//Set initial values	
	Mu			= _Mu;			// 
	Sigma			= _Sigma;		//

}


// Public Methods //////////////////////////////////////////////////////////////
//Probability Density Function
float Normal_Distribution::GetPDF(float x)
{

    //return exp(-pow(x - Mu,2) / 2 * pow(Sigma,2)) / sqrt(2 * CONSTANT_Pi * pow(Sigma,2));
    return exp(-pow(x,2) / 2) / sqrt(2 * CONSTANT_Pi);

}

//Density square
float Normal_Distribution::GetPDF_2(float x)
{

    return -x * exp(-x * x / 2) / sqrt(2 * CONSTANT_Pi);

}

//Cumulative Distribution Function
float Normal_Distribution::GetCDF(float x)
{
float t;
float y;
float z;

    if (abs(x) < 13) {
        y = 1 / (1 + CONSTANT_aa * abs(x));
        z = CONSTANT_b1 * pow(y,5) - CONSTANT_b2 * pow(y,4) + CONSTANT_b3 * pow(y,3) - CONSTANT_b4 * pow(y,2) + CONSTANT_b5 * y;
        t = 1 - (z * exp(-x * x / 2) / sqrt(2 * CONSTANT_Pi));
    } 
    else {
        t = 1;
    }
            
    if (x >= 0) {
        return t;
    } else {
        return 1 - t;
    }
}


//Return Quantile z(P) from probability P
float Normal_Distribution::GetQuantile(float p)
{
float Vm;
float Vh = 16;
float Vl = -16;
float Pr;
int i = 0;
float Eps;

	if (p <= 0.0) {
		return Vl;
	} else if (p >= 1.0) {
        	return Vh;
	} else {        
        	do 
		{
          		i++;
          		Vm = (Vh + Vl) / 2;
            
			Pr = GetCDF(Vm);
          		Eps = abs(Pr - p);
			
			/*
			//DEBUG
			Serial.print("\nF(x) | ");
			Serial.print("i:");
			Serial.print(i);
			Serial.print("\tVl:");
			Serial.print(Vl,4);
			Serial.print("\tVh:");
			Serial.print(Vh,4);
			Serial.print("\tVm:");
			Serial.print(Vm,4);
			Serial.print("\t ->F(Vm):");
			Serial.print(Pr,4);
			Serial.print("\t ->Eps:");
			Serial.print(Eps,4);
			*/
        
          		//New Boundary selection
          		if (Pr > p) {
				Vh = Vm;
				//Serial.print("\t (Pr > p) Vh=Vm->Vh:");
				//Serial.print(Vh,4);
          		} else {
				Vl = Vm;
				//Serial.print("\t (Pr < p) Vl=Vm->Vl:");
				//Serial.print(Vl,4);
			}
            
        	} 
		while ((Eps > CONSTANT_EpsStop) && (i < 70));
	}
            
        if (i >= 70) {
            return -9999;
        } else {
            return Vm;
    	}

}


float Normal_Distribution::GetMu(void)
{
	return Mu;
}


float Normal_Distribution::GetSigma(void)
{
	return Sigma;
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


// /////////////////////////////////////////////////////////////////////////////

