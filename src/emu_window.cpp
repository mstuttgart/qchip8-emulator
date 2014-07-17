#include "emu_window.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////

EmuWindow::EmuWindow()
{

	// Inicializamos os menus
	createActions();
	createMenus();

	//--------------------------------------------------------

	chip8System = new Chip8System ( &chip8CPU, this );

	// Setamos a cor de fundo e a cor do pixel
	slotDefaultTheme();
	//chip8System->setBackgroundColor ( "#212435" );
	//chip8System->setPixelColor ( "#b3e19c" );

	// Setamos o widget central da QMainWindow
	setCentralWidget ( chip8System );

	// Titulo da janela
	setWindowTitle ( tr ( "QChip8 Emulator" ) );

	// Icone janela
	setWindowIcon ( QIcon ( QPixmap ( "../image/drawing.svg" ) ) );

	resize ( chip8System->getPixelSize() * 64,
	         chip8System->getPixelSize() * 32 + fileMenu->height() );

}

////////////////////////////////////////////////////////////////////////////

EmuWindow::~EmuWindow()
{
	delete chip8System;
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotOpen()
{
	// Retorna o caminho do arquivo no sistema
	QString fileName =
	    QFileDialog::getOpenFileName (
	        this, tr ( "Open file" ), "", tr ( "Chip8 Roms(*.ch8 *.c8 *);;" ) );

	// Sera vazio caso o usuario clique em cancelar
	if ( !fileName.isEmpty() ) {

		QFile file ( fileName );

		if ( !file.open ( QIODevice::ReadOnly ) ) {

			// Caso o arquivo nao pode ser aberto
			QMessageBox::critical ( this, tr ( "ERROR" ), tr ( "Could not open file!" ) );
			return;

		}

		if ( !chip8CPU.load ( fileName.toStdString() ) ) {
			std::cout << "ROM loaded fail!" << std::endl;
			file.close();
			return;
		}

		// Usado para capturarmos o nome do arquivo sem o path
		QFileInfo fileInfo ( file.fileName() );
		QString filename ( fileInfo.fileName() );

		std::cout << filename.toStdString() << " ROM loaded with success!" << std::endl;

		// Mudamos o titulo da janela
		this->setWindowTitle ( filename );

		// Iniciamos a emulacao
		chip8System->startEmulation();

		// Ativamos a funcao de pausar
		pauseResumeAction->setEnabled ( true );

		file.close();
	}
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotQuit()
{
	//return;
	chip8System->stopEmulation();
	close();
}

////////////////////////////////////////////////////////////////////////////


void EmuWindow::slotPlayResume()
{
	
	if ( chip8System->isPaused() ) {
		chip8System->resumeEmulation();
		pauseResumeAction->setIcon ( QIcon::fromTheme ( "media-playback-pause" ) );
		return;
	}

	chip8System->pauseEmulation();
	pauseResumeAction->setIcon ( QIcon::fromTheme ( "media-playback-start" ) );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotSoftReset()
{
	chip8CPU.softReset();
	chip8System->updateScreen();
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotHardReset()
{
	chip8CPU.hardReset();
	chip8System->stopEmulation();
	pauseResumeAction->setEnabled( false );
	chip8System->updateScreen();
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotSound()
{
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotWindowSize0x05()
{
	chip8System->setPixelSize ( 0.5 * chip8System->getDefaultPixelSize() );

	resize ( chip8System->getPixelSize() * 64,
	         chip8System->getPixelSize() * 32 + menuBar()->height() );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotWindowSize0x1()
{
	chip8System->setPixelSize ( 1 * chip8System->getDefaultPixelSize() );

	resize ( chip8System->getPixelSize() * 64,
	         chip8System->getPixelSize() * 32 + menuBar()->height() );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotWindowSize0x2()
{
	chip8System->setPixelSize ( 2 * chip8System->getDefaultPixelSize() );

	resize ( chip8System->getPixelSize() * 64,
	         chip8System->getPixelSize() * 32 + menuBar()->height() );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotTelmacCosmapTheme()
{
	chip8System->setBackgroundColor ( "#000000" );
	chip8System->setPixelColor ( "#ffffff" );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotDefaultTheme()
{
	chip8System->setBackgroundColor ( "#212435" );
	chip8System->setPixelColor ( "#ddff55" );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotHP48Theme()
{
	chip8System->setBackgroundColor ( "#cadd5c" );
	chip8System->setPixelColor ( "#3c4176" );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotYellowBlueTheme()
{
	chip8System->setBackgroundColor ( "#3c4176" );
	chip8System->setPixelColor ( "#cadd5c" );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotLaraGTheme()
{
	chip8System->setBackgroundColor ( "#d2d4e0" );
	chip8System->setPixelColor ( "#b841a3" );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::slotAbout()
{
	QMessageBox::about ( this, tr ( "About QChip8 Emulator" ),
	                     tr ( "<p>The <b>QChip8 Emulator</b> is a "
	                          "freeware open source RCA COSMAC VIP emulator and "
	                          "CHIP-8 interpreter for Microsoft Windows and GNU Linux, "
							  "implemented with Qt4 framework."
	                          "<p>QChip8 Emulator may be freely distributed, not for commercial purposes."
	                          "If you want to reuse anything, go ahead, as long as you credit me, "
	                          "and your project is open source too.</p>"
	                          "<p>Developer: Michell Stuttgart</p>"
	                          "<p>Contact: michellstut@gmail.com</p>"
							  "<p>Internal RCA COSMAC VIP Operating System, "
							  "CHIP-8 interpreters (C) Joseph Weisbecker 1977-1990(?)</p>") );

}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::createActions()
{
	// Alocamos os acionadores de acao
	openAction = new QAction ( QIcon::fromTheme ( "document-open" ), tr ( "&Open ROM image.." ), this );
	exitAction = new QAction ( QIcon::fromTheme ( "application-exit" ), tr ( "&Quit" ), this );

	openAction->setShortcut ( tr ( "Ctrl+O" ) );
	exitAction->setShortcut ( tr ( "Ctrl+Q" ) );

	connect ( openAction, SIGNAL ( triggered() ), this, SLOT ( slotOpen() ) );
	connect ( exitAction, SIGNAL ( triggered() ), this, SLOT ( slotQuit() ) );

	//------------------------------------------------------------

	pauseResumeAction = new QAction ( QIcon::fromTheme ( "media-playback-start" ), tr ( "&Run/Pause" ), this );
	soundAction      = new QAction ( tr ( "&Sound" ), this );
	softResetAction  = new QAction ( QIcon::fromTheme ( "view-refresh" ), tr ( "&Soft Reset" ), this );
	hardResetAction  = new QAction ( QIcon::fromTheme ( "system-reboot" ), tr ( "&Hard Reset" ), this );

	pauseResumeAction->setEnabled ( false );

	pauseResumeAction->setShortcut ( tr ( "Space" ) );
	softResetAction->setShortcut ( tr ( "Ctrl+U" ) );
	hardResetAction->setShortcut ( tr ( "Ctrl+R" ) );

	soundAction->setCheckable ( true );
	soundAction->setChecked ( true );

	connect ( pauseResumeAction, SIGNAL ( triggered() ), this, SLOT ( slotPlayResume() ) );
	connect ( soundAction,  SIGNAL ( triggered() ), this, SLOT ( slotSound() ) );
	connect ( softResetAction,  SIGNAL ( triggered() ), this, SLOT ( slotSoftReset() ) );
	connect ( hardResetAction,  SIGNAL ( triggered() ), this, SLOT ( slotHardReset() ) );

	//--------------------------------------------------------------

	windowSizeActionGroup = new QActionGroup ( this );

	windowSizeAction_x05 = new QAction ( tr ( "x0.5" ), windowSizeActionGroup );
	windowSizeAction_x1  = new QAction ( tr ( "x1" ),   windowSizeActionGroup );
	windowSizeAction_x2  = new QAction ( tr ( "x2" ),   windowSizeActionGroup );

	// Elemento x1 é default
	windowSizeAction_x1->setCheckable ( true );
	windowSizeAction_x1->setChecked ( true );

	windowSizeAction_x05->setCheckable ( true );
	windowSizeAction_x05->setChecked ( false );

	windowSizeAction_x2->setCheckable ( true );
	windowSizeAction_x2->setChecked ( false );

	windowSizeActionGroup->addAction ( windowSizeAction_x05 );
	windowSizeActionGroup->addAction ( windowSizeAction_x1 );
	windowSizeActionGroup->addAction ( windowSizeAction_x2 );

	connect ( windowSizeAction_x05, SIGNAL ( triggered() ), this, SLOT ( slotWindowSize0x05() ) );
	connect ( windowSizeAction_x1, SIGNAL ( triggered() ),  this, SLOT ( slotWindowSize0x1() ) );
	connect ( windowSizeAction_x2, SIGNAL ( triggered() ),  this, SLOT ( slotWindowSize0x2() ) );

	//-----------------------------------------------

	presetActionGroup = new QActionGroup ( this );

	defaltPresetAction       = new QAction ( tr ( "Default" ), presetActionGroup );
	telmacCosmapPresetAction = new QAction ( tr ( "TELMAC/COSMAP" ), presetActionGroup );
	hp48PresetAction         = new QAction ( tr ( "HP48" ), presetActionGroup );
	color01PresetAction      = new QAction ( tr ( "YellowBlues" ), presetActionGroup );
	laragPresetAction        = new QAction ( tr ( "LaraG" ), presetActionGroup );

	// Elemento x1 é default
	defaltPresetAction->setCheckable ( true );
	defaltPresetAction->setChecked ( true );

	telmacCosmapPresetAction->setCheckable ( true );
	telmacCosmapPresetAction->setChecked ( false );

	hp48PresetAction->setCheckable ( true );
	hp48PresetAction->setChecked ( false );

	color01PresetAction->setCheckable ( true );
	color01PresetAction->setChecked ( false );

	laragPresetAction->setCheckable ( true );
	laragPresetAction->setChecked ( false );

	presetActionGroup->addAction ( defaltPresetAction );
	presetActionGroup->addAction ( telmacCosmapPresetAction );
	presetActionGroup->addAction ( hp48PresetAction );
	presetActionGroup->addAction ( color01PresetAction );
	presetActionGroup->addAction ( laragPresetAction );

	connect ( defaltPresetAction, SIGNAL ( triggered() ), this, SLOT ( slotDefaultTheme() ) );
	connect ( telmacCosmapPresetAction, SIGNAL ( triggered() ),  this, SLOT ( slotTelmacCosmapTheme() ) );
	connect ( hp48PresetAction, SIGNAL ( triggered() ),  this, SLOT ( slotHP48Theme() ) );
	connect ( color01PresetAction, SIGNAL ( triggered() ),  this, SLOT ( slotYellowBlueTheme() ) );
	connect ( laragPresetAction, SIGNAL ( triggered() ),  this, SLOT ( slotLaraGTheme() ) );

	//---------------------------------------------------------------

	aboutAction   = new QAction ( QIcon::fromTheme ( "system-help" ), tr ( "&About" ), this );
	aboutQtAction = new QAction ( tr ( "About &Qt" ), this );

	aboutAction->setShortcut ( tr ( "Ctrl+H" ) );

	connect ( aboutAction,   SIGNAL ( triggered() ), this, SLOT ( slotAbout() ) );
	connect ( aboutQtAction, SIGNAL ( triggered() ), qApp, SLOT ( aboutQt() ) );

}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::createMenus()
{
	// Configuramos a barra de menu

	// Menu file
	fileMenu = new QMenu ( tr ( "&File" ), this );
	fileMenu->addAction ( openAction );
	fileMenu->addSeparator();
	fileMenu->addAction ( exitAction );

	// Menu emulation
	emulationMenu = new QMenu ( tr ( "E&mulation" ), this );

	emulationMenu->addAction ( pauseResumeAction );
	emulationMenu->addSeparator();
	emulationMenu->addAction ( soundAction );
	emulationMenu->addSeparator();
	emulationMenu->addAction ( softResetAction );
	emulationMenu->addAction ( hardResetAction );

	// Menu view
	viewMenu        = new QMenu ( tr ( "V&iew" ), this );
	windowSizeMenu  = new QMenu ( tr ( "&Window size" ), this );
	colorPresetMenu = new QMenu ( tr ( "&Theme" ), this );

	windowSizeMenu->addAction ( windowSizeAction_x05 );
	windowSizeMenu->addAction ( windowSizeAction_x1 );
	windowSizeMenu->addAction ( windowSizeAction_x2 );

	windowSizeMenu->setIcon ( QIcon::fromTheme ( "zoom-in" ) );

	colorPresetMenu->addAction ( defaltPresetAction );
	colorPresetMenu->addSeparator();
	colorPresetMenu->addAction ( telmacCosmapPresetAction );
	colorPresetMenu->addAction ( hp48PresetAction );
	colorPresetMenu->addAction ( color01PresetAction );
	colorPresetMenu->addAction ( laragPresetAction );

	viewMenu->addMenu ( windowSizeMenu );
	viewMenu->addMenu ( colorPresetMenu );

	// Menu help
	helpMenu = new QMenu ( tr ( "&Help" ), this );
	helpMenu->addAction ( aboutAction );
	helpMenu->addAction ( aboutQtAction );

	// Adicionamos o menus na barra de menis
	menuBar()->addMenu ( fileMenu );
	menuBar()->addMenu ( emulationMenu );
	menuBar()->addMenu ( viewMenu );
	menuBar()->addMenu ( helpMenu );

}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::keyPressEvent ( QKeyEvent* event )
{
	chip8System->keyPress ( event );
}

////////////////////////////////////////////////////////////////////////////

void EmuWindow::keyReleaseEvent ( QKeyEvent* event )
{
	chip8System->keyRelease ( event );
}

////////////////////////////////////////////////////////////////////////////
