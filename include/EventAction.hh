
#ifndef STEventAction_h
#define STEventAction_h 1


#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction( const G4Event* );
    virtual void EndOfEventAction( const G4Event* );
};

#endif