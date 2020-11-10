#pragma once
class Runner {
private:
    const float weight;       //poids en kg
    const float size;         //taille en mètre
    const int shoesWeight;    //poids en grammes
    const float avgSpeed;     //vitesse en km/h
    const int training;       //en semaines
    float hydratation;        //en pourcentage
    float traveled;           //en km
public:
    Runner(const float& newweight,
        const float& newsize,
        const int& newshoesweight,
        const float& newavgspeed,
        const int& newtraining,
        float& newhydratation,
        float& newtraveled);
    void SetHydratation(float& newhydratation);
    void SetTraveled(float& newtraveled);
    const float GetSize();
    const int GetShoesWeight();
    const float GetAvgSpeed();
    const int GetTraining();
    float GetHydratation();
    float GetTraveled();
};