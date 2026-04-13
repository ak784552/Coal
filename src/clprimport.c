static  char    sccsid[]="%Z% %M% %I% %E% %U%";
/********************************************************************/
/* <clprimport.c>                                                   */
/********************************************************************/
#include "colmn.h"

extern condList  CLcList;
extern CLPRTBL   *pGLprocTable;
extern CLPRTBL   *pCLprocTable;
extern GlobalCt  *pGlobTable;
extern CLCOMMON  CLcommon;
extern int giOptions[];
extern tdtLruScrHead *tpLruScrHeadImp;
extern tdtLruScrHead *tpLruScrHead;
extern XHASHB *xhpImportReserve;

int cl_pr_ex_import();
static int _imp_cmp_name();
static int _imp_cmp_name_id();
static int _imp_cmp_leaf();
static int _import_reserve(/*scrname*/);

/************************************/
/* cl_process_import				*/
/************************************/
int cl_process_import(y,scrct,leafTop)
condList *y;
ScrPrCT  *scrct;
Leaf     *leafTop;
{
	Leaf *leaf;
	int rc,cno;

	if (scrct == NULL) return ECL_SYSTEM_ERROR;

	rc = 0;
	if (leafTop) leaf = leafTop;
	else if (!(leaf = scrct->TreeTop)) return ECL_SYSTEM_ERROR;

	if (((cno=leaf->cmd.cid)==C_NODE_SCRIPT || cno==C_NODE_IMPORT) &&
		    leaf->leftleaf) leaf = leaf->leftleaf;
	while (leaf && rc==NormalEnd) {
		cno = leaf->cmd.cid;
		if (cno==C_PROC || cno==C_FUNCTION ||  cno == C_CLASS) break;
		else if (cno == C_NODE_DEFINE) leaf = leaf->leftleaf;
		else {
			if (leaf->cmd.cid == C_IMPORT) {
DEBUGOUTL1(100,"[ %s ]",cl_get_pcmd_line(leaf));
				if (CLcommon.dbgopt[0]) {
					cl_debug_mode(leaf,NULL,0);
				}
				rc = cl_pr_ex_import(y,leaf,pGLprocTable->CurScr);
				if (rc) clerrdisp(rc,leaf);
			}
			leaf = leaf->rightleaf;
		}
	}
	return rc;
}

/************************************/
/* _mk_scr_const					*/
/************************************/
ScrConstCt *_mk_scr_const(scrct)
ScrPrCT *scrct;
{
	ScrConstCt *scrconst;

	if (scrconst = (ScrConstCt *)Malloc(sizeof(ScrConstCt))) {
		scrconst->pId = Strdup(scrct->pId);
		/* 2024.3.16 */
		scrconst->ConstCt = NULL;
		scrconst->LeafConstCt = NULL;
		scrconst->NodeLeaf = NULL;
#if 1	/* 2024.12.23 */
		scrconst->pha_vnam=akxs_xhash_new2(0,MAX_VAR_IY,0,sizeof(tdtInfoParm));
#endif
#if 1	/* 2026.4.13 */
		scrconst->pImpId = NULL;
#endif
	}
	return scrconst;
}

/************************************/
/* cl_pr_ex_import					*/
/*	scrct : pGLprocTable->CurScr	*/
/************************************/
int cl_pr_ex_import(y,leaf,scrct)
condList *y;
Leaf    *leaf;
ScrPrCT *scrct;
{
	static char *fmt="***** Import Name ( %s ) Skipped *****";
	static char *_fn_="cl_pr_ex_import";
	int rc,parmnum,namelen,iUSE_MAIN,len,iIMPORTCACHE,iIMPORTTOP,i,iRESERVE,iID;
	char *name,*scrname,*skipped,*p,*import_id,*argv[2],*pImpId;
	tdtInfoParm InfoParm;
	Leaf     *leafw,*leafTop,*leafimp;
	ScrPrCT  Scrprct,*scrprctlru,*scrimp;
	ScrConstCt *myscrconst,*scrconst;
	ConstantCt *pConstCt;
	ParList sc_nam;

	if (!leaf || !scrct) return ECL_SYSTEM_ERROR;

	/* Importファイル名の取り込みとチェック */
	/* 2020.5.13 */
	rc = cl_ex_get_proc_name(leaf->cmd.prmp[0],NULL,&sc_nam);
	if (rc) {
		ERROROUT("cl_pr_ex_import: file name get procedure error.");
		return rc;
	}
	/* 2020.5.13 */
	if (rc = cl_exe_scr_name_check(&sc_nam,NULL)) return rc;
	name =    sc_nam.par;
	namelen = sc_nam.parlen;
	if (!(scrname = cl_set_script_name_extension(name,namelen)))
		return ECL_EX_IMPORT;
	/* 自分自身は、Importしない */
	if (!strcmp(scrname,scrct->pId)) {
		PRDBGOUTL1(1,fmt,scrname);
		return 0;
	}
	/* オプションの取り込みとチェック */
	iIMPORTTOP = pGlobTable->options[5] & 0x01;
	iRESERVE = iUSE_MAIN = 0;
	parmnum = leaf->cmd.prmnum;
	iID = 0;
	import_id = NULL;
	for (i=1;i<parmnum;i++) {
		if (rc=cl_arg_to_char(leaf->cmd.prmp[i],NULL,&InfoParm,"オプション")) {
			ERROROUT("cl_pr_ex_import: option get procedure error.");
			return rc;
		}
		p = InfoParm.pi_data;
		if (iID) {
			if (InfoParm.pi_dlen <= 0) {
				ERROROUT1(FORMAT(42),_fn_);	/* %s: パラメータが足りません。*/
				return ECL_EX_IMPORT;
			}
			if (!(import_id = cl_tmp_const_malloc(InfoParm.pi_dlen+1))) return ECL_MALLOC_ERROR;
			memzcpy(import_id,p,InfoParm.pi_dlen);

printf("%s: import_id=[%s]\n",_fn_,import_id);

		}
		else {
			if (*p == '-') p++;
			if (!stricmp(p,"HEAD")) iIMPORTTOP = 1;
			else if (!stricmp(p,"TAIL")) iIMPORTTOP = 0;
			else if (!stricmp(p,"USE_MAIN")) iUSE_MAIN = 1;
			else if (!stricmp(p,"RESERVE")) iRESERVE = 1;	/* add 2025.11.28 */
			else if (!stricmp(p,"AS")) {
				if (i >= parmnum-1) {
					ERROROUT1(FORMAT(42),_fn_);	/* %s: パラメータが足りません。*/
					return ECL_EX_IMPORT;
				}
				iID = 1;
			}
			else {
					/* cl_pr_ex_import: 不正なオプション[%s]です。 */
				ERROROUT2(FORMAT(561),_fn_,InfoParm.pi_data);
				return ECL_EX_IMPORT;
			}
		}
	}
printf("%s: import_id=%08x\n",_fn_,import_id);
#if 1	/* 2025.11.28 */
	if (iRESERVE) {
		return _import_reserve(scrname);
	}
#endif
	if (iUSE_MAIN) iIMPORTTOP = 1;
	/* 2024.3.16 */
	pConstCt = NULL;
	/****************************************/
	/* 現セッションにImport済みかのチェック */
	/****************************************/
#if 1	/* 2026.4.11 */
	myscrconst = NULL;
	if (!pCLprocTable->pListImport) {
		if (!(pCLprocTable->pListImport=akxs_list_new(0,0))) {
			ERROROUT("cl_pr_ex_import: pListImport malloc error.");
			return ECL_EX_IMPORT;
		}
		/* 呼び出し先から復帰したときに、自分のConstCTを戻せるように
		   自分自身も登録しておく。自分をImportできないようにもできる。 */
		if (!(myscrconst=_mk_scr_const(scrct))) return ECL_SYSTEM_ERROR;
		myscrconst->NodeLeaf = leafw;
		akxs_list_set(pCLprocTable->pListImport,myscrconst);
	}
printf("%s: scrname=[%s]\n",_fn_,scrname);
	skipped = "";
	scrconst = NULL;
	if (!(y->option & D_CLST_OPT_NO_CHK_IMP)) {
#if 1	/* 2026.4.11 */
		rc = _imp_cmp_name_id(pCLprocTable->pListImport,scrname,import_id,&scrconst);
printf("%s: rc=%08x\n",_fn_,rc);
		if (rc & 0x04) {
							/* %s: Import済みスクリプトのId(%s)と一致しません。*/
			if (rc & 0x01) ERROROUT2(FORMAT(692),_fn_,nval(scrconst->pImpId,""));
			else ERROROUT1(FORMAT(365),import_id);	/* %sが重複しています。*/
			return ECL_EX_IMPORT;
		}
		else if (rc & 0x01) skipped = "Skipped ";
#else
		if (akxs_list_srch(pCLprocTable->pListImport,imp_nam,_imp_cmp_name,0)) {
			skipped = "Skipped ";
		}
#endif
	}
	PRDBGOUTL2(1,"***** Current Session Import Name ( %s ) %s*****",scrname,skipped);
	/* import済みのときは、ここでリターンする */
	if (*skipped) return 0;
#endif
	/********************************************/
	/* セッション間領域にImport済みかのチェック */
	/********************************************/
	skipped = "";
	/* 2024.3.2 */
	if (!pGLprocTable->pListImport) {
		if (!(pGLprocTable->pListImport=akxs_list_new(0,0))) {
			ERROROUT("cl_pr_ex_import: pListImport malloc error.");
			return ECL_EX_IMPORT;
		}
		leafw = cl_make_node_leaf(pConstCt,C_NODE_SCRIPT,scrct->pId);
		leafTop  = scrct->TreeTop;
		scrct->TreeTop = leafw;
		scrct->sc_pFlag |= D_LEAF_IMPORTMODE;
		leafw->leftleaf = leafTop;
		leafw->pFlag = scrct->sc_pFlag;

		/* 呼び出し先から復帰したときに、自分のConstCTを戻せるように
		   自分自身も登録しておく。自分をImportできないようにもできる。 */
		if (!myscrconst) {
			if (!(myscrconst=_mk_scr_const(scrct))) return ECL_SYSTEM_ERROR;
			myscrconst->NodeLeaf = leafw;
		}
/*
printf("cl_pr_ex_import:1 leafw=%08x\n",leafw);
*/
	/* 2024.3.2 */
		akxs_list_set(pGLprocTable->pListImport,myscrconst);
	}
	if (!(y->option & D_CLST_OPT_NO_CHK_IMP)) {
		/* 2026.4.11 */
		rc = _imp_cmp_name_id(pGLprocTable->pListImport,scrname,import_id,&scrconst);
		if (rc & 0x04) {
							/* %s: Import済みスクリプトのId(%s)と一致しません。*/
			if (rc & 0x01) ERROROUT2(FORMAT(692),_fn_,nval(scrconst->pImpId,""));
			else ERROROUT1(FORMAT(365),import_id);	/* %sが重複しています。*/
			return ECL_EX_IMPORT;
		}
		else if (rc & 0x01) skipped = "Skipped ";
	}
	PRDBGOUTL2(1,"***** Global Session Import Name ( %s ) %s*****",scrname,skipped);
#if 0	/* 2026.4.12 */
	/* import済みのときは、ここでリターンする */
	if (*skipped) return 0;
#endif
	/* Import済みでもキャッシュから消えていることもある */
	/* 2024.3.2 */
	if (scrprctlru=cl_lru_scr_src(tpLruScrHeadImp,scrname)) {	/* キャッシュにあるか調べる */
DEBUGOUTL1(0,"cl_pr_ex_import: %s is found in cache",scrname);
		scrimp = &Scrprct;
		scrimp->ConstCt = NULL;
		scrimp->TreeTop = scrprctlru->TreeTop;
		scrimp->LeafConstCt = scrprctlru->LeafConstCt;
/*
printf("cl_pr_ex_import: LeafConstCt=%08x\n",scrimp->LeafConstCt);
*/
		scrimp->pId = scrprctlru->pId;
		iIMPORTCACHE = D_LEAF_CACHED;
	}
	else {
		scrimp = cl_mk_scr_and_reg(y,tpLruScrHeadImp,&Scrprct,scrname);
		if (!scrimp) return ECL_SYSTEM_ERROR;
		if (!cl_mk_lk_make(scrimp)) return ECL_SYSTEM_ERROR;
		iIMPORTCACHE = scrimp->sc_pFlag & D_LEAF_CACHED;
printf("%s: import cached scrimp=%08x iIMPORTCACHE=%08x\n",_fn_,scrimp,iIMPORTCACHE);
printf("%s: pha_vnam=%08x\n",_fn_,scrimp->Vary->pha_vnam);
	/* 2024.3.2 */
	}
#if 1	/* 2026.4.11 */
	if (!scrconst) {
		if (!(scrconst=_mk_scr_const(scrimp))) return ECL_SYSTEM_ERROR;
		if (import_id) p = Strdup(import_id);
		else p = NULL;
		scrconst->pImpId = p;
		akxs_list_set(pGLprocTable->pListImport,scrconst);
	}
	akxs_list_set(pCLprocTable->pListImport,scrconst);
#endif
	leafimp = scrimp->TreeTop;
	/* ImportしたスクリプトのNodeLeafは、Importしたスクリプトで使用しているので
	   自分用のNodeLeafを作成する */
	leafw = cl_make_node_leaf(pConstCt,C_NODE_IMPORT,scrname);
	leafw->leftleaf = leafimp;
	leafw->pFlag = iIMPORTCACHE;
	scrconst->NodeLeaf = leafw;
/*
printf("cl_pr_ex_import:2 leafw=%08x\n",leafw);
*/
	if (cl_search_proc(leafw,"main")) {
				/* %s: Importファイル[%s]内にmainがあります。 */
		ERROROUT2(FORMAT(562),_fn_,scrname);
		if (!iUSE_MAIN) {
					/* %s: mainを無効にしました。 */;
			ERROROUT1(FORMAT(563),_fn_);
			leafw->pFlag |= D_LEAF_INEFFECTIVE;
		}
	}
	if (iIMPORTTOP) {
		/* ImportしたスクリプトのTreeは先頭に挿入する */
		leafTop  = scrct->TreeTop;
		scrct->TreeTop = leafw;
		leafw->rightleaf = leafTop;
		leafTop  = NULL;
	}
	else {
		/* ImportしたスクリプトのTreeは最後に追加する */
		leafTop = leafw;
		leafw = scrct->TreeTop;
		while (leafw->rightleaf) {
			leafw = leafw->rightleaf;
		}
		leafw->rightleaf = leafTop;
	}
/**********
	ImportしたtreeにあるONとDEFINEは、後でまとめて実行する。
	Import文は、treeの先頭から、PROCまたはFUNCTIONの前にあるもののみ実行する。
	これは、Importしているスクリプトがキャッシュされているときは、Importを実行
	しなくても良いようにするためである。
	if (rc = cl_process_on(&Scrprct)) {
		ERROROUT("Error occured ON condition Process");
	}
	else if (rc = cl_process_define(&Scrprct)) {
		ERROROUT("Error occured Define Process");
	}
	else
************/
#if 1	/* 2026.4.11 */
	if (leafimp) {

printf("%s: define import leaf scrimp=%08x\n",_fn_,scrimp);

		argv[0] = "";
		argv[1] = NULL;
		scrimp->sc_pFlag2 |= D_LEAF_IMPORTMODE;	/* add 2024.2.29 */
		/* 2021.2.20 */
		if ((rc=_set_node_path(pGLprocTable->CurScr,leafimp,argv,NULL)) < 0) return -1;
		pCLprocTable->imp_pha_vnam = scrimp->Vary->pha_vnam;
		if (rc = cl_process_define(scrimp,leafimp)) {
			ERROROUT1("%s: Error occured GLOBAL Define Process",_fn_);
			return -1;
		}
	}
	scrimp->sc_pFlag2 &= ~D_LEAF_IMPORTMODE;	/* add 2024.2.29 */

printf("%s: define script leaf\n",_fn_);

#endif
	if (rc = cl_process_import(y,scrct,leafTop)) {
		ERROROUT1("Error occured Import Process rc=%d",rc);
	}

	return rc;
}

/************************************/
/* _imp_cmp_name					*/
/************************************/
static int _imp_cmp_name(scrname,scrconst)
ScrConstCt *scrconst;
char *scrname;
{
	return strcmp(scrconst->pId,scrname);
}

/************************************/
/* _imp_cmp_name_id					*/
/* ppImpId : scrname ありのときのpImpIdを返す */
/* rc : 0x01 : scrname あり			*/
/*		0x02 : imp_id あり,scrnameありと同じ位置 */
/*		0x04 : imp_id あり,scrnameありと異なる位置 */
/************************************/
static int _imp_cmp_name_id(pCt,scrname,imp_id,pscrconst)
tdtRbCtl *pCt;
char *scrname,*imp_id;
ScrConstCt **pscrconst;
{
	ScrConstCt *scrconst,*p;
	int rc,iNAM,iSAME_IMPID,k,iIMPID;

	iIMPID = k = iNAM = iSAME_IMPID = 0;
	p = NULL;
	if (pscrconst) *pscrconst = NULL;
	akxs_rb_read(pCt,0);
	while (scrconst=(ScrConstCt *)akxs_rb_read(pCt,1)) {
		k++;
		if (!strcmp(scrname,scrconst->pId)) {
			iNAM = k;
			p = scrconst;
		}
		if (imp_id && scrconst->pImpId) {
			if (!strcmp(imp_id,scrconst->pImpId)) {
				iSAME_IMPID = k;
			}
		}
		else if (iNAM) break;
	}
	rc = 0;
	if (iSAME_IMPID) iIMPID = 4;
	if (iNAM) {
		rc |= 1;
		if (iNAM == iSAME_IMPID) iIMPID = 2;
		if (pscrconst) *pscrconst = p;
	}
printf("_imp_cmp_name_id: rc=%d iIMPID=%d\n",rc,iIMPID);
	return rc | iIMPID;
}

/************************************/
/* _imp_cmp_leaf					*/
/************************************/
static int _imp_cmp_leaf(nodeleaf,scrconst)
ScrConstCt *scrconst;
Leaf       *nodeleaf;
{
	return (scrconst->NodeLeaf == nodeleaf) ? 0 : -1;
}

/************************************/
/* cl_get_scr_const_ct				*/
/************************************/
ScrConstCt *cl_get_scr_const_ct(scrct,nodeleaf)
ScrPrCT *scrct;
Leaf    *nodeleaf;
{
	tdtRbCtl *pCt;
	ScrConstCt *scrconst;

DEBUGOUTL2(120,"cl_get_scr_const_ct: called scrct=%08x,nodeleaf=%08x",scrct,nodeleaf);
/*
if (nodeleaf) printf("cl_get_scr_const_ct: called scrct=%08x,nodeleaf=%08x\n",scrct,nodeleaf);
*/
	scrconst = NULL;
	if (scrct && nodeleaf) {
		/* 2024.3.2 */
		if (pCt=pGLprocTable->pListImport) {
			if (akxs_list_srch(pCt,nodeleaf,_imp_cmp_leaf,0)) {
				akxs_list_read(pCt,-1,&scrconst);

DEBUGOUTL1(161,"cl_get_scr_const_ct: found scrconst=%08x",scrconst);
/*
printf("cl_get_scr_const_ct: found scrconst=%08x\n",scrconst);
*/
			}
		}
	}
	return scrconst;
}

/************************************/
/* cl_set_scr_const_ct				*/
/************************************/
int cl_set_scr_const_ct(scrct,nodeleaf,impscrct)
ScrPrCT *scrct,*impscrct;
Leaf    *nodeleaf;
{
	tdtRbCtl *pCt;
	ScrConstCt *scrconst;
	int rc;

DEBUGOUTL3(120,"cl_set_scr_const_ct: called scrct=%08x,nodeleaf=%08x impscrct=%08x",scrct,nodeleaf,impscrct);
/*
if (nodeleaf) printf("cl_set_scr_const_ct: called scrct=%08x,nodeleaf=%08x impscrct=%08x\n",scrct,nodeleaf,impscrct);
*/
	rc = 0;
	if (scrct && nodeleaf) {
		/* 2021.8.18 */
		/* 2024.3.2 */
		if (!impscrct) return -1;
		if (scrconst = cl_get_scr_const_ct(impscrct,nodeleaf)) {
			scrct->ConstCt     = scrconst->ConstCt;
			scrct->LeafConstCt = scrconst->LeafConstCt;

DEBUGOUTL1(120,"cl_set_scr_const_ct: LeafConstCt=%08x",scrconst->LeafConstCt);
/*
printf("cl_set_scr_const_ct: LeafConstCt=%08x\n",scrconst->LeafConstCt);
*/
			rc = 1;
		}
	}
	return rc;
}
#if 1	/* 2025.11.29 */
/************************************/
/* cl_sel_import					*/
/************************************/
static int _import_reserve(scrname)
char *scrname;
{
	static char *_fn_="cl_import_reserve";
	int rc,i,len,pos1,pos2,ih;
	char *p,*pp,dir[256];
	FILE *fp;
/*
printf("%s: scrname=[%s]\n",_fn_,scrname);
*/
	if (!xhpImportReserve) {
		if (!(xhpImportReserve = akxs_xhash_new2(0,10,7,sizeof(char *)))) return -1;
	}
	rc = 0;
	if (fp = cl_lex_file_open(scrname,dir,"cl_pr_ex_import")) {
		p = NULL;
		for (i=0;i<2;i++) {
			len = akxa_get_line(dir,sizeof(dir),fp,0x01);
/*
printf("%s: len=%d dir=[%s]\n",_fn_,len,dir);
*/
			if (len < 0) {
				fclose(fp);
				break;
			}
			pos1 = akxnskipto(dir,len," ");
/*
printf("%s: pos1=%d\n",_fn_,pos1);
*/
			if (pos1 < len) {
				if (!akxmemcmplen(dir,pos1,"//import",8,1)) {
					pp = dir + pos1;
					len -= pos1;
					pos2 = akxnskipin(pp,len," ");
/*
printf("%s: pos2=%d len=%d pp=[%s]\n",_fn_,pos2,len,pp);
*/
					if (pos2 < len) {
						if (!(p=Strdup(pp+pos2))) return ECL_MALLOC_ERROR;
/*
printf("%s: p=[%s]\n",_fn_,p);
*/
					}
					break;
				}
			}
		}
		ih = akxs_xhash2(xhpImportReserve,'S',scrname,&p);
/*
printf("%s: akxs_xhash2 ih=%d\n",_fn_,ih);
*/
		if (ih < 0) rc = ih;
		else if (!ih) rc = -1;
	}
	else {
		ERROROUT2(FORMAT(49),_fn_,dir);	/* %s: *** [%s] Open Error. Check up SCRIPTPATH */
		rc = ECL_SCRIPT_ERROR;
	}
	return rc;
}

/************************************/
/* cl_sel_import					*/
/************************************/
int cl_sel_import(name,kind)
char *name;
int kind;
{
	condList *y;
	Leaf tleaf,*leaf;
	ScrPrCT *scrct;
	parmList tPrmlist,*Prmp[2];
	int i,rc,ih,iMAX;
	char *p,*onam,*pp,*pkey,**pdat;

	rc = 0;
	/* 2025.12.31 */
	if (akxs_xhash(xhpImportReserve,'T',NULL) <= 0) return 0;
	iMAX = xhpImportReserve->xha_xhix;
	i = 0;
	for (;;) {
		i = akxs_xhash_next_i(iMAX,xhpImportReserve,i);
		if (i == AKX_HASH_NEXT_BREAK) break;
		xhpImportReserve->xha_xhix = i;
		if ((ih = akxs_xhash2(xhpImportReserve,'P',&pkey,&pdat)) < 0) {
			rc = ih;
			break;
		}
		else if (ih > 0) {
			p = (char *)*pdat;
/*
printf("cl_sel_import: pkey=[%s] p=[%s]\n",pkey,p);
*/
			if (instr(p,name) > 0) {
				y = &CLcList;
				scrct = cl_search_scr_ct();
				leaf = &tleaf;
				memset(leaf,0,sizeof(Leaf));
				tleaf.cmd.cid    = C_IMPORT;
				tleaf.cmd.prmnum = 1;
				tleaf.cmd.prmp = Prmp;
				tleaf.cmd.prmp[0]= &tPrmlist;
				tPrmlist.opt     = D_GX_OPT_NO_USE_OBJ;
				if (kind) onam = "FUNC";
				else onam = "PROC";
				pp = stradd5("D_",onam,"_",name,NULL);
/*
printf("cl_sel_import: name=[%s] kind=%d pp=[%s]\n",name,kind,pp);
*/
				ih = cl_set_main_define(pp,NULL,'S');
				tPrmlist.prmlen = strlen(pkey);
				tPrmlist.prp    = pkey;
				y->option |= D_CLST_OPT_NO_CHK_IMP;
				rc = cl_pr_ex_import(y,leaf,scrct);
				y->option &= ~D_CLST_OPT_NO_CHK_IMP;
				ih = cl_set_main_define(pp,NULL,'D');
				break;
			}
		}
	}
	return rc;
}
#endif
