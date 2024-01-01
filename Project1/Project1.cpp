// Project1.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include "Network.h"
using namespace std;

double toSigmoid(double x)
{
    return x / (1.0f + abs(x));
}


int main()
{
    Network nw;
    vector<double> xtrain = { 10.0f, 20.0f, 30.0f };
    vector<double> ytrain = { toSigmoid(20.0f), toSigmoid(40.0f), toSigmoid(60.0f) };
    nw.addInputLayer(1);
    nw.addHiddenLayer(3);
    nw.addHiddenLayer(3);
    nw.addOutpuLayer(1);
    nw.learn(xtrain, ytrain, 100000);
    cout << "predict : " << nw.predict(10) << endl;
    cout << "real : " << 20 << endl;
    nw.displayNetwork();
    return 0;
}