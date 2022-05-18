/// \file B1PrimaryGeneratorAction.hh
/// \brief Definition of the B1PrimaryGeneratorAction class

#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "B1EventAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "g4root.hh"
#include "g4analysis.hh"
#include "TFile.h"
#include "TTree.h"
#include "TThread.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
// #include "CLHEP/Units/SystemOfUnits.h"
#include "G4Event.hh"
#include "G4RunMessenger.hh"
#include "G4GenericMessenger.hh" //added


class G4ParticleGun;   
class G4Event;
class G4Box;
class G4UIdirectory;
class G4UIcmdWithABool;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class B1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    B1PrimaryGeneratorAction();    
    virtual ~B1PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  
  private:
    G4ParticleGun*  fParticleGun; // gun for leptons
    G4ParticleGun*  fParticleGun1; //gun for hadrons
    G4Box* fEnvelopeBox;
    static G4ParticleTable* fParticleTable;
    TTree *gst;
    TFile *input;
    int pdg ,id,counter,entry;
    double E,px,py,pz;
    bool cc,nc,qes,mec,dis,coh,res , interaction ,scattering;
    G4String interaction_type , Scattering_type , data_file;
    int arr[7000];

    double vx,vy,vz;

   G4GenericMessenger *fMessenger;
  //  G4GenericMessenger *fcc;
  //  G4GenericMessenger *fnc;
  //  G4UIdirectory *genie;
  

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
