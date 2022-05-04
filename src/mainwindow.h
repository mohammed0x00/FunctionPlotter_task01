#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "expressionParser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initialize();

private slots:
    void on_plotButton_clicked();

    void on_autoNoPointsCheckBox_stateChanged(int arg1);

    void on_aboutButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;

    // Enum that represent the type of the errors (invalidRanges, syntaxError)
    typedef enum Error_Type_enum {invalidRanges, syntaxError} Error_Type;

    bool validateExpression(const char * expressionString, size_t len);
    void plot(ExpressionParser * ex, double minValue, double maxValue, int numberOfPoints);
    void displayErrorMessage(Error_Type err);

};
#endif // MAINWINDOW_H
