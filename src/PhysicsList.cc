/////////////////////////////////////////////////////
// ModularPhysicsList class
// for channeling applications
// https://geant4.kek.jp/lxr/source/examples/extended/medical/GammaTherapy/src/PhysicsList.cc

// user headers
#include "PhysicsList.hh"

// kernel headers
#include "G4PhysListFactory.hh"
#include "G4SystemOfUnits.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4GenericBiasingPhysics.hh"

//////////////////////////////////////////////////
// constructor
PhysicsList::PhysicsList(G4String refListName): G4VModularPhysicsList()
{
    SetVerboseLevel(1);
    
    // production cuts (the contents of the chip have different cuts. See chip classes)
    fCutForGamma     = 1.0*mm;
    fCutForElectron  = 1.0*mm;
    fCutForPositron  = 1.0*mm;
    fCutForProton    = 1.0*mm;
    
    G4PhysListFactory factory; // use factory to build from reference list

    phys = nullptr; // G4VModularPhysicsList object

    // using G4PhysListFactory to check
    // if reference physics list name is valid
    if (factory.IsReferencePhysList(refListName)){
        phys = factory.GetReferencePhysList(refListName);
        G4cout << "STPhysicsList::Importing reference physics list: " << refListName << G4endl;
        
        // Attention: additions need to be done here!
        // Add step limit process from builder
        phys->RegisterPhysics(new G4StepLimiterPhysics());

        // Biasing
        auto* biasingPhysics = new G4GenericBiasingPhysics;

        // change EM models and biasing options
        phys->ReplacePhysics(new G4EmLivermorePhysics);

        std::vector< G4String > processesToBias;
        processesToBias.push_back( "protonInelastic" ); //
//        processesToBias.push_back( "hadElastic" ); //
        biasingPhysics->PhysicsBias( "proton", processesToBias );

        phys->RegisterPhysics(biasingPhysics);

    }
    // abort if no valid physics list
    if (!phys) {
        G4cout << "STPhysicsList::No valid physics list defined:" << refListName << G4endl;
        abort();
    }

    // print and register all physics from that list
    for (G4int i = 0; ; ++i) {
        auto* elem = const_cast<G4VPhysicsConstructor*> (phys->GetPhysics(i));
        if (elem == nullptr) break;
        G4cout << "STPhysicsList::Register physics: " << elem->GetPhysicsName() << G4endl;
        RegisterPhysics(elem);
    }    
}

//////////////////////////////////////////////////
// destructor
PhysicsList::~PhysicsList()
{
    delete phys;
}

//////////////////////////////////////////////////
// construct all the physics process from models
void PhysicsList::ConstructProcess()
{    
//    phys->SetApplyCuts(true,"all");
    phys->ConstructProcess();
}

//////////////////////////////////////////////////
// set production thresholds
void PhysicsList::SetCuts()
{
    // set cut values for gamma at first and for e- second and next for e+,
    // because some processes for e+/e- need cut values for gamma
    SetCutValue(fCutForGamma, "gamma");
    SetCutValue(fCutForElectron, "e-");
    SetCutValue(fCutForPositron, "e+");
    SetCutValue(fCutForProton, "proton");
    DumpCutValuesTable();
}
