#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>

#include <memory>
#include <iostream>
#include "core.h"


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("HomeSpeak server");
    QCoreApplication::setApplicationVersion("0.1 alpha");

    QCommandLineParser parser;
    parser.setApplicationDescription("HomeSpeak server program");
    parser.addHelpOption();
    parser.addVersionOption();

    auto core = std::make_unique<Core>();

    return app.exec();
}