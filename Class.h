#pragma once
class Point3D {
private:
    int x, y, z;
public:
    Point3D(const int& newx, const int& newy, const int& newz);
    int GetX();
    int GetY();
    int GetZ();
    float distanceTo(const Point3D& otherPoint3D);
};

class Runner {
private:
    int weight;       //poids en kg
    float size;         //taille en mètre
    int shoesWeight;    //poids en grammes
    float avgSpeed;     //vitesse en km/h
    int training;       //en semaines
    int dossard;
public:
    Runner();
    Runner(int& newweight,
        float& newsize,
        int& newshoesweight,
        float& newavgspeed,
        int& newtraining,
        int& newdossard);
    int GetWeight();
    float GetSize();
    int GetShoesWeight();
    float GetAvgSpeed();
    int GetTraining();
    int GetDossard();
    void SetWeight(int weight);
    void SetSize(float size);
    void SetShoesWeight(int shoes);
    void SetAvgSpeed(float avgspeed);
    void SetTraining(int training);
    void SetDossard(int dossard);
};

class InfosRunner : public Runner {
private:
    Runner michel;
    float vinst;
    float traveled;
    int hydratation;
public:
    InfosRunner();
    InfosRunner(Runner& newmichel,
        float& newvinst,
        float& newtraveled,
        int& newhydratation);
    Runner GetMichel();
    float GetVinst();
    float GetTraveled();
    int GetHydratation();
    void SetVinst(float vinst);
    void SetTraveled(float traveled);
    void SetHydratation(int hydratation);

};