/////////////////////////////////////////////////////
// Geant4 application for shielding and channeling
// Developed by George Dedes
// for the Space Talos Ltd
// https://spacetalos.com/

// kernel headers
#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"

// user headers
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "EventAction.hh"
//#include "STRunAction.hh"
//#include "STStackingAction.hh"
#include "SteppingAction.hh"

int main( int argc, char** argv )
{
    G4cout << "//----------------------------------------------------------//" << G4endl;
    G4cout << "// Minimal Biasing Example by Space Talos //" << G4endl;
    G4cout << "//----------------------------------------------------------//" << G4endl;

    // passing reference physics list to factory
    G4String physName = "QGSP_BIC_HP_EMZ";

    // Choose the Random engine
    G4Random::setTheEngine( new CLHEP::RanecuEngine );


    // Construct the default run manager
    auto* runManager = new G4RunManager;

    // user initializations and actions
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList(physName));
    runManager->SetUserAction(new PrimaryGeneratorAction());
//    runManager->SetUserAction(new STRunAction());
    runManager->SetUserAction(new EventAction());
//    runManager->SetUserAction(new STStackingAction());
    runManager->SetUserAction(new SteppingAction());

    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto* UImanager = G4UImanager::GetUIpointer();
    // Process macro or start UI session
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand( command+fileName );


    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !#include "G4UIExecutive.hh"
    delete visManager;
    delete runManager;
}
