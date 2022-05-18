/// \file B1PrimaryGeneratorAction.cc
/// \brief Implementation of the B1PrimaryGeneratorAction class

#include "B1PrimaryGeneratorAction.hh"
#include "G4RunMessenger.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), //1st gun
  fParticleGun1(0), //2nd gun
  fEnvelopeBox(0)  
  
{


//creating messengers for input

fMessenger = new G4GenericMessenger(this,"/genie/");
fMessenger->DeclareProperty("interaction_type",interaction_type,"interaction type");
fMessenger->DeclareProperty("Scattering_type",Scattering_type,"scattering type");
fMessenger->DeclareProperty("data_file",data_file,"genie data file");  //use this if you want to give data file as an input


//reading the data file...................................


input = TFile::Open("withflux31.root", "READ");   //
gst = (TTree*)input->Get("gst");

entry = gst->GetEntries();

//interaction and scattering
gst->SetBranchAddress("cc",&cc);
gst->SetBranchAddress("nc",&nc);
gst->SetBranchAddress("qel",&qes);
gst->SetBranchAddress("mec",&mec);
gst->SetBranchAddress("dis",&dis);
gst->SetBranchAddress("coh",&coh);
gst->SetBranchAddress("res",&res);
//data for leptons
gst->SetBranchAddress("iev",&id);
gst->SetBranchAddress("fspl",&pdg);
gst->SetBranchAddress("El",&E);
gst->SetBranchAddress("pxl",&px);
gst->SetBranchAddress("pyl",&py);
gst->SetBranchAddress("pzl",&pz);

//vertex
gst->SetBranchAddress("vtxx",&vx);
gst->SetBranchAddress("vtxy",&vy);
gst->SetBranchAddress("vtxz",&vz);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fParticleGun1;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{


// TFile *input = TFile::Open(data_file, "READ");   //if you want to give genie data file as input, uncomment line (70-93) and comment reading file in above (27-51)
// gst = (TTree*)input->Get("gst");

// entry = gst->GetEntries();

// //interaction and scattering
// gst->SetBranchAddress("cc",&cc);
// gst->SetBranchAddress("nc",&nc);
// gst->SetBranchAddress("qel",&qes);
// gst->SetBranchAddress("mec",&mec);
// gst->SetBranchAddress("dis",&dis);
// gst->SetBranchAddress("coh",&coh);
// gst->SetBranchAddress("res",&res);
// //data for leptons
// gst->SetBranchAddress("iev",&id);
// gst->SetBranchAddress("fspl",&pdg);
// gst->SetBranchAddress("El",&E);
// gst->SetBranchAddress("pxl",&px);
// gst->SetBranchAddress("pyl",&py);
// gst->SetBranchAddress("pzl",&pz);
// //vertex
// gst->SetBranchAddress("vtxx",&vx);
// gst->SetBranchAddress("vtxy",&vy);
// gst->SetBranchAddress("vtxz",&vz);

//filtering
counter=0;
for (int i=0;i<entry;i++)
{
  gst->GetEntry(i);
  if (interaction_type=="cc"){interaction=cc;}
  if (interaction_type=="nc"){interaction=nc;}
  if (Scattering_type=="qes"){scattering=qes;}
  if (Scattering_type=="mec"){scattering=mec;}
  if (Scattering_type=="dis"){scattering=dis;}
  if (Scattering_type=="coh"){scattering=coh;}
  if (Scattering_type=="res"){scattering=res;}
  if (interaction && scattering)
  {
    counter++;
//  cout<<id<<endl;
    arr[counter]=id;   //array for filtered ID
  }
}
G4cout<<"No of events with this pair "<<counter<<G4endl;

G4int eventid = anEvent->GetEventID(); //G4 Event ID
// G4cout<<"eventid is "<<eventid<<G4endl;

gst->GetEntry(arr[eventid+1]);  //getting entry corresponding to eventID
G4cout<<"event id from genie corresponding to G4 ID: "<<arr[eventid+1]<<G4endl;


//for leptons

fParticleGun  = new G4ParticleGun(1);
G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
G4ParticleDefinition* particle  = particleTable->FindParticle(pdg);
fParticleGun->SetParticleDefinition(particle);

double p = sqrt(px*px+py*py+pz*pz);  //momentum

// fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px/p,py/p,-pz/p)); 
fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px/p,py/p,pz/p));

fParticleGun->SetParticleEnergy(E *GeV);
fParticleGun->SetParticleMomentum(p *GeV);

// double x0= 16*(G4UniformRand()-0.5);  //random number between -8 and 8

// G4cout<<"x0: "<<x0<<G4endl;
// fParticleGun->SetParticlePosition(G4ThreeVector(x0 *m,x0 *m ,+7.4*m));
fParticleGun->SetParticlePosition(G4ThreeVector(vx *m,vy *m ,vz*m));


fParticleGun->GeneratePrimaryVertex(anEvent); 


//2nd gun definition for hadrons


int n=gst->GetLeaf("nf")->GetValue();   //number of hadrons in one event

//getting data for hadrons

for (int j =0 ;j<n;j++){
int pdgh=gst->GetLeaf("pdgf")->GetValue(j);  //pdg of final state hadrons
double pxh=gst->GetLeaf("pxf")->GetValue(j);
double pyh=gst->GetLeaf("pyf")->GetValue(j);
double pzh=gst->GetLeaf("pzf")->GetValue(j);
double Eh=gst->GetLeaf("Ef")->GetValue(j);

fParticleGun1  = new G4ParticleGun(n);
G4ParticleTable* particleTable1 = G4ParticleTable::GetParticleTable();
if(pdgh<10002605)     //excluding iron (there is iron in final hadronic system of coh scattering)
{        
G4ParticleDefinition* particle1  = particleTable1->FindParticle(pdgh);
fParticleGun1->SetParticleDefinition(particle1);

double ph = sqrt(pxh*pxh+pyh*pyh+pzh*pzh);  //momentum

// fParticleGun1->SetParticleMomentumDirection(G4ThreeVector(pxh/ph,pyh/ph,-pzh/ph));
fParticleGun1->SetParticleMomentumDirection(G4ThreeVector(pxh/ph,pyh/ph,pzh/ph));

fParticleGun1->SetParticleEnergy(Eh *GeV);
fParticleGun1->SetParticleMomentum(ph *GeV);
}

// double x1= 16*(G4UniformRand()-0.5);    //random number between -8 and 8
// G4cout<<"x1: "<<x1<<G4endl;
// fParticleGun1->SetParticlePosition(G4ThreeVector(x1 *m,x1 *m ,+7.4*m));
fParticleGun1->SetParticlePosition(G4ThreeVector(vx *m,vy *m ,vz*m));


fParticleGun1->GeneratePrimaryVertex(anEvent);

G4cout<<"*****************************************"<<G4endl;

}

// input->Close();

// ************************************************//

}


