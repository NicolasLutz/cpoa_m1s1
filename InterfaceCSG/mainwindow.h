#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QKeyEvent>
#include <QTimer>

#include "renderImg.h"
#include "csgtree.h"
#include "boundingbox.h"
#include "csgdisk.h"
#include "csgregularpolygon.h"
#include "csgoperation.h"

namespace Ui {
class MainWindow;
}


/**
 * @brief TextEdit Widget for CSG Graph
 */
class GraphTextEdit: public QPlainTextEdit
{
protected:
	char m_pressed;
public:

	GraphTextEdit();

	void keyPressEvent(QKeyEvent* event) { m_pressed = char(event->key()+32); }

    void keyReleaseEvent(QKeyEvent* event) { m_pressed = char(0); }

	char pressed() const { return m_pressed; }
};



class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindow *ui;
    RenderImg *m_render;
    void _setIndics();

protected:
	/// current selected node
    CsgNode *m_currentNode;

    /// current primitive (could be NULL)
    CsgPrimitive *m_prim;

    /// current operation (could be NULL)
    CsgOperation *m_oper;

    /// the CSG tree
    CsgTree m_tree;

	/// Bounding Box to draw
    BoundingBox m_bb;

	/// widget for ascii art grapg drawing
    GraphTextEdit *m_graphTextEdit;

	/// current transfo matrix for storing current primitive matrix
    Matrix33f m_transfo;

    Vec2f m_centerSelection;

	/// just to avoid ping-pong signal
	bool m_stopSignal;

    QTimer m_timer;

	void updateTextGraph();

	void closeEvent(QCloseEvent *event);

	void transfoChanged();

	void resetTransfoWidgets();

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void drawTree();

public slots:
	void createPrimtive();
	void createOperation();
	void applyTransfo();
	void resetTransfo();
	void transfoSliderChanged();
	void transfoSpinChanged();
	void loadImage();
	void saveImage();
	void drawSobel();
	void loadCSG();
	void saveCSG();
	void appendCSG();
	void clearCSG();
	void swapLRRoot();
	void unjoinRoot();
	void clone();
	void checkDrawCurrent();
	void currentNodeChanged(int id);
	void nodeTextSelected(bool);
    void updateFountain();

    //Ajoutés après//
    void on_actionDraw_BB_triggered();
};

#endif // MAINWINDOW_H
