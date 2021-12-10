
/////////////////////////////////////////////////////
// SteppingAction class for testing purposes

// user headers
#include "SteppingAction.hh"

// kernel headers
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"


//////////////////////////////////////////////////
// constructor
SteppingAction::SteppingAction()
        : G4UserSteppingAction()
{}


//////////////////////////////////////////////////
// deconstructor
SteppingAction::~SteppingAction()
{}


//////////////////////////////////////////////////
// accessing every step
void SteppingAction::UserSteppingAction( const G4Step* aStep )
{
    G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    if (eventID>-1) {
        if (aStep->GetTrack()->GetTrackID() == 1) {
            G4cout << "UserSteppingAction: PDG = " << aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding()
                   << " , in volume = " << aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()
                   << " , with weight = " << aStep->GetPreStepPoint()->GetWeight()
                   << " , from POSTstep process: " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()
                   << " , trackID = " << aStep->GetTrack()->GetTrackID()
                   << " , parentID = " << aStep->GetTrack()->GetParentID()
                   << " , current step = " << aStep->GetTrack()->GetCurrentStepNumber()
                   << G4endl;
        }
        if (aStep->GetPostStepPoint()->GetProcessDefinedStep() && aStep->GetTrack()->GetCreatorProcess()){
            G4cout << "UserSteppingAction: PDG = " << aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding()
               << " , in volume = " << aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()
               << " , with weight = " << aStep->GetPreStepPoint()->GetWeight()
               << " from POSTstep process: " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()
               << " , creator process " << aStep->GetTrack()->GetCreatorProcess()->GetProcessName()
               << " , trackID = " << aStep->GetTrack()->GetTrackID()
               << " , parentID = " << aStep->GetTrack()->GetParentID()
               << " , current step = " << aStep->GetTrack()->GetCurrentStepNumber()
               << G4endl;
        }
    }

}