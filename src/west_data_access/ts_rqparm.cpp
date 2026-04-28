#include "ts_rqparam.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include "tstype.h"
#include "tserreur.h"
#include "west_logging.h"
#include "Include_tslib_w32.h"
#include "tsparse.h"
#include <unistd.h>

#define MAXDATAPC 100000

struct sigaction newact, oldact;
sigset_t newmask, oldmask;
char tslib_reel = 'f';

Longint cr;
Longint extract = 1;
Longint l_rang = 1;      /* lecture rang par defaut */         /** +++  **/
Longint nb_extr2 = -1; /* nbre mesures quand extract = 2 */  /** +++  **/
Longint extraction, np_specif;
Longint num;
Longint nouttemp;
Longint type, absolute;


Longint lit_traite(char* nomsigp, Longint numchoc, Longint occ,
		Longint rang[], Double** X, Double** Y, Longint* maxreel);
void meser(char* mes1, char* mes2, Longint numer, Longint code);

/******************* tests tsrqparm *********************************/
Longint tsrqparm(char** pt_char_address, Longint* nb_val, Longint num_choc, const char* nom_prod, const char* nom_objet, const char* nom_param,
		Longint val_nb, int *output_format)
{
	//int format;
	Longint i;

	Longint cr = TSRqParm(num_choc, nom_prod, nom_objet, nom_param, val_nb,
				  pt_char_address, nb_val, output_format);
				  
	char *pt_char = *pt_char_address;
	
	int debug = 0;

        int format = *output_format;

	if (cr == 0 && debug == 1)
	{
		printf("nb_val=%d, format=%d\n", *nb_val, format);
		if (val_nb > *nb_val) val_nb = *nb_val;
		switch (format)
		{
			case OCTET:
			{
				short *pt_short;

				pt_short = (short *)pt_char;
				for (i = 0; i < val_nb; i++)
				{
					printf("OCTET::valeur %d : %d\n", i, *pt_short);
					pt_short += 1;
				}
				break;
			}
			case STRING12:
			{
				char	strg[13], *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(strg, ptc, 13);
					printf("valeur %d : %s\n", i, strg);
					ptc += 13;
				}
				break;
			}
			case INT16:
			{
				short *pt_short;
				pt_short = (short *)pt_char;

				for (i = 0; i < val_nb; i++)
				{
					printf("INT16::valeur %d : %d \n", i, *pt_short);
					pt_short += 1;
				}
				break;
			}
			case INT32:
			{
				int *pt_int;
				pt_int = (int *)pt_char;
				for (i = 0; i < val_nb; i++)
				{
					printf("INT32::valeur %d : %d \n", i, *pt_int);
					pt_int += 1;
				}
				break;
			}
			case REEL16:
			{
				float *pt_float;
				pt_float = (float *)pt_char;
				for (i = 0; i < val_nb; i++)
				{
					printf("REEL16::valeur %d : %f\n", i, *pt_float);
					pt_float += 1;
				}
				break;
			}
			case REEL32:
			{
				double *pt_double;
				pt_double = (double *)pt_char;
				for (i = 0; i < val_nb; i++)
				{
					printf("REEL32::valeur %d : %6.3f\n", i, *pt_double);
					pt_double += 1;
				}
				break;
			}
			case TWIN_INT16:
			{
				short *pt_short;
				pt_short = (short *)pt_char;
				for (i = 0; i < val_nb; i++)
				{
					printf("valeur %d : %d %d \n", i,
						   *pt_short, *(pt_short+1));
					pt_short += 2;
				}
				break;
			}
			case TWIN_REEL32:
			{
				float *pt_float;
				pt_float = (float *)pt_char;
				for (i = 0; i < val_nb; i++)
				{
					printf("valeur %d : %6.3f %6.3f \n", i,
						   *pt_float, *(pt_float+1));
					pt_float += 2;
				}
				break;
			}
			case INT_REEL32:
			{
				int v_int;
				float v_float;
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					v_int = *(int *)ptc;
					v_float = *(float *)(ptc+4);
					printf("valeur %d : %d %6.3f \n", i,
						   v_int, v_float);
					ptc += 8;
				}
				break;
			}
			case VOIE:
			{
				short voie;
				char	carte[L_NOM_CARTE], *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&voie, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(carte, ptc, L_NOM_CARTE);
					ptc += L_NOM_CARTE;
					printf("voie %d carte %s \n", voie, carte);
				}
				break;
			}
			case FONCTION:
			{
				char type[3];
				float amplitude, periode, ti, tf, yi, yf;
				short offset;
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(type, ptc, 3);
					ptc += 3;
					memcpy(&amplitude, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&periode, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&ti, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&tf, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&yi, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&yf, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&offset, ptc, sizeof(short));
					ptc += sizeof(short);
					printf(" type %s amp %f  \n", type, amplitude);
					printf("per %f ti %f tf %f yi %f yf %f of %d \n",
						   periode, ti, tf, yi, yf, offset);
				}
				break;
			}
			case VOIE_GAIN:
			{
				struct vgain
				{
					short voie;
					short gainpro;
					float gainfix;
				} *pt_vgain;

				pt_vgain = (struct vgain *) pt_char;
				for (i = 0; i < val_nb; i++)
				{
					printf("voie %d  gainpro %d gainfix %6.3f \n",
						   pt_vgain->voie, pt_vgain->gainpro, pt_vgain->gainfix);
					pt_vgain += 1;
				}
				break;
			}
			case REGISTRE:
			{
				struct reg
				{
					short numreg;
					char declenche[L_NOM_DECLENCHE];
					char comment[L_COMMENTAIRE];
				} *pt_reg;

				pt_reg = (struct reg *) pt_char;
				for (i = 0; i < val_nb; i++)
				{
					printf("reg %d decl %s com %s \n",
						   pt_reg->numreg, pt_reg->declenche, pt_reg->comment);
					pt_reg += 1;
				}
				break;
			}
			case F_STRAT_DIAG:
			{
				char nom[L_NOM_DONNEE], *ptc;
				short algo, a, b;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(nom, ptc, L_NOM_DONNEE);
					ptc += L_NOM_DONNEE;
					memcpy(&algo, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&a, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&b, ptc, sizeof(short));
					ptc += sizeof(short);
					printf("nom %s algo %d a %d b %d \n", nom, algo, a, b);
				}
				break;
			}
			case STRAT_PILOTE:
			{
				char ndiag[L_NOM_PRODUCTEUR];
				char nstrat[L_NOM_STRATEGIE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(ndiag, ptc, L_NOM_PRODUCTEUR);
					ptc += L_NOM_PRODUCTEUR;
					strncpy(nstrat, ptc, L_NOM_STRATEGIE);
					ptc += L_NOM_STRATEGIE;
					printf("diag %s strat %s \n", ndiag, nstrat);
				}
				break;
			}
			case DECL_COND:
			{
				char decl[L_NOM_DECLENCHE];
				char cond[33];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(decl, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					strncpy(cond, ptc, 33);
					ptc += 33;
					printf("decl %s cond %s \n", decl, cond);
				}
				break;
			}
			case EVT_EXTERNE:
			{
				char vld[2];
				char nref[L_NOM_REF];
				char nevt[L_NOM_EVENEMENT];
				float dbvld, fnvld;
				char cmt[L_COMMENTAIRE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(vld, ptc, 2);
					ptc += 2;
					strncpy(nref, ptc, L_NOM_REF);
					ptc += L_NOM_REF;
					strncpy(nevt, ptc, L_NOM_EVENEMENT);
					ptc += L_NOM_EVENEMENT;
					memcpy(&dbvld, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&fnvld, ptc, sizeof(float));
					ptc += sizeof(float);
					strncpy(cmt, ptc, L_COMMENTAIRE);
					ptc += L_COMMENTAIRE;
					printf("valid %s ref %s evt %s \n", vld, nref, nevt);
					printf("debvalid %6.3f finvalid %6.3f com %s \n", dbvld, fnvld, cmt);
				}
				break;
			}
			case SERNAM:
			{
				short	code;
				char nom[L_NOM_DECLENCHE];
				char affich[2], *ptc;
				char cmt[L_COMMENTAIRE];

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					code = *(short*)ptc;
					ptc += sizeof(short);
					strncpy(nom, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					strncpy(affich, ptc, 2);
					ptc += 2;
					strncpy(cmt, ptc, L_COMMENTAIRE);
					ptc += L_COMMENTAIRE;
					printf("code %d decl %s affich %s \n", code, nom, affich);
					printf("commentaire %s \n", cmt);
				}
				break;
			}
			case CADRAN:
			{
				short	code;
				char	nom[L_NOM_DECLENCHE];
				char	affich[2];
				char	strpil[L_NOM_STRATEGIE];
				char	cmt[L_COMMENTAIRE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&code, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(nom, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					strncpy(affich, ptc, 2);
					ptc += 2;
					strncpy(strpil, ptc, L_NOM_STRATEGIE);
					ptc += L_NOM_STRATEGIE;
					strncpy(cmt, ptc, L_COMMENTAIRE);
					ptc += L_COMMENTAIRE;
					printf("code %d decl %s affich %s \n", code, nom, affich);
					printf("strat %s commentaire %s \n", strpil, cmt);
				}
				break;
			}
			case LIEN:
			{
				char decl1[L_NOM_DECLENCHE];
				char decl2[L_NOM_DECLENCHE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(decl1, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					strncpy(decl2, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					printf("decl1 %s decl2 %s \n", decl1, decl2);
				}
				break;
			}
			case DECL_SEQ:
			{
				char ctype[L_CTYPE];
				char decl[L_NOM_DECLENCHE];
				char carte[L_NOM_CARTE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(ctype, ptc, L_CTYPE);
					ptc += L_CTYPE;
					strncpy(decl, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					strncpy(carte, ptc, L_NOM_CARTE);
					ptc += L_NOM_CARTE;
					printf("ctype %s declenche %s carte %s \n", ctype, decl, carte);
				}
				break;
			}
			case VOIE_SEQ:
			{
				short	voie, polar;
				int duree;
				char	cmt[L_COMMENTAIRE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&voie, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&polar, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&duree, ptc, sizeof(int));
					ptc += sizeof(int);
					strncpy(cmt, ptc, L_COMMENTAIRE);
					ptc += L_COMMENTAIRE;
					printf("voie %d polar %d duree %d \n", voie, polar, duree);
					printf("commentaire %s \n", cmt);
				}
				break;
			}
			case TAB_SEQ:
			{
				short voie;
				int temps, cad;
				short nbimp;
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&voie, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&temps, ptc, sizeof(int));
					ptc += sizeof(int);
					memcpy(&cad, ptc, sizeof(int));
					ptc += sizeof(int);
					memcpy(&nbimp, ptc, sizeof(short));
					ptc += sizeof(short);
					printf("voie %d temps %d cad %d nbimp %d \n", voie, temps, cad, nbimp);
				}
				break;
			}
			case T_DECODE:
			{
				char	type[2];
				short	polar;
				char	decl1[L_NOM_DECLENCHE];
				char	decl2[L_NOM_DECLENCHE];
				int	duree;
				char	cmt[L_COMMENTAIRE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(type, ptc, 2);
					ptc += 2;
					memcpy(&polar, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(decl1, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					strncpy(decl2, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					memcpy(&duree, ptc, sizeof(int));
					ptc += sizeof(int);
					strncpy(cmt, ptc, L_COMMENTAIRE);
					ptc += L_COMMENTAIRE;
					printf("type %s polar %d decl1 %s decl2 %s duree %d \n",
						   type, polar, decl1, decl2, duree);
					printf("commentaire %s \n", cmt);
				}
				break;
			}
			case T_IT:
			{
				short	polar;
				char	decl[L_NOM_DECLENCHE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&polar, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(decl, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					printf("polar %d decl %s \n", polar, decl);
				}
				break;
			}
			case T_ENCODE:
			{
				char	type[2];
				short	polar;
				char	decl[L_NOM_DECLENCHE];
				short	nbsaut, nbmax;
				char	cmt[L_COMMENTAIRE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(type, ptc, 2);
					ptc += 2;
					memcpy(&polar, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(decl, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					memcpy(&nbsaut, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&nbmax, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(cmt, ptc, L_COMMENTAIRE);
					ptc += L_COMMENTAIRE;
					printf("type %s polar %d decl %s saut %d nbmax %d\n",
						   type, polar, decl, nbsaut, nbmax);
					printf("commentaire %s \n", cmt);
				}
				break;
			}
			case F_COMMON:
			{
				char	diag[L_NOM_PRODUCTEUR];
				char	objet[L_NOM_OBJET];
				char	param[L_NOM_PARAM];
				char	col[L_NOM_COLONNE];
				char	format[L_FORMAT];
				short	ind1, ind2;
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(diag, ptc, L_NOM_PRODUCTEUR);
					ptc += L_NOM_PRODUCTEUR;
					strncpy(objet, ptc, L_NOM_OBJET);
					ptc += L_NOM_OBJET;
					strncpy(param, ptc, L_NOM_PARAM);
					ptc += L_NOM_PARAM;
					strncpy(col, ptc, L_NOM_COLONNE);
					ptc += L_NOM_COLONNE;
					memcpy(&ind1, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&ind2, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(format, ptc, L_FORMAT);
					ptc += L_FORMAT;
					printf("diag %s objet %s param %s col %s i1 %d i2 %d ft %s\n",
						   diag, objet, param, col, ind1, ind2, format);
				}
				break;
			}
			case F_CHRONO:
			{
				char	valid[2];
				char	repere[L_NOM_REPERE];
				char	decl[L_NOM_DECLENCHE];
				char	typedecl[2];
				float	decalage, duree;
				char	ref[9];
				char	cmt[L_COMMENTAIRE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(valid, ptc, 2);
					ptc += 2;
					strncpy(typedecl, ptc, 2);
					ptc += 2;
					strncpy(repere, ptc, L_NOM_REPERE);
					ptc += L_NOM_REPERE;
					strncpy(decl, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					memcpy(&decalage, ptc, sizeof(float));
					ptc += sizeof(float);
					strncpy(ref, ptc, 9);
					ptc += 9;
					memcpy(&duree, ptc, sizeof(float));
					ptc += sizeof(float);
					strncpy(cmt, ptc, L_COMMENTAIRE);
					ptc += L_COMMENTAIRE;
					printf("valid %s repere %s decl %s typ %s dec %6.3f ref %s dt %f\n",
						   valid, repere, decl, typedecl, decalage, ref, duree);
					printf("commentaire %s \n", cmt);
				}
				break;
			}
			case T_DECLENC:
			{
				char	nom[L_NOM_DECLENCHE];
				float	temps;
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(nom, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					memcpy(&temps, ptc, sizeof(float));
					ptc += sizeof(float);
					printf("nom %s valeur : %f \n", nom, temps);
				}
				break;
			}
			case L_DIAG:
			{
				char    nomdiag[L_NOM_OBJET];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(nomdiag, ptc, L_NOM_OBJET);
					ptc += L_NOM_OBJET;
					printf("nomdiag %s \n", nomdiag);
				}
				/*  free(pt_char); */
				break;
			}
			case T_DECLENCHE:
			{
				char decl[L_NOM_DECLENCHE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(decl, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					printf("declenche %s \n", decl);
				}
				break;
			}
			case TEXTE:
			{
				char texte[L_TEXTE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					strncpy(texte, ptc, L_TEXTE);
					ptc += L_TEXTE;
					printf("texte %s \n", texte);
				}
				break;
			}
			case F_TOPMSDIV:
			{
				short   type, autor, duree, sens;
				char    topms[L_NOM_DECLENCHE];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&type, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&autor, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(topms, ptc, L_NOM_DECLENCHE);
					ptc += L_NOM_DECLENCHE;
					memcpy(&duree, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&sens, ptc, sizeof(short));
					ptc += sizeof(short);
					printf("type %d autorisation %d topms %s duree %d sens %d\n",
						   type, autor, topms, duree, sens);
				}
				break;
			}
			case GRAPHE:
			{
				short no_page, no_graphe;
				char  titre[L_TITRE];
				float xmin, xmax, ymin, ymax;
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&no_page, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&no_graphe, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(titre, ptc, L_TITRE);
					ptc += L_TITRE;
					memcpy(&xmin, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&xmax, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&ymin, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&ymax, ptc, sizeof(float));
					ptc += sizeof(float);
					printf("page %d graphe %d titre %s \n",
						   no_page, no_graphe, titre);
					printf("xmin %6.3f xmax %6.3f ymin %6.3f ymax %6.3f \n",
						   xmin, xmax, ymin, ymax);
				}
				break;
			}
			case SIGNAL:
			{
				short no_page, no_graphe, indice, tri;
				char signal[L_NOM_OBJET];
				char couleur[L_COULEUR_SIGNAL];
				char valid[2];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&no_page, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(&no_graphe, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(signal, ptc, L_NOM_OBJET);
					ptc += L_NOM_OBJET;
					memcpy(&indice, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(couleur, ptc, L_COULEUR_SIGNAL);
					ptc += L_COULEUR_SIGNAL;
					memcpy(&tri, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(valid, ptc, 2);
					ptc += 2;
					printf("page %d graphe %d signal %s \n",
						   no_page, no_graphe, signal);
					printf("indice %d couleur %s tri %d valid %s \n",
						   indice, couleur, tri, valid);
				}
				break;
			}

			case INT2_CHAR64:
			{
				short int2;
				char	cmt[65], *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&int2, ptc, sizeof(short));
					ptc += sizeof(short);
					strncpy(cmt, ptc, 65);
					ptc += 65;
					printf("int2 : %d\tcmt : %s \n", int2, cmt);
				}
				break;
			}

			case FLOAT_CHAR64:
			{
				float float4;
				char	cmt[65], *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&float4, ptc, sizeof(float));
					ptc += sizeof(float);
					strncpy(cmt, ptc, 65);
					ptc += 65;
					printf("float4 : %6.2f\tcmt : %s \n", float4, cmt);
				}
				break;
			}

			case F_ACHRONO:
			{
				float decalage, duree;
				char code[2], type[2];
				char declenche[13];
				char comment[33];
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(code, ptc, sizeof(char)*2);
					ptc += sizeof(char) * 2;
					memcpy(type, ptc, sizeof(char)*2);
					ptc += sizeof(char) * 2;
					memcpy(declenche, ptc, sizeof(char)*13);
					ptc += sizeof(char) * 13;
					memcpy(&decalage, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(&duree, ptc, sizeof(float));
					ptc += sizeof(float);
					memcpy(comment, ptc, sizeof(char)*33);
					ptc += sizeof(char) * 33;
					printf("Code %s Type %s Declenche %s Decalage %g Duree %g Cmt %s\n",
						   code, type, declenche, decalage, duree, comment);

				}
			}
			break;

			case F_DESCRIPTEUR:
			{
				int num_choc;
				char nom_diag[13], donnee_brute[13], nom_trait[13], donnee_traitee[13];
				short indiceb, indicet;
				char *ptc;

				ptc = pt_char;
				for (i = 0; i < val_nb; i++)
				{
					memcpy(&num_choc, ptc, sizeof(int));
					ptc += sizeof(int);
					memcpy(nom_diag, ptc, sizeof(char)*13);
					ptc += sizeof(char) * 13;
					memcpy(donnee_brute, ptc, sizeof(char)*13);
					ptc += sizeof(char) * 13;
					memcpy(&indiceb, ptc, sizeof(short));
					ptc += sizeof(short);
					memcpy(nom_trait, ptc, sizeof(char)*13);
					ptc += sizeof(char) * 13;
					memcpy(donnee_traitee, ptc, sizeof(char)*13);
					ptc += sizeof(char) * 13;
					memcpy(&indicet, ptc, sizeof(short));
					ptc += sizeof(short);
					printf("Num choc %d Nom diag. %s Donnee brute %s Indice %d Nom trait %s Donnee traitee %s Indice %d\n",
						   num_choc, nom_diag, donnee_brute, indiceb, nom_trait, donnee_traitee, indicet);
				}
			}
			break;

			default:  puts(" Not yet implemented ");
		}
		//free(pt_char);	
	}
	else
	{
		if (debug ==1) printf("erreur tsrqparam %d\n", cr);
	}

	return cr;
}

Longint readSignal(char* nomsigp, Longint numchoc, Longint occ,
		Longint rang[], Double** X, Double** Y, Longint* len)
{
	//UDA_LOG(UDA_LOG_DEBUG, "ts_rqparm::reading signal: %s\n", nomsigp);
	Longint attempts = 3;
	cr = -1;
	Longint i = 1;
	while (cr != 0 && cr != 32 && attempts != 0) { //cr=32 means that no data are available for this shot
		UDA_LOG(UDA_LOG_DEBUG, "ts_rqparm::calling lit_traite...\n");
		cr = lit_traite(nomsigp, numchoc, occ, rang, (Double**)X, (Double**)Y, (Longint*)len);
		UDA_LOG(UDA_LOG_DEBUG, "ts_rqparm::readSignal, cr status=%ld\n", cr);
		if (cr != 0) {
			UDA_LOG(UDA_LOG_ERROR, "WEST:WARNING: attempt %ld for reading ARCAD signal %s has failed for shot %ld, cr=%ld\n", i, nomsigp, numchoc,cr);
			attempts = attempts - 1;
			sleep(0.001);
			i++;
		}
	}

	//    UDA_LOG(LOG_DEBUG, "%s\n", "First time values...");
	//    Longint j;
	//    for (j=0; j <10; j++) {
	//    		UDA_LOG(LOG_DEBUG, "value : %f\n", *(*X + j));
	//    }
	if (cr == 0) {
		Longint i;
		for (i = 0; i < *len; i++)
			*(*X + i) = *(*X + i) / CTPS; //TSLib gives the time in µs, so we do this conversion to put the time in seconds
	}
	return cr;
}

Longint
lit_traite(char* nomsigp, Longint numchoc, Longint occ,
		Longint rang[], Double** X, Double** Y, Longint* maxreel)
{
	//TODO : mxArray * pout[];
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called...\n");
	Double xab[2] = { 0, 0 };
	Longint nout = 2;
	register Longint i, j;
	Longint nbmax, nbmes, nbmesgr[3], lind[5], cr, cr1, numv;
	Longint nbcoord[MAX_COORD], nb_certif, rgrp = 0;
	/** +++ **/
	/* Longint	rang[2], maxreel, cooked_d = 0, fcomment = 0;*/
	Longint cooked_d = 0, fcomment = 0;

	Longint indices[2], rscalaire = 0, scomment = 0;
	Longint certif[MAX_CERTIF];

	Double Coord[10 * MAX_SIG];
	char* Xc, * Yc;
	char date[TAILLE_DATE], heure[TAILLE_HEURE], cmisc[TAILLE_MISC] = { '\0' };
	char* ptd, nomsig[TAILLE_NOM_DONNEE], nom_gen[TAILLE_NOM_DONNEE];
	char aff[64], nomsig_misc[TAILLE_NOM_DONNEE + 4];
	/********* New for ARCAD ************/
	/* pS_DescDon ptDescDon; */
	ts_donnee* ptDescDon;
	/********* New for ARCAD ************/
	pS_Entree ptEntree;
	pS_Unite ptUnite = NULL;
	//float *pr;
	Longint occur = 0, indg = 0;
	short pansement = 0, generique = 1;

	ptEntree = (pS_Entree)calloc(1, sizeof(struct S_Entree));
	ptEntree->union_var.lval = numchoc;
	
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called2...\n");

	/*****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/
	if (nomsigp[0] == '!') {
		strcpy(nomsigp, &nomsigp[1]);
		generique = 0;
	}
	/*****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/

	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called3...\n");
	tsparse(nomsigp, nomsig, indices, &rgrp, &occur);
	//tsparse (char *string, char *nomsig, Longint indices[], Longint *extr, Longint *occur)
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called4...\n");
	if (occ) {
		occur = occ;
	}
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called41...\n");
	if (occur) {
		ptEntree->ps_suivant = (pS_Entree)calloc(1, sizeof(struct S_Entree));
		ptEntree->ps_suivant->union_var.lval = occur;
		ptEntree->ps_suivant->ps_suivant = NULL;
	} else {
		ptEntree->ps_suivant = NULL;
	}
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called42...\n");
	for (i = 0; i < MAX_CERTIF; i++)
		certif[i] = 0;
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called43...\n");
	for (i = 0; i < MAX_COORD; i++)
		nbcoord[i] = 0;
#ifdef DEBUG
	printf ("avant Tsexist signal %s choc %ld \n", nomsig, numchoc);
#endif
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called44...\n");
	UDA_LOG(UDA_LOG_DEBUG, "nomsig=%s\n", nomsig);
	UDA_LOG(UDA_LOG_DEBUG, "nom_gen=%s\n", nom_gen);
	cr = TSExist_gen(nomsig, ptEntree, nbcoord, &numv, certif, date, heure,
			nom_gen, &indg);
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called45...\n");
	if ((strncmp(nomsig, nom_gen, strlen(nomsig))) && (nom_gen[0] == 'G')) {
		pansement = 1;
	}
	UDA_LOG(UDA_LOG_DEBUG, "lit_traite is called5...\n");
	/*****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/
	if ((extract > 3) && ((nom_gen[0] == 'g') || (nom_gen[0] == 'G')) &&
			(rgrp == 0)) {
		extract = 1;
	}

	if (generique)
		strcpy(nomsig, nom_gen);
	if (indg != 0) {
		rgrp = 1;
		indices[0] = indg;
		sprintf(aff, "lisant %s %ld !", nomsig, indg);
	} else
		sprintf(aff, "lisant %s !", nomsig);

#ifdef DEBUG
	printf ("Tsexist cr = %ld nbcoord[0] %ld \n", cr, nbcoord[0]);
#endif
	if (cr || (nbcoord[0] == 0)) {                /* ncoord[0]= 0 si certif <= -2 */
		if (cr) {            /* verification de l'existence du choc */
			cr1 = TSExist("num_choc", ptEntree, nbcoord, &numv, certif, date, heure);
			if (cr1) {            /* le choc n'existe pas */

				switch (cr1) {
				case 103:
					printf("Tslib Server down !!! \n");
					printf("N'en fau tasta per lou saupre \n");
					break;
				default:
					printf("TSExist - %s Choc absent cr1 = %ld\n",
							nomsig, cr1);
				}
				free(ptEntree);
				UDA_LOG(UDA_LOG_DEBUG, "Returning from 1\n");
				return (cr);
			}
		}
#ifdef DEBUG
		printf ("Tsexist cr = %ld nbcoord[0] %ld \n", cr, nbcoord[0]);
#endif
		/* Unites , date , heure , certifs ...   quand certif <= -2 */
		if (nbcoord[0] == 0) {            /* certif =-2 */
			cr = TSDescDon_choc(nomsig, numchoc, 0, &ptDescDon);
			if (cr) {
				char* meser_msg = (char *) ("TSDescDon_choc - ");
				meser(meser_msg, nomsig, cr, FATAL);
			}
			if ((ptDescDon->type_donnee >> S_SIMPLE) & 1) { /* signal simple */
				type = sigType;
			} else if ((ptDescDon->type_donnee >> D_GHOMO) & 1) { /* groupe */
				type = homoType;
			} else {
				char* meser_msg = (char *) ("Who are you ?");
				meser(meser_msg, nomsig, 1002, FATAL);
			}

			if (ptDescDon->type_donnee & 1 << 1) {  /* donnee traitee */
				cooked_d = 1;
			}
			free (ptDescDon);
			UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "Type of signal:", type);

			switch (type) {
			case homoType:
			case extgType:
				if (nout < 4) {
					printf("Il faut 4 arguments de sortie\n");
					UDA_LOG(UDA_LOG_DEBUG, "Returning from 2\n");
					return (cr);
				}
				break;
			default:
				if (nout < 3) {
					printf("Il faut 3 arguments de sortie\n");
					UDA_LOG(UDA_LOG_DEBUG, "Returning from 3\n");
					return (cr);
				}
				break;
			}

			j = num + 2;        /* on saute Y et T qui sont vides */
			if ((type == homoType) || (type == extgType)) {
				j++;
			}        /* certif = 4eme arg */

			ptd = cmisc;
#if (client == PC)
			strcpy (ptd, " ");
			for (i = 1; i < 2 * LONG_UNITE; i++)
				strcat (ptd, " ");	/* Simule Unites X et Y */
#else
			for (i = 0; i < 2 * LONG_UNITE; i++)    /* Simule Unites X et Y */
				*ptd++ = ' ';
			*ptd = '\0';
#endif
			strcat (cmisc, date);
			strcat (cmisc, heure);
			/*****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/
			ptd = cmisc;
			while (*ptd)
				ptd++;

			if (indg > 0)
				sprintf(nomsig_misc, "%s%ld", nomsig, indg);
			else
				strcpy(nomsig_misc, nomsig);

			for (i = 0; i < TAILLE_NOM_DONNEE + 4; i++) {
				if (i < strlen(nomsig_misc)) {
					*ptd++ = nomsig_misc[i];
				} else {
					*ptd++ = ' ';
				}
			}
			*ptd = '\0';
			if (cooked_d)
				strcat(cmisc, "T");
			else
				strcat(cmisc, "B");
			/*****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/
			nb_certif = 1;

			if (type == homoType) {
				nb_certif += nbcoord[1] * (nbcoord[2] > 0 ? nbcoord[2] : 1);
			}
#ifdef DEBUG
			printf ("Tsexist cr = %ld misc num = %ld \n", cr, j);
#endif
			/*pout[j] = mxCreatefloatMatrix (strlen (cmisc) + 1 + nb_certif + 1, 1, mxREAL);
            pr = mxGetPr (pout[j]);
            pr[0] = (float) nb_certif;
            for (i = 0; i < nb_certif; i++)
                pr[1 + i] = (float) certif[i];
            pr[1 + nb_certif] = (float) numv;
            for (i = 0; i < strlen (cmisc); i++)
                pr[2 + nb_certif + i] = cmisc[i];*/
			/* Fin  Unites , date , heure , certifs ...   */
		}
		UDA_LOG(UDA_LOG_DEBUG, "Signal name at line 393 : %s\n", nomsig);
		char* meser_msg = (char *) ("TSExist - ");
		meser(meser_msg, nomsig, ((cr != 0) ? cr : 9), NONFATAL);
		if (cr != 0) {
			UDA_LOG(UDA_LOG_DEBUG, "TSExist return false \n");
		} else {
			UDA_LOG(UDA_LOG_DEBUG, "no comprendo ! \n");
		}
		if (occur) {
			printf
			("En fait c'est l'occurrence %ld du choc %ld qui n'exite pas :-)\n",
					occur, numchoc);
			UDA_LOG(UDA_LOG_DEBUG, "Occurrence : %ld\n", occur);

			UDA_LOG(UDA_LOG_DEBUG, "En fait c'est l'occurrence du choc qui n'exite pas\n");
		}
		free(ptEntree);
		UDA_LOG(UDA_LOG_DEBUG, "Returning from 4\n");
		return (((cr != 0) ? cr : 199));
	}

	
	/********* New for ARCAD ************/
	cr = TSDescDon_choc(nomsig, (Longint)numchoc, (Longint)0, &ptDescDon);
	/********* New for ARCAD ************/
	if (cr) {
		char* meser_msg = (char *) ("TSDescDon_choc - ");
		meser(meser_msg, nomsig, cr, FATAL);
	}

	if ((ptDescDon->type_donnee >> D_TRAITEE) & 1) {
		cooked_d = 1;        /* donnee traitee */
	}
	if ((ptDescDon->type_donnee >> S_SIMPLE) & 1) {    /* signal simple */
		type = sigType;
	} else if ((ptDescDon->type_donnee >> D_GHOMO) & 1) {    /* groupe homogene */
		type = homoType;
	} else {
		char* meser_msg = (char *) ("Who are you ?");
		meser(meser_msg, nomsig, 1002, FATAL);
	}

	UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "Type of signal at line 433:", type);

	if (rgrp) {
		type = extgType;
	}        /* extraction d'un signal demandee */

	if (!(ptDescDon->type_donnee >> SG_FTMPS & 1)) {                /* non fonction du temps */
		if (ptDescDon->nb_coordonnees == 1) {
			rscalaire = 1;
		} else if (ptDescDon->nb_coordonnees > 1) {
			rscalaire = 2;
		}

		/*      if (ptDescDon->ps_coord != NULL)
    {*/            /* format caractere ? */
#if (client == PC || client == MAC)
		if ((!strncmp (ptDescDon->formaty, "c", 1)) ||
				(!strncmp (ptDescDon->formaty, "C", 1)))
#else
			if (!strncasecmp(ptDescDon->formaty, "c", 1))
#endif
			{
				ptd = ptDescDon->formaty;
				ptd++;
				scomment = 1;
				fcomment = atoi(ptd);    /* taille format */
			}
		/* } */
	}
	/* YBYBYBYBYBYBYB  FreeMemM (ptDescDon); */
	free (ptDescDon);

#ifdef DEBUG
	printf ("type %ld scomment %ld rgrp %ld rscalaire %ld absolu %ld\n",
			type, scomment, rgrp, rscalaire, absolute);
#endif
	/* Read the data */

	nbmax = nbcoord[0];
	if (rang[0] == 0) {
		rang[0] = 1;
	}        /** +++  **/
#if (client == PC)
	if (nbcoord[0] > MAXDATAPC)
	{
		if (rang[1] == 0)
			rang[1] = MAXDATAPC;	/** +++ **/
		printf ("==> Attention plus de 100000 mesures on ne peut  <==\n");
		printf ("==> lire que 100000 mesures maximum sur les PCs  <==\n");
		printf ("==> pour plus de renseignements Y.Buravand 23.42 <==\n");
	}
	else if ( extraction || rang[1] == 0 || np_specif == 0)
		rang[1] = nbcoord[0];	/** +++ **/
#else
	if (extraction || rang[1] == 0 || np_specif == 0)
		rang[1] = nbcoord[0];    /** +++ **/
#endif

#ifdef DEBUG
	printf ("extraction %ld extr2 %ld l_rang %ld\n", extraction,nb_extr2,l_rang);
#endif
	printf("%s \n", aff);
	if (type == homoType) {
		Longint nbmax_sv;
		/*extract = 1;*/  /** ++++ **/
		if (nb_extr2 < 0) {
			nbmax = nbcoord[0] * nbcoord[1] * (nbcoord[2] > 0 ? nbcoord[2] : 1);
			nbmax_sv = nbmax;
		} else {
			nbmax = nb_extr2 * nbcoord[1] * (nbcoord[2] > 0 ? nbcoord[2] : 1);
			nbmax_sv = nb_extr2;
		}

		if (nbmax > 100000)
			printf("What a big signal !! be quiet please data are coming soon ...\n");
		if ((*X = (Double*)calloc(nbmax, sizeof(Double))) == NULL){ 
			char* meser_msg = (char *) ("Alloc7 - ");
			char* space = (char *) (" ");
			meser(meser_msg, space, 1001, FATAL);
		}	
		if ((*Y = (Double*)calloc(nbmax, sizeof(Double))) == NULL){ 
			char* meser_msg = (char *) ("Alloc8 - ");
			char* space = (char *) (" ");
			meser(meser_msg, space, 1001, FATAL);
		}	
		/** ++++   **/
		if (l_rang == 1) {
#ifdef DEBUG
			printf ("avant TSGrpRg rangs %ld %ld nbmax %ld\n", rang[0], rang[1], nbmax);
			printf ("avant TSGrpRg nbcoord %ld %ld %ld extract=%ld \n", nbcoord[0], nbcoord[1], nbcoord[2],extract);
#endif
			UDA_LOG(UDA_LOG_DEBUG, "%s\n", "Calling TSGrpRg...");
			cr = TSGrpRg(nomsig, ptEntree, rang, nbmax_sv, extract, &ptUnite,
					&numv, certif, date, heure, nbmesgr, maxreel,
					(char*)*X, (char*)*Y, (char*)Coord);
		} else {
#ifdef DEBUG
			printf ("avant TSGrpX abs %g %g nbmax %ld\n", xab[0], xab[1], nbmax);
#endif
			UDA_LOG(UDA_LOG_DEBUG, "%s\n", "Calling TSGrpX...");
			cr = TSGrpX(nomsig, ptEntree, xab[0], xab[1], nbmax_sv, extract, &ptUnite,
					&numv, certif, date, heure, nbmesgr, maxreel, (char*)*X,
					(char*)*Y, (char*)Coord);
		}

		if (cr != 0) {
			if (l_rang == 1){ 
				char* meser_msg = (char *) ("TSGrpRg - ");
				meser(meser_msg, nomsig, cr, NONFATAL);
			}	
			else{
				char* meser_msg = (char *) ("TSGrpX - ");
				meser(meser_msg, nomsig, cr, NONFATAL);
			}	
			free(ptEntree);
			//free (X);
			//free (Y);
			UDA_LOG(UDA_LOG_DEBUG, "Returning from 5\n");
			return (cr);
		}
		lind[0] = nbmesgr[0];
		lind[1] = nbcoord[1] * (nbcoord[2] > 0 ? nbcoord[2] : 1);
		if (cooked_d == 0)
			lind[2] = lind[1];
		else
			lind[2] = 1;
#ifdef DEBUG
		printf ("apres lecture homotype lind[0] %ld, lind[1] %ld, lind[2] %ld\n",
				lind[0], lind[1], lind[2]);
#endif
	} else if (type == sigType) {
		/*extract = 1; */   /*   ++++ **/
		/*     if (nb_extr2 < 0 && !scomment) */
		if (nb_extr2 < 0)
			nbmax = nbcoord[0];
		else
			nbmax = nb_extr2;

		if (scomment) {            /* signal commentaire  */
			nbmax = nbmax * fcomment;
			if ((Xc = (char*)calloc(nbmax, sizeof(char))) == NULL){ 
				char* meser_msg = (char *) ("Alloc9 - ");
				char* space = (char *) (" ");
				meser(meser_msg, space, 1001, FATAL);
			}	
			if ((Yc = (char*)calloc(nbmax, sizeof(char))) == NULL){ 
				char* meser_msg = (char *) ("Alloc10 - ");
				char* space = (char *) (" ");
				meser(meser_msg, space, 1001, FATAL);
			}	
#ifdef DEBUG
			printf ("avant TSRSIGRg rangs %ld %ld nbmax %ld\n", rang[0], rang[1], nbmax);
#endif
			UDA_LOG(UDA_LOG_DEBUG, "%s\n", "Calling TSRSigRg...");
			cr = TSRSigRg(nomsig, ptEntree, rang, nbmax, extract, &ptUnite,
					&numv, certif, date, heure, &nbmes, maxreel, Xc, Yc);
#ifdef DEBUG
			printf ("apres TSRSigRg cr %ld nbmes %ld maxreel %ld fcomment %ld \n",
					cr,nbmes,*maxreel,fcomment);
			printf("Xc %s strlen(Xc) %zu\n",Xc,strlen(Xc));
#endif
			if (cr) {
				char* meser_msg = (char *) ("TSRSigRg - ");
				meser(meser_msg, nomsig, cr, NONFATAL);
				free(ptEntree);
				free(Xc);
				free(Yc);
				UDA_LOG(UDA_LOG_DEBUG, "Returning from 6\n");
				return (cr);
			}
			lind[0] = 1;
			lind[1] = nbmes * fcomment;
		} else
			/* signal "normal"  */
		{
			if (nbmax > 100000)
				printf("What a big signal !! be quiet please data are coming soon ...\n");
			if ((*X = (Double*)calloc(nbmax, sizeof(Double))) == NULL){ 
				char* meser_msg = (char *) ("Alloc9 - ");
				char* space = (char *) (" ");
				meser(meser_msg, space, 1001, FATAL);
			}	
			if ((*Y = (Double*)calloc(nbmax, sizeof(Double))) == NULL){ 
				char* meser_msg = (char *) ("Alloc10 - ");
				char* space = (char *) (" ");
				meser(meser_msg, space, 1001, FATAL);
			}	

			if (l_rang == 1) {
#ifdef DEBUG
				printf ("avant TSRSIGRg rangs %ld %ld nbmax %ld\n", rang[0], rang[1], nbmax);
#endif
				UDA_LOG(UDA_LOG_DEBUG, "%s\n", "Calling TSRSigRg...");
				UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "rang[0]: ", rang[0]);
				UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "rang[1]: ", rang[1]);
				UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "nbmax: ", nbmax);
				UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "extract: ", extract);


				cr = TSRSigRg(nomsig, ptEntree, rang, nbmax, extract, &ptUnite,
						&numv, certif, date, heure, &nbmes, maxreel, (char*)*X,
						(char*)*Y);
#ifdef DEBUG
				printf ("apres TSRSigRg cr %ld nbmes %ld maxreel %ld\n",
						cr,nbmes,*maxreel);
#endif
			} else {
#ifdef DEBUG
				printf ("avant TSRSigX xab %g %g nbmax %ld\n", xab[0], xab[1], nbmax);
#endif
				UDA_LOG(UDA_LOG_DEBUG, "%s\n", "Calling TSRSigX...");
				cr = TSRSigX(nomsig, ptEntree, xab[0], xab[1], nbmax, extract,
						&ptUnite, &numv, certif, date, heure, &nbmes, maxreel,
						(char*)*X, (char*)*Y);
			}
			if (cr) {
				if (l_rang == 1){ 
					char* meser_msg = (char *) ("TSRSigRg - ");
					meser(meser_msg, nomsig, cr, NONFATAL);
				}	
				else{
					char* meser_msg = (char *) ("TSRSigX - ");
					meser(meser_msg, nomsig, cr, NONFATAL);
				}	
				free(ptEntree);
				//free (X);
				//free (Y);
				UDA_LOG(UDA_LOG_DEBUG, "Returning from 7\n");
				return (cr);
			}
			lind[0] = nbmes;
			lind[1] = 1L;
			lind[2] = lind[1];
		}
		switch (rscalaire) {
		case 0:
		case 2:
			break;
		case 1:
			if (scomment == 1)
				for (i = 0; i < nbmes * fcomment; i++)
					Yc[i] = Xc[i];
			else
				for (i = 0; i < nbmes; i++)
					Y[i] = X[i];
			break;
		default:
			break;
		}

	} else if (type == extgType) {
		/* extract = 1; */    /**  ++++  **/
		if (nb_extr2 < 0)
			nbmax = nbcoord[0];
		else
			nbmax = nb_extr2;

		if ((*X = (Double*)calloc(nbmax, sizeof(Double))) == NULL){ 
			char* meser_msg = (char *) ("Alloc9.1 - ");
			char*  space = (char *) (" ");
			meser(meser_msg, space, 1001, FATAL);
		}	
		if ((*Y = (Double*)calloc(nbmax, sizeof(Double))) == NULL){ 
			char* meser_msg = (char *) ("Alloc10.1 - ");
			char*  space = (char *) (" ");
			meser(meser_msg, space, 1001, FATAL);
		}	
		if (l_rang == 1) {
#ifdef DEBUG
			printf ("aavnt TSRXtrRg ind0 %ld ind1 %ld \n", indices[0], indices[1]);
#endif
			UDA_LOG(UDA_LOG_DEBUG, "%s\n", "Calling TSXtrRg...");
			UDA_LOG(UDA_LOG_DEBUG, "aavnt TSRXtrRg ind0 %ld ind1 %ld \n", indices[0], indices[1]);
			UDA_LOG(UDA_LOG_DEBUG, "nomsig=%s\n", nomsig);
			UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "rang[0]: ", rang[0]);
			UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "rang[1]: ", rang[1]);
			UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "nbmax: ", nbmax);
			UDA_LOG(UDA_LOG_DEBUG, "%s %ld\n", "extract: ", extract);

			cr = TSXtrRg(nomsig, ptEntree, indices, rang, nbmax, extract, &ptUnite,
					&numv, certif, date, heure, &nbmes, maxreel, (char*)*X,
					(char*)*Y, (char*)Coord);
			UDA_LOG(UDA_LOG_DEBUG, "ts_rqparm::after calling TSXtrRg, status=%ld\n", cr);
		} else {
#ifdef DEBUG
			printf ("avant TSRXtrX ind0 %ld ind1 %ld \n", indices[0], indices[1]);
#endif
			UDA_LOG(UDA_LOG_DEBUG, "%s\n", "Calling TSXtrX...");
			cr = TSXtrX(nomsig, ptEntree, indices, xab[0], xab[1], nbmax, extract,
					&ptUnite, &numv, certif, date, heure, &nbmes, maxreel,
					(char*)*X, (char*)*Y, (char*)Coord);
		}
		if (cr) {
			if (l_rang == 1){ 
				char* meser_msg = (char *) ("TSXtrRg - ");
				meser(meser_msg, nomsig, cr, NONFATAL);
			}		
			else{ 
				char* meser_msg = (char *) ("TSXtrX - ");
				meser(meser_msg, nomsig, cr, NONFATAL);
			}	
			free(ptEntree);
			//free (X);
			//free (Y);
			UDA_LOG(UDA_LOG_DEBUG, "Returning from 8\n");
			return (cr);
		}
		lind[0] = nbmes;
		lind[1] = 1L;
		lind[2] = 1L;
	}
	if ((ptUnite) && (rscalaire != 1)) {
		//rscaltime = 1;
#if (client == PC)        /* scalaire = valeur temporelle ? */
                float coeff_temps;
		if ((!strncmp (ptUnite->nom, "mcs", 3)) ||
				(!strncmp (ptUnite->nom, "MCS", 3)))
			coeff_temps = 1.0E6;

		if ((!strncmp (ptUnite->nom, "ms", 2)) ||
				(!strncmp (ptUnite->nom, "MS", 2)))
			coeff_temps = 1.0E3;

		if ((!strncmp (ptUnite->nom, "s", 1)) ||
				(!strncmp (ptUnite->nom, "S", 1)))
			coeff_temps = 1.0;

#else
		/*if (!strncasecmp(ptUnite->nom, "mcs", 3))
            coeff_temps = 1.0E6;
        if (!strncasecmp(ptUnite->nom, "ms", 2))
            coeff_temps = 1.0E3;
        if (!strncasecmp(ptUnite->nom, "s", 1))
            coeff_temps = 1.0;*/
#endif
	}
	/* les valeurs  */
	if (scomment) {
		/*if (nouttemp > 0)
        {
            pout[num] = charMat (lind[0], lind[1] , Yc);
            num += 1;
            nouttemp--;
        }*/
	    free(Xc);
		free(Yc);
	} else {
		if (nouttemp > 0) {
#ifdef DEBUG
			printf ("Trying to create val %ld %ld matrix \n", lind[0], lind[1]);
			printf ("rscaltime %ld\n", rscaltime);
#endif
			/*pout[num] = mxCreatefloatMatrix (lind[0], lind[1], mxREAL);
            pr = mxGetPr (pout[num]);
            for (j = 0; j < lind[1]; j++)
            {
                if (rscaltime && rscalaire)
                {
                    for (i = 0; i < lind[0]; i++)
                        pr[i + j * lind[0]] = Y[i * lind[1] + j] / coeff_temps;
                }
                else
                {
                    for (i = 0; i < lind[0]; i++)
                        pr[i + j * lind[0]] = Y[i * lind[1] + j];
                }
            }*/

#ifdef DEBUG
			printf ("fin Trying to create val %ld %ld matrix \n", lind[0], lind[1]);
#endif
			num += 1;
			nouttemp--;
		}
		//free (Y);
	}
	/* les temps  */
	if (scomment) {
		if (nouttemp > 0) {
			//pout[num] = emptyMat ();
			num += 1;
			nouttemp--;
		}
		//free (Xc);
	} else {
#ifdef DEBUG
		printf ("Trying to create temps %ld %ld matrix\n", lind[0], lind[2]);
#endif
		/*		if (nouttemp > 0)
        {
            pout[num] = mxCreatefloatMatrix (lind[0], lind[2], mxREAL);
            pr = mxGetPr (pout[num]);
            if (!absolute) {
                if ( (it0 = tsignitron (&numchoc)) < 0) {
                    printf ("Ignitron non disponible => temps en absolu");
                    printf ("  Ignitron es beleu escondu\n");
                    it0 = 0;
                }
            }

            for (j = 0; j < lind[2]; j++)
            {
                if (absolute)
                {
                    if (rscalaire == 0)
                    {
                        for (i = 0; i < lind[0]; i++)
                            pr[i + j * lind[0]] = X[i * lind[1] + j] / CTPS;
                    }
                    else

		 * signal scalaire : rendu tel quel si valeur != temps

                    {
                        if (rscaltime)
                        {
                            for (i = 0; i < lind[0]; i++)
                                pr[i + j * lind[0]] = X[i * lind[1] + j] / coeff_temps;
                        }
                        else
                        {
                            for (i = 0; i < lind[0]; i++)
                                pr[i + j * lind[0]] = X[i * lind[1] + j];
                        }
                    }
                }
                else
                {
                        it0 = tsignitron(&numchoc);
                    if (rscalaire == 0)
                    {
                        for (i = 0; i < lind[0]; i++)
                            pr[i + j * lind[0]] = (X[i * lind[1] + j] - (float) it0) / CTPS;
                    }
                    else
                    {
                        if (rscaltime)
                        {
                            for (i = 0; i < lind[0]; i++)
                                pr[i + j * lind[0]] = X[i * lind[1] + j] / coeff_temps;
                        }
                        else
                        {
                            for (i = 0; i < lind[0]; i++)
                                pr[i + j * lind[0]] = X[i * lind[1] + j];
                        }
                    }
                }
            }
            num += 1;
            nouttemp--;
        }
        //free (X);*/
	}
#ifdef DEBUG
	printf ("Fin Trying to create temps %ld %ld matrix\n", lind[0], lind[2]);
#endif

	/* les coordonnees si groupe  */
	if (type == homoType) {
		if (nouttemp > 0) {
#ifdef DEBUG
			printf (" Trying to create Coord %ld %ld matrix\n", nbcoord[1], nbcoord[2]);
#endif
			/*pout[num] = mxCreatefloatMatrix (1, (nbcoord[1]  + *
                    (nbcoord[2] > 0 ? nbcoord[2] : 1)), mxREAL);
            pr = mxGetPr (pout[num]);
            for (j = 0; j < lind[1]; j++)
            {
                for (i = 0; i < 1; i++)
                    pr[i + j * 1] = Coord[i * (nbcoord[1] +
                            (nbcoord[2] > 0 ? nbcoord[2] : 0)) + j];
            }
               free((char *) Coord);
            num += 1;
            nouttemp--;*/
#ifdef DEBUG
			printf ("Fin Trying to create Coord %ld %ld matrix\n", nbcoord[1], nbcoord[2]);
#endif
		}

	}
	if ((type == extgType) && (!pansement)) {
		if (nouttemp > 0) {
			/*pout[num] = mxCreatefloatMatrix (1, 1 + (indices[1] != 0 ? 1 : 0), mxREAL);
            pr = mxGetPr (pout[num]);
            pr[0] = Coord[(Longint) 0];
            if (indices[1] != 0)
                pr[1] = Coord[1];*/
			/*    free((char *) Coord); */
			num += 1;
			nouttemp--;
		}
	}
	/* Unites , date , heure , certifs ...   */
	if (nouttemp > 0) {
#ifdef DEBUG
		printf ("Trying create misc  num %ld nouttemp = %ld\n", num, nouttemp);
#endif
		ptd = cmisc;
		for (i = 0; i < LONG_UNITE; i++) {
			if (ptUnite) {
				if (i < strlen(ptUnite->nom))
					*ptd++ = ptUnite->nom[i];
				else
					*ptd++ = ' ';
			} else
				*ptd++ = ' ';
		}
		ptUnite = ptUnite->ps_suivant;

		if (ptUnite) {
			while (ptUnite != NULL) {
				for (i = 0; i < LONG_UNITE; i++) {
					if (i < strlen(ptUnite->nom))
						*ptd++ = ptUnite->nom[(Longint)i];
					else
						*ptd++ = ' ';
				}
				ptUnite = ptUnite->ps_suivant;
			}
		} else {
			for (i = 0; i < LONG_UNITE; i++)
				*ptd++ = ' ';
		}
		*ptd = '\0';

		strcat (cmisc, date);
		strcat (cmisc, heure);
		/****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/
		ptd = cmisc;
		while (*ptd)
			ptd++;

		if (indg > 0)
			sprintf(nomsig_misc, "%s%ld", nomsig, indg);
		else
			strcpy(nomsig_misc, nomsig);

		for (i = 0; i < TAILLE_NOM_DONNEE + 4; i++) {
			if (i < strlen(nomsig_misc))
				*ptd++ = nomsig_misc[i];
			else
				*ptd++ = ' ';
		}
		*ptd = '\0';
		if (cooked_d)
			strcat(cmisc, "T");
		else
			strcat(cmisc, "B");
		/****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/
		nb_certif = 1;
		if (type == homoType)
			nb_certif = nbcoord[1] * ((nbcoord[2] > 0) ? nbcoord[2] : 1);
#ifdef DEBUG
		printf ("Fin ptunite misc %ld nb_certif\n", nb_certif);
#endif

		/*pout[num] = mxCreatefloatMatrix (strlen (cmisc) + 1 + nb_certif + 1, 1, mxREAL);
        pr = mxGetPr (pout[num]);
        pr[0] = (float) nb_certif;
        for (i = 0; i < nb_certif; i++)
            pr[1 + i] = (float) certif[i];
        pr[1 + nb_certif] = (float) numv;
        for (i = 0; i < strlen (cmisc); i++)
            pr[2 + nb_certif + i] = cmisc[(Longint) i];*/

		num += 1;
		nouttemp--;
#ifdef DEBUG
		printf ("Fin misc nouttemp %ld\n", nouttemp);
#endif
	}
	// Libération de la liste chaînée des unités
	// ---------------------------------------------------------------
	// LIBÉRATION COMPLÈTE DE LA LISTE CHAÎNÉE ptUnite (bug vieux de 25 ans)
	// ---------------------------------------------------------------
	if (ptUnite) {
		pS_Unite current = ptUnite;
		while (current) {
			pS_Unite next = current->ps_suivant;   // on garde le suivant avant de libérer

			// Si le nom a été alloué dynamiquement (cas fréquent)
			/*if (current->nom) {
				free(current->nom);
				current->nom = NULL;
			}*/

			// Libération de la structure elle-même
			free(current);

			current = next;
		}
		ptUnite = NULL;  // sécurité
	}
	free(ptEntree);
	UDA_LOG(UDA_LOG_DEBUG, "Returning from 9\n");
	return (cr);

}


void
meser(char* mes1, char* mes2, Longint numer, Longint code)
{
	printf("tsbase : %s%s :", mes1, mes2);

	numer--;

	if ((numer >= 0) && (numer < 1000)) {
		if (numer > 98) {
			numer = numer - 49;
		}
		if (numer > 65) {
			numer = numer - 85;
		}
		printf(" %s\n", err_tslib[numer]);
	} else {
		if ((numer > ERR_MAX) || (numer < 0)) {
			printf(" Erreur TSLIB (bug?) %ld\n", (Longint)numer);
			sigaction(SIGINT, &oldact, NULL);     /* reset previous action */
			printf("Bad news : Contact your System Manager ");
		}
		printf(" %s\n", err_tsmat[(Longint)(numer - 1000)]);
	}
	if (code == FATAL) {
		sigaction(SIGINT, &oldact, NULL);     /* reset previous action */
		printf("Oops Pecaire ... a ben-leu");
	}
}

void getSignalType(char* nomsig, Longint numchoc, Longint* signalType)
{
	ts_donnee* ptDescDon;
	cr = TSDescDon_choc(nomsig, numchoc, 0, &ptDescDon);
	if (cr) {
		char* meser_msg = (char *) ("SDescDon_choc - ");
		meser(meser_msg, nomsig, cr, FATAL);
	}
	if ((ptDescDon->type_donnee >> S_SIMPLE) & 1) {/* signal simple */
		UDA_LOG(UDA_LOG_DEBUG, "--> single signal\n");
		*signalType = 1;
	} else if ((ptDescDon->type_donnee >> D_GHOMO) & 1) { /* groupe */
		UDA_LOG(UDA_LOG_DEBUG, "--> group of  signals\n");
		*signalType = 2;
	} else {
		UDA_LOG(UDA_LOG_DEBUG, "--> Who are you ?\n");
		char* meser_msg = (char *) ("Who are you ?");
		meser(meser_msg, nomsig, 1002, FATAL);
	}
	free (ptDescDon);
}

void getExtractionsCount(char* nomsigp, Longint numchoc, Longint occ, Longint* extractionCount)
{

	Longint certif[MAX_CERTIF];
	Longint indices[2];
	Longint nbcoord[MAX_COORD];
	pS_Entree ptEntree;
	Longint occur = 0, indg = 0;
	char nomsig[TAILLE_NOM_DONNEE];
	char nom_gen[TAILLE_NOM_DONNEE];
	char date[TAILLE_DATE], heure[TAILLE_HEURE];
	Longint rgrp = 0;
	Longint numv;

	ptEntree = (pS_Entree)calloc(1, sizeof(struct S_Entree));
	ptEntree->union_var.lval = numchoc;

	/*****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/
	if (nomsigp[0] == '!') {
		strcpy(nomsigp, &nomsigp[1]);
	}
	/*****++++++++++++++++++++++++++++++++ MAJ Mars 2002 ****************/

	tsparse(nomsigp, nomsig, indices, &rgrp, &occur);

	if (occ) {
		occur = occ;
	}

	if (occur) {
		ptEntree->ps_suivant = (pS_Entree)calloc(1, sizeof(struct S_Entree));
		ptEntree->ps_suivant->union_var.lval = occur;
		ptEntree->ps_suivant->ps_suivant = NULL;
	} else {
		ptEntree->ps_suivant = NULL;
	}

	Longint i;
	for (i = 0; i < MAX_CERTIF; i++)
		certif[i] = 0;

	for (i = 0; i < MAX_COORD; i++)
		nbcoord[i] = 0;
	cr = TSExist_gen(nomsig, ptEntree, nbcoord, &numv, certif, date, heure,
			nom_gen, &indg);

	*extractionCount = nbcoord[1];

}
