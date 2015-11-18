#ifndef RENDERIMG_H
#define RENDERIMG_H

#include <QGLWidget>

//#include "image2grey.h"
//#include "vec2f.h"
//#include "particle.h"

//fprward declaration
class BoundingBox;

class RenderImg : public QGLWidget
{
	Q_OBJECT

public:
	RenderImg(QWidget *parent = 0);
	~RenderImg();

	void loadTexture(const std::string& filename);
	void updateDataTexture();

//	Image2grey & getImg();
	unsigned int getWidth();
	unsigned int getHeight();

	/**
	 * @brief clean image
	 */
	void clean();

   /**
	* @brief update sobel image
	*/
   void toggleSobel();

   void setBBDraw(bool v) { m_BBdraw = v;}


protected:
	/// Qt callbacks
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);


	/// transform win coordinate in texel image coordinate
	void coordInTexture(QMouseEvent *event, int& x, int& y);


	// convert from image coordinate to GL coordinates (x)
	inline float xImg2GL(float x)
	{
		return -1.0f + (2.0f*x)/float(m_widthTex-1);
	}

	// convert from image coordinate to GL coordinates (y)
	inline float yImg2GL(float y)
	{
		return 1.0f - (2.0f*y)/float(m_heightTex-1);// minus because of GL is bottom to up and image up to boytom
	}


	/// Texture information
	GLuint m_texture;
	int m_widthTex;
	int m_heightTex;
	unsigned char* m_ptrTex;

	/// GL Widget sizes
	int m_winW;
	int m_winH;
	int m_winS;

	/// for mouse move
	QPoint m_lastPos;
	/// key modifier state (shift/ctrl/...)
	int m_state_modifier;

	bool m_drawSobel;

	bool m_BBdraw;

//	void drawBB(const BoundingBox& bb);

	void drawSobel();

//	ici les declaration de:
//   - l'image a niveau de gris
//	 - l'image gradiant'

//	 la fontaine de particule
//	Fountain fountain;
};

#endif // RENDERIMG_H
