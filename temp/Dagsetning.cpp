#include "dagsetning.h"


//#ifndef _WINDOWS_
//	#include <windows.h>
//#endif

#include <stdio.h>

CDagsetning::CDagsetning(void)
: m_iDagur(0)
, m_iManudur(0)
, m_iAr(0)
{
	m_cstr="";
}

// �etta fall skal bara kalla � �r constructor.  
void CDagsetning::initilize(void)
{

}
CDagsetning::~CDagsetning(void)
{

}
//Meiga paktar vera -1 �ri� 2090 ? 
int CDagsetning::Paktar(unsigned int uiAr)
{
	/*regla sem gildir fyrir n�ja st�l
	Taki� �rtali� og deili� � �a� me� 19. 
	Afganginn skal margfalda me� 11, leggja �ar vi� 8, 
	draga fr� aldatali� (fyrir 1970 er aldatali� 19), leggja s��an vi� fj�r�ung aldatalsins (a� afgangi slepptum) og b�ta loks vi� �eirri t�lu sem f�st �egar aldatali� er margfalda� me� 8, 13 b�tt vi� og deilt � me� 25 (afgangi sleppt). � t�luna sem �� kemur �t er deilt me� 30, og er afgangurinn �� paktarnir. 
	D�mi: 1970. Vi� deilum 19 upp � 1970, f�um 13 � afgang, 
	margf�ldum �� t�lu me� 11 og f�um 143. �ar vi� b�tast 8, sem gefa 151. 
	Vi� dr�gum fr� aldatali� 19 og h�fum �� eftir 132. S��an leggst vi� fj�r�ungurinn af 19, 
	sem er 4, og f�st �� 136. Loks t�kum vi� 19, margf�ldum me� 8 (= 152), 
	b�tum 13 vi� (= 165) og deilum me� 25. �tkoman �ar er 6 sem vi� leggjum n� vi� 136 og f�um 142. 
	� �� t�lu deilum vi� me� 30. Afgangur ver�ur 22, og eru �a� paktar �rsins*/

	/*Fyrir gamla st�l gildir styttri regla: 
	Taki� �rtali� og deili� � �a� me� 19. 
	Afganginn skal margfalda me� 11 og leggja 8 vi�. 
	S��an er deilt � �tkomuna me� 30, og er afgangurinn �� paktarnir*/
	int iRest, iOld, iPaktar, iAldatal;
	iAldatal=uiAr/100;
	iRest=uiAr % 19;
	iRest*=11;
	iRest+=8;
	iRest-=iAldatal;
	iRest+=iAldatal/4;
	iOld=(((iAldatal*8)+13)/25);
	iRest+=iOld;
	iPaktar=iRest%30;

	return iPaktar;
}

int CDagsetning::Gyllitala(unsigned int uiAr)
{
	return 1+(uiAr % 19);
}

//skilar m�nu�i sem p�skadagur er � � �v� �ri sem iAr segir til um.
//ef iOutDagur er 0 �� er ekkert gert vi� �� breytu. annars
//skilar falli� m�na�adegi � �essa breytu
//P�skar ............. 22. mars til 25. apr�l 
int CDagsetning::DagurPaskar(int iAr, int *iOutDagur)
{	/*Besta reiknireglan til a� finna p�ska � n�ja st�l mun vera s� sem birtist nafnlaust � breska t�maritinu Nature �ri� 1876. Reglan er �essi: 

       Deili� � �rtali� me� 19 og kalli� afganginn a. 
       Deili� � �rtali� me� 100, kalla� deildina b og afganginn c. 
       Deili� � b me� 4, kalli� deildina d og afganginn e. 
       Deili� � b + 8 me� 25 og kalli� deildina f. 
       Deili� � b �f + 1 me� 3 og kalli� deildina g. 
       Deili� � 19a + b � d � g + 15 me� 30 og kalli� afganginn h. 
       Deili� � c me� 4 og kalli� deildina i og afganginn j. 
       Deili� � 32 + 2e + 2i � h � j me� 7 og kalli� afganginn k. 
       Deili� � a + 11h+22k me� 451 og kalli� deildina m. 
       Deili� � h + k � 7m + 114 me� 31, kalli� deildina n og afganginn p. 
		�� er n m�nu�urinn sem p�skadagur fellur �, og p + 1 er m�na�ardagurinn. 

Ef vi� t�kum 1971 sem d�mi f�um vi� a = 14, b = 19, c = 71, d = 4, e = 3, f = 1, g = 6, h = 20, i = 17, j = 3, k = 0, m = 0, n = 4, p = 10. �� eru p�skarnir � 4. m�nu�i �rsins og dagurinn er 10 + 1, �. e. 11. apr�l. 
*/
		int a,b,c,d,e,f,g,h,i,j,k,m,n,p;
		a=iAr % 19;					//Deili� � �rtali� me� 19 og kalli� afganginn a. 
        b=iAr/100;					//Deili� � �rtali� me� 100, kalla� deildina b og afganginn c. 
		c=iAr%100;
		d=b/4;						//Deili� � b me� 4, kalli� deildina d og afganginn e. 
		e=b%4;
		f=(b+8)/25;					//Deili� � b + 8 me� 25 og kalli� deildina f. 
		g=(b-f+1)/3;				//Deili� � b �f + 1 me� 3 og kalli� deildina g. 
        h=((19*a)+b-d-g+15)%30;		//Deili� � 19a + b � d � g + 15 me� 30 og kalli� afganginn h. 
        i=c/4;						//Deili� � c me� 4 og kalli� deildina i og afganginn j. 
		j=c%4;
        k=(32+(2*e)+(2*i)-h-j)%7;	//Deili� � 32 + 2e + 2i � h � j me� 7 og kalli� afganginn k. 
		m=(a+(11*h)+(22*k))/451;	//Deili� � a + 11h+22k me� 451 og kalli� deildina m. 
        n=(h+k-(7*m)+114)/31;		//Deili� � h + k � 7m + 114 me� 31, kalli� deildina n og afganginn p. 
		p=(h+k-(7*m)+114)%31;
		//�� er n m�nu�urinn sem p�skadagur fellur �, og p + 1 er m�na�ardagurinn. 
		if (iOutDagur)
			*iOutDagur=p+1;
		return n;
}


// skilar nafni m�na�ar � l�gst�fum. Ef usManudur er NULL �� reynir falli� a� skila m�nu�i �essarar dagsetningar
// Skilagildi� ber a� afrita strax �v� �ll f�ll � klasanum sem skila streng �essa s�mu breytu.
// not thread save
char * CDagsetning::NafnManadar(unsigned short usManudur)
{
	if (!usManudur ||(usManudur>12 || usManudur<1))
		return 0;
//lock the temp variable
	switch(usManudur)
	{
		case 1 : m_cstr="jan�ar";	break;
		case 2 : m_cstr="febr�ar";	break;
		case 3 : m_cstr="mars";		break;
		case 4 : m_cstr="apr�l";	break;
		case 5 : m_cstr="ma�";		break;
		case 6 : m_cstr="j�n�";		break;
		case 7 : m_cstr="j�l�";		break;
		case 8 : m_cstr="�g�st";	break;
		case 9 : m_cstr="september";break;
		case 10: m_cstr="okt�ber";	break;
		case 11: m_cstr="n�vember";	break;
		case 12: m_cstr="desember";	break;
	}
	return m_cstr.getString();
}
// skilar n�meri �ess j�lasveins sem kemur � desember
// 
unsigned short CDagsetning::erJolasveinn(int iManudur, int iDagur)
{
	if (iManudur!=12 || iDagur>24 || iDagur<12)
		return 0;
	return iDagur-11;
}
// skilar nafni j�lasveins. 
// Ef usJolasveinn er NULL e�a ef gild� <1 e�a >13 �� skilar falli� 0
// L�gleg gildi eru 1,2,3,4,5,6,7,8,9,10,11,12 og 13.
// Skilagildi� ber a� afrita strax �v� �ll f�ll � klasanum sem skila streng �essa s�mu breytu.
// not thread save
// Nota�u falli� me� erJolasveinn sem skilar n�meri j�lasveins �tfr� dagsetningu
char * CDagsetning::NafnJolasveins(unsigned short usJolasveinn)
{
	usJolasveinn+=11;
	if (!usJolasveinn || usJolasveinn>24 || usJolasveinn<12)
		return 0;
	switch(usJolasveinn)
	{
		/* 1*/case 12: m_cstr="Stekkjastaur";	break;
		/* 2*/case 13: m_cstr="Giljagaur";		break;
		/* 3*/case 14: m_cstr="St�fur";			break;
		/* 4*/case 15: m_cstr="�v�rusleikir";	break;
		/* 5*/case 16: m_cstr="Pottaskefill";	break;
		/* 6*/case 17: m_cstr="Askasleikir";	break;
		/* 7*/case 18: m_cstr="Hur�askellir";	break;
		/* 8*/case 19: m_cstr="Skyrjarmur";		break;
		/* 9*/case 20: m_cstr="Bj�gnakr�kir";	break;
		/*10*/case 21: m_cstr="Gluggag�gir";	break;
		/*11*/case 22: m_cstr="G�tta�efur";		break;
		/*12*/case 23: m_cstr="Ketkr�kur";		break;
		/*13*/case 24: m_cstr="Kertasn�kir";	break;
	}
	return m_cstr.getString();
}
// skilar v�su j�lasveins. 
// Ef usJolasveinn er NULL e�a ef gild� <1 e�a >13 �� skilar falli� 0
// L�gleg gildi eru 1,2,3,4,5,6,7,8,9,10,11,12 og 13.
// Skilagildi� ber a� afrita strax �v� �ll f�ll � klasanum sem skila streng �essa s�mu breytu.
// not thread save
// Nota�u falli� me� erJolasveinn sem skilar n�meri j�lasveins �tfr� dagsetningu
char * CDagsetning::VisaJolasveins(unsigned short usJolasveinn)
{
	usJolasveinn+=11;
	if (!usJolasveinn || usJolasveinn>24 || usJolasveinn<12)
		return 0;
	switch(usJolasveinn)
	{									
		/* 1*/case 12: m_cstr="Stekkjastaur kom fyrstur,\nstinnur eins og tr�.\nHann lauma�ist � fj�rh�sin\nog l�k � b�ndans f�.\n\nHann vildi sj�ga �rnar,\n- �� var �eim ekki um sel,\n�v� greyi� haf�i staurf�tur,\n- �a� gekk n� ekki vel.";	break;
		/* 2*/case 13: m_cstr="Giljagaur var annar,\nme� gr�a hausinn sinn.\n- Hann skrei� ofan �r gili\nog skauzt � fj�si� inn.\n\nHann faldi sig � b�sunum\nog fro�unni stal,\nme�an fj�sakonan �tti\nvi� fj�samanninn tal.";break;
		/* 3*/case 14: m_cstr="St�fur h�t s� �ri�ji\nstubburinn s�.\nHann kr�kti s�r � p�nnu,\n�egar kostur var �.\n\nHann hlj�p me� hana � burtu\nog hirti agnirnar,\nsem brunnu stundum fastar\nvi� barminn h�r og �ar.";		break;
		/* 4*/case 15: m_cstr="S� fj�r�i, �v�rusleikir,\nvar fjarskalega mj�r.\nOg �sk�p var� hann gla�ur,\n�egar eldabuskan f�r.\n\n�� �aut hann eins og elding\nog �v�runa greip,\nog h�lt me� b��um h�ndum,\n�v� h�n var stundum sleip.";	break;
		/* 5*/case 16: m_cstr="S� fimmti, Pottaskefill,\nvar skr�ti� kuldastr�.\n- �egar b�rnin fengu sk�fir\nhann bar�i dyrnar �.\n\n�au ruku upp, til a� g� a�\nhvort gestur v�ri � fer�.\n�� fl�tti' ann s�r a� pottinum\nog f�kk s�r g��an ver�.";	break;
		/* 6*/case 17: m_cstr="S� sj�tti, Askasleikir,\nvar alveg d�malaus. -\nHann fram undan r�munum\nrak sinn lj�ta haus.\n\n�egar f�lki� setti askana\nfyrir k�tt og hund,\nhann slunginn var a� n� �eim\nog sleikja � �msa lund.";	break;
		/* 7*/case 18: m_cstr="Sj�undi var Hur�askellir,\n- s� var nokku� kl�r,\nef f�lki� vildi � r�kkrinu\nf� s�r v�nan d�r.\n\nHann var ekki s�rlega\nhnugginn yfir �v�,\n�� harkalega marra�i\nhj�runum �.";	break;
		/* 8*/case 19: m_cstr="Skyrjarmur, s� �ttundi,\nvar skelfilegt naut.\nHann hlemminn o�n af s�num\nme� hnefanum braut.\n\nSvo h�ma�i hann � sig\nog yfir matnum gein,\nunz st�� hann � bl�stri\nog stundi og hrein.";	break;
		/* 9*/case 20: m_cstr="N�undi var Bj�gnakr�kir,\nbr�g��ttur og snar.\nHann hentist upp � rj�frin\nog hnupla�i �ar.\n\n� eldh�sbita sat hann\n� s�ti og reyk\nog �t �ar hangi� bj�ga,\nsem engan sveik.";	break;
		/*10*/case 21: m_cstr="T�undi var Gluggag�gir,\ngr�lyndur mann,\nsem lauma�ist � skj�inn\nog leit inn um hann.\n\nEf eitthva� var �ar inni\n�litlegt a� sj�,\nhann oftast n�r seinna\n� �a� reyndi a� n�.";	break;
		/*11*/case 22: m_cstr="Ellefti var G�tta�efur,\n- aldrei f�kk s� kvef,\nog haf�i �� svo hl�legt\nog heljarst�rt nef.\n\nHann ilm af laufabrau�i\nupp � hei�ar fann,\nog l�ttur, eins og reykur,\n� lyktina rann.";	break;
		/*12*/case 23: m_cstr="Ketkr�kur, s� t�lfti,\nkunni � �msu lag. -\nHann �ramma�i � sveitina\n� �orl�ksmessudag.\n\nHann kr�kti s�r � tutlu,\n�egar kostur var �.\nEn stundum reyndist stuttur\nstauturinn hans ��.";	break;
		/*13*/case 24: m_cstr="�rett�ndi var Kertasn�kir,\n- �� var t��in k�ld,\nef ekki kom hann s��astur\n� a�fangadagskv�ld.\n\nHann elti litlu b�rnin\nsem brostu, gl�� og f�n,\nog tr�tlu�u um b�inn\nme� t�lgarkertin s�n.";	break;
	}
	return m_cstr.getString();
}
// Skilar nafni vikudags � l�gst�fum. 
// Skilagildi fallsins ber a� afrita strax �v� �ll f�ll � klasanum sem skila streng nota sama minnish�lf(breytu).
// sunnudagur=1, m�nudagur=2, �ri�judagur=3 o.s.fr.
// ef bLongName er 0 �� skilar falli� �riggja stafa n�fnum eins og:
// sun, m�n=2, �ri=3 o.s.fr.
// not thread save

char * CDagsetning::NafnVikudags(unsigned short usVikudagur, bool bLongName)
{
	if (usVikudagur>6)
		return 0;

	switch(usVikudagur)
	{
		case 0 : m_cstr="sunnudagur";	break;
		case 1 : m_cstr="m�nudagur";	break;
		case 2 : m_cstr="�ri�judagur";	break;
		case 3 : m_cstr="mi�vikudagur";	break;
		case 4 : m_cstr="fimmtudagur";	break;
		case 5 : m_cstr="f�studagur";	break;
		case 6 : m_cstr="laugardagur";	break;
	}
	if (!bLongName)
		m_cstr.left(3);

	return m_cstr.getString();
}

//     
//  Athugar hvort vi�komandi dagsetning er h�t��ardagur e�a hefur textastreng.  
//  -Ef skilagildi� er >  0 �� er vi�komandi dagur h�t��ardagur.
//  -Ef skilagildi� er == 0 �� er vi�komandi dagur EKKI h�t��ardagur.
//  -ef skilagildi� er <  0 �� er vi�komandi dagur ekki h�t��ardagur en
//   �a� er einhver textastrengur tengdur �essari dagsetningu.
//   T.d. "b�ndadagur".
//  Skilgreining h�t��ardags: 
//	   Dagur sem er l�gbundinn fr�dagur en �� ekki helgidagur.  
//     �� a� fr� s� l�gbo�i� hluta dagsins �� er hann me�h�ndla�ur sem fr�dagur.  
//     D�mi: A�fangadagur er fr�dagur �� a� l�gbundi� fr� er a�eins eftir 12:00 �ann dag.
//
//  Nota m� skylagildi �essa falls til �ess a� setja inn � falli� NafnHatidardags.
//  D�mi um notkun: 
//		CDagsetning cDags;
//		m_cstring str;
//  	int i=cDags.erHatid(2004, 4, 11);
//  	if (i!=0)
//  		str=cDags.NafnHatidardags(i);
//      N� inniheldur str textann "p�skadagur" 
//
//   erHatid skilar h�sta gild 18 og l�gsta gild -16
//   ef �� �tlar a� �tf�ra �etta fall � erf�um klasa �� er 
//   �ruggast a� nota t�lur sem eru minni en -99 og st�rri en 99
//   �egar �� ert a� v�sa � a�ra h�t�ardaga sem �� vilt sj�lfur tiltaka.

int CDagsetning::erHatid(int iAr, int iManudur, int iDagur)
{
	int iPaskaMan,iPaskarDag, iVikudagur, m, d;

	if (12==iManudur && 23==iDagur)				return -14;//�orl�ksmessa
	if (12==iManudur && 24==iDagur)				return 2;//a�fangadagur
	if (12==iManudur && 25==iDagur)				return 3;//J�ladagur
	if (12==iManudur && 26==iDagur)				return 9;//Annar � j�lum
	if ( 5==iManudur &&  1==iDagur)				return 10;//verkal��sdagurinn
	if ( 1==iManudur &&  1==iDagur)				return 7;//n��rsdagur
	if ( 1==iManudur &&  6==iDagur)				return -13;//�rett�ndinn
	if (12==iManudur && 31==iDagur)				return 8;//gaml�rsdagur
	if (6==iManudur && 17==iDagur)				return 14;//�j��h�t��ardagurinn

	iPaskaMan=DagurPaskar(iAr, &iPaskarDag);
	if (iPaskaMan==iManudur && iPaskarDag==iDagur)	return 1;//p�skadagur
	if (iManudur<=iPaskaMan)
	{	
		DagurFostudagurinnLangi(iAr,&m,&d);	if (m==iManudur && d==iDagur) return 11;//f�studagurinn langi
		DagurSkirdagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return 12;//DagurSkirdagur
		DagurAnnar_i_Paskum(iAr,&m,&d);		if (m==iManudur && d==iDagur) return 13;//DagurAnnar_i_Paskum
		DagurOskudagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return -2;//�skudagur	rr	
		DagurBolludagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return -8;//bolludagur
		DagurSprengidagur(iAr,&m,&d);		if (m==iManudur && d==iDagur) return -9;//sprengidagur
		DagurPalmasunnudagur(iAr,&m,&d);	if (m==iManudur && d==iDagur) return  18;//P�lmasunnudagur
	}//if (iManudur<=iPaskaMan)
	
	DagurHvitasunnudagur(iAr,&m,&d);		if (m==iManudur && d==iDagur) return 4;//Hv�tasunnudagur
	DagurAnnar_i_Hvitasunnu(iAr,&m,&d);		if (m==iManudur && d==iDagur) return 15;//Annar � hv�tasunnu
	//komi� getur fyrir a� uppstigningardagur lendi � sama dag og 1. ma�(verkl��sdag) �� s�st �essi dagur aldrei
	DagurUppstigningardagur(iAr,&m,&d);		if (m==iManudur && d==iDagur) return 5;//Uppstigningardagur	
	DagurSjomannadagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return  16;//sj�mannadagur
	DagurMaedradagur(iAr,&m,&d);			if (m==iManudur && d==iDagur) return  -15;//m��radagur
	DagurAdventa(iAr,&m,&d);				if (m==iManudur && d==iDagur) return  17;//a�venta
	DagurSumardagurinnFyrsti(iAr,&m,&d);	if (m==iManudur && d==iDagur) return  -1;//sumardagurinn fyrsti
	
	if ( 2==iManudur && 14==iDagur)				return -3;//Valent�nusdagur
	if (12==iManudur &&  1==iDagur)				return -4;//fullveldisdagurinn 
	if ( 2==iManudur && 29==iDagur)				return -10;//hlaup�rsdagur
	if (11==iManudur && 11==iDagur)				return -12;//dagur �slenskrar tungu
	if ( 6==iManudur && 24==iDagur)				return -16;//J�nsmessa


	DagurFridagurVerslunarmanna(iAr,&m,&d);	
	if (m==iManudur && d==iDagur)
		return 6;//fr�dagur verslunarmanna fyrist m�nudagur � �g�st
	iVikudagur=vikudagur(iAr, iManudur, iDagur);

	//konudagur og b�ndadagur semma ekki �ri� 2023
	//vetrardagur, fyrsti, laugardagurinn a� lokinni 26. viku (� sumarauka�rum 27. viku) sumars. Fyrsta vetrardag ber upp � 21.-27. okt�ber, nema � r�mspillis�rum: 28. okt�ber. 
	if (10==iManudur && 28==iDagur && erRimspillisar(iAr))
		return -7;//fyrist vetrardagur
	if (10==iManudur &&  20<iDagur &&  28>iDagur && 6==iVikudagur/*!erRimspillisar(iAr) ekki �arf a� t�kka � �essu vegna return fyrir ofan*/)
		return -7;//fyrist vetrardagur
	
	//finna b�ndadag sem er fyrsti dagur �orra
	//�orri, 4. m�nu�ur vetrar a� �slensku t�matali; hefst  me� f�studegi � 
	//13. viku vetrar (19.-25. jan. nema � eftir r�mspillis�ri, �� 26. jan.).
	if (1==iManudur &&  18<iDagur &&  27>iDagur)				
	{
		
		if (26==iDagur && erRimspillisar(iAr-1))
		{
				return -5;//b�ndadagur
		}
		else
		{
			if (5==iVikudagur && iDagur!=26)
				return -5;//b�ndadagur
		}
	}//b�ndadagur if (1==iManudur &&  18<iDagur &&  27>iDagur)				

	//konudagur, fyrsti dagur "g�u". Sagt er a� h�sfreyjur hafi �tt a� fagna g�u �ennan dag, og a� b�ndur hafi �tt a� gera h�sfreyjum eitthva� vel til. �ess munu einnig d�mi, a� hlutverk hj�nanna � �essum si� hafi veri� hin gagnst��u. 
	//g�a (��ur g�i), fimmti m�nu�ur vetrar a� forn�slensku t�matali; hefst me� sunnudegi � 18. viku vetrar (18.- 24. febr�ar, nema � eftir r�mspillis�ri, �� 25. febr�ar). Nafnsk�ring �viss. 
	if (2==iManudur &&  25==iDagur && erRimspillisar(iAr))
		return -6;//konudagur
	if (2==iManudur &&  17<iDagur &&  25>iDagur && 0==iVikudagur && !erRimspillisar(iAr))
		return -6;//konudagur

	
//	finna bolludag
    //bolludagur, m�nudagurinn � "f�stuinngang". Nafni� er kennt vi� bollur sem si�ur er a� bor�a �ennan dag. ��tt si�urinn s� erlendur mun nafni� upprunni� � �slandi.
	//f�stuinngangur (f�stu�gangur, f�stugangur), fyrstu dagar �eirrar viku sem langafasta hefst �, �. e. sunnudagur, m�nudagur og �ri�judagur � undan �skudegi, e�a a�eins fyrsti dagurinn af �essum �remur (f�stuinngangs-sunnudagur). 
//	finna a�ventu
	//a�venta, "j�lafasta". Nafni� er dregi� af latneska or�inu adventus sem merkir koma, �. e. koma Krists, og sk�rskotar til j�lanna sem fram undan eru. 
	//j�lafasta (a�venta), tr�arlegt f�stut�mabil � undan j�lunum. Hefst me� 4. sunnudegi fyrir j�ladag, �.e. 27. n�v. - 3. des. 
//	finna b�ndadag
	//b�ndadagur, fyrsti dagur "�orra", mi�svetrardagur. �essi dagur var tyllidagur a� fornu. Sagt er a� b�ndur hafi �� �tt a� "bj��a �orra � gar�" og a� h�sfreyjur hafi �tt a� gera b�ndum eitthva� vel til. Einnig munu finnast d�mi um �a� a� hlutverk hj�nanna � �essum si� hafi veri� hin gagnst��u. 
	//�orri, 4. m�nu�ur vetrar a� �slensku t�matali; hefst  me� f�studegi � 13. viku vetrar (19.-25. jan. nema � eftir "r�mspillis�ri", �� 26. jan.). Nafnsk�ring �viss. 
	//r�mspillis�r (varna�ar�r), �a� �r sem "r�mspillir" hefst.
	//r�mspillir, t�mabil � �slenska misseristalinu �egar allir vi�mi�unart�mar tengdir g�mlu misserunum ver�a degi seinna (mi�a� vi� dagsetningar e�a messudaga) en m�gulegt er samkv�mt venjulegum r�mreglum. �etta gerist � �au skipti sem "sumarauka" er skoti� inn degi s��ar en venjulega, oftast � 28 �ra fresti. R�mspillir stendur fr� "sumaraukanum", �. e. fr� mi�sumri,  fram � hlaup�rsdag n�sta �r. 
	// sumarauki (lagningarvika, vi�lagning, vi�urlag), innskotsvika sem b�tt er inn � �slenska misseristali� � nokkurra �ra fresti til a� samr�ma �a� hinu n�tt�rlega �rst��a�ri. � tveimur misserum (sumri og vetri) teljast venjulega t�lf m�nu�ir �r�tugn�ttir og fj�rar n�tur umfram (aukan�tur), e�a 364 dagar samtals. �rst��a�ri� er r�mum degi lengra. Af �v� lei�ir, a� me� hverju �ri sem l��ur ver�a b��i sumar og vetur � misseristalinu st��ugt fyrr � fer�inni mi�a� vi� �rst��irnar ef ekki er lagf�rt me� innskotsd�gum. Lagf�ringin er framkv�md � �ann h�tt a� einni viku (sumarauka) er skoti� inn � eftir aukan�ttum svo a� mi�sumar, og �ar me� n�sta sumarkoma n�u m�nu�um (270 d�gum) s��ar, ver�ur viku seinna en ella hef�i or�i�. Eftir n�gildandi reglu (� gregor�anska t�matalinu e�a n�ja st�l) m� sumardagurinn fyrsti ekki koma fyrr en 19. apr�l. Sumaraukanum er �v� skoti� inn � hvert sinn sem fyrirsj�anlegt er a� sumardagurinn fyrsti myndi annars koma of snemma n�sta �r (18. e�a 17. apr�l). H�gt er a� s�na fram � a� sumarauki hefst alltaf 22. j�l� ef s� dagur er sunnudagur, en 23. j�l� ef s� dagur er sunnudagur og hlaup�r fer � h�nd. Sumarauka�r ver�a �ll �r sem enda � m�nudegi, svo og �r sem enda � sunnudegi ef hlaup�r fer � h�nd.
	//� prentu�um alman�kum �slenskum fram til 1928 var sumarauka b�tt aftan vi� s��asta sumarm�nu�, en eftir �a� var horfi� a� �eim eldri reglum sem a� ofan greinir.
	//� gamla st�l (j�l�anska t�matalinu) var sumarauka skoti� inn �au �r sem endu�u � fimmtudegi, svo og �au �r sem endu�u � mi�vikudegi, ef n�sta �r var hlaup�r. Me� �essu m�ti var sumardagurinn fyrsti aldrei fyrr en 9. apr�l. 
	//Fyrstu reglur um sumarauka voru l�gteknar um mi�ja 10. �ld a� r��i �orsteins surts.



/*H�t��ir sem fylgja p�skunum 

�msir merkisdagar kirkjunnar flytjast til � �rinu me� p�skunum svo sem kunnugt er. �essa daga er h�gt a� finna me� s�mu a�fer� og notu� er til a� finna p�skana, nema hva� dagsetningarnar � fingrunum ver�a a�rar en ��r sem s�ndar eru � 26. mynd. Ef vi� t�kum hv�tasunnuna sem d�mi, getur h�n � fyrsta lagi or�i� 10. ma� (�egar p�skar eru 22. mars). Til �ess a� finna hv�tasunnuna tilteki� �r byrjum vi� � �v� a� leita uppi fingursta� p�skadagsins, en �egar a� �v� kemur a� finna �� dagsetningu sem svarar til fingursta�arins, ver�um vi� � sta� 22. mars a� setja 10. ma� � uppli� v�sifingurs innanver�an og telja �a�an. Kemur �� 11. ma� � mi�li� v�sifingurs innanver�an, 12. ma� � framli� v�sifingurs innanver�an o. s. frv. �ar til komi� er a� 13. j�n� � utanver�um uppli� litlafingurs h�gri handar, en �a� er s��asti fingursta�urinn. Kemur �a� heim, a� hv�tasunnan er 13. j�n� �au �r sem p�skana ber upp � 25. apr�l. 

hv�tasunnudagur og uppstigningardagur fylgja p�skunum sem s�r segir: 
  

P�skar ............. 22. mars til 25. apr�l 
�skudagur ..........  4. febr�ar til 10. mars //�skudagur, mi�vikudagur � 7. viku fyrir p�ska
Uppstigningardagur . 30. apr�l til 3. j�n� 
Hv�tasunna ......... 10. ma� til 13. j�n� 

Me� �v� a� athuga almanaki� getur lesandinn h�glega 
fundi� fleiri t�mam�rk, s. s. fyrir n�uviknaf�stu, 
bolludag, sprengidag, p�lmasunnudag, 
k�ngsb�nadag, tr�nitatis og d�radag. 
*/
	return 0;
}

// Falli� skilar texta dagsetningar sem falli� erHatid fann.
// Skilagildi� fr� fallinu ber a� afrita strax �v� �ll f�ll � klasanum sem skila streng nota s�mu breytu.
// Skilagildi fallsins ber a� afrita strax �v� �ll f�ll � klasanum sem skila streng nota sama minnish�lf(breytu).
// Ef villa skilar falli� NULL
// Not thread save
//  D�mi um notkun: 
//		CDagsetning cDags;
//		m_cstring str;
//  	int i=cDags.erHatid(2004, 4, 11);
//  	if (i!=0)
//  		str=cDags.NafnHatidardags(i);
//      N� inniheldur str textann "p�skadagur" 

char * CDagsetning::NafnHatidardags(int iHatidarIndex)
{
	if (!iHatidarIndex || iHatidarIndex==0)
		return 0;
	
	unsigned short us;
	if (iHatidarIndex<0)//Ekki h�t��ardagur en til er textastrengur fyrir vi�komandi dagsetningu
	{
		us=iHatidarIndex*-1;

		switch(us)
		{
			case 1 : m_cstr="sumardagurinn fyrsti";		break;
			case 2 : m_cstr="�skudagur";				break;
			case 3 : m_cstr="valent�nusdagur";			break;
			case 4 : m_cstr="fullveldisdagurinn";		break;
			case 5 : m_cstr="b�ndadagur";				break;
			case 6 : m_cstr="konudagur";				break;
			case 7 : m_cstr="fyrsti vetrardagur";		break;
			case 8 : m_cstr="bolludagur";				break;
			case 9 : m_cstr="sprengidagur";				break;
			case 10 : m_cstr="hlaup�rsdagur";			break;
		  //case 11 : m_cstr="";						break;
			case 12 : m_cstr="dagur �slenskrar tungu";	break;
			case 13 : m_cstr="�rett�ndinn";				break;
			case 14 : m_cstr="�orl�ksmessa";			break;
			case 15 : m_cstr="m��radagur";				break;
			case 16 : m_cstr="j�nsmessa";				break;
			
			default: return 0;

		}//switch(us)
		return m_cstr.getString();
	}//if (us<0)//Ekki h�t�� en til er textastrengur fyrir vi�komandi dagsetningu
	us=iHatidarIndex;

	switch(us)//H�t��ardagur
	{
		case 1 : m_cstr="p�skadagur";				break;
		case 2 : m_cstr="a�fangadagur";				break;
		case 3 : m_cstr="j�ladagur";				break;
		case 4 : m_cstr="hv�tasunnudagur";			break;
		case 5 : m_cstr="uppstigningardagur";		break;
		case 6 : m_cstr="fr�dagur verslunarmanna";	break;
		case 7 : m_cstr="n��rsdagur";				break;
		case 8 : m_cstr="gaml�rsdagur";				break;
		case 9 : m_cstr="annar � j�lum";			break;
		case 10: m_cstr="verkal��sdagur";			break;
		case 11: m_cstr="f�studagurinn langi";		break;
		case 12: m_cstr="sk�rdagur";				break;
		case 13: m_cstr="annar � p�skum";			break;
		case 14: m_cstr="�j��h�t��ardagurinn";		break;
		case 15 : m_cstr="annar � hv�tasunnu";		break;
		case 16 : m_cstr="sj�mannadagur";			break;
		case 17 : m_cstr="a�venta";					break;
		case 18 : m_cstr="p�lmasunnudagur";			break;
			
		default: return 0;
	}
	return m_cstr.getString();
}


/*
 *	Count of days, which is Feb 29, from Jan 1, 0 to Jan 1, nYear
 *	There is no Feb 29 between Jan 1, 0 and Jan 1, -3, one between Jan 1, 0 and Jan 1, -4
 *	one between Jan 1, 0 and Jan 1, 3 AD, one between Jan 1, 0 and Jan 1, 4
 */
int	CountOfFeb29( int nYear )
{
	int	nCount = 0;

	if( nYear > 0 ) 
	{
		nCount = 1;	/* Year 0 is a leap year */
		nYear--;/* Year nYear is not in the period */
	}
	nCount += nYear / 4 - nYear / 100 + nYear / 400;

	return nCount;
}
// Skilar vikudag dagsetningar 0=sunnudagur, 1=m�nudagur o.s.fr.
 /**************************************************************************
 *                                                                         *
 *   In the Gregorian calendar, which is widely used now, the year AD 1    *
 *   is directly preceded by the year 1 BC; a year 0 does not exist in     *
 *   this system. In contrast, astronomical reckoning indeed uses a year   *
 *   0. For the purpose of distinction, astronomical reckoning drops the   *
 *   symbols AD and BC and uses a plus or minus sign before the year       *
 *   instead. The astronomical year +1 therefore corresponds to the year   *
 *   AD 1, the year 0 corresponds to 1 BC, and the year -1 to 2 BC. For    *
 *   convenience, I'll use astronomical years in the program.              *
 *                                                                         *
 ***************************************************************************/
// Skilar vikudag dagsetningar 0=sunnudagur, 1=m�nudagur o.s.fr.
unsigned short CDagsetning::vikudagur(int nYear, int nMonth, int nDay)
{
	int	nDayOfWeek;
	const static int	pnDaysBeforeMonth[] = {
		 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
	};
	
	if (!( nMonth > 0 && nMonth <= 12 )||
		!( nDay > 0 )||
		!( nDay <= ( pnDaysBeforeMonth[ nMonth+1 ] - pnDaysBeforeMonth[ nMonth ] )
		|| ( nMonth == 2 && nDay == 29 && erHlaupar(nYear) ))
		)
		return -1;
	
	/* the day of Jan 1, nYear */
	nDayOfWeek = 6 + nYear % 7 + CountOfFeb29(nYear) % 7 + 14;/* + 14 : makes nDayOfWeek >= 0 */
	
	/* the day of nMonth 1, nYear */
	nDayOfWeek += pnDaysBeforeMonth[ nMonth ];
	if( nMonth > 2 && erHlaupar(nYear) )	nDayOfWeek++;
	
	/* the day of nMonth nDay, nYear */
	nDayOfWeek += nDay - 1;
	nDayOfWeek %= 7;
	
	return nDayOfWeek;
}
//skilar m�nu�i
unsigned int CDagsetning::ArsDagarToManudur(int iAr, unsigned int ArsManudarDagar)
{
	unsigned int i=erHlaupar(iAr);
	if (!ArsManudarDagar || ArsManudarDagar>365+i)
		return 0;
	ArsManudarDagar--;
	if (ArsManudarDagar<  31  ) return 1;
	if (ArsManudarDagar<  59+i) return 2;
	if (ArsManudarDagar<  90+i) return 3;
	if (ArsManudarDagar< 120+i) return 4;
	if (ArsManudarDagar< 151+i) return 5;
	if (ArsManudarDagar< 181+i) return 6;
	if (ArsManudarDagar< 212+i) return 7;
	if (ArsManudarDagar< 243+i) return 8;
	if (ArsManudarDagar< 273+i) return 9;
	if (ArsManudarDagar< 304+i) return 10;
	if (ArsManudarDagar< 334+i) return 11;
	if (ArsManudarDagar< 365+i) return 12;
	
	return 0;
}
//skilar �rsd�gum
unsigned int CDagsetning::ArsManudurToDagar(int iAr, int iManudur)
{
	if (!iAr || iAr<0 || !iManudur)
		return 0;
	int i=erHlaupar(iAr);
	switch(iManudur)
	{
		case 1 : return 31;
		case 2 : return 59+i;
		case 3 : return 90+i;
		case 4 : return 120+i;
		case 5 : return 151+i;
		case 6 : return 181+i;
		case 7 : return 212+i;
		case 8 : return 243+i;
		case 9 : return 273+i;
		case 10: return 304+i;
		case 11: return 334+i;
		case 12: return 365+i;
	}
	
	return 0;
}
//ey�ir tilteknum dagafj�lda �r dagsetningu.
//uiRemove fj�ldi daga til a� ey�a
//iAr �r dagsetningar sem breyta �
//iManudur m�nu�ur dagsetningar breyta �.
//iDagur dagur dagsetningar breyta �.
void CDagsetning::DaysDelete(int *iAr, int *iManudur, int *iDagur, unsigned int uiRemove)
{
	int iTmpAr=*iAr, iTmpMan=*iManudur, iTmpDag=*iDagur, i;
	unsigned int uiArsDagaFjoldi=ArsManudurToDagar(iTmpAr, iTmpMan-1);
	uiArsDagaFjoldi+=iTmpDag;
	while (uiRemove>(unsigned int)(365+erHlaupar(iTmpAr)))
	{
		uiRemove-=(365+erHlaupar(iTmpAr));
		iTmpAr--;
	}
	uiArsDagaFjoldi-=uiRemove;
	iTmpMan=ArsDagarToManudur(iTmpAr, uiArsDagaFjoldi);
	i=ArsManudurToDagar(iTmpAr, iTmpMan-1);
	iTmpDag=uiArsDagaFjoldi-i;
	*iAr=iTmpAr;
	*iManudur=iTmpMan;
	*iDagur=iTmpDag;


	/*
	int months[]={0 ,31 ,28 ,31 ,30 ,31 ,30 ,31 ,31 ,30 ,31 ,30 ,31 };
		//        0  1   2   3   4   5   6   7   8   9   10  11  12

		if (erHlaupar(*iAr)) months[2]=29;
		*iDagur-=uiRemove;
		while ( *iDagur < 1)
			{	*iManudur=*iManudur-1;
				*iDagur+=months[*iManudur];
				
				if (*iManudur<1)
					{
						*iAr=*iAr-1;
						*iManudur=12;
						if (erHlaupar(*iAr))	months[2]=29;
						else					months[2]=28;
					}	
			}//days no more than a month will allows
	*/
}
//b�tir tilteknum dagafj�lda vi� dagsetningu.
//uiAdd fj�ldi daga til a� b�ta vi�
//iAr �r dagsetningar sem breyta �
//iManudur m�nu�ur dagsetningar breyta �.
//iDagur dagur dagsetningar breyta �.
void CDagsetning::DaysAdd(int *iAr, int *iManudur, int *iDagur, unsigned int uiAdd)
{		//           j   f   m   a   m   j   j   a   s   o   n   d 
	int months[]={0 ,31 ,28 ,31 ,30 ,31 ,30 ,31 ,31 ,30 ,31 ,30 ,31 };
		//        0  1   2   3   4   5   6   7   8   9   10  11  12
	    //           31 ,59, 90, 120,151,181,212,243,273,304,334,365

		if (erHlaupar(*iAr)) months[2]=29;
		*iDagur=*iDagur+uiAdd;
		while ( *iDagur > (months[*iManudur]) )
			{
				*iDagur=*iDagur-months[*iManudur];
				*iManudur=*iManudur+1;
				if (*iManudur>12)
					{
						*iAr=*iAr+1;
						*iManudur=0;
						if (erHlaupar(*iAr))	months[2]=29;
						else					months[2]=28;
					}	
			}//days no more than a month will allows
		
		
		while ( *iManudur > 12 )	
		{
			*iManudur-=12;//should never happen just a debug check
			*iAr=*iAr+1;
		}//months no more than 12;

}

bool CDagsetning::erHlaupar(int iAr)
{
	if (!(iAr%4))
	{
		if (!(iAr%100))
		{
			if (!(iAr%400))
				return 1;									
			return 0;
		}//if (gengur(year,100))			
		return 1;
	}//if gengur(year,4)
	return 0;
}

bool CDagsetning::erRimspillisar(int iAr)
{  //r�mspillis�r ver�a �ll �r sem enda � m�nudegi, svo og �r sem enda � sunnudegi ef hlaup�r fer � h�nd.
	int iVikudagur=vikudagur(iAr, 12, 31);
//	if (iVikudagur==1)
//		return true;
	if (iVikudagur==0 && erHlaupar(iAr+1))
		return true;
	
	return false;
}

//In iAr
//out iManudur og iDagur
//iManudur og iDagur innihalda dagsetningu f�studagsins langa sem er alltaf � f�studegi
void CDagsetning::DagurFostudagurinnLangi(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 2);
}
//In iAr
//out iManudur og iDagur
//iManudur og iDagur innihalda dagsetningu Sk�rdags sem er alltaf � fimmtudegi
void CDagsetning::DagurSkirdagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 3);
}
//In iAr
//out iManudur og iDagur
//iManudur og iDagur innihalda dagsetningu annars � p�skum sem er alltaf � m�nudegi
void CDagsetning::DagurAnnar_i_Paskum(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysAdd(&iAr, iManudur, iDagur, 1);
}
//p�lmasunnudagur 
//In iAr
//out iManudur og iDagur
//iManudur og iDagur innihalda dagsetningu P�lmasunnudags sem er alltaf sunnudaginn fyrir p�ska.
void CDagsetning::DagurPalmasunnudagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 7);
}
//Bolludagur ..........  
void CDagsetning::DagurBolludagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 48);
}
//Sprengidagur ..........  
void CDagsetning::DagurSprengidagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 47);
}
//�skudagur ..........  4. febr�ar til 10. mars //�skudagur, mi�vikudagur � 7. viku fyrir p�ska
void CDagsetning::DagurOskudagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysDelete(&iAr, iManudur, iDagur, 46);
}

//Hv�tasunna ......... 10. ma� til 13. j�n� 
void CDagsetning::DagurHvitasunnudagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysAdd(&iAr, iManudur, iDagur, 49);
}
void CDagsetning::DagurAnnar_i_Hvitasunnu(int iAr, int *iManudur, int *iDagur)
{
	DagurHvitasunnudagur(iAr, iManudur, iDagur);
	DaysAdd(&iAr, iManudur, iDagur, 1);
}
//komi� getur fyrir a� uppstigningardagur lendi � sama dag og 1. ma�(verkl��sdag)
//Uppstigningardagur . 30. apr�l til 3. j�n� 
void CDagsetning::DagurUppstigningardagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=DagurPaskar(iAr, iDagur);
	DaysAdd(&iAr, iManudur, iDagur, 39);
}

//fr�dagur verslunarmanna fyrist m�nudagur � �g�st 
void CDagsetning::DagurFridagurVerslunarmanna(int iAr, int *iManudur, int *iDagur)
{//2.8.2004 er fr�dagur verslunarmanna
	*iManudur=8;
	*iDagur=FyrstiVikudagur(1, iAr, *iManudur);
}

//m��radagurinn, al�j��legur dagur til a� hei�ra m��ur, haldinn annan sunnudag ma�m�na�ar �r hvert.
void CDagsetning::DagurMaedradagur(int iAr, int *iManudur, int *iDagur)
{
	*iManudur=5;
	*iDagur=FyrstiVikudagur(0, iAr, *iManudur)+7;
	return;//todo: annar sunnudagur � ma� (2004 er hann 9.ma�)
}
//sj�mannadagurinn, h�t��isdagur tileinka�ur sj�m�nnum, haldinn fyrsta sunnudag � j�n�, nema s� dagur s� hv�tasunnudagur, �� er sj�mannadagurinn viku s��ar. �essari reglu hefur veri� fylgt allar g�tur s��an 1938, ef fr� eru talin �rin 1965-1968,  en �au �r var haldi� upp � sj�mannadaginn � ma�m�nu�i.
void CDagsetning::DagurSjomannadagur(int iAr, int *iManudur, int *iDagur)
{   //todo: sj�mannadagur er fyrsti sunnudagur � j�n� nema
	//ef s� dagur er hv�tasunnudagur �� er sj�mannadagurinn
	//annan sunnudag � j�n�(2004 er hann 6.j�n�)
	DagurHvitasunnudagur(iAr, iManudur, iDagur);
	if (*iManudur==6 && *iDagur<8)
	{
		*iDagur=*iDagur+7;//sj�mannadagur f�rist � n�stu viku vegna hv�tasunnu
		return;
	}
	*iManudur=6;
	*iDagur=FyrstiVikudagur(0, iAr, *iManudur);
}

//j�lafasta (a�venta), tr�arlegt f�stut�mabil � undan j�lunum. Hefst me� 4. sunnudegi fyrir j�ladag, �.e. 27. n�v. - 3. des.
void CDagsetning::DagurAdventa(int iAr, int *iManudur, int *iDagur)
{	*iManudur=11;
	*iDagur=27;

	*iDagur=FyrstiVikudagur(0, iAr, *iManudur, 27);
	if (*iDagur>30)
	{
		*iManudur=12;
		*iDagur=*iDagur-30;
	}

	return;//todo: (2004 er hann 28.n�vember)www
}
//Finnur og skilar fyrsta dag m�na�ar sem hefur vikudaginn sem tiltekinn er � iFinnaVikudag.
//Athugi�:      Falli� villuleitar ekki.  �annig a� � notkun fallsins skaltu vera
//              viss um a� �� s�rt a� senda l�gleg gildi � f�ribreytum fallsins.
//iDagur:       �essi breyta m� vera NULL og er �a� sj�lfgildi hennar.
//              Ef h�n er NULL �� skilar falli� fyrsta dag m�na�ar sem er tiltekinn er � iFinnaVikudag.
//              Ef h�n er Ekki tiltekin �� mun falli� leita fr� og me� �eim dag sem tiltekinn er.
//              Var��:  Falli� mun ekki villuleita hvort dagsetningin er l�gleg.
//              D�mi:  Ef f�ribreytur eru t.d. �essar:  iAr=2004, iManudur=1 og iDagur=30 og iFinnaVikudag=1
//              �� mun falli� skyla 33 sem er �l�gleg dagsetning �.e.a.s "33. jan�ar 2004" er ekki til.
//iFinnaVikudag:Hva�a vikudag skal leita a�.  L�gleg gildi eru fr� og me� 0 til 6 �ar sem 0 er sunnudagur og 6 er laugardagur.
int CDagsetning::FyrstiVikudagur(int iFinnaVikudag, int iAr, int iManudur, int iDagur)
{
	int iOffset=1, iAdd, iVikudagur;
	if (iDagur)
		iOffset=iDagur;
	iVikudagur=vikudagur(iAr, iManudur, iOffset);
	if (iVikudagur<=iFinnaVikudag)
		iAdd=(iFinnaVikudag-iVikudagur);
	else
		iAdd=(7+iFinnaVikudag-iVikudagur);
	
	return iAdd+iOffset;
}


void CDagsetning::DagurSumardagurinnFyrsti(int iAr, int *iManudur, int *iDagur)
{	*iManudur=4;
	*iDagur=FyrstiVikudagur(4, iAr, *iManudur, 19);

	return;//Sumardagurinn fyrsti er � � apr�l (4. m�n) fr� og me� 19-25
}

//todo:� a� taka sumars�lst��ur???
/*jafnd�gur, s� stund �egar s�l er beint yfir mi�baug jar�ar. �etta gerist tvisvar � �ri, � t�mabilinu 19.-21. mars (vorjafnd�gur) og 21.-24. september (haustjafnd�gur). Um �etta leyti er dagurinn (fr� s�laruppr�s til s�larlags) um �a� bil jafnlangur n�ttinni hvar sem er � j�r�inni, og af �v� er nafni� dregi�.  Breytileiki dagsetninganna stafar a�allega af �v� a� almanaks�ri� er ekki n�kv�mlega jafnlangt �rst��a�rinu, og samr�mingin vi� �rst��a�ri� ver�ur a� gerast � st�kkum, me� aukadegi � hlaup�rum.
� stj�rnufr��i teljast jafnd�gur � �v� augnabliki �egar mi�baugslengd s�lar er 0� e�a 180�. Mi�baugslengdin reiknast fr� vorpunkti, og munar litlu � �essari skilgreiningu og �eirri sem  ��ur var nefnd.  
*/
void CDagsetning::DagurVorjafndaegur(int iAr, int *iManudur, int *iDagur)
{//er �etta ekki reikna� eins og vetrardagurinn fyrist?
	return;//todo: hven�r byrjar vori�?  //19.-21. mars (vorjafnd�gur) (2004 er hann 20 mars)
}
void CDagsetning::DagurHaustjafndaegur(int iAr, int *iManudur, int *iDagur)
{//er �etta ekki reikna� eins og vetrardagurinn fyrist?
	return;//todo: hven�r byrjar hausti�?  //21.-24. september (haustjafnd�gur).
}

// Skilar dagafj�lda � m�nu�i
// Ef villa �� skilar falli� 0;
int CDagsetning::DagaFjoldi(int iAr, int iManudur)
{
	if (!iAr || iAr<0 ||
		!iManudur ||iManudur>12 || iManudur<1)
		return 0;

	int months[]={0 ,31 ,28 ,31 ,30 ,31 ,30 ,31 ,31 ,30 ,31 ,30 ,31 };
	months[2]+=erHlaupar(iAr);
	return months[iManudur];
}

// Skilar fj�lda virkra daga fr� og me� dagsetningum tilteknum � f�ribreytum
int CDagsetning::FjoldiVirkraDaga(int iFraAr, int iFraMan, int iFraDag, int iTilAr, int iTilMan, int iTilDag)
{
	CDagsetning cd;
	int iRet=0;
	cd.DaysDelete(&iFraAr, &iFraMan, &iFraDag, 1);
	do
	{	cd.DaysAdd(&iFraAr, &iFraMan, &iFraDag, 1);
		iRet+=cd.erVirkurDagur(iFraAr, iFraMan, iFraDag);
		
	}while(!(iFraAr==iTilAr && iFraMan==iTilMan &&iFraDag==iTilDag));
	return iRet;
}
// Skilar fj�lda fr�daga daga fr� og me� dagsetningum tilteknum � f�ribreytum
	// Til fr�daga teljast helgidagar og h�t��ardagar
int  CDagsetning::FjoldiFriDaga(int iFraAr, int iFraMan, int iFraDag, int iTilAr, int iTilMan, int iTilDag)
{
	CDagsetning cd;
	int iRet=0;
	cd.DaysDelete(&iFraAr, &iFraMan, &iFraDag, 1);
	do
	{	cd.DaysAdd(&iFraAr, &iFraMan, &iFraDag, 1);
		iRet+=!cd.erVirkurDagur(iFraAr, iFraMan, iFraDag);
		
	}while(!(iFraAr==iTilAr && iFraMan==iTilMan &&iFraDag==iTilDag));
	return iRet;
}
//athugar hvort dagur er virkur e�a ekki
//Falli� skilar 0 ef dagurinn er sunnudagur, laugardagur e�a h�t��ardagur
bool CDagsetning::erVirkurDagur(int iAr, int iManudur, int iDagur)
{
	int iVikudagur=vikudagur(iAr, iManudur, iDagur);
	if (iVikudagur==0 || iVikudagur==6)
		return 0;//Helgidagur
	if (erHatid(iAr, iManudur, iDagur)>0)
		return 0;//H�t��ardagur
	return 1;//Virkur dagur


}