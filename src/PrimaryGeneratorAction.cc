/////////////////////////////////////////////////////
// PrimaryGeneratorAction class
// for the creation of the beam

// user headers
#include "PrimaryGeneratorAction.hh"

// kernel headers
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"
#include "G4VPrimaryGenerator.hh"

//////////////////////////////////////////////////
PrimaryGeneratorAction::PrimaryGeneratorAction()  : G4VUserPrimaryGeneratorAction(),
myGPSGun(nullptr)
{

    // Defaults (pencil beam)
    beamX0 = beamY0 = beamZ0 = 0.;
    beamPx = beamPy = 0.;
    beamPz = 1.;

    // particle gun
    myGPSGun = new G4GeneralParticleSource();

    // default particle kinematic
    // they can be overwritten in GeneratePrimaries
    myParticleTable = G4ParticleTable::GetParticleTable();
    myParticle = myParticleTable->FindParticle( "proton" );
    myGPSGun->SetParticlePosition(G4ThreeVector(beamX0, beamY0, beamZ0));
    myGPSGun->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(beamX0, beamY0, beamZ0));
    myGPSGun->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(beamPx, beamPy, beamPz));
    myGPSGun->GetCurrentSource()->GetEneDist()->SetMonoEnergy( 20.*MeV );
    myGPSGun->SetParticleDefinition(myParticle);
}

//////////////////////////////////////////////////
// destructor
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete myGPSGun;
}

//////////////////////////////////////////////////
// concrete implementation of virtual function
// to create primary particles per event
void PrimaryGeneratorAction::GeneratePrimaries( G4Event* anEvent )
{

    myGPSGun->GeneratePrimaryVertex(anEvent);
}
