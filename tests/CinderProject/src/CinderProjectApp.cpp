#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppBasic {
  public:
	void setup();
	void update();
	void draw();

	void mouseDown( MouseEvent event );
    
    void prepareSettings( Settings *settings );
  private:
    gl::Texture myImage;

};

void CinderProjectApp::setup()
{
    myImage = gl::Texture( loadImage( loadResource( "image.png" ) ) );
}

void CinderProjectApp::update()
{
}

void CinderProjectApp::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) );
    //gl::clear( Color( 1, 0, 0 ), true );
    
    float gray = sin( getElapsedSeconds() ) * 0.5f + 0.5f;
    gl::clear( Color( gray, gray, gray ), true );
    
    gl::draw( myImage, getWindowBounds() );
    
    gl::drawSolidCircle( Vec2f( 350.0f, 150.0f ), 50.0f, 7 );
    
    float x = cos( getElapsedSeconds() ) * 100.0f;
    float y = sin( getElapsedSeconds() ) * 100.0f;
    gl::drawSolidCircle( Vec2f( x, y ) + getWindowSize() / 2, abs( x ) );
}

void CinderProjectApp::mouseDown( MouseEvent event )
{
}

void CinderProjectApp::prepareSettings( Settings *settings ){
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}

CINDER_APP_BASIC( CinderProjectApp, RendererGl )
