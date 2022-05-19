QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_expressionparserclass.cpp

INCDIR_EXPRESSIONPARSER_MODULE = ../FunctionPlotter/

SOURCES += $$INCDIR_EXPRESSIONPARSER_MODULE/expressionParser.cpp

INCLUDEPATH += \
    $$INCDIR_EXPRESSIONPARSER_MODULE

HEADERS += $$INCDIR_EXPRESSIONPARSER_MODULE/expressionParser.h
