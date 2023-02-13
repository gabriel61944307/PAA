/*
    Gabriel Rodrigues Malaquias - 758906
    Trabalho 1 de PAA - seleção do n-ésimo maior número em um vetor desordenado.
*/


#include <bits/stdc++.h>

using namespace std;

double resp = -1;

int partition(vector<double> &v, int inicio, int fim){
    double pivo = v[fim];
    int i = inicio, j = inicio;
    while(j < fim){
        if(v[j] <= pivo){
            double aux = v[j];
            v[j] = v[i];
            v[i] = aux;
            i++;
        }
        j++;
    }
    v[fim] = v[i];
    v[i] = pivo;

    return i;
}

void quickSort(vector<double> &v, int inicio, int fim, int k){
    if(inicio < fim){
        int pivo = partition(v, inicio, fim);
        /*for(int i = 0; i < v.size(); i++){
            cout << v[i] << " ";
        }
        cout << endl;*/
        if(pivo == (v.size() - k)) {
            resp = v[pivo];
            return;
        }
        else if(pivo > (v.size() - k))  quickSort(v, inicio, pivo-1, k);
        else    quickSort(v, pivo+1, fim, k);
    }
}

int main(){
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int k; cin >> k;
        int c; cin >> c;
        vector<double> v(c);
        for(int j = 0; j < c; j++){
            cin >> v[j];
        }
        
        quickSort(v, 0, c-1, k);
        if(resp == -1) cout << fixed << setprecision(2) << v[v.size() - k] << endl;
        else cout << fixed << setprecision(2) << resp  << endl;
        resp = -1;
    }



    return 0;
}
