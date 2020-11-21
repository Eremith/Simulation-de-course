#include <iostream>
#include <cmath>
#include "Class.h"

using namespace std;

Point3D::Point3D(const int& newx, const int& newy, const int& newz) : x(newx), y(newy), z(newz) {}
int Point3D::GetX() {
    return x;
}
int Point3D::GetY() {
    return y;
}
int Point3D::GetZ() {
    return z;
}
float Point3D::distanceTo(const Point3D& otherPoint3D) {
    const int dx = x - otherPoint3D.x;
    const int dy = y - otherPoint3D.y;
    const int dz = z - otherPoint3D.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

Runner::Runner(int& newweight,
    float& newsize,
    int& newshoesweight,
    float& newavgspeed,
    int& newtraining,
    int& newdossard) :
    weight(newweight),
    size(newsize),
    shoesWeight(newshoesweight),
    avgSpeed(newavgspeed),
    training(newtraining),
    dossard(newdossard) {};
Runner::Runner() {
    weight = 0;
    size = 0;
    shoesWeight = 0;
    avgSpeed = 0;
    training = 0;
    dossard = 0;
}
int Runner::GetWeight() {
    return weight;
}
float Runner::GetSize() {
    return size;
}
int Runner::GetShoesWeight() {
    return shoesWeight;
}
float Runner::GetAvgSpeed() {
    return avgSpeed;
}
int Runner::GetTraining() {
    return training;
}
int Runner::GetDossard() {
    return dossard;
}
void Runner::SetWeight(int newweight) {
    weight = newweight;
}
void Runner::SetSize(float newsize) {
    size = newsize;
}
void Runner::SetShoesWeight(int newshoes) {
    shoesWeight = newshoes;
}
void Runner::SetAvgSpeed(float newavgspeed) {
    avgSpeed = newavgspeed;
}
void Runner::SetTraining(int newtraining) {
    training = newtraining;
}
void Runner::SetDossard(int newdossard) {
    dossard = newdossard;
}

InfosRunner::InfosRunner() {
    vinst = 0;
    traveled = 0;
    hydratation = 0;
}
InfosRunner::InfosRunner(Runner& newmichel,
    float& newvinst,
    float& newtraveled,
    int& newhydratation) :
    michel(newmichel),
    vinst(newvinst),
    traveled(newtraveled),
    hydratation(newhydratation) {};
Runner InfosRunner::GetMichel() {
    return michel;
}
float InfosRunner::GetVinst() {
    return vinst;
}
float InfosRunner::GetTraveled() {
    return traveled;
}
int InfosRunner::GetHydratation() {
    return hydratation;
}
void InfosRunner::SetVinst(float newvinst) {
    vinst = newvinst;
}
void InfosRunner::SetTraveled(float newtraveled) {
    traveled = newtraveled;
}
void InfosRunner::SetHydratation(int newhydratation) {
    hydratation = newhydratation;
}