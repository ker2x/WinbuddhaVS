/*
 * Copyright (c) 2010, Emilio Del Tessandoro
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY EMILIO DEL TESSANDORO o ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL EMILIO DEL TESSANDORO BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef BuddhaGenerator_H
#define BuddhaGenerator_H

#include <string>
#include <vector>
#include <cmath>
#include <cfloat>
#include <stdlib.h>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSemaphore>
#include <QImage>
#include <cstdio>
#include <iostream>
#include "buddha.h"
#include "random.h"
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



class BuddhaGenerator : public QThread {
public:	
	// general data and utility functions
	Buddha* b;
	BuddhaGenerator( )   { raw = NULL; }
	~BuddhaGenerator( )  { delete[] raw; }

	void initialize ( Buddha* b );

	// for the raw image and the sequence of points
	vector<complex<double>> seq;
	unsigned int* raw;
	
	void drawPoint ( complex<double>& c, bool r, bool g, bool b );
	int inside ( complex<double>& c );
	int evaluate ( complex<double>& begin, double& distance, unsigned int& contribute, unsigned int& calculated );
	int findPoint ( complex<double>& begin, double& centerDistance, unsigned int& contribute, unsigned int& calculated );
	int metropolis();
	
	// things for the random stuff
	unsigned long int seed;
	Random generator;
	
	void gaussianMutation ( complex<double>& z, double radius );
	void exponentialMutation ( complex<double>& z, double radius );
	
	// for the synchronization and for controlling the execution
	QMutex mutex;
	QWaitCondition resumeCondition;		// this is to stop the Worker and wait for the resume signal
	CurrentStatus status;
	
	void pause ( );
	void stop ( );
	void resume ( );
	bool flow ( );	 // test if we have to stop, pause or whatever
	void run ( );	
};

#endif


