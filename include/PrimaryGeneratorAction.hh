#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class G4GeneralParticleSource;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();

  // method from the base class
  virtual void GeneratePrimaries( G4Event* );

 private:
    G4GeneralParticleSource*  myGPSGun; // pointer a to G4 GPS class
    G4ParticleTable* myParticleTable;
    G4ParticleDefinition* myParticle;

    G4double beamX0;
    G4double beamY0;
    G4double beamZ0;
    G4double beamPx;
    G4double beamPy;
    G4double beamPz;
};

#endif