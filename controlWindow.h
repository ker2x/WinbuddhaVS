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


#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QtWidgets/QSlider>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QAbstractSpinBox>
#include <QtCore/QVariant>
#include <QtWidgets/QMainWindow>
#include <QtGui/QtGui>
#include "renderWindow.h"
#include "buddha.h"

#define PRECISION	15

static const uint maxLightness = 200;
static const uint maxContrast = 300;
static const uint maxFps = 40;

class ControlWindow : public QMainWindow {
	Q_OBJECT

public:
    double minRe;
	double maxRe;
    double minIm;
    double maxIm;
	double minScale; //should start at 1, not 100 as the contrast/lightness
	double maxScale;
	double step;

	int sleepTime;
    uint lowr, lowg, lowb;
	uint highr, highg, highb;
    int contrast, lightness;
	double fps;
    double cre, cim;
	double scale;
	Buddha* b;

	QWidget *centralWidget;

	QGroupBox *graphBox;
	QGroupBox *buttonsBox;
	QGroupBox *renderBox;

	QDoubleSpinBox *reBox;
	QDoubleSpinBox *imBox;
	QDoubleSpinBox *zoomBox;

    QSpinBox *minRbox;
    QSpinBox *maxRbox;
    QSpinBox *minGbox;
    QSpinBox *maxGbox;
    QSpinBox *minBbox;
    QSpinBox *maxBbox;

	QLabel *iterationRedLabel;
	QLabel *reLabel;
	QLabel *imLabel;
	QLabel *zoomLabel;
	QLabel *iterationGreenLabel;
    QLabel *iterationBlueLabel;
	QLabel *contrastLabel;
	QLabel *lightLabel;
	QLabel *fpsLabel;
	QLabel *threadsLabel;
	QLabel *mouseLabel;

	QSlider *contrastSlider;
	QSlider *lightSlider;
	QSlider *fpsSlider;
	QSlider *threadsSlider;

	QRadioButton *normalZoom;
	QRadioButton *mouseZoom;
	QIcon* icon;

	QMenuBar *menuBar;
	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;
	
	RenderWindow* renderWin;
	

	void createGraphBox ( );
	void createRenderBox ( );
	void createControlBox ( );
	void createMenus( );
	void createActions( );
	void updateFpsLabel( );
	void updateThreadLabel( quint8 );

public:
	QPushButton *resetButton;
	QPushButton *startButton;
	QAction* exitAct, *aboutQtAct, *aboutAct, *screenShotAct, *saveAct, *openAct;

	ControlWindow ( );
	
	bool valuesChanged( );
	static int expVal ( int x ) { return (int) pow( 2.0, x / 2.0 ); }
    double getCre( )	{ return cre; }
    double getCim( )	{ return cim; }
    double getScale( )	{ return scale; }
	void modelToGUI ( );

public slots:
	void handleStartButton( );
    void handleResetButton( );
    void renderWinClosed( );
	void exit( );

    void setMinRIteration(int value);
    void setMinGIteration(int value);
    void setMinBIteration(int value);

    void setMaxRIteration(int value);
    void setMaxGIteration(int value);
    void setMaxBIteration(int value);

	void setLightness( int value );
	void setContrast( int value );
	void setFps( int value );
	void setButtonStart( ) { startButton->setText( tr( "&Start" ) ); }
	void setButtonResume( ) { startButton->setText( tr( "Re&sume" ) ); }
	void setButtonStop( ) { startButton->setText( tr( "&Stop" ) ); }
	void setCre ( double d );
	void setCim ( double d );
	void setScale ( double d );
	void setThreadNum ( int value );
	void about ( );
	void saveScreenshot( );
	void sendValues( bool pause = true );

signals:
	void closed ( );
    void setValues( double cre, double cim, double scale, uint lowr, uint lowg, uint lowb, uint highr, uint highg, uint highb, QSize wsize, bool pause );
	void startCalculation( );
	void stopCalculation( );
	void pauseCalculation( );
	void clearBuffers( );
	void changeThreadNumber( int );
	void screenshotRequest ( QString fileName );

protected:
	void closeEvent ( QCloseEvent* event );
	void showEvent ( QShowEvent* event );
};

#endif

