/////////////////////////////////////////////////////
// DetectorConstruction class
// for the creation of mass geometry volumes

// user headers
#include "DetectorConstruction.hh"
#include "GB01BOptrMultiParticleChangeCrossSection.hh"

// kernel headers
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UserLimits.hh"

//////////////////////////////////////////////////
// constructor
DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{}

//////////////////////////////////////////////////
// destructor
DetectorConstruction::~DetectorConstruction()
{}

//////////////////////////////////////////////////
// concrete implementation of virtual Construct
G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Get NIST material manager
    G4NistManager* nist = G4NistManager::Instance();

    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;

    //////////////////////////////////////////////////////////////////////
    // World
    const G4double world_sizeX = 1. *m;
    const G4double world_sizeY = 1. *m;
    const G4double world_sizeZ  = 1. *m;
    
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4cout << "Material Name for World: " << world_mat << G4endl;

    // define the solid for the world
    auto* solidWorld = new G4Box( "WorldS", world_sizeX, world_sizeY, world_sizeZ );

    // define the logical volume for the world
    auto* logicWorld = new G4LogicalVolume( solidWorld, world_mat, "WorldL" );

    // place the world
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, // no rotation
                               G4ThreeVector(),  // at (0,0,0)
                               logicWorld,     // its logical volume
                               "WorldP", // its name
                               nullptr, // its mother volume
                               false,   // no boolean operation
                               0,     // copy number
                               checkOverlaps); // overlaps checking

    //////////////////////////////////////////////////////////////////////
    // A box-shaped target
    const G4double target_sizeX = 0.5 *m;
    const G4double target_sizeY = 0.5 *m;
    const G4double target_sizeZ  = 0.5 *m;

    G4Material* target_mat = nist->FindOrBuildMaterial("G4_WATER");
    G4cout << "Material Name for Target: " << target_mat << G4endl;

    // define the solid for the target
    auto* solidTarget = new G4Box( "TargetS", target_sizeX, target_sizeY, target_sizeZ );

    // define the logical volume for the target
    auto* logicTarget = new G4LogicalVolume( solidTarget, target_mat, "TargetL" );

    // place the target
    G4VPhysicalVolume* physTarget = new G4PVPlacement(nullptr, // no rotation
                                                     G4ThreeVector(),  // at (0,0,0)
                                                     logicTarget,     // its logical volume
                                                     "TargetP", // its name
                                                     logicWorld, // its mother volume
                                                     false,   // no boolean operation
                                                     0,     // copy number
                                                     checkOverlaps); // overlaps checking

    // Sets a max step length, with G4StepLimiter
    G4double maxStep = 10.0*mm; // arbitrary value, to be tuned
    fStepLimit = new G4UserLimits(maxStep);
    logicWorld->SetUserLimits(fStepLimit);

    // always return the physical World
    return physWorld;
}

// TODO port biasing into the chip class
/////////////////////////////////////////////////////////
// concrete implementation of virtual ConstructSDandField
void DetectorConstruction::ConstructSDandField() {
    // Biasing
    // -- Fetch volume for biasing:
    G4LogicalVolume *logicBias1 = G4LogicalVolumeStore::GetInstance()->GetVolume("TargetL"); // hardcoded name!

    GB01BOptrMultiParticleChangeCrossSection *testBias1 = new GB01BOptrMultiParticleChangeCrossSection();
    testBias1->AttachTo(logicBias1);
    testBias1->AddParticle("proton");
    G4cout << " Attaching biasing operator " << testBias1->GetName()
           << " to logical volumes " << logicBias1->GetName()
           << G4endl;

}
