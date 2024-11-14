#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

#include "Triangulation.h"

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget* parent = nullptr);
    ~Visualizer();

private slots:
    void onLoadFileClick();
    void onTranslateClick();

private:
    void setupUi();

private:
    Triangulation triangulation;

    QPushButton* loadFile;
    QPushButton* translate;
    QTextEdit* loadEdit;
    QTextEdit* translateEdit;
};