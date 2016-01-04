#ifndef RENDERIMG_H
#define RENDERIMG_H

#include <QGLWidget>

#include "image2grey.h"
#include "imgGradient.h"
#include "vec2f.h"
#include "boundingbox.h"
#include "particlesystem.h"
#define BASE_H 512
#define BASE_W 512

class RenderImg : public QGLWidget
{
	Q_OBJECT

public:
	RenderImg(QWidget *parent = 0);
	~RenderImg();

	void loadTexture(const std::string& filename);
	void updateDataTexture();

    Image2Grey & getImg();
	unsigned int getWidth();
	unsigned int getHeight();

    void toGLVec2f(Vec2f& vertice);

	/**
	 * @brief clean image
	 */
	void clean();

   /**
	* @brief update sobel image
	*/
   void toggleSobel();
   void toggleBBdraw();

   void setBBDraw(bool v) { m_drawBB = v;}

   void updateBB(const BoundingBox& bb);

   void updateFountain();

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
        return 1.0f - (2.0f*y)/float(m_heightTex-1);// minus because of GL is bottom to up and image up to bottom
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

    bool m_drawBB;

	void drawSobel();
    void drawBB();

//	ici les declaration de:
//   - l'image a niveau de gris
    Image2Grey m_img;
//	 - l'image gradiant'
    Image2<Vec2f> m_gradImg;

    GradientSobel m_GS;
    BoundingBox m_bb;

//	 la fontaine de particule
    ParticleSystem m_fountain;
};

#endif // RENDERIMG_H
