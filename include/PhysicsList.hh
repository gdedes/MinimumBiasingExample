#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4PhysListFactory.hh"

class PhysicsList: public G4VModularPhysicsList
{
public:
    PhysicsList(G4String );
    virtual ~PhysicsList();
    
    void ConstructPhysicsList();
    void ConstructProcess();
    virtual void SetCuts();
    

private:
    G4VModularPhysicsList* phys;
    
    G4double fCutForGamma;
    G4double fCutForElectron;
    G4double fCutForPositron;
    G4double fCutForProton;
};

#endif
