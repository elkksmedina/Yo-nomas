/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: saleth
 *
 * Created on 4 de abril de 2025, 21:04
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstring>

using namespace std;

#define N 4
#define P 100

/*
 * 
 */

void convertirBinario(int num,int cromosoma[],int slots){
    int i;
    for(i=0;i<slots;i++)cromosoma[i]=0;
    i=0;
    while(num!=0){
        cromosoma[i++]=num%2;
        num=num/2;
    }
}

void imprimirMatriz(int matriz[][N],int cromosoma[],int slots,int n){
    for(int i=0;i<slots;i++){//recorre cromosoma
        if(0<i and i%n==0)cout<<endl;
        if(cromosoma[i]==1){
            int fila=i/n, columna=i%n;
            cout<<right<<setw(3)<<matriz[fila][columna];
        }else{
            cout<<right<<setw(3)<<0;
        }
    }
    cout<<endl<<endl;
}

void encontrarSolucionOptima(int pesos[][N],int valores[][N],int n,int p){
    int espacioDisp=pow(n,2);
    int totalComb=pow(2,espacioDisp);
    int cromosoma[espacioDisp]{};
    int pesoOptimo=0,valorOptimo=0,combinacionOptima;
    
    for(int i=1;i<=totalComb;i++){//combinaciones
        int pesoAcumulado=0,valorAcumulado=0;
        convertirBinario(i,cromosoma,espacioDisp);
        for(int j=0;j<espacioDisp;j++){//recorre cromosoma
            if(cromosoma[j]==1){
                int fila=j/n, columna=j%n;
                pesoAcumulado+=pesos[fila][columna];
                valorAcumulado+=valores[fila][columna];
            }
        }
        if(pesoAcumulado<=p and (pesoOptimo<pesoAcumulado or
                (pesoOptimo==pesoAcumulado and valorOptimo<valorAcumulado))){
            pesoOptimo=pesoAcumulado;
            valorOptimo=valorAcumulado;
            combinacionOptima=i;
        }
    }
    convertirBinario(combinacionOptima,cromosoma,espacioDisp);
    cout<<"PESOS (Toneladas)"<<endl;
    imprimirMatriz(pesos,cromosoma,espacioDisp,n);
    cout<<"VALORES (Miles de $)"<<endl;
    imprimirMatriz(valores,cromosoma,espacioDisp,n);
}

int main(int argc, char** argv) {
    int n=4,p=100;
    int pesos[N][N]={{20,20,20,20},
                     {10,30,10,30},
                     {10,10,10,10},
                     {15,15,15,15}};
    int valores[N][N]={{10,10,10,50},
                       {80,10,10,20},
                       {20,20,20,20},
                       {50,50,50,50}};
    encontrarSolucionOptima(pesos,valores,n,p);
    return 0;
}
