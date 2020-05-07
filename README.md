# hydrogui


A graphical interface for [Hydrogen: MVICFG Generator](https://github.com/iowastateuniversity-programanalysis/hydrogen) that utilizes the [wxWidgets Framework](http://www.wxwidgets.org/).


NOTE: The wxWidgets framework must be installed in order to build this project. You can download the wxWidgets (for your respective distro) [from the wxWidgets downloads page](https://www.wxwidgets.org/downloads/)


Post wxWidgets installation:

An install script is provided for debian distributions (install.sh) + fedora (fedorainstall.sh). The GUI can be run by executing the run.sh script or via the command:

>g++ App.cpp MainWindow.cpp `wx-config --cxxflags --libs` -o hydrogui && ./hydrogui

The objective of this project is to make the tool "Hydrogen" a bit more user friendly.
