# hydrogui


A graphical interface for [Hydrogen: MVICFG Generator](https://github.com/iowastateuniversity-programanalysis/hydrogen) that utilizes the [WxWidgets Framework](http://www.wxwidgets.org/).

An install script is provided for debian distributions (install.sh) + fedora (fedorainstall.sh). The GUI can be run by executing the run.sh script or via the command:

>g++ App.cpp MainWindow.cpp `wx-config --cxxflags --libs` -o hydrogui && ./hydrogui

The objective of this project is to make the tool "Hydrogen" a bit more user friendly.
