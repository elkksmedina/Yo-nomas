/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: saleth
 *
 * Created on 4 de abril de 2025, 16:01
 */

 #include <cstdlib>
 #include <iostream>
 #include <iomanip>
 #include <cmath>
 #include <fstream>
 
 using namespace std;
 
 #define MAX_ARMAS 12
 #define MAX_GUERREROS 3
 #define MAX_REQUISITOS 3
 #define MAX_TIPOS 3
 
 /*
  * 
  */
 struct Arma{
     char letra;
     int poder;
     int tipo;
     int ind_requisitos[MAX_REQUISITOS];
     int cant_requi;
     bool usada;
 };
 struct Guerrero{
     int poder;
     int tipo_armas[MAX_TIPOS];
     int cant_tipos;
 };
 struct Mochila{
     int cant_armas;
     int ind_armas[MAX_ARMAS];
 };
 
 void cargarArmas(Arma armas[]){
     armas[0]={'Z',60,3,{},0,false};
     armas[1]={'P',80,1,{0},1,false};
     armas[2]={'R',38,2,{},0,false};
     armas[3]={'D',25,2,{2},1,false};
     armas[4]={'E',49,2,{},0,false};
     armas[5]={'F',57,1,{},0,false};
     armas[6]={'G',68,3,{},0,false};
     armas[7]={'H',35,2,{0,4},2,false};
     armas[8]={'I',62,2,{2},1,false};
     armas[9]={'J',42,2,{},0,false};
     armas[10]={'K',36,1,{0},1,false};
     armas[11]={'L',54,3,{},0,false};
 }
 
 void cargarGuerreros(Guerrero guerreros[]){
     guerreros[0]={120,{2},1};
     guerreros[1]={160,{1,3},2};
     guerreros[2]={80,{3},1};
 }
 
 void convertirBinario(int num,int cromosoma[],int N){
     int i;
     for(i=0;i<N;i++) cromosoma[i]=0;//inicializo todos los slots en 0
     i=0;
     while(num!=0){
         cromosoma[i++]=num%2;
         num=num/2;
     }
 }
 
 void llenarMochila(Mochila& m,int combinacion[],int slots){
     int indice=0;
     m.cant_armas=0;
     for(int k=0;k<slots;k++){//3er nivel ind_armas
         if(combinacion[k]==1){
             m.ind_armas[indice]=k;
             m.cant_armas++;
             indice++;
         }
     }
 }
 
 bool armaPermitida(int tipo,Guerrero g){
     for(int i=0;i<g.cant_tipos;i++)
         if(tipo==g.tipo_armas[i]) return true;
     return false;
 }
 bool requisitosCumplidos(Mochila m,Arma armas[],int ind_arma){
     for(int i=0;i<armas[ind_arma].cant_requi;i++){
         int ind=armas[ind_arma].ind_requisitos[i];
         bool encontrado=false;
         for(int j=0;j<m.cant_armas;j++){
             if(m.ind_armas[j]==ind){
                 encontrado=true;
                 break;
             }
         }
         if(!encontrado)return false;
     }
     return true;
 }
 bool verificarMochila(Mochila m,Arma armas[],Guerrero g){
     int poderTotal=0;
     for(int i=0;i<m.cant_armas;i++){
         int ind=m.ind_armas[i];
         if(armas[ind].usada) return false;
         if(!armaPermitida(armas[ind].tipo,g))return false;
         if(!requisitosCumplidos(m,armas,ind))return false;
         poderTotal+=armas[ind].poder;
     }
     return poderTotal>g.poder;
 }
 
 void actualizarArmas(Mochila m,Arma armas[]){
     for(int i=0;i<m.cant_armas;i++)
         armas[m.ind_armas[i]].usada=true;
 }
 void imprimirMochila(Mochila m){
     for(int i=0;i<m.cant_armas;i++)
         cout<<m.ind_armas[i]<<" ";
     cout<<endl;
 }
 void cargarMochilas(Arma armas[],Guerrero guerreros[],int totalArmas,int totalGuerreros){
     int total_combinaciones=pow(2,totalArmas);
     int cromosoma[total_combinaciones];
     Mochila mochila[totalGuerreros];
     
     for(int i=0;i<totalGuerreros;i++){//1 nivel mochila
         for(int j=1;j<=total_combinaciones;j++){//2do nivel comb_armas
             Mochila bufferMochila;
             convertirBinario(j,cromosoma,totalArmas);
             llenarMochila(bufferMochila,cromosoma,totalArmas);
             if(verificarMochila(bufferMochila,armas,guerreros[i])){
                 actualizarArmas(bufferMochila,armas);
                 mochila[i]=bufferMochila;
                 imprimirMochila(mochila[i]);
             }
         }
     } 
 }
 
 int main(int argc, char** argv) {
     int totalArmas=12;
     int totalGuerreros=3;
     Arma armas[MAX_ARMAS]{};
     Guerrero guerreros[MAX_GUERREROS]{};
     
     cargarArmas(armas);
     cargarGuerreros(guerreros);
     cargarMochilas(armas,guerreros,totalArmas,totalGuerreros);
 
     return 0;
 }
 
 
 