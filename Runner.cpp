#include <iostream>
#include "Runner.h"

using namespace std;

Runner::Runner(const float& newweight,
    const float& newsize,
    const int& newshoesweight,
    const float& newavgspeed,
    const int& newtraining,
    float& newhydratation,
    float& newtraveled) :
    weight(newweight),
    size(newsize),
    shoesWeight(newshoesweight),
    avgSpeed(newavgspeed),
    training(newtraining),
    hydratation(newhydratation),
    traveled(newtraveled) {};
void Runner::SetHydratation(float& newhydratation) {
    hydratation = newhydratation;
}
void Runner::SetTraveled(float& newtraveled) {
    traveled = newtraveled;
}
const float Runner::GetSize() {
    return size;
}
const int Runner::GetShoesWeight() {
    return shoesWeight;
}
const float Runner::GetAvgSpeed() {
    return avgSpeed;
}
const int Runner::GetTraining() {
    return training;
}
float Runner::GetHydratation() {
    return hydratation;
}
float Runner::GetTraveled() {
    return traveled;
}