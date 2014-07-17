#include "chip8_system.hpp"

#include <QPainter>

using namespace std;

////////////////////////////////////////////////////////////////////////////

Chip8System::Chip8System ( Chip8_CPU* _chip8Emu, QWidget *parent ) :
	QWidget ( parent ), chip8Display ( _chip8Emu->getDisplay() )
{

	chip8Emu  = _chip8Emu;
	pixelSize = 8;

	started = false;
	paused  = false;

	image.load ( "../image/space.png" );
	
}

////////////////////////////////////////////////////////////////////////////

Chip8System::~Chip8System()
{
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::paintEvent ( QPaintEvent* event )
{
	Q_UNUSED ( event );

	QPainter painter ( this );

	// Contorno dos retangulos
	painter.setPen ( pixelPen );
	painter.setBrush ( pixelBrush );

	if ( !started && !paused ) {
		renderSplashScreen ( &painter );
		return;
	}

	renderChip8Display ( &painter );

}

////////////////////////////////////////////////////////////////////////////

void Chip8System::timerEvent ( QTimerEvent* event )
{
	event->accept();
	chip8Emu->fetch();
	chip8Emu->execute();
	repaint();
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::keyPress ( QKeyEvent* event )
{

	switch ( event->key() ) {

		case Qt::Key_1:
			chip8Emu->setKey ( 0x1, true );
			break;

		case Qt::Key_2:
			chip8Emu->setKey ( 0x2, true );
			break;

		case Qt::Key_3:
			chip8Emu->setKey ( 0x3, true );
			break;

		case Qt::Key_4:
			chip8Emu->setKey ( 0xC, true );
			break;

			//--------------------------------

		case Qt::Key_Q:
			chip8Emu->setKey ( 0x4, true );
			break;

		case Qt::Key_W:
			chip8Emu->setKey ( 0x5, true );
			break;

		case Qt::Key_E:
			chip8Emu->setKey ( 0x6, true );
			break;

		case Qt::Key_R:
			chip8Emu->setKey ( 0xE, true );
			break;

			//--------------------------------

		case Qt::Key_A:
			chip8Emu->setKey ( 0x7, true );
			break;

		case Qt::Key_S:
			chip8Emu->setKey ( 0x8, true );
			break;

		case Qt::Key_D:
			chip8Emu->setKey ( 0x9, true );
			break;

		case Qt::Key_F:
			chip8Emu->setKey ( 0XE, true );
			break;

			//--------------------------------

		case Qt::Key_Z:
			chip8Emu->setKey ( 0xA, true );
			break;

		case Qt::Key_X:
			chip8Emu->setKey ( 0x0, true );
			break;

		case Qt::Key_C:
			chip8Emu->setKey ( 0x0, true );
			break;

		case Qt::Key_V:
			chip8Emu->setKey ( 0xF, true );
			break;

			//--------------------------------

		case Qt::Key_P:
			if ( !event->isAutoRepeat() )
				pauseEmulation();

			break;

		case Qt::Key_Space:
			if ( !event->isAutoRepeat() )
				startEmulation();

			break;

		default:
			QWidget::keyPressEvent ( event );

	}//switch
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::keyRelease ( QKeyEvent* event )
{
	switch ( event->key() ) {

		case Qt::Key_1:
			chip8Emu->setKey ( 0x1, false );
			break;

		case Qt::Key_2:
			chip8Emu->setKey ( 0x2, false );
			break;

		case Qt::Key_3:
			chip8Emu->setKey ( 0x3, false );
			break;

		case Qt::Key_4:
			chip8Emu->setKey ( 0xC, false );
			break;

			//--------------------------------

		case Qt::Key_Q:
			chip8Emu->setKey ( 0x4, false );
			break;

		case Qt::Key_W:
			chip8Emu->setKey ( 0x5, false );
			break;

		case Qt::Key_E:
			chip8Emu->setKey ( 0x6, false );
			break;

		case Qt::Key_R:
			chip8Emu->setKey ( 0xE, false );
			break;

			//--------------------------------

		case Qt::Key_A:
			chip8Emu->setKey ( 0x7, false );
			break;

		case Qt::Key_S:
			chip8Emu->setKey ( 0x8, false );
			break;

		case Qt::Key_D:
			chip8Emu->setKey ( 0x9, false );
			break;

		case Qt::Key_F:
			chip8Emu->setKey ( 0XE, false );
			break;

			//--------------------------------

		case Qt::Key_Z:
			chip8Emu->setKey ( 0xA, false );
			break;

		case Qt::Key_X:
			chip8Emu->setKey ( 0x0, false );
			break;

		case Qt::Key_C:
			chip8Emu->setKey ( 0x0, false );
			break;

		case Qt::Key_V:
			chip8Emu->setKey ( 0xF, false );
			break;

		default:
			QWidget::keyReleaseEvent ( event );

	}//switch
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::startEmulation()
{
	if ( started )
		return;

	started = true;
	timerId = startTimer ( 5 );
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::resumeEmulation()
{
	if ( !paused || !started )
		return;

	timerId = this->startTimer ( 5 );
	paused  = false;

}

////////////////////////////////////////////////////////////////////////////

void Chip8System::pauseEmulation()
{
	if ( !started )
		return;

	paused = true;
	killTimer ( timerId );

}

////////////////////////////////////////////////////////////////////////////

void Chip8System::stopEmulation()
{
	this->killTimer ( timerId );
	started = false;
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::setInterval ( int value )
{
	timerId = value;
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::setPixelSize ( int value )
{
	pixelSize = value;
}

int Chip8System::getPixelSize() const
{
	return pixelSize;
}

////////////////////////////////////////////////////////////////////////////

int Chip8System::getDefaultPixelSize()
{
	return PIXEL_SIZE;
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::setBackgroundColor ( const std::string nameColor )
{
	QPalette p ( palette() );
	p.setColor ( QPalette::Background, nameColor.c_str() );
	this->setAutoFillBackground ( true );
	this->setPalette ( p );
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::setPixelColor ( const std::string nameColor )
{
	this->pixelBrush = QBrush ( nameColor.c_str() );
	this->pixelPen   = QColor ( nameColor.c_str() );
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::renderChip8Display ( QPainter* painter )
{
	int line;
	int mult;

	// Draw
	for ( int y = 0; y < 32; y++ ) {

		line = y * pixelSize;
		mult = y << 6; //*64

		for ( int x = 0; x < 64; x++ ) {

			if ( chip8Display[ mult + x ] != 0 )
				painter->drawRect ( x * pixelSize, line, pixelSize, pixelSize );

		}//for

	}//for
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::renderSplashScreen ( QPainter* painter )
{
	QRect rect = painter->viewport();
	QSize size = image.size();
	size.scale ( rect.size(), Qt::KeepAspectRatio );
	painter->setViewport ( rect.width() * 0.5  - size.width() * 0.5,
	                       rect.height() * 0.5 - size.height() * 0.5,
	                       size.width(), size.height() );

	painter->drawImage ( rect, image );
}

////////////////////////////////////////////////////////////////////////////

bool Chip8System::isPaused() const
{
	return paused;
}

////////////////////////////////////////////////////////////////////////////

bool Chip8System::isStarted() const
{
	return started;
}

////////////////////////////////////////////////////////////////////////////

void Chip8System::updateScreen()
{
	repaint();
}

////////////////////////////////////////////////////////////////////////////