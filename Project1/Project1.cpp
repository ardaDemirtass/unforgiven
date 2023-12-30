// Project1.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include "Network.h"
using namespace std;

int main()
{
    Network nw;
    vector<double> xtrain = { 1.0f, 2.0f };
    vector<double> ytrain = { 2.0f, 4.0f };
    nw.addInputLayer(1);
    nw.addHiddenLayer(3);
    nw.addOutpuLayer(1);
    //nw.learn(xtrain, ytrain, 1);
    nw.predict(4.0f);
    nw.displayNetwork();
    return 0;
}