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
    
    float setDelta(float delta);
};

float QArc::innerRadius() {
    return this->radius-this->thickness/2;
};
float QArc::outerRadius() {
    return this->radius+this->thickness/2;
};
float QArc::setDelta(float delta) {
    this->delta = delta;//(2*M_PI < delta)?2*M_PI:delta;
    
    return this->delta;
}
void QArc::refresh(float x, float y, float delta, float radius, float thickness)
{
    this->x = x;
    this->y = x;
    this->setDelta(delta);
    this->radius = radius;
    this->thickness = thickness;
    
    
    //path.arcTo(<#float x#>, <#float y#>, <#float tanX#>, <#float tanY#>, <#float radius#>);
    //path.arc(<#float centerX#>, <#float centerY#>, <#float radius#>, <#float startRadians#>, <#float endRadians#>)
    
    

    float startRadians = (delta>0)?0:delta;
    float endRadians = (delta>0)?delta:0;
    
    // Calculate the CAP positions
        this->clear();
        this->moveTo(x, y);
        this->arc(x, y, innerRadius(), startRadians, this->delta);
        Vec2f p2 = this->getCurrentPoint();
        this->arc(x, y, outerRadius(), startRadians, this->delta);
        Vec2f p1 = this->getCurrentPoint();
    
    // Start
    this->clear();
    
    // inner
    this->arc(x, y, innerRadius(), startRadians, endRadians);
    
    this->reverse();
    
    // outter
    this->arc(x, y, outerRadius(), startRadians, endRadians);
    
    //cap
    //this->close();
    //this->arc((p1.x+p2.x)/2, (p1.y+p2.y)/2, thickness/2, this->delta, this->delta+M_PI);
    
    //this->lineTo(x, y);
    
};

//------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------
class QApp : public AppBasic {
  public:
	void setup();
	void update();
	void draw();

	void mouseDown( MouseEvent event );
    
    void prepareSettings( Settings *settings );
  private:
    gl::Texture myImage;
    
    QArc path;
    float delta = 0;

    float x = 0;
    float y = 0;
};

void QApp::setup()
{
    //myImage = gl::Texture( loadImage( loadResource( "image.png" ) ) );
    //gl::draw( myImage, getWindowBounds() );
}

void QApp::update()
{
}

void QApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	//gl::clear( Color( 1, 1, 1 ) );
    
    
    // constant
    delta += 0.1;
    // [-2PI, 2PI]
    delta = sin( getElapsedSeconds() ) * 2*M_PI;
    // [0, 2PI]
    delta = (1+sin( getElapsedSeconds() ) ) * M_PI;

    //gl::drawSolidCircle( Vec2f( xx, yy ) + getWindowSize() / 2, abs( xx ) );
    
    // clear the contents of the path, so we can draw whatever we want
    //path.clear();

    
    // now draw the path
    
    path.refresh(x, y, delta, 100, 40);
    //gl::color(1, 1, 0);
    gl::color(1, .9, 0);
    gl::drawSolid( path );
    
    
    path.refresh(x, y, delta*0.9, 70, 10);
    //gl::color(1, 0, 1);
    gl::color(.9, 0, .8);
    gl::drawSolid( path );
    
    path.refresh(x, y, delta*0.8, 140, 30);
    //gl::color(0, 1, 1);
    gl::color(0, .7, 1);
    gl::drawSolid( path );
}

void QApp::mouseDown( MouseEvent event )
{
    x = event.getX();
    y = event.getY();
    
    delta = 0;
}

void QApp::prepareSettings( Settings *settings ){
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}

CINDER_APP_BASIC( QApp, RendererGl )
