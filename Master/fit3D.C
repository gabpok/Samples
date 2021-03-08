#include <iostream>
#include <fstream>
using namespace std;

Double_t fit3D(Double_t *q, Double_t *par){
  return 1+par[0]*TMath::Exp(-par[1]*q[0]*q[0]/0.03893755-par[2]*q[1]*q[1]/0.03893755-par[3]*q[2]*q[2]/0.03893755);
}

void getfitprojc(TH3D *expden, TH3D *projhist, TF3 *funqk){
  for (int q1int = 1; q1int <= expden->GetNbinsX(); q1int++)
    for (int q2int = 1; q2int <= expden->GetNbinsY(); q2int++)
      for (int q3int = 1; q3int <= expden->GetNbinsZ(); q3int++) {
	         projhist->SetBinContent(q1int, q2int, q3int,
				   funqk->Eval(expden->GetXaxis()->GetBinCenter(q1int), expden->GetYaxis()->GetBinCenter(q2int),expden->GetZaxis()->GetBinCenter(q3int)));
      }
}

void fit3D(Int_t energy,Int_t kt){
  Double_t mt_7[10] = {0.235, 0.25, 0.271804, 0.32, 0.333136, 0.41, 0.42131, 0.52, 0.523872, 0.535};
  Double_t mt_11[10] = {0.235, 0.25, 0.261515, 0.32, 0.327164, 0.41, 0.415994, 0.52, 0.522246, 0.535};
  Double_t mt_39[10] = {0.235, 0.25, 0.261515, 0.32, 0.334328, 0.41, 0.421988, 0.52, 0.524492, 0.535};
  Double_t mt_62[10] = {0.235, 0.25, 0.27349, 0.32 ,0.335448, 0.41, 0.4233642, 0.52, 0.528566, 0.535};
  Double_t mt[10];

  if (energy == 7){
    for(Int_t i =0; i < 10; i++){
      mt[i] = mt_7[i];
    }
  }
  else if (energy == 11){
    for(Int_t i =0; i < 10; i++){
      mt[i] = mt_11[i];
    }
  }
  else if (energy == 39){
    for(Int_t i =0; i < 10; i++){
      mt[i] = mt_39[i];
    }
  }
  else if (energy == 62){
    for(Int_t i =0; i < 10; i++){
      mt[i] = mt_62[i];
    }
  }
  char Buff[100];
  sprintf(Buff, "/Users/gabriela/Documents/magister/wyniki/tpi/%00i_kt_%00i.root", energy, kt);
  TFile *f = new TFile(Buff);
  TH3D *num = (TH3D*)f->Get("cnuma");
  TH3D *den = (TH3D*)f->Get("cdena");

  int min= 41;
	int max= 42;

	double minY, maxY;
  if(energy == 11 || energy == 62){
    minY = 0.95;
    maxY = 1.3;
  }
  else if(energy == 7 && kt == 4){
    minY = 0.95;
    maxY = 1.4;
  }
  else {
    minY = 0.95;
  	maxY = 1.25;
  }
	double minX = 0.0;
	double maxX = 0.25;

	TH1D *n_out= (TH1D*)(num->ProjectionX("_outx", min, max, min, max, "e"));
  n_out->SetTitle("Out direction");
	n_out->SetMinimum(minY);
	n_out->SetMaximum(maxY);
	n_out->GetXaxis()->SetRangeUser(minX, maxX);
	//n_out->GetXaxis()->SetTitle("k* [GeV/c]");
	n_out->GetYaxis()->SetTitleOffset(1.53);
	n_out->GetYaxis()->SetTitle("CF(k*)");
	n_out->SetMarkerStyle(20);
	n_out->SetMarkerColor(kMagenta-2);
	n_out->SetMarkerSize(1.0);
  TH1D *d_out= (TH1D*)(den->ProjectionX("_outy", min, max, min, max, "e"));

	TH1D *n_side= (TH1D*)(num->ProjectionY("_sidex", min, max, min, max, "e"));
  n_side->SetTitle("Side direction");
  n_side->SetMinimum(minY);
	n_side->SetMaximum(maxY);
	n_side->GetXaxis()->SetRangeUser(minX, maxX);
	n_side->GetYaxis()->SetTitleOffset(0.7);
	n_side->GetYaxis()->SetTitle("CF(k*)     ");
	n_side->SetMarkerStyle(20);
	n_side->SetMarkerColor(kMagenta-2);
	n_side->SetMarkerSize(1.0);
  TH1D *d_side= (TH1D*)(den->ProjectionY("_sidey", min, max, min, max, "e"));

	TH1D *n_long= (TH1D*)(num->ProjectionZ("_longx", min, max, min, max, "e"));
  n_long->SetTitle("Long direction");
  n_long->SetMinimum(minY);
	n_long->SetMaximum(maxY);
	n_long->GetXaxis()->SetRangeUser(minX, maxX);
	n_long->GetXaxis()->SetTitle("k* [GeV/c]");
	n_long->GetYaxis()->SetTitleOffset(0.7);
	n_long->GetYaxis()->SetTitle("CF(k*)     ");
	n_long->SetMarkerStyle(20);
	n_long->SetMarkerColor(kMagenta-2);
	n_long->SetMarkerSize(1.0);
  TH1D *d_long= (TH1D*)(den->ProjectionZ("_longy", min, max, min, max, "e"));

  TH3D *ratio = (TH3D*) num->Clone("Corr");
  ratio->Sumw2();
  ratio->Divide(den);

  TF3 *fit = new TF3("fit", fit3D, 0., 0.15, 0., 0.15, 0., 0.15,4);
  fit->SetParLimits(0, 0.0, 1.0);
  fit->SetParLimits(1, 0.0, 100.0);
  fit->SetParLimits(2, 0.0, 100.0);
  fit->SetParLimits(3, 0.0, 100.0);
  fit->SetParameter(0, 0.1);
  fit->SetParameter(1, 5.0);
  fit->SetParameter(2, 5.0);
  fit->SetParameter(3, 5.0);
  fit->SetParName(0, "Lambda");
  fit->SetParName(1, "R_out Squared");
  fit->SetParName(2, "R_side Squared");
  fit->SetParName(3, "R_long Squared");

  ratio->Fit("fit", "R");

  int first = 0;

  double lambda    = fit->GetParameter(first);
  double lambdaErr = fit->GetParError(first);
  double rout      = sqrt(fit->GetParameter(first+1));
  double routErr   = (fit->GetParError(first+1))/(2*sqrt(fit->GetParameter(first+1)));
  double rside     = sqrt(fit->GetParameter(first+2));
  double rsideErr  = (fit->GetParError(first+2))/(2*sqrt(fit->GetParameter(first+2)));
  double rlong     = sqrt(fit->GetParameter(first+3));
  double rlongErr  = (fit->GetParError(first+3))/(2*sqrt(fit->GetParameter(first+3)));

  printf(" standard:  Lambda   =  %5.5f +/- %4.5f  \n",lambda,lambdaErr);
  printf(" standard:    Rout   =  %6.5f +/- %4.5f  \n",rout,routErr);
  printf(" standard:   Rside   =  %6.5f +/- %4.5f  \n",rside,rsideErr);
  printf(" standard:   Rlong   =  %6.5f +/- %4.5f  \n",rlong,rlongErr);

  ofstream txt_file;
  char Buff1[100];
  sprintf(Buff1, "/Users/gabriela/Documents/magister/wyniki/3d_e%00i_kt_%00i.txt", energy, kt);
  txt_file.open(Buff1, ios::app);
  if(kt == 1){
    txt_file << "kt = 0.2 - 0.3" << endl;
  } else if(kt == 2){
    txt_file << "kt = 0.3 - 0.36" << endl;
  } else if(kt == 3){
    txt_file << "kt = 0.36 - 0.46" << endl;
  }
  else if(kt == 4){
    txt_file << "kt = 0.48 - 0.54" << endl;
  }
  txt_file << "Lambda " << lambda << " +/- " << lambdaErr << endl;
  txt_file << "Rout " << rout << " +/- " << routErr << endl;
  txt_file << "Rside " << rside << " +/- " << rsideErr << endl;
  txt_file << "Rlong " << rlong << " +/- " << rlongErr << endl;
  txt_file << " " << endl;
  txt_file.close();

  TH1D *h_lambda = new TH1D("lambda", "", 9, mt);
  h_lambda->SetStats(0);
  h_lambda->SetMarkerStyle(20);
  h_lambda->SetMarkerSize(2);
  h_lambda->SetMarkerColor(kMagenta-2);

  TH1D *h_rout = new TH1D("out", "", 9, mt);
  h_rout->SetStats(0);
  h_rout->SetMarkerStyle(20);
  h_rout->SetMarkerSize(2);
  h_rout->SetMarkerColor(kMagenta-2);

  TH1D *h_rside = new TH1D("side", "", 9, mt);
  h_rside->SetStats(0);
  h_rside->SetMarkerStyle(20);
  h_rside->SetMarkerSize(2);
  h_rside->SetMarkerColor(kMagenta-2);

  TH1D *h_rlong = new TH1D("long", "", 9, mt);
  h_rlong->SetStats(0);
  h_rlong->SetMarkerStyle(20);
  h_rlong->SetMarkerSize(2);
  h_rlong->SetMarkerColor(kMagenta-2);

  if(kt == 1){
    h_lambda->SetBinContent(2, lambda);
    h_lambda->SetBinError(2, lambdaErr);
    h_rout->SetBinContent(2, rout);
    h_rout->SetBinError(2, routErr);
    h_rside->SetBinContent(2, rside);
    h_rside->SetBinError(2, rsideErr);
    h_rlong->SetBinContent(2, rlong);
    h_rlong->SetBinError(2, rlongErr);
  }
  else if(kt == 2){
    h_lambda->SetBinContent(4, lambda);
    h_lambda->SetBinError(4, lambdaErr);
    h_rout->SetBinContent(4, rout);
    h_rout->SetBinError(4, routErr);
    h_rside->SetBinContent(4, rside);
    h_rside->SetBinError(4, rsideErr);
    h_rlong->SetBinContent(4, rlong);
    h_rlong->SetBinError(4, rlongErr);
  }
  else if(kt == 3){
    h_lambda->SetBinContent(6, lambda);
    h_lambda->SetBinError(6, lambdaErr);
    h_rout->SetBinContent(6, rout);
    h_rout->SetBinError(6, routErr);
    h_rside->SetBinContent(6, rside);
    h_rside->SetBinError(6, rsideErr);
    h_rlong->SetBinContent(6, rlong);
    h_rlong->SetBinError(6, rlongErr);
  }
  else if(kt == 4){
    h_lambda->SetBinContent(8, lambda);
    h_lambda->SetBinError(8, lambdaErr);
    h_rout->SetBinContent(8, rout);
    h_rout->SetBinError(8, routErr);
    h_rside->SetBinContent(8, rside);
    h_rside->SetBinError(8, rsideErr);
    h_rlong->SetBinContent(8, rlong);
    h_rlong->SetBinError(8, rlongErr);
  }

  char Buff3[100];
  sprintf(Buff3, "/Users/gabriela/Documents/magister/wyniki/3D_e%00i_kt_%00i.root", energy, kt);
  TFile *t_3D = new TFile(Buff3, "RECREATE");
  h_lambda->Write();
  h_rout->Write();
  h_rside->Write();
  h_rlong->Write();
  t_3D->Close();

  TH3D *fit_histo = new TH3D ("his", "his", ratio->GetNbinsX(), -0.8, 0.8, ratio->GetNbinsY(), -0.8, 0.8, ratio->GetNbinsZ(), -0.8, 0.8);
  getfitprojc(ratio,fit_histo,fit);

  TH1D *fit_out = (TH1D*)(fit_histo->ProjectionX("fit_outx", min, max, min, max, "e"));
  fit_out->SetLineColor(kBlack);
  fit_out->SetLineWidth(2.);
  fit_out->Scale(0.25);
  TH1D *fit_side = (TH1D*)(fit_histo->ProjectionY("fit_sidex", min, max, min, max, "e"));
  fit_side->Scale(0.25);
  fit_side->SetLineColor(kBlack);
  fit_side->SetLineWidth(2.);
  TH1D *fit_long = (TH1D*)(fit_histo->ProjectionZ("fit_longx", min, max, min, max, "e"));
  fit_long->Scale(0.25);
  fit_long->SetLineColor(kBlack);
  fit_long->SetLineWidth(2.);

  for(Int_t i = 0; i < fit_out->GetNbinsX(); i++){
    fit_out->SetBinError(i,0);
  }
  for(Int_t i = 0; i < fit_side->GetNbinsX(); i++){
    fit_side->SetBinError(i,0);
  }
  for(Int_t i = 0; i < fit_long->GetNbinsX(); i++){
    fit_long->SetBinError(i,0);
  }

  TLegend *leg1 = new TLegend(0.32,0.72,0.65,0.85);
  leg1->SetBorderSize(0);
  leg1->AddEntry(n_out, "Correlation function", "p");
  leg1->AddEntry(fit_out, "Fit of correlation function", "l");

  TLatex *out = new TLatex(); out->SetTextFont(42); out->SetTextSize(60);

  TCanvas *c1 = new TCanvas("c1", "c1", 1200, 400);

  TPad *column00 = new TPad("column00", "", 0,0,0.33,1);
  column00->Draw();
  column00->cd();
  //column00->Range(0,0,1,1);
  column00->SetFillColor(0);
  column00->SetBorderMode(0);
  column00->SetBorderSize(2);
  column00->SetFrameBorderMode(0);
  column00->SetRightMargin(0);
	//śc1->Divide(3,1);

  //out->DrawLatex(0.1, 1.1, "Out direction");
  n_out->Divide(d_out);
	n_out->Draw("p");
  fit_out->Draw("CHIST SAME");
  column00->cd();
  c1->cd();

  TPad *column10 = new TPad("column10", "",0.33,0,0.66,1);
  column10->Draw();
  column10->cd();
  //column10->Range(0,0,1,1);
  column10->SetFillColor(0);
  column10->SetBorderMode(0);
  column10->SetBorderSize(2);
  column10->SetFrameBorderMode(0);
  column10->SetRightMargin(0);
  column10->SetLeftMargin(0);

  n_side->Divide(d_side);
	n_side->Draw();
  fit_out->Draw("CHIST SAME");

  column10->cd();
  c1->cd();

  TPad *column20 = new TPad("column20", "",0.66,0,0.99,1);
  column20->Draw();
  column20->cd();
  //column20->Range(0,0,1,1);
  column20->SetFillColor(0);
  column20->SetBorderMode(0);
  column20->SetBorderSize(2);
  column20->SetFrameBorderMode(0);
  column20->SetLeftMargin(0);

  n_long->Divide(d_long);
	n_long->Draw();
  fit_long->Draw("CHIST SAME");
  leg1->Draw();

  column20->cd();
  c1->cd();

  char Buff2[100];
  sprintf(Buff2, "/Users/gabriela/Documents/magister/wyniki/fit_3D/fit_%00i_kt_%00i.pdf", energy, kt);
  c1->Print(Buff2);
  c1->Close();

}
