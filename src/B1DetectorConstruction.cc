/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
// Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 18*m, env_sizeZ = 14*m;
  // G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;
    
  // World
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld =    
    new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,world_mat, "World");
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                    
                      G4ThreeVector(),logicWorld, "World", 0,false,  0,  checkOverlaps); 

 for (G4int i=-75 ;i<=75 ;i++) 
{
  //iron plate

  G4Material* iron_plate_mat = nist->FindOrBuildMaterial("G4_Fe");

  G4Box* solidIronPlate =    
    new G4Box("IronPlate",0.5*16*m, 0.5*16*m, 0.5*5.6*cm);
      
  G4LogicalVolume* logicIronPlate =                         
    new G4LogicalVolume(solidIronPlate,iron_plate_mat,"IronPlate");
               
  new G4PVPlacement(0,G4ThreeVector(0,0,(9.6*i) *cm),logicIronPlate,"IronPlate",logicWorld,false,i,checkOverlaps); 

  //glass plate

  G4Material* glass_plate_mat = nist->FindOrBuildMaterial("G4_GLASS_PLATE");

  G4Box* solidGlass =    
    new G4Box("GlassPlate",0.5*16*m, 0.5*16*m, 0.5*0.01*mm);
      
  G4LogicalVolume* logicGlass=                         
    new G4LogicalVolume(solidGlass,glass_plate_mat,"GlassPlate");
               
  new G4PVPlacement(0,G4ThreeVector(0,0,((9.6*i)+4.8)*cm),logicGlass,"GlassPlate",logicWorld,false,i,checkOverlaps); 

  fScoringVolume = logicGlass;
  }
  //
  return physWorld;
  // G4GDMLParser parser;
  // parser.Read("ical.gdml");
  // G4VPhysicalVolume* World = parser.GetWorldVolume(); 
  // return World;
   
}

void B1DetectorConstruction::ConstructSDandField()
{
  G4ThreeVector fieldValue = G4ThreeVector(0.,1.5*tesla,0.);
  G4GlobalMagFieldMessenger *fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
