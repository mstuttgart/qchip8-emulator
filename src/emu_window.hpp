#ifndef EMUWINDOW_HPP
#define EMUWINDOW_HPP

#include <QMainWindow>
#include <QtGui>
#include <QKeyEvent>

#include "chip8_system.hpp"

class EmuWindow : public QMainWindow
{

	Q_OBJECT

public:
	EmuWindow();
	virtual ~EmuWindow();

public slots:

	void slotOpen();
	void slotQuit();

	void slotPlayResume();
	void slotSound();
	void slotSoftReset();
	void slotHardReset();
	
	void slotDefaultTheme();
	void slotTelmacCosmapTheme();
	void slotHP48Theme();
	void slotYellowBlueTheme();
	void slotLaraGTheme();

	void slotWindowSize0x05();
	void slotWindowSize0x1();
	void slotWindowSize0x2();

	void slotAbout();

protected:

	void keyPressEvent ( QKeyEvent *event );
	void keyReleaseEvent ( QKeyEvent *event );
	void createActions();
	void createMenus();

private:

	QAction* openAction;
	QAction* exitAction;

	QAction* pauseResumeAction;
	QAction* stopAction;
	QAction* soundAction;
	QAction* softResetAction;
	QAction* hardResetAction;

	QAction* windowSizeAction_x05;
	QAction* windowSizeAction_x1;
	QAction* windowSizeAction_x2;
	QActionGroup* windowSizeActionGroup;
	
	QAction* defaltPresetAction;
	QAction* telmacCosmapPresetAction;
	QAction* hp48PresetAction;
	QAction* color01PresetAction;
	QAction* laragPresetAction;
	QActionGroup* presetActionGroup;
	
	QAction* aboutAction;
	QAction* aboutQtAction;

	QMenu* fileMenu;
	QMenu* emulationMenu;
	QMenu* viewMenu;
	QMenu* windowSizeMenu;
	QMenu* colorPresetMenu;
	QMenu* helpMenu;

	Chip8System* chip8System;
	Chip8_CPU chip8CPU;

};

#endif // EMUWINDOW_HPP
