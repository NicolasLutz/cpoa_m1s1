#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include"csgPrimitive.h"

#include <QFileDialog>
#include <QTextCursor>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
    m_currentNode(NULL),
    m_prim(NULL),
    m_oper(NULL),
	m_graphTextEdit(NULL),
    m_stopSignal(false),
    m_timer(this)
{
	ui->setupUi(this);

	m_render = new RenderImg();
//	m_tree.setWH(m_render->getWidth(),m_render->getHeight());

	ui->HLayout->insertWidget(0,m_render,99);
	m_render->setFocusPolicy(Qt::ClickFocus);

	ui->translationX->setMinimum(-int(m_render->getWidth()/2));
	ui->translationX->setMaximum(m_render->getWidth()/2);
	ui->translationY->setMinimum(-int(m_render->getHeight()/2));
	ui->translationY->setMaximum(m_render->getHeight()/2);

	ui->scaleX->setMinimum(-100);
	ui->scaleX->setMaximum(100);
	ui->scaleY->setMinimum(-100);
	ui->scaleY->setMaximum(100);


	connect(ui->create_oper,SIGNAL(clicked()),SLOT(createOperation()));
	connect(ui->create_prim,SIGNAL(clicked()),SLOT(createPrimtive()));
	connect(ui->resetTransfo,SIGNAL(clicked()),SLOT(resetTransfo()));
    connect(ui->applyTransfo,SIGNAL(clicked()),SLOT(applyTransfo()));

	connect(ui->translationX,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->translationY,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->rotation,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->scaleX,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->scaleY,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));

	connect(ui->dsb_tx,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_ty,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_Rot,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_sx,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_sy,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));

	connect(ui->actionLoadIMG, SIGNAL(triggered()), this, SLOT(loadImage()));
	connect(ui->actionSaveIMG, SIGNAL(triggered()), this, SLOT(saveImage()));
	connect(ui->actionDrawSobel, SIGNAL(triggered()), this, SLOT(drawSobel()));

	connect(ui->actionLoadCSG, SIGNAL(triggered()), this, SLOT(loadCSG()));
	connect(ui->actionSaveCSG, SIGNAL(triggered()), this, SLOT(saveCSG()));
	connect(ui->actionAppendCSG, SIGNAL(triggered()), this, SLOT(appendCSG()));
	connect(ui->actionClearCSG, SIGNAL(triggered()), this, SLOT(clearCSG()));

	connect(ui->actionClone, SIGNAL(triggered()), this, SLOT(clone()));
	connect(ui->actionSwapLRRoot, SIGNAL(triggered()), this, SLOT(swapLRRoot()));
	connect(ui->actionUnjoinRoot, SIGNAL(triggered()), this, SLOT(unjoinRoot()));

	connect(ui->currentNode, SIGNAL(valueChanged(int)), this, SLOT(currentNodeChanged(int)));
	connect(ui->checkBox_drawCurrent, SIGNAL(toggled(bool)), this, SLOT(checkDrawCurrent()));

	m_graphTextEdit = new GraphTextEdit();
	m_graphTextEdit->show();
	connect(m_graphTextEdit,SIGNAL(copyAvailable(bool)),SLOT(nodeTextSelected(bool)));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateFountain()));
    m_timer.start(50);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	m_graphTextEdit->close();
}

void MainWindow::createPrimtive()
{
	int prim =  ui->prim_type->currentIndex();
	int sides = ui->nb_sides->value();

// VOTRE CODE ICI : primitive creation
    switch(prim)
    {
        case 0:
            m_currentNode = new CsgDisk();
            m_tree.add((CsgDisk *)m_currentNode); //or reinterpret_cast<CsgDisk *>
            break;
        case 1:
            m_currentNode = new CsgRegularPolygon(sides);
            m_tree.add((CsgRegularPolygon *)m_currentNode);
        break;
        default:
            std::cerr << "unknown operation" << std::endl;
            break;
    }

	drawTree();
    ui->currentNode->setValue(m_currentNode->Id()); // recupere l'id du noeud cree
	updateTextGraph();
}

void MainWindow::createOperation()
{
	int typeOp = ui->Operation->currentIndex();
	int left = ui->id_filsGauche->value();
	int right = ui->id_filsDroit->value();

	std::cout << "createOperation  ";
	std::cout << "type "<< typeOp;
	std::cout << " child: "<< left << " & "<< right;
	std::cout << std::endl;

    CsgOperation* oper=new CsgOperation();
	switch(typeOp)
	{
//		Ici on recupère les deux fils à partir des identifiants et on crée le noeud operation correspondant
		case 0:
            oper->setType(CSG_UNION);
            m_tree.join(oper, m_tree.fromId(left), m_tree.fromId(right));
			break;
		case 1:
            oper->setType(CSG_INTERSECTION);
            m_tree.join(oper, m_tree.fromId(left), m_tree.fromId(right));
			break;
		case 2:
            oper->setType(CSG_DIF);
            m_tree.join(oper, m_tree.fromId(left), m_tree.fromId(right));
			break;
		default:
			std::cerr << "unknown operation" << std::endl;
			return;
			break;
	};


	drawTree();

    if (oper != NULL)
        ui->currentNode->setValue(oper->Id());

    m_currentNode = oper;

	updateTextGraph();

}

/// fige la tranformation en la sauvegardant
void MainWindow::applyTransfo()
{
    CsgPrimitive *currentPrNode;
    if((currentPrNode=dynamic_cast<CsgPrimitive *>(m_currentNode))!=NULL)
    {
        currentPrNode->T_save();
    }
	drawTree();
}


void MainWindow::resetTransfoWidgets()
{
    _setIndics();
	transfoSliderChanged();
}


void MainWindow::resetTransfo()
{
    CsgPrimitive *currentPrNode;
    CsgOperation *currentOpNode;
    if((currentPrNode=dynamic_cast<CsgPrimitive *>(m_currentNode))!=NULL)
    {
        // reaffecte la tranfo sauvée à la primitive courante (si primitive)
        // VOTRE CODE ICI
        currentPrNode->T_reset();
    }
    else if((currentOpNode=dynamic_cast<CsgOperation *>(m_currentNode))!=NULL)
    {
        // reaffecte les transfos des primitives descendentes de l'operation courante
        // VOTRE CODE ICI
        m_currentNode=currentOpNode->Left();
        resetTransfo();
        m_currentNode=currentOpNode->Right();
        resetTransfo();
        m_currentNode=currentOpNode;
    }
    else
    {
        std::cerr << "Couldn't cast current node" << std::endl;
    }
	resetTransfoWidgets();
}

void MainWindow::transfoChanged()
{
	// recupere la primitive courante et lui applique les transformations
	// VOTRE CODE ICI
    CsgPrimitive *currentPrNode;
    if((currentPrNode=dynamic_cast<CsgPrimitive *>(m_currentNode))!=NULL)
    {
        // reaffecte la tranfo sauvée à la primitive courante (si primitive)
        // VOTRE CODE ICI
        float tx=ui->dsb_tx->value()/(m_render->getWidth()/2);
        float ty=ui->dsb_ty->value()/(m_render->getHeight()/2);
        currentPrNode->T_applyTransfo(tx, ty,
                                      (ui->dsb_Rot->value()*M_PI)/180,
                                      ui->dsb_sx->value(), ui->dsb_sy->value());
    }
	// Option: de même avec un noeud Operation !

    if(m_currentNode!=NULL)
        m_render->updateBB(m_currentNode->BBox());

	drawTree();
}

#define S1_FACTOR 10.0
#define S2_FACTOR 100.0


void MainWindow::transfoSliderChanged()
{
	if (m_stopSignal)
		return;

	m_stopSignal = true;

	ui->dsb_tx->setValue(ui->translationX->value());
	ui->dsb_ty->setValue(ui->translationY->value());
	ui->dsb_Rot->setValue(ui->rotation->value());

	int ss = ui->scaleX->value();
	if (ss>=0)
		ui->dsb_sx->setValue(1.0+ss/S1_FACTOR);
	else
		ui->dsb_sx->setValue(1.0/(1.0-ss/S2_FACTOR));

	ss = ui->scaleY->value();
	if (ss>=0)
		ui->dsb_sy->setValue(1.0+ss/S1_FACTOR);
	else
		ui->dsb_sy->setValue(1.0/(1.0-ss/S2_FACTOR));

	m_stopSignal = false;

	transfoChanged();
}


void MainWindow::transfoSpinChanged()
{
	if (m_stopSignal)
		return;

	m_stopSignal = true;

	ui->translationX->setValue(ui->dsb_tx->value());
	ui->translationY->setValue(ui->dsb_ty->value());
	ui->rotation->setValue(ui->dsb_Rot->value());

	double ss = ui->dsb_sx->value();
	if (ss>=1.0)
		ui->scaleX->setValue((ss-1.0)*S1_FACTOR);
	else
		ui->scaleX->setValue((1.0-1.0/ss)*S2_FACTOR);

	ss = ui->dsb_sy->value();
	if (ss>=1.0)
		ui->scaleY->setValue((ss-1.0)*S1_FACTOR);
	else
		ui->scaleY->setValue((1.0-1.0/ss)*S2_FACTOR);

	m_stopSignal = false;

	transfoChanged();
}

void MainWindow::_setIndics()
{
    CsgPrimitive *currentPrNode;
    if((currentPrNode=dynamic_cast<CsgPrimitive *>(m_currentNode))!=NULL)
    {
        m_stopSignal=true;
        ui->translationX->setValue((int)(currentPrNode->T_Matrix().Tx()*m_render->getWidth() / 2.0f));
        ui->translationY->setValue((int)(currentPrNode->T_Matrix().Ty()*m_render->getHeight() / 2.0f));
        ui->rotation->setValue(currentPrNode->T_Matrix().Rad()*180/M_PI);

        ui->dsb_tx->setValue(ui->translationX->value());
        ui->dsb_ty->setValue(ui->translationY->value());
        ui->dsb_Rot->setValue(ui->rotation->value());

        //Scale

        ui->dsb_sx->setValue(currentPrNode->T_Matrix().Vx());
        ui->dsb_sy->setValue(currentPrNode->T_Matrix().Vy());

        double ss = ui->dsb_sx->value();
        if (ss>=1.0)
            ui->scaleX->setValue((ss-1.0)*S1_FACTOR);
        else
            ui->scaleX->setValue((1.0-1.0/ss)*S2_FACTOR);

        ss = ui->dsb_sy->value();
        if (ss>=1.0)
            ui->scaleY->setValue((ss-1.0)*S1_FACTOR);
        else
            ui->scaleY->setValue((1.0-1.0/ss)*S2_FACTOR);

        m_stopSignal=false;
    }
}

#undef S1_FACTOR
#undef S2_FACTOR


void MainWindow::loadImage()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath(),tr("pgm (*.pgm);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();
		// load texture
		m_render->loadTexture(strFN);
	}
}

void MainWindow::saveImage()
{
	QString fileName = QFileDialog::getSaveFileName(this,
									tr("Save File"), QDir::currentPath(),tr("pgm (*.pgm);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();
        m_render->getImg().save(strFN);
	}
}

void MainWindow::drawSobel()
{
	m_render->toggleSobel();
    m_render->updateDataTexture();
}

void MainWindow::loadCSG()
{
	QString fileName = QFileDialog::getOpenFileName(this,
									tr("Open File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

		std::ifstream in(strFN.c_str());
		if (!in.good())
		{
			std::cerr << "Unable to open file " << strFN << std::endl;
			return;
		}

        // VOTRE CODE ICI
        m_tree.clear();
        CsgOperation *opNode;
        CsgPrimitive *prNode;
        char id;
        while(in.good())
        {
            in >> id;
            opNode=NULL;
            prNode=NULL;
            switch(id)
            {
                case 'O':
                    opNode=new CsgOperation();
                    prNode=NULL;
                    in >> *opNode;
                    break;
                case 'D':
                    prNode=new CsgDisk();
                    opNode=NULL;
                    in >> *prNode;
                    break;
                case 'R':
                    prNode=new CsgRegularPolygon();
                    opNode=NULL;
                    in >> *prNode;
                    break;
                default:
                    break;
            }
            if(prNode!=NULL)
            {
                m_tree.add(prNode);
            }
            else if(opNode!=NULL)
            {
                m_tree.join(opNode, m_tree.fromId(opNode->getSpecialLeft()), m_tree.fromId(opNode->getSpecialRight()));
            }
        }
        in.close();
        updateTextGraph();
        drawTree();
	}
}

// same as load but no clear before readind the tree
void MainWindow::appendCSG()
{
	QString fileName = QFileDialog::getOpenFileName(this,
									tr("Open File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
    if (!fileName.isEmpty())
    {
        std::string strFN = fileName.toStdString();

        std::ifstream in(strFN.c_str());
        if (!in.good())
        {
            std::cerr << "Unable to open file " << strFN << std::endl;
            return;
        }

        // VOTRE CODE ICI
        CsgOperation *opNode;
        CsgPrimitive *prNode;
        char id;
        unsigned int counter=CsgNode::Counter();
        while(in.good())
        {
            in >> id;
            opNode=NULL;
            prNode=NULL;
            switch(id)
            {
                case 'O':
                    opNode=new CsgOperation();
                    prNode=NULL;
                    in >> *opNode;
                    break;
                case 'D':
                    prNode=new CsgDisk();
                    opNode=NULL;
                    in >> *prNode;
                    break;
                case 'R':
                    prNode=new CsgRegularPolygon();
                    opNode=NULL;
                    in >> *prNode;
                    break;
                default:
                    std::cerr << "Unknown csg node identifier found: " << id << std::endl;
                    break;
            }
            if(prNode!=NULL)
            {
                m_currentNode=m_tree.add(prNode);
            }
            else if(opNode!=NULL)
            {
                m_currentNode=m_tree.join(opNode, m_tree.fromId(counter+opNode->getSpecialLeft()), m_tree.fromId(counter+opNode->getSpecialRight()));
            }
        }
        in.close();
        updateTextGraph();
        drawTree();
    }
}

void MainWindow::saveCSG()
{
	QString fileName = QFileDialog::getSaveFileName(this,
									tr("Save File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

        std::ofstream out(strFN.c_str(), std::ofstream::trunc);
        if (!out.good())
        {
            std::cerr << "Unable to open/create file " << strFN << std::endl;
            return;
        }
        // VOTRE CODE ICI
        for(CsgTree::const_iterator it=m_tree.begin(); it!=m_tree.end(); ++it)
        {
            out << *((*it).second);
        }
	}
}

void MainWindow::clearCSG()
{
	// VOTRE CODE ICI
    m_tree.clear();
    m_currentNode=NULL;
    CsgNode::resetCounter();
    updateTextGraph();
	drawTree();
}


void MainWindow::clone()
{
	// VOTRE CODE ICI
    if(m_currentNode!=NULL)
    {
        m_currentNode=m_tree.add(m_currentNode->clone());
        ui->currentNode->setValue(m_currentNode->Id());
    }
	updateTextGraph();
	drawTree();
}


void MainWindow::drawTree()
{
	m_render->clean();

	// VOTRE CODE ICI (trace le graph dans l'image de m_render
    if (ui->checkBox_drawCurrent->isChecked() && m_currentNode!=NULL)
	{
        Vec2f currentVertice;
		// OPTION: trace le noeud courant dans l'image de m_render
		// VOTRE CODE ICI
        Image2Grey& img=m_render->getImg();
        Vec2f xy1_bbox=m_currentNode->BBox().XY1_img(m_render->getWidth(), m_render->getHeight());
        Vec2f xy2_bbox=m_currentNode->BBox().XY2_img(m_render->getWidth(), m_render->getHeight());
        Image2Grey::iterator_bbox it=img.beginOf((int)xy1_bbox.X(), (int)xy2_bbox.X(), (int)xy2_bbox.Y());
        Image2Grey::iterator_bbox end=img.endOf((int)xy2_bbox.X(), (int)xy1_bbox.Y());
        for(; it!=end; ++it)
        {
            currentVertice=it.Vertice();
            m_render->toGLVec2f(currentVertice);
            if(m_currentNode->intersects(currentVertice))
                *it=255;
            else
                *it=0;
        }
        m_render->updateBB(m_currentNode->BBox());
	}
    else
        m_render->setBBDraw(false);

	m_render->updateDataTexture();
}


void MainWindow::nodeTextSelected(bool sel)
{
	if (!sel)
		return;

	QTextCursor cursor = m_graphTextEdit->textCursor();
	std::string nodeLabel = cursor.selectedText().toStdString();

	if (nodeLabel.size() !=5)
		return;

	// get id from label string
	std::string strId = nodeLabel.substr(2,4);
	std::stringstream ss(strId);
	unsigned int id;
	ss >> id;

	ui->currentNode->setValue(id);

	if (m_graphTextEdit->pressed() == 'l')
	{
		ui->id_filsGauche->setValue(id);
	}
	else if (m_graphTextEdit->pressed() == 'r'	)
	{
		ui->id_filsDroit->setValue(id);
	}
	else
	{
		ui->currentNode->setValue(id);
	}
}

void MainWindow::updateTextGraph()
{
	// update Graph in TextWindow
	m_graphTextEdit->clear();

	std::string str;	//	std::string str = m_tree.asciiArtGraph();
	m_graphTextEdit->appendPlainText(str.c_str());
}


void MainWindow::currentNodeChanged(int id)
{
// VOTRE CODE ICI
    m_currentNode = NULL;
    resetTransfoWidgets();
    m_currentNode = m_tree.fromId(id);
    _setIndics();
	drawTree();
}


void MainWindow::swapLRRoot()
{
// VOTRE CODE ICI
    CsgOperation *currentOpNode;
    if((currentOpNode=dynamic_cast<CsgOperation *>(m_currentNode))!=NULL)
    {
        currentOpNode->swap();
        updateTextGraph();
        drawTree();
    }
}

void MainWindow::unjoinRoot()
{
// VOTRE CODE ICI
    CsgOperation *currentOpNode;
    if((currentOpNode=dynamic_cast<CsgOperation *>(m_currentNode))!=NULL)
    {
        currentOpNode->setLeft(NULL);
        currentOpNode->setRight(NULL);
        currentOpNode->setParent(NULL);
        m_tree.removeId(currentOpNode->Id());
    }
    m_currentNode = NULL;
	updateTextGraph();
	drawTree();
}


void MainWindow::checkDrawCurrent()
{
	drawTree();
}



GraphTextEdit::GraphTextEdit()
{
	this->resize(800,800);
	this->setWindowTitle("CSG-Graph");
	this->setReadOnly(true);
	this->setWordWrapMode(QTextOption::NoWrap);

	QFont font = QFont ("Courier");
	font.setStyleHint(QFont::TypeWriter);
	font.setPointSize(11);
	font.setFixedPitch (true);
	this->setFont (font);
}

//Ajoutés après//

void MainWindow::on_actionDraw_BB_triggered()
{
    m_render->toggleBBdraw();
    if(m_currentNode!=NULL)
        m_render->updateBB(m_currentNode->BBox());
}

void MainWindow::updateFountain()
{
    m_timer.stop();
    m_render->updateFountain();
    m_timer.start(50);
}
