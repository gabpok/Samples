#include <iostream>
#include <fstream>
using namespace std;

void chi2_spectra_dwa(Int_t energy, Int_t par){
  double x[7] = {0};
  double y[7] = {0};
  double chi[7] = {0};
  double chi2[7] = {0};
  double chi_q[7] = {0};
  char buff1[100];
  sprintf(buff1, "/Users/gabriela/Documents/magister/wyniki/%00i/pt_spectra_%00iGeV_Uboot_p%00i.root", energy, energy, par);
  char buff2[100];
  sprintf(buff2, "/Users/gabriela/Documents/magister/wyniki/%00i/star_bes_%00iGeV_rap25.root", energy, energy);
  TFile *uboot = new TFile(buff1, "READ");
  TFile *star = new TFile(buff2, "READ");

  TH1D *piPositiveUboot = (TH1D*) uboot->Get("pi+");
  TH1D *piNegativeUboot = (TH1D*) uboot->Get("pi-");
  TH1D *kaPositiveUboot = (TH1D*) uboot->Get("K+");
  TH1D *kaNegativeUboot = (TH1D*) uboot->Get("K-");
  TH1D *prUboot = (TH1D*) uboot->Get("p");
  TH1D *antPrUboot = (TH1D*) uboot->Get("pbar");

  TH1D *piPositiveStar = (TH1D*) star->Get("pi+");
  TH1D *piNegativeStar = (TH1D*) star->Get("pi-");
  TH1D *kaPositiveStar = (TH1D*) star->Get("K+");
  TH1D *kaNegativeStar = (TH1D*) star->Get("K-");
  TH1D *prStar = (TH1D*) star->Get("p");
  TH1D *antPrStar = (TH1D*) star->Get("pbar");

  int ndf = 13;
  int bin = 13;
  for(int i = 1; i <= bin; i++){
      //positive pion
      x[0] = piPositiveUboot->GetBinContent(i);
      y[0] = piPositiveStar->GetBinContent(i+6);
      //negative pion
      x[1] = piNegativeUboot->GetBinContent(i);
      y[1] = piNegativeStar->GetBinContent(i+6);
      //positive kaon
      x[2] = kaPositiveUboot->GetBinContent(i);
      y[2] = kaPositiveStar->GetBinContent(i+6);
      //negative kaon
      x[3] = kaNegativeUboot->GetBinContent(i);
      y[3] = kaNegativeStar->GetBinContent(i+6);
      //proton
      x[4] = prUboot->GetBinContent(i);
      y[4] = prStar->GetBinContent(i+6);
      //pbar
      x[5] = antPrUboot->GetBinContent(i);
      y[5] = antPrStar->GetBinContent(i+6);
      //All
      x[6] = x[0] + x[1] + x[2] + x[3] + x[4] + x[5];
      y[6] = y[0] + y[1] + y[2] + y[3] + y[4] + y[5];
      for(int j = 0; j < 7; j++){
        chi[j] += (y[j] - x[j])*(y[j] - x[j])/x[j];
      }
    }

  for(int i = 0; i < 7; i++){
    chi2[i] = chi[i]/ndf;
  }

  ofstream os;
  char buff3[100];
  sprintf(buff3, "/Users/gabriela/Documents/magister/wyniki/%00i/%00i_p%000i.txt", energy, energy, par);
  os.open(buff3, ios::app);
  os<<"Pi+ :"<<chi2[0]<<endl;
  os<<"Pi- :"<<chi2[1]<<endl;
  os<<"Ka+ :"<<chi2[2]<<endl;
  os<<"Ka- :"<<chi2[3]<<endl;
  os<<"P :"<<chi2[4]<<endl;
  os<<"Pbar :"<<chi2[5]<<endl;
  os<<"All :"<<chi2[6]<<endl;
  os<<"        "<<endl;
  os<<"Pi+ :"<<chi2_err[0]<<endl;
  os<<"Pi- :"<<chi2_err[1]<<endl;
  os<<"Ka+ :"<<chi2_err[2]<<endl;
  os<<"Ka- :"<<chi2_err[3]<<endl;
  os<<"P :"<<chi2_err[4]<<endl;
  os<<"Pbar :"<<chi2_err[5]<<endl;
  os<<"All :"<<chi2_err[6]<<endl;
  os.close();
}
