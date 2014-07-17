#ifndef EMUDISPLAY_HPP
#define EMUDISPLAY_HPP

#include <QWidget>
#include <QKeyEvent>
#include <string>
#include "chip8_cpu.hpp"

#define PIXEL_SIZE	8

class Chip8System : public QWidget
{
	Q_OBJECT

private:

	Chip8_CPU* chip8Emu;
	const bool* chip8Display;

	int pixelSize;
	int timerId;
	bool started;
	bool paused;

	QColor pixelPen;
	QBrush pixelBrush;
	
	QImage image;

protected:
	void paintEvent ( QPaintEvent* event );
	void timerEvent ( QTimerEvent* event );

	void renderChip8Display( QPainter* painter );
	void renderSplashScreen( QPainter* painter );

public:

	Chip8System ( Chip8_CPU* _chip8Emu, QWidget *parent = 0 );

	virtual ~Chip8System();

	void keyPress ( QKeyEvent *event );
	void keyRelease ( QKeyEvent *event );

	void startEmulation();
	void resumeEmulation();
	void pauseEmulation();
	void stopEmulation();

	bool isPaused() const;
	bool isStarted() const;

	void setInterval ( int value );
	void setPixelSize ( int value );

	int getPixelSize() const;
	int getDefaultPixelSize();

	void setBackgroundColor ( const std::string nameColor );
	void setPixelColor ( const std::string nameColor );
	
	void updateScreen();
	
};

#endif // EMUDISPLAY_HPP
