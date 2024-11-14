#include <QFileDialog>
#include <QGridLayout>
#include "Visualiser.h"
#include "STLReader.h"
#include "DataWriter.h"
#include "ObjWriter.h"


Visualizer::Visualizer(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();

    connect(loadFile, &QPushButton::clicked, this, &Visualizer::onLoadFileClick);
    connect(translate, &QPushButton::clicked, this, &Visualizer::onTranslateClick);
}

Visualizer::~Visualizer()
{

}

void Visualizer::setupUi()
{
    loadFile = new QPushButton("Load File", this);
    translate = new QPushButton("Translate", this);
    loadEdit = new QTextEdit(this);
    translateEdit = new QTextEdit(this);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFile, 0, 0);
    layout->addWidget(translate, 1, 0);
    layout->addWidget(loadEdit, 0, 1);
    layout->addWidget(translateEdit, 1, 1);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    loadFile->setFixedSize(100, 30);
    translate->setFixedSize(100, 30);
    loadEdit->setFixedHeight(30);
    translateEdit->setFixedHeight(30);

    loadEdit->setReadOnly(true);
    translateEdit->setReadOnly(true);
}

void  Visualizer::onLoadFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open STL File"), "", tr("STL Files (*.stl)"));

    if (!fileName.isEmpty())
    {
        loadEdit->clear();

        STLReader reader;
        reader.read(fileName, triangulation);

        loadEdit->setText(fileName);
    }
}

void Visualizer::onTranslateClick()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Data File"), "/data", tr("Data Files (*.obj)"));

    if (!fileName.isEmpty())
    {
        translateEdit->clear();

        ObjWriter writer;
        writer.Write(fileName.toStdString(), triangulation);

        translateEdit->setText(fileName);

    }
}