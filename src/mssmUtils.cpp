
#include "mssmUtils.h"
#include <iostream>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

namespace softsusy {
  
  void generalBcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    MssmSusy s; MssmSoftPars r;
    double m3sq = m.displayM3Squared();
    s = m.displayMssmSusy();
    r.set(inputParameters);
    r.setM3Squared(m3sq);
    m.setSoftPars(r);
    m.setMssmSusy(s);
    
    return;
  }
  
  /// This one doesn't overwrite mh1sq or mh2sq at the high scale
  void generalBcs2(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    MssmSusy s; MssmSoftPars r;
    double mh1sq = m.displayMh1Squared();
    double mh2sq = m.displayMh2Squared();
    double m3sq = m.displayM3Squared();
    s = m.displayMssmSusy();
    r.set(inputParameters);
    r.setMh1Squared(mh1sq);
    r.setMh2Squared(mh2sq);
    r.setM3Squared(m3sq);
    m.setSoftPars(r);
    m.setMssmSusy(s);
    
    return;
  }
  
  void extendedSugraBcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    int i;
    for (i=1; i<=3; i++) m.setGauginoMass(i, inputParameters.display(i));
    if (inputParameters.display(25) > 1. && m.displaySetTbAtMX())
      m.setTanb(inputParameters.display(25));
    m.setTrilinearElement(UA, 3, 3, m.displayYukawaElement(YU, 3, 3) *
			  inputParameters.display(11));
    m.setTrilinearElement(DA, 3, 3, m.displayYukawaElement(YD, 3, 3) *
			  inputParameters.display(12));
    m.setTrilinearElement(EA, 3, 3, m.displayYukawaElement(YE, 3, 3) *
			  inputParameters.display(13));
    m.setTrilinearElement(UA, 1, 1, 0.);
    m.setTrilinearElement(DA, 1, 1, 0.);
    m.setTrilinearElement(EA, 1, 1, 0.);
    m.setTrilinearElement(UA, 2, 2, 0.);
    m.setTrilinearElement(DA, 2, 2, 0.);
    m.setTrilinearElement(EA, 2, 2, 0.);
    m.setSoftMassElement(mLl, 1, 1, signedSqr(inputParameters.display(31)));
    m.setSoftMassElement(mLl, 2, 2, signedSqr(inputParameters.display(32)));
    m.setSoftMassElement(mLl, 3, 3, signedSqr(inputParameters.display(33)));
    m.setSoftMassElement(mEr, 1, 1, signedSqr(inputParameters.display(34)));
    m.setSoftMassElement(mEr, 2, 2, signedSqr(inputParameters.display(35)));
    m.setSoftMassElement(mEr, 3, 3, signedSqr(inputParameters.display(36)));
    m.setSoftMassElement(mQl, 1, 1, signedSqr(inputParameters.display(41)));
    m.setSoftMassElement(mQl, 2, 2, signedSqr(inputParameters.display(42)));
    m.setSoftMassElement(mQl, 3, 3, signedSqr(inputParameters.display(43)));
    m.setSoftMassElement(mUr, 1, 1, signedSqr(inputParameters.display(44)));
    m.setSoftMassElement(mUr, 2, 2, signedSqr(inputParameters.display(45)));
    m.setSoftMassElement(mUr, 3, 3, signedSqr(inputParameters.display(46)));
    m.setSoftMassElement(mDr, 1, 1, signedSqr(inputParameters.display(47)));
    m.setSoftMassElement(mDr, 2, 2, signedSqr(inputParameters.display(48)));
    m.setSoftMassElement(mDr, 3, 3, signedSqr(inputParameters.display(49)));
    
    if (!m.displayAltEwsb()) {
      m.setMh1Squared(inputParameters.display(21));
      m.setMh2Squared(inputParameters.display(22));
    }
  }
  
  /// universal mSUGRA boundary conditions
  void sugraBcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double m0 = inputParameters.display(1);
    double m12 = inputParameters.display(2);
    double a0 = inputParameters.display(3);
    
    /// Sets scalar soft masses equal to m0, fermion ones to m12 and sets the
    /// trilinear scalar coupling to be a0
    ///  if (m0 < 0.0) m.flagTachyon(true); Deleted on request from A Pukhov
    m.standardSugra(m.displayMssmSusy(), m0, m12, a0);
    
    return;
  }
  
  void nuhmI(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double m0 = inputParameters.display(1);
    double m12 = inputParameters.display(2);
    double mH  = inputParameters.display(3);
    double a0 = inputParameters.display(4);
    
    /// Sets scalar soft masses equal to m0, fermion ones to m12 and sets the
    /// trilinear scalar coupling to be a0
    ///  if (m0 < 0.0) m.flagTachyon(true); Deleted on request from A Pukhov
    m.standardSugra(m.displayMssmSusy(), m0, m12, a0);
    m.setMh1Squared(mH * mH); m.setMh2Squared(mH * mH);
    
    return;
  }
  
  void nuhmII(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double m0 = inputParameters.display(1);
    double m12 = inputParameters.display(2);
    double mH1  = inputParameters.display(3);
    double mH2  = inputParameters.display(4);
    double a0 = inputParameters.display(5);
    
    /// Sets scalar soft masses equal to m0, fermion ones to m12 and sets the
    /// trilinear scalar coupling to be a0
    ///  if (m0 < 0.0) m.flagTachyon(true); Deleted on request from A Pukhov
    m.standardSugra(m.displayMssmSusy(), m0, m12, a0);
    m.setMh1Squared(mH1 * mH1); m.setMh2Squared(mH2 * mH2);
    
    return;
  }
  
  /// Other types of boundary condition
  void amsbBcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double m32 = inputParameters.display(1);
    double m0 = inputParameters.display(2);
    
    m.standardSugra(m.displayMssmSusy(), m0, 0., 0.);
    m.addAmsb(m.displayMssmSusy(), m32);
    return;
  }
  
  void lvsBcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double m0  = inputParameters.display(1);
    double m12 = inputParameters.display(1) * sqrt(3.);
    double a0  = -inputParameters.display(1) * sqrt(3.);
    
    m.standardSugra(m.displayMssmSusy(), m0, m12, a0);
    
    return;
  }
  
  void gmsbBcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    int n5     = int(inputParameters.display(1));
    double mMess  = inputParameters.display(2);
    double LAMBDA = inputParameters.display(3);
    double cgrav = inputParameters.display(4);
    
    m.minimalGmsb(m.displayMssmSusy(), n5, LAMBDA, mMess, cgrav);
    
    return;
  }
  
     //new code

  void FGMCaseB2bcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double alpha  = inputParameters.display(1);
    double M0  = inputParameters.display(2);
    double nM = inputParameters.display(3);
    double nHd = inputParameters.display(4);
    double nHu = inputParameters.display(5);
    m.FGMCaseB2(m.displayMssmSusy(), alpha, M0, nM, nHd, nHu);

    return;
  }
  
    void FGMCaseB1bcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double alpha  = inputParameters.display(1);
    double M0  = inputParameters.display(2);
    double nM = inputParameters.display(3);
    double nHd = inputParameters.display(4);
    double nHu = inputParameters.display(5);
    m.FGMCaseB1(m.displayMssmSusy(), alpha, M0, nM, nHd, nHu);

    return;
  }
  
      void FGMCaseB1Altbcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double alpha  = inputParameters.display(1);
    double M0  = inputParameters.display(2);
    double nM = inputParameters.display(3);
    double nHd = inputParameters.display(4);
    double nHu = inputParameters.display(5);
    m.FGMCaseB1Alt(m.displayMssmSusy(), alpha, M0, nM, nHd, nHu);

    return;
  }
  
    void FGMCaseB1Largebcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double alpha  = inputParameters.display(1);
    double M0  = inputParameters.display(2);
    double nM = inputParameters.display(3);
    m.FGMCaseB1Large(m.displayMssmSusy(), alpha, M0, nM);

    return;
  }
    void FGMCaseBNonRNbcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    m.FGMCaseBNonRN(m.displayMssmSusy(), inputParameters(1), inputParameters(2), inputParameters(3), inputParameters(4));

    return;
  }
    void FGMCaseBNonRN1bcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    m.FGMCaseBNonRN1(m.displayMssmSusy(), inputParameters(1), inputParameters(2), inputParameters(3), inputParameters(4), inputParameters(5), inputParameters(6));

    return;
  }
    void FGMCaseBNonRN2bcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    m.FGMCaseBNonRN2(m.displayMssmSusy(), inputParameters(1), inputParameters(2), inputParameters(3), inputParameters(4), inputParameters(5), inputParameters(6));

    return;
  }
  void FGMCaseBNonRN3bcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    m.FGMCaseBNonRN3(m.displayMssmSusy(), inputParameters(1), inputParameters(2), inputParameters(3), inputParameters(4), inputParameters(5), inputParameters(6), inputParameters(7));

    return;
  }
  void FGMCaseB0bcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double alpha  = inputParameters.display(1);
    double M0  = inputParameters.display(2);
    double nM = inputParameters.display(3);
    m.FGMCaseB0(m.displayMssmSusy(), alpha, M0, nM);

    return;
  }
  
  void userDefinedBcs(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    m.methodBoundaryCondition(inputParameters);
    sugraBcs(m, inputParameters);
  }
  
  void nonUniGauginos(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    double m0 = inputParameters.display(1);
    double m12 = inputParameters.display(2);
    double a0 = inputParameters.display(3);
    
    /// Sets scalar soft masses equal to m0, fermion ones to m12 and sets the
    /// trilinear scalar coupling to be a0
    ///  if (m0 < 0.0) m.flagTachyon(true); Deleted on request from A Pukhov
    m.standardSugra(m.displayMssmSusy(), m0, m12, a0);
    
    m.setGauginoMass(2, inputParameters.display(4));
    m.setGauginoMass(3, inputParameters.display(5));
    
    return;
  }
  
  // Boundary conditions of split gauge mediated SUSY breaking (see
  // http://www.physics.rutgers.edu/~somalwar/conlsp/slepton-coNLSP.pdf
  // for example). Note that here, mu is set at mMess instead of at the
  // electroweak scale.
  void splitGmsb(MssmSoftsusy & m, const DoubleVector & inputParameters) {
    
    double n5 = inputParameters(1);
    double lambdaL = inputParameters(2);
    double lambdaD = inputParameters(3);
    double mMess = inputParameters(4);
    double muOm2 = inputParameters(5);
    double mAOm2 = inputParameters(6);
    double cgrav = inputParameters(7);
    
    double lambda1 = n5 * (0.6 * lambdaL + 0.4 * lambdaD);
    double lambda2 = n5 * lambdaL;
    double lambda3 = n5 * lambdaD;
    
    double m1, m2, m3;
    m1 = sqr(m.displayGaugeCoupling(1)) / (16.0 * sqr(PI)) * lambda1;
    m2 = sqr(m.displayGaugeCoupling(2)) / (16.0 * sqr(PI)) * lambda2;
    m3 = sqr(m.displayGaugeCoupling(3)) / (16.0 * sqr(PI)) * lambda3;
    m.setGauginoMass(1, m1);
    m.setGauginoMass(2, m2);
    m.setGauginoMass(3, m3);
    
    m.setM32(2.37e-19 * sqrt((sqr(lambdaL) + sqr(lambdaD)) * 0.5) *
	     mMess * cgrav);
    
    m.setM32(2.37e-19 * sqrt((sqr(lambdaL) + sqr(lambdaD)) * 0.5) *
	     mMess * cgrav);
    
    double g1f = sqr(sqr(m.displayGaugeCoupling(1)));
    double g2f = sqr(sqr(m.displayGaugeCoupling(2)));
    double g3f = sqr(sqr(m.displayGaugeCoupling(3)));
    
    double lambdaP1sq = n5 * (0.6 * sqr(lambdaL) + 0.4 * sqr(lambdaD));
    double lambdaP2sq = n5 * sqr(lambdaL);
    double lambdaP3sq = n5 * sqr(lambdaD);
    
    double mursq, mdrsq, mersq, mqlsq, mllsq;
    mursq = 2.0 *
      (4.0 / 3.0 * g3f * lambdaP3sq + 0.6 * 4.0 / 9.0 * g1f * lambdaP1sq)
      / sqr(16.0 * sqr(PI));
    mdrsq = 2.0 *
      (4.0 / 3.0 * g3f * lambdaP3sq + 0.6 * 1.0 / 9.0 * g1f * lambdaP1sq)
      / sqr(16.0 * sqr(PI));
    mersq = 2.0 *
      (0.6 * g1f * lambdaP1sq)
      / sqr(16.0 * sqr(PI));
    mqlsq = 2.0 *
      (4.0 / 3.0 * g3f * lambdaP3sq + 0.75 * g2f * lambdaP2sq +
       0.6 * g1f / 36.0 * lambdaP1sq)
      / sqr(16.0 * sqr(PI));
    mllsq = 2.0 *
      (0.75 * g2f * lambdaP2sq + 0.6 * 0.25 * g1f * lambdaP1sq)
      / sqr(16.0 * sqr(PI));
    
    // You need Higgs masses too!
    
    DoubleMatrix id(3, 3);
    id(1, 1) = 1.0; id(2, 2) = 1.0; id(3, 3) = 1.0;
    
    m.setSoftMassMatrix(mQl, mqlsq * id);
    m.setSoftMassMatrix(mUr, mursq * id);
    m.setSoftMassMatrix(mDr, mdrsq * id);
    m.setSoftMassMatrix(mLl, mllsq * id);
    m.setSoftMassMatrix(mEr, mersq * id);
    
    m.universalTrilinears(m.displayMssmSusy(), 0.0);
    DoubleVector pars(2); ///< encodes EWSB BC
    pars(1) = muOm2 * m2;
    pars(2) = mAOm2 * m2;
    
    /// Save the two parameters
    m.setEwsbConditions(pars);
  }
  
  /// Returns true if a point passes the Higgs constraint from LEP2, false
  /// otherwise.  Error is the amount of uncertainty on SOFTSUSY's mh prediction
  bool testLEPHiggs(const MssmSoftsusy & r, double error) {
    double Mh = r.displayPhys().mh0(1);
    Mh = Mh + error;
    double sinba2 = sqr(sin(atan(r.displayTanb()) - r.displayPhys().thetaH));
    
    ///  cout << "sinba2=" << sinba2 << endl;
    
    if (Mh < 90.0) return false;
    else if (90.0 <= Mh &&  Mh < 99.0) {
      if (sinba2 < -6.1979 + 0.12313 * Mh - 0.00058411 * sqr(Mh)) return true;
      else return false;
    }
    else if (99.0 <= Mh &&  Mh < 104.0) {
      if (sinba2 < 35.73 - 0.69747 * Mh + 0.0034266 * sqr(Mh)) return true;
      else return false;
    }
    else if (104.0 <= Mh &&  Mh < 109.5) {
      if (sinba2 < 21.379 - 0.403 * Mh + 0.0019211 * sqr(Mh)) return true;
      else return false;
    }
    else if (109.5 <= Mh &&  Mh < 114.4) {
      if (sinba2 <  1/(60.081 - 0.51624 * Mh)) return true;
      else return false;
    }
    return true;
  }
  
  /// from hep-ph/9507294 -- debugged 19/11/04
  double ufb3fn(double mu, double htau, double h2, int family, const MssmSoftsusy
		& temp) { 
    double vufb3 = 0.0;
    /// potential value for these VEVs
    if (fabs(h2) > 
	sqrt(sqr(mu) / (4.0 * sqr(htau)) + 
	     4.0 * temp.displaySoftMassSquared(mLl, family, family) /  
	     (0.6 * sqr(temp.displayGaugeCoupling(1)) +
	      sqr(temp.displayGaugeCoupling(2)))) - fabs(mu) / 
	temp.displayYukawaElement(YE, 3, 3) * 0.5)
      vufb3 = 
	sqr(h2) * (temp.displayMh2Squared() +
		   temp.displaySoftMassSquared(mLl, family, family)) + 
	fabs(mu * h2) / htau * 
	(temp.displaySoftMassSquared(mLl, 3, 3) +
	 temp.displaySoftMassSquared(mEr, 3, 3) 
	 + temp.displaySoftMassSquared(mLl, family, family)) -
	2.0 * sqr(temp.displaySoftMassSquared(mLl, family, family)) / 
	(0.6 * sqr(temp.displayGaugeCoupling(1)) +
	 sqr(temp.displayGaugeCoupling(2)));
    else
      vufb3 = 
	sqr(h2) * temp.displayMh2Squared() + 
	fabs(mu * h2) / htau * 
	(temp.displaySoftMassSquared(mLl, 3, 3) +
	 temp.displaySoftMassSquared(mEr, 3, 3)) +  
	1.0 / 8.0 * (0.6 * sqr(temp.displayGaugeCoupling(1)) +
		     sqr(temp.displayGaugeCoupling(2))) * 
	sqr(sqr(h2) + fabs(mu * h2) / htau);
    
    if (PRINTOUT > 1) cout << vufb3 << endl;
    return vufb3;
  }
  
  /// For ufb3direction, returns scale at which one-loop corrections are smallest
  double getQhat(double inminTol,double eR, double h2, double Lisq, double mx,
		 MssmSoftsusy & temp) {
    double oldQhat = -1.0e16;
    int maxNum = 40;
    
    int d; for (d = 1; d <= maxNum; d++)     {
      double qhat = 
	maximum(maximum(maximum(temp.displayGaugeCoupling(2) * eR, 
				temp.displayGaugeCoupling(2) * fabs(h2)), 
			temp.displayGaugeCoupling(2) * sqrt(fabs(Lisq))),
		temp.displayYukawaElement(YU, 3, 3) * fabs(h2));
      /// Run all paramaters to that scale
      if (qhat < mx) temp.runto(qhat);
      else temp.runto(mx); 
      if (PRINTOUT > 1) cout << qhat << " ";
      
      if (fabs((qhat - oldQhat) / qhat) < inminTol) return qhat;
      oldQhat = qhat;
    }
    /// Return NOB if no convergence on qhat
    return -numberOfTheBeast;
  }
  
  /// Difference between two SOFTSUSY objects in and out: EWSB terms only
  double sumTol(const MssmSoftsusy & in, const MssmSoftsusy & out, int numTries) {
    
    DoubleVector sT(34);
    sumTol(in.displayDrBarPars(), out.displayDrBarPars(), sT);
    /// The predicted value of MZ^2 is an absolute measure of how close to a
    /// true solution we are:
    // double tbPred = 0.;
    /// We allow an extra factor of 10 for the precision in the predicted value
    /// of MZ compared to TOLERANCE if the program is struggling and gone beyond
    /// 10 tries - an extra 2 comes from MZ v MZ^2
    /* int k = sT.size() - 2;
    if (!in.displayProblem().testSeriousProblem()) {
      sT(k) = 0.5 * sTfn(predictedMzSq, sqr(MZ));
      if (numTries > 10) sT(k) *= 0.1;
      } */
    
    return sT.max();
  }
  
  /// Prints out what the lsp is
  string recogLsp(int temp, int posj) {
    string out;
    switch(temp) {
    case -1: out = "gravitino"; break;
    case 0: out = "neutralino"; break;
    case 1:
      switch(posj) {
      case 3: out = "stop"; break;
      case 2: out = "scharm"; break;
      case 1: out = "sup"; break;
      } break;
    case 2:
      switch(posj) {
      case 3: out = "sbottom"; break;
      case 2: out = "sstange"; break;
      case 1: out = "sdown"; break;
      } break;
    case 3:
      switch(posj) {
      case 3: out = "stau"; break;
      case 2: out = "smu"; break;
      case 1: out = "selectron"; break;
      } break;
    case 4: out = "chargino"; break;
    case 5: out = "sneutrino"; break;
    case 6: out = "gluino"; break;
    default:
      ostringstream ii;
      ii << "Wrong input to lsp printing routine\n";
      throw ii.str(); break;
    }
    return out;
  }
  
  ostream & operator <<(ostream &left, const MssmSoftsusy &s) {
    left << HR << endl;
#ifdef COMPILE_TWO_LOOP_GAUGE_YUKAWA
    left << "Included higher-order thresholds=" << s.included_thresholds << endl;
#endif ///< COMPILE_TWO_LOOP_GAUGE_YUKAWA
    left << "Gravitino mass M3/2: " << s.displayGravitino() << endl;
    left << "Msusy: " << s.displayMsusy() << " MW: " << s.displayMw()
	 << " Predicted MZ: " << sqrt(s.displayPredMzSq()) << endl;
    left << "Data set:\n" << s.displayDataSet();
    left << HR << endl;
    left << "RPC MSSM parameters at Q: " << s.displayMu() << endl;
    left << s.displayMssmSoftPars() << s.displayMssmSusy();
    left << "thresholds: " << s.displayMssmApprox().displayThresholds();
    left << " #loops: " << s.displayMssmApprox().displayLoops() << endl;
    left << "t1/v1(MS)=" << s.displayTadpole1Ms()
	 << " t2/v2(MS)=" << s.displayTadpole2Ms() << endl;
    left << HR << "\nPhysical MSSM parameters:\n";
    left << s.displayPhys() << endl;
    double mass; int posi, posj, id;
    id = s.lsp(mass, posi, posj);
    
    /// If the gravitino mass is non-zero, and if it is smaller than the visible
    /// sector LSP mass, make it clear that the particle is the NLSP
    left << "lsp is " << recogLsp(id, posj);
    left << " of mass " << mass << " GeV\n";
    if (s.displayProblem().test()) left << "***** PROBLEM *****" <<
				     s.displayProblem() << " *****" << endl;
    left << HR << endl;
    
    if (s.displaySetTbAtMX()) left << "Tan beta is set at user defined scale\n";
    if (s.displayAltEwsb()) left << "Alternative EWSB conditions: mu="
				 << s.displayMuCond()
				 << " mA=" << s.displayMaCond() << endl;
    
    return left;
  }

  DoubleVector calcMh1SqSugraCoeffs(const MssmSoftsusy & m, double scale) {
    MssmSoftsusy model(m);
    const double mx = model.displayMxBC();
    model.runto(mx);

    const DoubleVector savedPars(model.display());

    DoubleVector coeffs(4);

    // coefficient of M_0^2, M_{1/2}^2 and A_0^2
    for (int i = 1; i <= 3; ++i) {
      DoubleVector inputs(3);
      inputs(i) = 1.0;

      sugraBcs(model, inputs);

      model.runto(scale);

      coeffs(i) = model.displayMh1Squared();

      model.set(savedPars);
      model.setMu(mx);
    }

    // coefficient of M_{1/2} A_0
    DoubleVector crossTermInputs(3);
    crossTermInputs(1) = 0.0;
    crossTermInputs(2) = 1.0;
    crossTermInputs(3) = 1.0;

    sugraBcs(model, crossTermInputs);

    model.runto(scale);

    coeffs(4) = model.displayMh1Squared() - coeffs(2) - coeffs(3);

    return coeffs;
  }

  DoubleVector calcMh2SqSugraCoeffs(const MssmSoftsusy & m, double scale) {
    MssmSoftsusy model(m);
    const double mx = model.displayMxBC();
    model.runto(mx);

    const DoubleVector savedPars(model.display());

    DoubleVector coeffs(4);

    // coefficient of M_0^2, M_{1/2}^2 and A_0^2
    for (int i = 1; i <= 3; ++i) {
      DoubleVector inputs(3);
      inputs(i) = 1.0;

      sugraBcs(model, inputs);

      model.runto(scale);

      coeffs(i) = model.displayMh2Squared();

      model.set(savedPars);
      model.setMu(mx);
    }

    // coefficient of M_{1/2} A_0
    DoubleVector crossTermInputs(3);
    crossTermInputs(1) = 0.0;
    crossTermInputs(2) = 1.0;
    crossTermInputs(3) = 1.0;

    sugraBcs(model, crossTermInputs);

    model.runto(scale);

    coeffs(4) = model.displayMh2Squared() - coeffs(2) - coeffs(3);

    return coeffs;
  }

} ///< namespace softsusy
