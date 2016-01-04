#include "renderImg.h"
#include <QMouseEvent>
#include <iostream>

#include "imgGradient.h"
#include "boundingbox.h"

#include <limits>


RenderImg::RenderImg( QWidget *parent ):
	QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
	m_texture(0),
    m_widthTex(BASE_W),
    m_heightTex(BASE_H),
	m_drawSobel(false),
    m_drawBB(false),
    m_img(m_widthTex, m_heightTex),
    m_GS(),
    m_fountain(m_widthTex, m_heightTex)
  // QQ INIT A AJOUTER ?
{
	// VOTRE CODE ICI
    m_img.clear();
    m_ptrTex=m_img.getArray();
}


void RenderImg::loadTexture(const std::string& filename)
{
    m_img.load(filename);
    m_widthTex=(int)m_img.getWidth();
    m_heightTex=(int)m_img.getHeight();
    m_ptrTex=m_img.getArray();

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_widthTex, m_heightTex, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_ptrTex);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderImg::updateDataTexture()
{
    m_widthTex=(int)m_img.getWidth();
    m_heightTex=(int)m_img.getHeight();
    m_ptrTex=m_img.getArray();

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexSubImage2D(GL_TEXTURE_2D,0,0,0,m_widthTex, m_heightTex, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_ptrTex);
	glBindTexture(GL_TEXTURE_2D, 0);

    if(m_drawSobel)
        m_gradImg=m_GS(m_img);

	updateGL();
}

Image2Grey& RenderImg::getImg()
{
    return m_img;
}

unsigned int RenderImg::getWidth()
{
    return m_widthTex; // RETURN IMAGE WIDTH
}

unsigned int RenderImg::getHeight()
{
    return m_heightTex; // RETURN IMAGE HEIGHT
}

void RenderImg::toGLVec2f(Vec2f& vertice)
{
    vertice.setX(xImg2GL(vertice.X()));
    vertice.setY(yImg2GL(vertice.Y()));
}

RenderImg::~RenderImg()
{
	glDeleteTextures(1, &m_texture);
	m_texture = 0;
}

void RenderImg::initializeGL()
{
	glClearColor(0.0f,0.0f,0.4f,0.0f);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_widthTex, m_heightTex, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_ptrTex);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderImg::paintGL()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();		// let's go 2D

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f( -1,1);
	glTexCoord2f(0,1);
	glVertex2f(-1,-1);
	glTexCoord2f(1,1);
	glVertex2f( 1,-1);
	glTexCoord2f(1,0);
	glVertex2f( 1,1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

    // for debugging
    if (m_drawSobel)
    {
        drawSobel();
    }
    if(m_drawBB)
        drawBB();

    glPointSize(4.0f);
    glColor3f(1.0f,0,0);
    glBegin(GL_POINTS);

    // VOTRE CODE ICI : -nombre de particules- <- lol
    for (ParticleSystem::const_iterator it=m_fountain.begin(); it!=m_fountain.end(); ++it)
    {
        // here get back position of each particle in ptPos
        glVertex2f(2.0f*(*it)->getPosition().X()/m_widthTex-1.0f, -2.0f*(*it)->getPosition().Y()/m_heightTex+1.0f);
    }
    glEnd();

}

void RenderImg::resizeGL(int width, int height)
{
	m_winW = width;
	m_winH = height;
	int side = qMin(width, height);
	m_winS = side;
	glViewport((width - side) / 2, (height - side) / 2, side, side);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
    makeCurrent();
    updateGL();
}

void RenderImg::coordInTexture(QMouseEvent *event, int& x, int& y)
{
    if (m_winS == m_winW)
    {
        x = (float(event->x())/m_winW)*m_widthTex;
        y = (float(event->y()-(m_winH-m_winS)/2)/m_winH)*m_heightTex;
    }
    else
    {
        x = (float(event->x()-(m_winW-m_winS)/2)/m_winH)*m_widthTex;
        y = (float(event->y())/m_winH)*m_heightTex;
    }
}


void RenderImg::mousePressEvent(QMouseEvent *event)
{
	int x,y;
	coordInTexture(event, x, y);
	m_lastPos.setX(x);
	m_lastPos.setY(y);

	std::cout << "PRESS in texture "<< x << " / "<< y << std::endl;

	if (m_state_modifier & Qt::ShiftModifier)
    {
        std::cout << "     with Shift (new particle)" << std::endl;
        m_fountain.generate(Vec2f(x,y));
    }
	if (m_state_modifier & Qt::ControlModifier)
		std::cout << "     with Ctrl" << std::endl;

    //makeCurrent();
    updateGL();
}


void RenderImg::mouseReleaseEvent(QMouseEvent *event)
{
    int x,y;
    coordInTexture(event, x, y);
    m_lastPos.setX(x);
    m_lastPos.setY(y);

    std::cout << " RELEASE in texture "<< x << " / "<< y << std::endl;

}


void RenderImg::keyPressEvent(QKeyEvent* event)
{
	m_state_modifier = event->modifiers();

	if (event->key() == 'A')	// here 'A' check 'a' pressed (thanks to Qt!)
	{
		std::cout << " touche a enfoncee" << std::endl;
	}

}


void RenderImg::keyReleaseEvent(QKeyEvent* event)
{
	m_state_modifier = 0;
}



void RenderImg::clean()
{
    unsigned char* ptr=m_ptrTex;

    for (int i=0; i<m_heightTex; ++i)
    {
        for (int j=0; j<m_widthTex; ++j)
        {
            *ptr++ = 0;
        }
    }
}


void RenderImg::toggleSobel()
{
	m_drawSobel = !m_drawSobel;
	if (m_drawSobel)
    {
        m_gradImg=m_GS(m_img, GRAD_55); //more precise
        updateGL();
    }
    else
        m_gradImg.clear();
}

void RenderImg::toggleBBdraw()
{
    m_drawBB = !m_drawBB;
    if (m_drawBB)
    {
        updateGL();
    }
}

void RenderImg::drawSobel()
{
    glBegin(GL_LINES);
    for (int j=0; j<m_heightTex; ++j)
    {
        for (int i=0; i<m_widthTex; ++i)
        {
            Vec2f& v=m_gradImg.getPixel(i,j);

            if (v*v > 0.001f)
            {
                float x = -1.0f + (2.0f*i)/(m_widthTex-1);
                float y = 1.0f  - (2.0f*j)/(m_heightTex-1);// minus because of GL is bottom to up and image up to boytom
                v *= 4.0f/m_widthTex;
                glColor3f(1.0f,1.0f,0.0f);
                glVertex2f(x,y);
                glColor3f(1.0f,0.0f,0.0f);
                glVertex2f(x+v[0],y-v[1]);
            }
        }
    }
    glEnd();
}


void RenderImg::updateBB(const BoundingBox& bb)
{
    m_bb=bb;
    updateGL();
}

void RenderImg::drawBB()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f,0.5f,0.5f);
    glVertex2f( m_bb.X1(), m_bb.Y1() );
    glVertex2f( m_bb.X1(), m_bb.Y2() );
    glColor3f(0.1f,0.5f,0.5f);
    glVertex2f( m_bb.X2(), m_bb.Y2() );
    glVertex2f( m_bb.X2(), m_bb.Y1() );
    glEnd();
}

void RenderImg::updateFountain()
{
    if(m_fountain.progress(m_img, m_gradImg))
        updateGL();
}
