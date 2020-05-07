export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
g++ App.cpp MainWindow.cpp `wx-config --cxxflags --libs` -o hydrogui && ./hydrogui
