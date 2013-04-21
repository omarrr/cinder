#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Vector.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//------------------------------------------------------------------
// QArc
//------------------------------------------------------------------
class QArc : public Path2d {
  public:
    void refresh(float x, float y, float delta, float radius, float thickness);
    float outerRadius();
    float innerRadius();
    
  private:
    float x = 0;
    float y = 0;
    float delta = 0;
    float thickness = 0;
    float radius = 0;
};

float QArc::innerRadius()
{
    return this->radius-this->thickness/2;
};
float QArc::outerRadius()
{
    return this->radius+this->thickness/2;
};
/*
void QArc::refresh2(float x, float y, float delta, float radius, float thickness)
{
    this->x = x;
    this->y = x;
    this->delta = (2*M_PI < delta)?2*M_PI:delta;
    this->radius = radius;
    this->thickness = thickness;
    
    
    //path.arcTo(<#float x#>, <#float y#>, <#float tanX#>, <#float tanY#>, <#float radius#>);
    //path.arc(<#float centerX#>, <#float centerY#>, <#float radius#>, <#float startRadians#>, <#float endRadians#>)
        
    
    this->clear();
    this->moveTo(x, y);
    this->arc(x, y, innerRadius(), 0, this->delta);
    Vec2f p2 = this->getCurrentPoint();
    
    this->clear();

    // out
    this->arc(x, y, outerRadius(), 0, this->delta);
    Vec2f p1 = this->getCurrentPoint();

    // cap
    //this->lineTo(p2);
    
    this->reverse();
    
    this->arc(x, y, innerRadius(), 0, this->delta);
    
    //cap
    //this->close();
    this->arc((p1.x+p2.x)/2, (p1.y+p2.y)/2, thickness/2, this->delta, this->delta+M_PI);
    
    //this->lineTo(x, y);
    
};*/
void QArc::refresh(float x, float y, float delta, float radius, float thickness)
{
    this->x = x;
    this->y = x;
    this->delta = (2*M_PI < delta)?2*M_PI:delta;
    this->radius = radius;
    this->thickness = thickness;
    
    
    //path.arcTo(<#float x#>, <#float y#>, <#float tanX#>, <#float tanY#>, <#float radius#>);
    //path.arc(<#float centerX#>, <#float centerY#>, <#float radius#>, <#float startRadians#>, <#float endRadians#>)
    
    
    this->clear();
    this->moveTo(x, y);
    this->arc(x, y, innerRadius(), 0, this->delta);
    Vec2f p2 = this->getCurrentPoint();

    this->arc(x, y, outerRadius(), 0, this->delta);
    Vec2f p1 = this->getCurrentPoint();
    
    this->clear();
    
    // inner
    this->arc(x, y, innerRadius(), 0, this->delta);
    
    this->reverse();
    
    // outter
    this->arc(x, y, outerRadius(), 0, this->delta);
    
    //cap
    //this->close();
    this->arc((p1.x+p2.x)/2, (p1.y+p2.y)/2, thickness/2, this->delta, this->delta+M_PI);
    
    //this->lineTo(x, y);
    
};
//------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------
class CinderProjectApp : public AppBasic {
  public:
	void setup();
	void update();
	void draw();

	void mouseDown( MouseEvent event );
    
    void prepareSettings( Settings *settings );
  private:
    gl::Texture myImage;
    
    //Path2d path;
    QArc path;
    float delta = 0;

    float x = 0;
    float y = 0;
};

void CinderProjectApp::setup()
{
    //myImage = gl::Texture( loadImage( loadResource( "image.png" ) ) );
    //gl::draw( myImage, getWindowBounds() );
}

void CinderProjectApp::update()
{
}

void CinderProjectApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    //gl::clear( Color( 1, 0, 0 ), true );
    //float gray = sin( getElapsedSeconds() ) * 0.5f + 0.5f;
    //gl::clear( Color( gray, gray, gray ), true );
    
    //gl::draw( myImage, getWindowBounds() );
    
    //gl::drawSolidCircle( Vec2f( 350.0f, 150.0f ), 50.0f, 7 );
    //gl::drawSolidCircle( Vec2f( x, y ), 50.0f, 7 );
    
    //float xx = cos( getElapsedSeconds() ) * 100.0f;
    //float yy = sin( getElapsedSeconds() ) * 100.0f;
    //gl::drawSolidCircle( Vec2f( xx, yy ) + getWindowSize() / 2, abs( xx ) );
    
    // clear the contents of the path, so we can draw whatever we want
    //path.clear();

    //path.moveTo(x, y);
    //path.arcTo(<#float x#>, <#float y#>, <#float tanX#>, <#float tanY#>, <#float radius#>);
    //path.arc(<#float centerX#>, <#float centerY#>, <#float radius#>, <#float startRadians#>, <#float endRadians#>)
    //path.arcTo(x+0, y+100, x+100, y+100, 100);
    
    
    delta += 0.1;
    
    //path.arc(x, y, 100, 0, delta);
    path.refresh(x, y, delta, 100, 40);
    
    // now draw the path
    //gl::color(1, 1, 0);
    gl::color(1, .9, 0);
    gl::drawSolid( path );
    //gl::color(1, 0, 0);
    //gl::draw( path );
    
    
    path.refresh(x, y, delta*0.9, 70, 10);
    //gl::color(1, 0, 1);
    gl::color(.9, 0, .8);
    gl::drawSolid( path );
    
    path.refresh(x, y, delta*0.8, 140, 30);
    //gl::color(0, 1, 1);
    gl::color(0, .7, 1);
    gl::drawSolid( path );
}

void CinderProjectApp::mouseDown( MouseEvent event )
{
    x = event.getX();
    y = event.getY();
    
    delta = 0;
}

void CinderProjectApp::prepareSettings( Settings *settings ){
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}

CINDER_APP_BASIC( CinderProjectApp, RendererGl )
