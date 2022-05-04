#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "expressionParser.h"
#include <exception>
#include <string>
#include <QVariant>
#include <QStyleOption>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setup UI
    ui->setupUi(this);

    // Init.
    MainWindow::initialize();

}

MainWindow::~MainWindow()
{
    // Delete the UI object from Heap
    delete ui;
}

void MainWindow::initialize()
{
    // create graph:
    ui->customPlot->addGraph();

    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
}

bool MainWindow::validateExpression(const char * expressionString, size_t len)
{
    int numberOfOperands = 0;
    int numberOfOperations = 0;
    char prevChar = expressionString[0];

    // Check whether the first element is a Number/Variable, add/subrract operation or otherwise
    if(ExpressionParser::isNumber(expressionString[0]) || ExpressionParser::isVariable(expressionString[0])) {
        numberOfOperands++;
    }
    else if(expressionString[0] == '+' || expressionString[0] == '-') {
        numberOfOperations++;
    }
    else {
        // Invalid begining character
        return false;
    }

    // Test the sequence (Previous Character - Current Character)
    for(size_t i = 1; i < len; i++) {
        if(ExpressionParser::isNumber(expressionString[i])) {
            if(ExpressionParser::isNumber(prevChar)) {
                // Number - Number
            }
            else if(ExpressionParser::isOperator(prevChar)) {
                // Operator - Number
                numberOfOperands++;
            }
            else {
                // Variable - Number
                // Otherwise - Number
                return false;
            }
        }
        else if(ExpressionParser::isOperator(expressionString[i])) {
            if(i == len - 1)
            {
                return false;
            }
            else if(ExpressionParser::isNumber(prevChar)) {
                // Number - Operator
                numberOfOperations++;
            }
            else if(ExpressionParser::isVariable(prevChar)) {
                // Variable - Operator
                numberOfOperations++;
            }
            else {
                // Operator - Operator
                // Otherwise - Operator
                return false;
            }
        }
        else if(ExpressionParser::isVariable(expressionString[i])) {
            if(ExpressionParser::isOperator(prevChar)) {
                // Operator - Variable
                numberOfOperands++;
            }
            else {
                // Number - Variable
                // Variable - Variable
                // Otherwise - Variable
                return false;
            }
        }
        else {
            return false;
        }

        // Update previous character
        prevChar = expressionString[i];
    }

    // Check whether the number of operations > the number of operands
    if(numberOfOperands < numberOfOperations)
    {
        return false;
    }

    return true;
}

void MainWindow::displayErrorMessage(Error_Type err)
{
    switch(err)
    {
    case invalidRanges:
        (new QMessageBox())->critical(0, "Error", "Invalid Range Values");
        break;
    case syntaxError:
        (new QMessageBox())->critical(0, "Error", "Syntax Error");
        break;
    default:
        break;
    }
}

void MainWindow::plot(ExpressionParser * ex, double minValue, double maxValue, int numberOfPoints)
{
    double minOfVerticalAxis = std::numeric_limits<double>::max();
    double maxOfVerticalAxis = std::numeric_limits<double>::min();
    QVector<double> x(numberOfPoints + 1), y(numberOfPoints + 1); // initialize with entries 0..numberOfPoints

    // Generate data:
    for (int i = 0; i <= numberOfPoints; ++i)
    {
        // Divide the whole range into points
        x[i] = (i * (maxValue - minValue) / numberOfPoints) + minValue;

        // Calculate the corresponding y values
        y[i] = ex->calculate(x[i]);

        // Get the minimum value of y
        if(y[i] < minOfVerticalAxis) {
            minOfVerticalAxis = y[i];
        }

        // Get the maximum value of y
        if(y[i] > maxOfVerticalAxis) {
            maxOfVerticalAxis = y[i];
        }
    }

    // assign data to graph
    ui->customPlot->graph(0)->setData(x, y);

    // set axes ranges, so we see all data
    ui->customPlot->xAxis->setRange(minValue, maxValue);
    ui->customPlot->yAxis->setRange(minOfVerticalAxis - 1, maxOfVerticalAxis + 1);

    // Plot it
    ui->customPlot->replot();
}

void MainWindow::on_plotButton_clicked()
{
    bool validInput = true;
    double minValue;
    double maxValue;
    int numberOfPoints;
    const char* inputStringPtr;
    ExpressionParser * ex ;
    
    // Check & Parse range values
    try {
        // Convert x range values to double
        minValue = stod(ui->minValueBox->text().toStdString());
        maxValue = stod(ui->maxValueBox->text().toStdString());
        if(maxValue <= minValue)
        {
            throw (std::exception());
        }
    }  catch (std::exception) {
        // Invalid range values
        validInput = false;
        displayErrorMessage(invalidRanges);
    }

    // Preprocessing
    std::string str = ui->equationBox->text().toStdString();
    inputStringPtr = str.c_str();

    // Validating the Expression String
    if(validInput){
        if(validateExpression(inputStringPtr, str.length())) {
            // Expression is valid
            ex = new ExpressionParser(inputStringPtr, str.length());
        }
        else {
            validInput = false;
            displayErrorMessage(syntaxError);
        }
    }


    // If CheckBox is checked set number of points equal DEFAULT_NUMBER_OF_POINTS
    if(ui->autoNoPointsCheckBox->checkState() == Qt::Checked) {
        numberOfPoints = DEFAULT_NUMBER_OF_POINTS;
    }
    else {
        numberOfPoints = ui->noPointsSpinBox->value();
    }

    // If input is correct, plot it
    if(validInput){
        plot(ex, minValue, maxValue, numberOfPoints);
    }

    // Remove ExpressionParser object
    if(validInput) {
        delete ex;
    }

}


void MainWindow::on_autoNoPointsCheckBox_stateChanged(int arg1)
{
    bool state = ui->autoNoPointsCheckBox->isChecked();

    // Disable Spin Box if the CheckBox is Checked
    ui->noPointsSpinBox->setDisabled(state);

    // Set Spin Box value to DEFAULT_NUMBER_OF_POINTS if the CheckBox is Checked
    ui->noPointsSpinBox->setValue(DEFAULT_NUMBER_OF_POINTS);
}


void MainWindow::on_aboutButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("<h3>Created by : Mohammed Ali Mansour</h3>");
    msgBox.exec();
}


void MainWindow::on_closeButton_clicked()
{
    // Close The Window
    MainWindow::close();
}

