
/////////////////////////////////////////////////////
// EventAction class

// user headers
#include "EventAction.hh"

// kernel headers
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"


/////////////////////////////////////////////////////
// constructor
EventAction::EventAction() : G4UserEventAction()
{}


/////////////////////////////////////////////////////
// destructor
EventAction::~EventAction()
{}

/////////////////////////////////////////////////////
// do stuff at the beginning of each event
void EventAction::BeginOfEventAction( const G4Event* myEvent )
{
    if (myEvent->GetEventID()%1==0) {
        const G4Run* myRun = G4RunManager::GetRunManager()->GetCurrentRun();
        G4int totNoEvents = myRun->GetNumberOfEventToBeProcessed();
        G4cout << "Processing event: " << myEvent->GetEventID() << " / " << totNoEvents << G4endl;
    }
}


/////////////////////////////////////////////////////
// do stuff at the end of each event
void EventAction::EndOfEventAction( const G4Event* ) {

}

