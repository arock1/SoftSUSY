/* Two loop self energy function for suL */

#include "supermodel.h"
#include "self_scalar.h"

/* Facts about QCD: */
#define CG 3.L
#define Cq (4.L/3.L)
#define Iq 0.5L

/* Defined in se_squark.c */
TSIL_COMPLEX pi1_suL (int, int, TSIL_REAL);
TSIL_COMPLEX Pi1_suL (int, int, TSIL_REAL);

/* Used in multiple routines below */
TSIL_COMPLEX PsuL[2][2], NsuL[2][2];
int arePandNsuLSet = NO;

/* For u,d,c,s, uncomment these lines: */
TSIL_COMPLEX LsuL[2], LsuLc[2], RsuL[2], RsuLc[2];

/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */
/* hep-ph/0502168 eqs. (4.5) and (4.6). */

void SetPandNsuL ()
{
  int i,j;

  LsuL[0] = LsuLc[0] = 0.0L;
  LsuL[1] = LsuLc[1] = -1.0L;
  RsuL[0] = RsuLc[0] = 1.0L;
  RsuL[1] = RsuLc[1] = 0.0L;

  for (i=0; i<2; i++)
    for (j=0; j<2; j++) {
      PsuL[i][j] = LsuL[i]*LsuLc[j] - RsuL[i]*RsuLc[j];
      NsuL[i][j] = LsuL[i]*RsuLc[j] + RsuL[i]*LsuLc[j];
    }

  arePandNsuLSet = YES;
}

/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */
/* 0502168 eq. (4.8) */

TSIL_COMPLEX pi20_suL (int i, int j, TSIL_REAL s) 
{
  int k,m,n,r,t;
  TSIL_COMPLEX result = 0.0L;
  TSIL_COMPLEX term = 0.0L;
  TSIL_DATA bar;
  TSIL_RESULT gaak,gaak2;
  TSIL_COMPLEX vFFFFS, vFffFS, vfFfFS, vfFFfS, vFFffS, vffffS;
  TSIL_COMPLEX mFFFFS, mFFffS, mFfFfS, mFffFS, mffffS;
  TSIL_COMPLEX sSSS;

  if (arePandNsuLSet == NO) SetPandNsuL ();

  /* 0502168 eq. (4.8), term by term: */
  for (k=0; k<2; k++)
    for (m=0; m<2; m++)
      for (n=0; n<2; n++)
	term += PsuL[i][k] * PsuL[k][m] * PsuL[m][n] * PsuL[n][j] *
	  X_SSS (m2_suL[k],m2_suL[n],m2_suL[m],Q2);

  result += 0.25L*term;

  term = 0.0L;
  for (k=0; k<2; k++)
    term += PsuL[i][k] * PsuL[k][j] *
      W_SSFF (m2_suL[k],m2_suL[k],0.0L,m2_gluino,Q2);

  /* NOTE m_up = 0 for up != top */

  /* for (k=0; k<2; k++) */
  /*   for (m=0; m<2; m++) { */
  /*     term += -PsuL[i][k] * NsuL[k][m] * PsuL[m][j] * 0.0L * m_gluino * */
  /* 	W_SSff (m2_suL[k],m2_suL[m],0.0L,m2_gluino,Q2); */
  /*   } */
  result += 0.5*term;

  /* Now term will be the second part, multiplied by (4Cq^2 - 2CG Cq): */
  term = 0.0L;

  for (k=0; k<2; k++) {
    TSIL_SetParameters (&bar,m2_gluino,0.0L,0.0L,m2_gluino,m2_suL[k],Q2);
    TSIL_Evaluate (&bar, s);
    TSIL_CopyResult (&bar, &gaak); 
    V_FFFFS (&gaak, &gaak, 
	     &vFFFFS, &vFffFS, &vfFfFS, &vfFFfS, &vFFffS, &vffffS);

    result += (LsuL[i] * LsuLc[j] * LsuL[k] * LsuLc[k] + 
	       RsuL[i] * RsuLc[j] * RsuL[k] * RsuLc[k]) * vFFFFS
      + (LsuL[i] * RsuLc[j] * RsuL[k] * LsuLc[k] + 
	 RsuL[i] * LsuLc[j] * LsuL[k] * RsuLc[k]) * m2_gluino * vfFFfS
      /* + (LsuL[i] * LsuLc[j] * RsuL[k] * RsuLc[k] +  */
      /* 	 RsuL[i] * RsuLc[j] * LsuL[k] * LsuLc[k]) * 0.0L * vFffFS */
      /* - NsuL[i][j] * 0.0L * m_gluino * vfFfFS */
      /* + (LsuL[i] * RsuLc[j] * LsuL[k] * RsuLc[k] +  */
      /* 	 RsuL[i] * LsuLc[j] * RsuL[k] * LsuLc[k]) * 0.0L * m2_gluino * vffffS */
      ;

    /* if (i==j) */
    /*   result += -NsuL[k][k] * 0.0L * m_gluino * vFFffS; */

    TSIL_PermuteResult (&gaak, XYandZU, &gaak2);
    M_FFFFS (&gaak2, &mFFFFS, &mFFffS, &mFfFfS, &mFffFS, &mffffS);

    term += (LsuL[i] * RsuLc[j] * RsuL[k] * LsuLc[k] + 
	     RsuL[i] * LsuLc[j] * LsuL[k] * RsuLc[k]) * mFFFFS
      /* - NsuL[i][j] * 0.0L * m_gluino * mFFffS */
      + (LsuL[i] * LsuLc[j] * LsuL[k] * LsuLc[k]
      + RsuL[i] * RsuLc[j] * RsuL[k] * RsuLc[k]) * m2_gluino * mFffFS
      /* + (LsuL[i] * RsuLc[j] * LsuL[k] * RsuLc[k] +  */
      /* 	 RsuL[i] * LsuLc[j] * RsuL[k] * LsuLc[k]) * 0.0L * m2_gluino * mffffS */
      ;

    /* if (i==j) */
    /*   term += -NsuL[k][k] * 0.0L * m_gluino * mFfFfS; */

    /* M_FFFFS (&gaak, &mFFFFS, &mFFffS, &mFfFfS, &mFffFS, &mffffS); */
    /* term += (LsuL[i] * LsuLc[j] * RsuL[k] * RsuLc[k] +  */
    /* 	     RsuL[i] * RsuLc[j] * LsuL[k] * LsuLc[k]) * 0.0L * mFffFS; */

    for (m=0; m<2; m++)
      for (n=0; n<2; n++) {
	TSIL_SetParametersST (&bar,m2_suL[k],m2_suL[m],m2_suL[n],Q2);
	TSIL_Evaluate (&bar, s);
	/* For clarity (we just need this one function): */
	sSSS = -bar.S[uxv].value;
	term += 0.25L * PsuL[i][k] * PsuL[k][m] * PsuL[m][n] * PsuL[n][j] * sSSS;
      }
  }
  result *= 4.0L*Cq*Cq;
  result += term*(4.0L*Cq*Cq - 2.0L*CG*Cq);

  /* Next bit is last three lines of eq. (4.8).  These involve summing
     over all 12 quark/squark mass eigenstates. */

  term = 0.0L;

  /* stop */
  for (r=0; r<2; r++) {

    TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_gluino,m2_top,m2_stop[r],Q2);
    TSIL_Evaluate (&bar, s);
    TSIL_CopyResult (&bar, &gaak); 
    V_FFFFS (&gaak, &gaak, &vFFFFS, &vFffFS, &vfFfFS, &vfFFfS, &vFFffS, &vffffS);

    term += -2.0L * NsuL[i][j] * m_top * m_gluino * vfFfFS
      + NsuL[i][j] * NsuL[r][r] * 0.0L * m_top * (vfFFfS + m2_gluino*vffffS);

    if (i == j)
      term += vFFFFS + m2_gluino*vFffFS - 2.0L*NsuL[r][r]*m_top*m_gluino*vFFffS;

    for (k=0; k<2; k++)
      for (t=0; t<2; t++) {
        TSIL_SetParametersST (&bar,m2_suL[k],m2_stop[r],m2_stop[t],Q2);
        TSIL_Evaluate (&bar, s);
        /* For clarity (just need this one function): */
        sSSS = -bar.S[uxv].value;
	term += 0.25L * PsuL[i][k] * PsuL[k][j] * PsuL[r][t] * PsuL[t][r] * sSSS;
      }
  }

  /* sbot */
  for (r=0; r<2; r++) {

    TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_gluino,m2_bot,m2_sbot[r],Q2);
    TSIL_Evaluate (&bar, s);
    TSIL_CopyResult (&bar, &gaak); 
    V_FFFFS (&gaak, &gaak, 
	     &vFFFFS, &vFffFS, &vfFfFS, &vfFFfS, &vFFffS, &vffffS);

    /* Take mbot ~ 0 */
    /* term += -2.0L*NsuL[i][j]*m_bot*m_gluino*vfFfFS */
    /*   + NsuL[i][j]*NsuL[r][r]*0.0L*m_bot*(vfFFfS + m2_gluino*vffffS) */
    ;

    if (i == j)
      term += vFFFFS + m2_gluino*vFffFS 
	/* - 2.0L*NsuL[r][r]*m_bot*m_gluino*vFFffS */
	;

    for (k=0; k<2; k++)
      for (t=0; t<2; t++) {
        TSIL_SetParametersST (&bar,m2_suL[k],m2_sbot[r],m2_sbot[t],Q2);
        TSIL_Evaluate (&bar, s);
        /* For clarity (just need this one function): */
        sSSS = -bar.S[uxv].value;
	term += 0.25L * PsuL[i][k] * PsuL[k][j] * PsuL[r][t] * PsuL[t][r] * sSSS;
      }
  }

  /* suL */
  for (r=0; r<2; r++) {

    TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_gluino,0.0L,m2_suL[r],Q2);
    TSIL_Evaluate (&bar, s);
    TSIL_CopyResult (&bar, &gaak); 
    V_FFFFS (&gaak, &gaak, 
	     &vFFFFS, &vFffFS, &vfFfFS, &vfFFfS, &vFFffS, &vffffS);

    /* Tese terms are all zero since the fermion mass is zero */
    /* term = -2.0L*NsuL[i][j]* 0.0L *m_gluino*vfFfFS */
    /*   + NsuL[i][j]*NsuL[r][r]*0.0L* 0.0L *(vfFFfS + m2_gluino*vffffS); */

    if (i == j)
      term += vFFFFS + m2_gluino*vFffFS 
	/* - 2.0L*NsuL[r][r]* 0.0L *m_gluino*vFFffS */
	;

    for (k=0; k<2; k++)
      for (t=0; t<2; t++) {
        TSIL_SetParametersST (&bar,m2_suL[k],m2_suL[r],m2_suL[t],Q2);
        TSIL_Evaluate (&bar, s);
        /* For clarity (just need this one function): */
        sSSS = -bar.S[uxv].value;
	term += 0.25L * PsuL[i][k] * PsuL[k][j] * PsuL[r][t] * PsuL[t][r] * sSSS;
      }
  }

  /* suR */
  for (r=0; r<2; r++) {

    TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_gluino,0.0L,m2_suR[r],Q2);
    TSIL_Evaluate (&bar, s);
    TSIL_CopyResult (&bar, &gaak); 
    V_FFFFS (&gaak, &gaak, 
	     &vFFFFS, &vFffFS, &vfFfFS, &vfFFfS, &vFFffS, &vffffS);

    /* Tese terms are all zero since the fermion mass is zero */
    /* term = -2.0L*NsuL[i][j]* 0.0L *m_gluino*vfFfFS */
    /*   + NsuL[i][j]*NsuL[r][r]*0.0L* 0.0L *(vfFFfS + m2_gluino*vffffS); */

    if (i == j)
      term += vFFFFS + m2_gluino*vFffFS 
	/* - 2.0L*NsuL[r][r]* 0.0L *m_gluino*vFFffS */
	;

    for (k=0; k<2; k++)
      for (t=0; t<2; t++) {
        TSIL_SetParametersST (&bar,m2_suL[k],m2_suR[r],m2_suR[t],Q2);
        TSIL_Evaluate (&bar, s);
        /* For clarity (just need this one function): */
        sSSS = -bar.S[uxv].value;
	term += 0.25L * PsuL[i][k] * PsuL[k][j] * PsuL[r][t] * PsuL[t][r] * sSSS;
      }
  }

  /* sdL */
  for (r=0; r<2; r++) {

    TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_gluino,0.0L,m2_sdL[r],Q2);
    TSIL_Evaluate (&bar, s);
    TSIL_CopyResult (&bar, &gaak); 
    V_FFFFS (&gaak, &gaak, 
	     &vFFFFS, &vFffFS, &vfFfFS, &vfFFfS, &vFFffS, &vffffS);

    /* Tese terms are all zero since the fermion mass is zero */
    /* term = -2.0L*NsuL[i][j]* 0.0L *m_gluino*vfFfFS */
    /*   + NsuL[i][j]*NsuL[r][r]*0.0L* 0.0L *(vfFFfS + m2_gluino*vffffS); */

    if (i == j)
      term += vFFFFS + m2_gluino*vFffFS 
	/* - 2.0L*NsuL[r][r]* 0.0L *m_gluino*vFFffS */
	;

    for (k=0; k<2; k++)
      for (t=0; t<2; t++) {
        TSIL_SetParametersST (&bar,m2_suL[k],m2_sdL[r],m2_sdL[t],Q2);
        TSIL_Evaluate (&bar, s);
        /* For clarity (just need this one function): */
        sSSS = -bar.S[uxv].value;
	term += 0.25L * PsuL[i][k] * PsuL[k][j] * PsuL[r][t] * PsuL[t][r] * sSSS;
      }
  }

  /* sdR */
  for (r=0; r<2; r++) {

    TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_gluino,0.0L,m2_sdR[r],Q2);
    TSIL_Evaluate (&bar, s);
    TSIL_CopyResult (&bar, &gaak); 
    V_FFFFS (&gaak, &gaak, 
	     &vFFFFS, &vFffFS, &vfFfFS, &vfFFfS, &vFFffS, &vffffS);

    /* Tese terms are all zero since the fermion mass is zero */
    /* term = -2.0L*NsuL[i][j]* 0.0L *m_gluino*vfFfFS */
    /*   + NsuL[i][j]*NsuL[r][r]*0.0L* 0.0L *(vfFFfS + m2_gluino*vffffS); */

    if (i == j)
      term += vFFFFS + m2_gluino*vFffFS 
	/* - 2.0L*NsuL[r][r]* 0.0L *m_gluino*vFFffS */
	;

    for (k=0; k<2; k++)
      for (t=0; t<2; t++) {
        TSIL_SetParametersST (&bar,m2_suL[k],m2_sdR[r],m2_sdR[t],Q2);
        TSIL_Evaluate (&bar, s);
        /* For clarity (just need this one function): */
        sSSS = -bar.S[uxv].value;
	term += 0.25L * PsuL[i][k] * PsuL[k][j] * PsuL[r][t] * PsuL[t][r] * sSSS;
      }
  }
  result += 4.0L*Cq*Iq*term;

  result *= g3*g3*g3*g3;
  /* End of eq. (4.8) */

  return result;
}

/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */
/* Eq. (4.9), tilde version (i.e., with j=i and tilded versions of
   G_SSS, G_SSFF, and G_SSff).

   Note s arg technically redundant since this should only ever be
   evaluated for s = m2_suL[i]. */

TSIL_COMPLEX pi21tilde_suL (int i, TSIL_REAL s) 
{
  int k;
  TSIL_COMPLEX result = 0.0L;
  TSIL_DATA bar;
  TSIL_RESULT gaak;
  TSIL_COMPLEX gFF,gff;
  TSIL_COMPLEX gSSFF,gSSff;

  if (arePandNsuLSet == NO) SetPandNsuL ();

  TSIL_SetParameters (&bar,0.0L,0.0L,m2_gluino,m2_gluino,0.0L,Q2);
  TSIL_Evaluate (&bar, s);
  TSIL_CopyResult (&bar, &gaak); 
  G_FF (&gaak, &gFF, &gff);

  TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_suL[i],0.1L,m2_gluino,Q2);
  TSIL_Evaluate (&bar, s);
  TSIL_CopyResult (&bar, &gaak);
  Gtilde_SSFF (&gaak, &gSSFF, &gSSff);

  TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_suL[i],0.01L,m2_gluino,Q2);
  TSIL_Evaluate (&bar, s);
  TSIL_CopyResult (&bar, &gaak);
  Gtilde_SSFF (&gaak, &gSSFF, &gSSff);

  TSIL_SetParameters (&bar,0.0L,m2_gluino,m2_suL[i],0.0L,m2_gluino,Q2);
  TSIL_Evaluate (&bar, s);
  TSIL_CopyResult (&bar, &gaak);
  Gtilde_SSFF (&gaak, &gSSFF, &gSSff);

  /* NOTE m_q = 0 for up != top */
  result += Cq*CG*(gFF + gSSFF 
		   /* - NsuL[i][i]*0.0L*m_gluino*(gff + gSSff) */
		   );

  TSIL_SetParameters (&bar,0.0L,0.0L,m2_suL[i],m2_gluino,0.0L,Q2);
  TSIL_Evaluate (&bar, s);
  TSIL_CopyResult (&bar, &gaak);
  Gtilde_SSFF (&gaak, &gSSFF, &gSSff);

  result += (2.0L*Cq - CG)*Cq*(gSSFF
			       /* - NsuL[i][i]*0.0L*m_gluino*gSSff */
			       );

  for (k=0; k<2; k++)
    result += Cq * Cq * PsuL[i][k] * PsuL[k][i] *
      (G_S(m2_suL[k],Q2) + Gtilde_SSS(m2_suL[i],m2_suL[k],Q2));

  result *= g3*g3*g3*g3;

  return result;
}

/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */
/* Eq. (4.10), tilde version */
/* s arg is useless for same reason as above... */

TSIL_COMPLEX pi22tilde_suL (int i, TSIL_REAL s) 
{
  int r;
  TSIL_COMPLEX result, term;

  result = Cq*F1tilde(m2_suL[i], Q2) 
         + CG*F2tilde(m2_suL[i], Q2)
         + CG*F3tilde(m2_suL[i], m2_gluino, Q2);

  /* Now do final sum over r. First is r = top. Note that the two F3
     terms are the same for r=top, and all remaining F3 terms are
     identical for m_quark = 0. */
  term = 2.0L*F3tilde(m2_suL[i], m2_top, Q2) 
       + 2.0L*F3tilde(m2_suL[i], m2_bot, Q2) 
       + 8.0L*F3tilde(m2_suL[i], 0.0L, Q2);

  for (r=0; r<2; r++)
    term += F4tilde(m2_suL[i], m2_stop[r], Q2)
          + F4tilde(m2_suL[i], m2_sbot[r], Q2)
          + F4tilde(m2_suL[i], m2_suL[r], Q2)
          + F4tilde(m2_suL[i], m2_suR[r], Q2)
          + F4tilde(m2_suL[i], m2_sdL[r], Q2)
          + F4tilde(m2_suL[i], m2_sdR[r], Q2);

  /* Final assembly: */
  result += Iq*term;
  result *= g3*g3*g3*g3*Cq;

  return result;
}

/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */
/* eq. (4.12); valid for s = m2_suL[i] */

TSIL_COMPLEX pi20tilde_suL (int i, TSIL_REAL s) 
{
  if (arePandNsuLSet == NO) SetPandNsuL ();

  return pi20_suL (i, i, s) 
    + pi1_suL (i, i, s) * 2.0L * g3 * g3 * Cq * (BpFF(0.0L,m2_gluino,s,Q2) 
    /* - NsuL[i][i] * 0.0L * m_gluino * Bpff(0.0L,m2_gluino,s,Q2) */
						  );
}
