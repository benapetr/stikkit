#include <QCoreApplication>
#include "configuration.hpp"
#include "syslog.hpp"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    //return a.exec();
    Stikkit::Syslog::Log("hi");
    return 0;
}
