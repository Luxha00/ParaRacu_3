#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "sinhroniziranaVrsta.h"
#include <random>

using namespace std;
using namespace std::chrono;

int seed = 0;
int nfes = 0;
int PSL = 9999;
double MF = 0;
int nfesLmt = 1000000;
int L = 2501;
int threads = 0;
vector <int> sequence;
mutex myMutex;
condition_variable var;
vector <vector<int>> sosedi;
vector <vector<int>> kandidati;
vector <int> bestPSLSequence;
vector <int> bestMFSequence;
sinhroniziranaVrsta<vector<int>> vrsta;
vector<thread>guide;

void getSosede(){
    kandidati.push_back(sosedi[0]);
    vrsta.vstavi(sosedi[0]);
    for(int i = 1; i <= L; i++){
        if (sequence[i-1] == -1){
            sosedi[i][i-1] = 1;
        }
        else{
            sosedi[i][i-1] = -1;
        }
        vrsta.vstavi(sosedi[i]);
    }
}

void randomize(){
    random_device rd;
    mt19937 mt(seed+nfes);
    uniform_int_distribution<int> dist(0,1);
    for ( int i = 0; i < L; i++){
        sequence.push_back(dist(mt));
    }
    for ( int i = 0; i < L; i++){
        if(sequence[i] == 0){
            sequence[i] = -1;
        }
    }
}

void getPSL(int ckHigh, vector<int> seq){
    if (ckHigh < PSL){
        myMutex.lock();
        if (ckHigh < PSL) {
            PSL = ckHigh;
            bestPSLSequence = seq;
        }
        myMutex.unlock();
    }
}

void getMF(vector <int> sequence, double ckVsota){
    double L2 = L * L;
    double multi = 2;
    double mf = L2/(multi*ckVsota);
    if (mf > MF){
        MF = mf;
        bestMFSequence = sequence;
    }
}

void Ck(vector <int> sequence){
    vector <int> Cks;
    int ck = 0;
    double ckVsota = 0;
    int ckHigh = 0;
    for (int k = 1; k < L; k++){
        for(int i = 0; i < L-k; i++){
            ck += sequence[i] * sequence[i+k];
        }
        int ck2 = ck * ck;
        if (ck <0){
            ck = -ck;
        }
        if (ck > ckHigh){
            ckHigh = ck;
        }
        ckVsota += ck2;
        ck = 0;
    }
    getPSL(ckHigh, sequence);
    getMF(sequence, ckVsota);
}

void threadRun(){
    while(nfes<nfesLmt){
        vector<int> tmp = vrsta.beri();
        Ck(tmp);
    }
}

void exeThreads(int threads){
    for (int i = 0; i < threads; i++){
        guide.push_back(thread (threadRun));
    }
}

void getRandomSequence(int L) {
    exeThreads(threads);
    while (nfes < nfesLmt) {
        this_thread::sleep_for(1ms);
        if (vrsta.vrsta.empty()) {
            randomize();
            for (int i = 0; i <= L; i++) {
                if (nfes < nfesLmt) {
                    sosedi.push_back(sequence);
                    nfes++;
                }
            }
            getSosede();
            sequence.clear();
            sosedi.clear();
        }
    }
    for (int i = 0; i < threads; i++){
        guide[i].join();
    }
    for (int i = 0; i < threads; i++){
        guide.pop_back();
    }
}

int main(int argc, char *argv[]) {
    //for (int i = 0; i < argc; ++i)
    //    cout << argv[i] << "\n";
    //L = reinterpret_cast<int>(argv[0]);
    //seed = reinterpret_cast<int>(argv[1]);
    //nfesLmt = reinterpret_cast<int>(argv[2]);
    cout << "enter seed: " << endl;
    cin >> seed;
    cout << "enter threads: " << endl;
    cin >> threads;
    auto start = high_resolution_clock::now();
    thread a(getRandomSequence, L);
    a.join();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "L: " << L << endl;
    cout << "NfesLmt: " << nfesLmt << endl;
    cout << "seed: " << seed << endl;
    cout << "Runtime in seconds:" << duration.count() << endl;
    double speed = nfesLmt / duration.count();
    cout << "Speed: " << speed << endl;
    cout << "\n" << "best PSL: " << PSL << endl;
    cout << "sequence: " << endl;
    for (int i = 0; i < L; ++i) {
        cout << bestPSLSequence[i] << ", ";
    }
    cout << "\n" <<"best MF: " << MF << endl;
    cout << "sequence: " << endl;
    for (int i = 0; i < L; ++i) {
        cout << bestMFSequence[i] << ", ";
    }
    return 0;
}
