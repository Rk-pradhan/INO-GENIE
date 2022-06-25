
void readData()
{
	
TFile *input = TFile::Open("test.root", "READ");
TTree *gst = (TTree*)input->Get("gst");

int entry = gst->GetEntries();

int arr[7000];    //creating an array (u can take any array size more than number of entry)


int id ,n,eid,pdg;
bool cc,nc,qes,mec,dis,coh,res;
double E;
gst->SetBranchAddress("iev",&id);     
gst->SetBranchAddress("cc",&cc);
gst->SetBranchAddress("nc",&nc);
gst->SetBranchAddress("qel",&qes);
gst->SetBranchAddress("mec",&mec);
gst->SetBranchAddress("dis",&dis);
gst->SetBranchAddress("coh",&coh);
gst->SetBranchAddress("res",&res);
// gst->SetBranchAddress("nf",&n);
gst->SetBranchAddress("El",&E);
gst->SetBranchAddress("fspl",&pdg);



string interaction;
bool interaction1;
cout<<"enter interaction type ";           //input for interaction type
cin>>interaction;

string scattering;
bool scattering1;
cout<<"enter scattering type ";            //input for scattering type
cin>>scattering;


int counter=0;                             //to count the number of id with the input interaction and scattering pair.

for (int i=0;i<entry;i++)
{

gst->GetEntry(i);


if (interaction=="cc"){interaction1=cc;}
if (interaction=="nc"){interaction1=nc;}
if (scattering=="qes"){scattering1=qes;}
if (scattering=="mec"){scattering1=mec;}
if (scattering=="dis"){scattering1=dis;}
if (scattering=="coh"){scattering1=coh;}
if (scattering=="res"){scattering1=res;}




// // for (int j =0 ;j<n;j++){
// // int pdg=gst->GetLeaf("pdgf")->GetValue(j);



 if (interaction1 && scattering1)
{
 counter++;
//  cout<<id<<endl;
 arr[counter]=id;

//  cout<<sizeof(array)<<endl;
}


}  //end of loop

cout<<"No of events with this pair "<<counter<<endl;
// for(int j =1;j<=counter;j++)
// {
//     cout<<arr[j]<<endl;
// }

// cout<<arr[5]<<endl;
// cout<<counter<<endl;
// cout <<xx<<endl;



int event_no ;
cout<<"run/beamOn/";       //enter event number (starting from 0)
cin>>event_no;

cout<<"Geant4 event ID: "<<event_no+1<<endl;

cout<<"event id from genie corresponding to G4: "<<arr[event_no+1]<<endl;

gst->GetEntry(arr[event_no+1]);

cout<<"energy of lepton with pid: "<<pdg<<" is "<<E<<endl;    //now you can get any information corresponding to your interaction and scattering pair.

 n=gst->GetLeaf("nf")->GetValue(); 
for (int j =0 ;j<n;j++){
int pdgh=gst->GetLeaf("pdgf")->GetValue(j);
double pxh=gst->GetLeaf("pxf")->GetValue(j);
double pyh=gst->GetLeaf("pyf")->GetValue(j);
double pzh=gst->GetLeaf("pzf")->GetValue(j);
double Eh=gst->GetLeaf("Ef")->GetValue(j);

double ph = sqrt(pxh*pxh+pyh*pyh+pzh*pzh);
cout<<"***********************************************"<<endl;
cout<<"energy of hadron with pid: "<<pdgh<<" is "<<Eh<<endl;

cout<<"Momentum of hadron with pid: "<<pdgh<<" is "<<ph<<endl;
cout<<"***********************************************"<<endl;

}


}
